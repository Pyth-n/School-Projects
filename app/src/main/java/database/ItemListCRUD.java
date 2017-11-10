package database;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.provider.BaseColumns;

import java.util.ArrayList;
import java.util.List;

import models.ItemList;

/**
 * Created by CarlosIribar on 11/10/17.
 */

public class ItemListCRUD extends ListTrackerDataSource implements CRUD{

  public ItemListCRUD(Context context) {
    super(context);
  }

  public long saveItemList(ItemList itemList) {
    long id;
    SQLiteDatabase database = open();
    database.beginTransaction();

    ContentValues listValues = new ContentValues();
    listValues.put(ListTrackerSQLiteHelper.LIST_COLUMN_NAME  , itemList.getName());
    listValues.put(ListTrackerSQLiteHelper.LIST_COLUMN_CATEGORY_ID, itemList.getCategoryId());

    if (itemList.getId() !=  0) {
      listValues.put(BaseColumns._ID, itemList.getId());
      id = database.update(
              ListTrackerSQLiteHelper.ITEM_TABLE_NAME,
              listValues,
              String.format("%s=%d", BaseColumns._ID, itemList.getId()), null);
    } else {
      id = database.insert(ListTrackerSQLiteHelper.LIST_TABLE_NAME, null, listValues);
    }
    database.setTransactionSuccessful();
    database.endTransaction();
    close(database);
    return id;
  }


  public void delete(long itemListId) {
    SQLiteDatabase database = open();
    database.beginTransaction();

    database.delete(ListTrackerSQLiteHelper.ITEM_TABLE_NAME,
            String.format("%s=%s", ListTrackerSQLiteHelper.ITEM_COLUMN_FOREIGN_KEY_LIST, String.valueOf(itemListId)),
            null);
    database.delete(ListTrackerSQLiteHelper.LIST_TABLE_NAME,
            String.format("%s=%s", BaseColumns._ID, String.valueOf(itemListId)),
            null);
    database.setTransactionSuccessful();
    database.endTransaction();
  }

  public List<ItemList> getLists() {
    List<ItemList> lists = new ArrayList<>();
    String [] columns =  new String [] {
            BaseColumns._ID,
            ListTrackerSQLiteHelper.LIST_COLUMN_CATEGORY_ID,
            ListTrackerSQLiteHelper.LIST_COLUMN_NAME
    };

    SQLiteDatabase database = open();
    Cursor cursor = database.query(
            ListTrackerSQLiteHelper.LIST_TABLE_NAME,
            columns,
            null, //selection
            null, //selection args
            null, //group by
            null, //having
            null
    );

    if (cursor.moveToFirst()) {
      do {
        ItemList itemList = new ItemList(getStringFromColumnName(cursor, ListTrackerSQLiteHelper.LIST_COLUMN_NAME));
        itemList.setId(getLongFromColumnName(cursor, BaseColumns._ID));
        itemList.setCategoryId(getLongFromColumnName(cursor, ListTrackerSQLiteHelper.LIST_COLUMN_CATEGORY_ID));
        lists.add(itemList);
      } while (cursor.moveToNext());
    }
    cursor.close();
    close(database);
    return lists;
  }
}
