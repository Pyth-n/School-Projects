package multithread;

import android.os.AsyncTask;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by David on 10/26/2017.
 */

public class ListLoader extends AsyncTask<Void, Integer, Void> {
    // Member Variables
    private List<List> list = new ArrayList<>();
    private String TAG = this.getClass().getName();

    public ListLoader(List<List> list, String tag) {
        this.list = list;
        this.TAG = tag;
    }

    protected void onPreExecute() {

    }

    protected Void doInBackground(Void... params) {

        return null;
    }

    protected void onProgressUpdate(Integer... value) {

    }

    protected void onPostExecute(Void value) {

    }
}
