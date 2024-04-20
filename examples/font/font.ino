/**!
 * @file font.ino
 * @brief Text Display Example
 * @details Now supports Chinese and ASCII characters, Korean, Japanese, Greek, and Cyrillic.
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

/**
 * User-selectable macro definition color
 * BLACK BLUE RED GREEN CYAN MAGENTA
 * YELLOW WHITE NAVY DARKGREEN DARKCYAN MAROON
 * PURPLE OLIVE LIGHTGREY DARKGREY ORANGE
 * GREENYELLOW 
 */
uint8_t labelId = 0;
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
  lcd.cleanScreen();
  delay(500);
  //set background color
  lcd.setBackgroundColor(/*Displaying the background color*/WHITE);
 
  //Drawing text
  //The fourth parameter is the font size, where 0 represents a font height of 24 pixels and 1 represents a font height of 12 pixels.
  //This parameter is only applicable to eChinese and eAscii text.
  labelId = lcd.drawString( 10, 10, "您好，世界hello,World012\n안녕하세요こんにちは\nПривет мирΓεια σου κόσμε", 0, RED);
  labelId = lcd.drawString( 10, 100, "您好，世界hello,World012\n안녕하세요こんにちは\nПривет мирΓεια σου κόσμε", 1, RED);
  
}

void loop(void)
{
  delay(3000);
}