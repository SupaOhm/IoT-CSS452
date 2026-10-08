#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Your SSID";
const char* password = "Your Password";
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;
const char* ClientID = "Client_SubNode_YourStudentID";
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
  ClientESP.setCallback(callback);
  ConnectMQTT(); //Connect to the MQTT server.

  pinMode(26, OUTPUT); //Set the pin mode to the pin GPIO26
  digitalWrite(26, LOW);
}

void loop() {
  if (!ClientESP.connected()) {
    ConnectMQTT();
  }
  ClientESP.loop();  
}

void ConnectMQTT() {
  while (!ClientESP.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect to the broker
    if (ClientESP.connect(ClientID, NULL, NULL)) {
          Serial.println("connected");
          ClientESP.setCallback(callback);
          ClientESP.subscribe(Topic);         
    } else {
      Serial.print("failed, rc=");
      Serial.print(ClientESP.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }  
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  String ValString;
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    ValString += (char)payload[i];
  }
  Serial.println();
  
  int ValInt = ValString.toInt();  
  Serial.print("Sub : ");
  Serial.println(ValInt);
  Serial.println("============== Wait 2 seconds ===================");
  if (ValInt > 500) {
    digitalWrite(26, HIGH);   // Turn the LED on 
  } else {
    digitalWrite(26, LOW);  // Turn the LED off
  }
}
