<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
	<meta charset="UTF-8" />
	<title>
	<?php 
		$name = $_POST['firstname'];
		echo $name . " 's Order Review";
	?>
	</title>
	<link rel="stylesheet" href="style/style.css" />

	<style>
	.text p a{
		color: black;
	}
	</style>
</head>
<body>
	<div class="document">
      <div id="title">
         <h1><a href="index.html">Music Store</a></h1>
      </div>
      <div class="content">
         <!-- Navigation Links -->
         <div class="menu">
            <ul id="list">
               <li class="item"><a href="index.html">Home</a></li>
               <li class="item"><a href="shop/shop.html">Shop</a></li>
               <li class="item" style="float:right;"><a href="#">Cart <span id="cart">0</span></a></li>
            </ul>
         </div>
      </div>
      <!-- Main text -->
      <form action="confirm.php" method="post" id="formReview">
      <div class="text">
         <p style="text-indent:0px;"><a href="index.html">home</a> > review</p>
         <h2 style="text-align:center">Purchase Review</h2>
        
        <?php
        // Get data from form
		$albums = $_POST['album'];
		$total = 0;
		$firstName = $_POST['firstname'];
		$lastName = $_POST['lastname'];
		$address = $_POST['address'];
		$state = $_POST['state'];
		$zip = $_POST['zip'];
		$phoneNumber = $_POST['phonenumber'];
		$creditCard = $_POST['creditcard'];
		$expiration = $_POST['expiration'];
		$ccType = $_POST['ccType'];
		$date = date_create($_POST['expiration']);
		// Display this review 
		echo "<p><strong>Name: </strong>$firstName $lastName</p>";
		echo "<p><strong>Address: </strong>$address, $state $zip</p>";
		echo "<p><strong>Phone Number: </strong>$phoneNumber</p>";
		echo "<p><strong>Payment: </strong>$ccType</p>";
		echo "<p><strong>Expiration: </strong>" . date_format($date, "F/Y") . "</p>";
		echo "<h3 style='color:black;'>Items</h3>";


		if (empty($albums))
		{
			echo "<h1>EMPTY!</h1>";
		}
		else
		{
			$n = count($albums);
			//echo "Selected $n door(s): ";
			for($i = 0; $i < $n; $i++)
			{
				//echo ($albums[$i] . " ");
				// write a switch here too add up the total
				switch ($albums[$i])
				{
					case "beatles":
						$price = 4.99;
						echo "<p>The Beatles - Past Masters - $price</p>";
						$total += $price;
						break;
					case "beatles2":
						$price = 5.99;
						echo "<p>The Beatles - Collection - $price</p>";
						$total += $price;
						break;
					case "floyd":
						$price = 6.99;
						echo "<p>Pink Floyd - The Dark Side - $price</p>";
						$total += 6.99;
						break;
					case "floyd2":
						$price = 4.99;
						echo "<p>Pink Floyd - The Wall - $price</p>";
						$total += $price;
						break;
					case "cash":
						$price = 5.99;
						echo "<p>Cash - $price</p>";
						$total += $price;
						break;
					case "daft":
						$price = 6.99;
						echo "<p>Daft Punk - Homework - $price</p>";
						$total += $price;
						break;
				}
			}
		}
		echo "<p><strong>Total: </strong>$total</p>";
		?>
      
      <input type="submit" value="Submit" name="submitted"/>
      <input type="submit" value="Cancel"/>
      </div>
      </form>
      <div id="footer">
         &copy; Music Store
      </div>
   </div>

</body>
</html>