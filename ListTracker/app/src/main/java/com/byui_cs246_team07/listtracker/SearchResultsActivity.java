package com.byui_cs246_team07.listtracker;

import android.app.SearchManager;
import android.app.SearchableInfo;
import android.content.Intent;
import android.support.v7.app.ActionBar;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.Html;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.support.v7.widget.Toolbar;
import android.widget.ListView;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import models.Item;
import models.ItemList;

/**
 * Search Results - Displays results after search from MainActivity
 * @author David
 */
public class SearchResultsActivity extends AppCompatActivity {

    private final String TAG = this.getClass().getName();
    public static final String LIST_INTENT = "listItemList";
    public static final String ITEM_INTENT = "listItem";

    private ListView searchList;
    private ListView searchItem;

    private String query;
    private ArrayAdapter<String> adapterList;
    private ArrayAdapter<String> adapterItem;
    private List<ItemList> lists;
    private List<Item> items;
    private List<ItemList> itemParent;

    public SearchResultsActivity() {
        itemParent = new ArrayList<ItemList>();
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_search_results);

        handleResourceIds();

        handleIntent(getIntent());

        handleActionBar();

        handleAdapter();

        handleEventListeners();
    }

    @Override
    protected void onResume() {
        super.onResume();
    }

    @Override
    protected void onNewIntent(Intent intent) {
        handleIntent(intent);
    }

    private void handleResourceIds() {
        searchList = findViewById(R.id.search_lists);
        searchItem = findViewById(R.id.search_items);
    }

    private void handleIntent(Intent intent) {
        if (Intent.ACTION_SEARCH.equals(intent.getAction())) {
            query = intent.getStringExtra(SearchManager.QUERY);

            lists = (List<ItemList>) intent.getSerializableExtra(MainActivity.LISTS_ID);
            items = (List<Item>) intent.getSerializableExtra(MainActivity.ITEMS_ID);
        }
    }

    private void handleActionBar() {
        Toolbar myToolbar = findViewById(R.id.search_toolbar);
        setSupportActionBar(myToolbar);

        ActionBar actionBar = getSupportActionBar();
        actionBar.setTitle(Html.fromHtml(
                "<font color=\"#ffffff\">" + "Search Results: " + query + "</font>"
        ));
    }

    private void handleAdapter() {
        adapterList = new ArrayAdapter<String>(this, android.R.layout.simple_list_item_1);
        adapterItem = new ArrayAdapter<String>(this, android.R.layout.simple_list_item_1);
        searchedListAndItems();


        searchList.setAdapter(adapterList);
        searchItem.setAdapter(adapterItem);
    }

    private void searchedListAndItems() {
        // Remove items from the list that is not in the query
        for (Iterator<Item> iterator = items.iterator(); iterator.hasNext();) {
            if (!iterator.next().getName().equalsIgnoreCase(query)) {
                iterator.remove();
            }
        }

        // Look for the parent of a list and populate
        if (!items.isEmpty()) {
            for (int i = 0; i < items.size(); i++) {
                for (int j = 0; j < lists.size(); j++) {
                    if (items.get(i).getListId() == lists.get(j).getId()) {
                        itemParent.add(lists.get(j));
                        Log.d(TAG, items.get(i).getName() + " inside of " + lists.get(j).getName());
                    }
                }
            }

            for (int i = 0; i < items.size(); i++) {
                adapterItem.add(items.get(i).getName() + "\t(" + itemParent.get(i).getName() + ")");
            }
        }

        // Remove from list whatever is not the query
        for (Iterator<ItemList> iterator = lists.iterator(); iterator.hasNext();) {
            if (!iterator.next().getName().equalsIgnoreCase(query)) {
                iterator.remove();
            }
        }

        // After, populate the adapter with the searched query
        for (int i = 0; i < lists.size(); i++) {
            adapterList.add(lists.get(i).getName());
        }
    }

    private void handleEventListeners() {
        searchList.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int pos, long l) {
                Intent intent = new Intent(getApplicationContext(), ListActivity.class);
                intent.putExtra(LIST_INTENT, (Serializable) lists.get(pos));
                intent.putExtra("Class", "SearchActivity.java");
                intent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
                startActivity(intent);
                finish();
            }
        });

        searchItem.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int i, long l) {
                Intent intent = new Intent(getBaseContext(), ItemActivity.class);
                intent.putExtra("Class", "SearchActivity.java");
                intent.putExtra(ITEM_INTENT,(Serializable) items.get(i));
                intent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
                Log.d(TAG, "Sending: " + items.get(i).getName());
                startActivity(intent);
                finish();
            }
        });
    }
}
