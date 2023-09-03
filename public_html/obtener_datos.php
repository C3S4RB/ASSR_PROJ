<?php
include 'conexion_web.php';

 

 

$query1 = "SELECT Nombre, Aforomaximo, Aforodisponible FROM locales WHERE IDlocal = 1";
$query2 = "SELECT Nombre, Aforomaximo, Aforodisponible FROM locales WHERE IDlocal = 2";

 

 

$result1 = mysqli_query($con, $query1);
$data1 = mysqli_fetch_assoc($result1);

 

 

$result2 = mysqli_query($con, $query2);
$data2 = mysqli_fetch_assoc($result2);

 

 

mysqli_close($con);

 

 

$data = array('local1' => $data1, 'local2' => $data2);

 

 

header('Content-Type: application/json');
echo json_encode($data);
?>