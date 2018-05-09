<?php
    $TITLE = "Prove 03";
    $BOOTSTRAP = true;
    $CSSLOC = "../styles/prove03.css";
    //$SCRIPTLOC = "../../scripts/script.js";
    require '../scripts/include/meta-head.php';
?>
<body>

    <div class="container">

        <nav class="navbar navbar-expand-sm navbar-light bg-light rounded">

                <a class="navbar-brand" href="#">Gamez</a>
                <button class="navbar-toggler" aria-expanded="false" aria-controls="navbarsExample09" aria-label="Toggle navigation" type="button" data-toggle="collapse" data-target="#navbarsExample09">
                    <span class="navbar-toggler-icon"></span>
                </button>
                <div class="collapse navbar-collapse" id="navbarsExample09">
                    <ul class="navbar-nav mr-auto">
                        <li class="nav-item active">
                            <a class="nav-link" href="prove3.php">Browse <span class="sr-only">(current)</span></a>
                        </li>

                    </ul>
                    <ul class="navbar-nav">
                        <li class="nav-item dropdown">
                            <a class="nav-link dropdown-toggle" id="dropdown09" aria-expanded="false" aria-haspopup="true" href="#" data-toggle="dropdown">Cart</a>

                            <ul class="dropdown-menu dropdown-cart" aria-labelledby="dropdown09">
                                <li class="dropdown-item disabled" href="#">
                                    <span class="item">
                                        <span class="item-left">
                                            <img src="../imgs/image.jpg" class="cart-image"/>
                                            <span class="item-info">
                                                <span>Item name</span>
                                                <span>23$</span>
                                            </span>
                                        </span>
                                        <span class="item-right">
                                            <button class="btn btn-xs btn-danger pull-right">x</button>
                                        </span>
                                    </span>
                                </li>



                                <li class=""><hr></li>
                                <li class="text-center"><a href="#">View Cart</a></li>
                            </ul>
                        </li>
                    </ul>

                </div>

        </nav>

        <div class="container">
            <?php
            echo "<h1>Welcome!</h1>"
            ?>

            <div class="row">
                <div class="col-sm">
                    One column
                </div>
                <div class="col-sm">
                    Two column
                </div>
                <div class="col-sm">
                    three column
                </div>
                <div class="col-sm">
                    four column
                </div>
            </div>

        </div>


    </div>

    <?php
        require '../scripts/include/bootstrap-scripts.php';
    ?>
</body>
</html>