<?php
     defined('query_people') || die("You don't have access to view this file!");

     define("USE_DB", true);
    require 'connectDB.php';

     // Query a list of all the user's full name. Inserted in a table.
    foreach($db->query('SELECT id, first_name, last_name FROM users') as $row) {
        echo '<tr>';

        echo '<td>';
        echo '<button class="btn btn-link" role="link" type="submit" name="viewProfile" value="' . $row['id'] . '">';
        echo $row['first_name'] . " " . $row['last_name'];
        echo '</button>';

        echo '</td>';

//        echo '<td><a href="profile.php?user=' . $row['id'] . '">' . $row['first_name'] . " " . $row['last_name'] . '</a></td>';
        echo '</tr>';
    }
?>