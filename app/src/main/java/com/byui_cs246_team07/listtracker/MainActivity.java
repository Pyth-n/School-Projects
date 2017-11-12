package com.byui_cs246_team07.listtracker;

import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Color;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.Toast;

import java.util.List;

import controllers.ItemController;
import controllers.ItemListController;
import models.ItemList;


public class MainActivity extends AppCompatActivity {
    public static final String ITEM_SELECTED = "itemSelected";
    public static final String LISTNAMEID = "com.byui_cs246_team07.listtracker.LISTNAMEID";

    private final String TAG = "MainActivity";
    private final String SORTBY = "sortBy";
    private final String CATEGORY = "categoryID";
    private final String LASTSCREENVIEWED = "lastScreenID";
    private final String LASTLISTVIEWED = "lastListID";
    private final String PREFERENCES = "listPrefs";

    private ItemListController itemListController;
    private ListView listOfLists;
    private List<String> listNames;
    private List<ItemList> lists;
    private ItemList itemListSelected;

    public MainActivity() {
        itemListController = new ItemListController(this);
    }

    /*
    * OnCreate
    */
    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        setListView();

        // TODO move this for a class
        /*ItemController controller = new ItemController(this);
        SharedPreferences settings = getSharedPreferences(PREFERENCES, Context.MODE_PRIVATE);
        controller.setCategoryName(settings.getString(CATEGORY, ""));
        controller.setListName(settings.getString(LASTLISTVIEWED, ""));
        controller.setSortBy(settings.getString(SORTBY, ""));
        Log.d("SHAREDPREFERENCES: ", settings.getString(CATEGORY, "Category Test"));
        Log.d("SHAREDPREFERENCES: ", settings.getString(LASTLISTVIEWED, "Last View Test"));
        Log.d("SHAREDPREFERENCES: ", settings.getString(SORTBY, "Sort By Test"));*/

        // Adds a listener so that an item can be selected and be highlighted

    }

    @Override
    protected void onStop() {
        super.onStop();

        // TODO move this for a sharedPreferenceManage controller
        SharedPreferences settings = getSharedPreferences(PREFERENCES, Context.MODE_PRIVATE);
        SharedPreferences.Editor editor = settings.edit();

        // Sort
        //editor.putString(SORTBY, controller.getSortBy());

        // Category
        //editor.putString(CATEGORY, controller.getCategoryName());

        // Last screen viewed
        //editor.putString(LASTSCREENVIEWED, this.getClass().getSimpleName());

        // List name for widget
        //editor.putString(LASTLISTVIEWED, controller.getListName());

        editor.apply();
    }

    public void createList(View view) {

        Intent intent = new Intent(this, ListCreationActivity.class);
        startActivity(intent);

    }

    public void loadList(View view) {

        if (itemListSelected != null) {
            Intent intent = new Intent(this, ListActivity.class);
            intent.putExtra(ITEM_SELECTED, itemListSelected);
            startActivity(intent);
        } else {
            Toast.makeText(this, "Select List first", Toast.LENGTH_SHORT).show();
        }
    }

    public void viewCategories(View view) {

        Intent intent = new Intent(this, CategoriesActivity.class);
        startActivity(intent);

    }

    public void deleteList(View view) {
      if (itemListSelected != null) {
        itemListController.delete(itemListSelected.getId());
        itemListSelected = null;
        setListView();
      }

    }

    public void sortCategory(View view) {

        Intent intent = new Intent(this, SortListOptionsActivity.class);
        startActivity(intent);

    }

    public void copyList(View view) {

        Intent intent = new Intent(this, ListCopierActivity.class);
        startActivity(intent);

    }

    public void moveList(View view) {

        Intent intent = new Intent(this, ListMoverActivity.class);
        startActivity(intent);

    }

    private void setListView() {
        listNames = itemListController.getListNames();
        lists = itemListController.getLists();
        ArrayAdapter<String> adapter = new ArrayAdapter<>(this,
            android.R.layout.simple_list_item_1, listNames);
        listOfLists = findViewById(R.id.listOfLists);
        listOfLists.setAdapter(adapter);
        Log.d(TAG, "Set View");
        listOfLists.setOnItemClickListener(new AdapterView.OnItemClickListener() {
          @Override
          public void onItemClick(AdapterView<?> adapterView, View view, int pos, long l) {
              itemListSelected = lists.get(pos);
            Log.d("POSITION: ", Integer.toString(pos));
          }
        });
    }

}
