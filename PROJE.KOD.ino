#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

char auth[] = "k2RiSnyLV9tD77PM-WLviWO-5xEDzfzn";


char ssid[] = "VodafoneNet-J7AL5S";
char pass[] = "Fsee.ee012";

#define DHTPIN 2
#define DHTTYPE DHT11     // DHT 11


DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
}


int sensorValue = 0;
void setup()
{
  
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  
  dht.begin();
  

  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run(); 
}
