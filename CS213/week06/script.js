/*
	Author: David Perez
	Note: Used the match() to check regex instead of searching. More modular approach (I think)
*/

function age(myAge, myClass){
	// Let's verify myAge
	if (myAge.match(/^(\d|[1-9]\d|10[0-9]|11[0-8])$/g)){
		document.getElementsByClassName(myClass)[0].style.visibility = 'hidden';
	}
	else{
		document.getElementsByClassName(myClass)[0].style.visibility = 'visible';
	}
}

function sSecurity(myNum, myClass){
	if(myNum.match(/^\s*\d{3}\-\d{2}\-\d{4}\s*$/g)){
		document.getElementsByClassName(myClass)[0].style.visibility = 'hidden';
	}
	else{
		document.getElementsByClassName(myClass)[0].style.visibility = 'visible';
	}
}

function creditCard(myDate, myClass){
	if (myDate.match(/^\s*\d{4}\s*\d{4}\s*\d{4}\s*\d{4}\s*$/g)){
		document.getElementsByClassName(myClass)[0].style.visibility = 'hidden';
	}
	else{
		document.getElementsByClassName(myClass)[0].style.visibility = 'visible';
	}
}

function validateDate(myDate, myClass){
	if (myDate.match(/^(\s*)(0?[1-9]|1[0-2])\/(0?[1-9]|(1|2)\d|3[0-1])\/(175[3-9]|17[6-9]\d|(18|19|20)\d{2}|2100)\s*$/g)){
		document.getElementsByClassName(myClass)[0].style.visibility = 'hidden';
	}
	else{
		document.getElementsByClassName(myClass)[0].style.visibility = 'visible';
	}
}

function validateState(state, myClass){
	// I tried to split this in half, but it resulted in a buggy output so 
	// not to sure how to split long regex
	if (state.match(/^(\s*)(A(L|K|Z|R)|C(A|O|T)|DE|FL|GA|HI|I(D|L|N|A)|K(S|Y)|LA|M(E|D|A|I|N|S|O|T)|N(E|V|H|J|M|Y|C|D)|O(H|K|R)|PA|RI|S(C|D)|T(N|X)|UT|V(T|A)|W(A|V|I|Y))(\s*)$/g)){
		document.getElementsByClassName(myClass)[0].style.visibility = 'hidden';
	}
	else{
		document.getElementsByClassName(myClass)[0].style.visibility = 'visible';
	}
}

function validateMoney(money, myClass){
	if (money.match(/^(\s*)(\$?)(\d,\d{3}|\d{1,3})(\.\d{2})?(\s*)$/g)){
		document.getElementsByClassName(myClass)[0].style.visibility = 'hidden';
	}
	else{
		document.getElementsByClassName(myClass)[0].style.visibility = 'visible';
	}
}
