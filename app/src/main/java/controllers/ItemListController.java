package controllers;

import android.content.Context;

import java.util.ArrayList;
import java.util.List;

import database.ItemCRUD;
import database.ItemListCRUD;
import models.Item;
import models.ItemList;

/**
 * Created by CarlosIribar on 11/9/17.
 */

public class ItemListController {

    private ItemListCRUD itemListCRUD;
    private ItemCRUD itemCRUD;

    public ItemListController(Context context) {
        itemListCRUD = new ItemListCRUD(context);
    }


    public List<String> getListNames() {
        List<String> listNames = new ArrayList<>();
        List<ItemList> lists =  itemListCRUD.getLists();
        for (ItemList itemList : lists) {
            listNames.add(itemList.getName());
        }
        return listNames;
    }

    public long saveItemList(ItemList itemList) {
        return itemListCRUD.saveItemList(itemList);
    }

    public List<Item> getRelatedItems(long itemId) {
        return itemCRUD.getItemsFromList(itemId);
    }

    public List<String> getRelatedItemsNames(long itemId) {
        List<String> listNames = new ArrayList<>();
        List<Item> lists =  getRelatedItems(itemId);
        for (Item item : lists) {
            listNames.add(item.getName());
        }
        return listNames;
    }
}
