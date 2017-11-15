package com.byui_cs246_team07.listtracker;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import java.util.ArrayList;
import java.util.List;

import controllers.ItemController;
import controllers.ItemListController;
import models.Item;
import models.ItemList;

public class ListActivity extends AppCompatActivity {
    // These are keys used for the intents
    public static final String LIST_ID = "com.byui.cs246.team07.listtracker.LISTID";
    public static final String ITEM = "com.byui.cs246.team07.listtracker.ITEMID";
    public static final String BUTTON_PRESSED = "com.byui.cs246.team07.listtracker.BUTTONID";
    public static final String PARENT_LIST = "PARENT_LIST";
    // TAG is used for logs
    private final String TAG = this.getClass().getName();

    // Widget IDs
    private ListView mListViewOfItems;
    private TextView mListName;

    private ItemListController controller;
    private ItemController itemController;
    private List<Item> items;
    private int mItemSelectedIndex;
    private Item itemSelected;
    private String nameOfList;
    private ItemList list;


    public ListActivity() {
        controller = new ItemListController(this);
        itemController = new ItemController(this);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_list);
        mItemSelectedIndex = -1;
        itemSelected = null;
        nameOfList = getIntent().getStringExtra(MainActivity.LISTNAMEID);

        // Sets resource IDs
        mListName = findViewById(R.id.listNameInListScreen);
        mListViewOfItems = findViewById(R.id.listOfItems);

        Intent intent = getIntent();
        list = (ItemList)intent.getSerializableExtra(MainActivity.ITEM_SELECTED);

        // Set the name of the list
        if (list != null) {
            mListName.setText(list.getName());
            // Set items
            items = controller.getRelatedItems(list.getId());
        }

        setListView();
        Log.d(TAG, "List opened");
    }

    /*createItem(): This function is called by the "Create Item" button. It opens up the ItemActivity
    * */
    public void createItem(View v) {
        // Will send intent to the ItemActivity
        Intent intent = new Intent(this, ItemActivity.class);
        intent.putExtra(PARENT_LIST, list);
        intent.putExtra(BUTTON_PRESSED, "createItem");

        Log.d(TAG, "Sending " + intent.getStringExtra(LIST_ID));
        startActivity(intent);
    }

    /*loadItem(): This function loads a selected item and sends an intent to
    * ItemActivity
    * */
    public void loadItem(View view) {
        // Makes sure an item is selected before creating and sending an intent
        if (mItemSelectedIndex != -1) {
            if (!items.isEmpty()){
                Item item = items.get(mItemSelectedIndex);
                Intent intent = new Intent(this, ItemActivity.class);
                intent.putExtra(PARENT_LIST, list);
                intent.putExtra(ITEM, item);
                intent.putExtra(BUTTON_PRESSED, "loadItem");
                startActivity(intent);
            } else {
                // TODO if its empty, start a create item, else it crashes
                Toast.makeText(this, "It's empty", Toast.LENGTH_SHORT).show();
            }

        } else {
            Toast.makeText(this, "Select an Item first", Toast.LENGTH_SHORT).show();
        }
    }

    public void deleteItem(View view) {
        // Null checks itemSelected so it doesn't cause a crash
        if (itemSelected != null) {
            String deleted = "Deleted " + itemSelected.getName();
            itemController.delete(itemSelected.getId());

            List<Item> newList = new ArrayList<>();
            for (Item item : items) {
                if (item.getId() != itemSelected.getId()) {
                    newList.add(item);
                }
            }
            itemSelected = null;
            items = newList;
            mItemSelectedIndex = -1;
            Toast.makeText(this, deleted, Toast.LENGTH_SHORT).show();
        } else {
            Toast.makeText(this, "Select Item to Delete", Toast.LENGTH_SHORT).show();
        }

        setListView();
    }

    public void copyItem(View view) {

        Intent intent = new Intent(this, ItemCopierActivity.class);
        startActivity(intent);

    }

    public void moveItem(View view) {

        Intent intent = new Intent(this, ItemMoverActivity.class);
        startActivity(intent);

    }

    public void sortList(View view) {

        Intent intent = new Intent(this, SortListOptionsActivity.class);
        startActivity(intent);

    }

    public void viewImageGallery(View view) {

        Intent intent = new Intent(this, ListImageGalleryActivity.class);
        startActivity(intent);

    }

    public void renameCategory(View view) {

        Log.d(TAG, "List renamed");
    }

    public void setListView() {
        // Adapter used add items and display in the ListView
        ArrayAdapter<String> adapter = new ArrayAdapter<String>(this, android.R.layout.simple_list_item_1);
        if (items != null) {
            for (Item item : items) {
                adapter.add(item.getName());
            }
        }

        /*for (int i = 0; i < 10; i++) {
            adapter.add("Mocked item " + Integer.toString(i + 1));
        }*/
        mListViewOfItems.setAdapter(adapter);

        // Adds a listener so that an item can be selected and be highlighted
        mListViewOfItems.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int pos, long l) {
                mItemSelectedIndex = pos;
                // Makes sure something is always selected. If no items selected, it is assigned null
                if (pos != -1) {
                    itemSelected = items.get(pos);
                } else {
                    itemSelected = null;
                }
                Log.d("POSITION: ", Integer.toString(pos));
            }
        });
    }
}
