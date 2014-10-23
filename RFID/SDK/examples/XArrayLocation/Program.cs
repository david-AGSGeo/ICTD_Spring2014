////////////////////////////////////////////////////////////////////////////////
//
//    xArray Location Example
//
////////////////////////////////////////////////////////////////////////////////

using System;
using Impinj.OctaneSdk;

namespace OctaneSdkExamples
{
    class Program
    {
        // Create an instance of the ImpinjReader class.
        static ImpinjReader reader = new ImpinjReader();

        static void Main(string[] args)
        {
            try
            {
                // Connect to the reader.
                // Change the ReaderHostname constant in SolutionConstants.cs 
                // to the IP address or hostname of your reader.
                reader.Connect(SolutionConstants.ReaderHostname);

                // Assign the LocationReported event handler.
                // This specifies which method to call
                // when a location report is available.
                reader.LocationReported += OnLocationReported;

                // Get the default settings
                // We'll use these as a starting point
                // and then modify the settings we're 
                // interested in.
                Settings settings = reader.QueryDefaultSettings();

                // Put the xArray into location mode
                settings.XArray.Mode = XArrayMode.Location;

                // Enable all three report types
                settings.XArray.Location.EntryReportEnabled = true;
                settings.XArray.Location.UpdateReportEnabled = true;
                settings.XArray.Location.ExitReportEnabled = true;

                // Set xArray placement parameters

                // The mounting height of the xArray, in centimeters
                settings.XArray.Placement.HeightCm = 457;
                // These settings aren't required in a single xArray environment
                // They can be set to zero (which is the default)
                settings.XArray.Placement.FacilityXLocationCm = 0;
                settings.XArray.Placement.FacilityYLocationCm = 0;
                settings.XArray.Placement.OrientationDegrees = 0;

                // Set xArray location parameters
                settings.XArray.Location.MotionWindowSeconds = 10;
                settings.ReaderMode = ReaderMode.AutoSetDenseReader;
                settings.Session = 2;
                settings.XArray.Location.TagAgeIntervalSeconds = 20;

                // Specify how often we want to receive location reports
                settings.XArray.Location.ReportIntervalSeconds = 5;

                // Uncomment this is you want to filter tags
                /*
                // Setup a tag filter.
                // Only the tags that match this filter will respond.
                // We want to apply the filter to the EPC memory bank.
                settings.Filters.TagFilter1.MemoryBank = MemoryBank.Epc;
                // Start matching at the third word (bit 32), since the 
                // first two words of the EPC memory bank are the
                // CRC and control bits. BitPointers.Epc is a helper
                // enumeration you can use, so you don't have to remember this.
                settings.Filters.TagFilter1.BitPointer = BitPointers.Epc;
                // Only match tags with EPCs that start with "3008"
                settings.Filters.TagFilter1.TagMask = "3008";
                // This filter is 16 bits long (one word).
                settings.Filters.TagFilter1.BitCount = 16;

                // Set the filter mode. Use only the first filter
                settings.Filters.Mode = TagFilterMode.OnlyFilter1;
                */

                // Apply the newly modified settings.
                reader.ApplySettings(settings);

                // Start the reader
                reader.Start();

                // Wait for the user to press enter.
                Console.WriteLine("Press enter to exit.");
                Console.ReadLine();

                // Apply the default settings before exiting.
                reader.ApplyDefaultSettings();

                // Disconnect from the reader.
                reader.Disconnect();
            }
            catch (OctaneSdkException e)
            {
                // Handle Octane SDK errors.
                Console.WriteLine("Octane SDK exception: {0}", e.Message);
            }
            catch (Exception e)
            {
                // Handle other .NET errors.
                Console.WriteLine("Exception : {0}", e.Message);
            }
        }

        // This event handler will be called when a location report is ready.
        static void OnLocationReported(ImpinjReader reader, LocationReport report)
        {
            // Print out the report details
            Console.WriteLine("Location report");
            Console.WriteLine("   Type = {0}", report.ReportType);
            Console.WriteLine("   EPC = {0}", report.Epc);
            Console.WriteLine("   X = {0} cm", report.LocationXCm);
            Console.WriteLine("   Y = {0} cm", report.LocationYCm);
            Console.WriteLine("   Timestamp = {0} ({1})", report.Timestamp, report.Timestamp.LocalDateTime);
            Console.WriteLine("   Read count = {0}", report.ConfidenceFactors.ReadCount);
        }
    }
}
