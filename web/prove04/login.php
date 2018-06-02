<?php
$TITLE = "Login";
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
        <h1>Login</h1>


        <!-- Login form -->
        <form action="authenticate.php" method="post">
            <div class="form-group">
                <label for="exampleInputEmail1">Email address</label>
                <input type="email" class="form-control" aria-describedby="emailHelp" placeholder="Enter email">
            </div>
            <div class="form-group">
                <label for="exampleInputPassword1">Password</label>
                <input type="password" class="form-control" placeholder="Password">
            </div>

            <button type="submit" class="btn btn-primary">Sign in</button>
            <br><br>
            <small class="form-text text-muted">Not registered? Click <a href="register.php">here</a> to sign up.</small>

        </form>

    </div>
</div>

<?php
    require '../scripts/include/bootstrap-scripts.php';
?>
</body>
</html>
