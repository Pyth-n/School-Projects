$(document).ready(function() {
    $('#addPill').click(function() {
        if($('#pillForm').is(":hidden")) {
            console.log("invisible");
            $('#pillForm').removeAttr('hidden');
        } else {
            $('#pillForm').attr('hidden', 'hidden');
        }
    })

    

});