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

// Setup PostgreSQL
const { Pool, Client } = require('pg');
const pgcredentials = process.env.DATABASE_URL;

// Initialize pool
const pool = new Pool({
    connectionString: pgcredentials,
});

// If error, exit app
pool.on('error', (err, client) => {
    process.exit(-1);
});

var routes = require('./api/routes/pillRoutes');
routes(app, pool);


app.listen(PORT, () => console.log("Running on port: " + PORT));