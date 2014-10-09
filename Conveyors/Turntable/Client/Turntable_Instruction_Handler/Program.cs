using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net.Sockets;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace Turntable_Instruction_Handler
{
    class Program
    {
        static void Main(string[] args)
        {
            // Create Instruction Object
            TurnInstruction ti = new TurnInstruction();
            // Populate Instruction
            ti.command = command.reset;
            ti.rotation = 0;
            ti.direction = 0;

            JObject o = new JObject(new JProperty("TurnInstruction",JObject.FromObject(ti)));


            //Connect("169.254.0.2", JsonConvert.SerializeObject(o));// JsonConvert.SerializeObject(ti));
            Connect("192.168.1.9", JsonConvert.SerializeObject(o));// JsonConvert.SerializeObject(ti));

            ti.command = command.calibrate;
            ti.rotation = 0;
            ti.direction = 0;
            JObject o2 = new JObject(new JProperty("TurnInstruction", JObject.FromObject(ti)));
            //Connect("169.254.0.2", JsonConvert.SerializeObject(o));// JsonConvert.SerializeObject(ti));
            Connect("192.168.1.9", JsonConvert.SerializeObject(o2));// JsonConvert.SerializeObject(ti));
            Console.WriteLine("\n Calibrated: Press Enter to continue");
            Console.Read();

            ti.command = command.quarter;
            ti.rotation = 1;
            ti.direction = 0;
            JObject o3 = new JObject(new JProperty("TurnInstruction", JObject.FromObject(ti)));
            //Connect("169.254.0.2", JsonConvert.SerializeObject(o));// JsonConvert.SerializeObject(ti));
            Connect("192.168.1.9", JsonConvert.SerializeObject(o3));// JsonConvert.SerializeObject(ti));
            Console.WriteLine("\n Press Enter to exit the program");
            Console.Read();

            ti.command = command.quarter;
            ti.rotation = 1;
            ti.direction = 0;
            JObject o4 = new JObject(new JProperty("TurnInstruction", JObject.FromObject(ti)));
            //Connect("169.254.0.2", JsonConvert.SerializeObject(o));// JsonConvert.SerializeObject(ti));
            Connect("192.168.1.9", JsonConvert.SerializeObject(o4));// JsonConvert.SerializeObject(ti));
            Console.WriteLine("\n Press Enter to exit the program");
            Console.Read();

            ti.command = command.quarter;
            ti.rotation = 1;
            ti.direction = 0;
            JObject o5 = new JObject(new JProperty("TurnInstruction", JObject.FromObject(ti)));
            //Connect("169.254.0.2", JsonConvert.SerializeObject(o));// JsonConvert.SerializeObject(ti));
            Connect("192.168.1.9", JsonConvert.SerializeObject(o5));// JsonConvert.SerializeObject(ti));
            Console.WriteLine("\n Press Enter to exit the program");
            Console.Read();

            ti.command = command.quarter;
            ti.rotation = 1;
            ti.direction = 0;
            JObject o6 = new JObject(new JProperty("TurnInstruction", JObject.FromObject(ti)));
            //Connect("169.254.0.2", JsonConvert.SerializeObject(o));// JsonConvert.SerializeObject(ti));
            Connect("192.168.1.9", JsonConvert.SerializeObject(o6));// JsonConvert.SerializeObject(ti));

            //ti.command = command.quarter;
            //ti.rotation = 2;
            //ti.direction = 0;
            //JObject o4 = new JObject(new JProperty("TurnInstruction", JObject.FromObject(ti)));
            //Connect("169.254.0.2", JsonConvert.SerializeObject(o));// JsonConvert.SerializeObject(ti));
            //Connect("169.254.0.2", JsonConvert.SerializeObject(o4));// JsonConvert.SerializeObject(ti));

            //Connect("127.0.0.1", JsonConvert.SerializeObject(ti));
            Console.WriteLine("\n Press Enter to exit the program");
            Console.Read();
        }

        static void Connect(String server, String message)
        {
            try
            {
                // Create a TcpClient. 
                // Note, for this client to work you need to have a TcpServer  
                // connected to the same address as specified by the server, port 
                // combination.
                Int32 port = 3000;
                TcpClient client = new TcpClient(server, port);

                // Translate the passed message into ASCII and store it as a Byte array.
                Byte[] data = System.Text.Encoding.ASCII.GetBytes(message);

                // Get a client stream for reading and writing. 
                //  Stream stream = client.GetStream();

                NetworkStream stream = client.GetStream();

                // Send the message to the connected TcpServer. 
                stream.Write(data, 0, data.Length);

                Console.WriteLine("Sent: {0}", message);

                // Receive the TcpServer.response. 

                // Buffer to store the response bytes.
                data = new Byte[256];

                // String to store the response ASCII representation.
                String responseData = String.Empty;

                // Read the first batch of the TcpServer response bytes.
                Int32 bytes = stream.Read(data, 0, data.Length);
                responseData = System.Text.Encoding.ASCII.GetString(data, 0, bytes);
                Console.WriteLine("Received: {0}", responseData);

                // Close everything.
                stream.Close();
                client.Close();
            }
            catch (ArgumentNullException e)
            {
                Console.WriteLine("ArgumentNullException: {0}", e);
            }
            catch (SocketException e)
            {
                Console.WriteLine("SocketException: {0}", e);
            }

            Console.WriteLine("\n Press Enter to continue...");
            Console.Read();
        }
    }
}
