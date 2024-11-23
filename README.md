# Remote Power Control System with ESP32

This project enables remote power control and monitoring for devices using an ESP32 microcontroller. Specificaly, it was designed to remotely power on a camera system embedded in the avionics bay of a high power model rocket. The system is designed to operate in **Access Point (AP) mode**, providing a direct Wi-Fi connection for a smartphone or other device to control the system through a web interface.

## Features
- **Remote Power Control**: Toggle power to an external device using a MOSFET controlled by the ESP32.
- **Real-Time Voltage Monitoring**: Read and display the output voltage using an ADC pin.
- **Web Interface**: Simple HTML-based interface to send commands and view status.

## Web Interface Routes
The ESP32 hosts a lightweight web server accessible through the IP `192.168.4.1`. The following routes are available:

1. **`/power_on`**  
   - Description: Turns the connected device ON by setting the MOSFET gate HIGH.
   - Response: Plain text confirmation (`"Power ON"`).

2. **`/power_off`**  
   - Description: Turns the connected device OFF by setting the MOSFET gate LOW.
   - Response: Plain text confirmation (`"Power OFF"`).

3. **`/status`**  
   - Description: Reads the current voltage from the connected device and returns the value.
   - Response: Plain text with the voltage reading (e.g., `"Voltage: 5.12V"`).

## Setup Instructions
1. **Power the ESP32**: Connect a 2S LiPo battery to the Adafruit ESP32 Feather V2’s JST connector.
2. **Connect to the Wi-Fi Network**:
   - Network Name: `ESP32_AP`
   - Password: `password123` (default in the code, can be changed).
3. **Access the Web Interface**:
   - Open a web browser on your smartphone or laptop.
   - Navigate to `http://192.168.4.1`.

## Code Overview
- The ESP32 creates a Wi-Fi Access Point using `WiFi.softAP(ssid, password)`.
- A web server listens for requests on the defined routes.
- GPIO 5 is configured to control the MOSFET for switching power.
- An ADC pin (default: GPIO 32) reads voltage via a voltage divider.

## Customization
- **Wi-Fi Credentials**: Update the `ssid` and `password` variables in the code.
- **GPIO Pins**: Modify the `mosfetPin` or `voltagePin` variables as needed.
- **Voltage Divider**: Ensure the resistor values match your voltage input to scale correctly.

---
