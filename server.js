const express = require('express');
const app = express();
const PORT = process.env.PORT || 1337;

app.set('view engine', 'ejs');

var routes = require('./api/routes/pillRoutes');
routes(app);


app.listen(1337, () => console.log("Running on port: " + PORT));