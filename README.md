# Arduino-SignalK Integration

## Description
This Arduino project is designed to integrate with a SignalK network, primarily for marine or caravan applications. It includes functionalities for Wi-Fi connectivity, communication with a SignalK server, and control of various systems (like lighting). The project features a 128x64 pixel I2C display for real-time status updates and system checks.

## Hardware Requirements
- Arduino compatible board (e.g., Arduino Uno, Mega, or ESP8266 module)
- 128x64 pixel I2C OLED display
- Necessary cables and connectors for the Arduino board and peripherals

## Software Dependencies
- Arduino IDE for coding and uploading the sketch to the Arduino board
- Adafruit_SSD1306 library for the I2C display
- Adafruit_GFX library for graphics functions
- Additional libraries for Wi-Fi and SignalK communication

## Setup and Configuration
1. Install the Arduino IDE on your computer.
2. Install the required libraries (Adafruit_SSD1306, Adafruit_GFX, and others) through the Arduino IDE's Library Manager.
3. Connect the I2C display to your Arduino board according to the display’s pin configuration.
4. Configure your Arduino board with the provided sketch (`Stiletto_giga_modified.ino`).
5. Update the Wi-Fi credentials and SignalK server details in the sketch to match your setup.

## Usage
- Power on the Arduino system.
- The I2C display will show the status of system checks during startup, including Wi-Fi and SignalK server connectivity.
- The system will control and monitor connected peripherals based on the sketch's functionalities.

## Notes
- This project is a starting point and can be expanded to include additional features and functionalities.
- Ensure to follow proper electronic safety protocols while setting up the hardware.

## Support and Contribution
For support, suggestions, or contributions to this project, please reach out through the project's repository or contact the author directly.
