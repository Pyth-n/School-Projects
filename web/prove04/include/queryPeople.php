<?php
     defined('query_people') || die("You don't have access to view this file!");

     try {
         $dbUrl = getenv('DATABASE_URL');
         $dbopts = parse_url($dbUrl);

         // Get url options from parsed
         $dbHost = $dbopts['host'];
         $dbPort = $dbopts['port'];
         $dbUser = $dbopts['user'];
         $dbPassword = $dbopts['pass'];
         $dbName = ltrim($dbopts['path'], '/');

         $db = new PDO("pgsql:host=$dbHost;port=$dbPort;dbname=$dbName", $dbUser, $dbPassword);

         $db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
     } catch (PDOException $ex) {
         echo 'ERROR!: ' . $ex->getMessage();
     }

     // Query a list of all the user's full name. Inserted in a table.
    foreach($db->query('SELECT first_name, last_name FROM users') as $row) {
        echo '<tr>';
        echo '<td>'. $row['first_name'] . " " . $row['last_name'] . '</td>';
        echo '</tr>';
    }
?>