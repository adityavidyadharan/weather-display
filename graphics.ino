#include <SPI.h>
#include "Adafruit_GFX.h"
#include "Adafruit_HX8357.h"
#include "icons/icons.h"

#include <ArduinoJson.h>
#include <TimeLib.h>

// These are 'flexible' lines that can be changed
#define TFT_CS 16
#define TFT_DC 17
#define TFT_RST 21 // RST can be set to -1 if you tie it to Arduino's reset

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_HX8357 tft = Adafruit_HX8357(TFT_CS, TFT_DC, TFT_RST);

void graphicsSetup() {
  Serial.println("HX8357D Startup"); 
  tft.begin();
  tft.setRotation(2);
  tft.fillScreen(0xEF5A);

  
  updateHeader();
  updateBody();
}

void drawHeader() {
  tft.setCursor(15, 15);
  tft.setTextColor(HX8357_BLACK);
  tft.setTextSize(3);
  int time_height = getTextDimensions(getTime(), 0, 0).h;
  tft.println(getTime());

  tft.setTextSize(2);
  tft.setCursor(15, 15 + time_height);
  tft.println(getDate());
  int date_height = getTextDimensions(getDate(), 0, 0).h;
}

void drawBody() {
  // JsonArray data = parseOpenWeather();
  String payload = fetchData("http://api.openweathermap.org/data/2.5/forecast/daily?lat=33.77514&lon=-84.39539&appid=APIID&cnt=9&units=imperial");
  JsonArray data = parseOpenWeather(payload);

  drawSection(data[0], 70);
  drawSection(data[1], 170);
  drawSection(data[2], 270);
  drawSection(data[3], 370);
}

TextDimensions getTextDimensions(String text, int x, int y) {
  TextDimensions td;
  tft.getTextBounds(text, x, y, &td.x1, &td.y1, &td.w, &td.h);
  return td;
}

void updateIndoorTemp(float temp) {
  // draw new temp
  tft.setCursor(320 - 15 - getTextDimensions((String(temp, 0)) + "F", 0, 0).w, 15);
  tft.println((String(temp, 0)) + "F");
}

void updateHeader() {
  float temp = getTemp();
  clearSection(0, 70);
  drawHeader();
  updateIndoorTemp(temp);
}

void updateBody() {
  clearSection(70, 400);
  drawBody();
}

void clearSection(int y, int h) {
  tft.fillRect(0, y, 320, y + h, 0xEF5A);
}

void drawSection(JsonObject info, int y) {
  tft.fillRoundRect(15, y, 290, 85, 10, HX8357_WHITE);
  tft.drawRoundRect(15, y, 290, 85, 10, HX8357_BLACK);

  tft.setTextSize(2);
  
  TextDimensions day_dimensions  = getTextDimensions(info["day"].as<String>(), 25, y);

  tft.setCursor(15 + (290 - day_dimensions.w) / 2, y + 5);
  tft.print(info["day"].as<String>());

  tft.setCursor(30, y + day_dimensions.h + 10 + 35);
  tft.print(((String) info["temperature"]["max"].as<int>()) + "F");
  tft.drawRGBBitmap(tft.getCursorX(), tft.getCursorY(), arrow_up, 15, 15);

  tft.setCursor(tft.getCursorX() + 15, tft.getCursorY());
  tft.print(((String) info["temperature"]["min"].as<int>()) + "F");
  tft.drawRGBBitmap(tft.getCursorX(), tft.getCursorY(), arrow_down, 15, 15);

  tft.setCursor(tft.getCursorX() + 15, tft.getCursorY());
  tft.print(((String) info["temperature"]["day"].as<int>()) + "F");
  tft.drawRGBBitmap(tft.getCursorX(), tft.getCursorY(), sunrise, 15, 15);

  tft.setCursor(tft.getCursorX() + 20, tft.getCursorY());
  int precipitation = info["precipitation"].as<double>() * 100;
  tft.print(((String) precipitation) + "%");
  tft.drawRGBBitmap(tft.getCursorX(), tft.getCursorY(), droplet, 15, 15);

  String forecast = info["forecast"].as<String>();
  int forecast_width = getTextDimensions(forecast, 0, 0).w;
  tft.setCursor(30, y + 30);
  tft.println(forecast);

  tft.drawRGBBitmap(15 + 290 - 60, y + 30, iconLookup(info["icon"].as<String>()), 45, 45);
}

const uint16_t* iconLookup (String name) {
  if (name == "01d") {
    return i01d;
  } else if (name == "02d") {
    return i02d;
  } else if (name == "03d") {
    return i03d;
  } else if (name == "04d") {
    return i04d;
  } else if (name == "09d") {
    return i09d;
  } else if (name == "10d") {
    return i10d;
  } else if (name == "11d") {
    return i11d;
  } else if (name == "13d") {
    return i13d;
  } else if (name == "50d") {
    return i50d;
  }
}
