package com.android.rudra;

import android.annotation.SuppressLint;
import android.content.Context;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.os.CountDownTimer;
import android.util.Log;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import com.android.volley.NetworkResponse;
import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.JsonObjectRequest;
import com.android.volley.toolbox.Volley;

import org.json.JSONException;
import org.json.JSONObject;


public class MainActivity2 extends AppCompatActivity {
    protected TextView Temperature, Humidity,Name,Knock_listen,Sound_Read;

    public String temp,hum,knock,sound;
    RequestQueue requestQueue;
    JsonObjectRequest request;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main2);
        Temperature = findViewById(R.id.TempData);
        Humidity  = findViewById(R.id.HumData);
        Knock_listen = findViewById(R.id.connected);
        Sound_Read = findViewById(R.id.SoundData);

//        Name = findViewById(R.id.spell);
        SharedPreferences sh = getSharedPreferences("MySharedPref", Context.MODE_PRIVATE);

        //String botname = sh.getString("name", "");

        String url = sh.getString("url", "");

       // Name.setText(botname);
        String ipadd = url;


        requestQueue = Volley.newRequestQueue(this);


        CountDownTimer t = new CountDownTimer(Long.MAX_VALUE, 1000) {

            // This is called every interval. (Every 10 seconds in this example)
            public void onTick(long millisUntilFinished) {
                Log.d("test", "Timer tick");
                String url = "http://" + ipadd;
                request = new JsonObjectRequest(Request.Method.GET, url, null, new Response.Listener<JSONObject>() {
                    @SuppressLint("SetTextI18n")
                    @Override
                    public void onResponse(JSONObject response) {
                        try {

                            temp = response.getString("Temperature")+"C";
                            hum = response.getString("Humidity")+"%";
                            knock = response.getString("Knock");
                            sound = response.getString("Sound")+"dB";




                            if (knock.equals("1"))
                            {
                                Knock_listen.setText("Knock Heard");
                            }
                            else if (knock.equals("0")) {
                                Knock_listen.setText("No Knock Heard");
                            }

                            Temperature.setText(temp);
                            Humidity.setText(hum);
                            Sound_Read.setText(sound);


                        } catch (JSONException e) {

                            e.printStackTrace();

                        }

                    }
                }, new Response.ErrorListener() {

                    @Override
                    public void onErrorResponse(VolleyError error) {
                        Toast.makeText(getApplicationContext(), "Something went wrong", Toast.LENGTH_SHORT).show();
                        Log.d("robostatus", "something is not right");




                    }
                });
                requestQueue.add(request);

            }

            public void onFinish() {
                Log.d("test", "Timer last tick");
                start();
            }
        }.start();


    }

}
