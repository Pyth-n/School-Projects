function translateDiv() {
	var x = document.getElementsByName('translate')[0].value;
	var y = document.getElementsByName('translate')[1].value;
	document.getElementById('translate').style.transform = "translate(" + x + "px,"
	+ y + "px)";
}

function rotateDiv() {
	var deg = document.getElementsByName('rotate')[0].value;
	document.getElementById('rotate').style.transform = "rotate(" + deg + "deg)";
	console.log("Degree: " + deg);
}

function scaleDiv() {
	var w = document.getElementsByName('scale')[0].value;
	var y = document.getElementsByName('scale')[1].value;
	document.getElementById('scale').style.transform = "scale(" + w + ", " + y + ")";
	console.log(w + ", " + y);
}

function skewDiv() {
	var x = document.getElementsByName('skewX')[0].value;
	document.getElementById('skewX').style.transform = "skewX(" + x + "deg)";
}

function skewYDiv() {
	var x = document.getElementsByName('skewY')[0].value;
	document.getElementById('skewY').style.transform = "skewY(" + x + "deg)";
}

function rotateXDiv() {
	var x = document.getElementsByName('rotateX')[0].value;
	document.getElementsByClassName('threeD')[0].style.transform = "rotateX(" + x + "deg)";
	console.log(x);
}

function rotateYDiv() {
	var y = document.getElementsByName('rotateY')[0].value;
	document.getElementsByClassName('threeD')[1].style.transform = "rotateY(" + y + "deg)";
	console.log(y);
}