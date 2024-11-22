
#include <WiFi.h>
#include <WebServer.h>

// Replace with your network credentials (if in Station mode)
const char* ssid = "ESP32_AP";
const char* password = "placeholder";

// Pins
const int mosfetPin = 5; // GPIO pin to control MOSFET
const int voltagePin = 34; // Analog pin for voltage monitoring

// Web server running on port 80
WebServer server(80);

// Function to read voltage
float readVoltage() {
  int rawValue = analogRead(voltagePin);
  float voltage = (rawValue / 4095.0) * 3.3; // Convert ADC value to voltage (3.3V reference)
  voltage = voltage * (100 + 10) / 10; // Adjust for voltage divider (100k + 10k)
  return voltage;
}

// Power ON handler
void handlePowerOn() {
  digitalWrite(mosfetPin, HIGH);
  server.send(200, "text/plain", "Power ON");
}

// Power OFF handler
void handlePowerOff() {
  digitalWrite(mosfetPin, LOW);
  server.send(200, "text/plain", "Power OFF");
}

// Voltage status handler
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
  server.on("/power_on", handlePowerOn);
  server.on("/power_off", handlePowerOff);
  server.on("/status", handleStatus);
  server.begin();
  Serial.println("Web server started");
}

void loop() {
  server.handleClient();
}
