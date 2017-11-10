package com.byui_cs246_team07.listtracker;

import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.TextView;

import java.util.List;

import controllers.ItemController;
import models.Item;

public class ListActivity extends AppCompatActivity {
    public static final String listNameID = "com.byui.cs246.team07.listtracker.LISTID";
    public static final String itemNameID = "com.byui.cs246.team07.listtracker.ITEMID";
    private final String TAG = this.getClass().getName();

    private int mItemSelectedIndex;
    ListView listViewOfItems;

    ItemController controller;
    TextView textView;
    List<Item> items;

    // TODO get the name of the list, then modify this value. Used for current activity and intent
    private String nameOfList = "Sample List Name";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_list);

        // Sets the name of the list in the current activity
        textView = findViewById(R.id.listNameInListScreen);
        textView.setText(nameOfList);

        // Attempt to get data base stuff
        controller = new ItemController();
        items = controller.getItems(this);

        listViewOfItems = findViewById(R.id.listOfItems);

        ArrayAdapter<String> adapter = new ArrayAdapter<String>(this, android.R.layout.simple_list_item_1);
        for (Item item : items) {
            adapter.add(item.getName());
        }

        listViewOfItems.setAdapter(adapter);
        listViewOfItems.setChoiceMode(ListView.CHOICE_MODE_SINGLE);

        // Adds a listener so that an item can be selected and be highlighted
        listViewOfItems.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int pos, long l) {
                for (int i = 0; i < listViewOfItems.getChildCount(); i++) {
                    if (pos == i) {
                        listViewOfItems.getChildAt(pos).setBackgroundColor(Color.GRAY);
                        mItemSelectedIndex = pos;

                    } else {
                        listViewOfItems.getChildAt(i).setBackgroundColor(Color.TRANSPARENT);
                    }
                }

                Log.d("POSITION: ", Integer.toString(pos));
            }
        });
    }

    /*createItem(): This function is called by the "Create Item" button. It opens up the ItemActivity
    * */
    public void createItem(View v) {
        Item item = items.get(mItemSelectedIndex);
        String itemName = item.getName();

        // Will send intent to the ItemActivity
        Intent intent = new Intent(this, ItemActivity.class);
        intent.putExtra(listNameID, nameOfList);

        // TODO move this to the load item section
        intent.putExtra(itemNameID, itemName);


        Log.d(TAG, "Sending " + intent.getStringExtra(listNameID));
        startActivity(intent);
    }


}
