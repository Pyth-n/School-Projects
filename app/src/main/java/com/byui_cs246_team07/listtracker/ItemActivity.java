package com.byui_cs246_team07.listtracker;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import controllers.ItemController;
import models.Item;
import models.ItemList;

public class ItemActivity extends AppCompatActivity {

    private ItemList parentList;
    private ItemController controller;
    // IDs of widgets
    private TextView mListName;
    private EditText mItemName;
    private EditText mTag;
    private EditText mDueDate;
    private TextView mDateCreated;
    private TextView mDateModified;
    private CheckBox mCheckBox;
    private EditText mPriorityNumber;
    private EditText mPriorityLevel;
    private EditText mNotes;

    public ItemActivity() {
        controller = new ItemController(this);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_item);

        // find resource IDs
        mItemName = findViewById(R.id.editItemName);
        mListName = (TextView) findViewById(R.id.listNameInItemScreen);

        // Set name of the list
        parentList = (ItemList) getIntent().getSerializableExtra(ListActivity.PARENT_LIST);
        mListName.setText(parentList.getName());

        // Differentiate between the buttons that sent the intent
        String buttonName = getIntent().getStringExtra(ListActivity.BUTTON_PRESSED);
        if (buttonName.equals("createItem")) {
            //Toast.makeText(this, "CREATING...", Toast.LENGTH_SHORT).show();

        }
        // TODO loading magic occurs here. Not sure how to utilize database to populate from list
        // TODO selected yet
        else if (buttonName.equals("loadItem")) {
            String itemName = getIntent().getStringExtra(ListActivity.ITEM_NAME_ID);
            mItemName.setText(itemName);
            Toast.makeText(this, "LOADING...", Toast.LENGTH_SHORT).show();
        }
    }

    public void saveItem(View view) {
        mListName = (TextView) findViewById(R.id.editItemName);
        Item item = new Item(mListName.getText().toString());
        item.setListId(parentList.getId());
        controller.saveItem(item);
    }

    public void setReminderDate(View view) {
        Intent intent = new Intent(this, ReminderActivity.class);
        startActivity(intent);
    }
}
