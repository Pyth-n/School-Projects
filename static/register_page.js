$(document).ready(function() {
    $('#registerUser').click(createUser);
});

/*
    Create a user with a POST request to /register
*/
function createUser() {
    const password = $('#password').val();
    const cp = $('#confirm_password').val();

    // Do passwords match?
    var doPasswordsMatch = passwordsMatch(password, cp);

    // If passwords don't match, don't create user!
    if(!doPasswordsMatch) {
        return;
    }

    const firstName = $('#first_name').val();
    const lastName = $('#last_name').val();
    const email = $('#email').val();   
    var isSpanish = false;

    // If checkbox is checked, spanish is desired
    if ($('#is_spanish').is(":checked")) {
        isSpanish = true;
    } 

    // Prepare the JSON to be sent
    var data = {
        user: {
            fn: firstName,
            ln: lastName,
            email: email,
            password: password,
            english: !isSpanish
        }
    }

    // Send POST request to /register endpoint
    $.post('/register', data, function(result) {
        console.log(result);
        switch (result.error) {
            case 'email':
                $('#emailUsed').removeAttr('hidden');
                break;
            default:
                // By default, redirect the user to /login GET
                $(location).attr('href', result.path + '?email=' + result.email);
                break;
        }
    });
}

/*
    Check if passwords match. Show wrong password text if they do not match
*/
function passwordsMatch(first, second) {
    // if passwords do NOT match
    if ($('#password').val() !== $('#confirm_password').val()) {
        $('#wrongPassword').removeAttr('hidden');
        return false;
    } 
    // if passwords DO match
    else {
        $('#wrongPassword').attr('hidden','hidden');
        return true;
    }
}
