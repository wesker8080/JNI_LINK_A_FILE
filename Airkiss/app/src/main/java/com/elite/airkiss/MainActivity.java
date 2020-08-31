package com.elite.airkiss;

import android.annotation.SuppressLint;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.widget.Button;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;



public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }
    TextView tv;
    TextView tvOne;
    TextView tvCclass;
    Button button;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        tv = findViewById(R.id.sample_text);
        tvOne = findViewById(R.id.tv_one);
        tvCclass = findViewById(R.id.tv_cclass);
        button = findViewById(R.id.button);
        tv.setText(stringFromJNI());
        tvCclass.setText("Cplusplus Class Test -> " + cPlusPlusClassFromJNI(4.0, 2.0, 3.0));
        //tvOne.setText(getFileContentFromJNI("sdcard/etLog/etl02.log"));
        handler.sendEmptyMessageDelayed(1,1000);
        writeFileContentFromJNI("sdcard/etLog/etl.log");
        button.setOnClickListener(v -> {
            //Intent intent = new Intent(MainActivity.this, Main2Activity.class);
            //intent.setFlags(Intent.FLAG_ACTIVITY_LAUNCH_ADJACENT|Intent.FLAG_ACTIVITY_NEW_TASK);
            //startActivity(intent);
          new Thread(){
              @Override
              public void run() {
                  //Looper.prepare();
                  Handler handler = new Handler(/*Looper.getMainLooper()*/){
                      @Override
                      public void handleMessage(Message msg) {
                        tvOne.setText("handleMessage");
                      }
                  };
                  handler.sendEmptyMessage(1);
                  //Looper.loop();
              }
          }.start();
        });
    }
    @SuppressLint("HandlerLeak")
    private Handler handler = new Handler(){
        @Override
        public void handleMessage(Message msg) {
            String nowTimeFromJNI = getNowTimeFromJNI();
            tv.setText(nowTimeFromJNI);
            handler.sendEmptyMessageDelayed(1,1000);
        }
    };
    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
    public native String getNowTimeFromJNI();
    public native String getFileContentFromJNI(String path);
    public native String writeFileContentFromJNI(String path);
    public native double cPlusPlusClassFromJNI(double height, double length, double breadth);
}
