#include <WiFi.h>
#include <WebServer.h>
#include <LiquidCrystal.h>

const char* ssid = "OPPO A31";
const char* password = "Bangari17";

IPAddress serverIP(192, 168, 43, 77);  // IP address of the ESP32 server
WebServer server(80);

// LCD Pin Mapping
const int LCD_RS = 12;
const int LCD_EN = 11;
const int LCD_D4 = 5;
const int LCD_D5 = 4;
const int LCD_D6 = 3;
const int LCD_D7 = 2;
const int LCD_COLS = 16;  // Number of columns in the LCD
const int LCD_ROWS = 2;   // Number of rows in the LCD

LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

void setup() {
  Serial.begin(115200);
  delay(1000);

  lcd.begin(LCD_COLS, LCD_ROWS);
  lcd.clear();

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
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Received:");
    lcd.setCursor(0, 1);
    lcd.print(message);
    server.send(200, "text/plain", "Message received");
    Serial.print("Received: ");
    Serial.println(message);
  });

  server.begin();
}

void loop() {
  server.handleClient();
}v
