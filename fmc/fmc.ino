#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

const char* ssid = "OPPO A31";
const char* password = "Bangari17";

const int ledPin1 = 32; // Pin connected to the first LED
const int ledPin2 = 25; // Pin connected to the second LED
const int ledPin3 = 26; // Pin connected to the third LED
const int dotDuration = 200; // Duration of a dot in milliseconds

WebServer server(80);
String message = "Bangari";

// Morse code lookup table
const char* morseTable[] = {
  ".-",   // A
  "-...", // B
  "-.-.", // C
  "-..",  // D
  ".",    // E
  "..-.", // F
  "--.",  // G
  "....", // H
  "..",   // I
  ".---", // J
  "-.-",  // K
  ".-..", // L
  "--",   // M
  "-.",   // N
  "---",  // O
  ".--.", // P
  "--.-", // Q
  ".-.",  // R
  "...",  // S
  "-",    // T
  "..-",  // U
  "...-", // V
  ".--",  // W
  "-..-", // X
  "-.--", // Y
  "--.."  // Z
};

void handleRoot() {
  String html = "<form method='post' action='/send'>"
                "<input type='text' name='message'>"
                "<input type='submit' value='Send Message'>"
                "</form>";
  server.send(200, "text/html", html);
}

void handleSend() {
  String receivedMessage = server.arg("message");
  if (receivedMessage != "") {
    message = receivedMessage;
    flashMorseCode(message);
    server.send(200, "text/plain", "Message sent as Morse code.");
  } else {
    server.send(400, "text/plain", "No message received.");
  }
}

void setup() {
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin3, LOW);

  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/send", handleSend);
  server.begin();
  Serial.println("Web server started");
}

void loop() {
  server.handleClient();
}

void flashMorseCode(const String& text) {
  for (int i = 0; i < text.length(); i++) {
    char c = toupper(text.charAt(i));
    if (c >= 'A' && c <= 'Z') {
      int index = c - 'A';
      const char* morseCode = morseTable[index];
      for (int j = 0; j < strlen(morseCode); j++) {
        if (morseCode[j] == '.') {
          flashDot();
        } else if (morseCode[j] == '-') {
          flashDash();
        }
        delay(dotDuration); // Pause between elements
      }
    } else if (c == ' ') {
      delay(dotDuration * 3); // Pause between words
    }
    delay(dotDuration * 3); // Pause between characters
  }
}

void flashDot() {
  digitalWrite(ledPin1, HIGH);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin3, LOW);
  delay(dotDuration);
  digitalWrite(ledPin1, LOW);
}

void flashDash() {
  digitalWrite(ledPin1, HIGH);
  digitalWrite(ledPin2, HIGH);
  digitalWrite(ledPin3, LOW);
  delay(dotDuration * 3);
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
}
