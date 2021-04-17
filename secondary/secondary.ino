#include <SoftwareSerial.h>
#include <Wire.h>

constexpr int I2C_ADDRESS = 9;
constexpr int RX_PIN = 2;
constexpr int TX_PIN = 3;

SoftwareSerial HC06(RX_PIN, TX_PIN);

int temperature = 0;
int humidity = 0;

void setup()
{
  Serial.begin(9600);
  HC06.begin(9600);
  Wire.begin(I2C_ADDRESS); //Start the I2C Bus as Slave on address 9.
  Wire.onReceive(receiveEvent); //Attach a function to trigger when something is received.
}

//Called whenever data is received through I2C.
void receiveEvent(int bytes)
{
  //Read the temperature first, then the humidity;
  temperature = Wire.read();
  humidity = Wire.read();

  //Create a string with the data, and send it through bluetooth.
  String toSend = String(temperature) + " " + String(humidity);
  
  HC06.println(toSend);
}

void loop()
{
  //The secondary board does nothing in the main loop.
}
