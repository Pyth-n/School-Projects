'use strict';

var pillModel = require('../models/pillModel');

// var pool = require('../../sql/db_auth');

// GET /register
exports.register_page = function(req, res) {
    // pool.query('SELECT * FROM users WHERE id = $1', [1], (err, res) => {
    //     if(err) { throw err; }
    
    //     console.log(res.rows[0].email);
    // });
    res.render('register');
}

// POST /register
exports.register = function(req, res) {
    // Register user with POST values
    pillModel.register_user(req.body.user);

    res.end();
}

exports.login_page = function(req, res) {
    res.render('login');
}

