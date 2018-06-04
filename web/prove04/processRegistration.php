<?php
    $password = null;

    // Store local variables
    $email = (string)$_POST['email'];
    $first_name = (string)$_POST['firstName'];
    $last_name = (string)$_POST['lastName'];

    // Verify password inputs are the same
    if($_POST['password'] === $_POST['passwordVerify']) {
        // Hash password
        $password = (string)password_hash($_POST['password'], PASSWORD_DEFAULT);
    } else {
        header('Location: register.php?error=password&fn=' . $first_name . '&ln=' . $last_name . '&email=' . $email);
        die();
    }

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

    try {
        $statement = $db->prepare($sql);
        $statement->bindParam(1, $email, PDO::PARAM_STR);
        $statement->bindParam(2, $password, PDO::PARAM_STR);
        $statement->bindParam(3, $first_name, PDO::PARAM_STR);
        $statement->bindParam(4, $last_name, PDO::PARAM_STR);
        $statement->execute();
    }
    catch (PDOException $e) {
        header('Location: register.php?error=1');
        exit();
    }

    header('Location: login.php?signup=true');
?>