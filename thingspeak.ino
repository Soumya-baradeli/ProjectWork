// Import nessesary libraries
#include <WiFi.h>
#include <HTTPClient.h>
 
#define ADC_VREF_mV    3300.0 // in millivolt
#define ADC_RESOLUTION 4096.0
#define PIN_LM35       35 // ESP32 pin GIOP36 (ADC0) connected to LM35
 
 
// Set our wifi name and password
const char* ssid = "OPPO A31";
const char* password = "Bangari17";
 
// Your thingspeak channel url with api_key query
String serverName = "https://api.thingspeak.com/update?api_key=LQ35EMID4DD1O7DK";
String apikey="LQ35EMID4DD1O7DK";
 
// Assign some variables to allow us read and send data every minute
unsigned long lastTime = 0;
unsigned long timerDelay = 15000;
 
 
void setup() {
  Serial.begin(115200); // Opens up the serial port with a baudrate of 9600 bits per second
 
 
  WiFi.begin(ssid, password); // Attempt to connect to wifi with our password
  Serial.println("Connecting"); // Print our status to the serial monitor
  // Wait for wifi to connect
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}
 
 
void loop() {
 int adcVal = analogRead(PIN_LM35);
   float milliVolt = adcVal * (ADC_VREF_mV / ADC_RESOLUTION);
     float tempC = milliVolt / 10;
       float tempF = tempC * 9 / 5 + 32;
    Serial.print("Temperature: ");
  Serial.print(tempC);   // print the temperature in °C
  Serial.print("°C");
  Serial.print("  ~  "); // separator between °C and °F
  Serial.print(tempF);   // print the temperature in °F
  Serial.println("°F");
 
   
  if ((millis() - lastTime) > timerDelay) { // Check if its been a minute
    if(WiFi.status()== WL_CONNECTED){ // Check to make sure wifi is still connected
      sendData(tempC, tempF); // Call the sendData function defined below
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}
 
 
void sendData(float temp, float pres){
  HTTPClient http; // Initialize our HTTP client
 
 
  String url = serverName + "&field1=" + temp + "&field2=" + pres; // Define our entire url
       
  http.begin(url.c_str()); // Initialize our HTTP request
       
  int httpResponseCode = http.GET(); // Send HTTP request
       
  if (httpResponseCode > 0){ // Check for good HTTP status code
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
  }else{
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  http.end();
}
