<?php
// Make sure people are logged in before accessing website
    session_start();
    if ($_SESSION['authenticated'] != true) {
        session_unset();
        session_destroy();
        header('Location: login.php');
        die();
    }
    define('USE_DB', true);
    require 'include/connectDB.php';
    $statement = $db->prepare('SELECT first_name, last_name, popularity FROM users WHERE id=:id');
    $statement->bindValue(':id', (int) $_SESSION['id'], PDO::PARAM_INT);
    $statement->execute();

    $ROWS = $statement->fetchAll(PDO::FETCH_ASSOC);
?>
<?php
    $TITLE = "Home - Pixel";
    $BOOTSTRAP = true;

    $CSSLOC = "style.css";
    //$SCRIPTLOC = "";

    require '../scripts/include/meta-head.php';
?>

<body>
<div class="container">

    <?php
        define('IN_MY_PROJECT', true);
        include 'include/navigation_bar.php';
    ?>

    <!-- Main body content -->
        <div class="jumbotron">
            <div class="row">

                <!-- Profile info column -->
                <div class="col-sm-4">
                    <h1><?php
                        echo $ROWS[0]['first_name'] . ' ' . $ROWS[0]['last_name'];
                        ?></h1>
                    <img src="../imgs/image.jpg" />
                    <br />
                    <small class="text-muted">Popularity: <?php echo $ROWS[0]['popularity']; ?> </small>
                </div>


                <!-- Profile content -->
                <div class="col-sm-8">
                    <h1>Pixels</h1>
                    <img src="../imgs/mario.jpg" class="img-fluid">
                </div>
            </div>

        </div>
</div>

<?php
    require '../scripts/include/bootstrap-scripts.php';
?>
</body>
</html>