<!DOCTYPE html>
<html lang="en">
<head>
    <title>Welcome <?php echo $_POST["name"]; ?></title>
    <meta charset="utf-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">

</head>
<body>
    <?php
        if($_GET["color"]) {
            echo "Your favorite color is: " . $_GET["color"];
        }
    ?>
</body>
</html>