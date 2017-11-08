package com.byui_cs246_team07.listtracker;

import android.content.Context;
import android.content.SharedPreferences;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;

import controllers.ItemController;


public class MainActivity extends AppCompatActivity {
    private final String SORTBY = "sortBy";
    private final String CATEGORY = "categoryID";
    private final String LASTSCREENVIEWED = "lastScreenID";
    private final String LASTLISTVIEWED = "lastListID";
    private final String PREFERENCES = "listPrefs";

	/*
	* OnCreate
	*/
  @Override
  protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    setContentView(R.layout.activity_main);

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

      ItemController controller = new ItemController();
      SharedPreferences settings = getSharedPreferences(PREFERENCES, Context.MODE_PRIVATE);
      controller.setCategoryName(settings.getString(CATEGORY, ""));
      controller.setListName(settings.getString(LASTLISTVIEWED, ""));
      controller.setSortBy(settings.getString(SORTBY, ""));
      Log.d("SHAREDPREFERENCES: ", settings.getString(CATEGORY, "Category Test"));
      Log.d("SHAREDPREFERENCES: ", settings.getString(LASTLISTVIEWED, "Last View Test"));
      Log.d("SHAREDPREFERENCES: ", settings.getString(SORTBY, "Sort By Test"));
  }

  @Override
  protected void onStop() {
      super.onStop();
      SharedPreferences settings = getSharedPreferences(PREFERENCES, Context.MODE_PRIVATE);
      SharedPreferences.Editor editor = settings.edit();

      ItemController controller = new ItemController();
      // Sort
      editor.putString(SORTBY, controller.getSortBy());

      // Category
      editor.putString(CATEGORY, controller.getCategoryName());

      // Last screen viewed
      editor.putString(LASTSCREENVIEWED, this.getClass().getSimpleName());

      // List name for widget
      editor.putString(LASTLISTVIEWED, controller.getListName());

      editor.apply();
  }

}
