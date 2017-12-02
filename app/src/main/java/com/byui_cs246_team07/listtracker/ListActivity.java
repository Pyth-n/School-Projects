package com.byui_cs246_team07.listtracker;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.ActionBar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.text.Html;
import android.util.Log;
import android.view.View;
import android.view.ViewGroup;
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

/**
 * Shows list and items
 * @author David Perez, Timothy Bohman, Carlos Iribar
 * @version 1
 */
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

    ArrayAdapter<String> adapter;
    private ItemListController controller;
    private ItemController itemController;
    private List<Item> items;
    private int mItemSelectedIndex;
    private Item itemSelected;
    private String nameOfList;
    private ItemList list;


    /**
     * Constructor
     */
    public ListActivity() {
        controller = new ItemListController(this);
        itemController = new ItemController(this);
        adapter = null;
        mItemSelectedIndex = -1;
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_list);
        itemSelected = null;

        // Sets resource IDs
        mListName = findViewById(R.id.listNameInListScreen);
        mListViewOfItems = findViewById(R.id.listOfItems);

        handleIntent(getIntent());

        handleActionBar();
    }

    private void handleIntent(Intent intent) {
        String fromClass = intent.getStringExtra("Class");

        if (fromClass.equals("MainActivity.java")) {
            list = (ItemList) intent.getSerializableExtra(MainActivity.ITEM_SELECTED);
            nameOfList = getIntent().getStringExtra(MainActivity.LISTNAMEID);
        }

        if (fromClass.equals("SearchActivity.java")) {
            list = (ItemList) intent.getSerializableExtra(SearchResultsActivity.LIST_INTENT);
            nameOfList = list.getName();
        }
    }

    @Override
    protected void onResume() {
        super.onResume();

        setListView();

        Log.d(TAG, "RESUMING");
    }

    @Override
    public void onPause() {
        super.onPause();

        Log.d(TAG, "PAUSING");
    }

    private void handleActionBar() {
        Toolbar myToolbar = findViewById(R.id.gallery_toolbar);
        setSupportActionBar(myToolbar);

        ActionBar actionBar = getSupportActionBar();
        actionBar.setTitle(Html.fromHtml(
                "<font color=\"#ffffff\">" + "List: " + nameOfList + "</font>"
        ));
    }

    /**
     * Starts Item Activity for create new items
     * @param v
     */
    public void createItem(View v) {
        // Will send intent to the ItemActivity
        Intent intent = new Intent(this, ItemActivity.class);
        intent.putExtra(PARENT_LIST, list);
        intent.putExtra(BUTTON_PRESSED, "createItem");
        intent.putExtra("Class", "ListActivity.java");

        Log.d(TAG, "Sending " + intent.getStringExtra(LIST_ID));
        startActivity(intent);
    }

    /**
     * Starts Item Activity and load an item
     * @param view
     */
    public void loadItem(View view) {
        // Makes sure an item is selected before creating and sending an intent
        if (mItemSelectedIndex != -1) {
            if (!items.isEmpty()) {
                Item item = items.get(mItemSelectedIndex);
                Intent intent = new Intent(this, ItemActivity.class);
                intent.putExtra(PARENT_LIST, list);
                intent.putExtra(ITEM, item);
                intent.putExtra(BUTTON_PRESSED, "loadItem");
                intent.putExtra("Class", "ListActivity.java");
                startActivity(intent);
            } else {
                // TODO if its empty, start a create item, else it crashes
                Toast.makeText(this, "Create an item first", Toast.LENGTH_SHORT).show();
            }

        } else {
            Toast.makeText(this, "Select an Item first", Toast.LENGTH_SHORT).show();
        }
    }

    /**
     * Delete item in the list
     * @param view
     */
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

    /**
     * Starts ItemCopierActivity
     * @param view
     */
    public void copyItem(View view) {
        if (itemSelected != null) {
            Log.d(TAG, "Copying " + itemSelected.getName());
            if (!items.isEmpty()) {
                Item item = items.get(mItemSelectedIndex);
                Intent intent = new Intent(this, ItemCopierActivity.class);
                intent.putExtra(ITEM, item);
                startActivity(intent);
            }
        }
    }

    /**
     * Starts ItemMoverActivity
     * @param view
     */
    public void moveItem(View view) {
        if (itemSelected != null) {
            Log.d(TAG, "Moving " + itemSelected.getName());
            if (!items.isEmpty()) {
                Item item = items.get(mItemSelectedIndex);
                Intent intent = new Intent(this, ItemMoverActivity.class);
                intent.putExtra(ITEM, item);
                startActivity(intent);
            }
        }
    }


    /**
     * Starts SortListOptions Activity
     * @param view
     */
    public void sortList(View view) {

        Intent intent = new Intent(this, SortListOptionsActivity.class);
        startActivity(intent);

    }

    /**
     * Starts ListImageGallery Activity
     * @param view
     */
    public void viewImageGallery(View view) {

        Intent intent = new Intent(this, ListImageGalleryActivity.class);
        intent.putExtra("Class", "ListActivity.java");
        intent.putExtra(LIST_ID, list);
        startActivity(intent);

    }

    /**
     * Renames selected list
     * @param view
     */
    public void renameList(View view) {

        Log.d(TAG, "List renamed");
    }

    /**
     * Sets adapters and list view listeners
     */
    public void setListView() {
        // Set the name of the list
        if (list != null) {
            mListName.setText(list.getName());
            // Set items
            items = controller.getRelatedItems(list.getId());
        }

        // Adapter used add items and display in the ListView
        adapter = new ArrayAdapter<String>(this, android.R.layout.simple_list_item_1) {
            @Override
            public View getView(int position, View convertView, ViewGroup parent) {
                TextView textView = (TextView) super.getView(position, convertView, parent);
                if (!items.isEmpty()) {
                    if (itemSelected != null) {
                        textView.setText(items.get(position).getName());
                    }
                }
                return textView;
            }
        };
        if (items != null) {
            for (Item item : items) {
                adapter.add(item.getName());
            }
        }

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
