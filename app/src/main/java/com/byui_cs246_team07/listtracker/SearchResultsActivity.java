package com.byui_cs246_team07.listtracker;

import android.app.SearchManager;
import android.content.Intent;
import android.support.v7.app.ActionBar;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.Html;
import android.util.Log;
import android.widget.ArrayAdapter;
import android.support.v7.widget.Toolbar;
import android.widget.ListView;

import java.util.ArrayList;
import java.util.List;

public class SearchResultsActivity extends AppCompatActivity {

    private ListView listView;

    private String query;
    private ArrayAdapter<String> adapter;
    private List<String> results;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_search_results);

        Toolbar myToolbar = findViewById(R.id.search_toolbar);
        setSupportActionBar(myToolbar);

        ActionBar actionBar = getSupportActionBar();

        listView = findViewById(R.id.search_lists);


        handleIntent(getIntent());
        actionBar.setTitle(Html.fromHtml(
                "<font color=\"#ffffff\">" + "Search Results: " + query + "</font>"
        ));

        results = new ArrayList<>();
        results.add(query);
        adapter = new ArrayAdapter<String>(this, android.R.layout.simple_list_item_1, results);

        listView.setAdapter(adapter);
    }

    @Override
    protected void onNewIntent(Intent intent) {
        handleIntent(intent);
    }

    private void handleIntent(Intent intent) {
        if (Intent.ACTION_SEARCH.equals(intent.getAction())) {
            query = intent.getStringExtra(SearchManager.QUERY);
            //use the query to search your data somehow
            Log.d("LOOL", query);
        }
    }
}
