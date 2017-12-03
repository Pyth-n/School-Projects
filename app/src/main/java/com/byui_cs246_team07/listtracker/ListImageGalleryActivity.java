package com.byui_cs246_team07.listtracker;

import android.content.Intent;
import android.net.Uri;
import android.support.v7.app.ActionBar;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.widget.RecyclerView;
import android.support.v7.widget.Toolbar;
import android.text.Html;
import android.util.Log;
import android.widget.ImageView;
import android.widget.LinearLayout;

import com.squareup.picasso.Picasso;

import java.net.URI;
import java.util.ArrayList;
import java.util.List;

import controllers.ItemController;
import models.Item;
import models.ItemList;

/**
 * @author David
 */
public class ListImageGalleryActivity extends AppCompatActivity {

    private final String TAG = this.getClass().getName();
    private ItemList list;
    private List<Item> items;
    private List<List<String>> uris;

    public ListImageGalleryActivity() {
        items = new ArrayList<>();
        uris = new ArrayList<List<String>>();
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_list_image_gallery);

        handleIntent(getIntent());
        handleActionBar();

        Uri tmp = Uri.parse(uris.get(0).get(0));
        LinearLayout linearLayout = findViewById(R.id.img_linear);

        ImageView imageView = new ImageView(this);
        imageView.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT,
                LinearLayout.LayoutParams.WRAP_CONTENT));

        linearLayout.addView(imageView);

        Picasso.with(this)
                .load(tmp)
                .into(imageView);

    }

    private void handleIntent(Intent intent) {
        String fromClass = intent.getStringExtra("Class");

        if (fromClass.equals("ListActivity.java")) {
            list = (ItemList) intent.getSerializableExtra(ListActivity.LIST_ID);
            items = (List<Item>) intent.getSerializableExtra(ListActivity.ITEM);

            for (int i = 0; i < items.size(); i++) {
                if (items.get(i).getImagesUrls().size() > 0) {
                    uris.add(items.get(i).getImagesUrls());
                }
            }

            Log.d(TAG, "Image gallery: " + list.getName());
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
