package com.byui_cs246_team07.listtracker;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;

public class ListActivity extends AppCompatActivity {
    public static final String listNameID = "com.byui.cs246.team07.listtracker.LISTID";
    private final String TAG = this.getClass().getName();

    // TODO get the name of the list, then modify this value. Used for current activity and intent
    private String nameOfList = "Sample List Name";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_list);

        // Sets the name of the list in the current activity
        TextView textView = (TextView) findViewById(R.id.listNameInListScreen);
        textView.setText(nameOfList);
    }

    /*createItem(): This function is called by the "Create Item" button. It opens up the ItemActivity
    * */
    public void createItem(View v) {
        // Will send intent to the ItemActivity
        Intent intent = new Intent(this, ItemActivity.class);
        intent.putExtra(listNameID, nameOfList);

        Log.d(TAG, "Sending " + intent.getStringExtra(listNameID));
        startActivity(intent);
    }
}
