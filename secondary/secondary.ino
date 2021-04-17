#include <SoftwareSerial.h>
#include <Wire.h>

int temperature = 0;
int humidity = 0;

#define rxPin 2
#define txPin 3

SoftwareSerial HC06(rxPin, txPin);
int BluetoothData;

void setup()
{
  Serial.begin(9600);

  HC06.begin(9600);
  
  // Start the I2C Bus as Slave on address 9
  Wire.begin(9); 
  
  // Attach a function to trigger when something is received.
  Wire.onReceive(receiveEvent);
}

void receiveEvent(int bytes)
{
  temperature = Wire.read(); //Read one character from the I2C.
  humidity = Wire.read();
  
  Serial.print("Received: t: ");
  Serial.print(temperature);
  Serial.print(" h: ");
  Serial.println(humidity);

  String s = String(temperature) + "x" + String(humidity);
  
  HC06.println(s);
}

void loop()
{
}
