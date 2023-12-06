#include "SignalKClient.h"

SignalKClient::SignalKClient() {}

void SignalKClient::begin(const char* ssid, const char* password, const char* host, uint16_t port) {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }
    webSocket.begin(host, port);
    webSocket.onEvent([this](WStype_t type, uint8_t* payload, size_t length) {
        this->onWebSocketEvent(type, payload, length);
    });
}

void SignalKClient::loop() {
    webSocket.loop();
}

void SignalKClient::subscribe(const String& path, std::function<void(JsonVariant&)> callback) {
    String message = "{\"context\":\"vessels.self\",\"subscribe\":[{\"path\":\"" + path + "\"}]}";
    webSocket.sendTXT(message);
    callbacks[path] = callback;
}

void SignalKClient::unsubscribe(const String& path) {
    String message = "{\"context\":\"vessels.self\",\"unsubscribe\":[{\"path\":\"" + path + "\"}]}";
    webSocket.sendTXT(message);
    callbacks.erase(path);
}

void SignalKClient::publish(const String& path, const JsonVariant& value) {
    DynamicJsonDocument doc(1024);
    doc["context"] = "vessels.self";
    doc["updates"][0]["values"][0]["path"] = path;
    doc["updates"][0]["values"][0]["value"] = value;
    String output;
    serializeJson(doc, output);
    webSocket.sendTXT(output);
}

void SignalKClient::onWebSocketEvent(WStype_t type, uint8_t* payload, size_t length) {
    if (type == WStype_TEXT) {
        DynamicJsonDocument doc(2048);
        deserializeJson(doc, payload);
        if (doc.containsKey("updates")) {
            for (JsonVariant update : doc["updates"][0]["values"].as<JsonArray>()) {
                String path = update["path"].as<String>();
                if (callbacks.find(path) != callbacks.end()) {
                    callbacks[path](update["value"]);
                }
            }
        }
    }
}
