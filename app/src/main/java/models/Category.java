package models;

import java.io.Serializable;
import java.util.List;

/**
 * Created by CarlosIribar on 10/31/17.
 */

public class Category implements Serializable {

    private String name;
    private long id;
    private List<ItemList> items;

    /**
     * Category Constructor
     * @param name
     */
    public Category(String name) {
        this.name = name;
    }

    /**
     * Get Items
     * @return
     */
    public List<ItemList> getItems() {
        return items;
    }

    /**
     * Set Items
     * @param items
     */
    public void setItems(List<ItemList> items) {
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

}
