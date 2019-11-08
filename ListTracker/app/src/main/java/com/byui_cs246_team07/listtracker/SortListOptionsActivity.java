package com.byui_cs246_team07.listtracker;

import android.app.Activity;
import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.RadioGroup;

public class SortListOptionsActivity extends AppCompatActivity {

    private final String TAG = this.getClass().getName();
    public  static final String SORT_BY = "sort_by";
    private String sortOptions;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_sort_list_options);
    }

    private void chooseSort() {
        Log.d(TAG, "Sort list option chosen");

    }

    public void orderByDate(View view) {
        sortOptions = "date";
        Log.d(TAG, "date");
    }

    public void orderByName(View view) {
        sortOptions = "name";
        Log.d(TAG, "name");
    }

    public void orderByManual(View view) {
        sortOptions = "manual";
        Log.d(TAG, "manual");
    }

    public void orderByModified(View view) {
        sortOptions = "modified";
        Log.d(TAG, "modified");
    }

    public void saveOrder(View view) {
        Intent resultIntent = new Intent();
        resultIntent.putExtra(SORT_BY, sortOptions);
        setResult(Activity.RESULT_OK, resultIntent);
        finish();
    }
}
