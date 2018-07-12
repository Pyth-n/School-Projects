$(document).ready(function() {
    $('#addPill').click(toggleAddForm);
});

function toggleAddForm() {
    if($('#pillForm').is(":hidden")) {
        console.log("invisible");
        $('#pillForm').removeAttr('hidden');
    } else {
        $('#pillForm').attr('hidden', 'hidden');
    }
}

// TODO: 