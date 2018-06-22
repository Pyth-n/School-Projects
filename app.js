const app = require('express')();
const PORT = process.env.PORT || 1337;

app.get('/', function(req, res) {
    console.log("Curled");
    res.end('Hello World!');
});

app.listen(PORT, () => console.log("Running on port: " + PORT));
