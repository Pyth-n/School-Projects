package com.byui_cs246_team07.listtracker;

import android.app.SearchManager;
import android.content.Intent;
import android.support.v7.app.ActionBar;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.Html;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.support.v7.widget.Toolbar;
import android.widget.ListView;

import java.util.ArrayList;
import java.util.List;

public class SearchResultsActivity extends AppCompatActivity {

    private final String TAG = this.getClass().getName();

    private ListView searchList;
    private ListView searchItem;

    private String query;
    private ArrayAdapter<String> adapterList;
    private ArrayAdapter<String> adapterItem;
    private List<String> lists;
    private List<String> items;

    public SearchResultsActivity() {

    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_search_results);

        handleToolbar();

        handleResourceIds();

        handleIntent(getIntent());

        handleActionBar();

        handleAdapter();
    }

    @Override
    protected void onResume() {
        super.onResume();
        searchList.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int pos, long l) {
                searchList.setSelector(android.R.color.darker_gray);

            }
        });
    }

    @Override
    protected void onNewIntent(Intent intent) {
        handleIntent(intent);
    }

    private void handleToolbar() {
        Toolbar myToolbar = findViewById(R.id.search_toolbar);
        setSupportActionBar(myToolbar);
    }

    private void handleResourceIds() {
        searchList = findViewById(R.id.search_lists);
    }

    private void handleIntent(Intent intent) {
        if (Intent.ACTION_SEARCH.equals(intent.getAction())) {
            query = intent.getStringExtra(SearchManager.QUERY);

            // gets the list names
            lists = intent.getStringArrayListExtra("KEY1");
            items = intent.getStringArrayListExtra("KEY2");
        }
    }

    private void handleActionBar() {
        ActionBar actionBar = getSupportActionBar();
        actionBar.setTitle(Html.fromHtml(
                "<font color=\"#ffffff\">" + "Search Results: " + query + "</font>"
        ));
    }

    private void handleAdapter() {
        List<String> results = searchedListAndItems();

        adapterList = new ArrayAdapter<String>(this, android.R.layout.simple_list_item_1);

        for (String str : results) {
            adapterList.add(str);
        }
        searchList.setAdapter(adapterList);
    }

    private List<String> searchedListAndItems() {
        List<String> results = new ArrayList<String>();

        if(!lists.isEmpty()) {
           for (int i = 0; i < lists.size(); i++) {
               if (lists.get(i).equalsIgnoreCase(query))
                   results.add(lists.get(i) + " (List)");
           }
        }

        if(!items.isEmpty()) {
            for (int i = 0; i < items.size(); i++) {
                if (items.get(i).equalsIgnoreCase(query))
                    results.add(items.get(i) + " (Item)");
            }
        }
        return results;
    }
}
