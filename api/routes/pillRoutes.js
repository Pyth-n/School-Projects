'use strict';

var pill = require('../controllers/pillController');


module.exports = function(app) {
    app.get('/', function(req, res) {
        res.json({'Hello': 'welcome here'});
        //return res.redirect('/register');
    });

    app.route('/register')
        .get(pill.register_page)
        .post(pill.register, function(req, res, next) {
            res.json("{Signed up: True}")
        });

    app.route('/login')
        .get(pill.login_page)
        .post(pill.login);

}