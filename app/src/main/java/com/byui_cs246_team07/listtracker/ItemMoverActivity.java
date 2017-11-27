package com.byui_cs246_team07.listtracker;

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

public class ItemMoverActivity extends AppCompatActivity {

    private final String TAG = this.getClass().getName();

    ArrayAdapter<String> adapter;
    private Item itemActive;
    private ItemListController itemListController;
    private ItemController itemController;
    private ListView listOfListsMove;


    private List<String> listNames;
    private List<ItemList> lists;
    private ItemList itemListSelected;

    public ItemMoverActivity() {
        itemListController = new ItemListController(this);
        itemController = new ItemController(this);
        itemListSelected = null;
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_item_mover);

        itemActive = (Item) getIntent().getSerializableExtra(ListActivity.ITEM);
        setListView();
    }

    /**
     * Sets the itemActive listID to the selected list's ID, which moves it to that list.
     * Returns to previous screen.
     * @param view
     */
    public void moveItem(View view) {
        if (itemActive != null && itemActive.getId() != 0) {
            itemActive.setListId(itemListSelected.getId());
            itemController.saveItem(itemActive);

            Toast.makeText(this, "Moved " + itemActive.getName() + " to "
            + itemListSelected.getName() + " list", Toast.LENGTH_SHORT).show();
            Log.d(TAG, "Item moved to: " + itemListSelected.getName());
        }

        // Simulates a back key press when button is clicked
        this.dispatchKeyEvent(new KeyEvent(KeyEvent.ACTION_DOWN, KeyEvent.KEYCODE_BACK));
        this.dispatchKeyEvent(new KeyEvent(KeyEvent.ACTION_UP, KeyEvent.KEYCODE_BACK));
    }

    private void setListView() {
        getControllerData();
        adapter = new ArrayAdapter<String>(this, android.R.layout.simple_list_item_1, listNames);
        listOfListsMove = findViewById(R.id.listOfListsMove);
        listOfListsMove.setAdapter(adapter);

        listOfListsMove.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int pos, long l) {
                listOfListsMove.setSelector(android.R.color.darker_gray);
                itemListSelected = lists.get(pos);
                Log.d(TAG, listNames.get(pos) + " selected.");
            }
        });
    }

    private void getControllerData() {
        listNames = itemListController.getListNames();
        lists = itemListController.getLists();
    }
}
