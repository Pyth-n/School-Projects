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

    /**
     * ListTrackerDataSource Constructor
     * @param context
     */
    public ListTrackerDataSource(Context context) {
        _context = context;
        _sqLiteHelper = new ListTrackerSQLiteHelper(context);
    }

    /**
     * Open database connection
     * @return
     */
    protected SQLiteDatabase open() {
        return _sqLiteHelper.getWritableDatabase();
    }

    /**
     * Close database connection
     * @param database
     */
    protected void close(SQLiteDatabase database) {
        database.close();
    }


    /**
     * Get int values from column in db
     * @param cursor
     * @param columnName
     * @return
     */
    protected int getIntFromColumnName(Cursor cursor, String columnName) {
        int columnIndex = cursor.getColumnIndex(columnName);
        return cursor.getInt(columnIndex);
    }

    /**
     * Get long values from column in db
     * @param cursor
     * @param columnName
     * @return
     */
    protected long getLongFromColumnName(Cursor cursor, String columnName) {
        int columnIndex = cursor.getColumnIndex(columnName);
        return cursor.getLong(columnIndex);
    }

    /**
     * Get String from column in db
     * @param cursor
     * @param columnName
     * @return
     */
    protected String getStringFromColumnName(Cursor cursor, String columnName) {
        int columnIndex = cursor.getColumnIndex(columnName);
        if (columnIndex > -1) {
            return cursor.getString(columnIndex);
        }
        return null;
    }

    /**
     * Get Boolean rom column in db
     * @param cursor
     * @param columnName
     * @return
     */
    protected Boolean getBooleanFromColumnName(Cursor cursor, String columnName) {
        int columnIndex = cursor.getColumnIndex(columnName);
        return cursor.getInt(columnIndex) != 0;
    }

    /**
     * Get Date from column name
     * @param cursor
     * @param columnName
     * @return
     */
    protected Date getDateFromColumnName(Cursor cursor, String columnName) {
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
