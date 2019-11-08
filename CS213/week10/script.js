
function test(file){
	// Display the stuff
	var xhttp = new XMLHttpRequest();

	xhttp.onreadystatechange = function() {
		if (this.readyState == 4 && this.status == 200){
			document.getElementById("text").innerHTML = "<pre>" + xhttp.responseText + "</pre>";
		}
		else{
			document.getElementById("text").innerHTML = "";
		}
	}
	xhttp.open("GET",file,true);
	xhttp.send();

}

function student(lol){
	// URL is one directory above
	var url = "../" + lol;
	var xhttp = new XMLHttpRequest();

	// Function is ran if xhttp request is successful
	xhttp.onreadystatechange = function() {
		if (this.readyState == 4 && this.status == 200)
		{

			// Make table headers
			var text = "<tr><th>Name</th><th>Address</th><th>Major</th><th>GPA</th></tr>";
			// Parse file response
			var parsedObj = JSON.parse(xhttp.responseText);
			
			// Loop through, add info to table
			for (var i = 0; i < parsedObj.students.length; i++){
				text += "<tr><td>" + parsedObj.students[i].first + " " + 
				parsedObj.students[i].last + "</td>" + "<td>" + parsedObj.students[i].address.city
				+ ", " + parsedObj.students[i].address.state + " " + parsedObj.students[i].address.zip 
				+ "</td>" + "<td>" + parsedObj.students[i].major + "</td>" + "<td>" +
				parsedObj.students[i].gpa + "</td></tr>";
				
			}
			document.getElementById('text2').style.display = "inline";
			document.getElementById("text3").innerHTML = text;
		}

	}
	
	xhttp.open("GET", url, true);
	xhttp.send();
	
}