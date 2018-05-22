<?php
    defined('IN_MY_PROJECT') || die("This is a script: YOU DON'T HAVE ACCESS TO THIS FILE.");

    // If bootstrap is set to true
    if($BOOTSTRAP) {
        // Opening navigation
        echo '<nav class="navbar navbar-expand-sm navbar-light bg-light rounded">';

        // Navigation brand
        echo '<a class="navbar-brand" href="#"><img src="logo.png" style="width:100px; height:100px;"></a>';


        // Hamburger
        echo '<button class="navbar-toggler" aria-expanded="false" aria-controls="pixelMenu" 
                aria-label="Toggle navigation" type="button" data-toggle="collapse" data-target="#pixelMenu">
                <span class="navbar-toggler-icon"></span>
              </button>';

        // Opening Navigation Bar
        echo '<div class="collapse navbar-collapse" id="pixelMenu" >';

        // Home button
        echo  '<ul class="navbar-nav mr-auto">
                    <li class="nav-item active">
                        <a class="nav-link" href="prove4.php">Home <span class="sr-only">(current)</span></a>
                    </li>
               </ul>';




        // Closing Navigation Bar
        echo '</div>';
        // Search form
        echo '<form class="form-inline center_form" action="#">
                <input class="form-control mr-sm-1" type="text" placeholder="Name">
                <button class="btn btn-success" type="submit">Search</button>
              </form>';
        // Ending navigation
        echo '</nav>';
    }
?>