// Require DB connection and credential
const pool = require('../../sql/db_auth');

// Bcrypt used to salt and hash passwords
const bcrypt = require('bcrypt');

// exports.register_user = function(data) {
//     console.log(data);
// }

exports.test_register_user = function(data) {
    console.log(data);
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
                        console.log("Email currently exists!");
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
    var password = data.password;
    var passwordHash = null;

    // TODO get hash from DB, then compare to password input
    const retrievePassText = 'SELECT password_h FROM users WHERE email = $1';
    pool.query(retrievePassText, [email], (err, res) => {
        
        if (err) console.error(err);
        var tmp = res.rows[0];

        if(tmp != undefined) {
            passwordHash = tmp.password_h;
            console.log("Found hash: " + tmp.password_h);
        } else {
            // Email doesn't exist
            console.log("Didn't find hash!");
            cb("email");
            return;
        }

        compare(password, passwordHash, cb);
    });

    
} // Login user

// Compare passwords
function compare(password, passwordHash, cb) {
    // Compare here
    bcrypt.compare(password, passwordHash, function(err, res) {
        if (res) {
            console.log("Passwords matched!");
            cb(false);
        } else {
            console.log("Passwords didn't match!")
            cb("password");
        }
    });
}