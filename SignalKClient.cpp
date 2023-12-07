#include "SignalKClient.h" // Includes the SignalKClient header file for class definition.

SignalKClient::SignalKClient() {} // Default constructor for the SignalKClient class.

void SignalKClient::begin(const char* ssid, const char* password, const char* host, uint16_t port) {
    // Initializes the WiFi connection and sets up the WebSocket connection.
    WiFi.begin(ssid, password); // Connects to the specified WiFi network.
    while (WiFi.status() != WL_CONNECTED) {
        delay(500); // Waits for the WiFi connection to establish.
    }
    webSocket.begin(host, port); // Starts the WebSocket connection with the given host and port.
    webSocket.onEvent([this](WStype_t type, uint8_t* payload, size_t length) {
        this->onWebSocketEvent(type, payload, length); // Sets the event handler for WebSocket events.
    });
}

void SignalKClient::loop() {
    webSocket.loop(); // Keeps the WebSocket connection alive and processes any incoming events.
}

void SignalKClient::subscribe(const String& path, std::function<void(JsonVariant&)> callback) {
    // Subscribes to a specific SignalK data path.
    String message = "{\"context\":\"vessels.self\",\"subscribe\":[{\"path\":\"" + path + "\"}]}"; // Creates the subscription message.
    webSocket.sendTXT(message); // Sends the subscription message over the WebSocket.
    callbacks[path] = callback; // Stores the callback function for the subscribed path.
}

void SignalKClient::unsubscribe(const String& path) {
    // Unsubscribes from a specific SignalK data path.
    String message = "{\"context\":\"vessels.self\",\"unsubscribe\":[{\"path\":\"" + path + "\"}]}"; // Creates the unsubscription message.
    webSocket.sendTXT(message); // Sends the unsubscription message over the WebSocket.
    callbacks.erase(path); // Removes the callback function for the unsubscribed path.
}

void SignalKClient::publish(const String& path, const JsonVariant& value) {
    // Publishes data to the SignalK server.
    DynamicJsonDocument doc(1024); // Creates a JSON document for the message.
    doc["context"] = "vessels.self"; // Sets the context for the message.
    doc["updates"][0]["values"][0]["path"] = path; // Sets the path for the data being published.
    doc["updates"][0]["values"][0]["value"] = value; // Sets the value for the data being published.
    String output;
    serializeJson(doc, output); // Serializes the JSON document to a string.
    webSocket.sendTXT(output); // Sends the publish message over the WebSocket.
}

void SignalKClient::onWebSocketEvent(WStype_t type, uint8_t* payload, size_t length) {
    // Handles different types of WebSocket events.
    switch (type) {
        case WStype_DISCONNECTED:
            // Handles disconnection event.
            Serial.println("Disconnected from server, attempting to reconnect...");
            reconnect(); // Attempts to reconnect.
            break;
        case WStype_CONNECTED:
            // Handles connection event.
            Serial.println("Connected to server");
            // Resubscribes to all previously subscribed topics.
            for (const auto& kv : callbacks) {
                subscribe(kv.first, kv.second);
            }
            break;
        case WStype_TEXT:
            // Handles incoming text message event.
            DynamicJsonDocument doc(2048); // Creates a JSON document for the incoming message.
            DeserializationError error = deserializeJson(doc, payload); // Deserializes the incoming JSON message.
            if (error) {
                // Handles JSON deserialization errors.
                Serial.print("JSON deserialization failed: ");
                Serial.println(error.c_str());
                return;
            }
            // Processes the incoming updates.
            if (doc.containsKey("updates")) {
                for (JsonVariant update : doc["updates"][0]["values"].as<JsonArray>()) {
                    String path = update["path"].as<String>(); // Extracts the path from the update.
                    if (callbacks.find(path) != callbacks.end()) {
                        callbacks[path](update["value"]); // Invokes the callback function for the path with the new value.
                    }
                }
            }
            break;
        case WStype_ERROR:
            // Handles WebSocket error event.
            Serial.println("WebSocket error occurred.");
            break;
    }
}

void SignalKClient::reconnect() {
    // Attempts to reconnect to the WiFi network and reinitialize the WebSocket connection.
    while (WiFi.status() != WL_CONNECTED) {
        delay(5000); // Waits 5 seconds before trying to reconnect.
        Serial.println("Attempting to reconnect to WiFi...");
        WiFi.reconnect(); // Attempts to reconnect to the WiFi network
    }
}
