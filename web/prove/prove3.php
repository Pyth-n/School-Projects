<?php
    $TITLE = "Prove 03";
    $BOOTSTRAP = true;
    $CSSLOC = "../styles/prove03.css";
    $SCRIPTLOC = "script.js";
    require '../scripts/include/meta-head.php';

?>

<?php
    $action = $_GET['action'];

    switch ($action) {
        case 1:
            echo '<div class="alert alert-danger" role="alert">
                An item has been removed from the cart!
                <button type="button" class="close" data-dismiss="alert" aria-label="Close">
                    <span aria-hidden="true">&times;</span>
                </button>
            </div>';
            break;
        case 2:
            echo '<div class="alert alert-success" role="alert">
                An item has been added to the cart!
                <button type="button" class="close" data-dismiss="alert" aria-label="Close">
                    <span aria-hidden="true">&times;</span>
                </button>
            </div>';
            break;
        default:
            break;
    }
    if($_GET['action'] == 1) {


    }
?>

<body>

    <div class="container">

        <!-- Navigation bar -->
        <nav class="navbar navbar-expand-sm navbar-light bg-light rounded">

            <!-- Brand -->
            <a class="navbar-brand" href="#"><img id="logo1" src="https://seeklogo.com/images/N/nintendo-switch-logo-38D4F5C7E7-seeklogo.com.png">Gamez</a>

            <!-- Hamburger toggle -->
            <button class="navbar-toggler" aria-expanded="false" aria-controls="navbarsExample09" aria-label="Toggle navigation" type="button" data-toggle="collapse" data-target="#navbarsExample09">
                <span class="navbar-toggler-icon"></span>
            </button>

            <div class="collapse navbar-collapse" id="navbarsExample09" >
                <ul class="navbar-nav mr-auto">
                    <li class="nav-item active">
                        <a class="nav-link" href="prove3.php">Browse <span class="sr-only">(current)</span></a>
                    </li>
                </ul>

                <!-- Shopping cart -->
                <ul class="navbar-nav">
                    <li class="nav-item dropdown">
                        <a class="nav-link dropdown-toggle" id="dropdown09" aria-expanded="false" aria-haspopup="true" href="#" data-toggle="dropdown">
                            Cart<span class="badge badge-light"><?php echo $_COOKIE['cookieAmount']; ?> </span></a>

                        <ul class="dropdown-menu dropdown-cart dropdown-menu-right" aria-labelledby="dropdown09">

                            <!-- Cart contents -->
                            <?php
                                require 'addcart.php';
                            ?>

                            <li class=""><hr></li>
                            <li class="text-center"><a href="../index.php">View Cart</a></li>
                        </ul>
                    </li>
                </ul>

            </div>

        </nav>

        <!-- Welcome -->
        <div class="container">

            <!-- Button group for changing pages -->
            <div class="btn-group" align="center" role="group" aria-label="Type of games">
                <form action="prove3.php" method="POST">
                    <button type="submit" class="btn btn-secondary" value="mainstream" name="selection">Mainstream</button>
                    <button type="submit" class="btn btn-secondary" value="nindies" name="selection">Nindies</button>
                </form>
            </div>
        </div>

        <form id="form1" method="post" action="cookiez.php">
        </form>

        <form id="form2" method="post" action="removeitem.php">
        </form>

        <div class="jumbotron">
            <?php
            // Handle page
            if($_POST['selection'] == 'nindies') {
                $PAGESEL = "NIN";
            } else {
                $PAGESEL = "MAINST";
            }
            require 'items.php';
            ?>
        </div>

    </div>

    <?php
        require '../scripts/include/bootstrap-scripts.php';
    ?>
</body>
</html>