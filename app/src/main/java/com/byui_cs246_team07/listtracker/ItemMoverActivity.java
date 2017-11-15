package com.byui_cs246_team07.listtracker;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;

public class ItemMoverActivity extends AppCompatActivity {

    private final String TAG = this.getClass().getName();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_item_mover);
    }


    private void moveItem() {
        Log.d(TAG, "Item moved");
    }
}
