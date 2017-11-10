package com.byui_cs246_team07.listtracker;

import android.content.Context;
import android.content.SharedPreferences;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;
import android.view.View;
import android.view.textservice.TextInfo;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.ListView;

import java.util.ArrayList;
import java.util.List;

import controllers.ItemController;
import models.Item;
import controllers.ItemListController;
import models.ItemList;


public class MainActivity extends AppCompatActivity {

    private final String TAG = "MainActivity";
    private final String SORTBY = "sortBy";
    private final String CATEGORY = "categoryID";
    private final String LASTSCREENVIEWED = "lastScreenID";
    private final String LASTLISTVIEWED = "lastListID";
    private final String PREFERENCES = "listPrefs";
    private ItemListController itemListController;
    private ListView listOfLists;
    private List<String> categoriesNames;

    MainActivity() {
        itemListController = new ItemListController(this);
    }

    /*
    * OnCreate
    */
    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        categoriesNames = itemListController.getListNames(getApplicationContext());
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
        editor.putString(LASTSCREENVIEWED, this.getClass().getSimpleName());

        // List name for widget
        //editor.putString(LASTLISTVIEWED, controller.getListName());

        editor.apply();
    }

    public void addCategory(View view) {

        Log.d(TAG, "addCategory");
        EditText editText = (EditText) findViewById(R.id.categoryName);
        String categoryName = editText.getText().toString();
        if (categoryName != null && categoryName != "") {
            ItemList itemList = new ItemList(categoryName);
            // TODO move the following line to a runnable class
            itemListController.saveItemList(itemList);
            categoriesNames.add(categoryName);
            editText.setText("");
            Log.d(TAG, "Save");
            setListView();
        }
    }

    private void setListView() {

        ArrayAdapter<String> adapter = new ArrayAdapter<String>(this, android.R.layout.simple_list_item_1, categoriesNames);
        listOfLists = (ListView) findViewById(R.id.listOfLists);
        listOfLists.setAdapter(adapter);
        Log.d(TAG, "Set View");
    }

}
