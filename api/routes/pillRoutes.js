'use strict';

var pill = require('../controllers/pillController');


module.exports = function(app) {
    app.get('/', function(req, res) {
        res.end();
    });

    app.route('/register')
        .get(pill.hello);

}