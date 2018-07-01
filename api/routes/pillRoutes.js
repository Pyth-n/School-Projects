'use strict';

var pill = require('../controllers/pillController');


module.exports = function(app) {
    app.get('/', function(req, res) {
        res.end();
    });

    app.route('/register')
        .get(pill.register_page);

    app.route('/login')
        .get(pill.login_page);

}