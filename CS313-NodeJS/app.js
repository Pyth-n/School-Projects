// Setup express and ejs
const app = require('express')();
app.set('view engine', 'ejs');

// Port will be from environment variable or 1337
const PORT = process.env.PORT || 1337;

var handleRate = require('./pkg/handleRate');

app.get('/prove09', function(req, res) {
    res.render('postal_rate_form');
});

app.get('/calculateRate', function(req, res) {
    handleRate(req, res);
    res.end();
});

app.listen(PORT, () => console.log("Running on port: " + PORT));