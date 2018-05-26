<?php
$TITLE = "Prove 04 - People";
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
            <h2>Registered Users</h2>

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
                            define('query_people', true);
                            include 'include/queryPeople.php';
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