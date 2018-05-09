<?php

    $itemValues = 3;
    $items = array(
        array("https://media.nintendo.com/nintendo/bin/wcfCyAd7t2N78FkGvEwCOGzVFBNQRbhy/AvG-_d4kEvEplp0mJoUew8IAg71YQveM.png",
            "59.99", "DKC"),
        array("https://media.nintendo.com/nintendo/bin/PqHlEWHNhL2mPNm6WE-ri95xMGxw-zzQ/0lslRCvuTZjKN2Sbt7Iu425Pcy6Rcef3.png",
            "59.99", "XC2"),
        array("https://media.nintendo.com/nintendo/bin/UkfHxHRJqBFa_g0kZAX0pPxi88OlpDJU/9vFfu_FAeX6Z7exumULKv5ZAfLiw99mH.png",
            "59.99", "KSA"),
        array("https://media.nintendo.com/nintendo/bin/SmENxSXqVepjMBF5NxYddvUr6gSfLeDn/qSG2l7_qvitLVncMwzncZbBoqANeYYL6.png",
            "59.99", "SMO"),
        array("https://media.nintendo.com/nintendo/bin/7mJ77M9tNuPL2CFJm3cpqnd9mL4u1EfA/gsOigHCTONwhOcPHcfxwpTx2UaV_m6On.png",
            "59.99", "BOTW"),
        array("https://media.nintendo.com/nintendo/bin/5ilkA0Fdb524PxC-MeU6u5xV1d_of7be/aRcKLbRChTkJ7FbNIBu3oLiGwJSeaUUT.png",
            "59.99", "MCD8")

    );

    $itemCount = count($items);

    echo '<div class="row" id="games">';
    for($i = 0; $i < $itemCount; $i++) {
        echo '<div class="col-sm-3 bord" align="center"> <img src="' . $items[$i][0] .
            '" class="img-fluid">' .
            '<br>$' . $items[$i][1] .
            '<span class="buttonBox"><br><button type="button" class="btn btn-light">Add to cart</button> </span></div>';

    }
    echo '</div>';
?>

