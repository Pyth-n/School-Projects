package com.byui_cs246_team07.listtracker;

import android.Manifest;
import android.app.SearchManager;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.pm.PackageManager;
import android.content.res.Configuration;
import android.os.Bundle;
import android.support.v4.app.ActivityCompat;
import android.support.v7.app.ActionBar;
import android.support.v7.app.AppCompatActivity;

//import android.support.v7.widget.SearchView;
import android.text.Html;
import android.util.Log;
import android.view.Display;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.SearchView;

import android.widget.TextView;
import android.widget.Toast;
import android.support.v7.widget.Toolbar;


import java.io.Serializable;
import java.util.List;

import controllers.ItemController;
import controllers.ItemListController;
import models.Item;
import models.ItemList;

/**
 * Main Activity - Shows list items in category
 * @author David Perez, Timothy Bohman, Carlos Iribar
 * @version 1
 */
public class MainActivity extends AppCompatActivity {

    public static final String ITEM_SELECTED = "itemSelected";
    public static final String LISTNAMEID = "com.byui_cs246_team07.listtracker.LISTNAMEID";
    public static final String LISTS_ID = "listItemList";
    public static final String ITEMS_ID = "listItem";
    private final String TAG = this.getClass().getName();
    private final String SORTBY = "sortBy";
    private final String CATEGORY = "categoryID";
    private final String LASTSCREENVIEWED = "lastScreenID";
    private final String LASTLISTVIEWED = "lastListID";
    private final String PREFERENCES = "listPrefs";
    private final Integer SORT_ACTIVITY = 1;
    private final String ORDER_BY = "ORDER_BY";
    private String orderBy;

    ArrayAdapter<String> adapter;
    private ItemListController itemListController;
    private ItemController itemController;
    private ListView listOfLists;
    private List<String> listNames;
    private List<ItemList> lists;
    private ItemList itemListSelected;
    private int itemListSelectedIndex;
    private SharedPreferences settings;
    private List<Item> items;

    SearchView searchView;
    /**
     * Constructor
     */
    public MainActivity() {
        itemListController = new ItemListController(this);
        itemController = new ItemController(this);
        itemListSelectedIndex = -1;
    }

    /*
    * OnCreate
    */
    @Override
    protected void onCreate(Bundle savedInstanceState) {

        //this.deleteDatabase("listTracker.db");

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        ActivityCompat.requestPermissions(MainActivity.this,
                new String[]{Manifest.permission.READ_EXTERNAL_STORAGE},1);

        ActivityCompat.requestPermissions(MainActivity.this,
                new String[]{Manifest.permission.MANAGE_DOCUMENTS},2);

        ActivityCompat.requestPermissions(MainActivity.this,
                new String[] {Manifest.permission.INTERNET}, 3);

        setListView();


        settings = getSharedPreferences(PREFERENCES, Context.MODE_PRIVATE);
        orderBy = settings.getString(ORDER_BY, "date");

        Log.d("SHAREDPREFERENCES: ", settings.getString(ORDER_BY, "date"));

        // Setup toolbar
        Toolbar myToolbar = (Toolbar) findViewById(R.id.main_toolbar);
        setSupportActionBar(myToolbar);

        if (getScreenOrientation() == 1) {
           ActionBar actionBar = getSupportActionBar();
           actionBar.setTitle(Html.fromHtml(
                "<font color=\"#ffffff\">" + getString(R.string.app_name) + "</font>"
        ));
        }

    }

    @Override
    public void onRequestPermissionsResult(int requestCode, String permissions[], int[] grantResults) {
        switch (requestCode) {
            case 1: {
                // If request is cancelled, the result arrays are empty.
                if (grantResults.length > 0
                        && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                    // permission granted and now can proceed
                    Toast.makeText(this, "external accepted", Toast.LENGTH_SHORT).show(); //a sample method called

                } else {

                    // permission denied
                    Toast.makeText(MainActivity.this, "Permission denied to read your External storage", Toast.LENGTH_SHORT).show();
                }
                //return;
            }
            case 2:
                if (grantResults.length > 0
                        && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                    // permission granted and now can proceed
                    Toast.makeText(this, "manage accepted", Toast.LENGTH_SHORT).show(); //a sample method called

                } else {

                    // permission denied
                    Toast.makeText(MainActivity.this, "Permission denied to read your External storage", Toast.LENGTH_SHORT).show();
                }
                return;
            // add other cases for more permissions
        }
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.action_buttons, menu);


        SearchManager searchManager = (SearchManager) getSystemService(Context.SEARCH_SERVICE);
        searchView = (SearchView) menu.findItem(R.id.action_search).getActionView();
        searchView.setSearchableInfo(searchManager.getSearchableInfo(getComponentName()));

        searchView.setOnQueryTextFocusChangeListener(new View.OnFocusChangeListener() {
            @Override
            public void onFocusChange(View view, boolean b) {
                if (!b) {
                    searchView.setIconified(true);
                    //searchView.clearFocus();
                }
            }
        });

        searchView.setOnQueryTextListener(new SearchView.OnQueryTextListener() {
            @Override
            public boolean onQueryTextSubmit(String s) {
                if (searchView != null) {
                    searchView.setIconified(true);
                    searchView.setIconified(true);
                    Log.d(TAG, "You queried: " + s);
                }
                return false;
            }

            @Override
            public boolean onQueryTextChange(String s) {
                return true;
            }
        });

        return true;
    }

    @Override
    public void startActivity(Intent intent) {
        // If new intent is from the search bar
        if (Intent.ACTION_SEARCH.equals(intent.getAction())) {
            intent.putExtra(LISTS_ID, (Serializable)lists);
            intent.putExtra(ITEMS_ID, (Serializable)items);
        }

        itemListSelectedIndex = -1;
        listOfLists.setSelector(android.R.color.transparent);

        super.startActivity(intent);
    }

    @Override
    protected void onResume() {
        super.onResume();
        items = itemController.getItems();

    }

    @Override
    protected void onPause() {
        super.onPause();


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

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        // Check which request we're responding to
        if (requestCode == SORT_ACTIVITY) {
            // Make sure the request was successful
            if (resultCode == RESULT_OK) {
                Log.d("Sorty by", data.getStringExtra(SortListOptionsActivity.SORT_BY));
                orderBy = data.getStringExtra(SortListOptionsActivity.SORT_BY);
                Log.d("Reodering", orderBy);
                setListView();
                SharedPreferences.Editor editor = settings.edit();
                editor.putString(ORDER_BY, orderBy);
            }
        }
    }

    private int getScreenOrientation()
    {
        Display getOrient = getWindowManager().getDefaultDisplay();
        int orientation = Configuration.ORIENTATION_UNDEFINED;
        if(getOrient.getWidth()==getOrient.getHeight()){
            orientation = Configuration.ORIENTATION_SQUARE;
        } else{
            if(getOrient.getWidth() < getOrient.getHeight()){
                orientation = Configuration.ORIENTATION_PORTRAIT;
            }else {
                orientation = Configuration.ORIENTATION_LANDSCAPE;
            }
        }
        return orientation;
    }

    /**
     * Starts List Creation Activity
     * @param view
     */
    public void createList(View view) {

        Intent intent = new Intent(this, ListCreationActivity.class);
        startActivity(intent);

    }

    /**
     * Starts List Activity
     * @param view
     */
    public void loadList(View view) {

        if (itemListSelected != null && itemListSelectedIndex != -1) {
            Intent intent = new Intent(this, ListActivity.class);
            intent.putExtra(ITEM_SELECTED, itemListSelected);
            intent.putExtra(LISTNAMEID, itemListSelected.getName());
            intent.putExtra("Class", "MainActivity.java");
            startActivity(intent);
        } else {
            Toast.makeText(this, "Select List first", Toast.LENGTH_SHORT).show();
        }
    }

    /**
     * Starts Category Activity
     * @param view
     */
    public void viewCategories(View view) {

        Intent intent = new Intent(this, CategoriesActivity.class);
        startActivity(intent);

    }

    /**
     * Delete list from category
     * @param view
     */
    public void deleteList(View view) {
        if (itemListSelected != null && itemListSelectedIndex != -1) {
            String deleted = "Deleted " + itemListSelected.getName();
            listOfLists.setSelector(android.R.color.transparent);
            adapter.remove(adapter.getItem(itemListSelectedIndex));
            itemListController.delete(itemListSelected.getId());
            itemListSelected = null;
            getControllerData();
            Toast.makeText(this, deleted, Toast.LENGTH_SHORT).show();
            adapter.notifyDataSetChanged();
        } else {
            Toast.makeText(this, "Select a list to delete", Toast.LENGTH_SHORT).show();
        }
    }

    /**
     * Starts ShortListOptions Activity
     * @param view
     */
    public void sortCategory(View view) {

        Intent intent = new Intent(this, SortListOptionsActivity.class);
        startActivityForResult(intent, SORT_ACTIVITY);

    }

    /**
     * Starts ListCopier Activity
     * @param view
     */
    public void copyList(View view) {

        Intent intent = new Intent(this, ListCopierActivity.class);
        startActivity(intent);

    }

    /**
     * Starts ListMover Activity
     * @param view
     */
    public void moveList(View view) {

        Intent intent = new Intent(this, ListMoverActivity.class);
        startActivity(intent);

    }

    /**
     * Renames category
     * @param view
     */
    public void renameCategory(View view) {

        Log.d(TAG, "Category renamed");
    }

    /**
     * Set adapters and list views listeners
     */
    private void setListView() {
        getControllerData();
        adapter = new ArrayAdapter<String>(this,
                android.R.layout.simple_list_item_1, listNames) {
            @Override
            public View getView(int position, View convertView, ViewGroup parent) {
                View view = super.getView(position, convertView, parent);
                TextView textView = (TextView) super.getView(position, convertView, parent);
                if (!lists.isEmpty()) {
                    ItemList item = lists.get(position);
                    textView.setText(item.getName());
                }

                return view;
            }

        };


        listOfLists = (ListView) findViewById(R.id.listOfLists);
        listOfLists.setAdapter(adapter);
        Log.d(TAG, "Set View");

        listOfLists.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int pos, long l) {
                listOfLists.setSelector(android.R.color.darker_gray);
                itemListSelected = lists.get(pos);
                itemListSelectedIndex = pos;
                Log.d("POSITION: ", Integer.toString(pos));
            }

        });
        adapter.notifyDataSetChanged();
    }

    /**
     * Populates list and list names
     */
    private void getControllerData() {
        listNames = itemListController.getListNames(orderBy);
        lists = itemListController.getLists(orderBy);
    }

}
