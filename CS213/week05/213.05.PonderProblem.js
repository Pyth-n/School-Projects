// For problem 1
function problem1(){
	// Say hi
	console.log("Hello World");
}

// For problem 2
function problem2(newName, text){
	// Replace the pattern with the new name
	var replace = text.replace(/\w\w\w\w\_\w\w\w/g, newName);
	console.log(replace);
}

// For problem 3
function problem3(fahr){
	// Convert then display fahrenheit to celsius
	var celsius = ((fahr - 32) * 5) / 9;
	console.log(celsius.toFixed(1));
}

// For problem 4
function problem4(weight){
	// Switch will return a price depending on weight
	switch(weight)
	{
		case '1':
			console.log("$" + 0.98);
			break;
		case '2':
			console.log("$" + 1.19);
			break;
		case '3':
			console.log("$" + 1.40.toFixed(2));
			break;
		case '4':
			console.log("$" + 1.61);
			break;
		case '5':
			console.log("$" + 1.82);
			break;
		default:
			console.log("Invalid weight");
	}
}

// For problem 5
function problem5(apr, term, amount){
	// Let's convert these first
	apr = Number(apr) / 100;
	term = Number(term);
	amount = Number(amount);

	// We'll loop through the terms
	for (var i = 1; i <= term; i++)
	{
		// Then increase the total amount
		amount = amount * (1 + apr);
	}
	// Finally, print results
	console.log("$" + amount.toFixed(2));
}