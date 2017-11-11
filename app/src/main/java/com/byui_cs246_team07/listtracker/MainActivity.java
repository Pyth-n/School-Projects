package com.byui_cs246_team07.listtracker;

import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Color;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;

import java.util.List;

import controllers.ItemController;
import controllers.ItemListController;


public class MainActivity extends AppCompatActivity {

    private final String TAG = "MainActivity";
    private final String SORTBY = "sortBy";
    private final String CATEGORY = "categoryID";
    private final String LASTSCREENVIEWED = "lastScreenID";
    private final String LASTLISTVIEWED = "lastListID";
    private final String PREFERENCES = "listPrefs";
    private ItemListController itemListController;
    private ListView listOfLists;
    private List<String> listNames;

    private int mItemSelectedIndex;

    public MainActivity() {
        itemListController = new ItemListController(this);
        mItemSelectedIndex = -1;
    }

    /*
    * OnCreate
    */
    @Override
    protected void onCreate(Bundle savedInstanceState) {

        //Remove this line after run once
        //this.deleteDatabase("listTracker.db");

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        listNames = itemListController.getListNames();
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
        listOfLists.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int pos, long l) {
                mItemSelectedIndex = pos;
                Log.d("POSITION: ", Integer.toString(pos));
            }
        });
    }

    @Override
    protected void onStop() {
        super.onStop();

        // TODO move this for a sharedPreferenceManage controller
        SharedPreferences settings = getSharedPreferences(PREFERENCES, Context.MODE_PRIVATE);
        SharedPreferences.Editor editor = settings.edit();

        ItemController controller = new ItemController(this);
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

        Intent intent = new Intent(this, ListActivity.class);
        startActivity(intent);

    }

    public void viewCategories(View view) {

        Intent intent = new Intent(this, CategoriesActivity.class);
        startActivity(intent);

    }

    public void sortCategory(View view) {

        Intent intent = new Intent(this, SortListOptionsActivity.class);
        startActivity(intent);

    }

    private void setListView() {
        ArrayAdapter<String> adapter = new ArrayAdapter<String>(this,
            android.R.layout.simple_list_item_1, listNames);
        listOfLists = (ListView) findViewById(R.id.listOfLists);
        listOfLists.setAdapter(adapter);
        Log.d(TAG, "Set View");
    }

}
