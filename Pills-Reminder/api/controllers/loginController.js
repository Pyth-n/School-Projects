var pillModel = require('../models/pillModel');

// GET /login
exports.login_page = function(req, res) {
    res.render('login');
}

// POST /login
exports.login = function(req, res, next) {
    pillModel.login_user(req.body.user, (err, data) => {
        if(err) {
            const json = {
                success: false
            }
            res.statusCode = 401;
            res.set('Content-Type', 'application/json');
            res.send(JSON.stringify(json, null, 3));
            return;
        }
        
        // Use data callback value to store in session
        data = JSON.parse(data);
        req.session.userid = data.id;
        req.session.token = data.token;
        res.statusCode = 200;
        res.set('Content-Type', 'application/json');

        const json = {
            success: true,
            nextPath: '/home'
        }
        res.send(JSON.stringify(json, null, 3));
        next();
    });
}

// GET /logout
exports.logout = function(req, res) {
    let jsonRes = {
        success: null,
        nextPath: '/'
    }
    if(req.session.userid) {
        req.session.destroy((err) => {
            if (err) {
                res.statusCode = 400;
                jsonRes.success = false;
                res.setHeader('Content-Type', 'application/json');
                res.send(JSON.stringify(jsonRes, null, 3));
            } else {
                res.statusCode = 200;
                jsonRes.success = true;
                res.setHeader('Content-Type', 'application/json');
                res.send(JSON.stringify(jsonRes, null, 3));
            }
        });
    }
}