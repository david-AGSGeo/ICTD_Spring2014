using System.Windows.Controls;
using Impinj.OctaneSdk;
using System;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.ComponentModel;


namespace GridTest
{
    /// <summary>
    /// Interaction logic for PageSettings.xaml
    /// </summary>
    /// 

    public partial class PageSettings : Page, INotifyPropertyChanged
    {
        public event PropertyChangedEventHandler PropertyChanged;

        private void NotifyPropertyChanged(String info)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(info));
            }
        }
        private ImageSource _txImageSource; 
        private ImageSource _rxImageSource;

        public ImageSource txImageSource
        {
            get
            {
                return _txImageSource;
            }
            set
            {
                _txImageSource = value;
                NotifyPropertyChanged("txImageSource");
            }
        }
        public ImageSource rxImageSource
        {
            get
            {
                return _rxImageSource;
            }
            set
            {
                _rxImageSource = value;
                NotifyPropertyChanged("rxImageSource");
            }
        }

        public PageSettings()
        {
            InitializeComponent();
        }

        public void LoadSettingsDefaults(FeatureSet features, Settings set)
        {
            // Reader mode
            comboReaderMode.ItemsSource = Enum.GetValues(typeof(ReaderMode));
            comboReaderMode.SelectedItem = set.ReaderMode;

            // Search mode
            comboSearchMode.ItemsSource = Enum.GetValues(typeof(SearchMode));
            comboSearchMode.SelectedItem = set.SearchMode;

            // Session
            comboSession.Items.Clear();
            comboSession.Items.Add("0");
            comboSession.Items.Add("1");
            comboSession.Items.Add("2");
            comboSession.Items.Add("3");
            comboSession.SelectedIndex = set.Session;

            // List of antennas
            listboxAntennas.Items.Clear();
            for (int i = 1; i <= features.AntennaCount; i++)
            {
                listboxAntennas.Items.Add(i);
            }
            listboxAntennas.UnselectAll();
            
            // Tx
            comboTx.Items.Clear();
            foreach (TxPowerTableEntry tx in features.TxPowers)
            {
                comboTx.Items.Add(tx.Dbm);
            }

            /* max power */
            comboTx.SelectedItem = null;

            // Rx

            comboRx.Items.Clear();
            foreach (RxSensitivityTableEntry rx in features.RxSensitivities)
            {
                comboRx.Items.Add(rx.Dbm);
            }

            /* max Power */
            comboRx.SelectedItem = null;
        }
    }
}
