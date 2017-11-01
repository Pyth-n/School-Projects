package models;

import java.util.List;

/**
 * Created by CarlosIribar on 10/31/17.
 */

public class ItemList {

    private String name;
    private String category;
    private long id;
    private List<Item> items;

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

    public String getCategory() {
        return category;
    }

    public void setCategory(String category) {
        this.category = category;
    }

    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    public ItemList(String name) {
        this.name = name;
    }

    public static List<Item> getCategoryItems(String name) {
        return null;
    }

    public Boolean save() {
        return null;
    }

}
