// Compute rates
var total = null;
module.exports = function (weight, mailType, res) {
    // Switch to determine function to call
    switch (mailType) {
        case 'lettersStamped':
            total = lettersStamped(weight);
            mailType = "Letters (stamped)";
            break;
        case 'lettersMetered':
            total = lettersMetered(weight);
            mailType = "Letters (metered)";
            break;
        case 'largeEnvelopes':
            total = largeEnvelopes(weight);
            mailType = "Large Envelopes";
            break;
        case 'firstClass':
            total = firstClass(weight);
            mailType = "First-Class Package Service - Retail";
            break;
    }

    console.log("Your total price is: " + total);

    var params = {weight: weight, mailType: mailType, total:total};
    res.render('rate_results', params);
}

function lettersStamped(weight) {
    if (weight > 3.5) { return 1.13; }
    if (weight > 3) { return 0.92; }
    if (weight > 2) { return 0.71; }
    if (weight > 0 ) { return 0.50; }
}

function lettersMetered(weight) {
    if (weight > 3.5) { return 1.10; }
    if (weight > 3) { return 0.89; }
    if (weight > 2) { return 0.68; }
    if (weight > 0 ) { return 0.47; }
}

function largeEnvelopes(weight) {
    if (weight > 13) { return 3.52; }
    if (weight > 12) { return 3.31; }
    if (weight > 11) { return 3.10; }
    if (weight > 10) { return 2.89; }
    if (weight > 9) { return 2.68; }
    if (weight > 8) { return 2.47; }
    if (weight > 7) { return 2.26; }
    if (weight > 6) { return 2.05; }
    if (weight > 5) { return 1.84; }
    if (weight > 4) { return 1.63; }
    if (weight > 3) { return 1.42; }
    if (weight > 2) { return 1.21; }
    if (weight > 1) { return 1.00; }
}

function firstClass(weight) {
    if (weight > 13) { return 5.50; }
    if (weight > 12) { return 5.15; }
    if (weight > 11) { return 4.80; }
    if (weight > 10) { return 4.45; }
    if (weight > 9) { return 4.10; }
    if (weight > 5) { return 3.75; }
    if (weight > 1) { return 3.50; }
}