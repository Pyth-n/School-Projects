<?php
    session_start();
    $target_dir = "uploads/" . $_SESSION['id'];

    // If the target location doesn't exist, create folder
    if(!file_exists($target_dir)) {
        $oldmask = umask(0);
        mkdir('uploads/' . $_SESSION['id'], 0777, true);
        umask($oldmask);
    }

    $uploadOk = 1;

    if($_SERVER['REQUEST_METHOD'] == 'POST') {
        $check = getimagesize($_FILES['file']['tmp_name']);
        if($check !== false) {
            echo "File is an image - " . $check["mime"] . ".<br>";
            $uploadOk = 1;
        } else {
            echo "File is not an image.";
            $uploadOk = 0;
        }

        if($uploadOk == 0) {

        } else {

            $tmp = explode(".", $_FILES['file']['name']);
            $newFileName = round(microtime(true)) . '.' . end($tmp);
            $saveLocation = $target_dir . '/' . $newFileName;

            if(move_uploaded_file($_FILES['file']['tmp_name'], $saveLocation)) {
                echo "Image was uploaded to $saveLocation";

                // store path in database
                define('USE_DB', true);
                require 'include/connectDB.php';

                $sql = "INSERT INTO images(user_uploaded_id, title, image_path) 
                        VALUES(
                          ?
                          , 'test'
                          , ?
                        )";

                $statement = $db->prepare($sql);
                $statement->bindParam(1, $_SESSION['id'], PDO::PARAM_INT);
                $statement->bindParam(2, $saveLocation);
                $statement->execute();

                $sql = "UPDATE users SET profile_picture_path = ? WHERE id=?";
                $statement = $db->prepare($sql);
                $statement->bindParam(1, $saveLocation, PDO::PARAM_STR);
                $statement->bindParam(2, $_SESSION['id'], PDO::PARAM_INT);
                $statement->execute();

                echo "<br>Database updated nicely";
                header('Location: prove4.php');

            } else {
                echo "sorry there was an error";
            }
        }
    }
?>