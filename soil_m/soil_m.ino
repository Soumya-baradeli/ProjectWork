#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "OPPO A31";
const char* password = "Bangari17";

IPAddress serverIP(192, 168, 43, 77);  // IP address of the ESP32 server
WebServer server(80);

void setup() {
  Serial.begin(115200);
  delay(1000);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("WiFi connected");

  Serial.print("ESP32 IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, []() {
    String message = "Hello from ESP32!";
    server.send(200, "text/plain", message);
    Serial.println("Sending data to Arduino: " + message);
  });

  server.begin();
}

void loop() {
  server.handleClient();
}