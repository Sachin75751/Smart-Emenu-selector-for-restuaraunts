#include <ESP8266WiFi.h>
#include <espnow.h>

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
}

void loop() {
  if (esp_now_recv_cb() > 0) {
    uint8_t message[32];
    int messageSize = sizeof(message);
    if (esp_now_read(message, &messageSize) == ESP_OK) {
      Serial.print("Received: ");
      Serial.println((char*)message);
    }
  }
}
