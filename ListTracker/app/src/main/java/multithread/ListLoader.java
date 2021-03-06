package multithread;

import android.content.Context;
import android.os.AsyncTask;
import android.util.Log;
import android.view.View;
import android.view.ViewGroup;
import android.view.ViewManager;
import android.widget.AbsListView;
import android.widget.ArrayAdapter;
import android.widget.ProgressBar;
import android.widget.Toast;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by David on 10/26/2017.
 */

public class ListLoader extends AsyncTask<Void, Integer, Void> {
    private final String TAG = this.getClass().getName();
    // Member Variables
    private Context mContext;
    private ProgressBar mProgressBar;

    private ArrayAdapter<String> mAdapter;
    private List<String> listNames;
    private List<String> listNamesString;
    private int status;


    public ListLoader(Context c, ArrayAdapter<String> adapter, ProgressBar progressBar, List<String> listNames) {
        this.mContext = c;
        this.mAdapter = adapter;
        this.mProgressBar = progressBar;
        this.listNames = listNames;
        listNamesString = new ArrayList<>();
        status = 0;
    }

    protected void onPreExecute() {
        mProgressBar.setVisibility(View.VISIBLE);
        mProgressBar.setProgress(status);
        Log.d(TAG, "Starting onPreExute()");
    }

    protected Void doInBackground(Void... params) {
        try {
            for (int i = 0; i < listNames.size(); i++) {
                listNamesString.add(listNames.get(i));
                publishProgress((i / listNames.size() * 100));
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
        if (mProgressBar != null) {
            mProgressBar.setVisibility(View.INVISIBLE);
            mAdapter.addAll(listNamesString);
            mAdapter.notifyDataSetChanged();
        }
        Toast.makeText(mContext, "Finished loading", Toast.LENGTH_SHORT).show();
    }
}
