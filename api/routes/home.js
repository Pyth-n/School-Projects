const express = require('express');
const router = express.Router();

const controller = require('../controllers/homeController');

// Home page is rendered
router.get('/home', controller.authenticate, controller.home_page);

router.get('/home/:id', controller.authenticate, controller.authenticateID, (req, res, next) => {
    console.log("Querying /home/" + req.params.id);
    res.render('home');
})

module.exports = router;
