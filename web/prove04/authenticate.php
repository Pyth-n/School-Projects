<?php
    // Start with null values
    $email = $password = null;

    // Ensure request was from a post
    if($_SERVER['REQUEST_METHOD'] == 'POST')
    {
        // Make sure these indexes are not empty
        if (!empty($_POST['email']) && !empty($_POST['password']))
        {
            // Set email and password respectively
            $email = $_POST['email'];
            $password = $_POST['password'];

            // Import database instance
            define('USE_DB', true);
            require 'include/connectDB.php';

            // Retrieve ID and password from users table, match with email
            $statement = $db->prepare("SELECT id, password_s FROM users WHERE email=:email");
            $statement->bindValue(':email', $email, PDO::PARAM_STR);
            $statement->execute();

            // Store associations
            $ROWS = $statement->fetchAll(PDO::FETCH_ASSOC);
            
            // Match password
            if(password_verify($password, $ROWS[0]['password_s'])) {
                session_start();
                $_SESSION["authenticated"] = true;
                $_SESSION["username"] = $email;
                $_SESSION["id"] = $ROWS[0]['id'];
                header('Location: prove4.php');
            } else { // Password didn't match
                header('Location: login.php?error=password');
            }

        } else { // Email or password input is empty
            header('Location: login.php?error=input');
        }

    } else { // Document requested without a post
        header('Location: login.php?error=access');
    }
?>