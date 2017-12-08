package multithread;

import android.content.Context;
import android.os.AsyncTask;
import android.util.Log;
import android.view.ViewManager;
import android.widget.ArrayAdapter;
import android.widget.ProgressBar;

import java.util.List;

import models.Item;


/**
 * Created by David on 10/26/2017.
 */

public class ListItemLoader extends AsyncTask<Void, Integer, Void> {

    private ProgressBar mProgressBar;
    private ArrayAdapter<String> mAdapter;
    private List<Item> itemNames;
    private int status;

    public ListItemLoader(ArrayAdapter<String> adapter, List<Item> itemNames, ProgressBar progressBar) {
        this.mAdapter = adapter;
        this.itemNames = itemNames;
        this.mProgressBar = progressBar;
        status = 0;
    }

    protected void onPreExecute() {
        mProgressBar.setProgress(status);
    }

    protected Void doInBackground(Void... params) {
        try {
            int i = 0;
            for (Item item : itemNames) {
                mAdapter.add(item.getName());
                publishProgress((i++ / itemNames.size() * 100));
            }


        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }

    protected void onProgressUpdate(Integer... value) {
        mProgressBar.setProgress(value[0]);
    }

    protected void onPostExecute(Void value) {
        ((ViewManager) mProgressBar.getParent()).removeView(mProgressBar);
        Log.d("ITEMLOAD", "Finished loading items");
    }
}
