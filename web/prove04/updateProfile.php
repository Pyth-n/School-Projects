<?php
// Make sure people are logged in before accessing website
session_start();
if ($_SESSION['authenticated'] != true) {
    header('Location: login.php');
}
?>
<?php
    // Store variables to edit
    $ID = (int) $_POST['ID'];
    $firstName = (string) $_POST['firstName'];
    $lastName = (string) $_POST['lastName'];
    $popularity = (int) $_POST['popularity'];

    // Update database
    define('USE_DB', true);
    require 'include/connectDB.php';

    $sql = "UPDATE users SET first_name=:fn, last_name=:ln, popularity=:pop WHERE id=:id";
    $statement = $db->prepare($sql);

    $statement->bindParam(':fn', $firstName, PDO::PARAM_STR);
    $statement->bindParam(':ln', $lastName, PDO::PARAM_STR);
    $statement->bindParam(':pop', $popularity, PDO::PARAM_INT);
    $statement->bindValue(':id', $ID, PDO::PARAM_INT);
    $statement->execute();

    echo "<br>complete i guess";
?>