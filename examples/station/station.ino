/**!
 * @file station.ino
 * @brief Comprehensive example of weather station
 * @details Can display the weather, date, time, temperature, humidity, wind speed
 * @n  Most parameters are related to the screen size (320*240). Please ensure that the custom parameters do not exceed the screen limits.
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @maintainer [qsjhyy](yihuan.huang@dfrobot.com)
 * @version  V1.0
 * @date  2023-05-29
 * @url https://github.com/DFRobot/DFRobot_LcdDisplay
 */
#include "DFRobot_LcdDisplay.h"
#include <MsTimer2.h>

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

DFRobot_LcdDisplay::sControlinf_t * bar1, * bar2, * bar3;

uint8_t hour = 9, Minute = 8, second = 56;

void flash()   //Interrupt handler that handles changes in time
{
  second++;
  if (second > 59) {
    second = 0;
    Minute++;
  }
  if (Minute > 59) {
    Minute = 0;
    hour++;
  }
}

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
  lcd.lvglInit(YELLOW_RGB565);

  //Create the icon, remember to display the icon first, icon on the "dot and line character", there will be interference coverage
  lcd.drawIcon(25, 100, DFRobot_LcdDisplay::eIconRainy, 200);
  lcd.drawIcon(140, 30, DFRobot_LcdDisplay::eIconThermometer, 200);
  lcd.drawIcon(135, 90, DFRobot_LcdDisplay::eIconRaindrops, 200);
  lcd.drawIcon(115, 155, DFRobot_LcdDisplay::eIconWind, 200);

  //Show the current time
  lcd.drawLcdTime(10, 10, hour, Minute, second, 0, ORANGE_RGB565, WHITE_RGB565);
  //Show the current date
  lcd.drawLcdDate(10, 50, 3, 29, 3, 1, LIGHTGREY_RGB565, WHITE_RGB565);
  //Show current weather
  lcd.drawString(38, 170, "大雨", 0, RED_RGB565, DARKGREEN_RGB565);

  //Create a progress bar for the temperature display
  bar1 = lcd.creatBar(180, 60, 80, 20, RED_RGB565);
  //Create a progress bar for displaying humidity
  bar2 = lcd.creatBar(180, 120, 80, 20, BLUE_RGB565);
  //Create a progress bar for the wind speed display
  bar3 = lcd.creatBar(180, 180, 80, 20, GREEN_RGB565);

  MsTimer2::set(1000, flash);        // Interrupt setting function, enter interrupt every 1000ms
  MsTimer2::start();                // start counting
}

void loop(void)
{
  //Show the current time
  lcd.drawLcdTime(10, 10, hour, Minute, second, 0, ORANGE_RGB565, WHITE_RGB565);
  lcd.setBar(bar1, String(25) + " °C");
  lcd.setBar(bar2, String(80) + " %");
  lcd.setBar(bar3, String(10) + " m/s");
  delay(300);

  lcd.setBar(bar1, String(28) + " °C");
  lcd.setBar(bar2, String(60) + " %");
  lcd.setBar(bar3, String(15) + " m/s");
  delay(300);

  lcd.setBar(bar1, String(30) + " °C");
  lcd.setBar(bar2, String(50) + " %");
  lcd.setBar(bar3, String(20) + " m/s");
  delay(400);
}
