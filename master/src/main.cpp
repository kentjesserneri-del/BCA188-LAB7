#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEClient.h>

#define SERVICE_UUID        "a2653b19-aa84-474a-95d3-93e76e4f4301"
#define CHARACTERISTIC_UUID "f0e65ff0-90b3-416b-ac35-be87a7805453"

const uint8_t BUTTON_PIN = 23;

// Real MAC addresses of the two slaves
const char* SLAVE1_MAC = "A4:F0:0F:76:38:46";  // ESP32 classic
const char* SLAVE2_MAC = "8C:BF:EA:18:0C:BD";  // ESP32-S3

bool lastButtonState = HIGH;

BLEClient* connectToSlave(const char* macStr, const char* label) {
  BLEAddress addr(macStr);
  BLEClient* client = BLEDevice::createClient();
  Serial.printf("Connecting to %s (%s)...\n", label, macStr);
  if (!client->connect(addr)) {
    Serial.printf("Failed to connect to %s\n", label);
    return nullptr;
  }
  Serial.printf("Connected to %s\n", label);
  BLERemoteService* svc = client->getService(SERVICE_UUID);
  if (!svc) {
    Serial.printf("Service not found on %s\n", label);
    return nullptr;
  }
  Serial.printf("%s ready\n", label);
  return client;
}

void sendCommand(BLEClient* client, const char* cmd) {
  if (!client || !client->isConnected()) return;
  BLERemoteService* svc = client->getService(SERVICE_UUID);
  if (!svc) return;
  BLERemoteCharacteristic* ch = svc->getCharacteristic(CHARACTERISTIC_UUID);
  if (!ch) return;
  ch->writeValue((uint8_t*)cmd, strlen(cmd), true);
}

void setup() {
  Serial.begin(115200);
  delay(500);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  Serial.println("Master starting BLE...");
  BLEDevice::init("ESP32-Master");
  Serial.println("Master ready. Waiting for button...");
}

void loop() {
  static BLEClient* slave1 = nullptr;
  static BLEClient* slave2 = nullptr;

  if (!slave1) slave1 = connectToSlave(SLAVE1_MAC, "Slave1");
  if (!slave2) slave2 = connectToSlave(SLAVE2_MAC, "Slave2");

  const bool pressed = (digitalRead(BUTTON_PIN) == LOW);

  if (pressed && lastButtonState == HIGH) {
    Serial.println("Button PRESSED — sending ON");
    sendCommand(slave1, "ON");
    sendCommand(slave2, "ON");
  } else if (!pressed && lastButtonState == LOW) {
    Serial.println("Button RELEASED — sending OFF");
    sendCommand(slave1, "OFF");
    sendCommand(slave2, "OFF");
  }

  lastButtonState = pressed;
  delay(50);
}