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

<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <title>Scelta delle condizioni meteorologiche</title>
</head>
<body>
    <h2>Seleziona le condizioni meteorologiche:</h2>
    <form method="post" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>">
        <input type="radio" name="condizioni" value="meteo-reale"> Meteo reale</input><br>
        <input type="radio" name="condizioni" value="soleggiato"> Soleggiato</input><br>
        <input type="radio" name="condizioni" value="pioggia-debole"> Pioggia debole</input><br>
        <input type="radio" name="condizioni" value="pioggia-forte"> Pioggia forte</input><br>
        <input type="radio" name="condizioni" value="poco-nuvoloso"> Poco nuvoloso</input><br>
        <input type="radio" name="condizioni" value="molto-nuvoloso"> Molto nuvoloso</input><br>
        <input type="radio" name="condizioni" value="grandine"> Grandine</input><br>
        <input type="radio" name="condizioni" value="neve-leggera"> Neve leggera</input><br>
        <input type="radio" name="condizioni" value="neve-forte"> Neve forte</input><br>
        <input type="radio" name="condizioni" value="tempesta"> Tempesta</input><br>
        <br>
        <input type="submit" name="submit" value="Salva">
    </form>

    <?php
    $configFile = 'config.json';

    if ($_SERVER["REQUEST_METHOD"] == "POST" && isset($_POST['condizioni'])) {
        $condizione = $_POST['condizioni'];

        $configJson = file_get_contents($configFile);

        $configArray = json_decode($configJson, true);
        $configArray['condizioni'] = $condizione;

        $newConfigJson = json_encode($configArray);

        if (file_put_contents($configFile, $newConfigJson) !== false) {
            echo "<p>Dati salvati con successo</p>";
        } else {
            echo "<p>Errore durante il salvataggio dei dati</p>";
        }
    }
    ?>
</body>
</html>
