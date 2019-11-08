<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
	<meta charset="UTF-8" />
	<title>
		Confirmation
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
      <div class="text">
         <p style="text-indent:0px;"><a href="index.html">home</a> > confirmation</p>
        
        <?php
       		if(isset($_POST['submitted'])) {
       			echo "<h2>Order successful</h2>";
       		}
       		else {
       			echo "<h2>Order cancelled</h2>";
       		}
		?>
      </div>

      <div id="footer">
         &copy; Music Store
      </div>
   </div>

</body>
</html>