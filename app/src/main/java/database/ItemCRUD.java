package database;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.provider.BaseColumns;
import android.text.TextUtils;
import android.util.Log;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;

import models.Item;
import models.ItemList;

/**
 * Created by CarlosIribar on 11/9/17.
 */

public class ItemCRUD extends ListTrackerDataSource implements CRUD{

    private final String TAG = this.getClass().getName();

    private String [] columns =  new String [] {
            ListTrackerSQLiteHelper.ITEM_COLUMN_COMPLETED,
            BaseColumns._ID,
            ListTrackerSQLiteHelper.ITEM_COLUMN_CREATED_DATE,
            ListTrackerSQLiteHelper.ITEM_COLUMN_FOREIGN_KEY_LIST,
            ListTrackerSQLiteHelper.ITEM_COLUMN_IMAGE_URLS,
            ListTrackerSQLiteHelper.ITEM_COLUMN_DUE_DATE,
            ListTrackerSQLiteHelper.ITEM_COLUMN_NAME,
            ListTrackerSQLiteHelper.ITEM_COLUMN_NOTES,
            ListTrackerSQLiteHelper.ITEM_COLUMN_TAGS,
            ListTrackerSQLiteHelper.ITEM_COLUMN_PRIORITY,
    };

    public ItemCRUD(Context contex) {
        super(contex);
    }

    public long saveItem(Item item) {

        long id;
        SQLiteDatabase database = open();
        database.beginTransaction();

        ContentValues itemValues = new ContentValues();
        itemValues.put(ListTrackerSQLiteHelper.ITEM_COLUMN_NAME, item.getName());
        itemValues.put(ListTrackerSQLiteHelper.ITEM_COLUMN_NOTES, item.getNotes());
        Boolean isCompleted = item.getCompleted();

        if (isCompleted != null) {
            itemValues.put(ListTrackerSQLiteHelper.ITEM_COLUMN_COMPLETED, isCompleted ? 1: 0);
        } else {
            itemValues.put(ListTrackerSQLiteHelper.ITEM_COLUMN_COMPLETED, 0);
        }
        itemValues.put(ListTrackerSQLiteHelper.ITEM_COLUMN_CREATED_DATE, new Date().toString());
        if (item.getDueDate() != null) {
            itemValues.put(ListTrackerSQLiteHelper.ITEM_COLUMN_DUE_DATE, item.getDueDate().toString());
        }
        if (item.getImagesUrls() != null) {
            itemValues.put(ListTrackerSQLiteHelper.ITEM_COLUMN_IMAGE_URLS, TextUtils.join("##", item.getImagesUrls()));
        }
        if (item.getTags() != null) {
            itemValues.put(ListTrackerSQLiteHelper.ITEM_COLUMN_TAGS, item.getTags());
        }
        if (item.getPriorityName() != null) {
          itemValues.put(ListTrackerSQLiteHelper.ITEM_COLUMN_PRIORITY_NAME, item.getPriorityName());
        }
        itemValues.put(ListTrackerSQLiteHelper.ITEM_COLUMN_PRIORITY, item.getPriority());
        itemValues.put(ListTrackerSQLiteHelper.ITEM_COLUMN_FOREIGN_KEY_LIST, item.getListId());

        if (item.getId() != 0) {
            itemValues.put(BaseColumns._ID, item.getId());
            id = database.update(
                    ListTrackerSQLiteHelper.ITEM_TABLE_NAME,
                    itemValues,
                    String.format("%s=%d", BaseColumns._ID, item.getId()), null);
        } else {
            id = database.insert(ListTrackerSQLiteHelper.ITEM_TABLE_NAME, null, itemValues);
        }

        database.setTransactionSuccessful();
        database.endTransaction();
        close(database);
        Log.d(TAG, "Item saved");
        return id;
    }

    public void delete(long itemId) {
        SQLiteDatabase database = open();
        database.beginTransaction();

        database.delete(ListTrackerSQLiteHelper.ITEM_TABLE_NAME,
                String.format("%s=%s", BaseColumns._ID, String.valueOf(itemId)),
                null);
        database.setTransactionSuccessful();
        database.endTransaction();
        Log.d(TAG, "Item deleted");
    }



    public List<Item> getItems() {
        List<Item> items = new ArrayList<>();

        SQLiteDatabase database = open();
        Cursor cursor = database.query(
                ListTrackerSQLiteHelper.ITEM_TABLE_NAME,
                columns,
                null, //selection
                null, //selection args
                null, //group by
                null, //having
                ListTrackerSQLiteHelper.ITEM_COLUMN_CREATED_DATE + " DESC"
        );

        if (cursor.moveToFirst()) {
            do {
                items.add(createItem(cursor));
            } while (cursor.moveToNext());
        }
        cursor.close();
        close(database);
        Log.d(TAG, "Database accessed: Item");
        return items;
    }

    public List<Item> getItemsFromList(long listId) {
      List<Item> items = new ArrayList<>();
      String whereClause =  ListTrackerSQLiteHelper.ITEM_COLUMN_FOREIGN_KEY_LIST + "= ?";
      String[] whereArgs = new String[]{
              String.valueOf(listId)
      };

      SQLiteDatabase database = open();
      Cursor cursor = database.query(
              ListTrackerSQLiteHelper.ITEM_TABLE_NAME,
              columns,
              whereClause, //selection
              whereArgs, //selection args
              null, //group by
              null, //having
              ListTrackerSQLiteHelper.ITEM_COLUMN_CREATED_DATE + " DESC"
      );

      if (cursor.moveToFirst()) {
        do {
          items.add(createItem(cursor));
        } while (cursor.moveToNext());
      }
      cursor.close();
      close(database);
      return items;
    }

    private Item createItem(Cursor cursor) {

      Item item = new Item(getStringFromColumnName(cursor, ListTrackerSQLiteHelper.ITEM_COLUMN_NAME));
      item.setNotes(getStringFromColumnName(cursor, ListTrackerSQLiteHelper.ITEM_COLUMN_NOTES));
      item.setTags(getStringFromColumnName(cursor, ListTrackerSQLiteHelper.ITEM_COLUMN_TAGS));
      item.setPriority(getIntFromColumnName(cursor, ListTrackerSQLiteHelper.ITEM_COLUMN_PRIORITY));
      item.setCompleted(getBooleanFromColumnName(cursor, ListTrackerSQLiteHelper.ITEM_COLUMN_COMPLETED));
      item.setCreatedDate(getDateFromColumnName(cursor, ListTrackerSQLiteHelper.ITEM_COLUMN_CREATED_DATE));
      item.setId(getLongFromColumnName(cursor, BaseColumns._ID));
      item.setDueDate(getDateFromColumnName(cursor, ListTrackerSQLiteHelper.ITEM_COLUMN_DUE_DATE));
      item.setListId(getLongFromColumnName(cursor, ListTrackerSQLiteHelper.ITEM_COLUMN_FOREIGN_KEY_LIST));
      item.setPriorityName(getStringFromColumnName(cursor, ListTrackerSQLiteHelper.ITEM_COLUMN_PRIORITY_NAME));
      return item;
    }
}
