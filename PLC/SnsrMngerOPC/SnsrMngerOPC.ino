#include <OPC.h>
#include <Bridge.h>

#include <SPI.h>

#include <DHT.h>

#include <Event.h>
#include <Timer.h>

#define LUX_CONVERSION 0.9765625  // The conversion factor of the ADC value to lux.

#define DHTPIN 2                // The I/O pin that the sensors will connect to

#define DHTTYPE DHT22           // DHT 22  (AM2302), The Type of sensor that will be used

DHT dht(DHTPIN, DHTTYPE);       // Handles the humidity/temperature sensor

Timer timer;                    // Create Timer object

OPCSerial aOPCSerial;           // Declaring the OPC object

float humidityValue;            // Stores humdity value
float temperatureValue;         // Stores temperature value
float luxValue;                 // Stores illuminance value

int lightLevel;                  // The 10 bit value of the voltage from light sensor read by ADC

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

// Retrieves the humidity value
float getLux(const char *itemID, const opcOperation opcOP, const float value) 
{
  return luxValue;
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
  aOPCSerial.addItem("getLux", opc_read, opc_float, getLux);
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
  
  // Update Light
  lightLevel = analogRead(A0);
  luxValue = lightLevel * LUX_CONVERSION;
  
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
//    Serial.print("Illuminance: ");
//    Serial.print(luxValue);
//    Serial.println(" lx");
//  }
}
