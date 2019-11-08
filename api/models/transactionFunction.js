module.exports = function(pool, queryText, queryValues, cb) {
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
                client.query(queryText, queryValues, (err, res) => {
                    if (shouldAbort(err)){
                        if (typeof cb === "function") {
                            cb(true, null);
                        }
                        return;
                    } else {
                        // Callback if everything is successfuly
                        if (typeof cb === "function") {
                            cb(false, JSON.stringify(res.rows[0]));
                        }
                    }
    
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

