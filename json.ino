#include <ArduinoJson.h>
#include <TimeLib.h>
#include <ArduinoTrace.h>

JsonArray parseOpenWeather(String json) {
  // String over = "{'city': {'id': 4180439, 'name': 'Atlanta', 'coord': {'lon': -84.3954, 'lat': 33.7751}, 'country': 'US', 'population': 420003, 'timezone': -14400}, 'cod': '200', 'message': 6.3013146, 'cnt': 9, 'list': [{'dt': 1682010000, 'sunrise': 1681988456, 'sunset': 1682035902, 'temp': {'day': 81.12, 'min': 57.58, 'max': 83.34, 'night': 68.94, 'eve': 78.75, 'morn': 58.8}, 'feels_like': {'day': 79.45, 'night': 67.87, 'eve': 78.75, 'morn': 57.29}, 'pressure': 1022, 'humidity': 23, 'weather': [{'id': 800, 'main': 'Clear', 'description': 'sky is clear', 'icon': '01d'}], 'speed': 10.89, 'deg': 174, 'gust': 18.01, 'clouds': 7, 'pop': 0.70}, {'dt': 1682096400, 'sunrise': 1682074786, 'sunset': 1682122349, 'temp': {'day': 77.43, 'min': 60.08, 'max': 78.51, 'night': 68.52, 'eve': 73.42, 'morn': 60.08}, 'feels_like': {'day': 76.19, 'night': 67.28, 'eve': 72.16, 'morn': 58.89}, 'pressure': 1016, 'humidity': 28, 'weather': [{'id': 803, 'main': 'Clouds', 'description': 'broken clouds', 'icon': '04d'}], 'speed': 11.03, 'deg': 175, 'gust': 24.81, 'clouds': 65, 'pop': 0.03}, {'dt': 1682182800, 'sunrise': 1682161117, 'sunset': 1682208795, 'temp': {'day': 69.35, 'min': 57.34, 'max': 71.87, 'night': 60.66, 'eve': 68.56, 'morn': 59.14}, 'feels_like': {'day': 67.15, 'night': 58.53, 'eve': 66.43, 'morn': 59.09}, 'pressure': 1013, 'humidity': 25, 'weather': [{'id': 500, 'main': 'Rain', 'description': 'light rain', 'icon': '10d'}], 'speed': 13.85, 'deg': 324, 'gust': 23.91, 'clouds': 36, 'pop': 0.59, 'rain': 1.37}, {'dt': 1682269200, 'sunrise': 1682247449, 'sunset': 1682295241, 'temp': {'day': 66.9, 'min': 53.02, 'max': 68.22, 'night': 55.98, 'eve': 60.58, 'morn': 53.02}, 'feels_like': {'day': 64.94, 'night': 53.29, 'eve': 58.5, 'morn': 50.7}, 'pressure': 1018, 'humidity': 35, 'weather': [{'id': 803, 'main': 'Clouds', 'description': 'broken clouds', 'icon': '04d'}], 'speed': 12.57, 'deg': 296, 'gust': 19.93, 'clouds': 59, 'pop': 0}, {'dt': 1682355600, 'sunrise': 1682333781, 'sunset': 1682381688, 'temp': {'day': 67.5, 'min': 49.75, 'max': 69.24, 'night': 59.88, 'eve': 62.64, 'morn': 49.75}, 'feels_like': {'day': 64.71, 'night': 57.13, 'eve': 59.86, 'morn': 47.16}, 'pressure': 1020, 'humidity': 16, 'weather': [{'id': 804, 'main': 'Clouds', 'description': 'overcast clouds', 'icon': '04d'}], 'speed': 7.23, 'deg': 323, 'gust': 13.47, 'clouds': 87, 'pop': 0}, {'dt': 1682442000, 'sunrise': 1682420114, 'sunset': 1682468135, 'temp': {'day': 55.72, 'min': 49.8, 'max': 59.13, 'night': 49.8, 'eve': 50, 'morn': 54.07}, 'feels_like': {'day': 53.87, 'night': 46.02, 'eve': 45.95, 'morn': 51.71}, 'pressure': 1021, 'humidity': 61, 'weather': [{'id': 500, 'main': 'Rain', 'description': 'light rain', 'icon': '10d'}], 'speed': 10.29, 'deg': 95, 'gust': 26.82, 'clouds': 99, 'pop': 1, 'rain': 2.39}, {'dt': 1682528400, 'sunrise': 1682506449, 'sunset': 1682554581, 'temp': {'day': 49.73, 'min': 47.07, 'max': 49.98, 'night': 47.84, 'eve': 48.06, 'morn': 49.91}, 'feels_like': {'day': 44.24, 'night': 43.41, 'eve': 43.23, 'morn': 46.15}, 'pressure': 1011, 'humidity': 96, 'weather': [{'id': 502, 'main': 'Rain', 'description': 'heavy intensity rain', 'icon': '10d'}], 'speed': 15.35, 'deg': 60, 'gust': 33.82, 'clouds': 100, 'pop': 1, 'rain': 34.73}, {'dt': 1682614800, 'sunrise': 1682592784, 'sunset': 1682641028, 'temp': {'day': 64.36, 'min': 47.89, 'max': 64.36, 'night': 53.47, 'eve': 54.55, 'morn': 47.93}, 'feels_like': {'day': 62.76, 'night': 52.56, 'eve': 53.28, 'morn': 46.13}, 'pressure': 1013, 'humidity': 48, 'weather': [{'id': 500, 'main': 'Rain', 'description': 'light rain', 'icon': '10d'}], 'speed': 8.79, 'deg': 7, 'gust': 23.91, 'clouds': 91, 'pop': 0.48, 'rain': 0.36}, {'dt': 1682701200, 'sunrise': 1682679121, 'sunset': 1682727475, 'temp': {'day': 52.39, 'min': 46.94, 'max': 52.39, 'night': 46.94, 'eve': 50.31, 'morn': 51.1}, 'feels_like': {'day': 51.85, 'night': 44.42, 'eve': 48.94, 'morn': 50.47}, 'pressure': 1012, 'humidity': 96, 'weather': [{'id': 501, 'main': 'Rain', 'description': 'moderate rain', 'icon': '10d'}], 'speed': 8.77, 'deg': 47, 'gust': 18.79, 'clouds': 100, 'pop': 1, 'rain': 15.68}]}";
  DynamicJsonDocument data(15000);
  deserializeJson(data, json);
  data.shrinkToFit();

  DynamicJsonDocument periods_doc(3000);
  JsonArray periods = periods_doc.to<JsonArray>();

  int count = 0;
  for(JsonVariant v : data["list"].as<JsonArray>()) {
    if (count++ == 4) break;
    DynamicJsonDocument doc(1000);
    JsonObject info = doc.to<JsonObject>();
    time_t t = v["dt"].as<time_t>();
    info["day"] = dayStr(weekday(t));
    info["temperature"] = v["temp"];
    if (v["weather"][0]["description"] == "heavy intensity rain") info["forecast"] = "heavy rain";
    else info["forecast"] = v["weather"][0]["description"];
    // if pop is 100 then make it 99
    if (v["pop"] == 1) info["precipitation"] = 0.99;
    else info["precipitation"] = v["pop"];
    // if today's precipitation is > 50 then set LED blue
    if (count == 1 && info["precipitation"] > 0.5) {
      Serial.println("Precipitation detected, setting LED blue");
      ledcWrite(HTTP_RED_CHANNEL, 0);
      ledcWrite(HTTP_GREEN_CHANNEL, 50);
      ledcWrite(HTTP_BLUE_CHANNEL, 100);
    }
    info["icon"] = v["weather"][0]["icon"];
    doc.shrinkToFit();
    periods.add(info);
  }
  
  periods_doc.shrinkToFit();
  return periods;
}

void parseGov(String json) {
  // put your setup code here, to run once:
  Serial.begin(115200);

  DynamicJsonDocument data(15000);
  deserializeJson(data, json);
  data.shrinkToFit();

  DynamicJsonDocument periods_doc(3000);
  JsonArray periods = periods_doc.to<JsonArray>();

  for(JsonVariant v : data["properties"]["periods"].as<JsonArray>()) {
    if (v["name"].as<String>().indexOf("Night") != -1 ) continue;

    DynamicJsonDocument doc(1000);
    JsonObject info = doc.to<JsonObject>();

    info["name"] = v["name"];
    info["temperature"] = v["temperature"];
    info["forecast"] = v["shortForecast"];
    info["precipitation"] = v["probabilityOfPrecipitation"]["value"];
    doc.shrinkToFit();
    periods.add(info);

    serializeJson(info, Serial);
    Serial.println();
  }
  periods_doc.shrinkToFit();
  serializeJson(periods, Serial);
  Serial.println();
}