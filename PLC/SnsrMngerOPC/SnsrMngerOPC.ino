#include <OPC.h>
#include <Bridge.h>

#include <SPI.h>

#include <DHT.h>

#include <Event.h>
#include <Timer.h>

// The I/O pin that the sensors will connect to
#define DHTPIN 2

// DHT 22  (AM2302), The Type of sensor that will be used
#define DHTTYPE DHT22   

// Handles the humidity/temperature sensor
DHT dht(DHTPIN, DHTTYPE);

// Create Timer object
Timer timer;

// Declaring the OPC object
OPCSerial aOPCSerial;

//Function codes 1(read coils), 3(read registers), 5(write coil), 6(write register)
//signed int Mb.R[0 to 125] and bool Mb.C[0 to 128] MB_N_R MB_N_C
//Port 502 (defined in Mudbus.h) MB_PORT

// Sensor Values
float humidityValue;            // Stores humdity value
float temperatureValue;         // Stores temperature value

/**************************************
 * OPC Callbacks
 */
 
// Retrieves the temperaturea value
float getTemperature(const char *itemID, const opcOperation opcOP, const float value) 
{
  return temperatureValue;
}

// Retrieves the humidity value
float getHumidity(const char *itemID, const opcOperation opcOP, const float value) 
{
  return humidityValue;
}

/****************************************
 * Setup Function - For Initialisation and setting up the Arduino
 */ 
void setup()
{
  // Set up an event so that every 2 seconds the values of sensors are updated.
  timer.every(2000, updateSensors);
  
  Serial.begin(9600);
  
  dht.begin();
  
  // Initialise OPC
  aOPCSerial.setup();
  
  // Add OPCItems
  aOPCSerial.addItem("getHumidity", opc_read, opc_float, getHumidity);
  aOPCSerial.addItem("getTemperature", opc_read, opc_float, getTemperature);
}

/****************************************
 * Main Loop - 
 */
void loop()
{
  // OPC process commands
  aOPCSerial.processOPCCommands();
  
  // Update Timer counters
  timer.update();
}

void updateSensors()
{
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  humidityValue = dht.readHumidity();
  temperatureValue = dht.readTemperature(false);
  
  // check if returns are valid, if they are NaN (not a number) then something went wrong!
//  if (isnan(humidityValue) || isnan(temperatureValue)) 
//  {
//    Serial.println("Failed to read from DHT");
//  } 
//  else 
//  {
//    Serial.print("Humidity: ");
//    Serial.print(humidityValue);
//    Serial.print(" %\t");
//    Serial.print("Temperature: ");
//    Serial.print(temperatureValue);
//    Serial.println(" *C");
//  }
}


