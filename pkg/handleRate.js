// Parse package
const url = require('url');

// Calculation export
var computeRate = require('../pkg/computeRate');
module.exports = function(req, res) {
    var variables = getVariables(req);

    var weight = variables.query.weight;
    var mailType = variables.query.mailType;

    computeRate(weight, mailType, res);
}

// Get GET variables
function getVariables(req) {
    return url.parse(req.url, true);
}