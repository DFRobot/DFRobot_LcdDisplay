/**!
 * @file station.ino
 * @brief Comprehensive example of weather station
 * @details Can display the weather, date, time, temperature, humidity, wind speed
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

uint8_t bar1, bar2, bar3, bar4,lcdTimeId,labelId1,labelId2,labelId3,labelId4;

uint8_t hour = 9, Minute = 8, second = 56;
uint8_t lastSecond = 0;
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

void setLux(uint8_t value){
  lcd.setBarValue(bar1, value);
  lcd.updateString(labelId1, 260, 22, String(value)+"lux", 0, ORANGE);
}

void setTemp(uint8_t value){
  lcd.setBarValue(bar2, value);
  lcd.updateString(labelId2, 260, 62, String(value)+"°C", 0, RED);
}

void setHum(uint8_t value){
  lcd.setBarValue(bar3, value);
  lcd.updateString(labelId3, 260, 102, String(value)+"%", 0, BLUE);
}

void setWind(uint8_t value){
  lcd.setBarValue(bar4, value);
  lcd.updateString(labelId4, 260, 142, String(value)+"m/s", 0, GREEN);
}

/**
 * User-selectable macro definition color
 * BLACK BLUE RED GREEN CYAN MAGENTA
 * YELLOW WHITE NAVY DARKGREEN DARKCYAN MAROON
 * PURPLE OLIVE LIGHTGREY DARKGREY ORANGE
 * GREENYELLOW 
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
  lcd.setBackgroundColor(BLACK);
  lcd.cleanScreen();
  delay(500);

  //Create the icon, remember to display the icon first, icon on the "dot and line character", there will be interference coverage 
  lcd.drawIcon(20, 0, lcd.eIconRainbow1, 350);
  
  lcd.drawIcon(130, 40, lcd.eIconThermometer, 120);
  lcd.drawIcon(125, 80, lcd.eIconRaindrops, 120);

  lcd.drawIcon(0, 176, lcd.eIconPottedPlantFlower, 256);
  lcd.drawIcon(53, 176, lcd.eIconCactus3, 256);
  lcd.drawIcon(106, 176, lcd.eIconGrass, 256);
  lcd.drawIcon(159, 176, lcd.eIconGrass1, 256);
  lcd.drawIcon(212, 176, lcd.eIconCactus1, 256);
  lcd.drawIcon(265, 176, lcd.eIconCactus2, 256);

  //Show the current time
  lcdTimeId = lcd.drawLcdTime(10, 64, hour, Minute, second, 1, LIGHTGREY);
  //Show the current date
  lcd.drawLcdDate(10, 95, 3, 29, 3, 0, LIGHTGREY);

  //Create a progress bar for the temperature display
  bar1 = lcd.creatBar(170, 22, 80, 15, ORANGE);
  labelId1 = lcd.drawString( 260, 22, "0lux", 0, ORANGE);
  //Create a progress bar for displaying humidity
  bar2 = lcd.creatBar(170, 62, 80, 15, RED);
  labelId2 = lcd.drawString( 260, 62, "0°C", 0, RED);
  //Create a progress bar for the wind speed display
  bar3 = lcd.creatBar(170, 102, 80, 15, BLUE);
  labelId3 = lcd.drawString( 260, 102, "0%", 0, BLUE);

  bar4 = lcd.creatBar(170, 142, 80, 15, GREEN);
  labelId4 = lcd.drawString( 260, 142, "0m/s", 0, GREEN);

  // Sets the value of the progress bar 
  setLux(rand()%100);
  setTemp(rand()%100);
  setHum(rand()%100);
  setWind(rand()%100);

  lcd.drawGif(0, 80, lcd.eGifRain, 160);     // Rain icon
  lcd.drawGif(115, 0, lcd.eGifSun, 120);    // Sun icon
  lcd.drawGif(115, 120, lcd.eGifWind, 120);  // Wind icon

  MsTimer2::set(1000, flash);        // Interrupt setting function, enter interrupt every 1000ms
  MsTimer2::start();                 // start counting  
}

void loop(void)
{
  //Show the current time

  if(lastSecond != second){
    lastSecond = second;
    lcd.updateLcdTime(lcdTimeId, 10, 64, hour, Minute, lastSecond, 1, LIGHTGREY);
  }
  delay(100);
}
