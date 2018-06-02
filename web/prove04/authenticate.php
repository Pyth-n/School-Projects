<?php
// Make sure people are logged in before accessing website
$email = null;
$password = null;

if($_SERVER['REQUEST_METHOD'] == 'POST')
{
    if (!empty($_POST['email']) && !empty($_POST['password']))
    {
        $email = $_POST['email'];
        $password = $_POST['password'];

        if($email == 'lol@gmail.com' && $password == 'lol') {
            session_start();
            $_SESSION["authenticated"] = true;
            $_SESSION["username"] = $email;
            header('Location: prove4.php');
        } else {
            $_SESSION["authenticated"] = false;
            header('Location: login.php');

        }

    }else
    {
        $_SESSION["authenticated"] = false;
        header('Location: login.php');

    }

} else
{
    $_SESSION["authenticated"] = false;
    header('Location: login.php');

}
?>