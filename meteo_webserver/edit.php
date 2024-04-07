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
$configFile = 'config.json';

$configJson = file_get_contents($configFile);

$configArray = json_decode($configJson, true);
?>

<!DOCTYPE html>
<html lang="it">
<head>
    <meta charset="UTF-8">
    <title>Edit posizione</title>
</head>
<body>
    <?php
    // Verifica se sono stati inviati dati in POST
    if ($_SERVER["REQUEST_METHOD"] == "POST") {
        
        $lat = $_POST['lat'];
        $lon = $_POST['lon'];

        $configArray['lat'] = $lat;
        $configArray['lon'] = $lon;

        $newConfigJson = json_encode($configArray);

        if (file_put_contents($configFile, $newConfigJson) !== false) {
            echo "<p>Dati salvati con successo</p>";
        } else {
            echo "<p>Errore durante il salvataggio dei dati</p>";
        }
    } else {
        ?>
        <h2>Inserisci latitudine e longitudine</h2>
        <form method="post" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>">
            Latitudine: <input type="text" name="lat" value="<?php echo $configArray["lat"]?>"><br>
            Longitudine: <input type="text" name="lon" value="<?php echo $configArray["lon"]?>"><br>
            <input type="submit" name="submit" value="Salva">
        </form>
        <?php
    }
    ?>
</body>
</html>
