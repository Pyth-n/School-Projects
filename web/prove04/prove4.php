<?php
// Make sure people are logged in before accessing website
    session_start();


    if ($_SESSION['authenticated'] != true || !isset($_SESSION['id'])) {
        session_unset();
        session_destroy();
        header('Location: login.php');
        die();
    }
    define('USE_DB', true);
    require 'include/connectDB.php';
    $statement = $db->prepare('SELECT first_name, last_name, popularity, profile_picture_path FROM users WHERE id=:id');
    $statement->bindValue(':id', (int) $_SESSION['id'], PDO::PARAM_INT);
    $statement->execute();

    $ROWS = $statement->fetchAll(PDO::FETCH_ASSOC);
?>
<?php
    $TITLE = "Home - Pixel";
    $BOOTSTRAP = true;

    $CSSLOC = "style.css";
    //$SCRIPTLOC = "";

    require '../scripts/include/meta-head.php';
?>

<body>
<div class="container">
    <?php
        define('IN_MY_PROJECT', true);
        include 'include/navigation_bar.php';
    ?>

    <!-- Main body content -->
        <div class="jumbotron">
            <div class="row">

                <!-- Profile info column -->
                <div class="col-sm-4" align="center">
                    <h1><?php
                        echo $ROWS[0]['first_name'] . ' ' . $ROWS[0]['last_name'];
                        ?></h1>
                    <img src="<?php echo $ROWS[0]['profile_picture_path']; ?>" class="img-fluid" />
                    <br />

                    <!-- Upload menu -->
                    <br>
                    <div class="dropdown">
                        <a class="btn btn-secondary btn-sm dropdown-toggle" href="#" role="button" id="uploadMenuLink" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
                            Upload
                        </a>
                        <form class="dropdown-menu p-4" action="uploadImage.php" method="post" enctype="multipart/form-data">
                            <div class="form-group" align="center">
                                <input type="file" name="file" id="file" class="inputfile">
                                <label for="file" class="btn btn-info">+</label>
                            </div>
                            <div align="center"><button type="submit" class="btn btn-success" >Upload</button></div>
                        </form>
                    </div>

                    <!-- Popularity -->
                    <small class="text-muted">Popularity: <?php echo $ROWS[0]['popularity']; ?> </small>
                </div>

                <!-- Profile content -->
                <div class="col-sm-8">
                    <div class="row">
                        <div class="col-4">
                            <h3>Pixels</h3>
                        </div>

                        <br>

                        <!-- Dropdown menus -->
                        <div class="dropdown col-5" align="right">
                            <!-- Pictures -->
                            <a class="btn btn-secondary btn-sm dropdown-toggle" href="#" role="button" id="uploadPixelLink" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
                                Pic
                            </a>
                            <form class="dropdown-menu dropdown-menu-right p-4" action="database/uploadPixel.php" method="post" enctype="multipart/form-data">
                                <small class="text-muted">*.jpg, *jpeg, *.gif</small>
                                <div class="form-group" align="right">
                                    <input type="file" name="file"> <br>
                                </div>

                                <div class="form-group">
                                    <input type="text" placeholder="Title *" required="true" name="title">
                                </div>

                                <div class="form-group">
                                    <input type="text" placeholder="Description" name="description">
                                </div>

                                <div align="center"><button type="submit" class="btn btn-success" name="submitPicture">Upload</button></div>
                            </form>
                        </div>

                        <div class="dropdown col-2" align="right">
                            <!-- Vid -->
                            <a class="btn btn-secondary btn-sm dropdown-toggle" href="#" role="button" id="uploadPixelLink" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
                                Vid
                            </a>

                            <form class="dropdown-menu dropdown-menu-right p-4" action="database/uploadPixel.php" method="post" enctype="multipart/form-data">
                                <small class="text-muted">*.mp4 <strong>NOTE: 12mb filesize limite</strong></small>
                                <div class="form-group" align="right">
                                    <input type="file" name="file" required="true">
                                </div>

                                <div class="form-group">
                                    <input type="text" placeholder="Title *" required="true" name="title">
                                </div>

                                <div class="form-group">
                                    <input type="text" placeholder="Description" name="description">
                                </div>

                                <div align="center"><button type="submit" class="btn btn-success" name="submitVideo">Upload</button></div>
                            </form>
                        </div>



                    </div>

                    <div align="center">
                    <!-- The wall -->
                    <?php
                    define('USE_DB', true);
                    require_once 'include/connectDB.php';
                        foreach ($db->query('SELECT image_path FROM images WHERE user_uploaded_id=24') as $row) {
                            echo '<div style="width:320px; height:300px; border: 1px solid black;">';
                            echo '<img src="' . $row['image_path'] . '"" class="img-fluid">' ;
                            echo '</div>';
                        }

                    ?>
                    </div>
                </div>
            </div>
        </div>
</div>

<?php
    require '../scripts/include/bootstrap-scripts.php';
?>
</body>
</html>