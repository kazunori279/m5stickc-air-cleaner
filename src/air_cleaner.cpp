/*
    M5StickC air-cleaner

    For M5StickCPlus2 + BME688 + Ozone generator: 
    
    BME688:
    https://shop.m5stack.com/products/env-pro-unit-with-temperature-humidity-pressure-and-gas-sensor-bme688?variant=44022918709505
    
    Usage: 
*/


#include <M5StickCPlus2.h>
#include <MedianFilterLib2.h>
#include <Preferences.h>

#include <Wire.h>
#include <bme68xLibrary.h>
#include <bsec2.h>

#define SERIAL_SPEED (115200)

#define BME_SCL_PIN (33)
#define BME_SDA_PIN (32)

#define BME688_ADDR (0x77)

Bsec2 envSensor;

bsecSensor sensorList[] = {
	BSEC_OUTPUT_IAQ,
	BSEC_OUTPUT_CO2_EQUIVALENT,
	BSEC_OUTPUT_BREATH_VOC_EQUIVALENT,
	BSEC_OUTPUT_RAW_TEMPERATURE,
	BSEC_OUTPUT_RAW_PRESSURE,
	BSEC_OUTPUT_RAW_HUMIDITY,
	BSEC_OUTPUT_RAW_GAS,
	BSEC_OUTPUT_STABILIZATION_STATUS,
	BSEC_OUTPUT_RUN_IN_STATUS
};

// update display
void updateDisp() {

}

// Print BME status
void checkBsecStatus(Bsec2 bsec)
{
  if (bsec.status < BSEC_OK)
  {
    Serial.println("BSEC error code : " + String(bsec.status));
  }
  else if (bsec.status > BSEC_OK)
  {
    Serial.println("BSEC warning code : " + String(bsec.status));
  }

  if (bsec.sensor.status < BME68X_OK)
  {
    Serial.println("BME68X error code : " + String(bsec.sensor.status));
  }
  else if (bsec.sensor.status > BME68X_OK)
  {
    Serial.println("BME68X warning code : " + String(bsec.sensor.status));
  }
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
}

void setup() { 

  // init M5
  M5.begin();
	Serial.begin(SERIAL_SPEED);
  Serial.println("Init start."); 

  // init BME
	Wire.begin(BME_SDA_PIN, BME_SCL_PIN);
  if (!envSensor.begin(BME68X_I2C_ADDR_HIGH, Wire)) {
      checkBsecStatus(envSensor);
  }  

  // check BME status
  Serial.println("BSEC library version " + String(envSensor.version.major) +
                  "." + String(envSensor.version.minor) + "." +
                  String(envSensor.version.major_bugfix) + "." +
                  String(envSensor.version.minor_bugfix));

  // init display
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

