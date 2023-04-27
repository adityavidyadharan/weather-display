#include <ArduinoJson.h>
#include <TimeLib.h>

time_t lastTime;

time_t lastSync;

struct TextDimensions {
  int16_t  x1, y1;
  uint16_t w, h;
};

void setup() {
  Serial.begin(115200);
  ledSetup();
  wifiConnect();
  while (!checkWifi());

  setTime();
  lastTime = now();
  lastSync = now();

  rotarySetup();
  dhtSetup();
  graphicsSetup();
}

void loop() {
  rotary_loop();
  if (minute() != minute(lastTime)) {
    lastTime = now();
    updateHeader();
  }

  if (lastSync < now() - 10800 && checkWifi()) {
    updateBody();
    lastSync = now();
  }
  checkWifi();
}
