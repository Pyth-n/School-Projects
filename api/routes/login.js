const express = require('express');
const pill = require('../controllers/loginController');

const router = express.Router();

// Render login page
router.get('/', pill.login_page);
router.post('/', pill.login);

// Log out
router.get('/logout', pill.logout);

module.exports = router;