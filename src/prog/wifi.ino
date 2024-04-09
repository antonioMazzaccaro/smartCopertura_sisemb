/*
    Copyright (C) 2024  Antonio Mazzaccaro

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#define WIFI_SSID "moto g84 5G_3521"
#define WIFI_PWD "12345678"

bool isWifiConnected() {
  return WiFi.status() == WL_CONNECTED;
}

void reconnectToWifi() {
  WiFi.reconnect();
}


bool connectToWifi() {
  WiFi.begin(WIFI_SSID, WIFI_PWD);

  uint8_t i = 0;
  while (!isWifiConnected() && i < 20) {
    delay(500);
    Serial.print(".");
    i++;
  }

  if (!isWifiConnected()) {
    Serial.println("Connessione a rete WiFi non riuscita");
    return false;
  }

  Serial.println("WiFi connessa");
  return true;
}