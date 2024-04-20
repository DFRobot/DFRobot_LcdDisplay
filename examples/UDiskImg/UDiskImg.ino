
/**!
 * @file  UDiskImg.ino
 * @brief  Displays a picture of a USB flash drive
 * @details  Display different images with different pathnames (maximum screen size 320*240);
 * @n  Can display: 16 or 24 bit (color depth) bmp picture; Small size (under 70*70)png image
 * @n  Most parameters are related to the screen size (320*240). Please ensure that the custom parameters do not exceed the screen limits.
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license  The MIT License (MIT)
 * @author  [qsjhyy](yihuan.huang@dfrobot.com)
 * @maintainer [GDuang](yonglei.ren@dfrobot.com)
 * @version  V2.0
 * @date  2024-03-19
 * @url https://github.com/DFRobot/DFRobot_LcdDisplay
 */
#include "DFRobot_LcdDisplay.h"

// #define I2C_COMMUNICATION  // I2C communication. If you want to use UART communication, comment out this line of code.

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

uint8_t iconId[5]; // An array for storing icon ids
void testIcon(){
    // Create a few ICONS at (0,0), which are file names, so the file will be read from an external USB flash drive
    // If there is no corresponding path on the USB flash drive, a white screen will be displayed
    iconId[0] = lcd.drawIcon(0, 0, "cat.png", 256);
    delay(200);
    iconId[1] = lcd.drawIcon(0, 0, "fish.png", 256);
    delay(200);
    iconId[2] = lcd.drawIcon(0, 0, "shy.png", 256);
    delay(200);
    iconId[3] = lcd.drawIcon(0, 0, "smile.png", 256);
    delay(200);
    iconId[4] = lcd.drawIcon(0, 0, "angry.png", 256);
    delay(200);
    // Move the ICONS one by one
    for(uint8_t i = 0; i < 5; i++){
        lcd.updateIcon(iconId[4], i*64, 0, "angry.png", 256);
    }
    delay(200);
    for(uint8_t i = 0 ; i < 4; i++){
        lcd.updateIcon(iconId[3], i*64, 0, "smile.png", 256);
    }
    delay(200);
    for(uint8_t i = 0; i < 3; i++){
        lcd.updateIcon(iconId[2], i*64, 0, "shy.png", 256);
    }
    delay(200);
    // Delete these ICONS
    for(uint8_t i = 0; i < 5; i++){
        lcd.deleteIcon(iconId[i]);
        delay(100);
    }

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
    lcd.setBackgroundColor(WHITE);
}

void loop(void){
    testIcon();
    delay(1000);
}
