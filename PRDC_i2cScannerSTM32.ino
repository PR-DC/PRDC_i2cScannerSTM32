/**
 * PRDC_i2cScannerSTM32.ino - I2C Scanner for Arduino_Core_STM32  
 * Author: Milos Petrasinovic <mpetrasinovic@pr-dc.com>
 * PR-DC, Republic of Serbia
 * info@pr-dc.com
 * 
 * --------------------
 * Copyright (C) 2021 PR-DC <info@pr-dc.com>
 *
 * This file is part of PRDC_i2cScannerSTM32.
 *
 * PRDC_i2cScannerSTM32 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as 
 * published by the Free Software Foundation, either version 3 of the 
 * License, or (at your option) any later version.
 * 
 * PRDC_i2cScannerSTM32 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with PRDC_i2cScannerSTM32.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
 
// Library
// --------------------
#include <Wire.h>

// Define I2C pins
// --------------------
#define I2C_SDA PB7 // I2C SDA pin
#define I2C_SCL PB6 // I2C SCL pin

// I2C Instance
// --------------------
TwoWire I2C_COM(I2C_SDA, I2C_SCL); // I2C instance

// setup function
// --------------------
void setup() {
  // Begin comunication with custom I2C istance
  I2C_COM.begin();

  // Begin serial communication
  Serial.begin(115200);
  while(!Serial);
  Serial.println("I2C Scanner for STM32 based boards");
}


// loop function
// --------------------
void loop(){
  uint8_t error, address;
  uint8_t num_devices;

  Serial.println("Scanning...");

  num_devices = 0;
  for(address = 1; address < 127; address++) {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    I2C_COM.beginTransmission(address);
    error = I2C_COM.endTransmission();

    if(error == 0) {
      Serial.print("I2C device found at address 0x");
      if(address < 16) {
        Serial.print("0");
      }
      Serial.print(address, HEX);
      Serial.println("!");
      num_devices++;
    } else if(error == 4) {
      Serial.print("Unknown error at address 0x");
      if(address < 16)  {
        Serial.print("0");
      }
      Serial.println(address, HEX);
    }    
  }
  
  Serial.println("Scanning done...");
  if(num_devices == 0) {
    Serial.println("No I2C devices found");
  }
  Serial.println();
  
  delay(1000); // wait one second before next scan
}
