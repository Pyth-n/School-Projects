package com.byui_cs246_team07.listtracker;

import android.content.Intent;
import android.support.v7.app.ActionBar;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.widget.Toolbar;
import android.text.Html;
import android.util.Log;

import java.util.List;

import models.ItemList;

public class ListImageGalleryActivity extends AppCompatActivity {

    private final String TAG = this.getClass().getName();
    private ItemList list;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_list_image_gallery);

        handleIntent(getIntent());
        handleActionBar();
    }

    private void handleIntent(Intent intent) {
        String fromClass = intent.getStringExtra("Class");

        list = (ItemList) intent.getSerializableExtra(ListActivity.LIST_ID);
        if (fromClass.equals("ListActivity.java")) {
            Log.d(TAG, list.getName());
        }
    }

    private void handleActionBar() {
        Toolbar toolbar = findViewById(R.id.gallery_toolbar);
        setSupportActionBar(toolbar);

        ActionBar actionBar = getSupportActionBar();
        actionBar.setTitle(Html.fromHtml(
                "<font color=\"#ffffff\">" + list.getName() + " images" + "</font>"
        ));
    }
}
