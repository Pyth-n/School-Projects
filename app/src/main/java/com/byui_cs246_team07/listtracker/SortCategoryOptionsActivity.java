package com.byui_cs246_team07.listtracker;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;

public class SortCategoryOptionsActivity extends AppCompatActivity {

    private final String TAG = this.getClass().getName();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_sort_category_options);
    }

    private void chooseSort() {
        Log.d(TAG, "Sort category option chosen");
    }
}
