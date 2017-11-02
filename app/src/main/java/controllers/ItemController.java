package controllers;

import android.content.Context;

import java.util.List;

import database.ListTrackerDataSource;
import models.Item;
import models.ItemList;

/**
 * Created by CarlosIribar on 11/2/17.
 */

public class ItemController {

    public Long saveItem(Context context, Item item) {
        ListTrackerDataSource lt = new ListTrackerDataSource(context);
        return lt.saveItem(item);
    }

    public Long saveList(Context context, ItemList itemList) {
        ListTrackerDataSource lt = new ListTrackerDataSource(context);
        return lt.saveItemList(itemList);
    }

    public List<Item> getItems(Context context) {
        ListTrackerDataSource lt = new ListTrackerDataSource(context);
        return lt.getItems();
    }

    public List<ItemList> getList(Context context) {
        ListTrackerDataSource lt = new ListTrackerDataSource(context);
        return lt.getLists();
    }
}
