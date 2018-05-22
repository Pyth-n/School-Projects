<?php
$TITLE = "Confirmation";
$BOOTSTRAP = true;
$CSSLOC = "../styles/prove03.css";
$SCRIPTLOC = "script.js";
require '../scripts/include/meta-head.php';

?>

<body>

    <div class="container">
        <nav class="navbar navbar-expand-sm navbar-light bg-light rounded">

            <!-- Brand -->
            <a class="navbar-brand" href="prove3.php"><img id="logo1" src="https://seeklogo.com/images/N/nintendo-switch-logo-38D4F5C7E7-seeklogo.com.png">Gamez</a>

            <div class="navbar">
                <ul class="navbar-nav mr-auto">
                    <li class="nav-item active">
                        <a class="nav-link" href="prove3.php">Browse <span class="sr-only">(current)</span></a>
                    </li>
                </ul>
            </div>
        </nav>
    </div>

    <div class="container">
        <!-- Form here -->
        <form id="form4" action="confirm.php" method="post">
            <div class="form-group">
                <label for="inputAddress">Address</label>
                <input type="text" class="form-control" id="inputAddress" placeholder="1234 Main St" name="address">
            </div>
            <div class="form-row">
                <div class="form-group col-md-6">
                    <label for="inputCity">City</label>
                    <input type="text" class="form-control" id="inputCity" name="city">
                </div>
                <div class="form-group col-md-4">
                    <label for="inputState">State</label>
                    <select id="inputState" class="form-control" name="State">
                        <option selected>Choose state...</option>
                        <?php require 'stateOptions.php'; ?>
                    </select>
                </div>
                <div class="form-group col-md-2">
                    <label for="inputZip">Zip</label>
                    <input type="text" class="form-control" id="inputZip" name="zipcode">
                </div>
            </div>
        </form>

    </div>

    <div class="container" align="center">
        <button type="submit" form="form4" name="confirm" value="1" class="btn btn-primary btn-lg">Confirm</button>
        <button type="submit" form="form4" name="confirm" value="0" class="btn btn-light btn-lg">Cancel</button>
    </div>



</body>
</html>