package models;

import android.content.Context;

import java.io.Serializable;
import java.util.List;

import database.ListTrackerDataSource;
import database.ListTrackerSQLiteHelper;

/**
 * Created by CarlosIribar on 10/31/17.
 */

public class ItemList implements Serializable {

    private String name;
    private long categoryId;
    private long id;
    private List<Item> items;

    public ItemList(String name) {
        this.name = name;
    }

    public List<Item> getItems() {
        return items;
    }

    public void setItems(List<Item> items) {
        this.items = items;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public long getCategoryId() {
        return categoryId;
    }

    public void setCategoryId(long category) {
        this.categoryId = category;
    }

    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    public static List<Item> getCategoryItems(String name) {
        return null;
    }

    
}
