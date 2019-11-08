package gallery;

import android.content.Context;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;

import com.byui_cs246_team07.listtracker.R;
import com.squareup.picasso.Picasso;

import java.util.ArrayList;

/**
 * Created by David on 12/3/2017.
 */
public class ImgAdapter extends RecyclerView.Adapter<ImgAdapter.ViewHolder> {

    private ArrayList<ImageData> galleryList;
    private Context context;

    public ImgAdapter(Context context, ArrayList<ImageData> galleryList) {
        this.galleryList = galleryList;
        this.context = context;
    }

    @Override
    public ImgAdapter.ViewHolder onCreateViewHolder(ViewGroup viewGroup, int i) {
        View view = LayoutInflater.from(viewGroup.getContext()).inflate(R.layout.cell_layout, viewGroup, false);
        return new ViewHolder(view);
    }

    @Override
    public void onBindViewHolder(ImgAdapter.ViewHolder viewHolder, int i) {
        viewHolder.title.setText(galleryList.get(i).getItemName());
        viewHolder.img.setScaleType(ImageView.ScaleType.CENTER_CROP);
        Picasso.with(context).load(galleryList.get(i).getUri()).into(viewHolder.img);
    }

    @Override
    public int getItemCount() {
        return galleryList.size();
    }

    public class ViewHolder extends RecyclerView.ViewHolder{
        private TextView title;
        private ImageView img;
        public ViewHolder(View view) {
            super(view);

            title = (TextView)view.findViewById(R.id.titles);
            img = (ImageView) view.findViewById(R.id.imgs);
        }
    }


}

