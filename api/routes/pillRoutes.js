'use strict';

var pill = require('../controllers/pillController');


module.exports = function(app, pool) {
    app.get('/', function(req, res) {
        pool.query('SELECT * FROM users WHERE id = $1', [1], (err, res) => {
            if(err) { throw err; }
        
            console.log(res.rows[0].email);
            pool.end();
        });
        res.end();
        //return res.redirect('/register');
    });

    app.route('/register')
        .get(pill.register_page)
        .post(pill.register);

    app.route('/login')
        .get(pill.login_page);

}