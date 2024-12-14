
# GroundControl - ESP32 Power Control and Monitoring System

This project uses an Adafruit ESP32 Feather V2 to remotely control and monitor the power to a device like a RunCam via Wi-Fi. The system is designed to operate in **Access Point (AP) mode**, providing a mobile-friendly web interface for control and monitoring.

## Features
- **Remote Power Control**: Use a MOSFET to switch power to the connected device on or off.
- **Real-Time Monitoring**: Read and display the voltage at the output using a voltage divider and the ESP32's ADC pin.
- **Responsive Web Interface**: Simple, mobile-friendly control panel accessible via a web browser.

## Components
- **Adafruit ESP32 Feather V2**: Handles Wi-Fi connectivity and control logic.
- **MOSFET (e.g., IRLZ44N)**: Used for switching power to the device.
- **Voltage Divider**: Scales the monitored voltage to a safe level for the ESP32 ADC.

## Web Interface
The ESP32 hosts a web server accessible at `http://192.168.4.1` after connecting to its Wi-Fi network (`groundcontrol`). The following routes are available:

1. **`/power_on`**: Turns the connected device ON.
2. **`/power_off`**: Turns the connected device OFF.
3. **`/status`**: Reads and displays the monitored voltage.

The root (`/`) serves a mobile-friendly control panel with buttons to access the above routes.

## Circuit Summary
- **Power Supply**:
  - Use a buck converter to step down a 7.4V or 11.1V battery to 5V.
  - Connect the buck converter output to the Feather’s USB pin for power.
- **MOSFET**:
  - Gate: GPIO 5 (with an optional 220Ω resistor).
  - Drain: Device negative terminal.
  - Source: Ground.
- **Voltage Divider**:
  - Resistor 1: 100kΩ (connect to the device positive terminal).
  - Resistor 2: 10kΩ (connect to ground).
  - ADC Output: Connect the junction of the resistors to GPIO 32 (A4).

## How to Use
1. **Upload the Code**:
   - Use the Arduino IDE to upload the provided sketch to the ESP32.
2. **Connect to the ESP32**:
   - Wi-Fi SSID: `groundcontrol`
   - Password: `password123`
3. **Access the Web Interface**:
   - Open a browser and navigate to `http://192.168.4.1`.
   - Use the control panel to power the device ON/OFF or check the voltage.

## Future Improvements
- Add authentication for web interface security.
- Expand the control panel to support multiple devices.
