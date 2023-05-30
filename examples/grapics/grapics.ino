/**!
 * @file grapics.ino
 * @brief Displaying basic shapes.
 * @details The basic shapes that can be displayed include point, line, circle, rectangle, triangle, and more.
 * @n  Most parameters are related to the screen size (320*240). Please ensure that the custom parameters do not exceed the screen limits.
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @maintainer [qsjhyy](yihuan.huang@dfrobot.com)
 * @version  V1.0
 * @date  2023-05-29
 * @url https://github.com/DFRobot/DFRobot_LcdDisplay
 */
/*
 * User-selectable macro definition color
 * BLACK_RGB565 BLUE_RGB565 RED_RGB565 GREEN_RGB565 CYAN_RGB565 MAGENTA_RGB565
 * YELLOW_RGB565 WHITE_RGB565 NAVY_RGB565 DARKGREEN_RGB565 DARKCYAN_RGB565 MAROON_RGB565
 * PURPLE_RGB565 OLIVE_RGB565 LIGHTGREY_RGB565 DARKGREY_RGB565 ORANGE_RGB565
 * GREENYELLOW_RGB565 DCYAN_RGB565
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

DFRobot_LcdDisplay::sControlinf_t* gauge;

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
}

void loop(void){

  testDrawPixel();
  testLine();
  testFastLines(PURPLE_RGB565,YELLOW_RGB565);
  testRects(BLACK_RGB565,WHITE_RGB565);
  testRoundRects();
  testCircles(24,BLUE_RGB565);
  testTriangles(YELLOW_RGB565);
}

/* Test to draw a pixel*/
void testDrawPixel()
{
  //Clear screen
  lcd.fillScreen(BLACK_RGB565);
  int x = 0;
  int y = 0;
  for(int i = 0; i <= 240/2; i += 10){
    for (x = i; x <= 320 - i - 10; x += 10){   // 上
      /*
       * @ brief draw a pixel
       * @ param x coordinate
       *         y coordinate
       * c pixel color
       */
      lcd.drawPixel(x, y, ORANGE_RGB565);
    }

    for (y = i; y <= 240 - i - 10; y += 10) {   // 右
      lcd.drawPixel(x, y, ORANGE_RGB565);
    }

    for (x = 320 - i; x >= i + 10; x -= 10) {   // 下
      lcd.drawPixel(x, y, ORANGE_RGB565);
    }

    for (y = 240 - i; y >= i + 20; y -= 10) {   // 左
      lcd.drawPixel(x, y, ORANGE_RGB565);
    }
    lcd.drawPixel(x, y, ORANGE_RGB565);
  }
}

/* Test to draw a line*/
void testLine(){
// 0x00FF is the color data in the format of RGB565
  uint16_t color = 0x00FF;
  lcd.fillScreen(BLACK_RGB565);
  for (int16_t x=0; x < 320; x+=6) {
    /*
     * @ brief draw a line
     * @ param x0 The x-coordinate of the first vertex
     *         y0 The y-coordinate of the first vertex
     *         x1 The x-coordinate of the second vertex
     *         y1 The y-coordinate of the second vertex
     *         c line color
     */
    lcd.drawLine(/*x0=*/320/*Screen width*//2, /*y0=*/240/*Screen height*//2, /*x1=*/x, /*y1=*/0, /*c=*/color+=0x0700);
  }
  for (int16_t y=0; y < 240; y+=6) {
    lcd.drawLine(320/2, 240/2, 320, y, color+=0x0700);
  }
 
  for (int16_t x = 320; x >= 0; x-=6) {
    lcd.drawLine(320/2, 240/2, x,240, color+=0x0700);
  }
  
  for (int16_t y = 240; y >= 0; y-=6) {
    lcd.drawLine(320/2, 240/2, 0, y, color+=0x0700);
  }
}

/* Test to fast draw line(need to set delay), only horizontal line and vertical line */
void testFastLines(uint16_t color1, uint16_t color2) {
  for (int16_t y=0; y < 240; y+=4) {

    lcd.drawLine(/*x=*/0, /*y=*/y, /*w=*/320, y, /*c=*/color2);
    delay(30);
  }
  
  for(int16_t x=0; x < 320; x+=3) {

    lcd.drawLine(/*x=*/x, /*y=*/0, /*h=*/x, 240, /*c=*/color1);
    delay(30);
  }
}

/* Test to draw a rectangle*/
void testRects(uint16_t color1, uint16_t color2) { 
    lcd.fillScreen(BLACK_RGB565);
    int16_t x=320-12;
    for (; x > 100; x-=320/40) {
      /*
       * @ brief draw a hollow rectangle
       * @ param x The x-coordinate of the vertex 
       * @ param y The y-coordinate of the vertex
       * @ param w horizontal side length
       * @ param h longitudinal side length
       * @ param color Fill color, RGB color with 565 structure
       */
      lcd.drawRect(/*x=*/320/2 -x/2, /*y=*/240/2 -x/2 , /*w=*/x, /*h=*/x, /*color=*/color2+=0x0F00);
      delay(100);
    }
  
    /*
     * @ brief draw a filled rectangle
     * @ param x The x-coordinate of the vertex
     * @ param y The y-coordinate of the vertex
     * @ param w horizontal side length
     * @ param h longitudinal side length
     * @ param color Fill color, RGB color with 565 structure
     */
    lcd.fillRect(/*x=*/320/2 -x/2, /*y=*/240/2 -x/2 , /*w=*/x, /*h=*/x, /*color=*/color2);
    delay(100);
    for(; x > 6; x-=320/40){
      lcd.drawRect(320/2 -x/2, 240/2 -x/2 , x, x, color1);
      delay(100);
    }
}

/* Test to draw a rounded rectangle */
void testRoundRects() {
  lcd.fillScreen(BLACK_RGB565);
// 0xF00F is the color data in the format of RGB565
  int color = 0xF00F;
  int i;
  int x = 0;
  int y = 0;
  int w = 320-3;
  int h = 240-3;
  for(i = 0 ; i <= 16; i+=2) {
    /*
     * @ brief Draw a hollow rounded rectangle
     * @ param x0 The x-coordinate of the start vertex 
     * @ param y0 The y-coordinate of the start vertex 
     * @ param w horizontal side length
     * @ param h longitudinal side length
     * @ param radius Round corner radius
     * @ param color border color, 565 structure RGB color
     */
    lcd.drawRoundRect(/*x0=*/x, /*y0=*/y, /*w=*/w, /*h=*/h, /*radius=*/20, /*color=*/color);
    x+=5;
    y+=5;
    w-=10;
    h-=10;
    color+=0x0100;
    delay(50);
  }
  for(i = 0 ; i <= 16; i+=2) {
    /*
     * @ brief Draw a filled and rounded rectangle
     * @ param x0 The x-coordinate of the start vertex
     * @ param y0 The y-coordinate of the start vertex
     * @ param w horizontal side length
     * @ param h longitudinal side length
     * @ param radius Round corner radius
     * @ param color Fill color, RGB color with 565 structure
     */
    lcd.fillRoundRect(/*x0=*/x, /*y0=*/y, /*w=*/w, /*h=*/h, /*radius=*/10, /*color=*/color);
    x+=5;
    y+=5;
    w-=10;
    h-=10;
    color+=0x0500;
    delay(50);
  }
}

/* Test to draw a circle */
void testCircles(uint8_t radius, uint16_t color) {
  lcd.fillScreen(BLACK_RGB565);
  for (int16_t x=radius; x <=320-radius; x+=radius*2) {
    for (int16_t y=radius; y <=240-radius; y+=radius*2) {
      /*
       * @ brief Draw a hollow circle
       * @ param x0 The x-coordinate of the center point
       * @ param y0 The y-coordinate of the center point
       * @ param r radius
       * @ param color Circle color, RGB color with 565 structure
       */
      lcd.drawCircle(/*x0=*/x, /*y0=*/y, /*r=*/radius, /*color=*/color);
        if(x == y ||x == -y ||x == y + 2*radius)
          /*
           * @ brief Draw a filled circle
           * @ param x0 The x-coordinate of the center point
           * @ param y0 The y-coordinate of the center point
           * @ param r radius
           * @ param color Fill color, RGB color with 565 structure
           */
          lcd.fillCircle(/*x0=*/x, /*y0=*/y, /*r=*/radius, /*color=*/color);
       color += 800;
       delay(100);
    }
  }
}

/* Test to draw a triangle */
void testTriangles(uint16_t color){
  lcd.fillScreen(BLACK_RGB565);
  
  for (int16_t i=0; i <=320; i+=24)
    /*
     * @ brief Draw a hollow triangle
     * @ param x0 The x-coordinate of the start vertex
     * @ param y0 The y-coordinate of the start vertex
     * @ param x1 The x-coordinate of the second vertex
     * @ param y1 The y-coordinate of the second vertex
     * @ param x2 The x-coordinate of the third vertex
     * @ param y2 The y-coordinate of the third vertex
     * @ param color border color, 565 structure RGB color
     */
    lcd.drawTriangle(/*x0=*/i,/*y0=*/0,/*x1=*/0,/*y1=*/240-i,/*x2=*/320-i,/*y2=*/240, /*color=*/color);
  
  for (int16_t i=0; i <320; i+=24)
    lcd.drawTriangle(320,i*4/3,0,240-i*4/3,i,0, color);

  for (int16_t i=0; i <320; i+=24)
    lcd.drawTriangle(320,i*4/3,i,0,320-i,240, color);

  color = RED_RGB565;
  for (int16_t i=0; i <=320; i+=24)
     /*
      * @ brief Draw a filled triangle
      * @ param x0 The x-coordinate of the start vertex
      * @ param y0 The y-coordinate of the start vertex
      * @ param x1 The x-coordinate of the second vertex
      * @ param y1 The y-coordinate of the second vertex
      * @ param x2 The x-coordinate of the third vertex
      * @ param y2 The y-coordinate of the third vertex
      * @ param color Fill color, RGB color with 565 structure
      */
    lcd.fillTriangle(/*x0=*/i,/*y0=*/0,/*x1=*/0,/*y1=*/240-i,/*x2=*/320-i,/*y2=*/240, /*color=*/color+=100);
  
  for (int16_t i=0; i <320; i+=24)
    lcd.fillTriangle(320,i*4/3,0,240-i*4/3,i,0, color+=100);

  for (int16_t i=0; i <320; i+=24)
    lcd.fillTriangle(320,i*4/3,i,0,320-i,240, color+=100);
}


