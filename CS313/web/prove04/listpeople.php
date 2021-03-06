<?php
    // Make sure people are logged in before accessing website
    session_start();
    if ($_SESSION['authenticated'] != true || !isset($_SESSION['id'])) {
        header('Location: login.php');
    }
?>

<?php
$TITLE = "Prove 04 - People";
$BOOTSTRAP = true;

$CSSLOC = "style.css";
//$SCRIPTLOC = "";

require '../scripts/include/meta-head.php';
?>

<?php
    // check if admin
    define('USE_DB', true);
    require 'include/connectDB.php';

    $SQL = 'SELECT is_admin FROM users WHERE id=:id';
    $statement = $db->prepare($SQL);
    $statement->bindValue(':id', $_SESSION['id'], PDO::PARAM_INT);
    $statement->execute();

    $rows = $statement->fetchAll(PDO::FETCH_ASSOC);
    $adminStatus = (boolean) $rows[0]['is_admin'];
?>

<body>
<div class="container">

    <?php
        define('IN_MY_PROJECT', true);
        include 'include/navigation_bar.php';
    ?>

    <!-- Main body content -->
    <div id="body_content">
        <div class="jumbotron"><h2>Registered Users <?php echo ($adminStatus == true ? '(Admin control)' : ''); ?></h2>
            <!-- table that shows people in database -->
           <table class="table table-striped">

                <thead>
                    <tr>
                        <th scope="col">Full Name</th>
                    </tr>
                </thead>

                <tbody>

                        <?php
                            if($adminStatus) {
                                echo '<form method="POST" action="profile.php">';
                                define('query_people', true);
                                include 'include/queryPeople.php';
                                echo '</form>';
                            } else {
                                echo '<form method="post" action="viewProfile.php">';
                                define('query_people', true);
                                include 'include/queryPeople.php';
                                echo '</form>';
                            }
                        ?>


                </tbody>

            </table>
        </div>
    </div>
</div>

<?php
    require '../scripts/include/bootstrap-scripts.php';
?>
</body>
</html>