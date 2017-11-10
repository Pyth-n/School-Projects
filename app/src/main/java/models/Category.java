package models;

import java.util.List;

/**
 * Created by CarlosIribar on 10/31/17.
 */

public class Category {

    private String name;
    private long id;
    private List<ItemList> items;

    public Category(String name) {
        this.name = name;
    }

    public List<ItemList> getItems() {
        return items;
    }

    public void setItems(List<ItemList> items) {
        this.items = items;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

}
