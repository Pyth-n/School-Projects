// Require DB connection and credential
const pool = require('../../sql/db_auth');

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
    const password = data.password;
    const isEnglish = (data.english == 'true');

    
    // PG Transaction
    pool.connect((err, client, done) => {

        const shouldAbort = (err) => {
            if (err) {
                console.error('Error in transaction', err.stack);
                client.query('ROLLBACK', (err) => {
                    if (err) {
                        console.error('Error rolling back client', err.stack);
                    }
                    done();
                });
            }
            return !!err;
        }

        client.query('BEGIN', (err) => {
            if (shouldAbort(err)) return;

            // ensure password is hashed and salted before inserting into database
            bcrypt.hash(password, 10, function(err, hash) {

                const insertUserText = 'INSERT INTO users(email, password_h, first_name, last_name, is_english) VALUES($1, $2, $3, $4, $5)';
                const insertUserValues = [email, hash, firstName, lastName, isEnglish];
                client.query(insertUserText, insertUserValues, (err, res) => {
                    if (shouldAbort(err)){
                        return;
                    } 
    
                    client.query('COMMIT', (err) => {
                        if (err) {
                            console.error('Error commiting transaction', err.stack);
                        }
                        done();
                    })
                });

            });
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
                cb(false, JSON.stringify(json));
            });
            
        } else {
            cb("password");
        }
    });
}

// TODO: insertToken into user's database
function insertToken(token, id) {
    
}