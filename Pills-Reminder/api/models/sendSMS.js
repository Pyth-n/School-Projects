// To email
const pillModel = require('./pillModel');

const GMAILAPP = process.env.GMAILAPP;
const nodemailer = require('nodemailer');

const transporter = nodemailer.createTransport({
    service: 'gmail',
    auth: {
        user: '3dgar.p@gmail.com',
        pass: GMAILAPP
    }
});

module.exports = (pillName, amount, phoneNumber, phoneProvider) => {
    pillModel.getProvider(phoneProvider, (err, provider) => {
        console.log("Sending " + pillName + " to " + phoneNumber + provider.provider_uri);
        var mailOptions = {
            from: '3dgar.p@gmail.com',
            to: phoneNumber + provider.provider_uri,
            subject: 'Pill Reminder',
            text: 'REMINDER: Take ' + amount + ' ' + pillName + '(s)' 
        }

        transporter.sendMail(mailOptions, function(err, info) {
            if (err) throw err;

            console.log("Sent: " + info.response);
        });

    });
}