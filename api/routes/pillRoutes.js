'use strict';

// ROUTER
const express = require('express');
const router = express.Router();

var pill = require('../controllers/pillController');


module.exports = function(app) {

    // Index
    router.get('/', pill.login_page);

    // REGISTER endpoint
    router.get('/register', pill.register_page);
    router.post('/register', pill.check_email_availability, pill.register)
    router.post('/register', pill.test);

    router.get('/login', pill.login_page);
    router.get('/home', (req, res) => {
        res.render('home');
    })

    
    app.use('/', router)
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