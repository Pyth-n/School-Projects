package com.byui_cs246_team07.listtracker;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;

import java.util.List;

import controllers.ItemController;
import models.Item;

public class MainActivity extends AppCompatActivity {

	/*
	* OnCreate
	*/
  @Override
  protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    //setContentView(R.layout.activity_main);

    //Example Creating items and gettings

    /*Item task = new Item("update tests");
    task.setPriority(1);
    task.setNotes("Some note");

    Item someOther = new Item("refactor tests");

    ItemController controller = new ItemController();
    controller.saveItem(this, task);
    controller.saveItem(this, someOther);

    List<Item> items = controller.getItems(this);
    for (Item item : items) {
      Log.d("MAIN", item.getName());
      Log.d("MAIN", item.getCreatedDate().toString());
    }*/
  }
}
