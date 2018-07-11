const express = require('express');
const router = express.Router();

const controller = require('../controllers/homeController');

// Home page is rendered
router.get('/home', controller.home_page);

module.exports = router;
