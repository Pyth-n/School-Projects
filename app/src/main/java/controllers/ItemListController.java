package controllers;

import android.content.Context;
import android.util.Log;

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
    private List<ItemList> lists;

    public ItemListController(Context context) {
        itemListCRUD = new ItemListCRUD(context);
        itemCRUD = new ItemCRUD(context);
    }


    public List<String> getListNames(String orderBy) {
        List<String> listNames = new ArrayList<>();
        getLists(orderBy);
        for (ItemList itemList : lists) {
            listNames.add(itemList.getName());
        }
        return listNames;
    }

    public List<ItemList>  getLists(String orderBy) {
        lists = itemListCRUD.getLists(orderBy);
        return lists;

    }

    public long saveItemList(ItemList itemList) {
        return itemListCRUD.saveItemList(itemList);
    }

    public List<Item> getRelatedItems(long itemId, String orderBy) {
        Log.d("Get Related the are", orderBy);
        return itemCRUD.getItemsFromList(itemId, orderBy);
    }

    public List<String> getRelatedItemsNames(long itemId, String orderBy) {
        List<String> listNames = new ArrayList<>();
        List<Item> lists =  getRelatedItems(itemId, orderBy);
        for (Item item : lists) {
            listNames.add(item.getName());
        }
        return listNames;
    }

    public void delete(long id) {
        itemListCRUD.delete(id);
    }


}
