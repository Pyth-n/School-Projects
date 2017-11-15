package com.byui_cs246_team07.listtracker;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.EditText;

import controllers.ItemListController;
import models.ItemList;

public class ListCreationActivity extends AppCompatActivity {

  private String TAG = this.getClass().getName();
  private ItemListController controller;

  public ListCreationActivity() {
    controller = new ItemListController(this);
  }

  @Override
  protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.activity_list_creation);
  }

  public void addList(View view) {

    Log.d(TAG, "addList");
    EditText editText = (EditText) findViewById(R.id.newListName);
    String listName = editText.getText().toString();
    if (listName != null && listName != "") {
      ItemList itemList = new ItemList(listName);
      // TODO move the following line to a runnable class
      controller.saveItemList(itemList);
      editText.setText("");
      Log.d(TAG, "Save");
      returnToMain();
    }
  }

  public void returnToMain() {
    Intent intent = new Intent(this, MainActivity.class);
    startActivity(intent);
  }
}
