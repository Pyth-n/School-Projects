<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="utf-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <title>David Perez's Homepage</title>
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    <!-- Bootstrap CDN -->
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.1/css/bootstrap.min.css" integrity="sha384-WskhaSGFgHYWDcbwN70/dfYBj47jz9qbsMId/iRN3ewGhXQFZCSftd1LZCfmhktB" crossorigin="anonymous">
    <link rel="stylesheet" type="text/css" media="screen" href="styles/main.css" />
    <script src="#"></script>
</head>

<body>
    <!-- Alert indicating future cookies -->
    <div class="alert alert-warning alert-dismassable fade show" role="alert" style="margin-bottom:0px">
        <strong>NOTE:</strong> Cookies will be used soon!
        <button type="button" class="close" data-dismiss="alert" aria-label="Close">
      <span aria-hidden="true">&times;</span>
    </button>
    </div>

    <!-- Main body -->
    <div class="container rounded-bottom">

        <!-- Navigation bar -->
        <nav class="navbar navbar-expand-sm navbar-light bg-light rounded">
        <div class="container-fluid">
            <a class="navbar-brand" href="#">CS 313</a>
            <button class="navbar-toggler" aria-expanded="false" aria-controls="navbarsExample09" aria-label="Toggle navigation" type="button" data-toggle="collapse" data-target="#navbarsExample09">
          <span class="navbar-toggler-icon"></span>
        </button>
            <div class="collapse navbar-collapse" id="navbarsExample09">
                <ul class="navbar-nav mr-auto">
                    <li class="nav-item active">
                        <a class="nav-link" href="#">Home <span class="sr-only">(current)</span></a>
                    </li>
                    <li class="nav-item dropdown">
                        <a class="nav-link dropdown-toggle" id="dropdown09" aria-expanded="false" aria-haspopup="true" href="https://example.com" data-toggle="dropdown">Assignments</a>
                        <div class="dropdown-menu" aria-labelledby="dropdown09">
                            <a class="dropdown-item disabled" href="#">Coming soon!</a>
                            <a class="dropdown-item" href="/assignments/hello.php">Hello</a>
                        </div>
                    </li>
                </ul>

            </div>
            </div>
        </nav>

        <!-- Bread crumbs -->
        <nav aria-label="breadcrumb" style="margin-top:2px">
            <ol class="breadcrumb">
                <li class="breadcrumb-item active" aria-current="page"><img src="/home.svg" alt="home"></li>
            </ol>
        </nav>

        <!-- Jumbotron for about me section -->
        <div class="jumbotron">
            <h2>About Me</h2>
            <hr />

            <!-- Media heading -->
            <div class="media">
                <img class="mr-3" src="imgs/image.jpg" alt="Generic placeholder image">
                <div class="media-body">
                    <h5 class="mt-0">David Perez</h5>
                    Welcome to my home page! This web page will host various pages for the assignments that I complete throughout CS 313
                </div>
            </div>

            <!-- PHP -->
            <?php
                echo "The time is: " . date("h:i:sa");
            ?>

        </div> <!-- //jumbotron -->
        
        <!-- My Interests -->
        <div class="jumbotron">
            <h2>Interests</h2>
            <hr />

            <div id="carouselExampleIndicators" class="carousel slide" data-ride="carousel">
                <ol class="carousel-indicators">
                    <li data-target="#carouselExampleIndicators" data-slide-to="0" class="active"></li>
                    <li data-target="#carouselExampleIndicators" data-slide-to="1"></li>
                    <li data-target="#carouselExampleIndicators" data-slide-to="2"></li>
                </ol>
                <div class="carousel-inner">
                    <div class="carousel-item active">
                    <img class="d-block w-100" src="imgs/mario.jpg" alt="First slide">
                        <div class="carousel-caption d-none d-md-block">
                            <h5>Mario Odyssey</h5>
                            <p>Classic.</p>
                        </div>
                    </div>
                    <div class="carousel-item">
                        <img class="d-block w-100" src="imgs/rocketleague.jpg" alt="Second slide">
                        <div class="carousel-caption d-none d-md-block">
                            <h5>Rocket League</h5>
                            <p>There is something intriguing about chasing a ball, especilly in a car.</p>
                        </div>
                    </div>
                    <div class="carousel-item">
                        <img class="d-block w-100" src="imgs/switch.jpg" alt="Third slide">
                        <div class="carousel-caption d-none d-md-block">
                            <h5>Nintendo Switch</h5>
                            <p>This has been my main gaming console. I love its versatility.</p>
                        </div>
                    </div>
                </div>
                <a class="carousel-control-prev" href="#carouselExampleIndicators" role="button" data-slide="prev">
                    <span class="carousel-control-prev-icon" aria-hidden="true"></span>
                    <span class="sr-only">Previous</span>
                </a>
                <a class="carousel-control-next" href="#carouselExampleIndicators" role="button" data-slide="next">
                    <span class="carousel-control-next-icon" aria-hidden="true"></span>
                    <span class="sr-only">Next</span>
                </a>
            </div>

        </div>

    </div> <!-- /container -->

    <script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js" integrity="sha384-ZMP7rVo3mIykV+2+9J3UJ46jBk0WLaUAdn689aCwoqbBJiSnjAK/l8WvCWPIPm49" crossorigin="anonymous"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.1.1/js/bootstrap.min.js" integrity="sha384-smHYKdLADwkXOn1EmN1qk/HfnUcbVRZyYmZ4qpPea6sjB/pTJ0euyQp0Mk8ck+5T" crossorigin="anonymous"></script>
</body>

</html>