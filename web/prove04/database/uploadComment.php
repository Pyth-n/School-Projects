<?php
    session_start();

    $liked = true;

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

        }

        if (isset($_POST['pictureLike'])) {
            echo "Liking the picture..";

            define('USE_DB', true);
            require '../include/connectDB.php';

            $SQL = 'UPDATE images SET image_likes = image_likes + 1 WHERE id=:id';
            $statement = $db->prepare($SQL);
            $statement->bindValue(':id', $_POST['pictureID'], PDO::PARAM_INT);
            $statement->execute();


        }

        if (isset($_POST['pictureDislike'])) {

            define('USE_DB', true);
            require '../include/connectDB.php';

            echo "Disliking the picture..";
            $SQL = 'UPDATE images SET image_likes = image_likes - 1 WHERE id=:id';
            $statement = $db->prepare($SQL);
            $statement->bindValue(':id', $_POST['pictureID'], PDO::PARAM_INT);
            $statement->execute();
            $liked = false;
        }

        if(isset($_POST['videoCommentSubmit'])) {
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
        }

        if (isset($_POST['videoLike'])) {
            echo "Liking the video..";
            define('USE_DB', true);
            require '../include/connectDB.php';

            $SQL = 'UPDATE videos SET video_likes = video_likes + 1 WHERE id=:id';
            $statement = $db->prepare($SQL);
            $statement->bindValue(':id', $_POST['videoID'], PDO::PARAM_INT);
            $statement->execute();
        }

        if (isset($_POST['videoDislike'])) {
            echo "Disliking the video..";

            define('USE_DB', true);
            require '../include/connectDB.php';

            $SQL = 'UPDATE videos SET video_likes = video_likes - 1 WHERE id=:id';
            $statement = $db->prepare($SQL);
            $statement->bindValue(':id', $_POST['videoID'], PDO::PARAM_INT);
            $statement->execute();
            $liked = false;
        }
        $updateID = null;

        if(isset($_POST['visiting'])) {
            $updateID = $_POST['visiting'];
        } else {
            $updateID = $_SESSION['id'];
        }

        if($liked) {
            define('USE_DB', true);
            require '../include/connectDB.php';

            $SQL = 'UPDATE users SET popularity = popularity + 1 WHERE id=:id';
            $statement = $db->prepare($SQL);
            $statement->bindValue(':id', $updateID, PDO::PARAM_INT);
            $statement->execute();
        } else {
            $SQL = 'UPDATE users SET popularity = popularity - 1 WHERE id=:id';
            $statement = $db->prepare($SQL);
            $statement->bindValue(':id', $updateID, PDO::PARAM_INT);
            $statement->execute();
        }


        if(isset($_POST['visiting'])) {
            header('Location:../viewProfile.php?profileId=' . $_POST['visiting']);
        } else {
            header('Location:../prove4.php');
        }
    }