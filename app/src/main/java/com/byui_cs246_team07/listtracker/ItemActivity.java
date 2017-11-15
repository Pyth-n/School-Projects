package com.byui_cs246_team07.listtracker;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
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
    private final String TAG = this.getClass().getName();
    // IDs of widgets
    private TextView mListName;
    private EditText mItemName;
    private EditText mTag;
    private EditText mDueDate;
    private TextView mDateCreated;
    private TextView mDateModified;
    private CheckBox mCompleted;
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


        getItemValues();
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
            Item item = (Item) getIntent().getSerializableExtra(ListActivity.ITEM);
            setItemValues(item);
            Toast.makeText(this, "LOADING...", Toast.LENGTH_SHORT).show();
        }
    }

    @Override
    protected void onResume() {

        super.onResume();

    }

    public void saveItem(View view) {

        if (!mItemName.getText().toString().equals("")) {
            Item item = createItem();
            controller.saveItem(item);
            Log.d(TAG, "Item saved");
            Toast.makeText(this, "Item saved", Toast.LENGTH_SHORT).show();

        } else {
            Toast.makeText(this, "Add at least a name", Toast.LENGTH_SHORT).show();
        }

    }

    private Item createItem() {

        Item item = new Item(mItemName.getText().toString());
        item.setListId(parentList.getId());
        item.setCompleted(mCompleted.isChecked());
        Log.d("Notes", mNotes.getText().toString());
        item.setNotes(mNotes.getText().toString());

        //item.setPriority(Integer.parseInt(mPriorityNumber.getText().toString()));
        return item;
    }

    private void getItemValues() {

        mItemName = (EditText) findViewById(R.id.editItemName);
        mListName = (TextView) findViewById(R.id.listNameInItemScreen);
        mNotes = (EditText) findViewById(R.id.editNotes);
        mPriorityNumber = (EditText) findViewById(R.id.priorityNumber);
        mCompleted = (CheckBox) findViewById(R.id.completed);
    }

    private void setItemValues(Item item) {

        mItemName.setText(item.getName());
        if (item.getNotes() != null) {
            mNotes.setText(item.getNotes());
        }
        if (item.getPriority() != null) {
            mPriorityNumber.setText((String.valueOf(item.getPriority())));
        }
        if (item.getCompleted() != null) {
            mCompleted.setChecked(item.getCompleted());
        }
    }

    private void setReminderDate(View view) {
        Intent intent = new Intent(this, ReminderActivity.class);
        startActivity(intent);
    }

    private boolean addImage() {
        Log.d(TAG, "Image added");
        return false;
    }

    private boolean deleteImage() {
        Log.d(TAG, "Image deleted");
        return false;
    }
}
