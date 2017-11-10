package com.byui_cs246_team07.listtracker;

import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.support.v7.app.AppCompatActivity;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;
import java.util.List;

import controllers.ItemController;
import models.Item;

public class ListActivity extends AppCompatActivity {
    // These are keys used for the intents
    public static final String LIST_NAME_ID = "com.byui.cs246.team07.listtracker.LISTID";
    public static final String ITEM_NAME_ID = "com.byui.cs246.team07.listtracker.ITEMID";
    public static final String BUTTON_PRESSED = "com.byui.cs246.team07.listtracker.BUTTONID";
    // TAG is used for logs
    private final String TAG = this.getClass().getName();

    // Widget IDs
    ListView mListViewOfItems;
    TextView mListName;

    ItemController controller;
    List<Item> items;
    private int mItemSelectedIndex;

    // TODO get the name of the list, then modify this value. Currently mocks list name
    private String nameOfList = "Sample List Name";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_list);
        mItemSelectedIndex = -1;

        // Sets resource IDs
        mListName = findViewById(R.id.listNameInListScreen);
        mListViewOfItems = findViewById(R.id.listOfItems);

        // Set the name of the list
        mListName.setText(nameOfList);

        // Attempt to get data base stuff
        controller = new ItemController(this);
        items = controller.getItems();

        // Adapter used add items and display in the ListView
        ArrayAdapter<String> adapter = new ArrayAdapter<String>(this, android.R.layout.simple_list_item_1);
        for (Item item : items) {
            adapter.add(item.getName());
        }
        for (int i = 0; i < 10; i++) {
            adapter.add("Mocked item " + Integer.toString(i + 1));
        }
        mListViewOfItems.setAdapter(adapter);
        mListViewOfItems.setChoiceMode(ListView.CHOICE_MODE_SINGLE);

        // Adds a listener so that an item can be selected and be highlighted
        mListViewOfItems.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int pos, long l) {
                for (int i = 0; i < mListViewOfItems.getChildCount(); i++) {
                    if (pos == i) {
                        mListViewOfItems.getChildAt(pos).setBackgroundColor(Color.GRAY);
                        mItemSelectedIndex = pos;
                    } else {
                        mListViewOfItems.getChildAt(i).setBackgroundColor(Color.TRANSPARENT);
                    }
                }
                Log.d("POSITION: ", Integer.toString(pos));
            }
        });
    }

    /*createItem(): This function is called by the "Create Item" button. It opens up the ItemActivity
    * */
    public void createItem(View v) {
        // Will send intent to the ItemActivity
        Intent intent = new Intent(this, ItemActivity.class);
        intent.putExtra(LIST_NAME_ID, nameOfList);
        intent.putExtra(BUTTON_PRESSED, "createItem");

        Log.d(TAG, "Sending " + intent.getStringExtra(LIST_NAME_ID));
        startActivity(intent);
    }

    /*loadItem(): This function loads a selected item and sends an intent to
    * ItemActivity
    * */
    public void loadItem(View view) {
        // Makes sure an item is selected before creating and sending an intent
        if (mItemSelectedIndex != -1) {
            Item item = items.get(mItemSelectedIndex);
            Intent intent = new Intent(this, ItemActivity.class);
            intent.putExtra(ITEM_NAME_ID, item.getName());
            intent.putExtra(LIST_NAME_ID, nameOfList);
            intent.putExtra(BUTTON_PRESSED, "loadItem");
            startActivity(intent);
        } else {
            Toast.makeText(this, "Select an Item first", Toast.LENGTH_SHORT).show();
        }
    }
}
