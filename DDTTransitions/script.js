function createTransition() {
	// See which radio button is selected
	var shape, text, duration, property;
	var radios = document.getElementsByName('shape');
	for (var i = 0; i < radios.length; i++) {
		if (radios[i].checked) {
			shape = radios[i].value;
			break;
		}
	}
	console.log("Shape: " + shape);

	// Get input text
	var text = document.getElementById('inputText').value;
	console.log("Text: " + text);

	// Get duration
	var duration = document.getElementById('inputDuration').value;
	console.log("Duration: " + duration);

	// Get property
	propertyRadio = document.getElementsByName('cssProperty');
	for (var i = 0; i < propertyRadio.length; i++) {
		if (propertyRadio[i].checked) {
			property = propertyRadio[i].value;
		}
	}
	console.log("Property: " + property);

	// Create the div
	var div = document.createElement("DIV");
	var node = document.createTextNode(text);
	var nodeProp = document.createTextNode("Property: " + property);
	var nodeShape = document.createTextNode("Shape: " + shape);
	var nodeDur = document.createTextNode("Duration: " + duration + "s");
	div.appendChild(node);
	div.appendChild(document.createElement("BR"));
	div.appendChild(nodeProp);
	div.appendChild(document.createElement("BR"));
	div.appendChild(nodeDur);
	div.setAttribute("onmouseover", "forTransition(this)");
	div.setAttribute("style", "background-color: black; color: white;")
	div.style.width = shape;
	div.style.height = "100px";
	document.getElementById('masterBox').appendChild(div);

	// Special case with properties
	if (property == "both") {
		div.style.transition = "width " + duration + "s" + ", height " + duration + "s";
	} else {
		div.style.transition = property + " " + duration + "s";
		console.log(div.style.transition = property + " " + duration + "s");
	}
	
}

function forTransition(val) {
	val.style.width = "200px";
	val.style.height = "200px";
}
