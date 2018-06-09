<?php
    session_start();

    // Authentication
    if($_SERVER['REQUEST_METHOD'] == 'POST' && isset($_SESSION['id'])) {
        if(isset($_POST['pictureCommentSubmit'])) {
            echo 'Uploading picture comment ID: ' . $_POST['pictureID'];

            define('USE_DB', true);
            require '../include/connectDB.php';

            $SQL = 'INSERT INTO image_comments(comment, image_commented, user_commented)
                    VALUES (?, ?, ?)';
            $statement = $db->prepare($SQL);
            $statement->bindParam(1, $_POST['pictureComment'], PDO::PARAM_STR);
            $statement->bindParam(2, $_POST['pictureID'], PDO::PARAM_INT);
            $statement->bindParam(3, $_SESSION['id'], PDO::PARAM_INT);
            $statement->execute();

        } else if(isset($_POST['videoCommentSubmit'])) {
            echo 'Uploading vid comment: ' . $_POST['videoID'] . '<br>';

            define('USE_DB', true);
            require '../include/connectDB.php';

            $SQL = 'INSERT INTO video_comments(comment, video_commented, user_commented)
                    VALUES (?, ?, ?)';
            $statement = $db->prepare($SQL);
            $statement->bindParam(1, $_POST['videoComment'], PDO::PARAM_STR);
            $statement->bindParam(2, $_POST['videoID'], PDO::PARAM_INT);
            $statement->bindParam(3, $_SESSION['id'], PDO::PARAM_INT);
            $statement->execute();
            echo "Uploaded comment.";
        } else {
            header('Location: ../signout.php');
            die();
        }
    }