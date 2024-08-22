#include <SoftwareSerial.h>  // Include the SoftwareSerial library for serial communication with Bluetooth
#include "DHT.h"  // Include the DHT library for temperature and humidity sensor
#define DHTPIN 4  // Define the pin where the DHT sensor is connected
#define DHTTYPE DHT11  // Define the type of DHT sensor used (DHT11)
#define MQ2pin (1)  // Define the pin where the MQ-2 gas sensor is connected

SoftwareSerial BTSerial(3,2); // Create a software serial object for Bluetooth communication on pins 3 (TX) and 2 (RX)

char c = ' ';  // Initialize a character variable for future use
char cup [10];  // Create a character array to hold converted sensor values
const int sensorMin = 0;  // Define the minimum sensor reading (analog input)
const int sensorMax = 1024;  // Define the maximum sensor reading (analog input)
DHT dht(DHTPIN, DHTTYPE);  // Initialize the DHT sensor object
int VaneValue = 0 ;  // Initialize a variable to store the wind vane sensor value
const int OutPin  = A4;  // Define the pin where the wind speed sensor is connected
float sensorValue;  // Initialize a variable to store gas sensor readings

void setup() 
{
    Serial.begin(9600);  // Start the Serial Monitor communication at 9600 baud rate
    Serial.println("Arduino with HC-06 is ready");  // Print a message to the Serial Monitor
 
    BTSerial.begin(9600);  // Start the Bluetooth serial communication at 9600 baud rate
    Serial.println("BTserial started at 9600");  // Print a message indicating Bluetooth communication started

    dht.begin();  // Initialize the DHT sensor
}
 
void loop()
{
  delay(2000);  // Wait for 2 seconds

  BTSerial.write("Sensor 2 \n");  // Send a message via Bluetooth indicating sensor 2 is active
  int sensorReading  = analogRead(A0);  // Read the analog value from pin A0 (fire sensor)
  int range = map(sensorReading, sensorMin, sensorMax, 0, 3);  // Map the sensor reading to a range between 0 and 3

  switch (range) {
  case 0:
    Serial.write(" Fire \n");  // If range is 0, print "Fire" to the Serial Monitor
    BTSerial.write("Fire \n");  // Send "Fire" via Bluetooth
    break;
  case 2:
    Serial.write(" No fire \n");  // If range is 2, print "No fire" to the Serial Monitor
    BTSerial.write("No Fire \n");  // Send "No Fire" via Bluetooth
    break;
  }

  sensorValue = analogRead(MQ2pin);  // Read the analog value from the MQ-2 gas sensor
  
  Serial.print("Gas Sensor Value: ");  // Print "Gas Sensor Value:" to the Serial Monitor
  BTSerial.write("Gas Sensor Value: ");  // Send "Gas Sensor Value:" via Bluetooth
  dtostrf(sensorValue,10,0,cup);  // Convert the sensor value to a string and store it in cup
  Serial.print(sensorValue);  // Print the gas sensor value to the Serial Monitor
  BTSerial.write(cup);  // Send the gas sensor value via Bluetooth
  BTSerial.write("\n");  // Send a newline character via Bluetooth
  
  if(sensorValue > 300)
  {
    Serial.print(" | Smoke detected!");  // If the gas sensor value is greater than 300, print "Smoke detected!" to the Serial Monitor
  }
  
  Serial.println("");  // Print a newline to the Serial Monitor

  float humi  = dht.readHumidity();  // Read the humidity value from the DHT sensor
  float tempC = dht.readTemperature();  // Read the temperature in Celsius from the DHT sensor
  float tempF = dht.readTemperature(true);  // Read the temperature in Fahrenheit from the DHT sensor

  humi = dht.readHumidity();  // Update the humidity value from the DHT sensor
  tempC = dht.readTemperature();  // Update the temperature in Celsius
  tempF = dht.readTemperature(true);  // Update the temperature in Fahrenheit

  Serial.print("Humidity: ");  // Print "Humidity:" to the Serial Monitor
  dtostrf(humi,10,0,cup);  // Convert the humidity value to a string and store it in cup
  Serial.print(humi);  // Print the humidity value to the Serial Monitor
  Serial.print("%");  // Print "%" to indicate percentage
  Serial.print("  |  ");  // Print separator characters for readability
  BTSerial.write("Humidity: ");  // Send "Humidity:" via Bluetooth
  BTSerial.write(cup);  // Send the humidity value via Bluetooth
  BTSerial.write("%");  // Send "%" via Bluetooth
  BTSerial.write("  |  ");  // Send separator characters via Bluetooth

  Serial.print("Temperature: ");  // Print "Temperature:" to the Serial Monitor
  dtostrf(tempF,10,0,cup);  // Convert the temperature value to a string and store it in cup
  Serial.print(tempF);  // Print the temperature value to the Serial Monitor
  Serial.println(" degrees F");  // Print "degrees F" to indicate Fahrenheit
  BTSerial.write("Temperature: ");  // Send "Temperature:" via Bluetooth
  BTSerial.write(cup);  // Send the temperature value via Bluetooth
  BTSerial.write(" degrees F \n");  // Send "degrees F" via Bluetooth with a newline

  VaneValue = analogRead(A3);  // Read the analog value from the wind vane sensor on pin A3
  Serial.print(VaneValue);  // Print the raw wind vane value to the Serial Monitor
  Serial.print("\t\t");  // Print a tab for formatting
  BTSerial.write("Vane value:");  // Send "Vane value:" via Bluetooth
  dtostrf(VaneValue,10,0,cup);  // Convert the wind vane value to a string and store it in cup
  BTSerial.write(cup);  // Send the wind vane value via Bluetooth
  BTSerial.write("  Wind Direction: ");  // Send "Wind Direction:" via Bluetooth
  delay(300);  // Wait for 300 milliseconds

  if(VaneValue < 100) {
    Serial.println("NW");  // If the wind vane value is less than 100, print "NW" to the Serial Monitor
    BTSerial.write("NW \n");  // Send "NW" via Bluetooth
  }
  else if (VaneValue < 205) {
    Serial.println("N");  // If the wind vane value is between 100 and 205, print "N" to the Serial Monitor
    BTSerial.write("N \n");  // Send "N" via Bluetooth
  }
  else if (VaneValue < 285){
    Serial.println("NE");  // If the wind vane value is between 205 and 285, print "NE" to the Serial Monitor
    BTSerial.write("NE \n");  // Send "NE" via Bluetooth
  }
  else if (VaneValue < 350) {
    Serial.println("E");  // If the wind vane value is between 285 and 350, print "E" to the Serial Monitor
    BTSerial.write("E \n");  // Send "E" via Bluetooth
  }
  else if (VaneValue < 425) {
    Serial.println("SE");  // If the wind vane value is between 350 and 425, print "SE" to the Serial Monitor
    BTSerial.write("SE\n");  // Send "SE" via Bluetooth
  }
  else if (VaneValue < 510) {
    Serial.println("S");  // If the wind vane value is between 425 and 510, print "S" to the Serial Monitor
    BTSerial.write("S \n");  // Send "S" via Bluetooth
  }
  else if (VaneValue < 582) {
    Serial.println("SW");  // If the wind vane value is between 510 and 582, print "SW" to the Serial Monitor
    BTSerial.write("SW \n");  // Send "SW" via Bluetooth
  }
  else {
    Serial.println("W");  // If the wind vane value is 582 or higher, print "W" to the Serial Monitor
    BTSerial.write("W \n");  // Send "W" via Bluetooth
  }

  int windADunits = analogRead(OutPin);  // Read the analog value from the wind speed sensor
  float windMPH =  pow((((float)windADunits - 264.0) / 85.6814), 3.36814);  // Calculate the wind speed in MPH using the sensor's calibration formula
  Serial.print(windMPH);  // Print the calculated wind speed to the Serial Monitor
  dtostrf(windMPH,10,0,cup);  // Convert the wind speed value to a string and store it in cup
  BTSerial.write(cup);  // Send the wind speed value via Bluetooth
  Serial.print(" MPH\n");  // Print " MPH

