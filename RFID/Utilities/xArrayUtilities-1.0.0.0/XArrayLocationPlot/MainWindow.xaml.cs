using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Reflection;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Shapes;
using Impinj.OctaneSdk;
using System.Configuration;

namespace XArrayLocationPlot
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private Random rand = new Random();
        private Dictionary<string, PlotPointInfo> points = new Dictionary<string, PlotPointInfo>();
        private ImpinjReader reader = new ImpinjReader();

        private int colorPtr = 0;
        private List<Color> systemColors = new List<Color>();

        private Dictionary<string, Color> colorMap = new Dictionary<string, Color>();

        private const double STROKE_THICKNESS = 1;
        private const double POINT_SIZE_PERCENTAGE = 2;

        private StreamWriter logFile;

        public MainWindow()
        {
            InitializeComponent();

            // Assign an event handler to catch all unhandled exceptions.
            AppDomain currentDomain = AppDomain.CurrentDomain;
            currentDomain.UnhandledException += new UnhandledExceptionEventHandler(UnhandledExceptionHandler);

            // Initialize the color array
            PropertyInfo[] props = typeof(Colors).GetProperties();
            foreach (PropertyInfo propInfo in props)
            {
                Color color = (Color) propInfo.GetValue(null, null);
                // Don't plot white
                if (color != Colors.White)
                {
                    systemColors.Add(color);
                }
            }

            // Register to receive location events from xArray
            reader.LocationReported += OnLocationReported;
            reader.DiagnosticsReported += OnDiagnosticsReported;

            // Get the path to the application directory
            string appPath = System.IO.Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location) + "\\"; 
            OpenNewLogFile(appPath + "\\log\\");

            // If a user-defined color map exists, load it.
            string mapFile = appPath + "\\color_map.txt";
            if (File.Exists(mapFile))
            {
                LoadColorMap(mapFile);
            }

            try
            {
                StartXArray();
            }
            catch (Exception ex)
            {
                // An error occurred, display the message
                MessageBox.Show(ex.Message);
                Application.Current.Shutdown();
            }
        }

        private void LoadColorMap(string mapFile)
        {
            string[] lines = File.ReadAllLines(mapFile);

            foreach (string l in lines)
            {
                string line = l.Trim();

                // Ignore comments and blank lines
                if (!line.StartsWith("//") && line.Length > 0)
                {
                    string[] kv = line.Split('=');

                    colorMap.Add(kv[0].Trim(), (Color)ColorConverter.ConvertFromString(kv[1]));
                }
            }
        }

        private void StartXArray()
        {
            reader.Connect(Properties.Settings.Default.ReaderAddress);
            Settings settings = reader.QueryDefaultSettings();

            // Put the xArray into location mode
            settings.XArray.Mode = XArrayMode.Location;

            // Enable all of the report types
            settings.XArray.Location.EntryReportEnabled = true;
            settings.XArray.Location.UpdateReportEnabled = true;
            settings.XArray.Location.ExitReportEnabled = true;
            settings.XArray.Location.DiagnosticReportEnabled = true;

            // Set xArray placement parameters

            // The mounting height of the xArray, in centimeters
            settings.XArray.Placement.HeightCm = Properties.Settings.Default.PlacementHeightCm;
            // These settings aren't required in a single xArray environment
            // They can be set to zero (which is the default)
            settings.XArray.Placement.FacilityXLocationCm = Properties.Settings.Default.FacilityXLocationCm;
            settings.XArray.Placement.FacilityYLocationCm = Properties.Settings.Default.FacilityYLocationCm;
            settings.XArray.Placement.OrientationDegrees = Properties.Settings.Default.OrientationDegrees;

            // Set xArray location parameters
            settings.XArray.Location.MotionWindowSeconds = Properties.Settings.Default.MotionWindowSec;
            settings.ReaderMode = Properties.Settings.Default.ReaderMode;
            settings.Session = Properties.Settings.Default.Session;
            settings.XArray.Location.TagAgeIntervalSeconds = Properties.Settings.Default.TagAgeIntervalSec;
            settings.Filters.Mode = TagFilterMode.None;
            // Specify how often we want to receive location reports
            settings.XArray.Location.ReportIntervalSeconds = Properties.Settings.Default.ReportIntervalSec;

            // Filter tags if enabled
            if (Properties.Settings.Default.TagFilterEpc.Trim().Length > 0)
            {
                // Setup a tag filter.
                // Only the tags that match this filter will respond.
                // We want to apply the filter to the EPC memory bank.
                settings.Filters.TagFilter1.MemoryBank = MemoryBank.Epc;
                // Start matching at the third word (bit 32), since the 
                // first two words of the EPC memory bank are the
                // CRC and control bits. BitPointers.Epc is a helper
                // enumeration you can use, so you don't have to remember this.
                settings.Filters.TagFilter1.BitPointer = BitPointers.Epc;
                // Only match tags with EPCs that start with the specified value
                settings.Filters.TagFilter1.TagMask = Properties.Settings.Default.TagFilterEpc;

                // Set the filter mode. Use only the first filter
                settings.Filters.Mode = TagFilterMode.OnlyFilter1;
            }

            // Apply the newly modified settings.
            reader.ApplySettings(settings);

            // Start the reader
            reader.Start();
        }

        private void StopXArray()
        {
            reader.Stop();
        }

        private Ellipse PlotPoint(Point p, Color color)
        {
            // Plot the point
            Ellipse dot = new Ellipse();
            dot.Stroke = System.Windows.Media.Brushes.Black;
            dot.StrokeThickness = 1;
            dot.Fill = new SolidColorBrush(color);
            dot.Height = canvasPlot.ActualHeight * (POINT_SIZE_PERCENTAGE / 100);
            dot.Width = canvasPlot.ActualWidth * (POINT_SIZE_PERCENTAGE / 100);
            dot.HorizontalAlignment = HorizontalAlignment.Left;
            dot.VerticalAlignment = VerticalAlignment.Top;
            canvasPlot.Children.Add(dot);

            // Translate the coordinates to a point on the plot
            p = TranslateCoordinates(p);

            // Position the dot
            Canvas.SetLeft(dot, p.X);
            Canvas.SetTop(dot, p.Y);

            // Receive mouse over events for this point
            dot.MouseEnter += OnPointMouseEnter;    

            return dot;
        }

        private Point TranslateCoordinates(Point p)
        {
            double dotHeight = canvasPlot.ActualHeight * (POINT_SIZE_PERCENTAGE / 100);
            double dotWidth = canvasPlot.ActualWidth * (POINT_SIZE_PERCENTAGE / 100);

            // Scale the X and Y based on the size of the canvas
            // First, calculate the number of pixels per centimeter for each axis 
            p.X *= (canvasPlot.ActualWidth / Properties.Settings.Default.XAxisCm);
            p.Y *= (canvasPlot.ActualHeight / Properties.Settings.Default.YAxisCm);

            // Adjust the coordinates. Canvas origin is upper left corner
            // We want it to be the center of the cartesian plane 
            p.X = p.X + (0.5 * canvasPlot.ActualWidth) - (dotWidth * 0.5);
            p.Y = (0.5 * canvasPlot.ActualHeight) - p.Y - (dotHeight * 0.5);

            return p;
        }

        private void DrawPlot()
        {
            this.InvalidateVisual();
            this.UpdateLayout();

            // Calculate dimensions of the largest square that will fit in the canvas
            int min = (int)Math.Min(columnCanvas1.ActualWidth + columnCanvas2.ActualWidth, 
                rowCanvas1.ActualHeight + rowCanvas2.ActualHeight);
            canvasPlot.Width = canvasPlot.Height = min;

            // Clear the canvas
            canvasPlot.Children.Clear();

            /*
            // Draw canvas border
            Rectangle rect = new Rectangle();
            rect.Stroke = System.Windows.Media.Brushes.LightGray;
            rect.StrokeThickness = STROKE_THICKNESS;
            rect.Fill = System.Windows.Media.Brushes.White;
            rect.Height = canvasPlot.ActualHeight;
            rect.Width = canvasPlot.ActualWidth;
            rect.HorizontalAlignment = HorizontalAlignment.Left;
            rect.VerticalAlignment = VerticalAlignment.Top;
            canvasPlot.Children.Add(rect);
            */

            // Draw the circle
            Ellipse circle = new Ellipse();
            circle.Stroke = System.Windows.Media.Brushes.LightGray;
            circle.StrokeThickness = STROKE_THICKNESS;
            circle.Fill = System.Windows.Media.Brushes.White;
            circle.Height = canvasPlot.ActualHeight;
            circle.Width = canvasPlot.ActualWidth;
            circle.HorizontalAlignment = HorizontalAlignment.Left;
            circle.VerticalAlignment = VerticalAlignment.Top;
            canvasPlot.Children.Add(circle);
            
            // X Axis
            Line x = new Line();
            x.X1 = 0;
            x.X2 = canvasPlot.ActualWidth;
            x.Y1 = canvasPlot.ActualHeight / 2;
            x.Y2 = canvasPlot.ActualHeight / 2;
            x.Stroke = System.Windows.Media.Brushes.LightGray;
            x.StrokeThickness = STROKE_THICKNESS;
            canvasPlot.Children.Add(x);

            // Y Axis
            Line y = new Line();
            y.X1 = canvasPlot.ActualWidth / 2;
            y.X2 = canvasPlot.ActualWidth / 2;
            y.Y1 = 0;
            y.Y2 = canvasPlot.ActualHeight;
            y.Stroke = System.Windows.Media.Brushes.LightGray;
            y.StrokeThickness = STROKE_THICKNESS;
            canvasPlot.Children.Add(y);

            // Plot the data
            foreach (KeyValuePair<string, PlotPointInfo> kv in points)
            {
                PlotPointInfo pointInfo = (PlotPointInfo) kv.Value;
                Ellipse point = PlotPoint(pointInfo.PointCoordinates, pointInfo.PointColor);
                pointInfo.RenderedPoint = point; 
            }
        }

        private void RemovePoint(string epc)
        {
            // Remove a point from the plot
            PlotPointInfo pointInfo = new PlotPointInfo();
            // Lookup the point associated with this EPC
            if (points.TryGetValue(epc, out pointInfo))
            {
                // Remove it from the screen
                canvasPlot.Children.Remove(pointInfo.RenderedPoint);
                
                // Remove it from the list of tags
                points.Remove(epc);
            }
        }

        private void UpdatePlot()
        {
            foreach (KeyValuePair<string, PlotPointInfo> kv in points)
            {
                PlotPointInfo pointInfo = (PlotPointInfo)kv.Value;
                Ellipse dot = pointInfo.RenderedPoint;
                if (dot == null)
                {
                    // This point has not been plotted yet. Plot it.
                    pointInfo.RenderedPoint = PlotPoint(pointInfo.PointCoordinates, pointInfo.PointColor);
                }
                else
                {
                    // This point has already been plotted. Just update the coordinates.
                    Point p = TranslateCoordinates(pointInfo.PointCoordinates);
                    Canvas.SetLeft(dot, p.X);
                    Canvas.SetTop(dot, p.Y);
                }
            }
        }

        private void OpenNewLogFile(string logDir)
        {
            // Create the data directory if necessary.
            if (!Directory.Exists(logDir))
            {
                Directory.CreateDirectory(logDir);
            }

            string filename = Properties.Settings.Default.ProfileName + "-";
            filename += Properties.Settings.Default.ReaderAddress + "-";
            filename += DateTime.Now.Month.ToString("00");
            filename += DateTime.Now.Day.ToString("00");
            filename += DateTime.Now.Year.ToString("0000");
            filename += DateTime.Now.Hour.ToString("00");
            filename += DateTime.Now.Minute.ToString("00");
            filename += DateTime.Now.Second.ToString("00");
            filename += ".txt";

            logFile = new StreamWriter(logDir + filename);

            // Write the application settings to the logfile
            foreach (SettingsProperty setting in Properties.Settings.Default.Properties)
            {
                WriteLineLog("// " + setting.Name + "=" + Properties.Settings.Default[setting.Name]);
            }
        }

        private void WriteLineLog(string line)
        {
            if (logFile.BaseStream != null)
            {
                logFile.WriteLine(line);
            }
        }

        private void CloseLogFile()
        {
            logFile.Close();
        }

        private void OnPointMouseEnter(object sender, MouseEventArgs e)
        {
            // Look up the tag associated with this point
            Ellipse selectedPoint = (Ellipse) sender;
            foreach (KeyValuePair<string, PlotPointInfo> kv in points)
            {
                PlotPointInfo pointInfo = (PlotPointInfo)kv.Value;
                if (pointInfo.RenderedPoint == selectedPoint)
                {
                    ToolTip tip = new ToolTip();
                    tip.Content = pointInfo.Epc;
                    selectedPoint.ToolTip = tip;
                }
            }
        }

        private void OnMainWindowResized(object sender, SizeChangedEventArgs e)
        {
            // Redraw the plot when the window is resized
            DrawPlot();
        }

        private void OnMainWindowLoaded(object sender, RoutedEventArgs e)
        {
            // Redraw the plot when the window is loaded
            DrawPlot();
        }

        protected override void OnRenderSizeChanged(SizeChangedInfo sizeInfo)
        {
            // Redraw the plot when the window is maximized
            base.OnRenderSizeChanged(sizeInfo);
            DrawPlot();
        }

        private Color AssignPointColor(string epc)
        {
            Color color;

            if (colorMap.Count > 0)
            {
                // A color map has been defined by the user.
                // Assign the specified color for this EPC.
                if (!colorMap.TryGetValue(epc, out color))
                {
                    // A color has not been specified for this EPC in the color map.
                    // Set the color to light gray.
                    color = Colors.LightGray;
                }
            }
            else
            {
                // A color map has not been specified. Assign colors in sequential order.
                if (colorPtr < systemColors.Count)
                {
                    // There are still colors left that haven't been assigned. Use one.
                    color = systemColors[colorPtr];
                    colorPtr++;
                }
                else
                {
                    // All the colors have been assigned. Use black.
                    color = Colors.Black;
                }
            }

            return color;
        }

        private void ProcessLocationReport(LocationReport report)
        {
            PlotPointInfo pointInfo;

            if (report.ReportType == LocationReportType.Exit)
            {
                // Exit report. Remove tag.
                RemovePoint(report.Epc.ToHexString());
            }
            else
            {
                // This is an Entry or Update report

                // Create a new PlotPointInfo if we haven't plotted this tag before
                if (!points.TryGetValue(report.Epc.ToHexString(), out pointInfo))
                {
                    // This is a new tag. 

                    // Determine the color
                    Color color = AssignPointColor(report.Epc.ToHexString());
                    
                    // Add it to the list of points.
                    pointInfo = new PlotPointInfo();
                    pointInfo.Epc = report.Epc.ToHexString();
                    pointInfo.PointColor = color;
                    points.Add(pointInfo.Epc, pointInfo);
                }

                // Update the current coordinates for this tag
                pointInfo.PointCoordinates = new Point(report.LocationXCm, report.LocationYCm);

                // Update the points on the plot
                UpdatePlot();
            }

            string sLong = String.Format("{0},{1},{2},{3},{4},{5},{6}",
                 report.ReportType, report.Timestamp, report.Epc.ToHexString(), report.LocationXCm, 
                 report.LocationYCm, report.ConfidenceFactors.ReadCount, IntListToCsv(report.ConfidenceFactors.Data));

            string sShort = String.Format("{0,-6} {1} {2}  {3,4}  {4,4} {5}",
                report.ReportType, report.Timestamp, report.Epc.ToHexString(), report.LocationXCm, 
                report.LocationYCm, report.ConfidenceFactors.ReadCount);

            // Update the listbox is it hasn't been disabled by the user
            if (checkDisableListbox.IsChecked == false)
            {
                listboxStatus.Items.Insert(0, sShort);
            }

            Debug.WriteLine(sLong);
            WriteLineLog(sLong);
        }

        private string IntListToCsv(List<uint> ints)
        {
            string s = "";
            string result = "";

            foreach (uint i in ints)
            {
                s += i + ",";
            }

            if (s.Length > 0)
            {
                result = s.Substring(0, s.Length - 1);
            }

            return result;
        }

        private void OnLocationReported(ImpinjReader reader, LocationReport report)
        {
            // Do this on the UI thread
            Action action = delegate()
            {
                ProcessLocationReport(report);
            };

            Dispatcher.Invoke(action);
        }

        private void OnDiagnosticsReported(ImpinjReader reader, DiagnosticReport report)
        {
            // Do this on the UI thread
            Action action = delegate()
            {
                WriteLineLog("Diagnostic," + IntListToCsv(report.Metrics));
            };

            Dispatcher.Invoke(action);
        }

        private void OnMainWindowClosing(object sender, EventArgs e)
        {
            if (reader.IsConnected)
            {
                // Unsubscribe from the event
                reader.LocationReported -= OnLocationReported;
                reader.DiagnosticsReported -= OnDiagnosticsReported;
                reader.Stop();
                reader.Disconnect();
                CloseLogFile();
            }
        }

        private void UnhandledExceptionHandler(object sender, UnhandledExceptionEventArgs args)
        {
            Exception e = (Exception)args.ExceptionObject;
            MessageBox.Show(e.Message + "\n\n" + e.StackTrace, "An exception occurred");
        }
    }
}
