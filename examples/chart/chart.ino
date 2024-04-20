/**!
 * @file chart.ino
 * @brief Creating a chart
 * @details Creating a chart,And being able to add data to the chart to draw a bar chart/line chart.
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

//#define I2C_COMMUNICATION  // I2C communication. If you want to use UART communication, comment out this line of code.

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

uint8_t chartId1 = 0;
uint8_t chartId2 = 0;
uint8_t chartId3 = 0;
uint8_t id1_1 = 0, id1_2 = 0, id2_1 = 0, id2_2 = 0, id3_1 = 0, id3_2 = 0;

uint16_t point1[5] = { 10,90,30,0,90 };
uint16_t point2[5] = { 90,30,80,10,100 };

/**
 * User-selectable macro definition color
 * BLACK BLUE RED GREEN CYAN MAGENTA
 * YELLOW WHITE NAVY DARKGREEN DARKCYAN MAROON
 * PURPLE OLIVE LIGHTGREY DARKGREY ORANGE
 * GREENYELLOW 
 */
void testChart(){
    // Create a chart and set the background color to white and the mode to Line chart mode
    chartId1 = lcd.creatChart(/*X-axis tick labels*/"Jan\nFeb\nMar\nApr\nMay", /*Y-axis tick labels*/"100\n80\n60\n40\n20\n0",/*background Color*/ 0xFFFFFF,/*Chart style:1-3*/1);
	  // Create a data series colored red on this chart
    id1_1 = lcd.creatChartSeries(chartId1, /*color*/0xFF0000);
	  // Add 5 points to the data series
    lcd.addChartSeriesData(chartId1, id1_1, point2, 5);
    delay(2000);
    // Update the color of the data series for this table to blue
    lcd.updateChartSeries(chartId1, id1_1, 0x0000FF);
    // Update the table to a bar chart and set the background to green
    lcd.updateChart(chartId1, 0x00FF00, 2);
	  delay(2000);
    // Update the color of the data series for this table to green
    lcd.updateChartSeries(chartId1, id1_1, 0x00FF00);
    // Update the table to a line chart and set the background to blue
    lcd.updateChart(chartId1, 0x0000FF, 3);
    // Update the value of the second point, counting from 0
    for(uint8_t i = 0; i<5; i++){
        lcd.updateChartPoint(chartId1, id1_1, 2, 20*i);
        delay(1000);
    }

    // Create a second table
    chartId2 = lcd.creatChart("Jun\nJul\nAug\nSep", "100\n80\n60\n40\n20\n0",/*background Color*/ 0xFFFF00,/*Chart style:1-3*/1);
    // Create a data series colored red on this table
    id2_1 = lcd.creatChartSeries(chartId2, /*color*/0xFF0000);
    // Create a data series colored blue on this table
    id2_2 = lcd.creatChartSeries(chartId2, /*color*/0x0000FF);
    // Add data to data series id2 1
    lcd.addChartSeriesData(chartId2, id2_1, point1, 4);
    // Add data to data series id2 2
    lcd.addChartSeriesData(chartId2, id2_2, point2, 4);
    delay(1000);

    // Create a third table
    chartId3 = lcd.creatChart("Jun\nJul\nAug\nSep", "100\n80\n60\n40\n20\n0",/*background Color*/ 0xFFFF00,/*Chart style:1-3*/2);
    // Create a data series colored red on this table
    id3_1 = lcd.creatChartSeries(chartId3, /*color*/0xFF0000);
    // Create a data series colored blue on this table
    id3_2 = lcd.creatChartSeries(chartId3, /*color*/0x0000FF);
    // Add data to data series id2 1
    lcd.addChartSeriesData(chartId3, id3_1, point1, 4);
    // Add data to data series id2 2
    lcd.addChartSeriesData(chartId3, id3_2, point2, 4);
    delay(1000);
    // Set Chart 1 to display at the top
    lcd.setTopChart(chartId1);
    delay(2000);
    // Set Chart 2 to display at the top
    lcd.setTopChart(chartId2);
    delay(2000);
    // Set Chart 3 to display at the top
    lcd.setTopChart(chartId3);
    delay(2000);
	  // Delete Figure 3
    lcd.deleteChart(chartId3);
    delay(1000);
    // Delete Chart 2
    lcd.deleteChart(chartId2);
    delay(1000);
    // Delete Chart 1
    lcd.deleteChart(chartId1);
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
  lcd.setBackgroundColor(WHITE);
  
  
}

void loop(void)
{
	testChart();
	delay(1000);
}