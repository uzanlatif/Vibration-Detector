#ifdef ESP32
  #include <WiFi.h>
#else
  #include <ESP8266WiFi.h>
#endif

#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

const char* ssid = "Hehe";
const char* password = "fauzan123";

const int sensor = 14;
const int led = 13;
const int buzzer = 12;

String server = "http://maker.ifttt.com";
String eventName = "Sensor_Gempa";
String IFTTT_Key = "bVv1vg2BFERrdGBDKh6nK-";
String IFTTTUrl="http://maker.ifttt.com/trigger/Sensor_Gempa/with/key/bVv1vg2BFERrdGBDKh6nK-";

int value1;
int value2;
int value3;

void setup(){
  WiFi.begin(ssid, password);
  Serial.begin(9600);
  
  pinMode(sensor,INPUT);
  pinMode(led, OUTPUT);
  pinMode(buzzer,OUTPUT);
  
}

void loop(){
  digitalWrite(led,LOW);
  int vib = digitalRead(sensor);
  if(vib == LOW){
  alarm();
  sendDataToSheet();
  Notifikasi();
  }
}

void alarm(){
  if (WiFi.status() == WL_CONNECTED) {
    digitalWrite(led,HIGH);
    digitalWrite(buzzer,HIGH);
    delay(1000);
    digitalWrite(led,LOW);
    digitalWrite(buzzer,LOW);
  }
}

void sendDataToSheet(void)
{
  String url = server + "/trigger/" + eventName + "/with/key/" + IFTTT_Key + "?value1=" + String((int)value1) + "&value2="+String((int)value2) +"&value3=" + String((int)value3);  
  Serial.println(url);
  //Start to send data to IFTTT
  HTTPClient http;
  Serial.print("[HTTP] begin...\n");
  http.begin(url); //HTTP

  Serial.print("[HTTP] GET...\n");
  // start connection and send HTTP header
  int httpCode = http.GET();
  // httpCode will be negative on error
  if(httpCode > 0) {
    // HTTP header has been send and Server response header has been handled
    Serial.printf("[HTTP] GET... code: %d\n", httpCode);
    // file found at server
    if(httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println(payload);
    }
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
  http.end();
}

void Notifikasi(){
  String url = server + "/trigger/" + "Notif" + "/with/key/" + IFTTT_Key + "?value1=" + String((int)value1) + "&value2="+String((int)value2) +"&value3=" + String((int)value3);  
  Serial.println(url);
  //Start to send data to IFTTT
  HTTPClient http;
  Serial.print("[HTTP] begin...\n");
  http.begin(url); //HTTP

  Serial.print("[HTTP] GET...\n");
  // start connection and send HTTP header
  int httpCode = http.GET();
  // httpCode will be negative on error
  if(httpCode > 0) {
    // HTTP header has been send and Server response header has been handled
    Serial.printf("[HTTP] GET... code: %d\n", httpCode);
    // file found at server
    if(httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println(payload);
    }
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
  http.end();
}
