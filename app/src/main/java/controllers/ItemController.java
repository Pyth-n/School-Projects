package controllers;

import android.content.Context;
import android.util.Log;

import java.util.List;

import database.ListTrackerDataSource;
import models.Item;
import models.ItemList;

/**
 * Created by CarlosIribar on 11/2/17.
 */

public class ItemController {
    private String sortValue;
    private String category;
    private String listName;
    private ListTrackerDataSource listTrackerDataSource;

    public ItemController(Context context) {
        listTrackerDataSource = new ListTrackerDataSource(context);
    }

    public Long saveItem(Item item) {
        return listTrackerDataSource.saveItem(item);
    }

    public Long saveList(ItemList itemList) {
        return listTrackerDataSource.saveItemList(itemList);
    }

    public List<Item> getItems() {
        return listTrackerDataSource.getItems();
    }

    public List<ItemList> getList() {
        return listTrackerDataSource.getLists();
    }

    public String getSortBy() {
        return sortValue;
    }

    public String getCategoryName() {
        return category;
    }

    public String getListName() {
        return listName;
    }

    public void setSortBy(String value) {
        Log.d("SETSORTBY: ", value);
        this.sortValue = value;
    }

    public void setCategoryName(String value) {
        Log.d("SETCATEGORYNAME: ", value);
        this.category = value;
    }

    public void setListName(String value) {
        Log.d("SETLISTNAME: ", value);
        this.listName = value;
    }
}
