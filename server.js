// Setup express and app
const express = require('express');
const app = express();
const path = require('path');
app.set('view engine', 'ejs');

// setup sessions
const session = require('express-session');
app.use(session({
    secret: 'tmp',
    resave: false,
    saveUninitialized: true
}));



// Body parser
const bodyParser = require('body-parser');
app.use(bodyParser.urlencoded({
    extended: true
}));
app.use(bodyParser.json());

// Get PORT
const PORT = process.env.PORT || 1337;

// Use static files
app.use('/', express.static(path.join(__dirname, 'static')));

var routes = require('./api/routes/pillRoutes');
routes(app);

var toSchedule = require('./schedule');
toSchedule();

app.listen(PORT, () => console.log("Running on port: " + PORT));