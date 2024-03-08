#include <Arduino.h>
#ifdef ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include "AudioFileSourceICYStream.h"
#include "AudioFileSourceBuffer.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2SNoDAC.h"

#include <EEPROM.h>

const char* ssid = "WiF";
const char* password = "akash@wifi";

// URL'S for audio streams
const char *URL[] = {
  "http://stream-156.zeno.fm/s9c3zek68a0uv?zs=2n3_bd2iRrmIN5-HuvzoXA", // Old Songs
  "http://radio.mohdrafi.com/rafi.mp3", // Md. Rafi Songs
  "http://stream-156.zeno.fm/s9c3zek68a0uv?zs=2n3_bd2iRrmIN5-HuvzoXA", // Kishore Kumar Songs 
  "http://stream-141.zeno.fm/rqqps6cbe3quv?zs=6k4kfGQRQA6poc6xbmaNjA&rj-ttl=5&rj-tok=AAABccQyYG8AGJ3KW_903AafBw", // Bollywood Song
};

AudioFileSourceICYStream *file;
AudioFileSourceBuffer *buff;
AudioOutputI2SNoDAC *out;
AudioGeneratorMP3 *mp3;

void bufffile() {
  file = new AudioFileSourceICYStream(URL[0]);  // Adjust the index to select the desired audio stream URL
  buff = new AudioFileSourceBuffer(file, 8192);
  out = new AudioOutputI2SNoDAC();
  mp3 = new AudioGeneratorMP3();
  mp3->begin(buff, out);
}

void RunStream() {
  if (mp3->isRunning()) {
    mp3->loop();
    Serial.println("Playing..");
  }
   Serial.println("Stoped..");
  
}

void setup() {
  Serial.begin(115200);
  Serial.println("Started");
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  digitalWrite(D3, LOW);
  digitalWrite(D4, HIGH);
  digitalWrite(D4, LOW);

  WiFi.disconnect();
  WiFi.softAPdisconnect(true);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Connecting to WiFi.....");
    delay(1000);
  }

  bufffile();
}

void loop() {
  RunStream();
}
