// Require DB connection and credential
const pool = require('../../sql/db_auth');


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
    

    console.log('First name: ' + firstName);
    console.log('last name: ' + lastName);
    console.log('email: ' + email);
    console.log('password: ' + password);
    console.log('English: ' + english);


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

            const insertUserText = 'INSERT INTO users(email, password_h, first_name, last_name, is_english) VALUES($1, $2, $3, $4, $5)';
            const insertUserValues = [email, password, firstName, lastName, english];
            client.query(insertUserText, insertUserValues, (err, res) => {
                if (shouldAbort(err)) return;

                client.query('COMMIT', (err) => {
                    if (err) {
                        console.error('Error commiting transaction', err.stack);
                    }
                    done();
                })
            });
        })

    });
    
}