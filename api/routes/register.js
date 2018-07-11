const express = require('express');
const pill = require('../controllers/pillController');

const router = express.Router();
    // REGISTER endpoint
    
    // Render the page
    router.get('/register', pill.register_page);

    // Check email availablility, if available, register
    router.post('/register', pill.check_email_availability, pill.register)

    // If not available, send to this route
    router.post('/register', pill.test);


module.exports = router;
