$(document).ready(function() {
    // Prevent submission with submit button

    $('#addPill').click(toggleAddForm);

    $('#addPillButton').click(pillFormController);

});

function toggleAddForm() {
    if($('#pillForm').is(":hidden")) {
        $('#pillForm').removeAttr('hidden');
    } else {
        $('#pillForm').attr('hidden', 'hidden');
    }
}

function pillFormController() {
    verifyTextInput((err) => {
        if (err) return;
        console.log("Continuing in callback...");
    });
    var days = verifyCheckboxes();
    //console.log("Controller days: " + days);
}

// TODO: Verify add pill form input. Check if name and amount are present
function verifyTextInput(cb) {
    // Reset error
    $('#pillNameError').attr('hidden', 'hidden');
    $('#pillAmountError').attr('hidden', 'hidden');

    const pillName = $('#pillName').val();
    const amount = $('#pillAmount').val();
    // console.log("Name; " + pillName + " amount: " + amount);
    const strength = $('#pillStrength').val();
    const left = $('#pillRemaining').val();
    // console.log('strength: ' + strength + ' left: ' + left);

    const hour = $('#hour').val();
    const minute = $('#minute').val();
    // console.log('hour: ' + hour + ' minute: ' + minute);

    if ((pillName == '') || (amount == '')) {
        if (pillName == ''){
            $('#pillNameError').removeAttr('hidden');
        }

        if (amount == '') {
            $('#pillAmountError').removeAttr('hidden');
        }
        cb(true);
        return;
    }

    cb(false);
}

function verifyCheckboxes(err, cb) {
    // JSON files for day booleans
    let days = {
        sunday: false,
        monday: false,
        tuesday: false,
        wednesday: false,
        thursday: false,
        friday: false,
        saturday: false
    }

    // Check which checkbox are checked
    $('div .form-check input[type=checkbox]').each(function() {
        // If it's checked
        if (this.checked) {
            days[$(this).val()] = true;
        }

        
    }, cb(null, JSON.stringify(days)));

    // return that json
    
}