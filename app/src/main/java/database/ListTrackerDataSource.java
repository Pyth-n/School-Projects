package database;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.provider.BaseColumns;
import android.text.TextUtils;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

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
            itemValues.put(ListTrackerSQLiteHelper.ITEM_COLUMN_TAGS, TextUtils.join("##", item.getTags()));
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

    public List<ItemList> getLists() {
        List<ItemList> lists = new ArrayList<>();
        String [] columns =  new String [] {
                BaseColumns._ID,
                ListTrackerSQLiteHelper.LIST_COLUMN_CATEGORY,
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
                itemList.setCategory(getStringFromColumnName(cursor, ListTrackerSQLiteHelper.LIST_COLUMN_CATEGORY));
                lists.add(itemList);
            } while (cursor.moveToNext());
        }
        cursor.close();
        close(database);
        return lists;
    }

    public List<Item> getItems() {
        List<Item> items = new ArrayList<>();
        String [] columns =  new String [] {
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
                Item item = new Item(getStringFromColumnName(cursor, ListTrackerSQLiteHelper.ITEM_COLUMN_NAME));
                item.setNotes(getStringFromColumnName(cursor, ListTrackerSQLiteHelper.ITEM_COLUMN_NOTES));
                item.setPriority(getIntFromColumnName(cursor, ListTrackerSQLiteHelper.ITEM_COLUMN_PRIORITY));
                item.setCompleted(getBooleanFromColumnName(cursor, ListTrackerSQLiteHelper.ITEM_COLUMN_COMPLETED));
                item.setCreatedDate(getDateFromColumnName(cursor, ListTrackerSQLiteHelper.ITEM_COLUMN_CREATED_DATE));
                item.setId(getLongFromColumnName(cursor, BaseColumns._ID));
                item.setDueDate(getDateFromColumnName(cursor, ListTrackerSQLiteHelper.ITEM_COLUMN_DUE_DATE));
                item.setListId(getLongFromColumnName(cursor, ListTrackerSQLiteHelper.ITEM_COLUMN_FOREIGN_KEY_LIST));
                items.add(item);
            } while (cursor.moveToNext());
        }
        cursor.close();
        close(database);
        return items;
    }

    private int getIntFromColumnName(Cursor cursor, String columnName) {
        int columnIndex = cursor.getColumnIndex(columnName);
        return cursor.getInt(columnIndex);
    }

    private long getLongFromColumnName(Cursor cursor, String columnName) {
        int columnIndex = cursor.getColumnIndex(columnName);
        return cursor.getLong(columnIndex);
    }

    private String getStringFromColumnName(Cursor cursor, String columnName) {
        int columnIndex = cursor.getColumnIndex(columnName);
        return cursor.getString(columnIndex);
    }

    private Boolean getBooleanFromColumnName(Cursor cursor, String columnName) {
        int columnIndex = cursor.getColumnIndex(columnName);
        return cursor.getInt(columnIndex) != 0;
    }

    private Date getDateFromColumnName(Cursor cursor, String columnName) {
        Date convertedDate = new Date();
        int columnIndex = cursor.getColumnIndex(columnName);
        String dateString = cursor.getString(columnIndex);
        if (dateString != null) {
            SimpleDateFormat dateFormat = new SimpleDateFormat("MM/dd/yyyy hh:mm:ss aa");
            try {
                convertedDate = dateFormat.parse(dateString);
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        return convertedDate;
    }
}
