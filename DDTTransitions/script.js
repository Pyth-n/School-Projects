function createTransition() {
	// See which radio button is selected
	var shape, text, duration, methodOfTrigger;
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

	// Way to trigger
	var triggerRadios = document.getElementsByName('trigger');
	for (var i = 0; i < triggerRadios.length; i++) {
		if (triggerRadios[i].checked) {
			methodOfTrigger = triggerRadios[i].value;
			break;
		}
	}
	console.log("Trigger: " + methodOfTrigger);

	// Create the div
	var div = document.createElement("DIV");
	var node = document.createTextNode(text + ": " + methodOfTrigger);
	div.appendChild(node);
	div.setAttribute("onmouseover", "forTransition(this)");
	div.setAttribute("onmouseout", "revertTransition(this)");
	div.setAttribute("style", "background-color: black; color: white;")
	div.style.width = shape;
	div.style.height = "100px";
	document.getElementById('masterBox').appendChild(div);
	div.style.transition = "width " + duration + "s";
}

function forTransition(val) {
	
}

function revertTransition(val) {

}