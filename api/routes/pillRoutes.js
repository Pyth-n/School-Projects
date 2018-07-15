'use strict';

var register_routes = require('./register');
var login_routes = require('./login');
var home_routes = require('./home');

module.exports = function(app) {

    app.use('/', home_routes);
    app.use('/', register_routes);
    app.use('/', login_routes);

    app.get('/logout', function(req, res) {
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
    });

    app.get('/index.html', function(req, res) {
        res.render('test');
    })
    
}