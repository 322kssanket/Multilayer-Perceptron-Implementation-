package com.example.sanket.projectmlp;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

import com.jjoe64.graphview.GraphView;
import com.jjoe64.graphview.series.DataPoint;
import com.jjoe64.graphview.series.LineGraphSeries;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;

public class graph extends AppCompatActivity {

    String valXY[];
    Double Xval;
    Double Yval;
    GraphView graph;
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_graph);
        GraphView graph = (GraphView) findViewById(R.id.graph);

        //BufferedReader reader = null;
        try {
            BufferedReader reader = new BufferedReader(new InputStreamReader(getAssets().open("error_vs_iters.csv")));
            //reader.readLine();  //skip first line of file
            //reader.readLine();  //skip second line of file
            String mline;

            ArrayList<DataPoint> arrDataPoint=new ArrayList<>();
            System.out.println("Hello");
            while ((mline = reader.readLine()) != null) {
                valXY = mline.split(",");
                Xval = Double.parseDouble(valXY[0]);
                Yval = Double.parseDouble(valXY[1]);
                DataPoint dp = new DataPoint(Xval, Yval);
                arrDataPoint.add(dp);
                System.out.println(Xval+" "+Yval);
            }
            DataPoint[] listDp = new DataPoint[arrDataPoint.size()];

            for(int i=0;i<arrDataPoint.size();i++){
                listDp[i]=arrDataPoint.get(i);
            }

            LineGraphSeries<DataPoint> series = new LineGraphSeries<>(listDp);
            graph.addSeries(series);
        } catch (IOException e) {
            e.printStackTrace();
        }
        graph.getViewport().setXAxisBoundsManual(true);
        graph.getViewport().setMinX(0);
        graph.getViewport().setMaxX(2000);

        //graph.getViewport().setScrollable(true); // enables horizontal scrolling
        //graph.getViewport().setScrollableY(true); // enables vertical scrolling

    }

}
