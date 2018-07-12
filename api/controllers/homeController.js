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
        next();
    } else {
        res.redirect('/home');
    }
}

// Render home page
module.exports.home_page = function(req, res, next) {
    res.statusCode = 200;
    return res.redirect('/home/' + req.session.userid);
}

module.exports.user_data = function(req, res, next) {
    let users = null;
    console.log("Querying /home/" + req.params.id);
    pillModel.queryUsersID(req.session.userid, (err, jsonUsers) => {
        if (err) return;

        
        req.session.dbUsers = jsonUsers;
        console.log(req.session.dbUsers);
        //console.log(req.sessions.dbUsers);
        res.render('home', JSON.parse(jsonUsers));
    });
    
}