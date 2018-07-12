const express = require('express');
const router = express.Router();

const controller = require('../controllers/homeController');

// Home page is rendered
router.get('/home', controller.authenticate, controller.home_page);

router.get('/home/:id', controller.authenticate, controller.authenticateID, controller.user_data);

module.exports = router;
