// Use express
const express = require('express');
const app = express();

// Get PORT from environment or use a hard-coded one
const PORT = process.env.PORT || 1337;

// Using EJS as viewing engine
app.set('view engine', 'ejs');

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

app.listen(PORT, () => console.log("Running on port: " + PORT));