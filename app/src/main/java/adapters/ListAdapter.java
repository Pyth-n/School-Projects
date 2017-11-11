package adapters;

import android.content.Context;
import android.view.View;
import android.widget.ArrayAdapter;

import java.util.List;

import models.ItemList;

/**
 * Created by CarlosIribar on 11/10/17.
 */

public class ListAdapter extends ArrayAdapter<ItemList> implements View.OnClickListener {

  private Context mContext;
  private List<ItemList> lists;

  public ListAdapter(List<ItemList> data, Context context) {
    super(context, android.R.layout.simple_dropdown_item_1line, data);
    this.lists = data;
    this.mContext=context;
  }

  @Override
  public void onClick(View v) {
  }
}
