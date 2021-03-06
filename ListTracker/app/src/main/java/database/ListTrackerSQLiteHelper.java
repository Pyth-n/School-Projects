package database;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.provider.BaseColumns;

/**
 * Created by CarlosIribar on 10/28/17.
 */

public class ListTrackerSQLiteHelper extends SQLiteOpenHelper {

    private static final int DATABASE_VERSION = 1;
    private static final String DATABASE_NAME = "listTracker.db";

    //CATEGORY
    public static final String CATEGORY_TABLE_NAME = "Category";
    public static final String CATEGORY_COLUMN_NAME = "name";

    private static final String CREATE_CATEGORY_TABLE =
            "CREATE TABLE " + CATEGORY_TABLE_NAME + '(' +
                    BaseColumns._ID + " INTEGER PRIMARY KEY AUTOINCREMENT, " +
                    CATEGORY_COLUMN_NAME + " TEXT NOT NULL " +
                    ")";

    // LIST
    public static final String LIST_TABLE_NAME = "list";
    public static final String LIST_COLUMN_NAME = "name";
    public static final String LIST_COLUMN_CATEGORY_ID = "categoryID";
    public static final String LIST_COLUMN_CREATED_DATE = "createdDate";
    public static final String LIST_COLUMN_MODIFIED_DATE = "modifiedDate";

    private static final String CREATE_LIST_TABLE =
            "CREATE TABLE " + LIST_TABLE_NAME + '(' +
                    BaseColumns._ID + " INTEGER PRIMARY KEY AUTOINCREMENT, " +
                    LIST_COLUMN_NAME + " TEXT NOT NULL, " +
                    LIST_COLUMN_CREATED_DATE + " TEXT NOT NULL , " +
                    LIST_COLUMN_MODIFIED_DATE + " TEXT NOT NULL , " +
                    LIST_COLUMN_CATEGORY_ID + " INTEGER, " +
                    "FOREIGN KEY(" + LIST_COLUMN_CATEGORY_ID + ") REFERENCES "+ CATEGORY_TABLE_NAME +"(_ID)" +
                    ")";

    // ITEM TABLE
    public static final String ITEM_TABLE_NAME = "item";
    public static final String ITEM_COLUMN_NAME = "name";
    public static final String ITEM_COLUMN_NOTES = "notes";
    public static final String ITEM_COLUMN_CREATED_DATE = "created_date";
    public static final String ITEM_COLUMN_MODIFIED_DATE = "modified_date";
    public static final String ITEM_COLUMN_DUE_DATE = "due_date";
    public static final String ITEM_COLUMN_PRIORITY = "priority";
    public static final String ITEM_COLUMN_PRIORITY_NAME = "priorityName";
    public static final String ITEM_COLUMN_TAGS = "tags";
    public static final String ITEM_COLUMN_COMPLETED = "completed";
    public static final String ITEM_COLUMN_IMAGE_URLS = "image_urls";
    public static final String ITEM_COLUMN_FOREIGN_KEY_LIST = "list_id";
    private static final String CREATE_ITEM_TABLE =
            "CREATE TABLE " + ITEM_TABLE_NAME + '(' +
                    BaseColumns._ID + " INTEGER PRIMARY KEY AUTOINCREMENT, " +
                    ITEM_COLUMN_NAME + " TEXT NOT NULL, " +
                    ITEM_COLUMN_NOTES + " TEXT, " +
                    ITEM_COLUMN_CREATED_DATE + " TEXT NOT NULL , " +
                    ITEM_COLUMN_MODIFIED_DATE + " TEXT NOT NULL , " +
                    ITEM_COLUMN_DUE_DATE + " TEXT, " +
                    ITEM_COLUMN_PRIORITY_NAME + " TEXT, " +
                    ITEM_COLUMN_PRIORITY +" INTEGER, " +
                    ITEM_COLUMN_TAGS + " TEXT, " +
                    ITEM_COLUMN_COMPLETED + " INTEGER NOT NULL CHECK (" + ITEM_COLUMN_COMPLETED + " IN (0,1)), " +
                    ITEM_COLUMN_IMAGE_URLS + " TEXT, " +
                    ITEM_COLUMN_FOREIGN_KEY_LIST + " INTEGER, " +
                    "FOREIGN KEY(" + ITEM_COLUMN_FOREIGN_KEY_LIST + ") REFERENCES "+ LIST_TABLE_NAME +"(_ID)" +
                    ")";


    /**
     * ListTrackerSQLiteHelper Constructor
     * @param context
     */
    public ListTrackerSQLiteHelper(Context context) {
        super(context, DATABASE_NAME, null, DATABASE_VERSION);
    }

    /**
     * Create SQL database
     * @param db
     */
    @Override
    public void onCreate(SQLiteDatabase db) {
        db.execSQL(CREATE_CATEGORY_TABLE);
        db.execSQL(CREATE_LIST_TABLE);
        db.execSQL(CREATE_ITEM_TABLE);
    }

    /**
     * Update database
     * @param db
     * @param oldVersion
     * @param newVersion
     */
    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {

    }

}
