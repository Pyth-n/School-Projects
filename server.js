// Setup express and app
const express = require('express');
const app = express();
app.set('view engine', 'ejs');

// Body parser
const bodyParser = require('body-parser');
app.use(bodyParser.urlencoded({
    extended: true
}));
app.use(bodyParser.json());

// Get PORT
const PORT = process.env.PORT || 1337;


var routes = require('./api/routes/pillRoutes');
routes(app);


app.listen(PORT, () => console.log("Running on port: " + PORT));