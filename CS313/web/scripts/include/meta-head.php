<?php
    // REQUIRED VARIABLES
    /*
        $CSSLOC = "location of CSS file"
        $SCRIPTLOC = "location of script file"
        $BOOTSTRAP = boolean; Integrate bootstrap CDN
        $TITLE = title of page
    */
    if(empty($CSSLOC)) { $CSSLOC = "#"; }
    if(empty($SCRIPTLOC)) { $SCRIPTLOC = "#"; }
    if(empty($TITLE)) { $TITLE = "Untitled Page"; }
    if(empty($BOOTSTRAP)){
        $BOOTSTRAP = NULL;
    } else {
        $BOOTSTRAP = "<link rel=\"stylesheet\" href=\"https://stackpath.bootstrapcdn.com/bootstrap/4.1.1/css/bootstrap.min.css\" integrity=\"sha384-WskhaSGFgHYWDcbwN70/dfYBj47jz9qbsMId/iRN3ewGhXQFZCSftd1LZCfmhktB\" crossorigin=\"anonymous\">";
    }
    echo '<!DOCTYPE html>
    <html lang="en">
    <head>
        <!-- Meta data -->
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
        ' . $BOOTSTRAP . '
        <!-- User Defined Data: DECLARE VARIABLES BEFORE USE -->
        <title>' . $TITLE . '</title>
        <link rel="stylesheet" type="text/css" media="screen" href="' . $CSSLOC . '" />
        <script src="' . $SCRIPTLOC . '"></script>
    </head>';
?>