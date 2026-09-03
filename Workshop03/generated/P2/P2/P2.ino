#include <WiFi.h>
#include <HTTPClient.h>

// Replace with your network credentials
const char* ssid = "MyWiFi";
const char* password = "Moon15Star18";

// REPLACE WITH THINGSPEAK.COM API KEY
String serverName = "http://api.thingspeak.com/update?api_key=LGUP3GH9R3ODSVNN";
// EXAMPLE:
//String serverName = "http://api.thingspeak.com/update?api_key=7HQJM49R8JAPR";

// THE DEFAULT TIMER IS SET TO 10 SECONDS FOR TESTING PURPOSES
// For a final application, check the API call limits per hour/minute to avoid getting blocked/banned
unsigned long lastTime = 0;
// Set timer to 10 seconds (10000)
unsigned long timerDelay = 10000;

void setup() {
  Serial.begin(115200); 
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP()); 
  Serial.println("Timer set to 10 seconds (timerDelay variable), it will take 10 seconds before publishing the first reading.");
}

void loop() {
  // Send an HTTP GET request
  if ((millis() - lastTime) > timerDelay) {
    // Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;
      String HttpRequest = serverName + "&field1=" + String(analogRead(A0)) + "&field2=" + String(random(100));
      
      // Create the HTTP Get request to ThingSpeak
      Serial.print("HTTP Request: ");
      Serial.println(HttpRequest);
      http.begin(client, HttpRequest);
      //Another option --> http.begin(client, HttpRequest.c_str());
      
      // Send HTTP GET request
      int httpResponseCode = http.GET();      
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}
