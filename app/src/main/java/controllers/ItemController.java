package controllers;

import android.content.Context;
import android.util.Log;

import java.io.Serializable;
import java.util.List;

import database.ItemCRUD;
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
    private ItemCRUD itemCRUD;

    public ItemController(Context context) {
        itemCRUD = new ItemCRUD(context);
    }

    public Long saveItem(Item item) {
        return itemCRUD.saveItem(item);
    }

    public List<Item> getItems() {
        return itemCRUD.getItems();
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

    public void delete(long id) {
        itemCRUD.delete(id);
    }
}
