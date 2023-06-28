#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "OPPO A31";
const char* password = "Bangari17";

IPAddress serverIP(192, 168, 43, 77);  // IP address of the ESP32 server
WebServer server(80);

void setup() {
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  Serial.println("WiFi connected");
  Serial.print("ESP32 IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, []() {
    String html = "<html><body><form action='/send' method='POST'>";
    html += "<input type='text' name='message'>";
    html += "<input type='submit' value='Send'></form></body></html>";
    server.send(200, "text/html", html);
  });

  server.on("/send", HTTP_POST, []() {
    String message = server.arg("message");
    sendMessageToArduino(message);
    server.send(200, "text/plain", "Message sent to Arduino");
    Serial.print("Message sent to Arduino: ");
    Serial.println(message);
  });

  server.begin();
}

void loop() {
  server.handleClient();
}

void sendMessageToArduino(String message) {
  // Implement your code to send the message to Arduino here
  // For example, you can use Serial communication to send the message
  Serial.println(message);
}
