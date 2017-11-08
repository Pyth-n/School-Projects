package multithread;

import android.os.AsyncTask;



/**
 * Created by David on 10/26/2017.
 */

public class Sorter extends AsyncTask<Void, Integer, Void> {
    private String sortCriteria;
    private boolean isAsc;
    private String TAG;

    public Sorter(String sortCriteria, boolean isAsc) {
        this.sortCriteria = sortCriteria;
        this.isAsc = isAsc;
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
