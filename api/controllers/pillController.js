'use strict';

exports.register_page = function(req, res) {
    res.render('register');
}

exports.register = function(req, res) {
    console.log("POST ON REGISTER");
    return res.redirect('/login' + '?registered=true');
}

exports.login_page = function(req, res) {
    res.render('login');
}

