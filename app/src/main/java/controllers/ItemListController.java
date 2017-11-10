package controllers;

import android.content.Context;

import java.util.ArrayList;
import java.util.List;

import database.ListTrackerDataSource;
import models.ItemList;

/**
 * Created by CarlosIribar on 11/9/17.
 */

public class ItemListController {

    private ListTrackerDataSource listTrackerDataSource;

    public ItemListController(Context context) {
        listTrackerDataSource = new ListTrackerDataSource(context);
    }


    public List<String> getListNames(Context context) {
        List<String> listNames = new ArrayList<>();
        ListTrackerDataSource lt = new ListTrackerDataSource(context);
        List<ItemList> lists =  lt.getLists();
        for (ItemList itemList : lists) {
            listNames.add(itemList.getName());
        }
        return listNames;
    }

    public long saveItemList(ItemList itemList) {
        return listTrackerDataSource.saveItemList(itemList);
    }
}
