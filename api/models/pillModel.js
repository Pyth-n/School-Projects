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
    const phoneNumber = data.phoneNumber;
    const phoneProvider = data.phoneProvider;

    // encrypt password
    bcrypt.hash(data.password, 10, function(err, hash) {
        let phoneProviderID = null;

        // Query phone provider ID
        pool.query('SELECT id FROM mobile_provider WHERE provider_uri=$1', [phoneProvider], function(err, res) {
            if (res.rows[0] != undefined) {
                phoneProviderID = res.rows[0].id;
            }
            const insertUserText = 'INSERT INTO users(email, password_h, first_name, last_name, is_english, phone_number, phone_provider) VALUES($1, $2, $3, $4, $5, $6, $7)';
            const insertUserValues = [email, hash, firstName, lastName, isEnglish, phoneNumber, phoneProviderID];
            transaction(pool, insertUserText, insertUserValues);
        })
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

// Get user's data
exports.queryUsersID = function(id, cb) {
    const query = "SELECT first_name, last_name, is_english FROM users WHERE id = $1";

    let users = null;

    pool.query(query, [id], (err, res) => {
        if (err) throw err;

        if (res.rows[0] != undefined) {
            users = JSON.stringify(res.rows[0], null, 3);
            
            cb(false, users);
            return;
        } else {
            cb(true, null);
            return;
        }
    });
}

exports.queryUserPill = function(id, pillID, cb) {
    let pills = null;
    const pillQuery = "SELECT id, pill_name, amount, strength, remaining FROM pill_description WHERE user_id = $1 AND id = $2";

    pool.query(pillQuery, [id, pillID], (err, res) => {
        if (err) throw err;

        if (res.rows[0] != undefined) {
            pills = JSON.stringify(res.rows, null, 3);
            cb(false, pills);
        } else {
            cb (true, null);
        }
    })
}

// Get user's pills
exports.queryUsersPill = function(id, cb) {
    let pills = null;

    const pillQuery = "SELECT id, pill_name, amount, strength, remaining FROM pill_description WHERE user_id = $1";
    
    pool.query(pillQuery, [id], (err, res) => {
        if (err) throw err;

        if (res.rows[0] != undefined) {
            pills = JSON.stringify(res.rows, null, 3);
            cb(false, pills);    
        } else {
            cb (true, null);
        }
    });
}

// Insert pill
exports.insertPill = function(id, data, cb) {

    const insertString = 'INSERT INTO pill_description(user_id, pill_name, amount, strength, remaining) VALUES($1, $2, $3, $4, $5) RETURNING *';
    const insertValue = [id, data.pill_name, data.amount, data.strength, data.remaining];

    // Start pill transaction
    transaction(pool, insertString, insertValue, (err, data) => {
        if(err){
            if (typeof cb === "function") {
                cb(true, null);
            }
        } else {
            if (typeof cb === "function") {
                cb(false, data);
            }
        }
    });
}

// Insert days
exports.insertDays = function(id, data, cb) {
    const insertString = "INSERT INTO reminder(pill_id, monday, tuesday, wednesday, thursday, friday, saturday, sunday) values($1,$2,$3,$4,$5,$6,$7,$8) RETURNING *";
    const insertValues = [id, data.monday, data.tuesday, data.wednesday, data.thursday, data.friday, data.saturday, data.sunday];

    transaction(pool, insertString, insertValues, (err, data) => {
        console.log("DAYS: " + data);
    });

    // if(typeof cb === "function") {
    //     cb(false);
    // }
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

