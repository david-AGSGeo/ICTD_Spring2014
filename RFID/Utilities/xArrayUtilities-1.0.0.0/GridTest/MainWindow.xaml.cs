using System;
using System.ComponentModel;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.IO;
using System.Reflection;
using System.Windows;
using System.Windows.Input;
using System.Windows.Threading;
using Impinj.OctaneSdk;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace GridTest
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window   
    {
        private PageMain pageMain = new PageMain();
        private PageConnect pageConnect = new PageConnect();
        private PageSettings pageSettings = new PageSettings();
        private RfidEngine engine = new RfidEngine();
        private bool readerRunning = false;
        private string appPath;
        private string addressFile;
        private const string EXAMPLE_READER_ADDRESS = "SpeedwayR-XX-XX-XX";
        static private FormatConvertedBitmap[] ArrayImages;
        static private FormatConvertedBitmap ArrayBlank;
        private Settings _settings;
        private FeatureSet _features;

        static MainWindow()
        {
            int i;
            ArrayImages = new FormatConvertedBitmap[52];
            for (i = 0; i < 52; i++)
            {
                String s = "pack://application:,,,/images/Bitmap";
                s += (i + 1);
                s += ".bmp";
                Uri uri = new Uri(s);
                BitmapImage b = new BitmapImage(uri);
                FormatConvertedBitmap fcb = new FormatConvertedBitmap(b, PixelFormats.Bgra32, null, 0);
                ArrayImages[i] = fcb;
                ArrayImages[i].Freeze();
            }

            String s2 = "pack://application:,,,/images/BitmapNone.bmp";
            Uri uri2 = new Uri(s2);
            BitmapImage b2 = new BitmapImage(uri2);
            FormatConvertedBitmap fcb2 = new FormatConvertedBitmap(b2, PixelFormats.Bgra32, null, 0);
            ArrayBlank = fcb2;
        }

        private WriteableBitmap BuildReaderTxImage() {
            /* go through each setting and see if the antenna is enabled */
            WriteableBitmap bout = new WriteableBitmap(ArrayBlank);;

            for (int i = 0; i < _features.AntennaCount; i++)
            {
                if (_settings.Antennas[i].IsEnabled)
                {
                    double power = _settings.Antennas[i].TxPowerInDbm;

                    WriteableBitmap bm = new WriteableBitmap(ArrayImages[i]);
                    int numElems = bout.PixelHeight * bout.PixelWidth;

                    unsafe
                    {
                        int j;
                        Int32* pbout = (Int32*)bout.BackBuffer;
                        Int32* pb = (Int32*)bm.BackBuffer;

                        for (j = 0; j < numElems; j++)
                        {
                            if (pbout[j] == pb[j])
                            {
                                /* do nothing */
                            }
                            else
                            {
                                int r = (pb[j] >> 16) & 0xFF;
                                int g = (pb[j] >> 8) & 0xFF;
                                int b = (pb[j] >> 0) & 0xFF;

                                /* black indicates this antenna is active */
                                if((r ==  0) && (b == 0) && (g == 0)) {
                                    int scale = (int) ((power - 10) * 12.5);
                                    int red = scale;
                                    int blue = 255 - scale;
                                    if (red < 0) { red = 0; }
                                    if (blue > 255 ) { blue = 255;}                                   
                                    if (red  > 255 ) { red = 255; }
                                    pbout[j] = (255 << 24) + (red << 16) + (0 << 8) + blue;
                                }
                            }
                        }
                    }
                }
            }
            bout.Freeze();
            return bout;
        }

        private WriteableBitmap BuildReaderRxImage()
        {
            /* go through each setting and see if the antenna is enabled */
            WriteableBitmap bout = new WriteableBitmap(ArrayBlank); ;

            for (int i = 0; i < _features.AntennaCount; i++)
            {
                if (_settings.Antennas[i].IsEnabled)
                {
                    double power = -1 * _settings.Antennas[i].RxSensitivityInDbm;

                    WriteableBitmap bm = new WriteableBitmap(ArrayImages[i]);
                    int numElems = bout.PixelHeight * bout.PixelWidth;

                    unsafe
                    {
                        int j;
                        Int32* pbout = (Int32*)bout.BackBuffer;
                        Int32* pb = (Int32*)bm.BackBuffer;

                        for (j = 0; j < numElems; j++)
                        {
                            if (pbout[j] == pb[j])
                            {
                                /* do nothing */
                            }
                            else
                            {
                                int r = (pb[j] >> 16) & 0xFF;
                                int g = (pb[j] >> 8) & 0xFF;
                                int b = (pb[j] >> 0) & 0xFF;

                                /* black indicates this antenna is active */
                                if ((r == 0) && (b == 0) && (g == 0))
                                {
                                    int scale = (int)((power - 30) * 5);
                                    int green = scale;
                                    int blue = 255 - scale;
                                    if (green < 0) { green = 0; }
                                    if (blue > 255) { blue = 255; }
                                    if (green > 255) { green = 255; }
                                    pbout[j] = (255 << 24) + (0 << 16) + (green << 8) + blue;
                                }
                            }
                        }
                    }
                }
            }
            bout.Freeze();
            return bout;
        }
        public MainWindow()
        {
            InitializeComponent();

            // Register event handlers
            engine.OnDataUpdated += OnDataUpdated;
            pageConnect.buttonConnect.Click += buttonConnect_Click;
            pageMain.buttonBack.Click += buttonBack_Click;
            pageMain.buttonStartStop.Click += buttonStartStop_Click;
            pageMain.buttonSettings.Click += buttonSettings_Click;
            pageSettings.buttonCancel.Click += buttonCancel_Click;
            pageSettings.buttonSave.Click += buttonSave_Click;

            pageSettings.AntennaEnabled.Checked += antennaEnabled_Checked;
            pageSettings.AntennaEnabled.Unchecked += antennaEnabled_Unchecked;

            pageSettings.comboTx.SelectionChanged += comboTx_SelectionChanged;
            pageSettings.comboRx.SelectionChanged += comboRx_SelectionChanged;

            pageSettings.listboxAntennas.SelectionChanged += listBoxAntennas_SelectionChanged;

            // Disabled for now
            //pageMain.buttonClear.Click += buttonClear_Click;
            pageConnect.comboReaderAddress.KeyDown += comboReaderAddress_KeyDown;

            ClearData();

            appPath = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location) + "\\";

            addressFile = appPath + "addresses.config";

            ReadAddressFile();

            this.Content = pageConnect;
        }

        /*
        void buttonClear_Click(object sender, RoutedEventArgs e)
        {
            ClearData();
        }
        */

        void comboReaderAddress_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Return)
            {
                InitiateConnect();
            }
        }

        public void ReadAddressFile()
        {
            if (File.Exists(addressFile))
            {
                pageConnect.comboReaderAddress.Items.Clear();
                string[] lines = File.ReadAllLines(addressFile);

                foreach (string line in lines)
                {
                    string l = line.Trim();
                    if (l.Length > 0)
                    {
                        pageConnect.comboReaderAddress.Items.Add(line);
                    }
                }

                if (pageConnect.comboReaderAddress.Items.Count > 0)
                {
                    pageConnect.comboReaderAddress.SelectedIndex = 0;
                }
            }
            else
            {
                pageConnect.comboReaderAddress.Items.Add("SpeedwayR-XX-XX-XX");
                pageConnect.comboReaderAddress.SelectedIndex = 0;
            }
        }

        private void buttonSettings_Click(object sender, RoutedEventArgs e)
        {
            /* fetch the current reader settings so we don't save state s*/
            _settings = engine.GetSettings();
            _features = engine.GetFeatureSet();
            pageSettings.LoadSettingsDefaults(_features, _settings);

            /* the settings structure is a bit weird because there are booleans for whether 
             * antenna power is enabled or now.  By default, lets just turn them on  */

            for (int i = 0; i <  _features.AntennaCount; i++)
            {
                if (_settings.Antennas[i].MaxTxPower)
                {
                    _settings.Antennas[i].MaxTxPower = false;
                    _settings.Antennas[i].TxPowerInDbm = (_features.TxPowers[_features.TxPowers.Count - 1]).Dbm;
                }
                if (_settings.Antennas[i].MaxRxSensitivity)
                {
                    _settings.Antennas[i].MaxRxSensitivity = false;
                    _settings.Antennas[i].RxSensitivityInDbm = (_features.RxSensitivities[0]).Dbm;
                }
            }

            /* don't start with this checkbox or the antennas will get changed */
            pageSettings.AntennaEnabled.IsChecked = null;
            this.Content = pageSettings;
            pageSettings.DataContext = pageSettings;
            this.DataContext = pageSettings;
            pageSettings.txImageSource = BuildReaderTxImage(); 
            pageSettings.rxImageSource = BuildReaderRxImage();
        }

        private void buttonStartStop_Click(object sender, RoutedEventArgs e)
        {
            if (readerRunning)
            {
                // Stop reading
                engine.Stop();
                pageMain.buttonStartStop.Content = "Start";
                readerRunning = false;
                pageMain.buttonSettings.IsEnabled = true;
                pageMain.buttonBack.IsEnabled = true;
            }
            else
            {
                // Start reading
                ClearData();
                engine.Start();
                pageMain.buttonStartStop.Content = "Stop";
                readerRunning = true;
                pageMain.buttonSettings.IsEnabled = false;
                pageMain.buttonBack.IsEnabled = false;
            }
        }

        private void listBoxAntennas_SelectionChanged(object sender, RoutedEventArgs e)
        {
            /* go through the listbox and figure out what to put for Tx, Rx and Enabled */
            var selectedItems = pageSettings.listboxAntennas.SelectedItems;

            if (selectedItems.Count > 0)
            {
                bool txdiff = false;
                bool rxdiff = false;
                bool enableddiff = false;
                double txpower = 0;
                double rxsense = 0;
                bool enabled = false;
                bool first = true;

                foreach (int antenna in selectedItems)
                {
                    if (first)
                    {
                        txpower = _settings.Antennas[antenna - 1].TxPowerInDbm;
                        rxsense = _settings.Antennas[antenna - 1].RxSensitivityInDbm;
                        enabled = _settings.Antennas[antenna - 1].IsEnabled;
                        first = false;
                    }
                    else
                    {
                        if (txpower != _settings.Antennas[antenna - 1].TxPowerInDbm)
                        {
                            txdiff = true;
                        }
                        if (rxsense != _settings.Antennas[antenna - 1].RxSensitivityInDbm)
                        {
                            rxdiff = true;
                        }
                        if (enabled != _settings.Antennas[antenna - 1].IsEnabled)
                        {
                            enableddiff = true;
                        }
                    }
                }
                if (enableddiff)
                {
                    /* mark the checkbox as unknown */
                    pageSettings.AntennaEnabled.IsChecked = null;
                }
                else
                {
                    pageSettings.AntennaEnabled.IsChecked = enabled;
                }
                if (txdiff)
                {
                    pageSettings.comboTx.SelectedValue = null;
                }
                else
                {
                    pageSettings.comboTx.SelectedValue = txpower;
                }
                if (rxdiff)
                {
                    pageSettings.comboRx.SelectedValue = null;
                } else 
                {
                    pageSettings.comboRx.SelectedValue = rxsense;
                }
            }
        }
        
        private void comboTx_SelectionChanged(object sender, RoutedEventArgs e)
        {
            /* have to find the set of items selected in the list and ensure we enable their antennas and set them to the 
             * power and rx sensivitity set in the dialog */

            var selectedItems = pageSettings.listboxAntennas.SelectedItems;
            foreach (int antenna in selectedItems)
            {
                if (pageSettings.comboTx.SelectedItem != null)
                {
                    _settings.Antennas[antenna - 1].TxPowerInDbm = (double)pageSettings.comboTx.SelectedItem;
                }
            }
            pageSettings.txImageSource = BuildReaderTxImage();
        }

        private void comboRx_SelectionChanged(object sender, RoutedEventArgs e)
        {
            /* have to find the set of items selected in the list and ensure we enable their antennas and set them to the 
             * power and rx sensivitity set in the dialog */

            var selectedItems = pageSettings.listboxAntennas.SelectedItems;
            foreach (int antenna in selectedItems)
            {
                if (pageSettings.comboRx.SelectedItem != null)
                {
                    _settings.Antennas[antenna - 1].RxSensitivityInDbm = (double)pageSettings.comboRx.SelectedItem;
                }
            }
            pageSettings.rxImageSource = BuildReaderRxImage();
        }

        private void antennaEnabled_Checked(object sender, RoutedEventArgs e)
        {
            /* have to find the set of items selected in the list and ensure we enable their antennas and set them to the 
             * power and rx sensivitity set in the dialog */

            var selectedItems = pageSettings.listboxAntennas.SelectedItems;
            foreach (int antenna in selectedItems)
            {
                if (pageSettings.comboTx.SelectedItem != null)
                {
                    _settings.Antennas[antenna - 1].TxPowerInDbm = (double)pageSettings.comboTx.SelectedItem;
                }
                if (pageSettings.comboRx.SelectedItem != null)
                {
                    _settings.Antennas[antenna - 1].RxSensitivityInDbm = (double)pageSettings.comboRx.SelectedItem;
                }
                _settings.Antennas[antenna - 1].IsEnabled = true;
            }

            pageSettings.txImageSource = BuildReaderTxImage();
            pageSettings.rxImageSource = BuildReaderRxImage();
        }

        private void antennaEnabled_Unchecked(object sender, RoutedEventArgs e)
        {
            /* uncheck all in the list */
            var selectedItems = pageSettings.listboxAntennas.SelectedItems;
            foreach (int antenna in selectedItems)
            {
                _settings.Antennas[antenna - 1].IsEnabled = false;
            }
            pageSettings.txImageSource = BuildReaderTxImage();
            pageSettings.rxImageSource = BuildReaderRxImage();
        }
        

        private void buttonBack_Click(object sender, RoutedEventArgs e)
        {
            engine.Stop();
            engine.Disconnect();
            ReadAddressFile();
            this.Content = pageConnect;
        }

        private void WriteAddressFile()
        {
            Dictionary<string, string> addresses = new Dictionary<string, string>();

            StreamWriter file = new StreamWriter(addressFile);

            // Write the last address successfully used.
            string lastAddress = pageConnect.comboReaderAddress.Text.Trim();
            file.WriteLine(lastAddress);
            addresses.Add(lastAddress.ToLower(), lastAddress);

            // Write any previous addresses that are in the combo box 
            int count = 0;
            foreach (string s in pageConnect.comboReaderAddress.Items)
            {
                string s_lower = s.ToLower();
                if (!addresses.ContainsKey(s_lower) && (s_lower != EXAMPLE_READER_ADDRESS.ToLower()))
                {
                    file.WriteLine(s.Trim());
                    addresses.Add(s.ToLower(), lastAddress);
                    count++;
                    // Limit the list to five
                    if (count == 4) break;
                }
            }
         
            file.Close();
        }

        private void InitiateConnect()
        {
            try
            {
                string address = pageConnect.comboReaderAddress.Text;
                engine.Connect(address);

                // If we make it here, we've successfully connected
                WriteAddressFile();

                ClearData();
                this.Content = pageMain;
            }
            catch (OctaneSdkException ex)
            {
                // There was an error connecting
                MessageBox.Show(ex.Message, "Connection Error", MessageBoxButton.OK);
            }
        }

        private void buttonConnect_Click(object sender, RoutedEventArgs e)
        {
            InitiateConnect();
        }

        private void buttonCancel_Click(object sender, RoutedEventArgs e)
        {
            this.Content = pageMain;
        }


        private void buttonSave_Click(object sender, RoutedEventArgs e)
        {
            _settings.ReaderMode = (Impinj.OctaneSdk.ReaderMode) pageSettings.comboReaderMode.SelectedItem;
            _settings.SearchMode = (Impinj.OctaneSdk.SearchMode) pageSettings.comboSearchMode.SelectedItem;
            _settings.Session = (ushort) pageSettings.comboSession.SelectedIndex;

            try
            {
                engine.SetSettings(_settings);
                this.Content = pageMain;
            }
            catch (OctaneSdkException ex)
            {
                // There was an error connecting
                MessageBox.Show(ex.Message, "Settings Error", MessageBoxButton.OK);
            }
        }

        private void ClearData()
        {
            engine.ClearData();
            pageMain.dg.DataContext = new ObservableCollection<GridEntry>();
        }

        private GridEntry GetRowFromGrid(GridEntry target)
        {
            ObservableCollection<GridEntry> gridData = (ObservableCollection<GridEntry>) pageMain.dg.DataContext;
            foreach (GridEntry e in gridData)
            {
                string key1 = e.Epc + e.Tid;
                string key2 = target.Epc + target.Tid;
                if (key1 == key2)
                {
                    return e;
                }
            }
            return null;
        }

        private void HandleDataUpdate()
        {
            Stopwatch sw = Stopwatch.StartNew();
            ObservableCollection<GridEntry> gridData = (ObservableCollection<GridEntry>)pageMain.dg.DataContext;
            ObservableCollection<GridEntry> engineData = engine.GetData();

            // Loop through engine data, 
            // updating or adding row as necessary
            foreach (GridEntry e in engineData)
            {
                GridEntry row = GetRowFromGrid(e);
                if (row == null)
                {
                    // Not in the grid. Add it.
                    gridData.Add(e);
                }
                else
                {
                    // Update the dynamic fields
                    row.PeakRssi = e.PeakRssi;
                    row.TagSeenCount = e.TagSeenCount;
                    row.Timestamp = e.Timestamp;
                    row.RowColor = e.RowColor;
                    row.Antenna = e.Antenna;
                    row.ImageSource = e.ImageSource;
                } 
            }

            //CollectionViewSource.GetDefaultView(dg.ItemsSource).Refresh();
            sw.Stop();
            Console.WriteLine("UI update time: {0} ms", sw.ElapsedMilliseconds);
        }

        private void OnDataUpdated()
        {
            // Do this on the main UI thread
            Action action = delegate()
            {
                HandleDataUpdate();
            };

            this.Dispatcher.Invoke(DispatcherPriority.Normal, action);
        }
        
        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            engine.Stop();
            engine.Disconnect();
        }
    }
}
