﻿////////////////////////////////////////////////////////////////////////////////
//
//    Configure Many Antennas
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
                // This example shows some of the options for configuring 
                // a reader with many antennas (xArray, Antenna Hub)

                // Connect to the reader.
                // Change the ReaderHostname constant in SolutionConstants.cs 
                // to the IP address or hostname of your reader.
                reader.Connect(SolutionConstants.ReaderHostname);

                // Assign the TagsReported event handler.
                // This specifies which method to call
                // when tags reports are available.
                reader.TagsReported += OnTagsReported;

                // Get the default settings
                // We'll use these as a starting point
                // and then modify the settings we're 
                // interested in.
                Settings settings = reader.QueryDefaultSettings();

                // Add antenna number to tag report
                settings.Report.IncludeAntennaPortNumber = true;

                // Start by disabling all of the antennas
                settings.Antennas.DisableAll();

                // Enable antennas by specifying an array of antenna IDs
                settings.Antennas.EnableById(new ushort[] { 1, 3, 5, 7, 9, 15, 22, 27, 28, 30, 33, 34, 39, 40, 41, 50 });
                // Or set each antenna individually
                //settings.Antennas.GetAntenna(1).IsEnabled = true;
                //settings.Antennas.GetAntenna(3).IsEnabled = true;
                // ...

                // Set all the antennas to the max transmit power and receive sensitivity
                settings.Antennas.TxPowerMax = true;
                settings.Antennas.RxSensitivityMax = true;
                // Or set all antennas to a specific value in dBm
                //settings.Antennas.TxPowerInDbm = 28.0;
                //settings.Antennas.RxSensitivityInDbm = -70.0;
                // Or set each antenna individually
                //settings.Antennas.GetAntenna(1).MaxTxPower = true;
                //settings.Antennas.GetAntenna(1).MaxRxSensitivity = true;
                //settings.Antennas.GetAntenna(2).TxPowerInDbm = 30.0;
                //settings.Antennas.GetAntenna(2).RxSensitivityInDbm = -70.0;
                // ...

                // xArray only
                // Enable antennas by sector number
                //settings.Antennas.EnableBySector(new ushort[] { 3, 4, 5 });

                // xArray only
                // Enable antennas by ring number
                //settings.Antennas.EnableByRing(new ushort[] { 6, 7 });

                // Apply the newly modified settings.
                reader.ApplySettings(settings);

                // Start reading.
                reader.Start();

                // Wait for the user to press enter.
                Console.WriteLine("Press enter to exit.");
                Console.ReadLine();

                // Stop reading.
                reader.Stop();

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

        static void OnTagsReported(ImpinjReader sender, TagReport report)
        {
            // This event handler is called asynchronously 
            // when tag reports are available.
            // Loop through each tag in the report 
            // and print the data.
            foreach (Tag tag in report)
            {
                Console.WriteLine("Antenna : {0} EPC : {1}", tag.AntennaPortNumber, tag.Epc);
            }
        }
    }
}
