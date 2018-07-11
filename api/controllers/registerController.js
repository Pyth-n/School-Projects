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

    var resJson = {
        "email": req.body.user.email,
        "path": "/"
    }

    // Register user with POST values
    pillModel.register_user(req.body.user);
    res.setHeader('Content-Type', 'application/json');
    res.send(JSON.stringify(resJson, null, 3));
}

// POST /register if email is NOT available
exports.test = function(req, res, next) {
    var jsonError = {
        "error": "email"
    }
    res.setHeader('Content-Type', 'application/json');
    res.send(JSON.stringify(jsonError, null, 3));
}
