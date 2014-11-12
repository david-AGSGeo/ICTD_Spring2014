using System;
using System.IO;
using System.IO.Pipes;

namespace DetectionAdroit
{
    class DetectionAdroit
    {
        NamedPipeClientStream client;
        StreamReader reader;
        StreamWriter writer;

        // Define Delimiters for each string
        char[] delimiterChars = { ' ', ',', '.', ':', '\t' };

        // Buffer where return message will be stored
        string[] returnMessage;

        string command;     // The command to send to the detection system
        string status;      // The returned status based on command.
        string color;       // The returned color of tablet.

        int offsetX;        // The offsetX of tablet/tray
        int offsetY;        // The offsetY of tablet/tray
        int angle;          // The angle of tray

        static void Main(string[] args)
        {
            // RETRIEVE NECESSARY DATAELEMENTS(TAGS/AGENT) in Adroit

            // DetectionAdroit da = new DetectionAdroit();
            // da.createAndConnect();

            // Based on command build string message and call writeToPipe method.

            // Either have a wait for detection system to process command or
            // call straight up readFromPipe method.

            // Call processReturnMessage().
        }

        void createAndConnect()
        {
            client = new NamedPipeClientStream(
                ".",
                "DetectionSystem",
                PipeDirection.InOut,
                PipeOptions.None
            );

            Console.Write("Attempting to connect to pipe...");
            client.Connect();
            Console.WriteLine("Connected to pipe.");
            Console.WriteLine("There are currently {0} pipe server instances open.",
                client.NumberOfServerInstances);

            reader = new StreamReader(client);
            writer = new StreamWriter(client);
        }

        void writeToPipe(string message)
        {
            writer.WriteLine(message);      // Write data into stream
            writer.Flush();                 // Causes buffered data to be written
        }

        void readFromPipe()
        {
            // Read return message and split the strings
            returnMessage = null;
            returnMessage = reader.ReadLine().Split(delimiterChars);
        }

        // TODO: 
        void buildMessage()
        {

        }

        // Processes the return message read from the pipe
        void processReturnMessage()
        {
            switch (command)
            {
                case "checkSystem":
                case "shutdown":
                    // Update status tag of detection system in adroit
                    // returnMessage[0] is the status
                    break;
                case "checkTray":
                    // Update Adroit Tags
                    // returnMessage[0] is the status of the current tray
                    // returnMessage[1] is the offset X
                    // returnMessage[2] is the offset Y
                    // returnMessage[3] is the angle
                    break;
                case "checkTablet":
                    if (returnMessage[0].Equals("noTablet"))
                    {
                        // Trigger a warning in adroit to put more tablets in the stock.
                    }
                    else
                    {
                        // Update Adroit Tags
                        // returnMessage[0] is the status if tablet
                        // returnMessage[1] is the offset X
                        // returnMessage[2] is the offset Y
                        // returnMessage[3] is the color
                    }
                    break;
                case "checkProduct":
                    // Update Product status tag
                    // returnMessage[0] is the status
                    break;
            }
        }
    }
}