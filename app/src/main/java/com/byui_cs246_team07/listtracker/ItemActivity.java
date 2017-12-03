package com.byui_cs246_team07.listtracker;

import android.content.Intent;
import android.graphics.Bitmap;
import android.net.Uri;
import android.provider.MediaStore;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.Editable;
import android.util.Log;
import android.view.KeyEvent;
import android.view.MotionEvent;
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
import models.Item;
import models.ItemList;

public class ItemActivity extends AppCompatActivity {

    private final int PICK_IMAGE_REQUEST = 1;
    final int THUMBNAIL_SIZE = 128;
    private ItemList parentList;
    private ItemController controller;
    private final String TAG = this.getClass().getName();
    // IDs of widgets
    private TextView mListName;
    private EditText mItemName;
    private EditText mTag;
    private EditText mDueDate;
    private TextView mDateCreated;
    private TextView mDateModified;
    private CheckBox mCompleted;
    private EditText mPriorityNumber;
    private EditText mPriorityName;
    private EditText mNotes;
    private Item  itemActive;
    private List<String> mNewImagesUrls;

    public ItemActivity() {
        controller = new ItemController(this);
        mNewImagesUrls = new ArrayList<String>();
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_item);

        // find resource IDs
        getItemValues();

        // Set name of the list
        parentList = (ItemList) getIntent().getSerializableExtra(ListActivity.PARENT_LIST);
        mListName.setText(parentList.getName());

        // Differentiate between the buttons that sent the intent
        String buttonName = getIntent().getStringExtra(ListActivity.BUTTON_PRESSED);
        if (buttonName.equals("createItem")) {
            //Toast.makeText(this, "CREATING...", Toast.LENGTH_SHORT).show();
        }

        else if (buttonName.equals("loadItem")) {
            itemActive = (Item) getIntent().getSerializableExtra(ListActivity.ITEM);
            setItemValues(itemActive);
            Log.d("Set Item", itemActive.getName());
            Toast.makeText(this, "Loading " + itemActive.getName(), Toast.LENGTH_SHORT).show();
        }

        ImageView imageView = (ImageView) findViewById(R.id.imageView);

        imageView.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View view, MotionEvent event) {
                int imageUrlsListIndex = 0;
                viewImageFullScreen(imageUrlsListIndex);
                return true;
            }

            /*@Override
            public boolean performClick() {
                int imageUrlsListIndex = 0;
                viewImageFullScreen(imageUrlsListIndex);
                return true;
            }*/
        });
    }

    @Override
    protected void onResume() {

        super.onResume();

    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        if (requestCode == PICK_IMAGE_REQUEST && resultCode == RESULT_OK && data != null && data.getData() != null) {

            Log.d(TAG, "Image selected");
            Uri uri = data.getData();
            Log.d(TAG, "Image URI: " + uri);
            String imagePath = uri.toString();
            //File file = new File(uri.getPath());
            //String imagePath = file.getAbsolutePath();
            Log.d(TAG, "Image path: " + imagePath);
            mNewImagesUrls.add(imagePath);
            displayImageThumbnail(uri);
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
        item.setImagesUrls(mNewImagesUrls);

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
        mListName = (TextView) findViewById(R.id.listNameInItemScreen);
        mNotes = (EditText) findViewById(R.id.editNotes);
        mPriorityNumber = (EditText) findViewById(R.id.priorityNumber);
        mCompleted = (CheckBox) findViewById(R.id.completed);
        mPriorityName = (EditText) findViewById(R.id.priorityLevelName);
        mTag = (EditText) findViewById(R.id.editTags);
        mDateCreated = (TextView) findViewById(R.id.dateCreated);
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
        /*if (!itemActive.getImagesUrls().isEmpty()) {
            List<String> imageUrls = itemActive.getImagesUrls();
            for (int i = 0; i < 1; i++) {
                String imagePath = imageUrls.get(i);
                Log.d(TAG, i + " image path retrieved: " + imagePath);

                File file = new File(imagePath);
                Uri imageUri;
                if(file.exists()) {
                    imageUri = Uri.fromFile(file);
                }
                else {
                    imageUri = Uri.parse(imagePath);
                }
                //Uri imageUri = Uri.parse(imagePath);
                Log.d(TAG, "Uri conversion complete: " + imageUri.toString());
                displayImageThumbnail(imageUri);
            }
        }*/
    }

    public void setReminderDate(View view) {
        Intent intent = new Intent(this, ReminderActivity.class);
        startActivity(intent);
    }

    public void addImage(View view) {
        Intent intent = new Intent();
        intent.setType("image/*");
        intent.setAction(Intent.ACTION_GET_CONTENT);
        startActivityForResult(Intent.createChooser(intent, "Select Picture"), PICK_IMAGE_REQUEST);
        Log.d(TAG, "Selecting image");
    }

    public void deleteImage(View view) {
        Log.d(TAG, "Image deleted");
    }

    public void viewImageFullScreen(int imageUrlsListIndex) {
        //List<String> imagesUrls = itemActive.getImagesUrls();
        if (!mNewImagesUrls.isEmpty()) {
            Intent intent = new Intent();
            intent.setAction(Intent.ACTION_VIEW);
            //File file = new File(imagesUrls.get(imageUrlsListIndex));
            //intent.setDataAndType(Uri.fromFile(file), "image/*");
            intent.setDataAndType(Uri.parse(mNewImagesUrls.get(imageUrlsListIndex)), "image/*");
            startActivity(intent);
        }
    }

    private void displayImageThumbnail(Uri uri) {
        try {
            Bitmap imgThumbnailBitmap = MediaStore.Images.Media.getBitmap(getContentResolver(), uri);
            imgThumbnailBitmap = Bitmap.createScaledBitmap(imgThumbnailBitmap, THUMBNAIL_SIZE, THUMBNAIL_SIZE, false);
            ImageView imageView = (ImageView) findViewById(R.id.imageView);
            imageView.setImageBitmap(imgThumbnailBitmap);
            Log.d(TAG, "Image display succeeded");
        } catch (IOException e) {
            e.printStackTrace();
            Log.d(TAG, "Image display failed");
        }
    }
}
