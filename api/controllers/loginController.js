var pillModel = require('../models/pillModel');

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