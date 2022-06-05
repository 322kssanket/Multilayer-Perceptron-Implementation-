package com.example.sanket.projectmlp;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.animation.Animation;
import android.view.animation.AnimationUtils;
import android.widget.ImageView;
import android.widget.TextView;
import com.example.atharv.projectmlp.R;

public class splashscreen extends AppCompatActivity {
    private TextView txtv;
    private ImageView imgv;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_splashscreen);
        txtv = (TextView) findViewById(R.id.tv);
        imgv = (ImageView) findViewById(R.id.iv);
        Animation anim1 = AnimationUtils.loadAnimation(this,R.anim.transition);
        //final Animation anim2 = AnimationUtils.loadAnimation(this,R.anim.rotate_img);
        txtv.startAnimation(anim1);
        imgv.startAnimation(anim1);
        anim1.setAnimationListener(new Animation.AnimationListener() {
            @Override
            public void onAnimationStart(Animation animation) {

            }

            @Override
            public void onAnimationEnd(Animation animation) {
                //imgv.startAnimation(anim2);
            }

            @Override
            public void onAnimationRepeat(Animation animation) {

            }
        });

        final Intent i = new Intent(this,MainActivity.class);
        Thread timer = new Thread(){
            public void run(){
                try{
                    sleep(8000);
                }
                catch (InterruptedException e)
                {
                    e.printStackTrace();
                }
                finally {
                    startActivity(i);
                    overridePendingTransition(R.anim.slide_in_right, R.anim.hold_on_close);
                }
            }
        };
        timer.start();
    }
}
