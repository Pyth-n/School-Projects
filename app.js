// Setup express and ejs
const app = require('express')();
app.set('view engine', 'ejs');

// Parse package
const url = require('url');

const PORT = process.env.PORT || 1337;

// Calculation export
var computeRate = require('./pkg/computeRate');

app.get('/prove09', function(req, res) {
    console.log("Curled");
    res.render('postal_rate_form');
});

app.get('/calculateRate', function(req, res) {
    handleRate(req, res);
    res.end();
});

// Get GET variables
function getVariables(req) {
    return url.parse(req.url, true);
}

// Handle GET rate
function handleRate(req, res) {
    var variables = getVariables(req);

    var weight = variables.query.weight;
    var mailType = variables.query.mailType;

    computeRate(weight, mailType, res);
}



app.listen(PORT, () => console.log("Running on port: " + PORT));
