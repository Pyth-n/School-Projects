'use strict';

var pillModel = require('../models/pillModel');

// GET /register
exports.register_page = function(req, res) {
    res.render('register');
}

// POST /register middleware
exports.check_email_availability = function(req, res, next) {
    // Check if email is available. If not, send to test(req res)
    pillModel.is_email_available(req.body.user, (err, isAvailable) => {
        if (err) next('route');
        if (isAvailable) {
            console.log("Email is available");
            next();
        } else {
            console.log("Email is NOT available");
            next('route');
        }
    });    
}

// POST /register
exports.register = function(req, res, next) {
    // Register user with POST values
    //pillModel.register_user(req.body.user);
    res.redirect('/login');
}

// POST /register
exports.test = function(req, res, next) {
    var jsonError = {
        "error": "email"
    }
    res.setHeader('Content-Type', 'application/json');
    res.send(JSON.stringify(jsonError, null, 3));
    
    console.log("This is the TEST middleware");
}

// GET /login
exports.login_page = function(req, res) {
    res.render('login');
}

// POST /login
exports.login = function(req, res) {
    pillModel.login_user(req.body.user, (err) => {
        if(err) return res.redirect('/login' + '?err=' + err);
        res.render('home');
    });
    
}