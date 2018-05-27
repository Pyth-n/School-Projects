<?php
    $TITLE = "Prove 04 - Querying Data";
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
            <h1>Welcome!</h1>
            <p>Please use the search button to search for profiles. Use the 'People' link
            above to see users in the database.</p>
        </div>
</div>

<?php
    require '../scripts/include/bootstrap-scripts.php';
?>
</body>
</html>