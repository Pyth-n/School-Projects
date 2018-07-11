const express = require('express');
const pill = require('../controllers/pillController');

const router = express.Router();

// Render login page
router.get('/', pill.login_page);

module.exports = router;