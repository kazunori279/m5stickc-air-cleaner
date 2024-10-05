/*
    M5StickC air-cleaner

    For M5StickC + BME688 + Ozone generator: 
    
    BME688:
    https://shop.m5stack.com/products/env-pro-unit-with-temperature-humidity-pressure-and-gas-sensor-bme688?variant=44022918709505
    
    Usage: 
*/


#include <M5StickC.h>
#include <MedianFilterLib2.h>
#include <Preferences.h>

#include <Wire.h>
#include <bme68xLibrary.h>
#include <bsec2.h>


void setup() { 
  
    // init display
    M5.begin();
    M5.Lcd.setRotation(3);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setTextDatum(MC_DATUM);


    // init pins
}


// main loop
unsigned long lastCheckTime = 0;

void loop() { 

  // For every second, check watering status and update UI
  if (millis() > lastCheckTime + 1000) {
    lastCheckTime =  millis();
    updateDisp();
  }  

  // UI events
  processUIEvents();
  delay(100);
}


// UI events
void processUIEvents() {
  
  // BtnA: start/stop watering
  M5.update();
  if(M5.BtnA.wasPressed()) {

  }

  // BtnB or Axp button: change watering threshold
  if (M5.BtnB.wasPressed()) {

    updateDisp();
  }
  if (M5.Axp.GetBtnPress() == 2) {

    updateDisp();
  }  
}


// update display
void updateDisp() {

}
