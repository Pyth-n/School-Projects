<?php
    if($_SERVER['REQUEST_METHOD'] == 'POST') {
        print_r($_POST);
        echo "<br>";
        print_r($_FILES);

/*        if($_FILES['file']['size'] > 0) {
            echo "NOT EMPTY";
        } else {
            echo "EMPTY";
            header('Location: ../prove4.php?error=uploadEmpty');
            die();
        }*/




        if(isset($_POST['submitPicture'])) {

            (string) $mimeType = mime_content_type($_FILES['file']);

            echo "You are uploading a picture of type: $mimeType";

        } else if(isset($_POST['submitVideo'])) {
            echo 'You are uploading a video.';
        }

    }