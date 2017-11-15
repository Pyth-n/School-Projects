package com.byui_cs246_team07.listtracker;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;

public class ReminderActivity extends AppCompatActivity {

    private final String TAG = this.getClass().getName();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_reminder);
    }

    public void saveReminderDate(View view) {
        Intent intent = new Intent(this, ItemActivity.class);
        startActivity(intent);
        Log.d(TAG, "Reminder set");
    }
}
