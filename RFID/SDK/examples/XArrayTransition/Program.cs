////////////////////////////////////////////////////////////////////////////////
//
//    xArray Transition Example
//
////////////////////////////////////////////////////////////////////////////////

using System;
using Impinj.OctaneSdk;
using System.Collections.Generic;

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

                // Assign the TransitionReported event handler.
                // This specifies which method to call
                // when a transition report is available.
                reader.TransitionReported += OnTransitionReported;

                // Get the default settings
                // We'll use these as a starting point
                // and then modify the settings we're 
                // interested in.
                Settings settings = reader.QueryDefaultSettings();

                // Put the xArray into transition mode
                settings.XArray.Mode = XArrayMode.Transition;

                // Enable all three report types
                settings.XArray.Transition.EntryReportEnabled = true;
                settings.XArray.Transition.TransitionReportEnabled = true;
                settings.XArray.Transition.StrayReportEnabled = true;
                
                // Set xArray transition parameters
                settings.ReaderMode = ReaderMode.AutoSetDenseReader;
                settings.XArray.Transition.InitialStraySearchTimeSec = 15;
                settings.XArray.Transition.StraySession = 2;
                settings.XArray.Transition.StrayTagAgeSec = 3000;
                settings.XArray.Transition.TOISession = 1;
                settings.XArray.Transition.StrayUpdateIntervalSec = 60;
                settings.XArray.Transition.TOITagAgeSec = 100;
                settings.XArray.Transition.TransitionZoneRange = TransitionZoneRange.Standard;

                // Create a list of transition zones. 
                // xArray currently supports a maximum of two zones.
                settings.XArray.Transition.TransitionZones = new List<TransitionZone>();
                
                // Define the first zone
                TransitionZone zone1 = new TransitionZone();
                // An numerical identifier for the zone
                zone1.ZoneId = 1;
                // A list of sectors to include in this zone
                zone1.SectorIds = new List<ushort>() { 2, 3, 8, 9 };
                // Add this zone to the list of zones
                settings.XArray.Transition.TransitionZones.Add(zone1);

                // Define the second zone
                TransitionZone zone2 = new TransitionZone();
                // An numerical identifier for the zone
                zone2.ZoneId = 2;
                // A list of sectors to include in this zone
                zone2.SectorIds = new List<ushort>() { 4, 5, 6, 7 };
                // Add this zone to the list of zones
                settings.XArray.Transition.TransitionZones.Add(zone2);

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
        static void OnTransitionReported(ImpinjReader reader, TransitionReport report)
        {
            // Print out the report details
            Console.WriteLine("Transition report");
            Console.WriteLine("   Type = {0}", report.ReportType);
            foreach (TagData epc in report.Epcs)
            {
                Console.WriteLine("   EPC = {0}", epc.ToHexString());
            }
            if (report.ReportType == TransitionReportType.TagTransition)
            {
                Console.WriteLine("   From Zone {0} to Zone {1}", report.FromZoneId, report.ToZoneId);
            }
            else
            {
                Console.WriteLine("   In Zone {0}", report.FromZoneId);
            }
            Console.WriteLine("   Timestamp = {0} ({1})", report.Timestamp, report.Timestamp.LocalDateTime);
            Console.WriteLine("   Confidence = {0}", report.Confidence);
        }
    }
}
