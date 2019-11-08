const schedule = require('node-schedule');
const pillModel = require('./api/models/pillModel');

var sendReminder = require('./api/models/sendSMS');

module.exports = function() {
    pillModel.countUserId((err, data) => {
        if (data == 0) {
            return;
        }

        // Get array of user IDs
        pillModel.getIDs((err, userID) => {
            //console.log(data);

            // Get each user's pill and time
            userID.forEach(userIdCB => {

                pillModel.getPillIDs(userIdCB.id, (err, pillID) => {

                    // Get time for each pill
                    pillID.forEach(pillIdCB => {
                     
                        pillModel.getReminderTime(pillIdCB.id, (err, time) => {
                            schedulePill(userIdCB.id, pillIdCB.id, time);
                        });
                    });

                });

            });
        })
    });
}

function schedulePill(user_id, pill_id, time) {
    //console.log("Scheduled user " + user_id + " with pill " + pill_id + " at " + time.hour + ":" + time.minute);

    pillModel.getPillData(pill_id, (err, pillData) => {
        let pillName = pillData.pill_name;
        let amount = pillData.amount;
        // let strength = pillData.strength;
        // let remaining = pillData.remaining;

        pillModel.getUserData(user_id, (err, userData) => {
            let phoneNumber = userData.phone_number;
            let phoneProvider = userData.phone_provider;
            
            var tmp = schedule.scheduleJob('0 ' + time.minute + ' ' + time.hour + ' * * *', function() {
                sendReminder(pillName, amount, phoneNumber, phoneProvider);
                return;
            });

        });
    });
}

