<?php
// Make sure people are logged in before accessing website
session_start();
if ($_SESSION['authenticated'] != true) {
    header('Location: login.php');
}
?>
<?php
$TITLE = "Prove 04 - Search";
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
            <h2>Search results for '<?php echo $_GET['searchQuery']; ?>'</h2>

            <!-- table that shows people in database -->
            <table class="table table-striped">

                <thead>
                <tr>
                    <th scope="col">Full Name</th>
                </tr>
                </thead>

                <tbody>
                <form method="POST" action="profile.php">
                    <?php
                    $SEARCH_QUERY = "none";
                    if(isset($_GET['searchQuery'])) {
                        $SEARCH_QUERY = $_GET['searchQuery'];
                    }

                    include 'include/querySearch.php';
                    ?>
                </form>

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