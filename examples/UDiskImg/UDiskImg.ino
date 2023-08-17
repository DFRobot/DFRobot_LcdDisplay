
/**!
 * @file  UDiskImg.ino
 * @brief  Displays a picture of a USB flash drive
 * @details  Display different images with different pathnames (maximum screen size 320*240);
 * @n  Can display: 16 or 24 bit (color depth) bmp picture; Small size (under 70*70)png image
 * @n  Most parameters are related to the screen size (320*240). Please ensure that the custom parameters do not exceed the screen limits.
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license  The MIT License (MIT)
 * @author  [qsjhyy](yihuan.huang@dfrobot.com)
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

DFRobot_LcdDisplay::sControlinf_t *img1, *img2;

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
  // Resetting the screen.
  lcd.reset();
  delay(3000);
  // Display USB flash drive pictures. You can display 16-bit or 24-bit (color depth) bmp pictures (maximum screen size 320*240) and small-size png pictures (below 70*70)
  // The last parameter is the zoom index range of (128~512),128- zoom out by one,512- zoom in by one
  img1 = lcd.drawDiskImg(/*x=*/0, /*y=*/0, /*File path name (String)*/"/sea.bmp", /* Exponential Scale*/256);
  delay(1000);
  lcd.lvglDelete(img1);
  img2 = lcd.drawDiskImg(0, 0, "/plants.png", 256);
  delay(1000);
  img1 = lcd.drawDiskImg(0, 0, "/cat.bmp", 256);
}

void loop(void)
{
}
