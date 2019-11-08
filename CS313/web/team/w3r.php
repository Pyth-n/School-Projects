<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="utf-8" />

    <title>Team 03</title>

    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    
    <link rel="stylesheet" type="text/css" media="screen" href="#" />
    <script src="#"></script>
</head>
<body>

    <form action="scripts/w3.php" method="POST" id="w3form">
        <!-- Name and e-mail -->
        Name <input type="text" name="nameInput"><br>
        Email <input type="text" name="emailInput"><br>

        <br>
        <pre>Choose a major:</pre>


        <?php
            $major = array(
                array("CS", "Computer Science"),
                array("WD", "Web Design and Development"),
                array("CIT", "Computer Information Technology"),
                array("CE", "Computer Engineering")
            );

            for($i = 0; $i < 4; $i++) {
                for($x = 0; $x < 2; $x++) {
                    switch($x) {
                        case 0:
                            $value = $major[$i][$x];
                            echo "<input type=\"radio\" name=\"major\" value=\"$value\">";
                            break;
                        case 1:
                            echo $major[$i][$x] . "<br>";
                            break;
                        default:
                            break;
                    }
                }
            }
        ?>

        
        <br>
        <pre>Comment:</pre>
        <textarea name="comment" form="w3form" placeholder="Enter text"></textarea>
        <br>

        <pre>Continent you've visited:</pre>
        <input type="checkbox" name="Continent[]" value="NA">North America
        <input type="checkbox" name="Continent[]" value="SA">South America
        <input type="checkbox" name="Continent[]" value="EU">Europe
        <input type="checkbox" name="Continent[]" value="AS">Asia
        <input type="checkbox" name="Continent[]" value="AU">Australia
        <input type="checkbox" name="Continent[]" value="AF">Africa
        <input type="checkbox" name="Continent[]" value="AN">Antarctica
        <br>

        <input type="submit" value="hit me">
    </form>

    

</body>
</html>