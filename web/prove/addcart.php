<?php
    require 'itemsInStock.php';

    $cookie_count = 0;
    $itemCount = count($items);

    for($i = 0; $i < $itemCount; $i++) {
        if($items[$i][2] == $_COOKIE[$items[$i][2]]) {
            $cookie_count++;
            echo '<li class="dropdown-item disabled" href="#">
                <span class="item">
                    <span class="item-left">
                        <img src="' . $items[$i][0] . '" class="img-fluid cart-image">
                        <span class="item-info">
                            <span>' . $items[$i][3] . '</span>
                            <span>$' . $items[$i][1] . '</span>
                        </span>
                    </span>
                    <span class="item-right">
                        <button type="submit" class="btn btn-xs btn-danger pull-right" name="removeitem" form="form2" value="' . $items[$i][2] . '"><img src="../trash.svg"> </button>
                    </span>
                
                </span>';
        }
    }
?>