using System;
using System.ComponentModel;
using System.Timers;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace GridTest
{
    public class GridEntry : INotifyPropertyChanged
    {

        static private FormatConvertedBitmap[] ArrayImages;

        // a static constructor to cache these pictures
        static GridEntry()
        {
            int i;
            ArrayImages = new FormatConvertedBitmap[52];
            for (i = 0; i < 52; i++)
            {
                BitmapImage b = new BitmapImage();
                b.BeginInit();
                String s = "pack://application:,,,/images/Bitmap";
                s += (i + 1);
                s += ".bmp";
                b.UriSource = new Uri(s);
                b.EndInit();
            
                FormatConvertedBitmap fcb = new FormatConvertedBitmap(b, PixelFormats.Bgra32, null, 0);
                
                ArrayImages[i] = fcb;
                ArrayImages[i].Freeze();
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;
        private Timer timerTagDisappeared = new Timer();
        public delegate void TagDisappearedHandler(GridEntry entry);
        public event TagDisappearedHandler OnTagDisappeared;

        public ushort Antenna
        {
            get
            {
                return _Antenna;
            }
            set
            {
                _Antenna = value;
                UpdateImage();
                NotifyPropertyChanged("Antenna");

                // update the image 

            }
        }

        public string Epc { get; set; }
        public string Tid { get; set; }
        public string Description { get; set; }
        
        private Color _RowColor;
        private ulong _Timestamp;
        private ushort _Antenna;
        private ulong _TagSeenCount;
        private string _PeakRssi;
        private ImageSource _ImageSource;
        private WriteableBitmap antennaView;

        public ImageSource ImageSource
        {
            get
            {
                return _ImageSource;
            }
            set
            {
                _ImageSource = value;
                NotifyPropertyChanged("ImageSource");
            }
        }

        public string PeakRssi 
        {
            get
            {
                return _PeakRssi;
            }
            set
            {
                _PeakRssi = value;
                NotifyPropertyChanged("PeakRssi");
            }
        }

        public ulong Timestamp 
        {
            get
            {
                return _Timestamp;
            }
            set
            {
                _Timestamp = value;
                NotifyPropertyChanged("Timestamp");
            }
        }

        public ulong TagSeenCount
        {
            get
            {
                return _TagSeenCount;
            }
            set
            {
                _TagSeenCount = value;
                NotifyPropertyChanged("TagSeenCount");
            }
        }
        
        public Color RowColor 
        {
            get
            {
                return _RowColor;
            }
            set
            {
                _RowColor = value;
                // If we set the row color, the brush changes.
                NotifyPropertyChanged("RowBrush");
            }
        }
        
        public SolidColorBrush RowBrush
        {
            get
            {
                return new SolidColorBrush(RowColor);
            }
        }

        public GridEntry(int antenna)
        {
            timerTagDisappeared.Interval = 5000;
            timerTagDisappeared.AutoReset = false;
            timerTagDisappeared.Elapsed += timerTagDisappeared_Elapsed;
            antennaView = new WriteableBitmap(ArrayImages[antenna - 1]);
            antennaView.Freeze();
            ImageSource = antennaView;
        }

        private void UpdateImage() {
            int numElems = antennaView.PixelHeight * antennaView.PixelWidth;
            WriteableBitmap upbm = new WriteableBitmap(ArrayImages[_Antenna - 1]);
            WriteableBitmap newbm = new WriteableBitmap(antennaView);

            int scale = 10;

            unsafe
            {
                int i;

                Int32* pnewbm = (Int32*)newbm.BackBuffer;
                Int32* pupbm = (Int32*)upbm.BackBuffer;

                for (i = 0; i < numElems; i++)
                {
                    if (pupbm[i] == pnewbm[i])
                    {
                        /* do nothing */
                    }
                    else
                    {
                        int r1 = (pnewbm[i] >> 16) & 0xFF;
                        int g1 = (pnewbm[i] >> 8) & 0xFF;
                        int b1 = (pnewbm[i] >> 0) & 0xFF;
                        int r2 = (pupbm[i] >> 16) & 0xFF;
                        int g2 = (pupbm[i] >> 8) & 0xFF;
                        int b2 = (pupbm[i] >> 0) & 0xFF;

                        /* fade the old image */
                        /* color fade the old antenna */
                        r1 += scale;
                        b1 += scale;
                        g1 += scale;
                        if (r1 > 255) { r1 = 255; }
                        if (b1 > 255) { b1 = 255; }
                        if (g1 > 255) { g1 = 255; }
                        pnewbm[i] = (0xff << 24) + (r1 << 16) + (g1 << 8) + b1;

                        /* mark the new antenna as black */
                        if (r2 == 0 && b2 == 0 && g2 == 0)
                        {
                            pnewbm[i] = (0xff << 24) + (0 << 16) + (0 << 8) + 0;
                        }
                    }
                }
            }
            newbm.Freeze();
            antennaView = newbm;
            ImageSource = antennaView;
        }

        private void timerTagDisappeared_Elapsed(object sender, ElapsedEventArgs e)
        {
            if (OnTagDisappeared != null)
            {
                OnTagDisappeared(this);
            }
        }

        public void RefreshTimer()
        {
            timerTagDisappeared.Stop();
            timerTagDisappeared.Start();
        }

        public GridEntry Copy()
        {
            return (GridEntry) this.MemberwiseClone();
        }

        private void NotifyPropertyChanged(String info)
        {
            if (PropertyChanged != null)
            {
                PropertyChanged(this, new PropertyChangedEventArgs(info));
            }
        }
    }
}
