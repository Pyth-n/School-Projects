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