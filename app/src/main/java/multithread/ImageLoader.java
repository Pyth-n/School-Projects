package multithread;

import android.os.AsyncTask;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by David on 10/26/2017.
 */

public class ImageLoader extends AsyncTask<Void, Integer, Void> {
    private List<String> images = new ArrayList<>();
    private String TAG;

    public ImageLoader(List<String> images, String tag) {
        this.images = images;
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
