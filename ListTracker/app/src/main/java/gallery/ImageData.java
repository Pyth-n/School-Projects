package gallery;

import android.net.Uri;

/**
 * Created by David on 12/3/2017.
 * Used to store image's path and item name
 */
public class ImageData {
    private String uri;
    private String itemName;

    public Uri getUri() {
        return Uri.parse(uri);
    }

    public void setUri(String uri) {
        this.uri = uri;
    }

    public String getItemName() {
        return itemName;
    }

    public void setItemName(String itemName) {
        this.itemName = itemName;
    }
}
