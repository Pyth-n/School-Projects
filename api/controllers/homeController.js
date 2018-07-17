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
            console.log("Tokens do NOT match");
            res.statusCode = 401;
            return res.redirect('/');
        }
    });
}

// Authenticates /home/:id
module.exports.authenticateID = function(req, res, next) {
    console.log("Authenticating ID");

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

        
        //req.session.dbUsers = jsonUsers;
        //console.log(req.session.dbUsers);
        //console.log(req.sessions.dbUsers);
        res.render('home', JSON.parse(jsonUsers));
    });
    
}

module.exports.addPill = function(req, res, next) {
    let jsonRes = {
        success: null
    }
    if (!req.body.user) {
        jsonRes.success = false;
        res.statusCode = 401;
        res.setHeader('Content-Type', 'application/json');
        res.send(JSON.stringify(jsonRes));
    }

    pillModel.insertPill(req.params.id, req.body.user, (err) => {
        if (err) return;
        res.end();
    })
}