/**
 * BasicHTTPClient.ino
 *
 *  Created on: 24.05.2015
 *
 */

#include <Arduino.h>

#include <WiFi.h>
#include <WiFiMulti.h>

#include <HTTPClient.h>

#define USE_SERIAL Serial

// #define WIFI_SSID "WhiteSky-InspireAtlanta"
// #define WIFI_PASSWORD "d2vcf354"
#define WIFI_SSID "Aditya iPhone 14 Pro"
#define WIFI_PASSWORD "25458565"

WiFiMulti wifiMulti;

#define WIFI_R 22
#define WIFI_G 14
#define WIFI_B 32
#define WIFI_RED_CHANNEL 0
#define WIFI_GREEN_CHANNEL 1
#define WIFI_BLUE_CHANNEL 2

#define HTTP_R 15
#define HTTP_G 33
#define HTTP_B 27
#define HTTP_RED_CHANNEL 3
#define HTTP_GREEN_CHANNEL 4
#define HTTP_BLUE_CHANNEL 5

int wifiStatus() {
    return wifiMulti.run() == WL_CONNECTED;
}

int checkWifi() {
    if (!wifiStatus()) {
        USE_SERIAL.println("WiFi not connected");
        ledcWrite(WIFI_RED_CHANNEL, 100);
        ledcWrite(WIFI_GREEN_CHANNEL, 0);
        ledcWrite(WIFI_BLUE_CHANNEL, 0);
        delay(1000);
        ledcWrite(WIFI_RED_CHANNEL, 0);
        delay(1000);
        return 0;
    }
    ledcWrite(WIFI_RED_CHANNEL, 0);
    ledcWrite(WIFI_GREEN_CHANNEL, 25);
    ledcWrite(WIFI_BLUE_CHANNEL, 0);
    return 1;
}

void ledSetup() {
    // setup PWM for wifi status LED
    ledcSetup(WIFI_RED_CHANNEL, 5000, 8);
    ledcAttachPin(WIFI_R, WIFI_RED_CHANNEL);
    ledcSetup(WIFI_GREEN_CHANNEL, 5000, 8);
    ledcAttachPin(WIFI_G, WIFI_GREEN_CHANNEL);
    ledcSetup(WIFI_BLUE_CHANNEL, 5000, 8);
    ledcAttachPin(WIFI_B, WIFI_BLUE_CHANNEL);

    ledcWrite(WIFI_RED_CHANNEL, 0);
    ledcWrite(WIFI_GREEN_CHANNEL, 0);
    ledcWrite(WIFI_BLUE_CHANNEL, 50);

    // setup PWM for HTTP status LED
    ledcSetup(HTTP_RED_CHANNEL, 5000, 8);
    ledcAttachPin(HTTP_R, HTTP_RED_CHANNEL);
    ledcSetup(HTTP_GREEN_CHANNEL, 5000, 8);
    ledcAttachPin(HTTP_G, HTTP_GREEN_CHANNEL);
    ledcSetup(HTTP_BLUE_CHANNEL, 5000, 8);
    ledcAttachPin(HTTP_B, HTTP_BLUE_CHANNEL);

    ledcWrite(HTTP_RED_CHANNEL, 0);
    ledcWrite(HTTP_GREEN_CHANNEL, 0);
    ledcWrite(HTTP_BLUE_CHANNEL, 50);
}
void wifiConnect() {
    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }
    USE_SERIAL.printf("[SETUP] Connecting to %s\n", WIFI_SSID);
    wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);
}

String fetchData(String url) {
    // Amber HTTP LED
    ledcWrite(HTTP_RED_CHANNEL, 50);
    ledcWrite(HTTP_GREEN_CHANNEL, 25);
    ledcWrite(HTTP_BLUE_CHANNEL, 0);

    HTTPClient http;

    USE_SERIAL.print("[HTTP] begin...\n");
    // configure traged server and url
    // http.begin("https://api.weather.gov/gridpoints/FFC/50,88/forecast"); //HTTP
    http.begin(url); //HTTP

    USE_SERIAL.print("[HTTP] GET...\n");
    // start connection and send HTTP header
    int httpCode = http.GET();

    // httpCode will be negative on error
    if(httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if(httpCode == HTTP_CODE_OK) {
            String payload = http.getString();
            Serial.println(payload);
            ledcWrite(HTTP_RED_CHANNEL, 0);
            ledcWrite(HTTP_GREEN_CHANNEL, 50);
            ledcWrite(HTTP_BLUE_CHANNEL, 0);
            return payload;
        }
    } else {
        USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        ledcWrite(HTTP_RED_CHANNEL, 100);
        ledcWrite(HTTP_GREEN_CHANNEL, 50);
        ledcWrite(HTTP_BLUE_CHANNEL, 0);
        return "";
    }
    http.end();
}