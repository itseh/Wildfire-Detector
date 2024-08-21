#include <SoftwareSerial.h>
#include "DHT.h"
#define DHTPIN 4
#define DHTTYPE DHT11
#define MQ2pin (1)

SoftwareSerial BTSerial(3,2); // TX | RX
 
char c = ' ';
char cup [10];
const int sensorMin = 0;
const int sensorMax = 1024;
DHT dht(DHTPIN, DHTTYPE);
int VaneValue = 0 ;
const int OutPin  = A4;
float sensorValue;

void setup() 
{
    Serial.begin(9600);
    Serial.println("Arduino with HC-06 is ready");
 
    // HC-06 default baud rate is 9600
    BTSerial.begin(9600);  
    Serial.println("BTserial started at 9600");

    dht.begin();
}
 
void loop()
{
  BTSerial.write("Sensor 1 \n") ;
  int sensorReading  = analogRead(A0);
    int range = map(sensorReading,  sensorMin, sensorMax, 0, 3);

  switch (range) {
  case 0:
    Serial.write(" Fire \n");
    BTSerial.write("Fire \n") ;
    break;
  case 2:
    Serial.write(" No fire \n");
    BTSerial.write("No Fire \n") ;
    break;
  }

  sensorValue = analogRead(MQ2pin);
  
  Serial.print("Gas Sensor Value: ");
  BTSerial.write("Gas Sensor Value: ") ;
  dtostrf(sensorValue,10,0,cup);
  Serial.print(sensorValue);
  BTSerial.write(cup) ;
  BTSerial.write("\n") ;
  
  if(sensorValue > 300)
  {
    Serial.print(" | Smoke detected!");
  }
  
  Serial.println("");

  float humi  = dht.readHumidity();
  // read temperature as Celsius
  float tempC = dht.readTemperature();
  // read temperature as Fahrenheit
  float tempF = dht.readTemperature(true);

  humi=dht.readHumidity();
  tempC=dht.readTemperature();
  tempF=dht.readTemperature(true);
    Serial.print("Humidity: ");
    dtostrf(humi,10,0,cup);
    Serial.print(humi);
    Serial.print("%");
    Serial.print("  |  "); 
    BTSerial.write("Humidity: ");
    BTSerial.write(cup);
    BTSerial.write("%");
    BTSerial.write("  |  "); 

    Serial.print("Temperature: ");
    dtostrf(tempF,10,0,cup);
    Serial.print(tempF);
    Serial.println(" degrees F");
    BTSerial.write("Temperature: ");
    BTSerial.write(cup);
    BTSerial.write(" degrees F \n");
   
  VaneValue = analogRead(A3);
Serial.print(VaneValue); Serial.print("\t\t");
BTSerial.write("Vane value:") ;
dtostrf(VaneValue,10,0,cup);
BTSerial.write(cup) ;
BTSerial.write("  Wind Direction: ") ;
delay(300) ;

if(VaneValue < 100) {
Serial.println("NW");
BTSerial.write("NW \n") ;
}
else if (VaneValue < 205) {
Serial.println("N");
BTSerial.write("N \n") ;
}
else if (VaneValue < 285){
Serial.println("NE");
BTSerial.write("NE \n") ;
}
else if (VaneValue < 350) {
Serial.println("E");
BTSerial.write("E \n") ;
}
else if (VaneValue < 425) {
Serial.println("SE");
BTSerial.write("SE\n") ;
}
else if (VaneValue < 510) {
Serial.println("S");
BTSerial.write("S \n") ;
}
else if (VaneValue < 582) {
Serial.println("SW");
BTSerial.write("SW \n") ;
}
else {
Serial.println("W");
BTSerial.write("W \n") ;
}

    int windADunits = analogRead(OutPin);
    float windMPH =  pow((((float)windADunits - 264.0) / 85.6814), 3.36814);
    Serial.print(windMPH);
    dtostrf(windMPH,10,0,cup);
    BTSerial.write(cup) ;
    Serial.print(" MPH\n");
    BTSerial.write(" MPH \n") ;

  // Keep reading from HC-06 and send to Arduino Serial Monitor
  if (BTSerial.available())
    Serial.write(BTSerial.read());
 
  // Keep reading from Arduino Serial Monitor and send to HC-06
  if (Serial.available())
  BTSerial.write(Serial.read());
  delay(3000) ;
}