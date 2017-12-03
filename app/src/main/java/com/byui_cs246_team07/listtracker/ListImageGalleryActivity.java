package com.byui_cs246_team07.listtracker;

import android.content.Intent;
import android.net.Uri;
import android.support.v7.app.ActionBar;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.widget.GridLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.support.v7.widget.Toolbar;
import android.text.Html;
import android.util.Log;
import android.widget.ArrayAdapter;
import android.widget.ImageView;
import android.widget.LinearLayout;

import com.squareup.picasso.Picasso;

import java.net.URI;
import java.util.ArrayList;
import java.util.List;

import controllers.ItemController;
import gallery.ImageData;
import gallery.ImgAdapter;
import models.Item;
import models.ItemList;

/**
 * @author David
 */
public class ListImageGalleryActivity extends AppCompatActivity {

    private final String TAG = this.getClass().getName();
    private ItemList list;
    private List<Item> items;

    public ListImageGalleryActivity() {
        items = new ArrayList<>();
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_list_image_gallery);

        handleIntent(getIntent());
        handleActionBar();

        handleImageViews();
    }

    private void handleIntent(Intent intent) {
        String fromClass = intent.getStringExtra("Class");

        if (fromClass.equals("ListActivity.java")) {
            list = (ItemList) intent.getSerializableExtra(ListActivity.LIST_ID);
            items = (List<Item>) intent.getSerializableExtra(ListActivity.ITEM);

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

    private void handleImageViews() {
        RecyclerView recyclerView = findViewById(R.id.img_recyclerView);
        recyclerView.setHasFixedSize(true);
        ArrayList<ImageData> createLists = getImageData();
        RecyclerView.LayoutManager layoutManager =
                new GridLayoutManager(getApplicationContext(), 2);
        recyclerView.setLayoutManager(layoutManager);

        ArrayList<ImageData> imgData = getImageData();
        ImgAdapter adapter = new ImgAdapter(getApplicationContext(), imgData);
        recyclerView.setAdapter(adapter);
    }

    private ArrayList<ImageData> getImageData() {
        List<ImageData> tmp = new ArrayList<>();

        for (int i = 0; i < items.size(); i++) {
            if (items.get(i).getImagesUrls().size() > 0) {
                for (int j = 0; j < items.get(i).getImagesUrls().size(); j++) {
                    ImageData imageData = new ImageData();
                    imageData.setItemName(items.get(i).getName());
                    imageData.setUri(items.get(i).getImagesUrls().get(j));
                    tmp.add(imageData);
                }
            }
        }

        return (ArrayList<ImageData>) tmp;
    }
}
