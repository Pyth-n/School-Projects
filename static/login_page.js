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

    const data = {
        user: {
            email: email,
            password: password
        }
    }

    $.post('/', data, function(result) {
        if (result.success == true) {
            $(location).attr('href', result.nextPath);
        }
    }).fail(function(result) {
        console.log(result.responseJSON);
        $('#failedPassword').removeAttr('hidden');
    });
    
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
