package database;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.provider.BaseColumns;
import android.text.TextUtils;
import android.util.Log;

import java.text.SimpleDateFormat;
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
            ListTrackerSQLiteHelper.ITEM_COLUMN_PRIORITY_NAME,
            ListTrackerSQLiteHelper.ITEM_COLUMN_MODIFIED_DATE
    };

    /**
     * ItemCRUD constructor
     * @param contex
     */
    public ItemCRUD(Context contex) {
        super(contex);
    }

    /**
     * Save Item in database
     * @param item
     * @return
     */
    public long saveItem(Item item) {

        long id;
        SimpleDateFormat dateFormat = new SimpleDateFormat("MM/dd/yyyy hh:mm:ss aa");
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

        Date date = new Date();
        if (item.getId() != 0) {
            itemValues.put(BaseColumns._ID, item.getId());
            String dateTime = dateFormat.format(date);
            itemValues.put(ListTrackerSQLiteHelper.ITEM_COLUMN_MODIFIED_DATE, dateTime);

            id = database.update(
                    ListTrackerSQLiteHelper.ITEM_TABLE_NAME,
                    itemValues,
                    String.format("%s=%d", BaseColumns._ID, item.getId()), null);
        } else {
            String dateTime = dateFormat.format(date);
            itemValues.put(ListTrackerSQLiteHelper.ITEM_COLUMN_CREATED_DATE, dateTime);
            itemValues.put(ListTrackerSQLiteHelper.ITEM_COLUMN_MODIFIED_DATE, dateTime);

            id = database.insert(ListTrackerSQLiteHelper.ITEM_TABLE_NAME, null, itemValues);
        }

        database.setTransactionSuccessful();
        database.endTransaction();
        close(database);
        Log.d(TAG, "Item saved");
        return id;
    }

    /**
     * Delete item in database
     * @param itemId
     */
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


    /**
     * Get Items from database
     * @return
     */
    public List<Item> getItems(String orderBy) {

        List<Item> items = new ArrayList<>();

        String orderByColumn = getOrderColumn(orderBy);
        SQLiteDatabase database = open();
        Cursor cursor = database.query(
                ListTrackerSQLiteHelper.ITEM_TABLE_NAME,
                columns,
                null, //selection
                null, //selection args
                null, //group by
                null, //having
                orderByColumn
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

    /**
     * Get Items from List in database
     * @param listId
     * @return
     */
    public List<Item> getItemsFromList(long listId, String orderBy) {
        List<Item> items = new ArrayList<>();
        String whereClause =  ListTrackerSQLiteHelper.ITEM_COLUMN_FOREIGN_KEY_LIST + "= ?";
        String[] whereArgs = new String[]{
                String.valueOf(listId)
        };


        String orderByColumn = getOrderColumn(orderBy);
        Log.d("OrderBYColumn", orderByColumn);
        SQLiteDatabase database = open();
        Cursor cursor = database.query(
                ListTrackerSQLiteHelper.ITEM_TABLE_NAME,
                columns,
                whereClause, //selection
                whereArgs, //selection args
                null, //group by
                null, //having
                orderByColumn
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

    /**
     * Create new Item instance
     * @param cursor
     * @return
     */
    private Item createItem(Cursor cursor) {

        Item item = new Item(getStringFromColumnName(cursor, ListTrackerSQLiteHelper.ITEM_COLUMN_NAME));
        item.setNotes(getStringFromColumnName(cursor, ListTrackerSQLiteHelper.ITEM_COLUMN_NOTES));
        item.setTags(getStringFromColumnName(cursor, ListTrackerSQLiteHelper.ITEM_COLUMN_TAGS));
        item.setPriority(getIntFromColumnName(cursor, ListTrackerSQLiteHelper.ITEM_COLUMN_PRIORITY));
        item.setCompleted(getBooleanFromColumnName(cursor, ListTrackerSQLiteHelper.ITEM_COLUMN_COMPLETED));
        item.setCreatedDate(getDateFromColumnName(cursor, ListTrackerSQLiteHelper.ITEM_COLUMN_CREATED_DATE));
        item.setModifiedDate(getDateFromColumnName(cursor, ListTrackerSQLiteHelper.ITEM_COLUMN_MODIFIED_DATE));

        item.setId(getLongFromColumnName(cursor, BaseColumns._ID));
        item.setDueDate(getDateFromColumnName(cursor, ListTrackerSQLiteHelper.ITEM_COLUMN_DUE_DATE));
        item.setListId(getLongFromColumnName(cursor, ListTrackerSQLiteHelper.ITEM_COLUMN_FOREIGN_KEY_LIST));
        item.setPriorityName(getStringFromColumnName(cursor, ListTrackerSQLiteHelper.ITEM_COLUMN_PRIORITY_NAME));
        item.setImagesUrls(getListFromColumnName(cursor, ListTrackerSQLiteHelper.ITEM_COLUMN_IMAGE_URLS));
        return item;
    }

    private String getOrderColumn(String orderBy) {
        String orderByColumn = ListTrackerSQLiteHelper.ITEM_COLUMN_CREATED_DATE + " ASC";
        if (orderBy != null && orderBy.equals("manual")) {
            orderByColumn = null;
        }

        if(orderBy != null && orderBy.equals("name")) {
            orderByColumn = ListTrackerSQLiteHelper.ITEM_COLUMN_NAME + " ASC";
        }

        if(orderBy != null && orderBy.equals("modified")) {
            orderByColumn = ListTrackerSQLiteHelper.ITEM_COLUMN_MODIFIED_DATE + " ASC";
        }
        return orderByColumn;
    }
}
