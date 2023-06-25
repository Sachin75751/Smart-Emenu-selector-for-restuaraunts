#include <ESP8266WiFi.h>
#include <espnow.h>

uint8_t receiverMacAddress[] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};  // Receiver's MAC address

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_add_peer(receiverMacAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
}

void loop() {
  sendHiMessage();
  delay(5000);
}

void sendHiMessage() {
  uint8_t message[] = "Hi";
  esp_now_send(receiverMacAddress, message, sizeof(message));
  Serial.println("Sent 'Hi' message");
}
