#include <WiFi.h>
#include <WiFiManager.h>

const char* AP_NAME = "BCA188-ESP32-2022-3303"; // The setup network the ESP32 creates.

const int BOOT_PIN = 0;               // BOOT button on most ESP32 dev boards
const unsigned long HOLD_MS = 3000;   // Hold for 3 seconds to reset saved Wi-Fi settings

WiFiManager wm;
unsigned long pressStart = 0;

void setup() {
  Serial.begin(115200);
  pinMode(BOOT_PIN, INPUT_PULLUP);

  wm.setConfigPortalTimeout(180); // Seconds. Restart if nobody completes setup.

  if (!wm.autoConnect(AP_NAME)) {
    Serial.println("Connection failed");
    delay(3000);
    ESP.restart();
  }

  Serial.println("Connected!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Hold BOOT for 3 seconds while running to erase saved Wi-Fi and restart.
  if (digitalRead(BOOT_PIN) == LOW) {
    if (pressStart == 0) pressStart = millis();
    if (millis() - pressStart >= HOLD_MS) {
      Serial.println("BOOT held 3s: resetting Wi-Fi settings...");
      wm.resetSettings();
      delay(500);
      ESP.restart();
    }
  } else {
    pressStart = 0;
  }
}
