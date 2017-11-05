package com.byui_cs246_team07.listtracker;

import android.os.AsyncTask;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by David on 10/26/2017.
 */

public class ListSaver extends AsyncTask<Void, Integer, Void> {
    private List<List> listToSave = new ArrayList<>();
    private String TAG;

    public ListSaver(List<List> list, String tag) {
        this.listToSave = list;
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
