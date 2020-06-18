#include <LWiFi.h>
#include "MCS.h"

#include "DHT.h"
#define DHTTYPE DHT11
#define DHTPIN 5 
char _lwifi_ssid[] = "home NO.17 1F";
char _lwifi_pass[] = "034921540";
MCSDevice mcs("DDoGeTuM", "WT4HYij392dHfwqO");

MCSDisplayInteger  Temp("C");
MCSDisplayInteger  Temp1("H");
DHT dht(DHTPIN, DHTTYPE);
void setup()
{
  Serial.begin(9600);
  dht.begin();
  Serial.println("Connect to Wifi");
  while (WiFi.begin(_lwifi_ssid, _lwifi_pass) != WL_CONNECTED) {
    Serial.println("Wifi Reconnecting..");
    delay(1000);
  }

  Serial.println("Connect to MCS...");
  while (!mcs.connected()) {
    Serial.println("MCS Reconnecting..");
    mcs.connect();
  }
  Serial.println("MCS Connected!");

  mcs.addChannel(Temp);
 mcs.addChannel(Temp1);
}


void loop()
{ float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);
Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
 while (WiFi.begin(_lwifi_ssid, _lwifi_pass) != WL_CONNECTED) {
    Serial.println("Wifi Reconnecting..");
    delay(1000);
  }

  while (!mcs.connected()) {
    mcs.connect();
    if (mcs.connected()) {
      Serial.println("MCS Reconnect");
    }
  }
  mcs.process(500);
  
  Temp.set(t);
  Temp1.set(h);
  Serial.println("Add sensor value.");
  
}
