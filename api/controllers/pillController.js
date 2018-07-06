'use strict';

var pillModel = require('../models/pillModel');

// GET /register
exports.register_page = function(req, res) {
    console.log(req.params.id);
    res.render('register');
}

// POST /register
exports.register = function(req, res) {
    console.log("POST ON REGISTER");

    // get POST values
    pillModel.register_user(req.body.user);

    res.end();
}

exports.login_page = function(req, res) {
    res.render('login');
}

