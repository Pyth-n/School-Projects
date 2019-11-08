<?php
    require 'itemsInStock.php';

    // Counts stock from itemsInStock.php
    $stockCount =  count($items);
    $totalCost = 0;

    for($i = 0; $i < $stockCount; $i++) {
        // Check if ID is in cookies
        if(isset($_COOKIE[$items[$i][2]])) {
            $totalCost += $items[$i][1];
            echo '<tr><th scope="row" class="remove">' . $items[$i][2] . '</th>';
            echo '<td>' . $items[$i][3] . '</td>';
            echo '<td>$' . $items[$i][1] . '</td>';
            echo '<td class="remove"><button type="submit" name="cancelCheckout" value="' . $items[$i][2] . '" form="removeItem" 
                class="btn btn-danger"><img src="../trash.svg"></button></td>';
            echo '</tr>';
        }
    }
?>