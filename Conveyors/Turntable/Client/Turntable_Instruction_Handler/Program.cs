﻿using System;
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
using System.Threading;


namespace Turntable_Instruction_Handler
{
    class Program
    {
        static SerialPort BTSerial = new SerialPort();
        static StreamReader reader; 
        static StreamWriter writer;
        static String readBTConveyor;
        static int ErrorCount = 0;

        static void Main(string[] args)
        {
            //Mutex to prevent multiple instances running
            bool createdNew = true;
            Mutex mutex = new Mutex(true, "ConveyorController", out createdNew);

            
                if (!createdNew)
                {
                    return;
                }
                else
                {
                    Console.WriteLine("First Instance");
                }
            
            
            TurnInstruction ti = new TurnInstruction();
            char[] outCharBuff = new char[1];
            //string readBTConveyor;
            BTSerial = new SerialPort();
            NamedPipeServerStream ConveyorReadPipe = null;
            NamedPipeServerStream ConveyorWritePipe = null;



            Console.WriteLine("Auto or manual? (a/m)");
            //int choice = Console.Read();
            int choice = 'a';
            switch (choice)
                    
            {
                case 'a':
                case 'A':
                    
                    //Pipe Server
                    Console.WriteLine("Creating Pipe......");
                    try
                    {
                        ConveyorReadPipe = new NamedPipeServerStream("ConveyorReadPipe");
                        ConveyorWritePipe = new NamedPipeServerStream("ConveyorWritePipe");


                        Console.WriteLine("Waiting for client...");
                        ConveyorReadPipe.WaitForConnection();
                        ConveyorWritePipe.WaitForConnection();
                    }
                    catch (System.IO.IOException)
                    {
                        Console.WriteLine("Exception");
                    }
                        Console.WriteLine("Connected");
                        reader = new StreamReader(ConveyorReadPipe);
                        writer = new StreamWriter(ConveyorWritePipe);
                        String inputString;
                    
                    
                    
                    //serial connection
                    SerialConnect();

                    while (true)
                    {
                        inputString = reader.ReadLine();
                        Console.WriteLine(inputString);
                        switch (inputString)
                        {
                            case "Reset":
                                try
                                {
                                    writer.WriteLineAsync(TurntableReset(ti));
                                    writer.Flush();
                                    
                                }
                                catch (System.IO.IOException)
                                {
                                    Console.WriteLine("Exception");
                                }
                                break;
                            case "Calibrate":
                                try
                                {
                                writer.WriteLineAsync(TurntableCalibrate(ti));
                                writer.Flush();
                               
                                break;
                                    }
                                catch (System.IO.IOException)
                                {
                                    Console.WriteLine("Exception");
                                }
                                break;
                            case "QuarterTurn":
                                    try
                                {
                                writer.WriteLineAsync(TurntableQuarterTurn(ti));
                                writer.Flush();
                                
                               
                                break;
                                        }
                                catch (System.IO.IOException)
                                {
                                    Console.WriteLine("Exception");
                                }
                                    break;
                            case "BTConveyorForward":
                                outCharBuff[0] = 's';
                                        try
                                {
                                if (BTSerial.IsOpen)
                                {
                                    BTSerial.Write(outCharBuff, 0, 1);
                                    Console.WriteLine(outCharBuff);
                                    readBTConveyor = BTSerial.ReadLine();
                                    Console.WriteLine(readBTConveyor);
                                    writer.WriteLine("Forward Complete");
                                    writer.Flush();
                                }
                                break;
                                            }
                                catch (System.IO.IOException)
                                {
                                    Console.WriteLine("Exception");
                                }
                                        break;
                            case "BTConveyorReset":
                                        try
                                        {
                                            outCharBuff[0] = 'r';
                                            if (BTSerial.IsOpen)
                                            {
                                                BTSerial.Write(outCharBuff, 0, 1);
                                                Console.WriteLine(outCharBuff);
                                                readBTConveyor = BTSerial.ReadLine();
                                                Console.WriteLine(readBTConveyor);
                                                writer.WriteLine("Reset Complete");
                                                writer.Flush();
                                            }

                                            break;
                                        }
                                        catch (System.IO.IOException)
                                        {
                                            Console.WriteLine("Exception");
                                        }
                                        break;
                            case "BTConveyorBackward":
                                 try
                                        {
                                        outCharBuff[0] = 'a';
                                        if (BTSerial.IsOpen)
                                        {
                                            BTSerial.Write(outCharBuff, 0, 1);
                                            Console.WriteLine(outCharBuff);
                                            readBTConveyor = BTSerial.ReadLine();
                                            Console.WriteLine(readBTConveyor);
                                            writer.WriteLine("Backwards Complete");
                                            writer.Flush();
                                        }

                                        break;
                                     }
                                        catch (System.IO.IOException)
                                        {
                                            Console.WriteLine("Exception");
                                        }
                                        break;
                            case "Disconnect":
                                return;
                                

                              
                            default:
                                Console.WriteLine("Unknown Command");
                                ErrorCount++;
                                if (ErrorCount > 5)
                                {
                                    return;
                                }
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
                                outCharBuff[0] = 's';
                                if (BTSerial.IsOpen)
                                {
                                    BTSerial.Write(outCharBuff, 0, 1);
                                    Console.WriteLine("sent 's'");
                                    try
                                    {
                                        readBTConveyor = BTSerial.ReadLine();
                                        Console.WriteLine(readBTConveyor);
                                    }
                                    catch (TimeoutException)
                                    {
                                        Console.WriteLine("no response");
                                    }
                                }
                                break;
                            case 'b':
                            case 'B':
                                outCharBuff[0] = 'r';
                                if (BTSerial.IsOpen)
                                {
                                    BTSerial.Write(outCharBuff, 0, 1);
                                    Console.WriteLine("sent 'r'");
                                    try
                                    {
                                        readBTConveyor = BTSerial.ReadLine();
                                        Console.WriteLine(readBTConveyor);
                                    }
                                    catch (TimeoutException) 
                                    {
                                        Console.WriteLine("no response");
                                    }
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
                
                Console.WriteLine("Connecting to port " + ports[3]);

                BTSerial.PortName = ports[3];
                BTSerial.BaudRate = 9600;
                try
                {
                    BTSerial.Open();
                }
                catch(Exception e)
                {
                    Console.WriteLine("Connection failed" + e.ToString());
                }
                if (BTSerial.IsOpen)
                    Console.WriteLine("Connected");
                else
                    Console.WriteLine("Connection failed");
            }
        }

        private static string TurntableQuarterTurn(TurnInstruction ti)
        {
            ti.command = command.quarter;
            ti.direction = 0;
            ti.rotation = 1;
            JObject o3 = new JObject(new JProperty("TurnInstruction", JObject.FromObject(ti)));
            return (Connect("192.168.1.9", JsonConvert.SerializeObject(o3)));
        }

        private static string TurntableCalibrate(TurnInstruction ti)
        {
            ti.command = command.calibrate;
            JObject o2 = new JObject(new JProperty("TurnInstruction", JObject.FromObject(ti)));
            return (Connect("192.168.1.9", JsonConvert.SerializeObject(o2)));
        }

        private static string TurntableReset(TurnInstruction ti)
        {
            ti.command = command.reset;
            JObject o = new JObject(new JProperty("TurnInstruction", JObject.FromObject(ti)));
            return (Connect("192.168.1.9", JsonConvert.SerializeObject(o)));
        }

        static string Connect(String server, String message)
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
                //writer.WriteLine(responseData);
                return responseData;
            }
            catch (ArgumentNullException e)
            {
                Console.WriteLine("ArgumentNullException: {0}", e);
                return "error";
            }
            catch (SocketException e)
            {
                Console.WriteLine("SocketException: {0}", e);
                return "error";
            }

            //  Console.WriteLine("\n Press Enter to continue...");
            //  Console.Read();

        }
    }

}
