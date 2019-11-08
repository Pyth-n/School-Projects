var items = 0;
var totalPrice = 0.00;

var albums = [
	[
		"The Beatles: Past Masters",
		4.99,
		0
	],
	[
		"With the Beatles: Remastered",
		5.99,
		0
	],
	[
		"Dark Side of the Moon",
		6.99,
		0
	],
	[
		"Pink Floyd: The Wall",
		5.99,
		0
	],
	[
		"Cash",
		5.99,
		0
	],
	[
		"Daft Punk: Homework",
		6.99,
		0
	]
];

// Updates cart with price, and also the number of items to purchase
function updateCart(albumNum){
	
	// Check if it was checked
	var verifyCheck = document.getElementsByClassName('albums')[albumNum].checked;
	if (verifyCheck == true){
		items += 1;
		albums[albumNum][2] += 1;
		// Let's set total price
		totalPrice += albums[albumNum][1];
	}
	else{
		items -= 1;
		albums[albumNum][2] -= 1;
		totalPrice -= albums[albumNum][1];
	}
	
	// Show button if at least one item is selected
	if (items > 0)
		document.getElementById('details').style.display = "inline";
	else
		document.getElementById('details').style.display = "none";

	// Update cart number
	document.getElementById('cart').innerHTML = items;
}

function tax(){
	// Compute Tax
	var total = totalPrice * 1.08;
	document.getElementById('tax').innerHTML = total.toFixed(2);
	return total.toFixed(2);
}

function parseOrder(){
	for (var i = 0; i < albums.length; i++){
		if (albums[i][2] > 0){
			document.getElementById('toPurchase').innerHTML += 
			"<div style='width:200px; display:inline'>" + albums[i][0] + "</div>" 
			+ "<span style='margin-left:30px'>" + albums[i][1] 
			+ "</span><span style='margin-left:30px'>" + albums[i][2] + "<br />";
		}
	}
	tax();
}

// Hides catalog, shows form 
function checkingOut(){
	document.getElementsByClassName('text')[0].style.display = "none";
	document.getElementsByClassName('text')[1].style.display = "block";
	parseOrder();
}

function verifyName(name, errorCheck){
	if (name.match(/^([a-z || A-Z]{1,})$/g))
		document.getElementById(errorCheck).style.visibility = "hidden";
	else
		document.getElementById(errorCheck).style.visibility = "visible";
}

function validateState(state, errorCheck){
	// I tried to split this in half, but it resulted in a buggy output so 
	// not to sure how to split long regex
	if (state.match(/^(\s*)(A[LKZR]|C[AOT]|DE|FL|GA|HI|I[DLNA]|K[SY]|LA|M[EDAINSOT]|N[EVHJMYCD]|O[HKR]|PA|RI|S[CD]|T[NX]|UT|V[TA]|W[AVIY])(\s*)$/g)){
		document.getElementById(errorCheck).style.visibility = 'hidden';
	}
	else{
		document.getElementById(errorCheck).style.visibility = 'visible';
	}
}

function validateZip(zip, errorCheck){
	if (zip.match(/^\d{5}$/g))
		document.getElementById(errorCheck).style.visibility = 'hidden';
	else
		document.getElementById(errorCheck).style.visibility = 'visible';
}

function validateAddress(address, errorCheck){
	if (address.match(/^.{1,}$/g))
		document.getElementById(errorCheck).style.visibility = 'hidden';
	else
		document.getElementById(errorCheck).style.visibility = 'visible';
}

function validatePhone(phone, errorCheck){
	if (phone.match(/^(\d{3}-\d{3}-\d{4})$/g))
		document.getElementById(errorCheck).style.visibility = 'hidden';
	else
		document.getElementById(errorCheck).style.visibility = 'visible';
}

function creditCard(cNumber, errorCheck){
	if (cNumber.match(/^\s*\d{4}\s*\d{4}\s*\d{4}\s*\d{4}\s*$/g))
		document.getElementById(errorCheck).style.visibility = 'hidden';
	else
		document.getElementById(errorCheck).style.visibility = 'visible';
}

function validateExp(cDate, errorCheck){
	if (cDate.match(/^(\d{2}\/\d{2})$/g))
		document.getElementById(errorCheck).style.visibility = 'hidden';
	else
		document.getElementById(errorCheck).style.visibility = 'visible';
}

function validateType(){
	var card = document.getElementById('cardType').selectedIndex;
	if (card == 0)
		document.getElementById('error7').style.visibility = 'visible';
	else
		document.getElementById('error7').style.visibility = 'hidden';
}

function resetForm(){
	console.log("Form was reset: Items still in cart");
}

function submitForm(){
	alert("Order submitted\nTotal: " + tax());
}

function resetForms(){
	document.getElementById('form1').reset();
	document.getElementById('details').style.display = "none";
}