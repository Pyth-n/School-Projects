package reminder;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;

import com.byui_cs246_team07.listtracker.MainActivity;
import com.byui_cs246_team07.listtracker.R;


/**
 * This is the activity that is started when the user presses the notification in the status bar
 */
public class NotificationPressedActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_notification_pressed);

        Intent intent = new Intent(this, MainActivity.class);
        startActivity(intent);
        finish();
    }

}