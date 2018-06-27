// Use express
const express = require('express');
const app = express();
app.set('view engine', 'ejs');

app.use(express.static('imgs'));
app.use('/style', express.static('public'));
app.use('/script', express.static('public'));

app.get('/', function(req, res) {
    res.render('home');
    res.end();
});

app.get('/projects', function(req, res) {
    res.render('projects');
    res.end();
});

app.get('/contact', function(req, res) {
    res.render('contact');
});

app.listen(1337);