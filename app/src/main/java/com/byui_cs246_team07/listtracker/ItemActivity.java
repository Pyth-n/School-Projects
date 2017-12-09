package com.byui_cs246_team07.listtracker;

import android.content.Intent;
import android.content.res.Configuration;
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
import android.view.Display;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
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

    private final int PICK_IMAGE_REQUEST = 1;
    final int THUMBNAIL_SIZE = 128;
    private final int EMPTY_IMAGE_INDEX = -1;
    private final int MAX_NUM_THUMBNAILS = 2;
    private final int HIDDEN_THUMBNAIL_INDEX = -1;
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
    private int mThumb1ImageIndex;
    private int mThumb2ImageIndex;

    private Item mItemActive;
    private List<String> mImagesUrls;

    public ItemActivity() {
        controller = new ItemController(this);
        listController = new ItemListController(this);
        mImagesUrls = new ArrayList<String>();
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_item);

        // find resource IDs
        getItemValues();
        handleIntent(getIntent());

        if (mItemActive != null)
            setItemValues(mItemActive);

        handleActionBar();
    }

    private ItemList getItemList() {
        List<ItemList> temp = listController.getLists(null);

        for (int i = 0; i < temp.size(); i++) {
            if (temp.get(i).getId() == mItemActive.getListId()) {
                Log.d(TAG, "Parent list is: " + temp.get(i).getName());
                return temp.get(i);
            }
        }

        return null;
    }

    private void handleIntent(Intent intent) {
        String fromClass = intent.getStringExtra("Class");

        if (fromClass.equals("SearchActivity.java")) {
            mItemActive = (Item) intent.getSerializableExtra(SearchResultsActivity.ITEM_INTENT);
            parentList = getItemList();
        }

        if (fromClass.equals("ListActivity.java")) {
            // Set name of the list
            parentList = (ItemList) getIntent().getSerializableExtra(ListActivity.PARENT_LIST);

            // Differentiate between the buttons that sent the intent
            String buttonName = getIntent().getStringExtra(ListActivity.BUTTON_PRESSED);
            if (buttonName.equals("createItem")) {
                mItemActive = null;
                //Toast.makeText(this, "CREATING...", Toast.LENGTH_SHORT).show();
            } else if (buttonName.equals("loadItem")) {
                mItemActive = (Item) getIntent().getSerializableExtra(ListActivity.ITEM);
                Log.d("Set Item", mItemActive.getName());
                Toast.makeText(this, "Loading " + mItemActive.getName(), Toast.LENGTH_SHORT).show();
            }
        }

        if (mItemActive != null)
            setItemValues(mItemActive);

        ImageView imageView1 = (ImageView) findViewById(R.id.image_1);

        imageView1.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View view, MotionEvent event) {
                int imageUrlsListIndex = mThumb1ImageIndex;
                viewImageFullScreen(imageUrlsListIndex);
                return true;
            }

            /*@Override
            public boolean performClick() {
                int imageUrlsListIndex = mThumb1ImageIndex;
                viewImageFullScreen(imageUrlsListIndex);
                return true;
            }*/
        });

        ImageView imageView2 = (ImageView) findViewById(R.id.image_2);

        imageView2.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View view, MotionEvent event) {
                int imageUrlsListIndex = mThumb2ImageIndex;
                viewImageFullScreen(imageUrlsListIndex);
                return true;
            }

            /*@Override
            public boolean performClick() {
                int imageUrlsListIndex = mThumb2ImageIndex;
                viewImageFullScreen(imageUrlsListIndex);
                return true;
            }*/
        });
    }

    private void handleActionBar() {
        Toolbar myToolbar = findViewById(R.id.item_toolbar);
        setSupportActionBar(myToolbar);

        // if screen is in portrait
        if (getScreenOrientation() == 1) {
            ActionBar actionBar = getSupportActionBar();
        actionBar.setTitle(Html.fromHtml(
                "<font color=\"#ffffff\">" + "Item within &quot;" + parentList.getName() + "&quot;</font>"));
        } else {
            TextView textView = findViewById(R.id.listNameInItemScreen);
            textView.setText(parentList.getName());
        }

        Log.d(TAG, String.valueOf(getScreenOrientation()));
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

            String imagePath = uri.toString();
            Log.d(TAG, "Image path: " + imagePath);
            mImagesUrls.add(imagePath);
            Toast.makeText(this, "Image #" + mImagesUrls.size() + " added", Toast.LENGTH_SHORT).show();
            rotateToNewestImages();
            updateImageThumbnails();
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
        if (mItemActive != null && mItemActive.getId() != 0) {
            item.setId(mItemActive.getId());
        }
        item.setListId(parentList.getId());
        item.setCompleted(mCompleted.isChecked());
        item.setNotes(mNotes.getText().toString());
        item.setTags(mTag.getText().toString());
        item.setPriorityName(mPriorityName.getText().toString());
        Editable priorityNumberEditable = mPriorityNumber.getText();
        item.setImagesUrls(mImagesUrls);

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
            Log.d(TAG, "Tags: " + item.getTags());
            mTag.setText(item.getTags());
        }

        if (!mItemActive.getImagesUrls().isEmpty()) {
            mImagesUrls = item.getImagesUrls();
            mThumb1ImageIndex = 0;
            if (mImagesUrls.size() > 1) {
                mThumb2ImageIndex = 1;
            } else {
                mThumb2ImageIndex = EMPTY_IMAGE_INDEX;
            }
            updateImageThumbnails();
        } else {
            mThumb1ImageIndex = EMPTY_IMAGE_INDEX;
            mThumb2ImageIndex = EMPTY_IMAGE_INDEX;
        }
    }

    public void setReminderDate(View view) {
        Intent intent = new Intent(this, ReminderActivity.class);
        startActivity(intent);
    }

    public void addImage(View view) {
        Intent intent = new Intent(Intent.ACTION_OPEN_DOCUMENT, MediaStore.Images.Media.EXTERNAL_CONTENT_URI);
        intent.setType("image/*");
        startActivityForResult(Intent.createChooser(intent, "Select Picture"), PICK_IMAGE_REQUEST);
        Log.d(TAG, "Selecting image");
    }

    public void deleteImage(View view) {
        if (!mImagesUrls.isEmpty()) {
            int imageNum = mThumb1ImageIndex + 1;
            mImagesUrls.remove(mThumb1ImageIndex);
            Log.d(TAG, "Image index " + imageNum + " deleted");
            Toast.makeText(this, "Deleted image #" + imageNum, Toast.LENGTH_SHORT).show();
            rotateToNewestImages();
            updateImageThumbnails();
        }
        else {
            Toast.makeText(this, "No image to delete", Toast.LENGTH_SHORT).show();
        }
    }

    public void viewImageFullScreen(int imageUrlsListIndex) {
        if (!mImagesUrls.isEmpty()) {
            Intent intent = new Intent();
            intent.setAction(Intent.ACTION_VIEW);
            intent.setDataAndType(Uri.parse(mImagesUrls.get(imageUrlsListIndex)), "image/*");
            Log.d(TAG, "Viewing image index " + imageUrlsListIndex);
            int imageNum = imageUrlsListIndex + 1;
            Toast.makeText(this, "Viewing image #" + imageNum, Toast.LENGTH_SHORT).show();
            startActivity(intent);
        }
    }

    private void displayImageThumbnail(int thumbnailIndex, Uri uri, boolean removedImage) {
        try {
            Bitmap imgThumbnailBitmap = null;
            if (!removedImage) {
                imgThumbnailBitmap = MediaStore.Images.Media.getBitmap(getContentResolver(), uri);
                imgThumbnailBitmap = Bitmap.createScaledBitmap(imgThumbnailBitmap, THUMBNAIL_SIZE, THUMBNAIL_SIZE, false);
            }
            ImageView imageViewThumb;
            if (thumbnailIndex == 0) {
                imageViewThumb = (ImageView) findViewById(R.id.image_1);
            } else if (thumbnailIndex == 1) {
                imageViewThumb = (ImageView) findViewById(R.id.image_2);
            } else {
                imageViewThumb = null;
            }
            if (thumbnailIndex != HIDDEN_THUMBNAIL_INDEX){
                Log.d(TAG, "URI: " + uri.toString());
                if (!removedImage) {
                    imageViewThumb.setVisibility(View.VISIBLE);
                    imageViewThumb.setImageBitmap(imgThumbnailBitmap);
                    Log.d(TAG, "Image display succeeded");
                } else {
                    imageViewThumb.setVisibility(View.INVISIBLE);
                    Log.d(TAG, "Image thumbnail hidden");
                }
            } else {
                Log.d(TAG, "New image thumbnail hidden");
            }
        } catch (IOException e) {
            e.printStackTrace();
            Log.d(TAG, "Image display failed");
        }
    }

    private void updateImageThumbnails() {
        boolean removedImage = false;
        int imageIndex = mThumb1ImageIndex;
        int thumbIndex = 0;
        for (thumbIndex = 0; ((thumbIndex < mImagesUrls.size()) && (thumbIndex < MAX_NUM_THUMBNAILS)); thumbIndex++) {
            if (thumbIndex == 0) {
                    imageIndex = mThumb1ImageIndex;
            }
            else {
                imageIndex = mThumb2ImageIndex;
            }
            String imagePath = mImagesUrls.get(imageIndex);
            Log.d(TAG, imageIndex + " image path retrieved: " + imagePath);
            Uri imageUri = Uri.parse(imagePath);
            Log.d(TAG, "Uri conversion complete: " + imageUri.toString());
            displayImageThumbnail(thumbIndex, imageUri, removedImage);
        }
        if ((thumbIndex >= mImagesUrls.size()) && (thumbIndex < MAX_NUM_THUMBNAILS)) {
            removedImage = true;
            displayImageThumbnail(thumbIndex, Uri.parse("INVISIBLE"), removedImage);
        }
        int imageDisplay1 = mThumb1ImageIndex + 1;
        int imageDisplay2 = mThumb2ImageIndex + 1;
        Toast.makeText(this, "Displaying image #" + imageDisplay1 + " and image #" + imageDisplay2, Toast.LENGTH_SHORT).show();
    }

    public void incrementDisplayedThumbnails(View view) {
        if (mImagesUrls.size() > 1) {
            if (mThumb1ImageIndex < mImagesUrls.size() - 1) {
                mThumb1ImageIndex++;
            } else {
                    mThumb1ImageIndex = 0;
            }
            if ((mThumb2ImageIndex < mImagesUrls.size() - 1)) {
                mThumb2ImageIndex++;
            } else {
                if (mThumb1ImageIndex == mImagesUrls.size() - 1) {
                    mThumb2ImageIndex = 0;
                } else {
                    mThumb2ImageIndex = EMPTY_IMAGE_INDEX;
                }
            }
            Toast.makeText(this, "Incremented displayed thumbnails", Toast.LENGTH_SHORT).show();
            Log.d(TAG, "Image index incrementing complete");
            updateImageThumbnails();
        } else {
            Toast.makeText(this, "There are not enough images to increment thumbnails", Toast.LENGTH_SHORT).show();
        }
    }

    private void rotateToNewestImages () {
        if (mImagesUrls.size() == 0) {
            mThumb1ImageIndex = HIDDEN_THUMBNAIL_INDEX;
            mThumb2ImageIndex = HIDDEN_THUMBNAIL_INDEX;
        } else if (mImagesUrls.size() == 1) {
            mThumb1ImageIndex = 0;
            mThumb2ImageIndex = HIDDEN_THUMBNAIL_INDEX;
        } else if (mImagesUrls.size() == MAX_NUM_THUMBNAILS){
            mThumb1ImageIndex = 0;
            mThumb2ImageIndex = 1;
        } else {
            mThumb1ImageIndex = mImagesUrls.size() - 2;
            mThumb2ImageIndex = mImagesUrls.size() - 1;
        }
    }
}
