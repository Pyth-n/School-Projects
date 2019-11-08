<?php
    session_start();

    $target_dir = "../uploads/" . $_SESSION['id'];
    if(!file_exists($target_dir)) {
        $oldmask = umask(0);
        mkdir('../uploads/' . $_SESSION['id'], 0777, true);
        umask($oldmask);
    }

    if($_SERVER['REQUEST_METHOD'] == 'POST' && isset($_SESSION['id'])) {
        print_r($_FILES);
        print_r($_POST);

        $uploadOk = true;

        echo "<br>";

        // Make sure input was not empty
        if($_FILES['file']['size'] > 0) {
            // Check MIME
            $mimeCheck = getimagesize($_FILES['file']['tmp_name']);
            if ($mimeCheck !== false) {
                echo "File type is - " . $mimeCheck['mime'] . '<br>';
            }
        } else {
            echo "EMPTY";
            $uploadOk = false;
            header('Location: ../prove4.php?error=uploadEmpty');
            die();
        }

        // Get extension of file
        $extension = explode(".", $_FILES['file']['name']);
        (string) $extension = strtolower(end($extension));
        echo "You are uploading file type: $extension";

        // If file is a php, it is malicious
        if($extension == "php") {
            $uploadOk = false;
            header('Location: ../signout.php?die=true');
            die();
        }


        if(isset($_POST['submitPicture'])) {

            // Ensure image type is that of which is allowed
            if($extension != "jpg" && $extension != "png" && $extension != "jpeg"
                && $extension != "gif" ) {
                echo "Sorry, only JPG, JPEG, PNG & GIF files are allowed.";
                $uploadOk = 0;
                header('Location: ../prove4.php?error=imageType');
                die();
            }
            // Upload with a different name
            $newFileName = round(microtime(true)) . '.' . $extension;
            if(move_uploaded_file($_FILES['file']['tmp_name'], $target_dir . '/' . $newFileName)) {
                define('USE_DB', true);
                require '../include/connectDB.php';

                $SQL = 'INSERT INTO images(title, description, image_path, user_uploaded_id) values(
                      ?
                    , ?
                    , ?
                    , ?
                       )';


                // SQL path
                $saveLocation = 'uploads/' . $_SESSION['id'] . '/' . $newFileName;

                $statement = $db->prepare($SQL);
                $statement->bindParam(1, $_POST['title'], PDO::PARAM_STR);
                $statement->bindParam(2, $_POST['description'], PDO::PARAM_STR);
                $statement->bindParam(3, $saveLocation, PDO::PARAM_STR);
                $statement->bindParam(4, $_SESSION['id'], PDO::PARAM_STR);

                $statement->execute();

                header('Location: ../prove4.php');

                echo "<br>User " . $_SESSION['id'] . ' uploaded ' . $_FILES['file']['name'];

            }

        }


        if(isset($_POST['submitVideo'])) {


            if($extension != "mp4") {
                header('Location: ../prove4.php');
                die();
            }

            (string) $newFileName = round(microtime(true));

            (string) $newFileName = $newFileName . '.' . $extension;


            if(move_uploaded_file($_FILES['file']['tmp_name'], $target_dir . '/' . $newFileName)) {

                // TODO: move to database
                define('USE_DB', true);
                require '../include/connectDB.php';

                echo "<br>uploading..";

                $SQL = 'INSERT INTO videos(title, description, video_path, user_uploaded_id) values(
                      ?
                    , ?
                    , ?
                    , ?
                       )';

                $saveLocation = 'uploads/' . $_SESSION['id'] . '/' . $newFileName;

                $statement = $db->prepare($SQL);
                $statement->bindParam(1, $_POST['title'], PDO::PARAM_STR);
                $statement->bindParam(2, $_POST['description'], PDO::PARAM_STR);
                $statement->bindParam(3, $saveLocation, PDO::PARAM_STR);
                $statement->bindParam(4, $_SESSION['id'], PDO::PARAM_INT);

                $statement->execute();

                echo "Uploaded video";
                header('Location: ../prove4.php');


            }
        }

    }