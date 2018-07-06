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

module.exports = pool;