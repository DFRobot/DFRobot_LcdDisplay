/**!
 * @file slider.ino
 * @brief Creating a slider control and setting the slider value.
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
// Slider color
uint32_t sliderColor = 0x00FF00;
// Generate random colors
uint32_t generateRandomColor() {
    uint8_t r = rand() % 256;
    uint8_t g = rand() % 256;
    uint8_t b = rand() % 256;
    return (r << 16) | (g << 8) | b;
}
uint8_t sliderId[11];
void testSlider(){
	  // Create a standing slider
    sliderId[0] = lcd.creatSlider(/*x = */0, /*y = */10, /*width=*/10, /*height=*/200, /*color*/RED);
    // Set the value of the slider to 50
    lcd.setSliderValue(sliderId[0],50);
    // Change the position of the slider (from left to right) and set the color to random
    for(uint8_t i = 0; i <= 10; i++){
      sliderColor = generateRandomColor();
      lcd.updateSlider(sliderId[0],i*31, 10, 10, 200, sliderColor);
      delay(100);
    }
    // Change the position of the slider (from right to left) and set the color to random
    for(uint8_t i = 0; i <= 10; i++){
      sliderColor = generateRandomColor();
      lcd.updateSlider(sliderId[0],310-i*31, 10, 10, 200, sliderColor);
      delay(100);
    }
    delay(1000);
    // Create multiple sliders with random colors, decreasing in height, from left to right
    for(uint8_t i = 1; i <= 10; i++){
      sliderColor = generateRandomColor();
      sliderId[i] = lcd.creatSlider(i*31, 10, 10, 200 - i*10, sliderColor);
      delay(100);
    }
    delay(1000);
    // Set random values for each slider in turn
    for(uint8_t i = 0; i<=10; i++){
      lcd.setSliderValue(sliderId[i],rand()%100);
      delay(100);
    }
    delay(1000);
    // Change the slider in turn, changing its position, width, height, color, changing it to the effect of a horizontal slider
    for(uint8_t i = 0; i<=10; i++){
      sliderColor = generateRandomColor();
      lcd.updateSlider(sliderId[i], 10, i*23, 310 -i*20 , 10, sliderColor);
      delay(100);
    }
    delay(1000);
    // Delete all the sliders one by one
    for(uint8_t i = 0 ; i <= 10; i++){
      lcd.deleteSlider(sliderId[i]);
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

  //Initializing 
  lcd.begin();

  lcd.cleanScreen();
  delay(500);
  lcd.setBackgroundColor(WHITE);
  testSlider();
}

void loop(void)
{
  testSlider();
  delay(1000);
}