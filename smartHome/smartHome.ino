
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Arduino_JSON.h>

#define lamp1  D5
#define button1  D1


const char* ssid = "WE_87B9D0";
const char* password = "jae05161";

//Your Domain name with URL path or IP address with path
const char*  serverName = "http://192.168.1.4:8000/Lamp1";

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 10000;

String lampStatus;
int lampStatusArr[1];


int button_curState = 0;
int button_lastState = 0;

bool lamp1cur_state = false;

void setup() {
  pinMode(lamp1,OUTPUT);
  pinMode(button1,INPUT_PULLUP);

  Serial.begin(115200); 

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");

}

void loop() {
  
  button_curState = digitalRead(button1);
  if(button_curState != button_lastState){
    if(lamp1cur_state){
      digitalWrite(lamp1,LOW);
      lamp1cur_state = false;
    }else{
      digitalWrite(lamp1,HIGH);
      lamp1cur_state = true;
    }
    button_lastState = button_curState;
  }

  // Send an HTTP POST request depending on timerDelay
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      
     lampStatus =  httpGETRequest(serverName);
     Serial.println(lampStatus);
     JSONVar myObject = JSON.parse(lampStatus);
     // JSON.typeof(jsonVar) can be used to get the type of the var
      if (JSON.typeof(myObject) == "undefined") {
        Serial.println("Parsing input failed!");
        return;
      }
      Serial.print("JSON object = ");
      Serial.println(myObject);
    
      // myObject.keys() can be used to get an array of all the keys in the object
      JSONVar keys = myObject.keys();
    
      for (int i = 0; i < keys.length(); i++) {
        JSONVar value = myObject[keys[i]];
        Serial.print(keys[i]);
        Serial.print(" = ");
        Serial.println(value);
        lampStatusArr[i] = int(value);
      }
      Serial.print("1 = ");
      Serial.println(lampStatusArr[0]);
      if(lampStatusArr[0] == 1){
        Serial.print("the lamp is on");
        digitalWrite(lamp1,HIGH);
        lamp1cur_state = true;
      }else{
        Serial.print("the lamp is off");
        digitalWrite(lamp1,LOW);
        lamp1cur_state = false;
      }
     
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
  
}




//////////////////////////////////


String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
    
  // Your IP address with path or Domain name with URL path 
  http.begin(client, serverName);
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "{}"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}
