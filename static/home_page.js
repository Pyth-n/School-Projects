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

var pillData = {
    pill_name: null,
    amount: null,
    strength: null,
    remaining: null,
    hour: null,
    minute: null
}

function toggleAddForm() {
    if($('#pillForm').is(":hidden")) {
        $('#pillForm').removeAttr('hidden');
    } else {
        $('#pillForm').attr('hidden', 'hidden');
    }
}

function pillFormController() {
    verifyTextInput(pillData, (err, pillJson) => {
        if (err) return;
        console.log(pillJson);

        verifyCheckboxes(daysData, function(dataJson) {
            //console.log(dataJson);
            
        })
    });
}

// Verify add pill form input. Check if name and amount are present
function verifyTextInput(data, cb) {
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
        cb(true, null);
        return;
    }
    
    data.pill_name = pillName;
    data.amount = amount;
    
    if (strength != ''){
        data.strength = strength;
    } else {
        data.strength = null;
    }
    if (left != ''){
        data.remaining = left;
    } else {
        data.remaining = null;
    }


    cb(false, JSON.stringify(data, null, 3));
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

function clearForm() {
    $('form .form-control').val("");
    $('form .form-check-input').removeAttr('checked');
}