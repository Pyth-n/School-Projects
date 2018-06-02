<?php
    // Hash password
    $password = (string)password_hash($_POST['password'], PASSWORD_DEFAULT);

    // Store local variables
    $email = (string)$_POST['email'];
    $first_name = (string)$_POST['firstName'];
    $last_name = (string)$_POST['lastName'];

    echo $password;

    // connect to database
    define('USE_DB', true);
    require 'include/connectDB.php';

    $sql = "INSERT INTO users (EMAIL, PASSWORD_S, FIRST_NAME, LAST_NAME, DATE_JOINED)
VALUES (
	?,
	?,
	?,
	?,
	current_timestamp
)";

    $statement = $db->prepare($sql);
    $statement->bindParam(1, $email, PDO::PARAM_STR);
    $statement->bindParam(2, $password, PDO::PARAM_STR);
    $statement->bindParam(3, $first_name, PDO::PARAM_STR);
    $statement->bindParam(4, $last_name, PDO::PARAM_STR);
    $statement->execute();


?>