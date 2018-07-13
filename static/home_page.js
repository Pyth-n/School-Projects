$(document).ready(function() {
    // Prevent submission with submit button

    $('#addPill').click(toggleAddForm);

    $('#addPillButton').click(pillFormController);

});

var daysData = {
        sunday: false,
        monday: false,
        tuesday: false,
        wednesday: false,
        thursday: false,
        friday: false,
        saturday: false
}

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

        verifyCheckboxes(daysData, function(data) {
            console.log(data);
        })
    });
    
}

// Verify add pill form input. Check if name and amount are present
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

// Checks checkmarks, callback function returns days JSON
function verifyCheckboxes(data, cb) {
    // Check which checkbox are checked
    $('div .form-check input[type=checkbox]').each(function() {
        // Update JSON if it is checked
        if (this.checked) {
            data[$(this).val()] = true;
        }        
    });

    // return that json
    if (typeof cb === "function")
        cb(JSON.stringify(data, null, 3));
}