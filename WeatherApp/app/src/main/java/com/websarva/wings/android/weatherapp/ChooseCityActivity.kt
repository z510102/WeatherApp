package com.websarva.wings.android.weatherapp

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.view.View
import android.widget.AdapterView
import android.widget.ListView

class ChooseCityActivity : AppCompatActivity() {
    private var _list: MutableList<MutableMap<String, String>> = mutableListOf()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_choose_city)
    }

    fun onButtonClick(view: View) {
        val intent = Intent(this@ChooseCityActivity, MainActivity::class.java)

        startActivity(intent)
    }
}