package com.byui_cs246_team07.listtracker;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.Toast;

import java.util.List;

import controllers.ItemController;
import controllers.ItemListController;
import models.Item;
import models.ItemList;

public class ItemCopierActivity extends AppCompatActivity {

    private final String TAG = this.getClass().getName();

    ArrayAdapter<String> adapter;
    private Item itemActive;
    private ItemListController itemListController;
    private ItemController itemController;
    private ListView listOfListsCopy;


    private List<String> listNames;
    private List<ItemList> lists;
    private ItemList itemListSelected;

    public ItemCopierActivity() {
        itemListController = new ItemListController(this);
        itemController = new ItemController(this);
        itemListSelected = null;
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_item_copier);

        itemActive = (Item) getIntent().getSerializableExtra(ListActivity.ITEM);

        setListView();
    }

    /**
     * Creates a new item instance with a copy of itemActive. Sets the new items
     * listID to the list it should be moved. Returns to previous screen.
     * @param view
     */
    public void copyItem(View view) {

        if (itemActive != null && itemActive.getId() != 0) {
            Item item = copyItemValues();
            itemController.saveItem(item);

            Toast.makeText(this, "Copied " + itemActive.getName() + " to "
                    + itemListSelected.getName() + " list", Toast.LENGTH_SHORT).show();

            Log.d(TAG, "Item copied to: " + itemListSelected.getName());
        }

        // Simulates a back key press when button is clicked
        this.dispatchKeyEvent(new KeyEvent(KeyEvent.ACTION_DOWN, KeyEvent.KEYCODE_BACK));
        this.dispatchKeyEvent(new KeyEvent(KeyEvent.ACTION_UP, KeyEvent.KEYCODE_BACK));
    }

    /**
     * Sets up the adapter. Also sets a listener for the array adapter items
     */
    private void setListView() {
        getControllerData();
        adapter = new ArrayAdapter<String>(this, android.R.layout.simple_list_item_1, listNames);
        listOfListsCopy = findViewById(R.id.listOfListsCopy);
        listOfListsCopy.setAdapter(adapter);

        listOfListsCopy.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int pos, long l) {
                listOfListsCopy.setSelector(android.R.color.darker_gray);
                itemListSelected = lists.get(pos);
                Log.d(TAG, listNames.get(pos) + " selected.");
            }
        });
    }

    private void getControllerData() {
        listNames = itemListController.getListNames();
        lists = itemListController.getLists();
    }

    /**
     * Copies itemActive into a new instance, doesn't copy the same ID.
     * @return
     */
    private Item copyItemValues() {
        Item item = new Item(itemActive.getName());
        item.setListId(itemListSelected.getId());
        //item.setId(itemActive.getId());
        item.setCompleted(itemActive.getCompleted());
        item.setNotes(itemActive.getNotes());
        item.setTags(itemActive.getTags());
        item.setPriorityName(itemActive.getPriorityName());
        item.setPriority(itemActive.getPriority());

        return item;
    }
}
