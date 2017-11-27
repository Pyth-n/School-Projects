package com.byui_cs246_team07.listtracker;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.Editable;
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
    private EditText mPriorityName;
    private EditText mNotes;
    private Item  itemActive;
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

        else if (buttonName.equals("loadItem")) {
            itemActive = (Item) getIntent().getSerializableExtra(ListActivity.ITEM);
            setItemValues(itemActive);
            Log.d("Set Item", itemActive.getName());
            Toast.makeText(this, "Loading " + itemActive.getName(), Toast.LENGTH_SHORT).show();
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
        if (itemActive != null && itemActive.getId() != 0) {
            item.setId(itemActive.getId());
        }
        item.setListId(parentList.getId());
        item.setCompleted(mCompleted.isChecked());
        item.setNotes(mNotes.getText().toString());
        item.setTags(mTag.getText().toString());
        item.setPriorityName(mPriorityName.getText().toString());
        Editable priorityNumberEditable = mPriorityNumber.getText();

        try {
            String priorityNum = mPriorityNumber.getText().toString();
            if (priorityNum != null && priorityNum != "") {
                item.setPriority(Integer.valueOf(mPriorityNumber.getText().toString()));
            }
        } catch (NumberFormatException e) {
            Log.d(TAG, "not a number");
        }

        //item.setPriority(Integer.parseInt(mPriorityNumber.getText().toString()));
        return item;
    }

    private void getItemValues() {

        mItemName = (EditText) findViewById(R.id.editItemName);
        mListName = (TextView) findViewById(R.id.listNameInItemScreen);
        mNotes = (EditText) findViewById(R.id.editNotes);
        mPriorityNumber = (EditText) findViewById(R.id.priorityNumber);
        mCompleted = (CheckBox) findViewById(R.id.completed);
        mPriorityName = (EditText) findViewById(R.id.priorityLevelName);
        mTag = (EditText) findViewById(R.id.editTags);
        mDateCreated = (TextView) findViewById(R.id.dateCreated);
    }

    private void setItemValues(Item item) {

        mItemName.setText(item.getName());
        mDateCreated.setText(item.getCreatedDateString());
        if (item.getNotes() != null) {
            mNotes.setText(item.getNotes());
        }
        if (item.getPriority() != null) {
            String priority = String.valueOf(item.getPriority());
            Log.d("Priori", priority);
            mPriorityNumber.setText(priority);
        }
        if (item.getCompleted() != null) {
            mCompleted.setChecked(item.getCompleted());
        }
        if (item.getNotes() != null) {
            mNotes.setText(item.getNotes());
        }
        if (item.getPriorityName() != null) {
            mPriorityName.setText(item.getPriorityName());
        }
        if (item.getTags() != null) {
            Log.d("Tags", item.getTags());
            mTag.setText(item.getTags());
        }
    }

    public void setReminderDate(View view) {
        Intent intent = new Intent(this, ReminderActivity.class);
        startActivity(intent);
    }

    public void addImage(View view) {
        Log.d(TAG, "Image added");
    }

    public void deleteImage(View view) {
        Log.d(TAG, "Image deleted");
    }
}
