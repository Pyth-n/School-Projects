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

    if ($('#is_spanish').is(":checked")) {
        isSpanish = true;
    } 

    var data = {
        user: {
            fn: firstName,
            ln: lastName,
            email: email,
            password: password,
            english: !isSpanish
        }
    }

    $.post('/register', data, function(result) {
        console.log(result);
    });

}

/*
    Check if passwords match. Show wrong password text if they do not match
*/
function passwordsMatch(first, second) {
    if ($('#password').val() !== $('#confirm_password').val()) {
        console.log("Passwords do not match!");
        $('#wrongPassword').removeAttr('hidden');
        return false;
    } else {
        console.log("Passwords match!")
        $('#wrongPassword').attr('hidden','hidden');
        return true;
    }
}