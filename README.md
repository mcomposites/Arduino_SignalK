# Arduino SignalK Library

## Description
SignalKClient is an Arduino library designed for easy interaction with SignalK servers. It enables subscribing to SignalK data paths, handling incoming data, and publishing data back to the server.

## Features
- Subscribe to SignalK data paths
- Publish data to SignalK server
- Callbacks for handling incoming data
- Robust error handling
- Supports multiple data contexts

## Installation
Download this library and import it into your Arduino IDE.

## Usage
### Basic Setup
Include the SignalKClient library in your Arduino project and use the following setup:

#include "SignalKClient.h"
SignalKClient signalk;
void setup() {
    Serial.begin(115200);
    signalk.begin("YourSSID", "YourPassword", "signalk_server_address", 3000);
    signalk.subscribe("your.path.here", [](JsonVariant& value) {
        // Handle the value
    });
}
void loop() {
    signalk.loop();
}

### Publishing Data
To publish data to the SignalK server, use:

signalk.publish("your.path.here", value);

## Contributing
Contributions to this project are welcome. Please send pull requests or open issues to suggest improvements.

## License
This project is licensed under the [MIT License](LICENSE).

## Acknowledgments
Special thanks to the Arduino and SignalK communities for their support and contributions to this project.
