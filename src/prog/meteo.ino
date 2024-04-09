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

#define METEO_API_HOST "demosnm.altervista.org"
#define METEO_API_PORT 80
#define MAX_NUM_TENTATIVI_LETTURA 2

uint8_t tentativiLetturaMeteo = 0;
WiFiClient client;

void readResponse() {

  // Skip HTTP headers
  char endOfHeaders[] = "\r\n\r\n";
  if (!client.find(endOfHeaders)) {
    Serial.println(F("Invalid response"));
    return;
  }

  JsonDocument doc;

  DeserializationError error = deserializeJson(doc, client);
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }

  meteo.id = doc["id"].as<uint16_t>();
  meteo.main = doc["main"].as<const char*>();
  meteo.description = doc["description"].as<const char*>();
  /*
  Serial.println(meteo.id);
  Serial.println(meteo.main);
  Serial.println(meteo.description);
  */
}

void chiediMeteoCallback() {
  if (isWifiConnected()) {

    String footer = String(" HTTP/1.1\r\n") + "Host: " + String(METEO_API_HOST) + "\r\n" + "Connection: close\r\n\r\n";

    if (client.connect(METEO_API_HOST, METEO_API_PORT)) {
      client.print("GET /meteo.php" + footer);
      tentativiLetturaMeteo = MAX_NUM_TENTATIVI_LETTURA;
    }

  } else {
    WiFi.reconnect();
  }
}

void leggiRispMeteo() {
  if (tentativiLetturaMeteo > 0) {
    if (client.available() == 0) {
      tentativiLetturaMeteo--;
    } else {
      readResponse();
      client.stop();
    }
  }
}