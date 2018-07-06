// Require DB connection and credential
const pool = require('../../sql/db_auth');

// Bcrypt used to salt and hash passwords
const bcrypt = require('bcrypt');

// Register user
exports.register_user = function(data) {
    // Assign POST values
    const firstName = data.fn;
    const lastName = data.ln;
    const email = data.email;
    const password = data.password;
    const isSpanish = data.english;
    var english = true;
    if (isSpanish) {
        english = false;
    } 
    
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
                const insertUserValues = [email, hash, firstName, lastName, english];
                client.query(insertUserText, insertUserValues, (err, res) => {
                    if (shouldAbort(err)) return;
    
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
exports.login_user = function(data) {
    const email = data.email;
    const password = data.password;

    const loginUserText = 'SELECT id, is_english FROM users WHERE email = $1 AND password_h = $2';
    const loginUserValues = [email, password];

    pool.query(loginUserText, loginUserValues, (err, res) => {
        if (err) throw err;

        console.log('id: ', res.rows[0]);
    })
    
}