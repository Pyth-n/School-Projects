<?php
    define('USE_DB', true);
    require 'connectDB.php';
    
    $SEARCH_QUERY = strtolower($SEARCH_QUERY);
    $statement = $db->prepare('SELECT * FROM users WHERE LOWER(last_name)=:last_name');
    $statement->bindValue(':last_name', $SEARCH_QUERY, PDO::PARAM_STR);
    $statement->execute();

    $ROWS = $statement->fetchAll(PDO::FETCH_ASSOC);

    foreach($ROWS as $results) {
        echo '<tr>';

        echo '<td>';
        echo '<button class="btn btn-link" role="link" type="submit" name="viewProfile" value="' . $results['id'] . '">';
        echo $results['first_name'] . " " . $results['last_name'];
        echo '</button>';

        echo '</td>';
        echo '</tr>';
    }
?>