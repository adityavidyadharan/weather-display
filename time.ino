#include <WiFi.h>
#include <TimeLib.h>

// timezone offset est
const int offset = 4;

void setTime() {
    // Amber HTTP LED
    ledcWrite(HTTP_RED_CHANNEL, 50);
    ledcWrite(HTTP_GREEN_CHANNEL, 25);
    ledcWrite(HTTP_BLUE_CHANNEL, 0);
    configTime(0, 0, "pool.ntp.org", "time.nist.gov");
    Serial.println("Waiting for NTP time sync: ");
    time_t now = time(nullptr);
    while (now < 8 * 3600 * 2) {
        delay(500);
        Serial.print(".");
        now = time(nullptr);
    }
    // now = 1682238401;
    now -= offset * 3600;
    Serial.println("");
    Serial.print("Got NTP time: ");
    Serial.println(ctime(&now));
    ledcWrite(HTTP_RED_CHANNEL, 0);
    ledcWrite(HTTP_GREEN_CHANNEL, 50);
    ledcWrite(HTTP_BLUE_CHANNEL, 0);
    setTime(now);
}

String getDate() {
    // return string in format "Saturday, Jan 20th"
    String day_str = dayStr(weekday());
    // get three letter month
    String month_str = monthStr(month());
    month_str = month_str.substring(0, 3);
    String date = String(day_str + ", " + month_str + " " + day());
    return date;
}

String getTime() {
    // return string in format "12:00 AM"
    String time_str = "";
    String hour_str = String(hourFormat12());
    String minute_str = String(minute());
    if (minute() < 10) {
        minute_str = "0" + minute_str;
    }
    String am_pm = isAM() ? "AM" : "PM";
    time_str = String(hour_str + ":" + minute_str + " " + am_pm);
    return time_str;
}