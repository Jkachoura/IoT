#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ESPmDNS.h> 
#include <DHT.h>
#include "secret.h"

#define LED 2
#define DHTPIN 4     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

DHT dht(DHTPIN, DHTTYPE);

/* create an instance of WiFiClientSecure */
WiFiClientSecure espClient;
PubSubClient client(espClient);

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
    delay(2000);
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    float h = dht.readHumidity();
    // Read temperature as Celsius (the default)
    float t = dht.readTemperature();
    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t)) {
      client.publish("chat/message", "Fout bij het lezen van de DHT Sensor van BOT-1021584");
      return;
    }
    if(recievedMessage.substring(13) == "led:uit"){
      client.publish("chat/message", "LED is uit voor BOT-1021584");
      digitalWrite(LED, 0);
    }
    if(recievedMessage.substring(13) == "led:aan"){
      client.publish("chat/message", "LED is aan voor BOT-1021584");
      digitalWrite(LED, 1);
    }
//    if(recievedMessage.substring(13) == "vochtigheid"){
//      String *vochtigheid = "Vochtigheid " + String(h) + "%";
//      client.publish("chat/message", vochtigheid);
//    }
//    if(recievedMessage.substring(13) == "temperatuur"){
//      String *temperatuur = "Temperatuur " + String(t) + "°C";
//      client.publish("chat/message", temperatuur);
//    }
  }
}

void mqttconnect(){
  /* Loop until reconnected */
  while (!client.connected())
  {
    Serial.print("MQTT connecting ...");
    /* client ID */
    String clientId = "ESP32Client";
    /* connect now */
    if (client.connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASS))
    {
      Serial.println("Sent user and pwd");
      client.subscribe("chat/message", 0);
    }
    else
    {
      Serial.print("failed, status code =");
      Serial.print(client.state());
      Serial.println("try again in 5 seconds");
      /* Wait 5 seconds before retrying */
      delay(5000);
    }
  }
}

void setup(){
  Serial.begin(115200);
  // We start by connecting to a WiFi network
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

  /* set SSL/TLS certificate */
  espClient.setCACert(local_root_ca);

  /* configure the MQTT server with IPaddress and port */
  client.setServer(MQTT_HOST, MQTT_PORT); //In my case, i put my server dns, ex: "example.com.br"

  //Remember to change this with line with your broker user and password. The client Id can be a number or a char
  if (client.connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASS)){
    Serial.println("Sent user and passwd");
    client.subscribe("chat/message", 0);
    client.publish("chat/message", "BOT-1021584 joined the chat");
  }

  /* this receivedCallback function will be invoked when client received subscribed topic */
  client.setCallback(callback);
  
  dht.begin();
  
  pinMode(LED, OUTPUT);
  digitalWrite(LED, 0);
}

void loop(){
  /* if client was disconnected then try to reconnect again */
  if (!client.connected()){
    mqttconnect();
  }
  
  /* this function will listen for incomming 
  subscribed topic-process-invoke receivedCallback */
  client.loop();
};