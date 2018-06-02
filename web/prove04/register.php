<?php
$TITLE = "Register";
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
        <h1>Register</h1>


        <!-- Register form -->
        <form action="processRegistration.php" method="post">

            <div class="form-row">
                <div class="form-group col-md-6">
                    <label for="email">Email</label>
                    <input type="email" required="true" class="form-control" placeholder="Email" name="email">
                    <small class="form-text text-muted">Note: Email will never be published.</small>
                </div>


                <div class="form-group col-md-6">
                    <label for="password">Password</label>
                    <input type="password" required="true" class="form-control" placeholder="Password" name="password">
                </div>
            </div>

            <div class="form-row">
                <div class="form-group col-md-6">
                    <label for="firstName">First name</label>
                    <input type="text" required="true" class="form-control" placeholder="First name" name="firstName">
                </div>

                <div class="form-group col-md-6">
                    <label for="lastName">Last name</label>
                    <input type="text" required="true" class="form-control" placeholder="Last name" name="lastName">
                </div>
            </div>

            <button type="submit" class="btn btn-primary">Register</button>

        </form>
</div>
</div>

<?php
require '../scripts/include/bootstrap-scripts.php';
?>
</body>
</html>
