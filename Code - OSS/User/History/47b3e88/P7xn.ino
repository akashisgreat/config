#include <Arduino.h>

#include "DNSServer.h"        // Содержится в пакете.
#include "ESP8266WebServer.h" // Содержится в пакете.
#include "WiFiManager.h"      // https://github.com/tzapu/WiFiManager

#include "AudioFileSourceBuffer.h" // https://github.com/earlephilhower/ESP8266Audio
#include "AudioFileSourceICYStream.h" // https://github.com/earlephilhower/ESP8266Audio
#include "AudioGeneratorMP3.h" // https://github.com/earlephilhower/ESP8266Audio
#include <ESP8266WiFi.h>
// #include "AudioGeneratorAAC.h"          //
// https://github.com/earlephilhower/ESP8266Audio
#include "AudioOutputI2SNoDAC.h" // https://github.com/earlephilhower/ESP8266Audio

#include <ESP8266HTTPClient.h> //Содержится в пакете
WiFiClient wclient;
// To run, set your ESP8266 build to 160MHz, update the SSID info, and upload.

// Randomly picked URL
// http://kpradio.hostingradio.ru:8000/
// http://radio.horoshee.fm:8000/mp3
// http://kpradio.hostingradio.ru:8000/russia.radiokp128.mp3
// const char *URL = "http://ic6.101.ru:8000/p933259";
// const char *URL = "http://icecast.russkoeradio.cdnvideo.ru:8000/rr_m.mp3";
// const char *URL = "http://music.myradio.ua/rep128.mp3";
// const char *URL = "http://jazz.streamr.ru/jazz-128.mp3";
// const char *URL = "http://87.110.219.34:8000/swhmp3";
// const char *URL = "http://87.110.219.34:8000/plusmp3";
// const char *URL = "http://91.90.255.111:80/MixFM_96"; //GOOD
// const char *URL = "https://nashe1.hostingradio.ru:18000/nashe20-64.mp3";
String URLs = "http://jazz.streamr.ru/jazz-64.mp3";
AudioGeneratorMP3 *mp3;
AudioFileSourceICYStream *file;
AudioFileSourceBuffer *buff;
AudioOutputI2SNoDAC *out;

void setup() {
  system_update_cpu_freq(SYS_CPU_160MHZ);
  Serial.begin(115200);
  WiFiManager wifiManager;
  wifiManager.autoConnect("radio");
  Serial.println("connected...yeey :)");
  String doneURL =
      getURL("http://backup.privet.lv/radio/?mac=" + WiFi.macAddress());
  Serial.println(WiFi.macAddress());
  if (doneURL == "") {
    doneURL = getURL("http://backup.privet.lv/radio/?mac=" + WiFi.macAddress());
  }
  if (doneURL != "")
    URLs = doneURL;
  Serial.println(URLs);
  AUDIO_init();
}

void loop() { handleAudio(); }

// ------------- Запрос на удаленный URL
// -----------------------------------------
String getURL(String urls) {
  String answer;
  HTTPClient http;
  http.begin(urls); // HTTP
  int httpCode = http.GET();
  if (httpCode == HTTP_CODE_OK) { // если сервер вернул данные
    answer = http.getString(); // Данные здесь
  }
  http.end();
  return answer;
}

// Radio.ino

// Called when a metadata event occurs (i.e. an ID3 tag, an ICY block, etc.
void MDCallback(void *cbData, const char *type, bool isUnicode,
                Stream *stream) {
  const char *ptr = reinterpret_cast<const char *>(cbData);
  (void)isUnicode; // Punt this ball for now
  Serial.printf("METADATA(%s) '%s' = '%s'\n", ptr, type,
                stream->readString().c_str());
  Serial.flush();
}

// Called when there's a warning or error (like a buffer underflow or decode
// hiccup)
void StatusCallback(void *cbData, int code, const char *string) {
  const char *ptr = reinterpret_cast<const char *>(cbData);
  Serial.printf("STATUS(%s) '%d' = '%s'\n", ptr, code, string);
  if (code == 3) {
    Serial.printf("Buffering restart");
    ESP.restart();
  }
  Serial.flush();
}

void AUDIO_init(void) {
  // file = new AudioFileSourceICYStream(URL);
  file = new AudioFileSourceICYStream(URLs.c_str());
  // file->RegisterMetadataCB(MDCallback, (void*)"ICY");
  buff = new AudioFileSourceBuffer(
      file, 1024 * 4); // you can increase default 2048 bufffersize to 4096
                       // (seems better) or 8192
  buff->RegisterStatusCB(StatusCallback, (void *)"buffer");
  out = new AudioOutputI2SNoDAC();
  mp3 = new AudioGeneratorMP3();
  mp3->RegisterStatusCB(StatusCallback, (void *)"mp3");
  mp3->begin(buff, out);
  delay(1000);
}

void handleAudio() {
  // static int lastms = 0;
  if (mp3->isRunning()) {
    // if (millis()-lastms > 1000) {
    //  lastms = millis();
    //  Serial.printf("Running for %d ms...\n", lastms);
    //  Serial.flush();
    // }
    if (!mp3->loop())
      mp3->stop();
  } else {
    Serial.printf("MP3 done\n");
    delay(1000);
  }
}
