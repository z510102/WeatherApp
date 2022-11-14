package com.websarva.wings.android.weatherapp

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.view.View
import android.widget.Adapter
import android.widget.AdapterView
import android.widget.ListView
import android.widget.SimpleAdapter
import android.widget.Spinner

class ChooseCityActivity : AppCompatActivity() {
    companion object {
        private const val DEBUG_TAG = "WeatherApp"

        private const val WEATHERINFO_URL = "https://api.openweathermap.org/data/2.5/weather?lang=ja"

        private const val APP_ID = "d69cb3b99bca1385860aafd20c655c95"
    }

    private var _list: MutableList<MutableMap<String, String>> = mutableListOf()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_choose_city)

        _list = createList()

        val lvCityList = findViewById<ListView>(R.id.lvCityList)

        //SimpleAdapter第4引数to用データの用意
        val from = arrayOf("name")

        //SimpleAdapter第5引数to用データの用意
        val to = intArrayOf(android.R.id.text1)

        //SimpleAdapterを生成
        val adapter = SimpleAdapter(this@ChooseCityActivity, _list, android.R.layout.simple_list_item_1, from, to)

        //アダプタの登録
        lvCityList.adapter = adapter

        lvCityList.onItemClickListener = ListItemClickListener()
    }

    private fun createList(): MutableList<MutableMap<String, String>> {
        //SimpleAdapterで使用するMutableListオブジェクトを用意
        var list: MutableList<MutableMap<String, String>> = mutableListOf()

        //それぞれのデータを格納するMapオブジェクトの用意とlistへのデータ登録
        var city = mutableMapOf("name" to "札幌", "q" to "Sapporo")
        list.add(city)

        city = mutableMapOf("name" to "東京", "q" to "Tokyo")
        list.add(city)

        city = mutableMapOf("name" to "横浜", "q" to "Yokohama")
        list.add(city)

        city = mutableMapOf("name" to "名古屋", "q" to "Nagoya")
        list.add(city)

        city = mutableMapOf("name" to "京都", "q" to "Kyoto")
        list.add(city)

        city = mutableMapOf("name" to "奈良", "q" to "Nara")
        list.add(city)

        city = mutableMapOf("name" to "大阪", "q" to "Osaka")
        list.add(city)

        city = mutableMapOf("name" to "神戸", "q" to "Kobe")
        list.add(city)

        city = mutableMapOf("name" to "広島", "q" to "Hiroshima")
        list.add(city)

        city = mutableMapOf("name" to "沖縄", "q" to "Okinawa")
        list.add(city)

        return list
    }

    private fun receiveWeatherInfo(urlFull: String) {

    }

    private inner class ListItemClickListener: AdapterView.OnItemClickListener {
        override fun onItemClick(parent: AdapterView<*>, view: View, position: Int, id: Long) {

            val item = parent.getItemAtPosition(position) as MutableMap<String, String>

            val q = item.get("q")

            q?.let {
                val urlFull = "$WEATHERINFO_URL&q=$q&appid=$APP_ID"
                receiveWeatherInfo(urlFull)
            }

            val cityName = item["name"]
            val qM = item["q"]

            //インテントオブジェクトを生成
            val intent = Intent(this@ChooseCityActivity, MainActivity::class.java)

            intent.putExtra("cityName", cityName)
            intent.putExtra("q", qM)

            //MainActivityの起動
            startActivity(intent)
        }
    }
}