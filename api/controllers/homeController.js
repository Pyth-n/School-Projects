var pillModel = require('../models/pillModel');

// Render home page
module.exports.home_page = function(req, res) {
    res.statusCode = 200;
    res.setHeader('Content-Type', 'text/html')
    res.render('home');
}