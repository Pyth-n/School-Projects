var pillModel = require('../models/pillModel');

// GET /register
exports.register_page = function(req, res) {
    res.render('register');
}

// POST /register middleware
exports.check_email_availability = function(req, res, next) {
    // Check if email is available. If not, send to emailUnavailable(req res)
    pillModel.is_email_available(req.body.user, (err, isAvailable) => {
        if (err) next('route');
        if (isAvailable) {            
            next();
        } else {
            next('route');
        }
    });    
}

// POST /register
exports.register = function(req, res, next) {

    var resJson = {
        success: true,
        email: req.body.user.email,
        nextPath: "/"
    }

    // Register user with POST values
    pillModel.register_user(req.body.user);
    res.statusCode = 200;
    res.setHeader('Content-Type', 'application/json');
    res.send(JSON.stringify(resJson, null, 3));
}

// POST /register if email is NOT available
exports.emailUnavailable = function(req, res, next) {
    var jsonError = {
        success: "false",
        error: "email"
    }
    res.statusCode = 401;
    res.setHeader('Content-Type', 'application/json');
    res.send(JSON.stringify(jsonError, null, 3));
}

exports.deleteAccount = function(req, res, next) {
    let user_id = req.params.id;

    pillModel.deleteUser(user_id, (err, success) => {
        res.send("{ success: true}");
    });
}