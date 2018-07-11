'use strict';

var register_routes = require('./register');
var login_routes = require('./login');


module.exports = function(app) {

    app.use('/', register_routes);
    app.use('/', login_routes);

    // app.get('/home', (req, res) => {
    //     res.render('home');
    // });
}