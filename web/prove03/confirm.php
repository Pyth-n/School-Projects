<?php
$TITLE = "Order Details";
$BOOTSTRAP = true;
$CSSLOC = "../styles/prove03.css";
$SCRIPTLOC = "script.js";
require '../scripts/include/meta-head.php';

?>

<?php

    if($_POST['confirm'] == 0) {
        header("Location: cart.php?remove=1");
        exit();
    }

?>

<body>

<div class="container">
    <nav class="navbar navbar-expand-sm navbar-light bg-light rounded">

        <!-- Brand -->
        <a class="navbar-brand" href="prove3.php"><img id="logo1" src="https://seeklogo.com/images/N/nintendo-switch-logo-38D4F5C7E7-seeklogo.com.png">Gamez</a>

        <div class="navbar">
            <ul class="navbar-nav mr-auto">
                <li class="nav-item active">
                    <a class="nav-link" href="prove3.php">Browse <span class="sr-only">(current)</span></a>
                </li>
            </ul>
        </div>
    </nav>
</div>



<div class="container" align="center">

    <div class="jumbotron" align="left">
        <!-- Form here -->
        <h1>Order Complete</h1>
        <h4>Order details:</h4>

        <table class="table">

        <?php
            require 'itemsInStock.php';
            $stockCount =  count($items);

            // Puts what was ordered
            for($i = 0; $i < $stockCount; $i++) {
                // Check if ID is in cookies
                if(isset($_COOKIE[$items[$i][2]])) {
                    echo '<tr><th scope="row" class="remove">' . $items[$i][2] . '</th>';
                    echo '<td>' . $items[$i][3] . '</td>';
                    echo '<td>$' . $items[$i][1] . '</td>';
                    echo '</tr>';
                }
            }
        ?>
        </table>

        <h4>Shipping details:</h4>


        <?php
            $address = test_input($_POST['address']);
            $city = test_input($_POST['city']);
            $state = test_input($_POST['State']);
            $zip = test_input($_POST['zipcode']);



            echo "Address: " . $address . "<br>";
            echo "City: " . $city . "<br>";
            echo 'State: ' . $state . "<br>";
            echo 'Zip code: ' . $zip . "<br>";

            function test_input($data) {

                if (empty($data) || $data == "") {
                    return "";
                }

                $data = trim($data);
                $data = stripslashes($data);
                $data = htmlspecialchars($data);
                return $data;
            }
        ?>

    </div>
</div>



</body>
</html>