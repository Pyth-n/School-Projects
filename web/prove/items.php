<?php

    $items = NULL;

    if ($PAGESEL == "MAINST"){
        $items = array(
            array("https://media.nintendo.com/nintendo/bin/wcfCyAd7t2N78FkGvEwCOGzVFBNQRbhy/AvG-_d4kEvEplp0mJoUew8IAg71YQveM.png",
                59.99, "DKC"),
            array("https://media.nintendo.com/nintendo/bin/PqHlEWHNhL2mPNm6WE-ri95xMGxw-zzQ/0lslRCvuTZjKN2Sbt7Iu425Pcy6Rcef3.png",
                59.99, "XC2"),
            array("https://media.nintendo.com/nintendo/bin/UkfHxHRJqBFa_g0kZAX0pPxi88OlpDJU/9vFfu_FAeX6Z7exumULKv5ZAfLiw99mH.png",
                59.99, "KSA"),
            array("https://media.nintendo.com/nintendo/bin/SmENxSXqVepjMBF5NxYddvUr6gSfLeDn/qSG2l7_qvitLVncMwzncZbBoqANeYYL6.png",
                59.99, "SMO"),
            array("https://media.nintendo.com/nintendo/bin/7mJ77M9tNuPL2CFJm3cpqnd9mL4u1EfA/gsOigHCTONwhOcPHcfxwpTx2UaV_m6On.png",
                59.99, "BOTW"),
            array("https://media.nintendo.com/nintendo/bin/5ilkA0Fdb524PxC-MeU6u5xV1d_of7be/aRcKLbRChTkJ7FbNIBu3oLiGwJSeaUUT.png",
                59.99, "MCD8")
        );
    } else {
        $items = array(
            array("//media.nintendo.com/nintendo/bin/BhITPyOUFDpMFX86GI0eTBz3HETPFTOo/tt2ihzlt7kqrAtIeZccBHNy9r0oEDTmO.png",
                "19.99", "CELESTE"),
            array("//media.nintendo.com/nintendo/bin/9V3-twd3YsRzzDZVp5n8WfN7gBreaZLA/6GjxyrmHed2OYNYqSji4Qz9O6aq8dW30.png",
                14.99, "SV"),
            array("https://media.nintendo.com/nintendo/bin/wbdYoMekzxot8h0otwqB0Tuv6Onxv8gO/ls44tcdURxOP1tbcAvkmvxpFMC-ZiWWL.png",
                19.99, "OSE"),
            array("https://media.nintendo.com/nintendo/bin/hS-2GbcDOYsqzMc5jzGAVbVAvoiaQpVv/r5pCJTtCF_PyNMoAjmmnvHDUhf7ujMPd.png",
                19.99, "OXF"),
            array("https://media.nintendo.com/nintendo/bin/RxtQWoFzbNXF0xkIOHT5mYlAT-JNrHX0/QW8GTbuZibnOhRJMy9DX74F5HGq68oE1.png",
                19.99, "FE"),
            array("//media.nintendo.com/nintendo/bin/OalVHoSpVXYWOegJev_oF2RQyP2fxWzQ/0t4xcrWsowkf8-m29Q-tV2uu31tvXuyG.png",
                19.99, "NINE")
        );
    }


    $itemCount = count($items);

    echo '<div class="row" id="games">';

    for($i = 0; $i < $itemCount; $i++) {
        echo '<div class="col-sm-3 bord" align="center"> <img src="' . $items[$i][0] .
            '" class="img-fluid">' .
            '<br>$' . $items[$i][1] .
            '<span class="buttonBox"><br><button type="submit" form="form1" class="btn btn-light" name="purchase" value="' .
            $items[$i][2] . '">Add to cart</button> </span></div>';
    }

    echo '</div>';
?>

