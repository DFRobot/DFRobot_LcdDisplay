# DFRobot_I2CLcd
- [中文版](./README_CN.md)

  The product is a TFT display screen with I2C and UART interfaces. It has built-in firmware that integrates some LVGL controls and GDL graphics display. Additionally, it features an integrated GT30L24A3W font chip on the hardware, which supports language display for multiple countries. The firmware chip also includes a large number of commonly used icons.
![Product Image](./resources/images/DFR0997.png)

## Product Link（https://www.dfrobot.com）
    SKU: DFR0997

## Table of Contents

* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits)

## Summary
Provides an arduino library to drive the display screen(DFR0997)

## Installation
To use this library, please download the library file first, and paste it into the \Arduino\libraries directory, then open the examples folder and run the demo in the folder.

## Methods

```C++
  /**
   * @fn drawPixel
   * @brief Function to draw a pixel 
   * @param x X-coordinate position of the pixel
   * @param y Y-coordinate position of the pixel
   * @param color The color of pixels, RGB565 format
   */
  void drawPixel(int16_t x, int16_t y, uint16_t color);
  
  /**
   * @fn lvglInit
   * @brief Initializing lvgl, however, when using lvgl's controls or ICONS, you need to call this function 
   * @param bg_color lvgl background color
   */
  void lvglInit(uint16_t bg_color = 0xffee);

  /**
   * @fn setFont
   * @brief Set font for easy calculation of consecutive font display positions.
   * @param font font types, eLcdFont_t
   */
  void setFont(eLcdFont_t font);
  /**
   * @fn fillScreen
   * @brief 填充整个屏幕
   * @param color color to fill screen, RGB565 format
   */
  void fillScreen(uint16_t color);
  
  /**
   * @fn setBackLight
   * @brief Set screen backlight.
   * @param on true(on)/false(off)
   */
  void setBackLight(bool on);
  
  /**
   * @fn drawLine
   * @brief Draw a straight line on the screen.
   * @param x0 Start X-coordinate of the line.
   * @param y0 Start Y-coordinate of the line.
   * @param x1 End X-coordinate of the line.
   * @param y1 End Y-coordinate of the line.
   * @param color the color of the line, RGB565 format
   */
  void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
  
  /**
   * @fn drawRect
   * @brief Draw rectangles on the screen
   * @param x0 Start of rectangle x coordinate
   * @param y0 Start of rectangle y coordinate
   * @param w  Width of a rectangle
   * @param h  Height of rectangle
   * @param color Rectangular color
   */
  void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
  
  /**
   * @fn fillRect
   * @brief Fill a rectangle on the screen
   * @param x0 Start of rectangle x coordinate
   * @param y0 Start of rectangle y coordinate
   * @param w  Width of a rectangle
   * @param h  Height of rectangle
   * @param color Rectangular color
   */
  void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
  
  /**
   * @fn drawRoundRect
   * @brief Draw rounded rectangles on the screen
   * @param x0 Start of rectangle x coordinate
   * @param y0 Start of rectangle y coordinate
   * @param w  Width of a rectangle
   * @param h  Height of rectangle
   * @param radius  Radius of the rounded corners
   * @param color Rectangular color
   */
  void drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,
      int16_t radius, uint16_t color);

  /**
   * @fn fillRoundRect
   * @brief Fill a rounded rectangle on the screen
   * @param x0 Start of rectangle x coordinate
   * @param y0 Start of rectangle y coordinate
   * @param w  Width of a rectangle
   * @param h  Height of rectangle
   * @param radius  Radius of the rounded corners
   * @param color Rectangular color
   */
  void fillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,
      int16_t radius, uint16_t color);
  
  /**
   * @fn drawCircle
   * @brief Draw circles on the screen
   * @param x0 Center of the circle x coordinate
   * @param y0 Center of the circle y coordinate
   * @param r  Radius of the circle
   * @param color Color of the circle
   */
  void drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);

  /**
   * @fn fillCircle
   * @brief Fill a circle on the screen
   * @param x0 Center of the circle x coordinate
   * @param y0 Center of the circle y coordinate
   * @param r  Radius of the circle
   * @param color Color of the circle
   */
  void fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);

  /**
   * @fn drawTriangle
   * @brief Draw a triangle on the screen
   * @param x0 The x-coordinate of the first point of the triangle
   * @param y0 The y-coordinate of the first point of the triangle
   * @param x1 The x-coordinate of the second point of the triangle
   * @param y1 The y-coordinate of the second point of the triangle
   * @param x2 The x-coordinate of the third point of the triangle
   * @param y2 The y-coordinate of the third point of the triangle
   * @param color Color of the circle
   */
  void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
      int16_t x2, int16_t y2, uint16_t color);

  /**
   * @fn fillTriangle
   * @brief Fill a triangle on the screen
   * @param x0 The x-coordinate of the first point of the triangle
   * @param y0 The y-coordinate of the first point of the triangle
   * @param x1 The x-coordinate of the second point of the triangle
   * @param y1 The y-coordinate of the second point of the triangle
   * @param x2 The x-coordinate of the third point of the triangle
   * @param y2 The y-coordinate of the third point of the triangle
   * @param color Color of the circle
   */
  void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
      int16_t x2, int16_t y2, uint16_t color);

  /**
   * @fn drawIcon
   * @brief Draw an icon
   * @param x The x-coordinate of the first point of the icon
   * @param y The y-coordinate of the first point of the icon
   * @param id The icon's corresponding number
   * @param size Icon scaling factor
   * @return Icon control handle
   */
  sControlinf_t * drawIcon(int16_t x,int16_t y,uint8_t id,uint16_t size = 255);
  
  /**
   * @fn drawDiskImg
   * @brief Used to draw the pictures inside the USB drive (in BMP or PNG format).
   * @param x The x-coordinate of the first point in the picture
   * @param y The y-coordinate of the first point in the picture
   * @param str The full file name of the image, such as "/img/cat.bmp"
   * @param size Scale factor for image resizing
   * @return The object of the picture control
   * @note The size of bmp and png is limited due to the small ram
   */
  sControlinf_t* drawDiskImg(int16_t x, int16_t y, String str, uint16_t size = 255);

  /**
   * @fn creatSlider
   * @brief Create a slider control
   * @param x The x-coordinate of the slider
   * @param y The y-coordinate of the slider
   * @param width The width of the slider
   * @param height The height of the slider
   * @param color The color of the slider
   * @return Slider control handle
   */
  sControlinf_t *creatSlider(uint16_t x,uint16_t y,uint8_t width,uint8_t height, uint16_t color);
  
  /**
   * @fn setSliderValue
   * @brief Sets the slider value
   * @param obj Slider control handle
   * @param value The value of the slider
   */
  void setSliderValue(sControlinf_t* obj,uint8_t value);
  
  /**
   * @fn creatBar
   * @brief Create a progress bar control
   * @param x The x coordinate of the progress bar
   * @param y The y coordinate of the progress bar
   * @param width Width of the progress bar
   * @param height Height of the progress bar
   * @param color Color of the progress bar
   * @return Progress bar control handle
   */
  sControlinf_t *creatBar(uint16_t x,uint16_t y,uint16_t width,uint8_t height, uint16_t color);
  
  /**
   * @fn setBar
   * @brief Set the value of the progress bar, which can include a unit but must start with a number
   * @param obj Progress bar control handle
   * @param str Value of the progress bar
   */
  void setBar(sControlinf_t* obj,String str);
  
  /**
   * @fn creatChart
   * @brief Create a chart control
   * @param strX Label on the x axis of the chart
   * @param strY Label on the y axis of the chart
   * @param type Type of chart (line chart / bar chart)
   * @return chart control handle
   */
  sControlinf_t *creatChart(String strX,String strY, uint8_t type);
  
  /**
   * @fn creatChartSerie
   * @brief Create a line chart or bar chart sequence in the chart
   * @param obj chart control handle
   * @param color Color of line chart/bar chart
   * @return Return the index of the series
   */
  uint8_t creatChartSerie(sControlinf_t* obj,uint16_t color);
  
  /**
   * @fn addChart
   * @brief Allocate and add a data series to the chart
   * @param obj chart control handle
   * @param id the allocated data series
   * @param point A graph/bar chart requires an array of data
   * @param len  array length
   */
  uint8_t addChart(sControlinf_t* obj,uint8_t id,uint16_t point[],uint8_t len);

  /**
   * @fn creatGauge
   * @brief Create a dial control
   * @param x The x-axis coordinate of the control
   * @param y The y-axis coordinate of the control
   * @param width  Control width
   * @param height Control height
   * @param color Control color
   * @return dial control handle
   */
  sControlinf_t *creatGauge(uint16_t x,uint16_t y,uint8_t width,uint8_t height, uint16_t color);
  
  /**
   * @fn setGaugeScale
   * @brief Setting the parameters of the dial control
   * @param obj dial control handle
   * @param angle angle of the scale (0..360)
   * @param start minimum value
   * @param end maximum value
   */
  void setGaugeScale(sControlinf_t* obj,uint16_t angle,int16_t start,int16_t end);

  /**
   * @fn setGaugeValue
   * @brief Set the value of a needle
   * @param obj dial control handle
   * @param value the new value
   */
  void setGaugeValue(sControlinf_t* obj,uint16_t value);

  /**
   * @fn creatCompass
   * @brief Creating a compass control
   * @param x The x-axis coordinate of the control
   * @param y The y-axis coordinate of the control
   * @param width  Control width
   * @param height Control height
   * @return compass control handle
   */
  sControlinf_t *creatCompass(uint16_t x,uint16_t y,uint8_t width,uint8_t height);

  /**
   * @fn setCompassScale
   * @brief Setting the angle of the compass pointer
   * @param obj compass control handle
   * @param scale Pointer angle(0~360)
   */
  void setCompassScale(sControlinf_t* obj,uint16_t scale);
  
  /**
   * @fn creatArc
   * @brief Creating an angle control
   * @param x The x-axis coordinate of the control
   * @param y The y-axis coordinate of the control
   * @param width  Control width
   * @param height Control height
   * @return Handle of the angle control
   */
  sControlinf_t *creatArc(uint16_t x,uint16_t y,uint8_t width,uint8_t height);
  
  /**
   * @fn setArcRotation
   * @brief Set the value of the angle control
   * @param obj Handle of the angle control
   * @param rotation the new value
   */
  void setArcRotation(sControlinf_t* obj,uint16_t rotation);

  /**
   * @fn creatLineMeter
   * @brief Create a linear gauge control
   * @param x The x-axis coordinate of the control
   * @param y The y-axis coordinate of the control
   * @param width  Control width
   * @param height Control height
   * @param color Control color
   * @return linear gauge control handle
   */
  sControlinf_t *creatLineMeter(uint16_t x,uint16_t y,uint8_t width,uint8_t height, uint16_t color);

  /**
   * @fn setMeterValue
   * @brief Set a new value on the line meter
   * @param obj pointer to a line meter object
   * @param value new value
   */
  void setMeterValue(sControlinf_t* obj,uint16_t value);
  
  /**
   * @fn setMeterScale
   * @brief Set a new value on the line meter
   * @param obj pointer to a line meter object
   * @param angle angle of the scale (0..360)
   * @param start minimum value
   * @param end maximum value
   */
  void setMeterScale(sControlinf_t* obj,uint16_t angle,int16_t start,int16_t end);
  
  /**
   * @fn drawString
   * @brief Display text on the screen
   * @param x The x-coordinate of the starting position
   * @param y The y-coordinate of the starting position
   * @param str The text to display
   * @param type Text size (only applicable to eChinese and eAscii): 0 (24px size), 1 (12px size)
   * @param color Color of text
   */
  void drawString(uint8_t x,uint8_t y,String str,uint8_t type,uint16_t color);

  /**
   * @fn drawString
   * @brief Display text on the screen
   * @param x The x-coordinate of the starting position
   * @param y The y-coordinate of the starting position
   * @param str The text to display
   * @param type Text size (only applicable to eChinese and eAscii): 0 (24px size), 1 (12px size)
   * @param color Color of text
   * @param bgColor The color of the text background
   */
  void drawString(uint8_t x,uint8_t y,String str,uint8_t type,uint16_t color,uint16_t bgColor);
  
  /**
   * @fn drawLcdTime
   * @brief Displays the set time on the screen
   * @param x The x-coordinate of the starting position
   * @param y The y-coordinate of the starting position
   * @param hour hour
   * @param Minute minute
   * @param seconds second
   * @param fontSize font size
   * @param color Color of text
   * @param bgColor The color of the text background
   */
  void drawLcdTime(uint8_t x,uint8_t y,uint8_t hour,uint8_t Minute,uint8_t seconds,uint8_t fontSize ,uint16_t color,uint16_t bgColor);

  /**
   * @fn drawLcdDate
   * @brief Displays the set date on the screen
   * @param x The x-coordinate of the starting position
   * @param y The y-coordinate of the starting position
   * @param month month
   * @param day day
   * @param weeks weekday
   * @param fontSize font size
   * @param color Color of text
   * @param bgColor The color of the text background
   */
  void drawLcdDate(uint8_t x,uint8_t y,uint8_t month,uint8_t day,uint8_t weeks,uint8_t fontSize,uint16_t color,uint16_t bgColor);

  /**
   * @fn reset
   * @brief Reset the display screen. After the display screen is reset, all the created lvgl controls will be deleted, and the displayed content will be cleared as well.
   */
  void reset();
  /**
   * @fn lvglDelete
   * @brief Delete a specific control that has been created.
   * @param obj Delete the handle of a control object
   */
  void lvglDelete(sControlinf_t* obj);
```

## Compatibility

MCU                | Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | -----
Arduino Uno        |      √       |              |             | 
FireBeetle-ESP8266        |      √       |              |             | 
FireBeetle-ESP32        |      √       |              |             | 
Arduino MEGA2560        |      √       |              |             | 
Arduino Leonardo|      √       |              |             | 
Micro:bit        |      √       |              |             | 
FireBeetle-M0        |      √       |              |             | 



## History

- 2023/05/29 - Version 1.0.0 released.

## Credits

Written by fengli(li.feng@dfrobot.com), 2022.08.08 (Welcome to our [website](https://www.dfrobot.com/))

