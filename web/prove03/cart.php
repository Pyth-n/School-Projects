<?php
$TITLE = "Cart Checkout";
$BOOTSTRAP = true;
$CSSLOC = "../styles/prove03.css";
$SCRIPTLOC = "script.js";
require '../scripts/include/meta-head.php';

?>


<body>

<?php

if($_GET['cancelled'] == 1) {
    echo '<div class="alert alert-danger" role="alert">
                Confirmation Cancelled
                <button type="button" class="close" data-dismiss="alert" aria-label="Close">
                    <span aria-hidden="true">&times;</span>
                </button>
            </div>';
}
?>
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

    <div class="container">
        <table class="table table-striped">

            <thead>
                <tr>
                    <th scope="col" class="remove">Item ID</th>
                    <th scope="col">Item name</th>
                    <th scope="col">Price</th>
                    <th scope="col"></th>
                </tr>
            </thead>

            <tbody>

                <?php require 'loadCart.php'; ?>

                <tr>
                    <th scope="row" class=""></th>
                    <td></td>
                    <td></td>
                    <td>Total: <br><?php echo $totalCost; ?></td>
                </tr>
            </tbody>

        </table>
        <form id="form3" action="checkout.php" method="post">

        </form>
        <form id="removeItem" action="removeitem.php" method="post">

        </form>
    </div>

    <div class="container" align="center">
        <button type="submit" form="form3" name="checkout" value="true" class="btn btn-primary btn-lg btn-block">Checkout</button>
    </div>
</body>
</html>