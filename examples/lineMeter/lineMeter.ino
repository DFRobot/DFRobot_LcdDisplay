/**!
 * @file lineMeter.ino
 * @brief Creating a linear gauge control.
 * @details Creating three linear gauge controls and controlling each one to display different values.
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

DFRobot_LcdDisplay::sControlinf_t *lineMeter1, *lineMeter2, *lineMeter3;

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
  lcd.lvglInit(/*Displaying the background color*/CYAN_RGB565);

  //Creating a linear gauge control. 
  lineMeter1 = lcd.creatLineMeter(/*x*/10,/*y*/100,/*width*/120,/*height*/120,/*color*/CYAN_RGB565);
  //Setting the parameters of the linear gauge control.
  lcd.setMeterScale(lineMeter1,/*angle of the scale*/270,/*start of angle*/0,/*end of angle*/100);

  lineMeter2 = lcd.creatLineMeter(100,15,120,120,GREEN_RGB565);
  lcd.setMeterScale(lineMeter2,270,0,100);
  lineMeter3 = lcd.creatLineMeter(195,100,120,120,ORANGE_RGB565);
  lcd.setMeterScale(lineMeter3, 270, 0, 100);

}

void loop(void)
{
  //Setting the value of the gauge.
  lcd.setMeterValue(lineMeter1,40);
  lcd.setMeterValue(lineMeter2,50);
  lcd.setMeterValue(lineMeter3,70);
  delay(3000);

  lcd.setMeterValue(lineMeter1,10);
  lcd.setMeterValue(lineMeter2,40);
  lcd.setMeterValue(lineMeter3,60);
  delay(3000);
}