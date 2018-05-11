<?php
    echo $_POST['removeitem'] . " brought you here";

    $removingFromCart = $_POST['removeitem'];

    require 'itemsInStock.php';

    $itemCount = count($items);

    $cookie_count = $_COOKIE['cookieAmount'];

    for($i = 0; $i < $itemCount; $i++) {
        if($items[$i][2] == $removingFromCart) {
            setcookie($removingFromCart, "", time() - 3600);
            $cookie_count--;
        }
    }

    setcookie("cookieAmount", $cookie_count);

    header("Location: prove3.php?action=1");
    exit();
?>