/**!
 * @file compass.ino
 * @brief Compass Control Example
 * @details Setting the orientation of the compass needle based on the values obtained from a sensor.
 * @n  Most parameters are related to the screen size (320*240). Please ensure that the custom parameters do not exceed the screen limits.
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @maintainer [qsjhyy](yihuan.huang@dfrobot.com)
 * @maintainer [GDuang](yonglei.ren@dfrobot.com)
 * @version  V2.0
 * @date  2024-03-19
 * @url https://github.com/DFRobot/DFRobot_LcdDisplay
 */
#include "DFRobot_LcdDisplay.h"

#define I2C_COMMUNICATION  // I2C communication. If you want to use UART communication, comment out this line of code. 

#ifdef  I2C_COMMUNICATION
  /**
    * Using the I2C interface.
    */
  DFRobot_Lcd_IIC lcd(&Wire, /*I2CAddr*/ 0x2c);
#else
  /**
    * Using the UART interface.
    */
  #if ((defined ARDUINO_AVR_UNO) || (defined ESP8266) || (defined ARDUINO_BBC_MICROBIT_V2))
    #include <SoftwareSerial.h>
    SoftwareSerial softSerial(/*rx =*/4, /*tx =*/5);
    #define FPSerial softSerial
  #else
    #define FPSerial Serial1
  #endif
  DFRobot_Lcd_UART lcd(FPSerial);
#endif

uint8_t compassId[21];

void testCompass(){
    uint16_t y = 0;
    uint16_t x = 0;
    // Create a compass with a diameter of 64 at point (0,0)
    compassId[0] = lcd.creatCompass(x, y, 64);
    // Change the coordinates of this compass to make it move
    for(uint8_t i = 0; i < 20; i++){
      lcd.updateCompass(compassId[0], x, y, 64);
      if((i+1)%5 == 0){
        y += 64;
        x = 0;
      }else{
        x += 64;
      }
      delay(200);
    }
    // Delete this compass
    lcd.deleteCompass(compassId[0]);
    delay(200);
    x = 0;
    y = 0;
    // Create a compass at different coordinate points and make it appear on the full screen
    for(uint8_t i = 0; i < 20; i++){
      compassId[i] = lcd.creatCompass(x, y, 64);
      if((i+1)%5 == 0){
        y += 64;
        x = 0;
      }else{
        x += 64;
      }
      delay(200);
    }
    delay(1000);
	  // Remove the compass one by one
    for(uint8_t i = 0; i < 20; i++){
      lcd.deleteCompass(compassId[i]);
      delay(200);
    }
    // Create a compass with a diameter of 64 at point (0,0)
    compassId[0] = lcd.creatCompass(0, 0, 30);
    // Change the compass so that it scales
    for(uint8_t i = 0 ; i<8; i++){
        lcd.updateCompass(compassId[0], 0, 0, 30*(i+1));
        delay(100);
    }
    for(uint8_t i = 0; i < 36; i++){
        lcd.setCompassScale(compassId[0],i*100);
        delay(50);
    }
    lcd.deleteCompass(compassId[0]);
    delay(2000);
}

void setup(void)
{
  #ifndef  I2C_COMMUNICATION
    #if (defined ESP32)
      FPSerial.begin(9600, SERIAL_8N1, /*rx =*/D2, /*tx =*/D3);
    #else
      FPSerial.begin(9600);
    #endif
  #endif

  Serial.begin(115200);

  //Initializing 
  lcd.begin();

  lcd.cleanScreen();
  delay(200);
  lcd.setBackgroundColor(WHITE);

  testCompass();
}


void loop(void)
{
	testCompass();
  delay(2000);
}