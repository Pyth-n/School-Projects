package database;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.provider.BaseColumns;
import android.util.Log;

import java.util.ArrayList;
import java.util.List;

import models.Category;
import models.Category;

/**
 * Created by CarlosIribar on 11/9/17.
 */

public class CategoryCRUD extends ListTrackerDataSource implements CRUD {

    private final String TAG = this.getClass().getName();

    /**
     * CategoryCRUD constructor
     * @param contex
     */
    public CategoryCRUD(Context context) {
        super(context);
    }

    /**
     * Save Item List in database
     * @param category
     * @return
     */
    public long saveItemList(Category category) {
        long id;

        SQLiteDatabase database = open();
        database.beginTransaction();

        ContentValues categoryValues = new ContentValues();
        categoryValues.put(ListTrackerSQLiteHelper.CATEGORY_COLUMN_NAME  , category.getName());

        if (category.getId() !=  0) {
            categoryValues.put(BaseColumns._ID, category.getId());
            id = database.update(
                    ListTrackerSQLiteHelper.CATEGORY_TABLE_NAME,
                    categoryValues,
                    String.format("%s=%d", BaseColumns._ID, category.getId()), null);
        } else {
            id = database.insert(ListTrackerSQLiteHelper.CATEGORY_TABLE_NAME, null, categoryValues);
        }
        database.setTransactionSuccessful();
        database.endTransaction();
        close(database);
        Log.d(TAG, "Category saved");
        return id;
    }

    /**
     * Delete category from database
     * @param categoryId
     */
    public void delete(long categoryId) {
        SQLiteDatabase database = open();
        database.beginTransaction();

        database.delete(ListTrackerSQLiteHelper.LIST_TABLE_NAME,
                String.format("%s=%s", ListTrackerSQLiteHelper.LIST_COLUMN_CATEGORY_ID, String.valueOf(categoryId)),
                null);
        database.delete(ListTrackerSQLiteHelper.CATEGORY_TABLE_NAME,
                String.format("%s=%s", BaseColumns._ID, String.valueOf(categoryId)),
                null);
        database.setTransactionSuccessful();
        database.endTransaction();
        Log.d(TAG, "Category deleted");
    }

    /**
     * Get Categories from database
     * @return
     */
    public List<Category> getCategories() {
        List<Category> lists = new ArrayList<>();
        String [] columns =  new String [] {
                BaseColumns._ID,
                ListTrackerSQLiteHelper.CATEGORY_COLUMN_NAME
        };

        SQLiteDatabase database = open();
        Cursor cursor = database.query(
                ListTrackerSQLiteHelper.CATEGORY_TABLE_NAME,
                columns,
                null, //selection
                null, //selection args
                null, //group by
                null, //having
                null
        );

        if (cursor.moveToFirst()) {
            do {
                Category category = new Category(getStringFromColumnName(cursor, ListTrackerSQLiteHelper.LIST_COLUMN_NAME));
                category.setId(getLongFromColumnName(cursor, BaseColumns._ID));
                lists.add(category);
            } while (cursor.moveToNext());
        }
        cursor.close();
        close(database);
        Log.d(TAG, "Database accessed: Category");
        return lists;
    }
}
