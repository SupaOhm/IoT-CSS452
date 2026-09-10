#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Your SSID";
const char* password = "Your Password";
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;
const char* ClientID = "Client_YourStudentID";
const char* Topic = "IoT/PotenValue_YourStudentID";
long lastMsg = 0;

WiFiClient ClientNode;
PubSubClient ClientESP(ClientNode);

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
    
  ClientESP.setServer(mqtt_server, mqtt_port); //Specify the MQTT server and port.
  ConnectMQTT(); //Connect to the MQTT server.
}

void loop() {
  if (!ClientESP.connected()) {
    ConnectMQTT();
  }
  
  long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    char Val[8];
    dtostrf(analogRead(A0), 1, 0, Val); 
    ClientESP.publish(Topic, Val);
    Serial.print("Pub: ");
    Serial.println(Val);
  }
}

void ConnectMQTT() {
  while (!ClientESP.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect to the broker
    if (ClientESP.connect(ClientID, NULL, NULL)) {
          Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(ClientESP.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }  
}
