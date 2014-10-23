using System;
using System.Collections;
using System.Collections.ObjectModel;
using System.Collections.Specialized;
using System.Timers;
using System.Reflection;
using System.IO;
using System.Windows.Media;
using Impinj.OctaneSdk;



namespace GridTest
{
    public class RfidEngine
    {
        private ImpinjReader reader = new ImpinjReader();

        public event DataUpdatedHandler OnDataUpdated;
        public delegate void DataUpdatedHandler();
        
        private OrderedDictionary tagLookupTable = new OrderedDictionary();

        private readonly object dataLock = new object();

        private Timer timerDataUpdate = new Timer();

        private string appPath;

        private StreamWriter logFile;

        public RfidEngine()
        {
            timerDataUpdate.Interval = 100;
            timerDataUpdate.AutoReset = true;
            timerDataUpdate.Elapsed += timerDataUpdate_Elapsed;

             appPath = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location) + "\\";
        }

        void timerDataUpdate_Elapsed(object sender, ElapsedEventArgs e)
        {
            if (OnDataUpdated != null)
            {
                OnDataUpdated();
            }
        }

        public ObservableCollection<GridEntry> GetData()
        {
            ObservableCollection<GridEntry> data = new ObservableCollection<GridEntry>();

            // Return a copy of the data as a List
            lock (dataLock)
            {
                foreach (DictionaryEntry e in tagLookupTable)
                {
                    data.Add(((GridEntry)e.Value).Copy());
                }
            }
            return data;
        }



        private void OpenNewLogFile(string logDir, string readerAddress)
        {
            // Create the data directory if necessary.
            if (!Directory.Exists(logDir))
            {
                Directory.CreateDirectory(logDir);
            }

            string filename = "GridTest" + "-";
            filename += readerAddress + "-";
            filename += DateTime.Now.Month.ToString("00");
            filename += DateTime.Now.Day.ToString("00");
            filename += DateTime.Now.Year.ToString("0000");
            filename += DateTime.Now.Hour.ToString("00");
            filename += DateTime.Now.Minute.ToString("00");
            filename += DateTime.Now.Second.ToString("00");
            filename += ".txt";

            logFile = new StreamWriter(logDir + filename);

            /* if logging is enabled, log to a file.  If we fail, just ignore */
            string sLong = String.Format("{0,24},{1,33},{2,20},{3,8},{4,8}",
            "Date/Time",
            "EPC",
            "Timestamp",
            "Antenna",
            "RSSI");
            WriteLineLog(sLong);
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

        public string GetTagModel(string tid)
        {
            tid = tid.ToUpper();

            if (tid.Length == 0)
            {
                return "";
            }
            else if (tid.Contains("E28011052000"))
            {
                return "Impinj Monza 4QT";
            }
            else if (tid.Contains("E28011042000"))
            {
                return "Impinj Monza 4U";
            }
            else if (tid.Contains("E280110C2000"))
            {
                return "Impinj Monza 4E";
            }
            else if (tid.Contains("E28011002000"))
            {
                return "Impinj Monza 4D";
            }
            else if (tid.Contains("E28011302000"))
            {
                return "Impinj Monza 5";
            }
            else if (tid.Contains("E28011402000") || tid.Contains("E28011412000"))
            {
                return "Impinj Monza X-2K Dura";
            }
            else
            {
                return "";
            }
        }

        public void Connect(string address)
        {
            reader.MaxConnectionAttempts = 2;
            reader.ConnectTimeout = 2000;
            reader.TagsReported += OnTagReportAvailableInternal;
            reader.Connect(address);
            Settings settings = reader.QueryDefaultSettings();
            settings.Report.IncludeAntennaPortNumber = true;
            settings.Report.IncludeFastId = true;
            settings.Report.IncludeFirstSeenTime = true;
            settings.Report.IncludePeakRssi = true;
            reader.ApplySettings(settings);

            OpenNewLogFile(appPath + "\\log\\", address);
        }

        public void Disconnect()
        {
            if (reader.IsConnected)
            {
                reader.TagsReported -= OnTagReportAvailableInternal;           
                reader.Disconnect();
                CloseLogFile();
            }
        }

        public void ClearData()
        {
            lock (dataLock)
            {
                tagLookupTable.Clear();
            }
        }

        public void Start()
        {
            reader.Start();
            timerDataUpdate.Start();
        }

        public void Stop()
        {
            if (reader.IsConnected)
            {
                reader.Stop();
                timerDataUpdate.Stop();
            }
        }

        public FeatureSet GetFeatureSet()
        {
            return reader.QueryFeatureSet();
        }

        public Settings GetSettings()
        {
            return reader.QuerySettings();
        }

        public void SetSettings(Settings set)
        {
            reader.ApplySettings(set);
        }

        private void ProcessTagData(ImpinjReader sender, TagReport report)
        {
            foreach (Tag tag in report)
            {
                /* if logging is enabled, log to a file.  If we fail, just ignore */
                string sLong = String.Format("{0,24},{1,33},{2,20},{3,8},{4,8}",
                System.DateTime.Now,
                tag.Epc.ToHexString(),
                tag.FirstSeenTime,
                tag.AntennaPortNumber,
                tag.PeakRssiInDbm);
                WriteLineLog(sLong);

                // Have we seen this tag before?
                string key = tag.Epc.ToHexString() + tag.Tid.ToHexString();
                GridEntry entry = (GridEntry) tagLookupTable[key];
                if (entry != null)
                {
                    // We've seen this tag before.
                    // Refresh its timer, update the timestamp, count and RSSI
                    entry.RefreshTimer();
                    entry.Antenna = tag.AntennaPortNumber;
                    entry.RowColor = Colors.Transparent;
                    entry.Timestamp = tag.FirstSeenTime.Utc;
                    entry.PeakRssi = string.Format("{0:N1}", tag.PeakRssiInDbm);
                    entry.TagSeenCount++;
                }
                else
                {
                    entry = new GridEntry(tag.AntennaPortNumber);
                    entry.Epc = tag.Epc.ToHexString();
                    entry.Tid = tag.Tid.ToHexString();
                    entry.Antenna = tag.AntennaPortNumber;
                    entry.Timestamp = tag.FirstSeenTime.Utc;
                    entry.PeakRssi = string.Format("{0:N1}", tag.PeakRssiInDbm);
                    entry.Description = GetTagModel(entry.Tid);
                    entry.RowColor = Colors.Transparent;
                    entry.TagSeenCount = 1;
                    entry.OnTagDisappeared += OnTagDisappeared;
                    tagLookupTable.Add(key, entry);

                    // Start its timer
                    entry.RefreshTimer();
                }
            }
        }

        void OnTagDisappeared(GridEntry entry)
        {
            lock (dataLock)
            {
                entry.RowColor = Colors.Red;
            }
        }

        private void OnTagReportAvailableInternal(ImpinjReader sender, TagReport report)
        {
            lock (dataLock)
            {
                ProcessTagData(sender, report);
            }
        }
    }
}
