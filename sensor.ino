#include "DHT.h"

#define DHTPIN 23

#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void dhtSetup() {
  Serial.println("DHT Setup");
  dht.begin();
}

float getTemp() {
  Serial.println("Getting Temp");
  Serial.println(dht.readTemperature(true));
  return dht.readTemperature(true);
}