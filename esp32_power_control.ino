// Full ESP32 Sketch with Updates for Power Control and Monitoring
#include <WiFi.h>
#include <WebServer.h>

// Replace with your network credentials (if in Station mode)
const char* ssid = "groundcontrol";
const char* password = "password123";

// Pins
const int mosfetPin = 5; // GPIO pin to control MOSFET
const int voltagePin = 32; // Analog pin for voltage monitoring (A4 on Feather)

// Web server running on port 80
WebServer server(80);

// Function to read voltage
float readVoltage() {
  int rawValue = analogRead(voltagePin);
  float voltage = (rawValue / 4095.0) * 3.3; // Convert ADC value to voltage (3.3V reference)
  voltage = voltage * (100 + 10) / 10; // Adjust for voltage divider (100k + 10k)
  return voltage;
}

// Handlers for Web Server
void handleRoot() {
  String html = "<html><head><title>Ground Control</title>";
  html += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
  html += "<style>";
  html += "body { font-family: Arial, sans-serif; text-align: center; padding: 20px; margin: 0; }";
  html += "h1 { color: #333; font-size: 24px; margin-bottom: 20px; }";
  html += "a { display: block; margin: 10px auto; padding: 15px 25px; font-size: 18px; "
         "text-decoration: none; color: white; background-color: #007BFF; border-radius: 5px; "
         "max-width: 300px; }";
  html += "a:hover { background-color: #0056b3; }";
  html += "</style>";
  html += "</head><body>";
  html += "<h1>Ground Control</h1>";
  html += "<a href=\"/power_on\">Turn Power ON</a>";
  html += "<a href=\"/power_off\">Turn Power OFF</a>";
  html += "<a href=\"/status\">Check Voltage Status</a>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handlePowerOn() {
  digitalWrite(mosfetPin, HIGH);
  server.send(200, "text/plain", "Power ON");
}

void handlePowerOff() {
  digitalWrite(mosfetPin, LOW);
  server.send(200, "text/plain", "Power OFF");
}

void handleStatus() {
  float voltage = readVoltage();
  String response = "Voltage: " + String(voltage) + "V";
  server.send(200, "text/plain", response);
}

void setup() {
  // Setup Serial Monitor
  Serial.begin(115200);
  
  // Configure GPIO
  pinMode(mosfetPin, OUTPUT);
  digitalWrite(mosfetPin, LOW); // Ensure device is off at startup

  // Setup Wi-Fi
  WiFi.softAP(ssid, password);
  Serial.println("Wi-Fi Access Point started");

  // Define server routes
  server.on("/", handleRoot);
  server.on("/power_on", handlePowerOn);
  server.on("/power_off", handlePowerOff);
  server.on("/status", handleStatus);
  server.begin();
  Serial.println("Web server started");
}

void loop() {
  server.handleClient();
}
