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
    <div class="container" id="body_content">
        <div class="jumbotron">
            <h1>Hi</h1>
        </div>
    </div>
</div>

<?php
    require '../scripts/include/bootstrap-scripts.php';
?>
</body>
</html>