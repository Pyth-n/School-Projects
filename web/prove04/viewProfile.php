<?php
// Make sure people are logged in before accessing website
session_start();

$visiting = null;

if ($_SESSION['authenticated'] != true || !isset($_SESSION['id'])) {
    session_unset();
    session_destroy();
    header('Location: login.php');
    die();
}

define('USE_DB', true);
require 'include/connectDB.php';

$statement = $db->prepare('SELECT first_name, last_name, popularity, profile_picture_path FROM users WHERE id=:id');

if(isset($_GET['profileId'])) {
    $visiting = $_GET['profileId'];
    $statement->bindValue(':id', (int) $visiting, PDO::PARAM_INT);
} else if(isset($_POST['viewProfile'])) {
    $visiting = $_POST['viewProfile'];
    $statement->bindValue(':id', (int) $visiting, PDO::PARAM_INT);
} else {
    $statement->bindValue(':id', (int) $_SESSION['id'], PDO::PARAM_INT);
}

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
                <div class="dropdown" id="uploadButton">
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
                <?php
                if (isset($visiting)) {
                    echo '<script>';
                    echo 'var elem = document.getElementById("uploadButton");';
                    echo 'elem.parentElement.removeChild(elem);';
                    echo '</script>';
                }
                ?>
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
                    <div class="dropdown col-5" align="right" id="picUploadButton">
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

                    <?php
                    if (isset($visiting)) {
                        echo '<script>';
                        echo 'var elem = document.getElementById("picUploadButton");';
                        echo 'elem.parentElement.removeChild(elem);';
                        echo '</script>';
                    }
                    ?>

                    <div class="dropdown col-2" align="right" id="vidUploadButton">
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

                    <?php
                    if (isset($visiting)) {
                        echo '<script>';
                        echo 'var elem = document.getElementById("vidUploadButton");';
                        echo 'elem.parentElement.removeChild(elem);';
                        echo '</script>';
                    }
                    ?>

                </div>

                <div class="container" align="center" style="; border: 1px solid black;">
                    <!-- The wall -->
                    <?php
                    define('USE_DB', true);
                    require_once 'include/connectDB.php';

                    $queryID = null;
                    if(isset($visiting)) {
                        $queryID = (int) $visiting;
                    } else {
                        $queryID = $_SESSION['id'];
                    }

                    // Display images and comments
                    foreach ($db->query('SELECT image_path, title, id, image_likes, description FROM images WHERE user_uploaded_id=' . $queryID) as $row) {
                        echo '<div>';
                        echo '<h4 align="left" style="margin-top:20px">' . $row['title'] . ' (' . $row['image_likes'] . ')</h4> ';
                        echo '<em>' . $row['description'] . '</em>';
                        echo '<img src="' . $row['image_path'] . '"" class="img-fluid">' ;

                        // display comments from this image
                        foreach ($db->query('SELECT comment, user_commented FROM image_comments WHERE image_commented=' . $row['id']) as $comment) {
                            $queryName = 'SELECT first_name, last_name FROM users WHERE id=:ucid';
                            $nameStatement = $db->prepare($queryName);
                            $nameStatement->bindValue(':ucid', $comment['user_commented'], PDO::PARAM_INT);
                            $nameStatement->execute();
                            $nameRow = $nameStatement->fetchAll(PDO::FETCH_ASSOC);
                            echo '<div class="container" align="left" style="padding: 10px 0px 10px 0px">';
                            echo '<strong>';
                            echo $nameRow[0]['first_name'] . ' ' . $nameRow[0]['last_name'] . ': ';
                            echo '</strong>';
                            echo $comment['comment'] . '<br>';
                        }

                        // Make comment form
                        echo '<form action="database/uploadComment.php" method="post" align="left">';
                        echo '<input type="text" name="pictureComment" placeholder="Comment" class="form-control">';
                        echo '<input type="hidden" name="pictureID" value="' . $row['id'] . '">';
                        if(isset($visiting)) {
                            echo '<input type="hidden" name="visiting" value="' . $visiting . '">';
                        }
                        echo '<button type="submit" class="btn btn-primary" name="pictureCommentSubmit">Post</button>';
                        echo '<button type="submit" class="btn btn-success" name="pictureLike">+</button>';
                        echo '<button type="submit" class="btn btn-danger" name="pictureDislike">-</button>';
                        echo '</form>';
                        echo '</div>';
                    }

                    // Display videos and comments
                    foreach ($db->query('SELECT video_path, title, id, video_likes, description FROM videos WHERE user_uploaded_id=' . $queryID) as $row) {
                        $vidSrc = $row['video_path'];

                        echo '<div class="embed-responsive-4by3" style="margin-top:20px">';
                        echo '<h4 align="left" >' . $row['title'] . ' (' . $row['video_likes'] . ')</h4>';
                        echo '<em>' . $row['description'] . '</em>';
                        echo '<video class="embed-responsive-item" width="320" height="240" controls>';
                        echo '<source src="' . $vidSrc . '" type="video/mp4">';
                        echo '</video><br>';

                        // display comments from this image
                        foreach ($db->query('SELECT comment, user_commented FROM video_comments WHERE video_commented=' . $row['id']) as $comment) {
                            $queryName = 'SELECT first_name, last_name FROM users WHERE id=:ucid';
                            $nameStatement = $db->prepare($queryName);
                            $nameStatement->bindValue(':ucid', $comment['user_commented'], PDO::PARAM_INT);
                            $nameStatement->execute();
                            $nameRow = $nameStatement->fetchAll(PDO::FETCH_ASSOC);
                            echo '<div class="container" align="left" style="padding: 10px 0px 10px 0px">';
                            echo '<strong>';
                            echo $nameRow[0]['first_name'] . ' ' . $nameRow[0]['last_name'] . ': ';
                            echo '</strong>';
                            echo $comment['comment'] . '<br>';
                        }

                        // Make comment form
                        echo '<form action="database/uploadComment.php" method="post" align="left">';
                        echo '<input type="text" name="videoComment" placeholder="Comment" class="form-control">';
                        echo '<input type="hidden" name="videoID" value="' . $row['id'] . '">';
                        if(isset($visiting)) {
                            echo '<input type="hidden" name="visiting" value="' . $visiting . '">';
                        }
                        echo '<button type="submit" class="btn btn-light" name="videoCommentSubmit">Post</button>';
                        echo '<button type="submit" class="btn btn-success" name="videoLike">+</button>';
                        echo '<button type="submit" class="btn btn-danger" name="videoDislike">-</button>';
                        echo '</form>';
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