#ifndef SignalKClient_h
#define SignalKClient_h

#include <Arduino.h>
#include <ArduinoJson.h>
#include <WebSocketsClient.h>
#include <WiFi.h>

class SignalKClient {
public:
    SignalKClient();
    void begin(const char* ssid, const char* password, const char* host, uint16_t port);
    void loop();
    void subscribe(const String& path, std::function<void(JsonVariant&)> callback);
    void unsubscribe(const String& path);
    void publish(const String& path, const JsonVariant& value);

private:
    WebSocketsClient webSocket;
    std::map<String, std::function<void(JsonVariant&)>> callbacks;

    void onWebSocketEvent(WStype_t type, uint8_t* payload, size_t length);
};

#endif
