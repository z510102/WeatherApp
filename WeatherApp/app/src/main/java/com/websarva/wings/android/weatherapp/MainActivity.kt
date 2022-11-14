package com.websarva.wings.android.weatherapp

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.os.Handler
import android.os.Looper
import android.util.Log
import android.view.View
import android.widget.AdapterView
import android.widget.ListView
import android.widget.SimpleAdapter
import android.widget.TextView
import androidx.annotation.UiThread
import androidx.annotation.WorkerThread
import androidx.core.os.HandlerCompat
import com.websarva.wings.android.weatherapp.R
import org.json.JSONObject
import java.io.BufferedReader
import java.io.InputStream
import java.io.InputStreamReader
import java.net.HttpURLConnection
import java.net.SocketTimeoutException
import java.net.URL
import java.util.concurrent.Executors

class MainActivity : AppCompatActivity() {
    companion object {
        private const val DEBUG_TAG = "WeatherApp"

        private const val WEATHERINFO_URL = "https://api.openweathermap.org/data/2.5/weather?lang=ja"
        private const val WEATHERTIME_URL = "https://api.openweathermap.org/data/2.5/forecast?lat={lat}&lon={lon}&appid={API key}"

        private const val APP_ID = "d69cb3b99bca1385860aafd20c655c95"
    }

    private var _list: MutableList<MutableMap<String, String>> = mutableListOf()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val q = intent.getStringExtra("q")

        val urlFull = "$WEATHERINFO_URL&q=$q&appid=$APP_ID"
        receiveWeatherInfo(urlFull)
    }

    @UiThread
    private fun receiveWeatherInfo(urlFull: String) {
        val handler = HandlerCompat.createAsync(mainLooper)
        val backgroundReceiver = WeatherInfoBackgroundReceiver(handler, urlFull)
        val executeService = Executors.newSingleThreadExecutor()
        executeService.submit(backgroundReceiver)
    }


    private inner class WeatherInfoBackgroundReceiver(handler: Handler, url: String): Runnable {
        private val _handler = handler

        private val _url = url

        @WorkerThread

        override fun run() {
            var result = ""

            val url = URL(_url)

            val con = url.openConnection() as? HttpURLConnection

            con?.let {
                try {
                    it.connectTimeout = 1000

                    it.readTimeout = 1000

                    it.requestMethod = "GET"

                    it.connect()

                    val stream = it.inputStream

                    result = is2String(stream)

                    stream.close()
                }

                catch (ex: SocketTimeoutException) {
                    Log.w(DEBUG_TAG, "通信タイムアウト", ex)
                }

                it.disconnect()
            }

            val postExecutor = WeatherInfoPostExecutor(result)
            _handler.post(postExecutor)
        }

        private fun is2String(stream: InputStream): String {
            val sb = StringBuilder()

            val reader = BufferedReader(InputStreamReader(stream, "UTF-8"))

            var line = reader.readLine()

            while(line != null) {
                sb.append(line)
                line = reader.readLine()
            }
            reader.close()
            return sb.toString()
        }
    }

    private inner class WeatherInfoPostExecutor(result: String): Runnable {
        private val _result = result

        @UiThread

        override fun run() {
            val rootJSON = JSONObject(_result)



            val cityName = intent.getStringExtra("cityName")

            val tvCityName = findViewById<TextView>(R.id.tvWeatherTelop)

            tvCityName.text = "${cityName}の天気"



            val weatherJSONArray = rootJSON.getJSONArray("weather")

            val weatherJSON = weatherJSONArray.getJSONObject(0)

            val weather = weatherJSON.getString("description")

            val desc = "${weather}"



            val coordJSON = rootJSON.getJSONObject("coord")

            val lat = coordJSON.getString("lat")

            val lon = coordJSON.getString("lon")

            val A = "$WEATHERTIME_URL&lat=$lat&lon=$lon&appid=$APP_ID"

            val weatherT = weatherJSON.getString("description")

            val descT = "${weatherT}"



            val main = rootJSON.getJSONObject("main")

            val max = "${main.getInt("temp_max")-273}℃ /"
            val min = "${main.getInt("temp_min")-273}℃"

            val maxT = "${main.getInt("temp_max")-273}℃ /"
            val minT = "${main.getInt("temp_min")-273}℃"



            val tvWeatherDesc = findViewById<TextView>(R.id.tvWeatherDesc)
            val tvWeatherDescT = findViewById<TextView>(R.id.tvWeatherDescT)
            val tvMax: TextView = findViewById(R.id.tvMax)
            val tvMin: TextView = findViewById(R.id.tvMin)
            val tvMaxT: TextView = findViewById(R.id.tvMaxT)
            val tvMinT: TextView = findViewById(R.id.tvMinT)

            tvWeatherDesc.text = desc
            tvWeatherDescT.text = descT
            tvMax.text = max
            tvMin.text = min
            tvMaxT.text = maxT
            tvMinT.text = minT
        }
    }

    fun onButtonClick(view: View) {
        val intent = Intent(this@MainActivity, ChangeCityActivity::class.java)

        startActivity(intent)
    }
}