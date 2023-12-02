#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Declaration for an SSD1306 display connected to I2C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

#include <WiFi.h>
#include <PubSubClient.h>
#include <LiquidCrystal.h>

const char* ssid = "XXXXXX";
const char* password = "XXXXXX"; 
const char* mqttServer = "MQTT_BROKER_IP";
const int mqttPort = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

// Define light control pins
const int lightPins[] = {5, 6, 7, 8, 9, 10, 11, 12};
const int numLights = 8;

// Define pin configuration for LCD
const int rs = 22, en = 23, d4 = 24, d5 = 25, d6 = 26, d7 = 27;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // Initialize I2C display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println("SSD1306 allocation failed");
    for(;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("Initializing...");
  display.display();

  // Wi-Fi Connection Check
  display.println("Connecting to Wi-Fi...");
  display.display();
  // Add Wi-Fi connection code here

  // SignalK Server Connection Check
  display.println("Connecting to SignalK Server...");
  display.display();
  // Add SignalK connection code here

  Serial.begin(115200);
  
  // Initialize light control pins
  for (int i = 0; i < numLights; i++) {
    pinMode(lightPins[i], OUTPUT);
    analogWrite(lightPins[i], 0); // Turn off lights initially
  }

  setupLCD();
  // Connect to WiFi
  setupWiFi();

  // Setup MQTT client
  client.setServer(mqttServer, mqttPort);
  client.setCallback(mqttCallback);
}

void loop() {
  // Add your main code here
}
