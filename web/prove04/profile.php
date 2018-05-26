<?php
$TITLE = "Prove 04 - Profile";
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
    <div id="body_content">
        <div class="jumbotron">

            <?php
                define('USE_DB', true);
                require 'include/connectDB.php';

                $userID = "";
                // ID selected
                if(isset($_POST['viewProfile'])) {
                    $userID = $_POST['viewProfile'];
                } else {
                    $userID = -1;
                }

                // query user information

                if($userID != -1) {
                    $statement = $db->prepare('SELECT * FROM users WHERE id=:id');
                    $statement->bindValue(':id', $userID, PDO::PARAM_INT);
                    $statement->execute();

                    $ROWS = $statement->fetchAll(PDO::FETCH_ASSOC);
                } else {
                    header("Location:prove4.php");
                    exit();
                }

            ?>

            <h2>First Name</h2>
                <?php echo $ROWS[0]['first_name']; ?>
            <h2>Last Name</h2>
                <?php echo $ROWS[0]['last_name']; ?>
            <h2>Popularity</h2>
                <?php echo $ROWS[0]['popularity']; ?>
            <h2>Date joined</h2>
                <?php echo $ROWS[0]['date_joined']; ?>
        </div>
    </div>
</div>

<?php
require '../scripts/include/bootstrap-scripts.php';
?>
</body>
</html>