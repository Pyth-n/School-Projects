function animateDiv() {
	var animationType, duration, delay, iteration, curve;
	var direction = "normal";

	// Get the number inputs
	duration = document.getElementsByName('durationTime')[0].value;
	delay = document.getElementsByName('delayTime')[0].value;
	iteration = document.getElementsByName('iterationCount')[0].value;
	if (iteration == 10) {
		iteration = "infinite";
	}

	// Get the radios
	var animationRadio = document.getElementsByName('animationType');
	for(var i = 0; animationRadio.length; i++) {
		if (animationRadio[i].checked) {
			animationType = animationRadio[i].value;
			break;
		}
	}

	var directionRadio = document.getElementsByName('directionType');
	for(var i = 0; i < directionRadio.length; i++) {
		if(directionRadio[i].checked) {
			direction = directionRadio[i].value;
		}
	}

	var curveRadio = document.getElementsByName("speed");
	for (var i = 0; i < curveRadio.length; i++) {
		if (curveRadio[i].checked) {
			curve = curveRadio[i].value;
			console.log(curve);
		}
	}

	addDiv(animationType, duration, delay, iteration, direction, curve);
}

function addDiv(animationType, duration, delay, iteration, direction, curve) {
	
	var div = document.createElement("DIV");
	div.setAttribute("style", "background-color:black; animation: " + animationType + " " + duration + "s"
		+ " " + curve + " " + delay + "s" + " " + iteration + " " + direction);
	div.style.width = "100px";
	div.style.height = "100px";
	document.getElementById("boxWrap").appendChild(div);
}

function clearDiv() {
	var node = document.getElementById('boxWrap');
	while (node.hasChildNodes()) {
		node.removeChild(node.lastChild);
	}
}