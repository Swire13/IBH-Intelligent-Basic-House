<?php

$db = mysqli_connect("localhost", "root", "raspberry", "IBH");

if (!$db) {
    echo "Error: Unable to connect to MySQL." . PHP_EOL;
    echo "Debugging errno: " . mysqli_connect_errno() . PHP_EOL;
    echo "Debugging error: " . mysqli_connect_error() . PHP_EOL;
    exit;
}

// Posts
$chcemJass = '';
$chcemTempp='';
$chcemSvetlo='';
$chcemHeat='';


if(isset($_GET['action'])) {
    $chcemJass = $_GET['action'];
    $chcemTempp = $_GET['action'];
    $chcemSvetlo=$_GET['action'];
    $chcemHeat=$_GET['action'];
}

switch ($chcemHeat) {
    case 'chcemTeplo':
        $val = '';
        $result = $db->query('SELECT heat_on FROM ovladanie WHERE room_name = "room_1"');
        if($result){
            while($row = $result->fetch_array()) {
                $val = $row;
            }
            echo  $val['heat_on'] ;
        }
        break;

    case 'nastavTeplo':
        $val = $_GET['hodnota'];
        $q = 'UPDATE ovladanie SET heat_on = '. $val .' WHERE room_name = "room_1"';
        $result = $db->query($q);

        if($result) {
            echo 1;
        }
        
    default:
        # code...
        break;
}

switch ($chcemSvetlo) {
    case 'chcemLight':
        $val = '';
        $result = $db->query('SELECT light_on FROM ovladanie WHERE room_name = "room_1"');
        if($result){
            while($row = $result->fetch_array()) {
                $val = $row;
            }
            echo  $val['light_on'] ;
        }
        break;

    case 'nastavLight':
        $val = $_GET['hodnota'];
        $q = 'UPDATE ovladanie SET light_on = '. $val .' WHERE room_name = "room_1"';
        $result = $db->query($q);

        if($result) {
            echo 1;
        }
        
    default:
        # code...
        break;
}




switch ($chcemTempp) {
    case 'chcemTemp':
        $val = '';
        $result = $db->query('SELECT heat_temp FROM ovladanie WHERE room_name = "room_1"');
        if($result){
            while($row = $result->fetch_array()) {
                $val = $row;
            }
            echo  $val['heat_temp'] ;
        }
        break;

    case 'nastavTemp':
        $val = $_GET['hodnota'];
        $q = 'UPDATE ovladanie SET heat_temp = '. $val .' WHERE room_name = "room_1"';
        $result = $db->query($q);

        if($result) {
            echo 1;
        }

    default:
        break;
}

switch($chcemJass) {
    case 'chcemJas':
        $val = '';
        $result = $db->query('SELECT light_pwm FROM ovladanie WHERE room_name = "room_1"');
        if($result){
            while($row = $result->fetch_array()) {
                $val = $row;
            }
            echo  $val['light_pwm'] ;
        }
        break;

    case 'getHistoryData':
        getHistoryData($db);

    case 'nastavJas':
        $val = $_GET['hodnota'];
        $q = 'UPDATE ovladanie SET light_pwm = '. $val .' WHERE room_name = "room_1"';
        $result = $db->query($q);

        if($result) {
            echo 1;
        }

    default:
        break;
}
// Vrat hodnoty pre historiu

function getHistoryData($db) {
    $result = $db->query('SELECT timestamp, temp1, humi1, pirs1 FROM statistiky ORDER BY timestamp DESC');

    if($result){
        while($row = $result->fetch_array()) {
            $myArray[] = $row;
        }
        echo json_encode($myArray);
    }
}

mysql_close($db);
?>


