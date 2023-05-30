
/**!
 * @file compass.ino
 * @brief Compass Control Example
 * @details Setting the orientation of the compass needle based on the values obtained from a sensor.
 * @n  Most parameters are related to the screen size (320*240). Please ensure that the custom parameters do not exceed the screen limits.
 * @n  After scaling the dial widget, the display quality may degrade. Please use appropriate parameters
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @maintainer [qsjhyy](yihuan.huang@dfrobot.com)
 * @version  V1.0
 * @date  2023-05-29
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

DFRobot_LcdDisplay::sControlinf_t *compss;

/**
 * User-selectable macro definition color
 * BLACK_RGB565 BLUE_RGB565 RED_RGB565 GREEN_RGB565 CYAN_RGB565 MAGENTA_RGB565
 * YELLOW_RGB565 WHITE_RGB565 NAVY_RGB565 DARKGREEN_RGB565 DARKCYAN_RGB565 MAROON_RGB565
 * PURPLE_RGB565 OLIVE_RGB565 LIGHTGREY_RGB565 DARKGREY_RGB565 ORANGE_RGB565
 * GREENYELLOW_RGB565 DCYAN_RGB565
 */
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

  lcd.begin();
  //Initializing 
  lcd.lvglInit(/*bg_color=*/GREEN_RGB565);
  //Creating a compass control.
  compss = lcd.creatCompass(/*x=*/16,/*y=*/0,/*width=*/128,/*height*/128);
}

void loop(void)
{
  //Setting the angle of the compass needle.
  lcd.setCompassScale(compss,/*Angle*/90);
  delay(1000);
  lcd.setCompassScale(compss,120);
  delay(1000);
  lcd.setCompassScale(compss,150);
  delay(1000);
  lcd.setCompassScale(compss,180);
  delay(1000);
  lcd.setCompassScale(compss,210);
  delay(1000);
  lcd.setCompassScale(compss,240);
  delay(1000);
  lcd.setCompassScale(compss,270);
  delay(1000);
  lcd.setCompassScale(compss,300);
  delay(1000);
}