package database;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.provider.BaseColumns;
import android.util.Log;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;

import models.ItemList;

/**
 * Created by CarlosIribar on 11/10/17.
 */

public class ItemListCRUD extends ListTrackerDataSource implements CRUD{

  private final String TAG = this.getClass().getName();

  /**
   * Item List CRUD Constructor
   * @param context
   */
  public ItemListCRUD(Context context) {
    super(context);
  }

  /**
   * Set ItemList in database
   * @param itemList
   * @return
   */
  public long saveItemList(ItemList itemList) {
    long id;
    SQLiteDatabase database = open();
    database.beginTransaction();

    ContentValues listValues = new ContentValues();
    listValues.put(ListTrackerSQLiteHelper.LIST_COLUMN_NAME  , itemList.getName());
    listValues.put(ListTrackerSQLiteHelper.LIST_COLUMN_CATEGORY_ID, itemList.getCategoryId());
    listValues.put(ListTrackerSQLiteHelper.LIST_COLUMN_CREATED_DATE, new Date().toString());


    if (itemList.getId() !=  0) {
      listValues.put(BaseColumns._ID, itemList.getId());
      listValues.put(ListTrackerSQLiteHelper.LIST_COLUMN_MODIFIED_DATE, new Date().toString());

      id = database.update(
              ListTrackerSQLiteHelper.LIST_TABLE_NAME,
              listValues,
              String.format("%s=%d", BaseColumns._ID, itemList.getId()), null);
    } else {
      listValues.put(ListTrackerSQLiteHelper.LIST_COLUMN_CREATED_DATE, new Date().toString());
      listValues.put(ListTrackerSQLiteHelper.LIST_COLUMN_MODIFIED_DATE, new Date().toString());
      id = database.insert(ListTrackerSQLiteHelper.LIST_TABLE_NAME, null, listValues);
    }
    database.setTransactionSuccessful();
    database.endTransaction();
    close(database);
    Log.d(TAG, "List saved");
    return id;
  }


  /**
   * Delete ItemList in database
   * @param itemListId
   */
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
    Log.d(TAG, "List deleted");
  }

  /**
   * Get Lists from database
   * @return
   */
  public List<ItemList> getLists(String orderBy) {
    List<ItemList> lists = new ArrayList<>();
    String [] columns =  new String [] {
            BaseColumns._ID,
            ListTrackerSQLiteHelper.LIST_COLUMN_CATEGORY_ID,
            ListTrackerSQLiteHelper.LIST_COLUMN_NAME,
            ListTrackerSQLiteHelper.LIST_COLUMN_MODIFIED_DATE,
            ListTrackerSQLiteHelper.LIST_COLUMN_CREATED_DATE
    };

    SQLiteDatabase database = open();
    Cursor cursor = database.query(
            ListTrackerSQLiteHelper.LIST_TABLE_NAME,
            columns,
            null, //selection
            null, //selection args
            null, //group by
            null, //having
            getOrderColumn(orderBy)
    );

    if (cursor.moveToFirst()) {
      do {
        ItemList itemList = new ItemList(getStringFromColumnName(cursor, ListTrackerSQLiteHelper.LIST_COLUMN_NAME));
        itemList.setId(getLongFromColumnName(cursor, BaseColumns._ID));
        itemList.setCategoryId(getLongFromColumnName(cursor, ListTrackerSQLiteHelper.LIST_COLUMN_CATEGORY_ID));
        itemList.setCreatedDate(getDateFromColumnName(cursor, ListTrackerSQLiteHelper.LIST_COLUMN_CREATED_DATE));
        itemList.setCreatedDate(getDateFromColumnName(cursor, ListTrackerSQLiteHelper.LIST_COLUMN_MODIFIED_DATE));
        lists.add(itemList);
      } while (cursor.moveToNext());
    }
    cursor.close();
    close(database);
    Log.d(TAG, "Database accessed: List");
    return lists;
  }

  private String getOrderColumn(String orderBy) {
    String orderByColumn = ListTrackerSQLiteHelper.LIST_COLUMN_CREATED_DATE + " ASC";
    if (orderBy != null && orderBy.equals("manual")) {
      orderByColumn = null;
    }
    if(orderBy != null && orderBy.equals("name")) {
      orderByColumn = ListTrackerSQLiteHelper.LIST_COLUMN_NAME + " ASC";
    }
    if(orderBy != null && orderBy.equals("modified")) {
      orderByColumn = ListTrackerSQLiteHelper.LIST_COLUMN_MODIFIED_DATE + " ASC";
    }
    return orderByColumn;
  }
}
