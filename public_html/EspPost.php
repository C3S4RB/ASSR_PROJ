<?php
include 'conexion.php';

if ($con) {
    echo "Conexion con base de datos exitosa! ";

    if (isset($_POST['accion'])) {
        $accion = $_POST['accion'];

        if ($accion === "sumar1") {
            $consulta = "UPDATE locales SET Aforodisponible = Aforodisponible + 1 WHERE IDlocal = 1;";
        } elseif ($accion === "restar1") {
            $consulta = "UPDATE locales SET Aforodisponible = Aforodisponible - 1 WHERE IDlocal = 1;";
        } elseif ($accion === "sumar2") {
            $consulta = "UPDATE locales SET Aforodisponible = Aforodisponible - 1 WHERE IDlocal = 2;";
        } elseif ($accion === "restar2") {
            $consulta = "UPDATE locales SET Aforodisponible = Aforodisponible - 1 WHERE IDlocal = 2;";
        } 
        
        else {
            echo "Acción no válida.";
            exit;
        }

        $resultado = mysqli_query($con, $consulta);

        if ($resultado) {
            echo "Registro en base de datos OK! ";
        } else {
            echo "Falla! Registro BD";
        }
    } else {
        echo "No se proporcionó una acción en la solicitud.";
    }
} else {
    echo "Falla! conexion con Base de datos ";
}
?>