// Use express
const express = require('express');
const app = express();

// Get PORT from environment or use a hard-coded one
const PORT = process.env.PORT || 1338;

// Get GMAILAPP environment variable to send email
const GMAILAPP = process.env.GMAILAPP;

// Using EJS as viewing engine
app.set('view engine', 'ejs');

// Body parser for POST data
const bodyParser = require('body-parser');

app.use(bodyParser.urlencoded({
    extended: true
}));

app.use(bodyParser.json());

// Use for email
var nodemailer = require('nodemailer');

var transporter = nodemailer.createTransport({
    service: 'gmail',
    auth: {
        user: '3dgar.p@gmail.com',
        pass: GMAILAPP
    }
});

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

    var mailOptions = {
        from: req.body.user.email,
        to: '3dgar.p@gmail.com',
        subject: 'Portfolio Contact',
        text: req.body.user.message + '<br>Email: ' + req.body.user.email + '<br>' + 'Name: ' + req.body.user.name
    };

    transporter.sendMail(mailOptions, function(error, info) {
        if (error) {
            throw error;
        } else {
            console.log('Email sent: ' + info.response);
        }
    });

    res.render('sent', params);
    res.end();
});

app.get('/test', function(req, res) {
    console.log(process.env.GMAILAPP);
    res.end();
});

app.listen(PORT, () => console.log("Running on port: " + PORT));