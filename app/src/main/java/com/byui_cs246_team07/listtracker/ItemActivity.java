package com.byui_cs246_team07.listtracker;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

public class ItemActivity extends AppCompatActivity {
    // IDs of widgets
    TextView mListName;
    EditText mItemName;
    EditText mTag;
    EditText mDueDate;
    TextView mDateCreated;
    TextView mDateModified;
    CheckBox mCheckBox;
    EditText mPriorityNumber;
    EditText mPriorityLevel;
    EditText mNotes;

    // TODO get the data from the database to store in the fields whenever intent from "load" occurs

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_item);

        // find resource IDs
        mItemName = findViewById(R.id.editItemName);
        mListName = (TextView) findViewById(R.id.listNameInItemScreen);

        // Set name of the list
        mListName.setText(getIntent().getStringExtra(ListActivity.LIST_NAME_ID));

        // Differentiate between the buttons that sent the intent
        String buttonName = getIntent().getStringExtra(ListActivity.BUTTON_PRESSED);
        if (buttonName.equals("createItem")) {
            Toast.makeText(this, "CREATING...", Toast.LENGTH_SHORT).show();
        }
        // TODO loading magic occurs here. Not sure how to utilize database to populate from list
        // TODO selected yet
        else if (buttonName.equals("loadItem")) {
            String itemName = getIntent().getStringExtra(ListActivity.ITEM_NAME_ID);
            mItemName.setText(itemName);
            Toast.makeText(this, "LOADING...", Toast.LENGTH_SHORT).show();
        }
    }
}
