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
    //console.log("Querying /home/" + req.params.id);
    pillModel.queryUsersID(req.session.userid, (err, jsonUsers) => {
        if (err) return;

        // TODO: Concat user JSON with pill_description JSON
        pillModel.queryUsersPill(req.session.userid, (err, jsonPills) => {
            // There's no pills
            if (err) {
                res.render('home', JSON.parse(jsonUsers));
            } 
            // Concatenate if there are pills
            else {
                
                res.render('home', {
                    user: JSON.parse(jsonUsers),
                    pill: JSON.parse(jsonPills)
                });
            }
        });
    });
}

module.exports.addPill = function(req, res, next) {
    let jsonRes = {
        success: null
    }
    if (!req.body.user || !req.body.daysData) {
        jsonRes.success = false;
        res.statusCode = 401;
        res.setHeader('Content-Type', 'application/json');
        res.send(JSON.stringify(jsonRes));
    }

    // First insert the pill, callback data gets the info just inserted
    pillModel.insertPill(req.params.id, req.body.user, (err, data) => {
        if (err) return;
        let returnData = JSON.parse(data);

        console.log("OFFICIALS DATA: " + data);

        // Insert PILL ID instead of USER ID
        // Then, insert the time
        pillModel.insertDays(returnData.id, req.body.daysData);
        res.end();
    })
}

module.exports.getPill = function(req, res) {
    pillModel.queryUserPill(req.params.id, req.params.pillid, (err, data) => {
        if (err) {
            res.statusCode = 402;
            res.setHeader('Content-Type', 'application/json');
            res.send("{ success: false }");
        }
        
        dataParsed = JSON.parse(data);
        let toSend = {
            success: true,
            data: dataParsed[0]
        }
        
        res.statusCode = 200;
        res.setHeader('Content-Type','application/json');
        res.send(toSend);
    });
}