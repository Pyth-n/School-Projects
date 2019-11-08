package com.byui_cs246_team07.listtracker;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.DatePicker;
import android.widget.Toast;

import java.util.Calendar;

import reminder.ScheduleClient;

/**
 * Activity that sets a reminder and notifies the  user
 */
public class ReminderActivity extends AppCompatActivity {

    private final String TAG = this.getClass().getName();

    private ScheduleClient scheduleClient;
    private DatePicker datePicker;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_reminder);

        scheduleClient = new ScheduleClient(this);
        scheduleClient.doBindService();

        datePicker = findViewById(R.id.reminderDatePicker);
    }

    public void saveReminderDate(View view) {
        int day = datePicker.getDayOfMonth();
        int month = datePicker.getMonth();
        int year = datePicker.getYear();

        // Currently sets all alarms to 6 because of activity design
        Calendar c = Calendar.getInstance();
        c.set(year, month, day);
        c.set(Calendar.HOUR_OF_DAY, 18);
        c.set(Calendar.MINUTE, 0);
        c.set(Calendar.SECOND, 0);

        scheduleClient.setAlarmForNotification(c);

        Toast.makeText(this, "Notification set for: " + day + "/" + (month + 1) + "/" + year, Toast.LENGTH_SHORT).show();

        Log.d(TAG, "Reminder set");
    }

    @Override
    protected void onStop() {
        super.onStop();
        if (scheduleClient != null)
            scheduleClient.doUnbindService();
    }
}
