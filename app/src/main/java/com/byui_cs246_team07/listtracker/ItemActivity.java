package com.byui_cs246_team07.listtracker;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class ItemActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_item);

        // Gets the intent from ListActivity. Sets the name of the list
        Intent intent = getIntent();
        String listName = intent.getStringExtra(ListActivity.listNameID);

        TextView textView = (TextView) findViewById(R.id.listNameInItemScreen);
        textView.setText(listName);
    }
}
