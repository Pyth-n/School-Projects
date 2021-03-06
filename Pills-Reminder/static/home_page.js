$(document).ready(function () {
    // Prevent submission with submit button
    verifyTimeInput();
    $('#addPill').click(toggleAddForm);
    $('#daily').click(dailyCheck);
    $('#addPillButton').click(pillFormController);
    $('.edit-pill').click(pillEdit);
    $('#edit-cancel').click(cancelEdit);
    $('#edit-pill').click(saveEdit);
    $('#edit-delete').click(deletePill);
    $('#delete-account').click(deleteAccount);
    $('#logOut').click(logOut);
});

var pillData = {
    user: {
        pill_name: null,
        amount: null,
        strength: null,
        remaining: null,
        hour: null,
        minute: null
    },
    daysData: {
        sunday: false,
        monday: false,
        tuesday: false,
        wednesday: false,
        thursday: false,
        friday: false,
        saturday: false    
    }
}

var config = {
    pillID: null
}

function toggleAddForm() {
    if ($('#pillForm').is(":hidden")) {
        $('#pillForm').removeAttr('hidden');
    } else {
        $('#pillForm').attr('hidden', 'hidden');
    }
}

function pillFormController() {
    verifyTextInput(pillData, (err, pillJson) => {
        if (err) return;
        
        addTimeToJson(pillData, (err, timeJson) => {
            verifyCheckboxes(pillData.daysData, function (dataJson) {
                
                // POST pill
                let ID = getID();
                $.post('/home/' + ID + '/pill', pillData, function(result) {
                    console.log(result);
                    location.reload();
                }).fail(function(err) {
                    console.log("Failed");
                });
            })
        });
    });
}

// TODO: Update HOUR and MINUTE on json
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
        if (pillName == '') {
            $('#pillNameError').removeAttr('hidden');
        }

        if (amount == '') {
            $('#pillAmountError').removeAttr('hidden');
        }
        cb(true, null);
        return;
    }

    data.user.pill_name = pillName;
    data.user.amount = amount;

    if (strength != '') {
        data.user.strength = strength;
    } else {
        data.user.strength = null;
    }
    if (left != '') {
        data.user.remaining = left;
    } else {
        data.user.remaining = null;
    }

    cb(false, JSON.stringify(data.user, null, 3));
}

function addTimeToJson(data, cb) {
    var hour = null;
    var minute = $('#minute').val();

    // Ensure hour isn't empty
    if ($('#hour').val() == '') {
        $('#hour').val(1);
        
    }

    // Correct minutes from 0-9 to prepend a 0
    if($('#minute').val() >= 0 || $('#minute').val() <=9) {
        //$('#minute').val('0' + $('#minute').val());
        minute = "0" + $('#minute').val();
    }
    if (minute.length > 2) {
        minute = minute[1] + minute[2];
    }

    

    data.user.hour = amOrPM($('#hour').val());
    data.user.minute = minute;

    if (typeof cb == "function"){
        cb(false, data.user);
    }
}


function amOrPM (hour) {
    var inputHour = hour;
    var newHour = null;

    if($('#PM').is(':checked')) {
        var mod = inputHour % 12;
        newHour = mod + 12;
                
    } else {
        if (hour == 12) {
            newHour = 0;
        } else {
            newHour = hour;
        }
        
    }
    return newHour;
}

function verifyTimeInput() {
    var hour = null;
    var minute = null;

    // Reject key E - +
    $('#hour').keypress(function (e) {
        var keyPressed = e.originalEvent.code;

        switch (keyPressed) {
            case 'KeyE':
            case 'Minus':
            case 'Equal':
                e.preventDefault();
                break;
        }
    });

    // Reject key E - +
    $('#minute').keypress(function (e) {
        var keyPressed = e.originalEvent.code;

        switch (keyPressed) {
            case 'KeyE':
            case 'Minus':
            case 'Equal':
                e.preventDefault();
                break;
        }
    });

    // Sanitize hours
    $('#hour').keyup(function (e) {
        if ($(this).val() > 12) {
            $(this).val(12);
        }

        if ($(this).val() < 0) {
            $(this).val(1);
        }
    })

    // Sanitize minutes
    $('#minute').keyup(function (e) {
        if ($(this).val() < 0) {
            $(this).val("00");
        }

        if ($(this).val() >= 60) {
            $(this).val(59)
        }
        if ($(this).val().length > 2) {
            $(this).val("00");
        }
    })
}

// Checks checkmarks, callback function returns days JSON
function verifyCheckboxes(data, cb) {
    // Check which checkbox are checked
    $('div .form-check input[type=checkbox]').each(function () {
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

function dailyCheck() {
    if (this.checked) {
        console.log("chekd");
        $('form .form-check-input').attr('checked', 'checked');
    } else {
        $('form .form-check-input').removeAttr('checked');
    }
}

function logOut(e) {
    console.log("Logging out...");

    $.get('/logout', (result) => {
        $(location).attr('href', result.nextPath);
    })
}

// Pill Edit buttons
function pillEdit(e) {
    let pillID = e.target.id;
    config.pillID = pillID;

    let ID = getID();
    $.get('/home/' + ID + '/pill/' + pillID, function(result) {
        $('#pill-body').attr('hidden','hidden');

        // Set values
        $('#pillName-edit').val(result.data.pill_name);
        $('#pillAmount-edit').val(result.data.amount);
        $('#pillStrength-edit').val(result.data.strength);
        $('#pillRemaining-edit').val(result.data.remaining);

        $('#pill-edit').removeAttr('hidden');
    })
}

// Sends a PUT request to edit pill
function saveEdit(e) {
    let ID = getID();
    let pillID = config.pillID;

    $.ajax({
        url: '/home/' + ID + '/pill/' + pillID,
        type: 'PUT',
        data: {
            pill_id: pillID,
            pill_name: $('#pillName-edit').val(),
            pill_amount: $('#pillAmount-edit').val(),
            pill_strength: $('#pillStrength-edit').val(),
            remaining: $('#pillRemaining-edit').val()
        },
        success: function(result) {
            $('#pill-edit').attr('hidden', 'hidden');
            $('#pill-body').removeAttr('hidden');
            location.reload();  
        }
    });
}

function cancelEdit(e) {
    $('#pill-edit').attr('hidden', 'hidden');
    $('#pill-body').removeAttr('hidden');
}

// get the ID of the current user
function getID() {
    let currentURL = (document.URL);
    let part = currentURL.split("/");
    let index = part.length - 1;
    let ID = part[index];
    return ID;
}

// Delete pill
function deletePill(e) {
    let ID = getID();
    let pillID = config.pillID;

    $.ajax({
        url: '/home/' + ID + '/pill/' + pillID,
        type: 'DELETE',
        success: function(result) {
            $('#pill-edit').attr('hidden', 'hidden');
            $('#pill-body').removeAttr('hidden');
            location.reload(); 
        }
    })
}

function deleteAccount(e) {
    let ID = getID();

    $.ajax({
        url: '/register/' + ID,
        type: 'DELETE',
        success: function(result) {
            $(location).attr('href', '/');
        }
    })

}