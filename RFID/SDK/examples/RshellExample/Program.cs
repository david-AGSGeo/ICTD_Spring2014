////////////////////////////////////////////////////////////////////////////////
//
//    RShell
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
            string reply;

            try
            {
                // Open up an RShell connection on the reader.
                // Specify the reader address, user name, password and connection timeout.
                reader.RShell.Open(SolutionConstants.ReaderHostname, "root", "impinj", 5000);

                // Send an RShell command
                RShellCmdStatus status = reader.RShell.Send("show network summary", out reply);
                
                // Check the status
                if (status == RShellCmdStatus.Success)
                {
                    Console.WriteLine("RShell command executed successfully.\n");
                }
                else
                {
                    Console.WriteLine("RShell command failed to execute.\n");
                }

                // Print out the entire reply.
                Console.WriteLine("RShell command reply : \n\n" + reply + "\n");
                
                // Close the RShell connection.
                reader.RShell.Close();

                // Wait for the user to press enter.
                Console.WriteLine("Press enter to exit.");
                Console.ReadLine();
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
