package com.example.sanket.projectmlp;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import com.jjoe64.graphview.series.DataPoint;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Vector;

public class MainActivity extends AppCompatActivity {
    Button b1,b2;
    EditText ed1,ed2,ed3,ed4,ed5,ed6,ed7;
    TextView tx1;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        b1 = (Button)findViewById(R.id.button1);
        b2 = (Button)findViewById(R.id.button2);
        ed1 = (EditText)findViewById(R.id.editText1);
        ed2 = (EditText)findViewById(R.id.editText2);
        ed3 = (EditText)findViewById(R.id.editText3);
        ed4 = (EditText)findViewById(R.id.editText4);
        ed5 = (EditText)findViewById(R.id.editText5);
        ed6 = (EditText)findViewById(R.id.editText6);
        ed7 = (EditText)findViewById(R.id.editText7);
        tx1 = (TextView)findViewById(R.id.op);
        final Intent i = new Intent(this,graph.class);

        b2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startActivity(i);
            }
        });

        b1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                int indx=0;
                try {
                    BufferedReader reader = new BufferedReader(new InputStreamReader(getAssets().open("mlpWeights.csv")));
                    String mline;
                    String valXY[];
                    Integer rows = -1;
                    Integer cols = -1;
                    Double res = 0.0;
                    int flag = 1;
                    int count = 0;

                    ArrayList <ArrayList <Double>> weights = new ArrayList<>();
                    ArrayList <Double> inputs = new ArrayList<>();
                    ArrayList <Double> outputs = new ArrayList<>();
                    inputs.add(1.0);
                    inputs.add(Double.parseDouble(ed1.getText().toString()));
                    inputs.add(Double.parseDouble(ed2.getText().toString()));
                    inputs.add(Double.parseDouble(ed3.getText().toString()));
                    inputs.add(Double.parseDouble(ed4.getText().toString()));
                    inputs.add(Double.parseDouble(ed5.getText().toString()));
                    inputs.add(Double.parseDouble(ed6.getText().toString()));
                    inputs.add(Double.parseDouble(ed7.getText().toString()));
                    while ((mline = reader.readLine()) != null) {
                        if(flag==1) {
                            valXY = mline.split(",");
                            rows = Integer.parseInt(valXY[0]);
                            cols = Integer.parseInt(valXY[1]);
                            System.out.print(rows+" "+cols+"\n");
                            count = 0;
                            flag=0;
                        }
                        else {
                            valXY = mline.split(",");
                            ArrayList<Double> tmp = new ArrayList<>();
                            for (int j = 0; j < cols; j++) {
                                tmp.add(Double.parseDouble(valXY[j]));
                                System.out.print(Double.parseDouble(valXY[j])+ " ");
                            }
                            System.out.println();
                            weights.add(tmp);
                            count++;
                            if(count==rows){
                                flag=1;
                                for(int i=0;i<rows;i++){
                                    res=0.0;
                                    for(int j=0;j<cols;j++){
                                        res += weights.get(i).get(j)*inputs.get(j);
                                    }
                                    outputs.add(res);
                                }
                                weights.clear();
                                inputs.clear();
                                for(int k=0;k<outputs.size();k++){
                                    inputs.add(outputs.get(k));
                                }
                                inputs.add(0,1.0);
                                outputs.clear();
                            }
                        }
                    }
                    res=inputs.get(0);
                    inputs.remove(0);
                    for(int x=0;x<inputs.size();x++){
                        if(res < inputs.get(x)){
                            res=inputs.get(x);
                            indx = x+1;
                        }
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                }

                tx1.setText("Output = "+ new Double(indx).toString());
            }
        });

    }

}
