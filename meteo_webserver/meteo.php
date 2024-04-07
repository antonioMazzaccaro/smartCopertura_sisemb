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

<?php

header('Content-Type: application/json');

$url = 'https://api.openweathermap.org/data/2.5/weather';

$configFile = 'config.json';

$lat = null;
$lon = null;
$appid = null;
$condizioni = null;

$configJson = file_get_contents($configFile);

$configArray = json_decode($configJson, true);

if ($configArray !== null) {
    $lat = $configArray['lat'];
    $lon = $configArray['lon'];
    $appid = $configArray['appid'];
    $condizioni = $configArray['condizioni'];

}

if ($lat !== null && $lon !== null && $appid !== null && $condizioni === "meteo-reale") {
    
    $curl = curl_init();

    curl_setopt($curl, CURLOPT_URL, $url . "?lat=" . $lat . "&lon=" . $lon ."&appid=" . $appid);
    curl_setopt($curl, CURLOPT_HTTPGET, true);
    curl_setopt($curl, CURLOPT_RETURNTRANSFER, true);

    $response = curl_exec($curl);

    if(curl_errno($curl)) {
        echo '{}';
        
    } else {
        $result = json_decode($response, true);

        if ($result === null) {
            echo "{}";
        } else {
            // Filtraggio dei campi non necessari

            $result = json_encode($result['weather']['0']);
            header("Content-Length: " . strlen($result));
            echo $result;
        }
    }

    curl_close($curl);

} else {
    $result = file_get_contents("condizioni/". $condizioni . ".json");
    header("Content-Length: " . strlen($result));
    echo $result;
}


?>
