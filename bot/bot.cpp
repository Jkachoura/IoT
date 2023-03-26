#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ESPmDNS.h> 
#include <DHT.h>
#include "secret.h"

#define LED 2
#define DHTPIN 4     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
WiFiClientSecure espClient;
PubSubClient client(espClient);

void wifiConnect(){
  // Function to connect to WiFi
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char *topic, byte *payload, unsigned int length){
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  String recievedMessage = "";
  for (int i = 0; i < length; i++)
  {
    recievedMessage.concat((char)payload[i]);
  }
  Serial.println(recievedMessage);

  if(recievedMessage.substring(0,11) == MQTT_CLIENT_ID){
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    delay(2000);
    // Read humidity
    float h = dht.readHumidity();
    // Read temperature
    float t = dht.readTemperature();
    // Check if any reads failed and try again
    if (isnan(h) || isnan(t)) {
      client.publish("chat/message", "Fout bij het lezen van de DHT Sensor van BOT-1021584");
      return;
    }
    // Now we check what someone send after the BOT-1021584: 
    // If someone send led:uit the LED on the BOT will turn off
    if(recievedMessage.substring(13) == "led:uit"){
      client.publish("chat/message", "LED is uit");
      digitalWrite(LED, 0);
    }
    // If someone send led:aan the LED on the BOT will turn on
    if(recievedMessage.substring(13) == "led:aan"){
      client.publish("chat/message", "LED is aan");
      digitalWrite(LED, 1);
    }
    // If somesone send vochtigheid the BOT will respond with the humidity from the place where the BOT is located
    if(recievedMessage.substring(13) == "vochtigheid"){
      String vochtigheid = "Vochtigheid is " + String(h) + "%";
      client.publish("chat/message", vochtigheid.c_str());
    }
    // If somesone send vochtigheid the BOT will respond with the temperature from the place where the BOT is located
    if(recievedMessage.substring(13) == "temperatuur"){
      String temperatuur = "Temperatuur is " + String(t) + "°C";
      client.publish("chat/message", temperatuur.c_str());
    }
  }
}

void mqttConnect(){
  // Looping until reconnected
  while (!client.connected()){
    Serial.print("MQTT connecting ...");
    if (client.connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASS)){
      client.subscribe("chat/message", 0);
      client.publish("chat/message", "BOT-1021584 joined the chat");
    }
    else{
      Serial.print("failed, status code =");
      Serial.print(client.state());
      Serial.println("try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup(){
  Serial.begin(115200);
  wifiConnect();

  // Sets the ssl/tls certificate
  espClient.setCACert(local_root_ca);

  // Set the MQTT server change in the secret.h file for different address and port.
  client.setServer(MQTT_HOST, MQTT_PORT);

  // Subscribe to correct topic on the mqtt server.
  if (client.connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASS)){
    client.subscribe("chat/message", 0);
    client.publish("chat/message", "BOT-1021584 joined the chat");
  }

  // The callback fucntion will be called if there's a message recieved on the topic
  client.setCallback(callback);
  
  dht.begin();
  
  pinMode(LED, OUTPUT);
  digitalWrite(LED, 0);
}

void loop(){
  // If client disconnect try to reconnect.
  if (!client.connected()){
    mqttConnect();
  }
  
  // Listening for incoming messages on the subscribed topic
  client.loop();
};
