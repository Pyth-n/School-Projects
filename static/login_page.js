$(document).ready(function(){
    $('#loginButton').click(login);
    

});

function login() {
    const email = $('#email').val();
    const password = $('#password').val();

    // If input is missing, show danger text
    if (checkInput(email, password)) {
        return;
    }

    

    console.log(email + ':' + password);
}

function checkInput(email, password) {
    $('#emptyPassword').attr('hidden', 'hidden');
    $('#emptyEmail').attr('hidden', 'hidden');

    if((email.length < 3) || (password.length < 1)) {
        if(email.length < 3) {
            $('#emptyEmail').removeAttr('hidden');
        } 

        if (password.length < 1) {
            $('#emptyPassword').removeAttr('hidden');
        } 
        return true;
    }
}
