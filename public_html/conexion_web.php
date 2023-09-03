<?php
$user = "id21160849_cborja";
$pass = "Cborja21@.";
$server = "localhost";
$db ="id21160849_db";
$con = mysqli_connect($server, $user, $pass, $db);

if (!$con) {
    die("Error de conexión: " . mysqli_connect_error());
}
?>
