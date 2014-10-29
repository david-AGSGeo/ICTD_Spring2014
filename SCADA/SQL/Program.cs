using System;
using System.Collections.Generic;
using System.Data;
using System.Data.SqlClient;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApplicationTMCBuffer
{
    class Program
    {
        static void Main(string[] args)
        {
            SqlConnection TMCDB_connection;
            SqlDataReader readBufferTable;
            SqlCommand insertBuffer;
            SqlDataReader readBuffer;
            SqlCommand deleteBuffer;

            string input;
            int menu;
            int BufferID;   //to store the BufferID column data
            string Location;    //to store the Location column data
            
            try
            {
                ///////////////////////////
                //CREATE THE SQL CONNECTION
                ///////////////////////////
                
                //in ConsoleApplication1\Settings.settings\Settings.Designer.cs
                //[global::System.Configuration.DefaultSettingValueAttribute(
                //              "Data Source=GEORGE;Initial Catalog=TMCDB;Integrated Security=True")]
                TMCDB_connection = new SqlConnection(Properties.Settings.Default.connectionString);

                //Open the SQL connection
                try
                {
                    TMCDB_connection.Open();
                }
                catch (SqlException e)
                {
                    Console.WriteLine(e.Message);
                }

                do
                {
                    /////////////////////////
                    // READ THE WHOLE TABLE
                    /////////////////////////

                    //Create an SQL query to read the Buffer table
                    readBufferTable = new SqlCommand("SELECT * FROM dbo.Buffer", TMCDB_connection).ExecuteReader();
                    if (readBufferTable.HasRows)    //Check for data
                    {
                        Console.WriteLine("BufferID\tLocation\n");
                        while (readBufferTable.Read())  //Display row(s) matching query
                        {
                            BufferID = readBufferTable.GetInt32(0);
                            Location = readBufferTable.GetString(1);
                            Console.WriteLine("{0}\t\t{1}", BufferID, Location);
                        }
                    }
                    else
                    {
                        Console.WriteLine("No rows found.");
                    }
                    readBufferTable.Close();

                    ///////////////
                    // MENU SELECT
                    ///////////////
                    Console.WriteLine("\nMENU\n\n1 to insert a new buffer\n2 to view a buffer\n3 to delete a buffer\nor return to end\n");
                    input = Console.ReadLine();
                    switch (input)
                    {
                        case "1":
                            //////////////////////////////////
                            // INSERT A BUFFER INTO THE TABLE
                            //////////////////////////////////
                            Console.WriteLine("Enter buffer id to insert\t");
                            BufferID = int.Parse(Console.ReadLine());

                            Console.WriteLine("Enter buffer location\t");
                            Location = Console.ReadLine();

                            //Create the SQL query to insert a new buffer into the Buffer table
                            insertBuffer = new SqlCommand();
                            insertBuffer.Connection = TMCDB_connection;
                            insertBuffer.CommandType = CommandType.Text;
                            insertBuffer.CommandText = @"INSERT INTO Buffer(BufferID,Location) VALUES(@param1,@param2)";
                            insertBuffer.Parameters.AddWithValue("@param1", BufferID);
                            insertBuffer.Parameters.AddWithValue("@param2", Location);

                            //Execute the insertBuffer query
                            try
                            {
                                insertBuffer.ExecuteNonQuery();
                            }
                            catch (SqlException e)
                            {
                                Console.WriteLine(e.Message);
                            }
                            break;

                        case "2":
                            //////////////////////////////////////
                            // READ A SINGLE BUFFER FROM THE TABLE
                            //////////////////////////////////////
                            Console.WriteLine("Enter buffer id to read");
                            BufferID = int.Parse(Console.ReadLine());

                            //Create an SQL query to read a buffer from the Buffer table
                            readBuffer = new SqlCommand("SELECT * FROM dbo.Buffer WHERE BufferId=" + BufferID, TMCDB_connection).ExecuteReader();

                            if (readBuffer.HasRows) //Check for data
                            {
                                Console.WriteLine("BufferID\tLocation\n");
                                while (readBuffer.Read())  //Display row(s) matching query
                                {
                                    BufferID = readBuffer.GetInt32(0);
                                    Location = readBuffer.GetString(1);
                                    Console.WriteLine("{0}\t\t{1}", BufferID, Location);
                                }
                            }
                            else
                            {
                                Console.WriteLine("No rows found.");
                                readBuffer.Close();
                            }
                            break;

                        case "3":
                            ////////////////////////////////////////
                            // DELETE A SINGLE BUFFER FROM THE TABLE
                            ////////////////////////////////////////
                            Console.WriteLine("Enter buffer id to delete\t");
                            BufferID = int.Parse(Console.ReadLine());

                            //Create the SQL query to delete a buffer from the Buffer table
                            deleteBuffer = new SqlCommand();
                            deleteBuffer.Connection = TMCDB_connection;
                            deleteBuffer.CommandType = CommandType.Text;
                            deleteBuffer.CommandText = @"DELETE FROM Buffer WHERE BufferID = @param3";
                            deleteBuffer.Parameters.AddWithValue("@param3", BufferID);

                            //Execute the deleteBuffer query
                            try
                            {
                                deleteBuffer.ExecuteNonQuery();
                            }
                            catch (Exception e)
                            {
                                Console.WriteLine(e.ToString());
                            }
                            break;

                        default:
                            Console.WriteLine("Invalid selection. Please select 1, 2, or 3.");
                            break;
                    }
                }
                while (input != "");

                //////////////////////////
                //CLOSE THE SQL CONNECTION
                //////////////////////////

                try
                {
                    TMCDB_connection.Close();
                }
                catch (Exception e)
                {
                    Console.WriteLine(e.ToString());
                }
            }

            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
            }
        }
    }
}
