// Blynk
#define BLYNK_PRINT Serial

// Blynk 
#define BLYNK_TEMPLATE_ID "TMPL65vMc04Gu"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "KzrM2__mUzxuqVzEINeyu1xwlHVfu4GQ"


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// WiFi 
char ssid[] = "Your SSID OR NAME WI-FI"; 
char pass[] = "Your PASSWORD";


// Soil moisture sensor
#define relay_PIN 33 //GPIO33 -> PIN for Relay water pump
#define soil_PIN 32  //GPIO32 -> PIN for Sensor


// Light sensor
#include <BH1750FVI.h>
BH1750FVI LightSensor(BH1750FVI::k_DevModeContLowRes);


// Val
int val;
float auto_soil ;
uint16_t lux ;


void setup()
{
 
  //Input and Output
  pinMode(soil_PIN,INPUT);
  pinMode(relay_PIN, OUTPUT);

  // Debug console
  Serial.begin(9600);

  LightSensor.begin();

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}


// Adjust the moisture value for the water pump to work
BLYNK_WRITE(V0){
    auto_soil = param.asInt(); 
}


void loop()
{
  Blynk.run();
  
  // Read soil moisture sensor
  val = analogRead(soil_PIN);
  
  // S_Analog to Percent
  float LevelVal = (val * (100.0 / 4095.0))-100; 
  float LevelVal1 = LevelVal*(-1);

  Serial.print("Soil moisture sensor value = ");  
  Serial.println(LevelVal1); 

  Blynk.virtualWrite(V1,(LevelVal1)); 
  
  // S_Water pump
    if(LevelVal1 < auto_soil ){
      digitalWrite(relay_PIN, LOW); // Working
      }
    else{
      digitalWrite(relay_PIN, HIGH); // Not working
      }


  // Light sensor
  lux = LightSensor.GetLightIntensity();
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lux");
  Blynk.virtualWrite(V2,(lux));


  delay(200);

}
