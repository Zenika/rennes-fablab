// Experiment wifi client of ESP32
// link pin 4 to a metalic surface
// then touch metalic surface with your finger to send request

#include <WiFi.h>
#include <HTTPClient.h>

#define SPOON_TOUCH 4
#define SSID "zenika"
#define PWD "zenika"

int capacitiveValue = 100; // global variable avoid reallocation
int threshold = 20; // to be adjusted
int lastCall = 0;
String serverUrl = "http://192.168.0.88:3000/ping";

void setup() {
  Serial.begin(115200);
  Serial.print("Connecting to ");
  Serial.println(SSID);
  WiFi.begin(SSID, PWD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.print("Connected. IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  capacitiveValue = touchRead(SPOON_TOUCH);
  if(capacitiveValue < threshold && millis() - lastCall > 1000) {
    lastCall = millis();
    HTTPClient http;
    String serverPath = serverUrl + "?name=Zenika";
    http.begin(serverPath);
    // Send HTTP GET request
    int httpResponseCode = http.GET();
      
    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      String payload = http.getString();
      Serial.println(payload);
    } else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
  }
}
