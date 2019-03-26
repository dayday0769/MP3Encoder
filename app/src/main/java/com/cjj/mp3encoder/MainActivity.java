package com.cjj.mp3encoder;

import android.os.Bundle;
import android.os.Environment;

import java.io.File;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
//        TextView tv = findViewById(R.id.sample_text);
////        tv.setText(JniManager.getInstance().stringFromJNI());
//        tv.setText(JniManager.getInstance().getLameVersion());

        String pcmPath = Environment.getExternalStorageDirectory().getAbsolutePath()+ File.separator+"16k.pcm";
        String mp3Path = Environment.getExternalStorageDirectory().getAbsolutePath()+ File.separator+"16k.mp3";
        JniManager.getInstance().init(pcmPath, 1, 16, 8000, mp3Path);
        JniManager.getInstance().encode();
        JniManager.getInstance().destroy();

    }


}
