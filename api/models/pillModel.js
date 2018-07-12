// Require DB connection and credential
const pool = require('../../sql/db_auth');
const transaction = require('./transactionFunction');

// Bcrypt used to salt and hash passwords
const bcrypt = require('bcrypt');

// Setup crypto: used to store a random session token
const crypto = require('crypto');

// Check email
exports.is_email_available = function(data, cb) {
    const retrieveEmailQuery = 'SELECT email FROM users WHERE email = $1';
    const retrieveEmailValue = [data.email];

    pool.query(retrieveEmailQuery, retrieveEmailValue, (err, res) => {
        if(err) cb(true, false);

        // check null
        var tmp = res.rows[0];

        if(tmp != undefined) {
            cb(false, false);
        } else {
            cb(false, true);
        }        
    });
}

// Register user
exports.register_user = function(data) {
    // Assign POST values
    const firstName = data.fn;
    const lastName = data.ln;
    const email = data.email;
    const isEnglish = (data.english == 'true');

    // encrypt password
    bcrypt.hash(data.password, 10, function(err, hash) {
        const insertUserText = 'INSERT INTO users(email, password_h, first_name, last_name, is_english) VALUES($1, $2, $3, $4, $5)';
        const insertUserValues = [email, hash, firstName, lastName, isEnglish];
        transaction(pool, insertUserText, insertUserValues);
    });
} // register_user

// Login user
exports.login_user = function(data, cb) {
    const email = data.email;
    const password = data.password;
    let id = null;
    let passwordHash = null;

    // get hash from DB, then compare to password input
    const retrievePassText = 'SELECT id, password_h FROM users WHERE email = $1';
    pool.query(retrievePassText, [email], (err, res) => {
        // error
        if (err) console.error(err);
       
        // Ensure we retrieved a value
        if(res.rows[0] != undefined) {
            passwordHash = res.rows[0].password_h;
            id = res.rows[0].id;
        } else { 
            // Email doesn't exist
            cb("email");
            return;
        }
        compare(password, passwordHash, id, cb);
    });

    
} // Login user

// Compare token with database
exports.verifyToken = function (id, token, cb) {
    const query = 'SELECT token, id FROM users WHERE id = $1';
    const value = [id];

    pool.query(query, value, (err, res) => {
        let getToken = null;
        

        if (err) {
            console.error(err);
            cb(true, false);
            return;
        }

        if(res.rows[0] != undefined) {
            getToken = res.rows[0].token;
        } else {
            cb(true, false);
            return;
        }

        if ((token == getToken)) cb(false, true);
        else cb(true, false);

    });
}

exports.queryUsersID = function(id, cb) {
    const query = "SELECT first_name, last_name, is_english FROM users WHERE id = $1";

    pool.query(query, [id], (err, res) => {
        if (err) throw err;

        if (res.rows[0] != undefined) {
            cb(false, JSON.stringify(res.rows[0]));
            return;
        } else {
            cb (true, null);
            return;
        }
    });
}

// Compare passwords
function compare(password, passwordHash, id, cb) {
    // Compare here
    bcrypt.compare(password, passwordHash, function(err, res) {
        // if passwords match
        if (res) {
            // callback that returns a crypto buffer to store in session
            crypto.randomBytes(32, (err, buff) => {
                const json = {
                    token: buff.toString('hex'),
                    id: id
                }
                insertToken(buff.toString('hex'), id);
                cb(false, JSON.stringify(json));
            });
            
        } else {
            cb("password");
        }
    });
}

// insertToken into user's database
function insertToken(token, id) {
    let query = 'UPDATE users SET token = $1 WHERE id = $2';
    let values = [token, id];
    transaction(pool, query, values);
}