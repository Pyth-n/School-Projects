<?php
    // Use this only if request is from the form
    if($_SERVER['REQUEST_METHOD'] === 'POST') {
        $name = $_POST['nameInput'];
        $email = $_POST['emailInput']; 
        $major = $_POST['major']; 
        $comment = $_POST['comment'];
        
        if(!empty($name)) {echo "Name: " . $name . "<br>";}
        if(!empty($email)){echo "Email: " . $email . "<br>";}
        if(!empty($major)){echo "Major: " . $major . "<br>";}
        if(!empty($comment)){echo "Comment: " . $comment . "<br>";}
        
        print_r($_POST['Continent']);
        $con = $_POST['Continent'];

        echo "You've visited the following continents: ";

        $N = count($con);
        for ($i = 0; $i < $N; $i++) {
            echo($con[$i] . ", ");
        }

    } else {
        echo "Don't hack";
    }
?>