<?php
    $removingFromCart = "";

    if(isset($_POST['removeitem'])) {
        $removingFromCart = $_POST['removeitem'];
    } else if(isset($_POST['cancelCheckout'])) {
        $removingFromCart = $_POST['cancelCheckout'];
    }

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

    if($_POST['cancelCheckout'] == $removingFromCart) {
        header("Location: cart.php?remove=1");
        exit();
    } else {
        header("Location: prove3.php?action=1");
        exit();
    }



?>