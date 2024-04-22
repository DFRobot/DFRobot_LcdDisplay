/**!
 * @file  graphics.ino
 * @brief  draw graphics on the display
 * @details  Draw various lines on the display screen by setting different parameters (maximum screen size 320*240);
 * @n  Can display: 16 or 24 bit (color depth) bmp picture; Small size (under 70*70)png image
 * @n  Most parameters are related to the screen size (320*240). Please ensure that the custom parameters do not exceed the screen limits.
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license  The MIT License (MIT)
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
    testLine();
    testRects();
    testCircles();
    testTriangles();
}

uint32_t fillColor = 0x00FF00;      // fill color
uint32_t borderColor = 0xFF0000;    // border color
// Draw lines
void testLine(){
    // Set the color to red
    uint32_t color = 0xFF0000;
    uint8_t lineNum = 0;
    // Draw a line up the border from the center of the screen (every 5 pixels dot a line, and the color of each line is gradually dimming from red)
    for (int16_t x=0; x < 319; x+=5) {
        // Draw a line, and the return line ID starts with 1, so it can be recorded directly as lineNum
    	lcd.drawLine(320/2, 240/2, x, 0, 1, color-=0x040000);
    	lineNum++;
  	}
  	// Set the color to green
    color = 0x00FF00;
    // Draw a line from the center of the screen towards the right border (a line is drawn every 5 pixels apart, and the color of each line is gradually dimming from green)
    for (int16_t y=0; y < 240; y+=5) {
      lcd.drawLine(320/2, 240/2, 319, y, 1, color-=0x000500);
      lineNum++;
    }
    // Set the color to blue
    color = 0x0000FF;
    // Draw a line from the center of the screen to the bottom of the border (a line is drawn every 5 pixels, and the color of each line is gradually dimming from blue)
    for (int16_t x = 319; x >= 0; x-=5) {
      lcd.drawLine(320/2, 240/2, x,239, 1, color-=0x000004);
      lineNum++;
    }
    // Set the color to yellow
    color = 0xFFFF00;
    // Draw a line from the center of the screen towards the right border (draw a line every 5 pixels, and the color of each line is gradually dimming from yellow)
    for (int16_t y = 239; y >= 0; y-=5) {
      lcd.drawLine(320/2, 240/2, 0, y, 1,color-=0x050500);
      lineNum++;
    }
    delay(9000);
    // Locate the line ID to Line 1
    lineNum = 1;
    // Set the color to yellow
    color = 0xFFFF00;
    // Change the color of the line drawn in the center of the screen up the border to gradually darken to yellow
    for (int16_t x=0; x < 319; x+=5) {
      lcd.updateLine(lineNum, 320/2, 240/2, x, 0, 1, color-=0x040400);
      lineNum++;
    }
    // Set the color to red
    color = 0xFF0000;
    // Change the color of the line drawn in the center of the screen to the right border to gradually darken to red
    for (int16_t y=0; y < 240; y+=5) {
      lcd.updateLine(lineNum, 320/2, 240/2, 319, y, 1, color-=0x050000);
      lineNum++;
    }
	// Set the color to green
    color = 0x00FF00;
    // Change the color of the line drawn on the bottom border in the center of the screen to green and gradually darken
    for (int16_t x = 319; x >= 0; x-=5) {
      lcd.updateLine(lineNum, 320/2, 240/2, x,239, 1, color-=0x000400);
      lineNum++;
    }
	// Set the color to blue
    color = 0x0000FF;
    // Change the color of the line drawn in the center of the screen to the right border to gradually darken to blue
    for (int16_t y = 239; y >= 0; y-=5) {
      lcd.updateLine(lineNum, 320/2, 240/2, 0, y, 1,color-=0x000005);
      lineNum++;
    }
    delay(9000);
    // Delete all the lines one by one
    for(uint8_t i = 1; i <= lineNum; i++){
      lcd.deleteLine(i);
    }
    delay(9000);
}

uint32_t generateRandomColor() {
    uint8_t r = rand() % 256;
    uint8_t g = rand() % 256;
    uint8_t b = rand() % 256;
    return (r << 16) | (g << 8) | b;
}
// Draw rectangles
uint8_t rectsId[20];
void testRects() { 
    // Draw a rectangle 320 by 240 starting from the vertex, border set to 1, border color random, no fill, fill color blue, no rounded corners
    rectsId[0] = lcd.drawRect(0, 0, 320, 240, 1, 0xFF0000, 0, 0x00FF00, 0);
    // Change the rectangle, change the starting point, length and width, so that it shrinks toward the center of the screen
    for(uint8_t i = 0; i < 20; i++){
      uint16_t x = 320/40*i;
      uint16_t y = 240/40*i;
      uint16_t w = 320 - x *2;
      uint16_t h = 240 - y *2;
      // Set the border color to random
      borderColor = generateRandomColor();
      lcd.updateRect(rectsId[0], x, y, w, h, 1, borderColor, 0, 0x00FF00, 0);
    }
    delay(1000);
    // Change the rectangle, change the starting point, length and width, and set the border color to blue so that it enlarges from the center of the screen
    for(uint8_t i = 0; i <= 20; i++){
      uint16_t x = 320/40*(20-i);
      uint16_t y = 240/40*(20-i);
      uint16_t w = 320 - x *2;
      uint16_t h = 240 - y *2;
      // Set the border color to random
      borderColor = generateRandomColor();
      lcd.updateRect(rectsId[0], x, y, w, h, 1, borderColor, 0, 0x00FF00, 0);
    }
    delay(1000);
    // Add a new rectangle, set a different starting point, length and width, so that it gradually spreads from the screen border to the center of the effect
    for(uint8_t i = 1; i < 20; i++){
      uint16_t x = 320/40*i;
      uint16_t y = 240/40*i;
      uint16_t w = 320 - x *2;
      uint16_t h = 240 - y *2;
      borderColor = generateRandomColor();
      rectsId[i] = lcd.drawRect(x, y, w, h, 1, borderColor, 0, 0x00FF00, 0);
    }
    delay(1000);
    
    // Change these rectangles from the center, change them to rounded corners, and enable Fill, fill color green gradient
    for(uint8_t i = 0; i <= 20; i++){
      uint16_t x = 320/40*(20-i);
      uint16_t y = 240/40*(20-i);
      uint16_t w = 320 - x *2;
      uint16_t h = 240 - y *2;
      // Set the fill color to random
      borderColor = generateRandomColor();
      fillColor = generateRandomColor();
      lcd.updateRect(rectsId[20-i],x, y, w, h, 1, borderColor, 1, fillColor, 1);
    }
    
    delay(1000);
    // Delete all rectangles one by one
    for(uint8_t i = 0; i < 20; i++){
      lcd.deleteRect(rectsId[i]);
    }
    delay(1000);
}

// Draw circles
uint8_t circlesId[21];
void testCircles() {
    // Set the border color to random
    borderColor = generateRandomColor();
    // With (160, 120) as the center of the circle, draw a circle with a radius of 1 and a border color of random color without filling
    circlesId[0] = lcd.drawCircle(160, 120, 1, 2, borderColor, 0, 0x0000FF);
    // Change the radius of the previous circle and the border color to make the circle larger
    for(uint8_t i = 0; i < 20; i++){
      borderColor = generateRandomColor();
      lcd.updateCircle(circlesId[0], 160, 120, 6*i, 2, borderColor, 0, 0x0000FF);
      delay(30);
    }
    // Take (160,120) as the center of the circle and add multiple circles to achieve the effect of multiple concentric circles
    for(uint8_t i = 1; i < 20; i++){
      borderColor = generateRandomColor();
      circlesId[i] = lcd.drawCircle(160, 120, 120-6*i, 2, borderColor, 0, 0x0000FF);
    }
    delay(1000);

    // Change the circles so that the concentric circles are all set to the fill color and the color is random
    for(uint8_t i = 0; i < 20; i++){
      borderColor = generateRandomColor();
      fillColor = generateRandomColor();
      lcd.updateCircle(circlesId[20-i], 160, 120, 6*i, 2, borderColor, 1, fillColor);
    }
  
    delay(1000);
    // Delete the circles one by one
    for(uint8_t i = 0; i < 20; i++){
      lcd.deleteCircle(circlesId[i]);
    }
    delay(1000);
}

uint8_t trianglesId[10];
// Draw triangles
void testTriangles(){
  // Draw a triangle with the top center of the screen as the vertex and the bottom of the screen for the other two vertices
  trianglesId[0] = lcd.drawTriangle(160, 0, 0, 239, 319, 239, 1, borderColor, 0, fillColor);
  // Update the three vertices of the triangle to scale
  for (uint8_t i=0; i <10; i++){
    lcd.updateTriangle(trianglesId[0], 160, i*12, i*16, 239 - i*12,319-i*16, 239-i*12, 1, borderColor, 0, fillColor);
  }
  delay(1000);  
  // Add triangles to achieve multiple concentric similar triangles
  for(uint8_t i = 9; i>0; i--){
    trianglesId[10-i] = lcd.drawTriangle(160, i*12, i*16, 239 - i*12,319-i*16, 239-i*12, 1, borderColor, 0, fillColor);
  }
  delay(1000);
  // Fill these triangles with random colors  
  for(uint8_t i = 0; i<10; i++){
    fillColor = generateRandomColor();
    lcd.updateTriangle(trianglesId[i], 160, i*12, i*16, 239 - i*12,319-i*16, 239-i*12, 1, borderColor, 1, fillColor);
  }
  delay(1000);
  // Delete the triangles one by one
  for(uint8_t i = 0 ;i < 10;i++){
    lcd.deleteTriangle(trianglesId[i]);
  }
  delay(1000);
}
