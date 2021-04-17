#include <Wire.h>
#include <dht_nonblocking.h>

constexpr int DHT_SENSOR_PIN = 2;
constexpr int I2C_ADDRESS = 9;
DHT_nonblocking DHT_SENSOR(DHT_SENSOR_PIN, DHT_TYPE_11);

void setup()
{
  Serial.begin(9600);
  Wire.begin(); // Start the I2C Bus as Master.
}

//Grabs temperature and humidity from the DHT sensor.
void measure_environment(float * temperature, float * humidity)
{
  bool done = false;

  while(!done)
  {
    done = DHT_SENSOR.measure(temperature, humidity);
  }
}

void loop()
{
  float temperature, humidity;

  //Read from the sensor.
  measure_environment(&temperature, &humidity);

  //Send info to the secondary board through I2C.
  Wire.beginTransmission(I2C_ADDRESS);
  Wire.write((int)temperature);
  Wire.write((int)humidity);
  Wire.endTransmission();
  
  delay(5000);
}
