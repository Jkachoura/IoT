#include "Arduino.h"
#include "DHT.h"
#include "secure.h"

#define LED 2
#define DHTPIN 4     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

DHT dht(DHTPIN, DHTTYPE);

String input;

void setup() {
  Serial.begin(115200);
  
  Serial.println("DHTxx test!");
  dht.begin();

  pinMode(LED, OUTPUT);
  digitalWrite(LED, 0);
}

void loop() {
  delay(2000);
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.println("Wat wil je niffo temperatuur, led:aan, led:uit of vochtigheid?");
  
  while (Serial.available() == 0){}
  
  input = Serial.readString();
  Serial.println(input);
  if(input == "vochtigheid\n"){
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.println("%");
  }
  if(input == "temperatuur\n"){
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.println("°C ");
  }
  if(input == "led:aan\n"){
    Serial.println("Led gaat aan!");
    digitalWrite(LED, 1);
  }
  if(input == "led:uit\n"){
    Serial.println("Led gaat aan!");
    digitalWrite(LED, 0);
  }
}