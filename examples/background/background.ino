/**!
 * @file chart.ino
 * @brief Creating a chart
 * @details Creating a chart,And being able to add data to the chart to draw a bar chart/line chart.
 * @n  Most parameters are related to the screen size (320*240). Please ensure that the custom parameters do not exceed the screen limits.
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [GDuang](yonglei.ren@dfrobot.com)
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

// Switch background color
void testBackgroundColor(){
    lcd.setBackgroundColor(RED);
    delay(1000);
    lcd.setBackgroundColor(GREEN);
    delay(1000);
    lcd.setBackgroundColor(BLUE);
    delay(1000);
    lcd.setBackgroundColor(WHITE);
    delay(1000);
}

// Switch background image
void testBackgroundImg(){
    // Internal storage of pictures
    lcd.setBackgroundImg(0,"bgDream.png");
    delay(1000);
    // Usb flash drive to store pictures
    lcd.setBackgroundImg(1,"fish.png");
    delay(1000);
    // Usb flash drive to store pictures
    lcd.setBackgroundImg(1,"cat.png");
    delay(1000);
    // Internal storage of pictures
    lcd.setBackgroundImg(0,"bgScenery.png");
    delay(1000);
    // Internal storage of pictures
    lcd.setBackgroundImg(0,"bgCity.png");
    delay(1000);
    // Internal storage of pictures
    lcd.setBackgroundImg(0,"bgTechnology.png");
    delay(1000);
    // Internal storage of pictures
    lcd.setBackgroundImg(0,"bgScience.png");
    delay(1000);
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
  
    lcd.begin();
    lcd.cleanScreen();
    delay(500);
    lcd.drawString( 10, 10, "您好，世界hello,World012\n안녕하세요こんにちは\nПривет мирΓεια σου κόσμε", 0, 0xFFFF00);
}

void loop(void)
{
    testBackgroundColor();
    testBackgroundImg();
}