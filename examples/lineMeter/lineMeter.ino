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
uint32_t bgColor = GREEN;
uint32_t pointerColor = RED;
uint32_t generateRandomColor() {
    uint8_t r = rand() % 256;
    uint8_t g = rand() % 256;
    uint8_t b = rand() % 256;
    return (r << 16) | (g << 8) | b;
}

uint8_t lineMeterId[13];
void testLineMeter(){
    uint16_t x = 0;
    uint16_t y = 0;
    // Creates a linear dials at point (0,0)
    lineMeterId[0] = lcd.creatLineMeter(0, 0, 120, 0, 100, pointerColor, bgColor);
    // Set the value of the linear gauge to 40
    lcd.setMeterValue(lineMeterId[0],40);
    // Change the coordinates of the dials so that it moves
    for(uint8_t i = 0; i < 7; i++){
      lcd.updateLineMeter(lineMeterId[0], i*32, 0, 120, 0, 100, pointerColor, bgColor);
      delay(100);
    }
    // Delete this dials
    lcd.deleteLineMeter(lineMeterId[0]);
    delay(100);
    // Create multiple dials, use a random pointer color, a random background color, and set the dials value to random so that it covers the entire screen
    for(uint8_t i = 0; i < 12; i++){
      bgColor = generateRandomColor();
      pointerColor = generateRandomColor();
      lineMeterId[i] = lcd.creatLineMeter(x, y, 80, 0, 60, pointerColor, bgColor);
      lcd.setMeterValue(lineMeterId[i],rand()%60);
      if((i+1)%4 == 0){
          y += 80;
          x = 0;
      }else{
          x += 80;
      } 
      delay(100);
    }
    delay(1000);
    // Remove the linear dial one by one
    for(uint8_t i = 0; i < 12; i++){
      lcd.deleteLineMeter(lineMeterId[i]);
      delay(100);
    } 
    // Create another linear dial
    lineMeterId[0] = lcd.creatLineMeter(0, 0, 120, 0, 100, pointerColor, bgColor);
    // Change the size of this linear dial so that it reaches the scaling phenomenon
    for(uint8_t i = 0; i < 10; i++){
      lcd.updateLineMeter(lineMeterId[0], 0, 0, 120+i*12, 0, 100, pointerColor, bgColor);
      delay(100);
    }
    // Set the pointer value of the dial at random
    for(uint8_t i = 0; i < 10; i++){
      lcd.setMeterValue(lineMeterId[0],rand()%100);
      delay(100);
    }
    // Remove linear dial
    lcd.deleteLineMeter(lineMeterId[0]);
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

  // Initializing 
  lcd.begin();

  lcd.cleanScreen();
  delay(500);
  lcd.setBackgroundColor(WHITE);
}

void loop(void)
{
  // Setting the value of the dial.
  testLineMeter();
  delay(1000);
}