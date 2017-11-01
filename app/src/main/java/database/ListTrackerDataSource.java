package database;

import android.content.ContentValues;
import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.provider.BaseColumns;
import android.text.TextUtils;

import java.util.Date;

import models.Item;
import models.ItemList;

/**
 * Created by CarlosIribar on 10/30/17.
 */

public class ListTrackerDataSource {

    private Context _context;
    private ListTrackerSQLiteHelper _sqLiteHelper;

    public ListTrackerDataSource(Context context) {
        _context = context;
        _sqLiteHelper = new ListTrackerSQLiteHelper(context);
    }

    private SQLiteDatabase open() {
        return _sqLiteHelper.getWritableDatabase();
    }

    private void close(SQLiteDatabase database) {
        database.close();
    }

    public long saveItemList(ItemList itemList) {
        long id;
        SQLiteDatabase database = open();
        database.beginTransaction();

        ContentValues listValues = new ContentValues();
        listValues.put(ListTrackerSQLiteHelper.LIST_COLUMN_NAME  , itemList.getName());
        listValues.put(ListTrackerSQLiteHelper.LIST_COLUMN_CATEGORY, itemList.getCategory());

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

    public long saveItem(Item item) {
        long id;
        SQLiteDatabase database = open();
        database.beginTransaction();

        ContentValues itemValues = new ContentValues();
        itemValues.put(ListTrackerSQLiteHelper.ITEM_COLUMN_NAME, item.getName());
        itemValues.put(ListTrackerSQLiteHelper.ITEM_COLUMN_NOTES, item.getNotes());
        Boolean isCompleted = item.getCompleted();

        itemValues.put(ListTrackerSQLiteHelper.ITEM_COLUMN_COMPLETED, isCompleted ? 1: 0);
        itemValues.put(ListTrackerSQLiteHelper.ITEM_COLUMN_CREATED_DATE, new Date().toString());
        itemValues.put(ListTrackerSQLiteHelper.ITEM_COLUMN_DUE_DATE, item.getDueDate().toString());

        itemValues.put(ListTrackerSQLiteHelper.ITEM_COLUMN_IMAGE_URLS, TextUtils.join("##", item.getImagesUrls()));
        itemValues.put(ListTrackerSQLiteHelper.ITEM_COLUMN_TAGS, TextUtils.join("##", item.getTags()));
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
        return id;
    }

    public void deleteItem(long itemId) {
        SQLiteDatabase database = open();
        database.beginTransaction();

        database.delete(ListTrackerSQLiteHelper.ITEM_TABLE_NAME,
                String.format("%s=%s", BaseColumns._ID, String.valueOf(itemId)),
                null);
        database.setTransactionSuccessful();
        database.endTransaction();
    }

    public void deleteItemList(long itemListId) {
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

}
