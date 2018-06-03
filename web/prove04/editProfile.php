<?php
// Make sure people are logged in before accessing website
session_start();
if ($_SESSION['authenticated'] != true) {
    header('Location: login.php');
}
?>
<?php
$TITLE = "Editing Profile";
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
            if(isset($_POST['ID'])) {
                $userID = $_POST['ID'];
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

            <form action="updateProfile.php" method="post">
                <div class="form-row">
                    <div class="form-group col-md-5">
                        <label for="firstName">First name</label>
                        <input type="text" required="true" class="form-control" value="<?php echo $ROWS[0]['first_name']; ?>" name="firstName">
                    </div>

                    <div class="form-group col-md-5">
                        <label for="lastName">Last name</label>
                        <input type="text" required="true" class="form-control" value="<?php echo $ROWS[0]['last_name']; ?>" name="lastName">
                    </div>
                    <div class="form-group col-md-2">
                        <label for="lastName">Popularity</label>
                        <input type="text" required="true" class="form-control" value="<?php echo $ROWS[0]['popularity']; ?>" name="popularity">
                    </div>
                </div>

                <input type="hidden" value="<?php echo $ROWS[0]['id']; ?>" name="ID">
                <button type="submit" class="btn btn-primary">Update</button>

            </form>

        </div>
    </div>
</div>

<?php
require '../scripts/include/bootstrap-scripts.php';
?>
</body>
</html>