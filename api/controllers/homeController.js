var pillModel = require('../models/pillModel');

// Authenticate user
module.exports.authenticate = function(req, res, next) {
    // If no token is stored in session, /GET /
    if (!req.session.token || !req.session.userid) {
        console.log("NOT authenticated");
        return res.redirect('/' + '?error=authentication');
    }
    
    // Verify token to prevent session hijacking
    pillModel.verifyToken(req.session.userid, req.session.token, (err, isValid) => {
        if (isValid) {
            next()
        } else {
            res.statusCode = 401;
            res.send("NOT AUTHENTICATED");
        }
    });
}

module.exports.authenticateID = function(req, res, next) {
    console.log("Authentocating ID");

    if (req.session.userid == req.params.id) {
        console.log("Correct ID");
        next();
    } else {
        console.log("INCORRECT id");
        res.redirect('/home');
    }
}

// Render home page
module.exports.home_page = function(req, res, next) {
    console.log("Welcome to the home page");
    res.statusCode = 200;
    return res.redirect('/home/' + req.session.userid);
}