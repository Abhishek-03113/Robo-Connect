package com.android.rudra;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {
    Button Login;
    public EditText name;
    public EditText ip;
    static public String boturl;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Login = (Button) findViewById(R.id.button);
//        name = (EditText) findViewById(R.id.name);
        ip = (EditText) findViewById(R.id.url);


        Login.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
//                Intent activity = new Intent(this, MainActivity2.class);
                Intent myIntent = new Intent(MainActivity.this, MainActivity2.class);
                startActivity(myIntent);
                Toast.makeText(getApplicationContext(),
                        "Connection Succesfull",
                        Toast.LENGTH_LONG).show();

                SharedPreferences sharedPreferences = getSharedPreferences("MySharedPref",MODE_PRIVATE);


                SharedPreferences.Editor myEdit = sharedPreferences.edit();

                //myEdit.putString("name", name.getText().toString());
                myEdit.putString("url", ip.getText().toString());

                myEdit.apply();
            }
        });


    }
}