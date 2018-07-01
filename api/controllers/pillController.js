'use strict';

exports.register_page = function(req, res) {
    res.render('register');
}


exports.login_page = function(req, res) {
    res.render('login');
}