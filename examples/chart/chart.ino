/**!
 * @file chart.ino
 * @brief Creating a chart
 * @details Creating a chart,And being able to add data to the chart to draw a bar chart/line chart.
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

DFRobot_LcdDisplay::sControlinf_t* chart;

uint8_t id1 = 0, id2 = 0;

uint16_t point1[5] = { 10,90,30,10,90 };
uint16_t point2[5] = { 90,30,80,10,100 };

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
  lcd.lvglInit(GREEN_RGB565);
  /*The actual value range of the y-axis is fixed at 0-100. If you want to display other scales, you can map them proportionally.
    For example, using the label "10\n8\n6\n4\n2\n0":
    - For input { 10,90,30,10,90 }, the displayed values would be { 1,9,3,1,9 }.
    Chart styles: 1. Line chart 2. Line chart with shading 3. Bar chart*/
  chart = lcd.creatChart(/*X-axis tick labels*/"Jan\nFeb\nMar\nApr\nMay", /*Y-axis tick labels*/"100\n80\n60\n40\n20\n0", /*Chart style:1-3*/3);

  //Allocate and add a data series to the chart
  id1 = lcd.creatChartSerie(chart, /*color*/RED_RGB565);
  id2 = lcd.creatChartSerie(chart, BLUE_RGB565);

  //Set the value of points from an array
  lcd.addChart(chart, id1, /*Array of values corresponding to each point*/point1, /*Number of points forming the line*/5);
  lcd.addChart(chart, id2, point2, 5);
}

void loop(void)
{
  delay(3000);
}