////////////////////////////////////////////////////////////////////////////////
//
//    Multiple Readers
//
////////////////////////////////////////////////////////////////////////////////

using System;
using Impinj.OctaneSdk;
using System.Collections.Generic;

namespace OctaneSdkExamples
{
    class Program
    {
        // Create a collection to hold all the ImpinjReader instances.
        static List<ImpinjReader> readers = new List<ImpinjReader>();

        static void Main(string[] args)
        {
            try
            {
                // Create two reader instances and add them to the List of readers.
                readers.Add(new ImpinjReader(SolutionConstants.ReaderHostname, "Reader #1"));
                // Change "SpeedwayR-10-27-52" to the IP address 
                // or hostname of the second reader.
                readers.Add(new ImpinjReader("SpeedwayR-10-27-52", "Reader #2"));

                // Loop through the List of readers to configure and start them.
                foreach (ImpinjReader reader in readers)
                {
                    // Connect to the reader
                    reader.Connect();

                    // Get the default settings
                    // We'll use these as a starting point
                    // and then modify the settings we're 
                    // interested in.
                    Settings settings = reader.QueryDefaultSettings();

                    // Apply the newly modified settings.
                    reader.ApplySettings(settings);

                    // Assign the TagsReported event handler.
                    // This specifies which method to call
                    // when tags reports are available.
                    reader.TagsReported += OnTagsReported;

                    // Start reading.
                    reader.Start();
                }

                // Wait for the user to press enter.
                Console.WriteLine("Press enter to exit.");
                Console.ReadLine();

                // Stop all the readers and disconnect from them.
                foreach (ImpinjReader reader in readers)
                {
                    // Stop reading.
                    reader.Stop();

                    // Disconnect from the reader.
                    reader.Disconnect();
                }
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
                Console.WriteLine("{0} ({1}) : {2}",
                                    sender.Name, sender.Address, tag.Epc);
            }
        }
    }
}
