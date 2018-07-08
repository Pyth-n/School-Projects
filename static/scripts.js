$(document).ready(function() {
    $('#registerUser').click(createUser);
});

function createUser() {
    const firstName = $('#first_name').val();
    const lastName = $('#last_name').val();
    const email = $('#email').val();
    const password = $('#password').val();
    const cp = $('#confirm_password').val();
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
            cp: cp,
            english: isSpanish
        }
    }

    console.log("First name: " + firstName);
    console.log("Last name: " + lastName);
    console.log("email: " + email);
    console.log("PW: " + password + ':' + cp);
    console.log("Spanish: " + !isSpanish);

    $.post('/register', data, function(result) {
        console.log(result);
    });

}