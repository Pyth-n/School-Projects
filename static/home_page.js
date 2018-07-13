$(document).ready(function() {
    $('#addPill').click(toggleAddForm);

    

});

function toggleAddForm() {
    if($('#pillForm').is(":hidden")) {
        $('#pillForm').removeAttr('hidden');
    } else {
        $('#pillForm').attr('hidden', 'hidden');
    }
}

// TODO: 