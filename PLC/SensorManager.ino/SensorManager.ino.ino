#include <SPI.h>
#include <Ethernet.h>

#include <Mudbus.h>

#include <DHT.h>

#include <Event.h>
#include <Timer.h>


// Debugging the Mudbus library
#define MbDebug

// The I/O pin that the sensors will connect to
#define DHTPIN 2

// DHT 22  (AM2302), The Type of sensor that will be used
#define DHTTYPE DHT22   

// Handles ModBus TCP Protocol Communiccations
Mudbus Mb;

// Handles the humidity/temperature sensor
DHT dht(DHTPIN, DHTTYPE);

// Create Timer object
Timer timer;

//Function codes 1(read coils), 3(read registers), 5(write coil), 6(write register)
//signed int Mb.R[0 to 125] and bool Mb.C[0 to 128] MB_N_R MB_N_C
//Port 502 (defined in Mudbus.h) MB_PORT

// Sensor Values
float humidityValue;            // Stores humdity value
float temperatureValue;         // Stores temperature value

void setup()
{
  // Setup network setup.
  byte mac[]     = { 0x90, 0xA2, 0xDA, 0x00, 0x51, 0x06 };
  byte ip[]      = { 169, 254, 57, 190};
  byte gateway[] = { 169, 254, 57, 1};
  byte dns[]     = { 169, 254, 57, 1 };
  byte subnet[]  = { 255, 255, 0, 0 };
  Ethernet.begin(mac, ip, gateway, dns, subnet);

  Serial.begin(9600);
  dht.begin();
  
  // Set up an event so that every 2 seconds the values of sensors are updated.
  timer.every(2000, updateSensors);
}

void loop()
{
  Mb.Run();
  timer.update();
}

void updateSensors()
{
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  humidityValue = dht.readHumidity();
  temperatureValue = dht.readTemperature(false);
  
  // Store Values into registers following ModBus
  Mb.R[0] = humidityValue;
  Mb.R[1] = temperatureValue;
  
  // check if returns are valid, if they are NaN (not a number) then something went wrong!
  if (isnan(humidityValue) || isnan(temperatureValue)) 
  {
    Serial.println("Failed to read from DHT");
  } 
  else 
  {
    Serial.print("Humidity: ");
    Serial.print(humidityValue);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(temperatureValue);
    Serial.println(" *C");
  }
} 
