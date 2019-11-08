package models;

import android.content.Context;

import java.io.Serializable;
import java.util.Date;
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
    private Date createdDate;
    private Date modifiedDate;
    private List<Item> items;

    /**
     * Item constructor
     * @param name
     */
    public ItemList(String name) {
        this.name = name;
    }

    public Date getCreatedDate() {
        return createdDate;
    }

    public void setCreatedDate(Date createdDate) {
        this.createdDate = createdDate;
    }

    public Date getModifiedDate() {
        return modifiedDate;
    }

    public void setModifiedDate(Date modifiedDate) {
        this.modifiedDate = modifiedDate;
    }

    /**
     * Get items
     * @return
     */
    public List<Item> getItems() {
        return items;
    }

    /**
     * Set items
     * @param items
     */
    public void setItems(List<Item> items) {
        this.items = items;
    }

    /**
     * Get Name
     * @return
     */
    public String getName() {
        return name;
    }

    /**
     * Set Name
     * @param name
     */
    public void setName(String name) {
        this.name = name;
    }

    /**
     * Get Category Id
     * @return
     */
    public long getCategoryId() {
        return categoryId;
    }

    /**
     * Set Category Id
     * @param category
     */
    public void setCategoryId(long category) {
        this.categoryId = category;
    }

    /**
     * Get Id
     * @return
     */
    public long getId() {
        return id;
    }

    /**
     * Set Id
     * @param id
     */
    public void setId(long id) {
        this.id = id;
    }

    /**
     * Get Category Items
     * @param name
     * @return
     */
    public static List<Item> getCategoryItems(String name) {
        return null;
    }

    
}
