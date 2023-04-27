# download openweathermap.org icons
# https://openweathermap.org/weather-conditions

import requests

day_icons = ["01d", "02d", "03d", "04d", "09d", "10d", "11d", "13d", "50d"]
night_icons = ["01n", "02n", "03n", "04n", "09n", "10n", "11n", "13n", "50n"]

#save icons to png/*.png
for icon in day_icons + night_icons:
    url = "https://openweathermap.org/img/wn/" + icon + ".png"
    r = requests.get(url, allow_redirects=True)
    open("png/i" + icon + ".png", "wb").write(r.content)
