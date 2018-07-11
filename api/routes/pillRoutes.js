'use strict';

var pill = require('../controllers/pillController');
var register_routes = require('./register');


module.exports = function(app) {

    app.use('/', register_routes);

    // Index
    app.get('/', pill.login_page);

    app.get('/login', pill.login_page);
    app.get('/home', (req, res) => {
        res.render('home');
    });
}
    // app.get('/', function(req, res) {
    //     res.json({'Hello': 'welcome here'});
    //     //return res.redirect('/register');
    // });

    // app.route('/register')
    //     .get(pill.register_page)
    //     .post(pill.check_email_availability, pill.register)
    //     .post(pill.test)


    // app.route('/login')
    //     .get(pill.login_page)
    //     .post(pill.login);