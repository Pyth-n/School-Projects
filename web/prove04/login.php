<?php
$TITLE = "Login";
$BOOTSTRAP = true;

$CSSLOC = "style.css";
//$SCRIPTLOC = "";

require '../scripts/include/meta-head.php';
?>
<body>
<?php
    if($_GET['signout'] == true) {
        echo '<div class="alert alert-warning alert-dismissible fade show" role="alert">
          You have been signed out.
          <button type="button" class="close" data-dismiss="alert" aria-label="Close">
            <span aria-hidden="true">&times;</span>
          </button>
        </div>';
    } else if($_GET['signup'] == true) {
        echo '<div class="alert alert-warning alert-dismissible fade show" role="alert">
          You have been signed up.
          <button type="button" class="close" data-dismiss="alert" aria-label="Close">
            <span aria-hidden="true">&times;</span>
          </button>
        </div>';
    }
?>
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
                <label for="email">Email address</label>
                <input type="email" required="true" class="form-control" name="email" placeholder="Enter email">
            </div>
            <div class="form-group">
                <label for="password">Password</label>
                <input type="password" required="true" class="form-control" name="password" placeholder="Password">
                <?php
                    if($_GET['error'] == "password") {
                        echo '<small class="form-text text-danger">Wrong password</small>';
                    }
                ?>
            </div>

            <button type="submit" class="btn btn-primary">Sign in</button>
            <br><br>
            <small class="form-text text-muted">Not registered? <a href="register.php">Click here to sign up</a>.</small>

        </form>

    </div>
</div>

<?php
    require '../scripts/include/bootstrap-scripts.php';
?>
</body>
</html>
