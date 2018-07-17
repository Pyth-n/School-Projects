'use strict';

var register_routes = require('./register');
var login_routes = require('./login');
var home_routes = require('./home');

module.exports = function(app) {

    app.use('/', home_routes);
    app.use('/', register_routes);
    app.use('/', login_routes);

    app.get('/index.html/:id', function(req, res) {
        res.render('test');
    })
    
}