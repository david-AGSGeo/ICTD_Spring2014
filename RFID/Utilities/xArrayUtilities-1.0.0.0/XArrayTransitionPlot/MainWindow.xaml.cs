using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Reflection;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Documents;
using System.Windows.Media;
using System.Windows.Shapes;
using Impinj.OctaneSdk;
using System.Windows.Input;
using System.Linq;
using System.Configuration;

namespace XArrayTransitionPlot
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private ImpinjReader reader = new ImpinjReader();
        private const double STROKE_THICKNESS = 1;
        private List<Color> systemColors = new List<Color>();
        private Dictionary<string, Color> colorMap = new Dictionary<string, Color>();
        private Random rand = new Random();
        private double lenSquare;
        private Point originZone1;
        private Point originZone2;
        private Dictionary<string, TagSquareInfo> squares = new Dictionary<string, TagSquareInfo>();
        private StreamWriter logFile;
        private int colorPtr = 0;

        public MainWindow()
        {
            InitializeComponent();

            ushort maxTagsPerZone = Properties.Settings.Default.MaxTagsPerZone;

            // The max number of squares per zone should be even
            if (maxTagsPerZone % 2 != 0) maxTagsPerZone++;

            // Initialize the color array
            PropertyInfo[] props = typeof(Colors).GetProperties();
            foreach (PropertyInfo propInfo in props)
            {
                Color color = (Color)propInfo.GetValue(null, null);
                // Don't plot white
                if (color != Colors.White)
                {
                    systemColors.Add(color);
                }
            }

            // Randomize the color list
            systemColors = systemColors.OrderBy(x => rand.Next()).ToList();

            // Register to receive transition events from xArray
            reader.TransitionReported += OnTransitionReported;
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

        private List<ushort> StringToIntList(string s)
        {
            // Convert a comma-delimited string of sectors into an ushort List
            List<ushort> list = new List<ushort>();

            string[] parts = s.Split(',');

            foreach (string part in parts)
            {
                list.Add(ushort.Parse(part));
            }
            return list;
        }

        private void StartXArray()
        {
            reader.Connect(Properties.Settings.Default.ReaderAddress);
            Settings settings = reader.QueryDefaultSettings();

            // Put the xArray into transition mode
            settings.XArray.Mode = XArrayMode.Transition;

            // Enable all of the report types
            settings.XArray.Transition.TransitionReportEnabled = true;
            settings.XArray.Transition.StrayReportEnabled = true;
            settings.XArray.Transition.EntryReportEnabled = true;
            settings.XArray.Transition.DiagnosticReportEnabled = true;

            // Set xArray transition parameters
            settings.XArray.Transition.InitialStraySearchTimeSec = Properties.Settings.Default.InitialStraySearchTimeSec;
            settings.XArray.Transition.StraySession = Properties.Settings.Default.StraySession;
            settings.XArray.Transition.StrayTagAgeSec = Properties.Settings.Default.StrayTagAgeSec;
            settings.XArray.Transition.TOISession = Properties.Settings.Default.TOISession;
            settings.XArray.Transition.StrayUpdateIntervalSec = Properties.Settings.Default.StrayUpdateIntervalSec;
            settings.XArray.Transition.TOITagAgeSec = Properties.Settings.Default.TOITagAgeSec;
            settings.XArray.Transition.TransitionZoneRange = Properties.Settings.Default.TransitionZoneRange;

            // Create a list of transition zones. 
            // xArray currently supports a maximum of two zones.
            settings.XArray.Transition.TransitionZones = new List<TransitionZone>();

            // Define the first zone
            TransitionZone zone1 = new TransitionZone();
            // An numerical identifier for the zone
            zone1.ZoneId = 1;
            // A list of sectors to include in this zone
            zone1.SectorIds = StringToIntList(Properties.Settings.Default.Zone1Sectors);
            // Add this zone to the list of zones
            settings.XArray.Transition.TransitionZones.Add(zone1);

            // Define the second zone
            TransitionZone zone2 = new TransitionZone();
            // An numerical identifier for the zone
            zone2.ZoneId = 2;
            // A list of sectors to include in this zone
            zone2.SectorIds = StringToIntList(Properties.Settings.Default.Zone2Sectors);
            // Add this zone to the list of zones
            settings.XArray.Transition.TransitionZones.Add(zone2);

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

        private Color AssignSquareColor(string epc, bool stray)
        {
            Color color;

            if (stray)
            {
                // Stray tags are light gray
                color = Colors.LightGray;
            }
            else if (colorMap.Count > 0)
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

        private void CreateNewSquare(string epc, ushort zone, bool stray)
        {
            TagSquareInfo squareInfo= new TagSquareInfo();
            
            // Save the EPC and zone for this square
            squareInfo.Epc = epc;
            squareInfo.Zone = zone;

            // Assign a color to this square
            Color color = AssignSquareColor(epc, stray);
            
            // Create the square
            Rectangle square = new Rectangle();
            square.Stroke = Brushes.White;
            square.StrokeThickness = STROKE_THICKNESS;
            square.Fill = new SolidColorBrush(color);
            square.Height = lenSquare;
            square.Width = lenSquare;
            Debug.WriteLine(lenSquare);
            square.HorizontalAlignment = HorizontalAlignment.Left;
            square.VerticalAlignment = VerticalAlignment.Top;
            squareInfo.RenderedSquare = square;

            // Receive mouse over events for this point
            square.MouseEnter += OnSquareMouseEnter;    
            
            // Add it to the list of squares
            squares.Add(epc, squareInfo);
        }

        private void OnSquareMouseEnter(object sender, MouseEventArgs e)
        {
            // Look up the tag associated with this point
            Rectangle selectedSquare = (Rectangle)sender;
            foreach (KeyValuePair<string, TagSquareInfo> kv in squares)
            {
                TagSquareInfo squareInfo = (TagSquareInfo)kv.Value;
                if (squareInfo.RenderedSquare == selectedSquare)
                {
                    ToolTip tip = new ToolTip();
                    tip.Content = squareInfo.Epc;
                    selectedSquare.ToolTip = tip;
                }
            }
        }

        private void ArrangeSquares(ushort zone, Point origin)
        {
            double column = 0;
            double row = 0;
            int squaresInZone = 0;

            // Count how many squares are in this zone
            foreach (KeyValuePair<string, TagSquareInfo> kv in squares)
            {
                if (kv.Value.Zone == zone)
                {
                    squaresInZone++;
                }
            }

            if (squaresInZone > 0 && squaresInZone <= Properties.Settings.Default.MaxTagsPerZone)
            {
                double squaresPerRow = Math.Ceiling(Math.Sqrt(squaresInZone));
                double numRows = Math.Ceiling(squaresInZone / squaresPerRow);
                double numColumns = Math.Ceiling(squaresInZone / numRows);
                double widthSquares = numColumns * lenSquare;
                double heightSquares = numRows * lenSquare;

                double x = ((canvasPlot.ActualWidth / 2) - widthSquares) / 2;
                double y = (canvasPlot.ActualHeight - heightSquares) / 2;
             
                foreach (KeyValuePair<string, TagSquareInfo> kv in squares)
                {
                    if (kv.Value.Zone == zone)
                    {
                        Rectangle square = kv.Value.RenderedSquare;

                        // If this square isn't on the canvas, add it
                        if (!canvasPlot.Children.Contains(square))
                        {
                            canvasPlot.Children.Add(square);
                        }

                        // Adjust it's size and position
                        square.Height = square.Width = lenSquare;
                       
                        Canvas.SetTop(square, (row * lenSquare) + origin.Y + y);
                        Canvas.SetLeft(square, (column * lenSquare) + origin.X + x);

                        column++;
                        if (column >= squaresPerRow)
                        {
                            column = 0;
                            row++;
                        }
                    }
                }
            }
        }

        private void DrawPlot()
        {
            this.InvalidateVisual();
            this.UpdateLayout();

            // Which is the smallest dimension of the canvas?
            int min = (int)Math.Min(columnCanvas1.ActualWidth + columnCanvas2.ActualWidth,
                rowCanvas1.ActualHeight + rowCanvas2.ActualHeight);

            // Set the canvas to a 2:1 ratio, so we can draw to squares in it
            canvasPlot.Width = min;
            canvasPlot.Height = min / 2;

            double areaPerZone = canvasPlot.Height * (canvasPlot.Width / 2);
            double areaPerSquare = areaPerZone / Properties.Settings.Default.MaxTagsPerZone;
            lenSquare = Math.Sqrt(areaPerSquare);

            // Clear the canvas
            canvasPlot.Children.Clear();

            // Draw two squares on the screen. One for each zone.
            Rectangle rectZone1 = new Rectangle();
            rectZone1.Stroke = Brushes.LightGray;
            rectZone1.StrokeThickness = STROKE_THICKNESS;
            rectZone1.Fill = System.Windows.Media.Brushes.White;
            rectZone1.Height = canvasPlot.ActualHeight;
            rectZone1.Width = canvasPlot.ActualWidth / 2;
            rectZone1.HorizontalAlignment = HorizontalAlignment.Left;
            rectZone1.VerticalAlignment = VerticalAlignment.Top;
            canvasPlot.Children.Add(rectZone1);
            originZone1 = new Point(0, 0);

            Rectangle rectZone2 = new Rectangle();
            rectZone2.Stroke = Brushes.LightGray;
            rectZone2.StrokeThickness = STROKE_THICKNESS;
            rectZone2.Fill = System.Windows.Media.Brushes.White;
            rectZone2.Height = canvasPlot.ActualHeight;
            rectZone2.Width = canvasPlot.ActualWidth / 2;
            rectZone2.HorizontalAlignment = HorizontalAlignment.Left;
            rectZone2.VerticalAlignment = VerticalAlignment.Top;
            canvasPlot.Children.Add(rectZone2);
            Canvas.SetTop(rectZone2, 0);
            Canvas.SetLeft(rectZone2, rectZone1.Width);
            originZone2 = new Point(rectZone1.Width, 0);

            // Add the zone labels
            Label labelZone1 = new Label();
            labelZone1.FontSize = 14;
            labelZone1.Foreground = Brushes.LightGray;
            labelZone1.Content = "Zone 1";
            canvasPlot.Children.Add(labelZone1);
            Canvas.SetTop(labelZone1, 0);
            Canvas.SetLeft(labelZone1, 0);

            Label labelZone2 = new Label();
            labelZone2.FontSize = 14;
            labelZone2.Foreground = Brushes.LightGray;
            labelZone2.Content = "Zone 2";
            canvasPlot.Children.Add(labelZone2);
            Canvas.SetTop(labelZone2, 0);
            Canvas.SetLeft(labelZone2, rectZone1.Width);
        }

        private void OnMainWindowResized(object sender, SizeChangedEventArgs e)
        {
            // Redraw the plot when the window is resized
            DrawPlot();
            // Adjust the position of the squares
            ArrangeAllSquares();
        }

        private void OnMainWindowLoaded(object sender, RoutedEventArgs e)
        {
            // Redraw the plot when the window is loaded
            DrawPlot();
            // Adjust the position of the squares
            ArrangeAllSquares();
        }

        protected override void OnRenderSizeChanged(SizeChangedInfo sizeInfo)
        {
            // Redraw the plot when the window is maximized
            base.OnRenderSizeChanged(sizeInfo);
            DrawPlot();
            // Adjust the position of the squares
            ArrangeAllSquares();
        }

        private void ProcessTransitionReport(TransitionReport report)
        {
            TagSquareInfo squareInfo;

            foreach (TagData epc in report.Epcs)
            {
                if (squares.TryGetValue(epc.ToHexString(), out squareInfo))
                {
                    // There is already a square on the screen that is 
                    // associated with this EPC
                    // Update the zone if the confidence for this report is > 50
                    if (report.Confidence > 50)
                    {
                        squareInfo.Zone = report.ToZoneId;
                    }
                }
                else
                {
                    // This is a new tag. Add it to the screen
                    bool stray = (report.ReportType == TransitionReportType.StrayTag) ? true : false;
                    if (!(stray && !Properties.Settings.Default.PlotStrays))
                    {
                        CreateNewSquare(epc.ToHexString(), report.ToZoneId, stray);
                    }
                }

                // Update the status box
                string sLog = String.Format("{0}  {1}  {2} {3}  {4}  {5}",
                    report.ReportType, report.Timestamp, epc, report.FromZoneId, report.ToZoneId, report.Confidence);

                string sConsole = String.Format("{0,-8}  {1}  {2,-29} {3}  {4}  {5}",
                    report.ReportType, report.Timestamp, epc, report.FromZoneId, report.ToZoneId, report.Confidence);

                // Write to the log file
                WriteLineLog(sLog);

                listboxStatus.Items.Insert(0, sConsole);
            }      
            
            // Adjust the position of the squares
            ArrangeAllSquares();
        }

        private void ArrangeAllSquares()
        {
            ArrangeSquares(1, originZone1);
            ArrangeSquares(2, originZone2);
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

        private void OnDiagnosticsReported(ImpinjReader reader, DiagnosticReport report)
        {
            // Do this on the UI thread
            Action action = delegate()
            {
                WriteLineLog("Diagnostic," + IntListToCsv(report.Metrics));
            };

            Dispatcher.Invoke(action);
        }

        private void OnTransitionReported(ImpinjReader reader, TransitionReport report)
        {
            // Do this on the UI thread
            Action action = delegate()
            {
                ProcessTransitionReport(report);
            };

            Dispatcher.Invoke(action);
        }

        private void OnMainWindowClosing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            if (reader.IsConnected)
            {
                // Unsubscribe from the events
                reader.TransitionReported -= OnTransitionReported;
                reader.DiagnosticsReported -= OnDiagnosticsReported;
                reader.Stop();
                reader.Disconnect();
                CloseLogFile();
            }
        }
    }
}
