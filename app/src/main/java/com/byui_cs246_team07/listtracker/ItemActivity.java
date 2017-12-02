package com.byui_cs246_team07.listtracker;

import android.Manifest;
import android.content.Intent;
import android.graphics.Bitmap;
import android.net.Uri;
import android.provider.MediaStore;
import android.support.v7.app.ActionBar;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.widget.Toolbar;
import android.text.Editable;
import android.text.Html;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import controllers.ItemController;
import controllers.ItemListController;
import models.Item;
import models.ItemList;

public class ItemActivity extends AppCompatActivity {

    private static final int REQUEST_STORAGE_PERMISSIONS = 1;
    private static final String[] STORAGE_PERMISSIONS = {
            Manifest.permission.READ_EXTERNAL_STORAGE,
            Manifest.permission.MANAGE_DOCUMENTS
    };

    private final int PICK_IMAGE_REQUEST = 1;
    final int THUMBNAIL_SIZE = 128;
    private ItemList parentList;
    private ItemController controller;
    private ItemListController listController;
    private final String TAG = this.getClass().getName();
    // IDs of widgets
    private EditText mItemName;
    private EditText mTag;
    private EditText mDueDate;
    private TextView mDateCreated;
    private TextView mDateModified;
    private CheckBox mCompleted;
    private EditText mPriorityNumber;
    private EditText mPriorityName;
    private EditText mNotes;
    private ImageView mimage_1;
    private ImageView mimage_2;

    private Item itemActive;
    private List<String> mNewImageUrls;

    public ItemActivity() {
        controller = new ItemController(this);
        listController = new ItemListController(this);
        mNewImageUrls = new ArrayList<String>();
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_item);

        // find resource IDs
        getItemValues();
        handleIntent(getIntent());

        if (itemActive != null)
            setItemValues(itemActive);

        handleActionBar();
    }

    private ItemList getItemList() {
        List<ItemList> temp = listController.getLists();

        for (int i = 0; i < temp.size(); i++) {
            if (temp.get(i).getId() == itemActive.getListId()) {
                Log.d(TAG, "Parent list is: " + temp.get(i).getName());
                return temp.get(i);
            }
        }

        return null;
    }

    private void handleIntent(Intent intent) {
        String fromClass = intent.getStringExtra("Class");

        if (fromClass.equals("SearchActivity.java")) {
            itemActive = (Item) intent.getSerializableExtra(SearchResultsActivity.ITEM_INTENT);
            parentList = getItemList();
        }

        if (fromClass.equals("ListActivity.java")) {
            // Set name of the list
            parentList = (ItemList) getIntent().getSerializableExtra(ListActivity.PARENT_LIST);

            // Differentiate between the buttons that sent the intent
            String buttonName = getIntent().getStringExtra(ListActivity.BUTTON_PRESSED);
            if (buttonName.equals("createItem")) {
                itemActive = null;
                //Toast.makeText(this, "CREATING...", Toast.LENGTH_SHORT).show();
            } else if (buttonName.equals("loadItem")) {
                itemActive = (Item) getIntent().getSerializableExtra(ListActivity.ITEM);
                Log.d("Set Item", itemActive.getName());
                Toast.makeText(this, "Loading " + itemActive.getName(), Toast.LENGTH_SHORT).show();
            }
        }
    }

    private void handleActionBar() {
        Toolbar myToolbar = findViewById(R.id.item_toolbar);
        setSupportActionBar(myToolbar);

        ActionBar actionBar = getSupportActionBar();
        actionBar.setTitle(Html.fromHtml(
                "<font color=\"#ffffff\">" + "Item within " + parentList.getName() + "</font>"
        ));
    }

    @Override
    protected void onResume() {

        super.onResume();

    }

    @Override
    protected void onNewIntent(Intent intent) {

    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        if (requestCode == PICK_IMAGE_REQUEST && resultCode == RESULT_OK && data != null && data.getData() != null) {

            Log.d(TAG, "Image selected");
            Uri uri = data.getData();
            Log.d(TAG, "Image URI: " + uri);
            mNewImageUrls.add(uri.toString());

            try {
                Bitmap imgThumbnailBitmap = MediaStore.Images.Media.getBitmap(getContentResolver(), uri);
                imgThumbnailBitmap = Bitmap.createScaledBitmap(imgThumbnailBitmap, THUMBNAIL_SIZE, THUMBNAIL_SIZE, false);
                mimage_1.setImageBitmap(imgThumbnailBitmap);
                Log.d(TAG, "Image display succeeded");
            } catch (IOException e) {
                e.printStackTrace();
                Log.d(TAG, "Image display failed");
            }
        }
    }

    public void saveItem(View view) {

        if (!mItemName.getText().toString().equals("")) {
            Item item = createItem();
            controller.saveItem(item);
            Log.d(TAG, "Item saved");
            Toast.makeText(this, "Item saved", Toast.LENGTH_SHORT).show();

            // Simulates a back key press when button is clicked
            this.dispatchKeyEvent(new KeyEvent(KeyEvent.ACTION_DOWN, KeyEvent.KEYCODE_BACK));
            this.dispatchKeyEvent(new KeyEvent(KeyEvent.ACTION_UP, KeyEvent.KEYCODE_BACK));
        } else {
            Toast.makeText(this, "Add at least a name", Toast.LENGTH_SHORT).show();
        }

    }

    private Item createItem() {

        Item item = new Item(mItemName.getText().toString());
        if (itemActive != null && itemActive.getId() != 0) {
            item.setId(itemActive.getId());
        }
        item.setListId(parentList.getId());
        item.setCompleted(mCompleted.isChecked());
        item.setNotes(mNotes.getText().toString());
        item.setTags(mTag.getText().toString());
        item.setPriorityName(mPriorityName.getText().toString());
        Editable priorityNumberEditable = mPriorityNumber.getText();
        item.setImagesUrls(mNewImageUrls);

        try {
            String priorityNum = mPriorityNumber.getText().toString();
            if (priorityNum != null && priorityNum != "") {
                item.setPriority(Integer.valueOf(mPriorityNumber.getText().toString()));
            }
        } catch (NumberFormatException e) {
            Log.d(TAG, "not a number");
        }

        return item;
    }

    private void getItemValues() {

        mItemName = (EditText) findViewById(R.id.editItemName);
        mNotes = (EditText) findViewById(R.id.editNotes);
        mPriorityNumber = (EditText) findViewById(R.id.priorityNumber);
        mCompleted = (CheckBox) findViewById(R.id.completed);
        mPriorityName = (EditText) findViewById(R.id.priorityLevelName);
        mTag = (EditText) findViewById(R.id.editTags);
        mDateCreated = (TextView) findViewById(R.id.dateCreated);
        mimage_1 = findViewById(R.id.image_1);
        mimage_2 = findViewById(R.id.image_2);

    }

    private void setItemValues(Item item) {

        mItemName.setText(item.getName());
        mDateCreated.setText(item.getCreatedDateString());
        if (item.getNotes() != null) {
            mNotes.setText(item.getNotes());
        }
        if (item.getPriority() != null) {
            String priority = String.valueOf(item.getPriority());
            Log.d("Priori", priority);
            mPriorityNumber.setText(priority);
        }
        if (item.getCompleted() != null) {
            mCompleted.setChecked(item.getCompleted());
        }
        if (item.getNotes() != null) {
            mNotes.setText(item.getNotes());
        }
        if (item.getPriorityName() != null) {
            mPriorityName.setText(item.getPriorityName());
        }
        if (item.getTags() != null) {
            Log.d("Tags", item.getTags());
            mTag.setText(item.getTags());
        }

        if (item.getImagesUrls().size() > 0) {

            try {
                Bitmap img = MediaStore.Images.Media.getBitmap(getContentResolver(), Uri.parse(item.getImagesUrls().get(0)));
                img = Bitmap.createScaledBitmap(img, THUMBNAIL_SIZE, THUMBNAIL_SIZE, false);
                mimage_1 = findViewById(R.id.image_1);
                mimage_1.setImageBitmap(img);

                if (item.getImagesUrls().size() > 1) {
                    Bitmap img2 = MediaStore.Images.Media.getBitmap(getContentResolver(), Uri.parse(item.getImagesUrls().get(1)));
                    img2 = Bitmap.createScaledBitmap(img2, THUMBNAIL_SIZE, THUMBNAIL_SIZE, false);
                    mimage_2 = findViewById(R.id.image_2);
                    mimage_2.setImageBitmap(img2);
                }

            } catch (IOException e) {
                e.printStackTrace();
            }


            for (int i = 0; i < item.getImagesUrls().size(); i++) {
                Log.d(TAG, item.getImagesUrls().get(i));
            }
            Log.d(TAG, "It's not empty!");
        }

    }

    public void setReminderDate(View view) {
        Intent intent = new Intent(this, ReminderActivity.class);
        startActivity(intent);
    }

    public void addImage(View view) {
        Intent intent = new Intent(Intent.ACTION_PICK, MediaStore.Images.Media.EXTERNAL_CONTENT_URI);
        intent.setType("image/*");
        //intent.setAction(Intent.ACTION_GET_CONTENT);
        //startActivityForResult(Intent.createChooser(intent, "Select Picture"), PICK_IMAGE_REQUEST);
        startActivityForResult(intent, PICK_IMAGE_REQUEST);
        Log.d(TAG, "Selecting image");
    }

    public void deleteImage(View view) {
        Log.d(TAG, "Image deleted");
    }
}
