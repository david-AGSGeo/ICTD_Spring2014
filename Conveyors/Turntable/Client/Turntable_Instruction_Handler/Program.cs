using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net.Sockets;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

using System.IO;
using System.IO.Pipes;
using System.IO.Ports;


namespace Turntable_Instruction_Handler
{
    class Program
    {
        static SerialPort BTSerial = new SerialPort();

        static void Main(string[] args)
        {
            TurnInstruction ti = new TurnInstruction();
            char[] charBuff = new char[1];
            
            BTSerial = new SerialPort();


            Console.WriteLine("Auto or manual? (a/m)");
            int choice = Console.Read();
            switch (choice)
            {
                case 'a':
                case 'A':

                    //Pipe Client
                    Console.WriteLine("Connecting...");
                    var client = new NamedPipeClientStream("CommsPipe9");
                    client.Connect();
                    Console.WriteLine("Connected");
                    StreamReader reader = new StreamReader(client);
                    StreamWriter writer = new StreamWriter(client);
                    String inputString;


                    while (true)
                    {
                        inputString = reader.ReadLine();
                        Console.WriteLine(inputString);
                        switch (inputString)
                        {
                            case "Reset":
                                TurntableReset(ti);
                                break;
                            case "Calibrate":
                                TurntableCalibrate(ti);
                                break;
                            case "QuarterTurn":
                                TurntableQuarterTurn(ti);
                                break;
                            case "BTConveyorConnect":
                                SerialConnect();
                                break;
                            case "BTConveyorForward":
                                charBuff[0] = 's';
                                if (BTSerial.IsOpen)
                                {
                                    BTSerial.Write(charBuff, 0, 1);
                                }
                                break;
                            case "BTConveyorBackward":
                                charBuff[0] = 'r';
                                if (BTSerial.IsOpen)
                                {
                                    BTSerial.Write(charBuff, 0, 1);
                                }
                                break;

                                charBuff[0] = 's';
                                if (BTSerial.IsOpen)
                                {
                                    BTSerial.Write(charBuff, 0, 1);
                                }
                            default:
                                Console.WriteLine("Unknown Command");
                                break; 
                        }

                    }

                case 'm':
                case 'M':
                    Console.WriteLine("(C)alibrate, (R)eset, (Q)uarterturn, (S)erialConnect, (F)orward, (B)ackward, e(X)it:");
                    while (true)
                    {
                        
                        int command = Console.Read();
                        
                        switch (command)
                        {
                            case 'r':
                            case 'R':
                                TurntableReset(ti);
                                break;
                            case 'c':
                            case 'C':
                                TurntableCalibrate(ti);
                                break;
                            case 'q':
                            case 'Q':
                                TurntableQuarterTurn(ti);
                                break;
                            case 's':
                            case 'S':
                                SerialConnect();
                                break;
                            case 'f':
                            case 'F':
                                charBuff[0] = 's';
                                if (BTSerial.IsOpen)
                                {
                                    BTSerial.Write(charBuff, 0, 1);
                                    Console.WriteLine("sent 's'");
                                }
                                break;
                            case 'b':
                            case 'B':
                                charBuff[0] = 'r';
                                if (BTSerial.IsOpen)
                                {
                                    BTSerial.Write(charBuff, 0, 1);
                                    Console.WriteLine("sent 'r'");

                                }
                                break;
                            case 'x':
                            case 'X':
                                BTSerial.Close();
                                return;

                            default:
                                //WriteLine("Unknown Command");
                                break;
                        }

                    }


                default:
                    //Console.WriteLine("Unknown Command");
                    break;
            }
        }



        private static void SerialConnect()
        {
            // Get a list of serial port names. 
            string[] ports = SerialPort.GetPortNames();

            Console.WriteLine("The following serial ports were found:");

            // Display each port name to the console. 
            foreach (string port in ports)
            {
                Console.WriteLine(port);
            }

            if (ports.Length > 2)
            {
                Console.WriteLine("Connecting to port " + ports[2]);

                BTSerial.PortName = ports[2];
                BTSerial.BaudRate = 9600;

                BTSerial.Open();
                if (BTSerial.IsOpen)
                    Console.WriteLine("Connected");
                else
                    Console.WriteLine("Connection failed");
            }
        }

        private static void TurntableQuarterTurn(TurnInstruction ti)
        {
            ti.command = command.quarter;
            ti.direction = 0;
            ti.rotation = 1;
            JObject o3 = new JObject(new JProperty("TurnInstruction", JObject.FromObject(ti)));
            Connect("192.168.1.9", JsonConvert.SerializeObject(o3));
        }

        private static void TurntableCalibrate(TurnInstruction ti)
        {
            ti.command = command.calibrate;
            JObject o2 = new JObject(new JProperty("TurnInstruction", JObject.FromObject(ti)));
            Connect("192.168.1.9", JsonConvert.SerializeObject(o2));// JsonConvert.SerializeObject(ti));
        }

        private static void TurntableReset(TurnInstruction ti)
        {
            ti.command = command.reset;
            JObject o = new JObject(new JProperty("TurnInstruction", JObject.FromObject(ti)));
            Connect("192.168.1.9", JsonConvert.SerializeObject(o));// JsonConvert.SerializeObject(ti));
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

            //  Console.WriteLine("\n Press Enter to continue...");
            //  Console.Read();

        }
    }

}
