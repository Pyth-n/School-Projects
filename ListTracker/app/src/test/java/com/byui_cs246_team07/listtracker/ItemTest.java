package com.byui_cs246_team07.listtracker;

/**
 * Created by CarlosIribar on 10/31/17.
 */
import org.junit.Test;

import java.util.ArrayList;
import java.util.List;

import models.Item;
import models.ItemList;

import static org.junit.Assert.*;

public class ItemTest {

    @Test
    public void createItemTest() {
        Item item = new Item("ItemName");
        item.setPriority(1);
        item.setNotes("note");

        //assertEquals(true, item.save());
    }

    @Test
    public void createListTest() {
        ItemList list = new ItemList("listName");
        List<Item> items = new ArrayList<>();
        items.add(new Item("myItem"));
        list.setItems(items);

       // assertEquals(true, list.save());
    }

    @Test
    public void loadItemTest() {
        // TODO Mock list
        List<Item> items =  ItemList.getCategoryItems("myCategory");
        //assertEquals(2, items.size());
    }
}
