////////////////////////////////////////////////////////////////////////////////
//
//    xArray Features
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
                // This example show some of features specific to xArray
                // For examples of Location and Transition modes, see the projects
                // named XArrayLocation and XArrayTransition
               
                // Connect to the reader.
                // Change the ReaderHostname constant in SolutionConstants.cs 
                // to the IP address or hostname of your reader.
                reader.Connect(SolutionConstants.ReaderHostname);

                // Turn the beacon LED on for 10 seconds
                Console.WriteLine("Turning beacon on for 10 seconds");
                reader.TurnBeaconOn(10000);

                // Wait for the user to press enter.
                Console.WriteLine("Press enter to continue.");
                Console.ReadLine();

                // Turn off the beacon off
                reader.TurnBeaconOff();

                // Query the state of the tilt sensor
                Console.WriteLine("Querying tilt sensor. Press any key to exit.");
                while (true)
                {
                    // Exit if the user presses a key
                    if (Console.KeyAvailable) break;
                    Status status = reader.QueryStatus();
                    Console.WriteLine("X = {0}, Y = {1}",
                        status.TiltSensor.XAxis, status.TiltSensor.YAxis);
                }

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
    }
}
