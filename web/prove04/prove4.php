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

/*    $statement = $db->prepare('SELECT image_path FROM images WHERE user_uploaded_id=:id');
    $statement->bindValue(':id', (int) $_SESSION['id'], PDO::PARAM_INT);
    $statement->execute();

    $ROWS2 = $statement->fetchAll(PDO::FETCH_ASSOC);*/
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

                                <div class="form-group" align="right">
                                    <input type="file" name="file" id="pictureFile" class="inputfile" accept=".jpg,.jpeg,.gif">
                                    <label for="file" class="btn btn-info">+</label>
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

                                <div class="form-group" align="right">
                                    <input type="file" name="file" id="" class="inputfile">
                                    <label for="file" class="btn btn-info">+</label>
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

                    <!-- The wall -->
                    <img src="../imgs/mario.jpg" class="img-fluid">
                </div>
            </div>

<!--            <div class="dropdown">
                <a class="btn btn-secondary dropdown-toggle" href="#" role="button" id="dropdownMenuLink" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
                    Dropdown link
                </a>

                <form class="dropdown-menu p-4">
                    <div class="form-group">
                        <label for="exampleDropdownFormEmail2">Email address</label>
                        <input type="email" class="form-control" id="exampleDropdownFormEmail2" placeholder="email@example.com">
                    </div>
                    <div class="form-group">
                        <label for="exampleDropdownFormPassword2">Password</label>
                        <input type="password" class="form-control" id="exampleDropdownFormPassword2" placeholder="Password">
                    </div>
                    <div class="form-check">
                        <input type="checkbox" class="form-check-input" id="dropdownCheck2">
                        <label class="form-check-label" for="dropdownCheck2">
                            Remember me
                        </label>
                    </div>
                    <button type="submit" class="btn btn-primary">Sign in</button>
                </form>
            </div>-->


        </div>
</div>

<?php
    require '../scripts/include/bootstrap-scripts.php';
?>
</body>
</html>