#include <Wire.h>
#include <dht_nonblocking.h>

constexpr int DHT_SENSOR_PIN = 2;
DHT_nonblocking DHT_SENSOR(DHT_SENSOR_PIN, DHT_TYPE_11);

void setup()
{
  Serial.begin(9600);
  Wire.begin(); // Start the I2C Bus as Master.
}

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

  measure_environment(&temperature, &humidity);

  Wire.beginTransmission(9); //Begin transmission on address #9.
  Wire.write((int)temperature);
  Wire.write((int)humidity);
  Wire.endTransmission();
  
  delay(5000);
}
