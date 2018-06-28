// Use express
const express = require('express');
const app = express();

// Get PORT from environment or use a hard-coded one
const PORT = process.env.PORT || 1337;

// Using EJS as viewing engine
app.set('view engine', 'ejs');

// Body parser for POST data
const bodyParser = require('body-parser');

app.use(bodyParser.urlencoded({
    extended: true
}));

app.use(bodyParser.json());

// Use these static files
app.use(express.static('imgs'));
app.use('/style', express.static('public'));
app.use('/script', express.static('public'));


// Homepage
app.get('/', function(req, res) {
    res.render('home');
    res.end();
});

// Projects
app.get('/projects', function(req, res) {
    res.render('projects');
    res.end();
});

// Contact
app.get('/contact', function(req, res) {
    res.render('contact');
});

// Send message
app.post('/send', function(req, res) {
    const params = { email: req.body.user.email, name: req.body.user.name, message: req.body.user.message };

    res.render('sent', params);
    res.end();
});

app.listen(PORT, () => console.log("Running on port: " + PORT));