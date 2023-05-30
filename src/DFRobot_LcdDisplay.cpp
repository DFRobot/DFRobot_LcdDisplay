/*!
 * @file DFRobot_LcdDisplay.cpp
 * @brief Define the infrastructure of the DFRobot_LcdDisplay class
 * @details This library can drive the DFR0997 display, and it can easily drive the color screen through both the I2C interface and UART interface
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @License     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @maintainer [qsjhyy](yihuan.huang@dfrobot.com)
 * @version  V1.0
 * @date  2023-05-29
 * @url https://github.com/DFRobot/DFRobot_LcdDisplay
 */
#include "DFRobot_LcdDisplay.h"
#include <Wire.h>
#include <Arduino.h>

uint8_t wordLen[10];

DFRobot_LcdDisplay::DFRobot_LcdDisplay()
{
}

bool DFRobot_LcdDisplay::begin()
{
  return true;
}

void DFRobot_LcdDisplay::setBackLight(bool on)
{
  uint8_t* cmd = creatCommand(CMD_OF_SETBACKLIGHT, CMDLEN_OF_SETBACKLIGHT);
  if (on == true) {
    cmd[4] = 1;
  } else {
    cmd[4] = 0;
  }

  writeCommand(cmd, CMDLEN_OF_SETBACKLIGHT);
  free(cmd);
}

void DFRobot_LcdDisplay::drawPixel(int16_t x, int16_t y, uint16_t color)
{
  uint8_t* cmd = creatCommand(CMD_OF_DRAWPIXEL, CMDLEN_OF_DRAWPIXEL);
  if (320 <= x) {
    x = 319;
  }
  if (240 <= y) {
    y = 239;
  }
  cmd[4] = x >> 8;
  cmd[5] = x & 0xFF;
  cmd[6] = y >> 8;
  cmd[7] = y & 0xFF;
  cmd[8] = color >> 8;
  cmd[9] = color & 0xFF;
  writeCommand(cmd, CMDLEN_OF_DRAWPIXEL);
  free(cmd);
}

void DFRobot_LcdDisplay::fillScreen(uint16_t color)
{
  uint8_t* cmd = creatCommand(CMD_OF_FILLSCREEN, CMDLEN_OF_FILLSCREEN);
  cmd[4] = color >> 8;
  cmd[5] = color & 0xFF;

  writeCommand(cmd, CMDLEN_OF_FILLSCREEN);
  free(cmd);
}

void DFRobot_LcdDisplay::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color)
{
  uint8_t* cmd = creatCommand(CMD_OF_DRAWLINE, CMDLEN_OF_DRAWLINE);
  cmd[4] = x0 >> 8;
  cmd[5] = x0 & 0xFF;
  cmd[6] = y0 >> 8;
  cmd[7] = y0 & 0xFF;
  cmd[8] = x1 >> 8;
  cmd[9] = x1 & 0xFF;
  cmd[10] = y1 >> 8;
  cmd[11] = y1 & 0xFF;
  cmd[12] = color >> 8;
  cmd[13] = color & 0xFF;
  writeCommand(cmd, CMDLEN_OF_DRAWLINE);
  free(cmd);
}

void DFRobot_LcdDisplay::drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
  uint8_t* cmd = creatCommand(CMD_OF_DRAWRECT, CMDLEN_OF_DRAWRECT);
  cmd[4] = x >> 8;
  cmd[5] = x & 0xFF;
  cmd[6] = y >> 8;
  cmd[7] = y & 0xFF;
  cmd[8] = w >> 8;
  cmd[9] = w & 0xFF;
  cmd[10] = h >> 8;
  cmd[11] = h & 0xFF;
  cmd[12] = color >> 8;
  cmd[13] = color & 0xFF;
  writeCommand(cmd, CMDLEN_OF_DRAWRECT);
  free(cmd);
}

void DFRobot_LcdDisplay::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
  uint8_t* cmd = creatCommand(CMD_OF_FILLRECT, CMDLEN_OF_FILLRECT);
  cmd[4] = x >> 8;
  cmd[5] = x & 0xFF;
  cmd[6] = y >> 8;
  cmd[7] = y & 0xFF;
  cmd[8] = w >> 8;
  cmd[9] = w & 0xFF;
  cmd[10] = h >> 8;
  cmd[11] = h & 0xFF;
  cmd[12] = color >> 8;
  cmd[13] = color & 0xFF;
  writeCommand(cmd, CMDLEN_OF_FILLRECT);
  free(cmd);
}

void DFRobot_LcdDisplay::drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,
  int16_t radius, uint16_t color)
{
  uint8_t* cmd = creatCommand(CMD_OF_DRAWROUNDRECT, CMDLEN_OF_DRAWROUNDRECT);
  cmd[4] = x0 >> 8;
  cmd[5] = x0 & 0xFF;
  cmd[6] = y0 >> 8;
  cmd[7] = y0 & 0xFF;
  cmd[8] = w >> 8;
  cmd[9] = w & 0xFF;
  cmd[10] = h >> 8;
  cmd[11] = h & 0xFF;
  cmd[12] = radius & 0xFF;
  cmd[13] = color >> 8;
  cmd[14] = color & 0xFF;
  writeCommand(cmd, CMDLEN_OF_DRAWROUNDRECT);
  free(cmd);
}

void DFRobot_LcdDisplay::fillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,
  int16_t radius, uint16_t color)
{
  uint8_t* cmd = creatCommand(CMD_OF_FILLROUNDRECT, CMDLEN_OF_FILLROUNDRECT);
  cmd[4] = x0 >> 8;
  cmd[5] = x0 & 0xFF;
  cmd[6] = y0 >> 8;
  cmd[7] = y0 & 0xFF;
  cmd[8] = w >> 8;
  cmd[9] = w & 0xFF;
  cmd[10] = h >> 8;
  cmd[11] = h & 0xFF;
  cmd[12] = radius;
  cmd[13] = color >> 8;
  cmd[14] = color & 0xFF;
  writeCommand(cmd, CMDLEN_OF_FILLROUNDRECT);
  free(cmd);
}

void DFRobot_LcdDisplay::drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color)
{
  uint8_t* cmd = creatCommand(CMD_OF_DRAWCIRCLE, CMDLEN_OF_DRAWCIRCLE);
  cmd[4] = x0 >> 8;
  cmd[5] = x0 & 0xFF;
  cmd[6] = y0 >> 8;
  cmd[7] = y0 & 0xFF;
  cmd[8] = r;
  cmd[9] = color >> 8;
  cmd[10] = color & 0xFF;
  writeCommand(cmd, CMDLEN_OF_DRAWCIRCLE);
  free(cmd);
}

void DFRobot_LcdDisplay::fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color)
{
  uint8_t* cmd = creatCommand(CMD_OF_FILLCIRCLE, CMDLEN_OF_FILLCIRCLE);
  cmd[4] = x0 >> 8;
  cmd[5] = x0 & 0xFF;
  cmd[6] = y0 >> 8;
  cmd[7] = y0 & 0xFF;
  cmd[8] = r;
  cmd[9] = color >> 8;
  cmd[10] = color & 0xFF;
  writeCommand(cmd, CMDLEN_OF_FILLCIRCLE);
  free(cmd);

}

void DFRobot_LcdDisplay::drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
  int16_t x2, int16_t y2, uint16_t color)
{
  uint8_t* cmd = creatCommand(CMD_OF_DRAWTRIANGLE, CMDLEN_OF_DRAWTRIANGLE);
  cmd[4] = x0 >> 8;
  cmd[5] = x0 & 0xFF;
  cmd[6] = y0 >> 8;
  cmd[7] = y0 & 0xFF;
  cmd[8] = x1 >> 8;
  cmd[9] = x1 & 0xFF;
  cmd[10] = y1 >> 8;
  cmd[11] = y1 & 0xFF;
  cmd[12] = x2 >> 8;
  cmd[13] = x2 & 0xFF;
  cmd[14] = y2 >> 8;
  cmd[15] = y2 & 0xFF;
  cmd[16] = color >> 8;
  cmd[17] = color & 0xFF;
  writeCommand(cmd, CMDLEN_OF_DRAWTRIANGLE);
  free(cmd);
}

void DFRobot_LcdDisplay::fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
  int16_t x2, int16_t y2, uint16_t color)
{
  uint8_t* cmd = creatCommand(CMD_OF_FILLTRIANGLE, CMDLEN_OF_FILLTRIANGLE);
  cmd[4] = x0 >> 8;
  cmd[5] = x0 & 0xFF;
  cmd[6] = y0 >> 8;
  cmd[7] = y0 & 0xFF;
  cmd[8] = x1 >> 8;
  cmd[9] = x1 & 0xFF;
  cmd[10] = y1 >> 8;
  cmd[11] = y1 & 0xFF;
  cmd[12] = x2 >> 8;
  cmd[13] = x2 & 0xFF;
  cmd[14] = y2 >> 8;
  cmd[15] = y2 & 0xFF;
  cmd[16] = color >> 8;
  cmd[17] = color & 0xFF;
  writeCommand(cmd, CMDLEN_OF_FILLTRIANGLE);
  free(cmd);
}

DFRobot_LcdDisplay::sControlinf_t* DFRobot_LcdDisplay::drawIcon(int16_t x, int16_t y, uint16_t id, uint16_t size)
{
  sControlinf_t* icon = (sControlinf_t*)malloc(sizeof(sControlinf_t));
  if (icon == NULL) {
    DBG("icon malloc fail !");
  }
  icon->x = x;
  icon->y = y;
  icon->width = 32;
  icon->height = 32;
  icon->color = 0;
  icon->id = id;
  icon->number = getNumber(1);
  icon->inf = NULL;

  sControlinf_t* obj = &head;
  while (obj->inf != NULL) {
    obj = obj->inf;
  }
  obj->inf = icon;
  if (size > 512) size = 512;
  if (size < 128) size = 128;
  uint8_t* cmd = creatCommand(CMD_OF_DRAWICON, CMDLEN_OF_DRAWICON);
  cmd[4] = icon->number;
  cmd[5] = icon->id >> 8;
  cmd[6] = icon->id & 0xFF;
  cmd[7] = x >> 8;
  cmd[8] = x & 0xFF;
  cmd[9] = y >> 8;
  cmd[10] = y & 0xFF;
  cmd[11] = size >> 8;
  cmd[12] = size & 0xFF;

  writeCommand(cmd, CMDLEN_OF_DRAWICON);
  delay(100);
  free(cmd);

  return icon;
}

DFRobot_LcdDisplay::sControlinf_t* DFRobot_LcdDisplay::drawDiskImg(int16_t x, int16_t y, String pathStr, uint16_t size)
{
  sControlinf_t* img = (sControlinf_t*)malloc(sizeof(sControlinf_t));
  if (img == NULL) {
    DBG("img malloc fail !");
  }
  img->x = x;
  img->y = y;
  img->id = pathStr.endsWith(".png");   // 0: .bmp ; 1: .png
  img->number = getNumber(1);
  img->inf = NULL;

  sControlinf_t* obj = &head;
  while (obj->inf != NULL) {
    obj = obj->inf;
  }
  obj->inf = img;

  if (size > 512) size = 512;
  if (size < 128) size = 128;

  int16_t length = pathStr.length() - 4;   // Remove the suffix to save on transmission byte count
  if (20 <= length) {
    DBG("The path name is too long. Shorten the path name");
    return NULL;
  }
  uint8_t* cmd = creatCommand(CMD_OF_DRAWDISKIMG, 12 + length);
  cmd[4] = img->number;
  cmd[5] = img->id;
  cmd[6] = x >> 8;
  cmd[7] = x & 0xFF;
  cmd[8] = y >> 8;
  cmd[9] = y & 0xFF;
  cmd[10] = size >> 8;
  cmd[11] = size & 0xFF;
  for (uint8_t i = 0; i < length; i++) {
    cmd[12 + i] = pathStr[i];
  }

  writeCommand(cmd, 12 + length);
  free(cmd);

  delay(1500);   // Reading and parsing images from a USB drive is slow, resulting in slow display

  return img;
}

DFRobot_LcdDisplay::sControlinf_t* DFRobot_LcdDisplay::creatSlider(uint16_t x, uint16_t y, uint8_t width, uint8_t height, uint16_t color)
{
  sControlinf_t* slider = (sControlinf_t*)malloc(sizeof(sControlinf_t));
  if (slider == NULL) {
    DBG("slider malloc fail !");
  }
  slider->x = x;
  slider->y = y;
  slider->width = width;
  slider->height = height;
  slider->color = color;
  slider->id = 1;
  slider->number = getNumber(1);
  slider->inf = NULL;
  sControlinf_t* obj = &head;
  while (obj->inf != NULL) {
    obj = obj->inf;
  }
  obj->inf = slider;

  uint8_t* cmd = creatCommand(CMD_DRAW_LVGLSLIDER, CMDLEN_DRAW_LVGLSLIDER);
  cmd[4] = slider->number;
  cmd[5] = 0;
  cmd[6] = x >> 8;
  cmd[7] = x & 0xFF;
  cmd[8] = y >> 8;
  cmd[9] = y & 0xFF;
  cmd[10] = width;
  cmd[11] = height;
  cmd[12] = color >> 8;
  cmd[13] = color & 0xFF;

  writeCommand(cmd, CMDLEN_DRAW_LVGLSLIDER);
  free(cmd);

  return slider;
}

void DFRobot_LcdDisplay::setSliderValue(sControlinf_t* obj, uint8_t value)
{
  uint8_t* cmd = creatCommand(CMD_DRAW_LVGLSLIDER, CMDLEN_CHANGE_LVGLSLIDER_VALUE);
  cmd[4] = obj->number;
  cmd[5] = 1;
  cmd[6] = 1;
  cmd[7] = value >> 8;
  cmd[8] = value & 0xFF;

  writeCommand(cmd, CMDLEN_CHANGE_LVGLSLIDER_VALUE);
  free(cmd);
}

DFRobot_LcdDisplay::sControlinf_t* DFRobot_LcdDisplay::creatBar(uint16_t x, uint16_t y, uint16_t width, uint8_t height, uint16_t color)
{
  sControlinf_t* bar = (sControlinf_t*)malloc(sizeof(sControlinf_t));
  if (bar == NULL) {
    DBG("BAR malloc fail !");
  }
  bar->x = x;
  bar->y = y;
  bar->width = width;
  bar->height = height;
  bar->color = color;
  bar->id = 1;
  bar->number = getNumber(1);
  bar->inf = NULL;
  sControlinf_t* obj = &head;
  while (obj->inf != NULL) {
    obj = obj->inf;
  }
  obj->inf = bar;

  uint8_t* cmd = creatCommand(CMD_DRAW_LVGLBAR, CMDLEN_DRAW_LVGLBAR);
  cmd[4] = bar->number;
  cmd[5] = 0;
  cmd[6] = x >> 8;
  cmd[7] = x & 0xFF;
  cmd[8] = y >> 8;
  cmd[9] = y & 0xFF;
  cmd[10] = width >> 8;
  cmd[11] = width & 0xFF;
  cmd[12] = height;
  cmd[13] = color >> 8;
  cmd[14] = color & 0xFF;

  writeCommand(cmd, CMDLEN_DRAW_LVGLBAR);
  free(cmd);

  return bar;
}

void DFRobot_LcdDisplay::setBar(sControlinf_t* obj, String str)
{
  uint8_t len = str.length();

  uint8_t* cmd = creatCommand(CMD_DRAW_LVGLBAR, len + 7);
  if (cmd == NULL) {
    DBG("cmd null");
  }

  cmd[4] = obj->number;
  cmd[5] = 1;
  cmd[6] = 1;
  for (uint8_t i = 0;i < len;i++) {
    cmd[7 + i] = str[i];
  }

  writeCommand(cmd, len + 7);
  free(cmd);
}

uint8_t DFRobot_LcdDisplay::getNumber(uint8_t id)
{
  LCD_UNUSED(id);
  uint16_t number = 1;
  sControlinf_t* obj = &head;
  sControlinf_t* last;
  while (1) {
    last = obj;
    obj = obj->inf;
    if (obj == NULL) {
      number = last->number + 1;
      break;
    }
  }
  return number;
}

DFRobot_LcdDisplay::sControlinf_t* DFRobot_LcdDisplay::creatGauge(uint16_t x, uint16_t y, uint8_t width, uint8_t height, uint16_t color)
{
  sControlinf_t* gauge = (sControlinf_t*)malloc(sizeof(sControlinf_t));
  if (gauge == NULL) {
    DBG("BAR malloc fail !");
  }
  gauge->x = x;
  gauge->y = y;
  gauge->width = width;
  gauge->height = height;
  gauge->color = color;
  gauge->id = 4;
  gauge->number = getNumber(1);
  gauge->inf = NULL;
  sControlinf_t* obj = &head;
  while (obj->inf != NULL) {
    obj = obj->inf;
  }
  obj->inf = gauge;

  uint8_t* cmd = creatCommand(CMD_DRAW_LVGLGAUGE, CMDLEN_DRAW_LVGLGAUGE);
  cmd[4] = gauge->number;
  cmd[5] = 0;
  cmd[6] = x >> 8;
  cmd[7] = x & 0xFF;
  cmd[8] = y >> 8;
  cmd[9] = y & 0xFF;
  cmd[10] = width;
  cmd[11] = height;
  cmd[12] = color >> 8;
  cmd[13] = color & 0xFF;

  writeCommand(cmd, CMDLEN_DRAW_LVGLGAUGE);
  free(cmd);

  return gauge;
}

void DFRobot_LcdDisplay::setGaugeScale(sControlinf_t* obj, uint16_t angle, int16_t start, int16_t end)
{

  uint8_t* cmd = creatCommand(CMD_DRAW_LVGLGAUGE, CMDLEN_CHANGE_LVGLGAUGE_SCALE);
  cmd[4] = obj->number;
  cmd[5] = 3;
  cmd[6] = angle >> 8;
  cmd[7] = angle & 0xFF;
  cmd[8] = 6;
  cmd[9] = 6;

  writeCommand(cmd, CMDLEN_CHANGE_LVGLGAUGE_SCALE);
  free(cmd);

  uint8_t* cmd1 = creatCommand(CMD_DRAW_LVGLGAUGE, CMDLEN_CHANGE_LVGLGAUGE_RANGE);
  cmd1[4] = obj->number;
  cmd1[5] = 1;
  cmd1[6] = start >> 8;
  cmd1[7] = start & 0xFF;
  cmd1[8] = end >> 8;
  cmd1[9] = end & 0xFF;
  writeCommand(cmd1, CMDLEN_CHANGE_LVGLGAUGE_RANGE);
  free(cmd1);
}

void DFRobot_LcdDisplay::setGaugeValue(sControlinf_t* obj, uint16_t value)
{
  uint8_t* cmd = creatCommand(CMD_DRAW_LVGLGAUGE, CMDLEN_CHANGE_LVGLGAUGE_VALUE);
  cmd[4] = obj->number;
  cmd[5] = 2;
  cmd[6] = value >> 8;
  cmd[7] = value & 0xFF;

  writeCommand(cmd, CMDLEN_CHANGE_LVGLGAUGE_VALUE);
  free(cmd);

}

DFRobot_LcdDisplay::sControlinf_t* DFRobot_LcdDisplay::creatCompass(uint16_t x, uint16_t y, uint8_t width, uint8_t height)
{

  sControlinf_t* compass = (sControlinf_t*)malloc(sizeof(sControlinf_t));
  if (compass == NULL) {
    DBG("BAR malloc fail !");
  }
  compass->x = x;
  compass->y = y;
  compass->width = width;
  compass->height = height;
  // compass->color = color;
  compass->id = 3;
  compass->number = getNumber(1);
  compass->inf = NULL;
  sControlinf_t* obj = &head;
  while (obj->inf != NULL) {
    obj = obj->inf;
  }
  obj->inf = compass;

  uint8_t* cmd = creatCommand(CMD_DRAW_LVGLCOMPASS, CMDLEN_DRAW_LVGLCOMPASS);
  cmd[4] = compass->number;
  cmd[5] = 0;
  cmd[6] = x >> 8;
  cmd[7] = x & 0xFF;
  cmd[8] = y >> 8;
  cmd[9] = y & 0xFF;
  cmd[10] = width;
  cmd[11] = height;
  cmd[12] = 0;
  cmd[13] = 0;

  writeCommand(cmd, CMDLEN_DRAW_LVGLCOMPASS);
  free(cmd);

  return compass;
}

void DFRobot_LcdDisplay::setCompassScale(sControlinf_t* obj, uint16_t scale)
{
  uint8_t* cmd = creatCommand(CMD_DRAW_LVGLCOMPASS, CMDLEN_CHANGE_LVGLCOMPASS_VALUE);
  cmd[4] = obj->number;
  cmd[5] = 1;
  cmd[6] = scale >> 8;
  cmd[7] = scale & 0xFF;

  writeCommand(cmd, CMDLEN_CHANGE_LVGLCOMPASS_VALUE);
  free(cmd);
}

DFRobot_LcdDisplay::sControlinf_t* DFRobot_LcdDisplay::creatArc(uint16_t x, uint16_t y, uint8_t width, uint8_t height)
{
  sControlinf_t* arc = (sControlinf_t*)malloc(sizeof(sControlinf_t));
  if (arc == NULL) {
    DBG("BAR malloc fail !");
  }
  arc->x = x;
  arc->y = y;
  arc->width = width;
  arc->height = height;
  arc->color = RED_RGB565;
  arc->id = 3;   
  arc->number = getNumber(1);
  arc->inf = NULL;
  sControlinf_t* obj = &head;
  while (obj->inf != NULL) {
    obj = obj->inf;
  }
  obj->inf = arc;

  uint8_t* cmd = creatCommand(CMD_DRAW_LVGLARC, CMDLEN_DRAW_LVGLARC);
  cmd[4] = arc->number;
  cmd[5] = 0;
  cmd[6] = x >> 8;
  cmd[7] = x & 0xFF;
  cmd[8] = y >> 8;
  cmd[9] = y & 0xFF;
  cmd[10] = width;
  cmd[11] = height;
  cmd[12] = arc->color >> 8;
  cmd[13] = arc->color & 0xFF;

  writeCommand(cmd, CMDLEN_DRAW_LVGLARC);
  free(cmd);

  return arc;

}

void DFRobot_LcdDisplay::setArcRotation(sControlinf_t* obj, uint16_t rotation)
{
  if (rotation > 359) rotation = 359;
  uint8_t* cmd = creatCommand(CMD_DRAW_LVGLARC, CMDLEN_CHANGE_LVGLARC_ROTATION);
  cmd[4] = obj->number;
  cmd[5] = 1;
  cmd[6] = 1;
  cmd[7] = rotation >> 8;
  cmd[8] = rotation & 0xFF;

  writeCommand(cmd, CMDLEN_CHANGE_LVGLARC_ROTATION);
  free(cmd);
}

void DFRobot_LcdDisplay::reset()
{
  uint8_t* cmd = creatCommand(CMD_RESET_LVGL, CMDLEN_RESET_LVGL);

  writeCommand(cmd, CMDLEN_RESET_LVGL);
  free(cmd);

}

uint8_t DFRobot_LcdDisplay::utf8toUnicode(uint8_t* utf8, uint16_t& uni)
{
  uint8_t lenght = 0;
  uint8_t index = 0;

  if (utf8[index] >= 0xfc) {

    uni = utf8[index] & 1;
    index++;
    for (uint8_t i = 1;i <= 5;i++) {
      uni <<= 6;
      uni |= (utf8[index] & 0x3f);

      index++;
    }
    lenght = 6;
  } else if (utf8[index] >= 0xf8) {

    uni = utf8[index] & 3;
    index++;
    for (uint8_t i = 1;i <= 4;i++) {
      uni <<= 6;
      uni |= (utf8[index] & 0x03f);

      index++;
    }
    lenght = 5;
  } else if (utf8[index] >= 0xf0) {

    uni = utf8[index] & 7;
    index++;
    for (uint8_t i = 1;i <= 3;i++) {
      uni <<= 6;
      uni |= (utf8[index] & 0x03f);
      index++;
    }
    lenght = 4;
  } else if (utf8[index] >= 0xe0) {
    uni = utf8[index] & 15;
    index++;
    for (uint8_t i = 1;i <= 2;i++) {
      uni <<= 6;
      uni |= (utf8[index] & 0x03f);
      index++;
    }
    lenght = 3;
  } else if (utf8[index] >= 0xc0) {

    uni = utf8[index] & 0x1f;
    index++;
    for (uint8_t i = 1;i <= 1;i++) {
      uni <<= 6;
      uni |= (utf8[index] & 0x03f);
      index++;


    }
    lenght = 2;
  } else if (utf8[index] <= 0x80) {
    uni = (utf8[index] & 0x7f);
    lenght = 1;

  } else {
    DBG("no this");
  }
  return lenght;
}

void DFRobot_LcdDisplay::drawStringHepler(uint16_t x, uint8_t y, uint8_t* uni, uint8_t lenght, uint8_t type, uint16_t color, uint16_t fgColor)
{


  uint8_t* cmd = creatCommand(CMD_OF_DRAWSTRING, lenght + 13);
  if (cmd == NULL) {
    DBG("cmd null");
  }
  cmd[4] = x >> 8;
  cmd[5] = x & 0xFF;
  cmd[6] = y;

  cmd[7] = type;
  cmd[8] = color >> 8;
  cmd[9] = color & 0xFF;
  cmd[10] = fgColor >> 8;
  cmd[11] = fgColor & 0xFF;
  cmd[12] = _font;
  for (uint8_t i = 0;i < lenght;i++) {
    cmd[13 + i] = uni[i];
  }
  writeCommand(cmd, lenght + 13);
  free(cmd);

}

void DFRobot_LcdDisplay::drawStringHepler(uint16_t x, uint8_t y, uint8_t* uni, uint8_t lenght, uint8_t type, uint16_t color)
{


  uint8_t* cmd = creatCommand(CMD_OF_DRAWSTRING2, lenght + 11);
  if (cmd == NULL) {
    DBG("cmd null");
  }
  cmd[4] = x >> 8;
  cmd[5] = x & 0xFF;
  cmd[6] = y;

  cmd[7] = type;
  cmd[8] = color >> 8;
  cmd[9] = color & 0xFF;
  cmd[10] = _font;
  for (uint8_t i = 0;i < lenght;i++) {
    cmd[11 + i] = uni[i];
  }
  writeCommand(cmd, lenght + 11);
  free(cmd);

}

void DFRobot_LcdDisplay::drawString(uint16_t x, uint8_t y, String str, uint8_t type, uint16_t color)
{

  uint8_t uni[36] = { 0 };

  int16_t length = str.length();
  uint8_t data[136] = { 0 };
  uint8_t* dataPtr = data;
  uint16_t unicode = 0;
  uint8_t lenght = 0;
  if (dataPtr == NULL) {
    DBG("data null");
  }
  uint16_t x1 = x;
  uint16_t y1 = y;

  for (uint8_t i = 0; i < length; i++) {
    data[i] = str[i];
  }

  while (length > 0) {
    uint8_t len1 = utf8toUnicode(dataPtr, unicode);
    length = length - len1;
    uni[lenght] = unicode >> 8;
    uni[lenght + 1] = unicode & 0xff;
    lenght += 2;

    dataPtr += len1;

    if (lenght == 20) {
      drawStringHepler(x1, y1, uni, lenght, type, color);
      lenght = 0;
      if ((type == 0) && (_font == eChinese)) {
        x1 += 10 * (25);
      } else if ((type == 1) && (_font == eChinese)) {
        x1 += 10 * (13);
      } else if ((type == 0) && (_font == eAscii)) {
        x1 += 10 * (12);
      } else if ((type == 1) && (_font == eAscii)) {
        x1 += 10 * (6);
      } else if (_font == eAlb) {
        x1 += 10 * (16);
      } else if (_font == eShiftJis || _font == eKorean || _font == eKhmer) {
        x1 += 10 * (24);
      } else {
        x1 += 10 * (8);
      }

    }
  }
  if (lenght == 0) return;
  drawStringHepler(x1, y1, uni, lenght, type, color);
}

void DFRobot_LcdDisplay::setFont(eLcdFont_t font)
{
  _font = font;
}

void DFRobot_LcdDisplay::lvglInit(uint16_t bg_color)
{
  uint8_t* cmd = creatCommand(CMD_INIT_LVGL, CMDLEN_INIT_LVGL);
  cmd[4] = 0XFF;
  cmd[5] = bg_color >> 8;
  cmd[6] = bg_color & 0xFF;
  writeCommand(cmd, CMDLEN_INIT_LVGL);
  free(cmd);
  delay(2000);
}

uint16_t DFRobot_LcdDisplay::getWordLen(uint8_t* utf8, uint8_t len)
{
  uint16_t index = 0;
  // uint32_t uni = 0;
  uint16_t length = 0;DBG("\n");
  DBG("len=");DBG(len);
  while (index < len) {
    DBG("index=");DBG(index);
    if (utf8[index] >= 0xfc) {
      index++;
      for (uint8_t i = 1;i <= 5;i++) {
        index++;
      }
      length += 1;
    } else if (utf8[index] >= 0xf8) {
      index++;
      for (uint8_t i = 1;i <= 4;i++) {
        index++;
      }
      length += 1;
    } else if (utf8[index] >= 0xf0) {
      index++;
      for (uint8_t i = 1;i <= 3;i++) {
        index++;
      }
      length += 15;
    } else if (utf8[index] >= 0xe0) {
      index++;
      for (uint8_t i = 1;i <= 2;i++) {
        index++;
      }
      length += 15;
    } else if (utf8[index] >= 0xc0) {

      index++;
      for (uint8_t i = 1;i <= 1;i++) {
        index++;
      }
      length += 9;
    } else if (utf8[index] <= 0x80) {
      index++;
      length += 9;
    }
  }
  return length;
}

DFRobot_LcdDisplay::sControlinf_t* DFRobot_LcdDisplay::creatStations(uint16_t x, uint16_t y, uint16_t zoo, uint16_t color, String str)
{
  sControlinf_t* station = (sControlinf_t*)malloc(sizeof(sControlinf_t));
  if (station == NULL) {
    DBG("BAR malloc fail !");
  }
  station->x = x;
  station->y = y;
  station->width = 100;
  station->height = 100;
  station->color = 0;
  station->id = 1;
  station->number = getNumber(1);
  station->inf = NULL;
  sControlinf_t* obj = &head;
  while (obj->inf != NULL) {
    obj = obj->inf;
  }
  obj->inf = station;

  uint8_t* cmd = creatCommand(CMD_DRAW_LVGLSTATION, CMDLEN_DRAW_LVGLSTATION);
  cmd[4] = station->number;
  cmd[5] = 1;
  cmd[6] = x >> 8;
  cmd[7] = x & 0xFF;
  cmd[8] = y >> 8;
  cmd[9] = y & 0xFF;
  cmd[10] = zoo >> 8;
  cmd[11] = zoo & 0xFF;
  cmd[12] = color >> 8;
  cmd[13] = color & 0xFF;
  writeCommand(cmd, CMDLEN_DRAW_LVGLSTATION);
  free(cmd);
  uint8_t lenght = str.length();
  for (uint8_t i = 0;i < lenght;i++) {
    wordLen[i] = str[i];
  }
  int16_t word = 0;
  if ((_font == eChinese) || (_font == eAscii)) {
    word = getWordLen(wordLen, lenght);
  } else if ((_font == eShiftJis) || (_font == eKorean)) {
    word = (lenght / 3) * 24;
  }
  int16_t zoo1 = (100 * zoo) / 256;
  int16_t x1 = x + (zoo1 - word) / 2 - (zoo1 - 100) / 2;
  int16_t y1 = y + (zoo1) / 2 + (10 * zoo) / 256 - (zoo1 - 100) / 2;
  delay(300);
  drawString(/*x=*/x1, y1, str,/*font size*/1,/*前景色*/color);
  return station;
}

void DFRobot_LcdDisplay::setStationValue(sControlinf_t* obj, String value)
{
  uint8_t len = value.length();
  uint8_t* cmd = creatCommand(CMD_DRAW_LVGLSTATION, len + 10);
  cmd[4] = obj->number;
  cmd[5] = 2;
  cmd[6] = obj->id;

  for (uint8_t i = 0;i < len;i++) {
    cmd[7 + i] = value[i];
  }
  writeCommand(cmd, len + 7);
  free(cmd);
  //return 1;
}

void DFRobot_LcdDisplay::drawString(uint16_t x, uint8_t y, String str, uint8_t type, uint16_t color, uint16_t bgColor)
{
  uint8_t uni[36] = { 0 };

  int16_t length = str.length();
  uint8_t data[136] = { 0 };
  uint8_t* dataPtr = data;
  uint16_t unicode = 0;
  uint8_t lenght = 0;
  if (dataPtr == NULL) {
    DBG("data null");
  }
  uint16_t x1 = x;
  uint16_t y1 = y;

  for (uint8_t i = 0; i < length; i++) {
    data[i] = str[i];
  }

  while (length > 0) {
    uint8_t len1 = utf8toUnicode(dataPtr, unicode);
    length = length - len1;
    uni[lenght] = unicode >> 8;
    uni[lenght + 1] = unicode & 0xff;
    lenght += 2;

    dataPtr += len1;

    if (lenght == 18) {
      drawStringHepler(x1, y1, uni, lenght, type, color, bgColor);
      lenght = 0;
      if ((type == 0) && (_font == eChinese)) {
        x1 += 9 * (25);
      } else if ((type == 1) && (_font == eChinese)) {
        x1 += 9 * (13);
      } else if ((type == 0) && (_font == eAscii)) {
        x1 += 9 * (12);
      } else if ((type == 1) && (_font == eAscii)) {
        x1 += 9 * (6);
      } else if (_font == eAlb) {
        x1 += 9 * (16);
      } else if (_font == eShiftJis || _font == eKorean || _font == eKhmer) {
        x1 += 9 * (24);
      } else {
        x1 += 9 * (8);
      }

    }
  }
  if (lenght == 0) return;
  drawStringHepler(x1, y1, uni, lenght, type, color, bgColor);

}

void DFRobot_LcdDisplay::drawLcdTime(uint8_t x, uint8_t y, uint8_t hour, uint8_t Minute, uint8_t seconds, uint8_t fontSize, uint16_t color, uint16_t bgColor)
{
  String time1 = "";

  if (hour < 10) {
    time1 += "0";
  }
  time1 += String(hour);
  time1 += ":";
  if (Minute < 10) {
    time1 += "0";
  }
  time1 += String(Minute);
  time1 += ":";
  if (seconds < 10) {
    time1 += "0";
  }
  time1 += String(seconds);

  setFont(eAscii);
  drawString(x, y, time1, fontSize, color, bgColor);
}

void DFRobot_LcdDisplay::drawLcdDate(uint8_t x, uint8_t y, uint8_t month, uint8_t day, uint8_t weeks, uint8_t fontSize, uint16_t color, uint16_t bgColor)
{
  String date = "";
  if (month < 10) {
    date += "0";
  }
  date += String(month);
  date += "月";
  if (day < 10) {
    date += "0";
  }
  date += String(day);
  date += "日 周";
  if (weeks == 1) {
    date += "一";
  } else if (weeks == 2) {
    date += "二";
  } else if (weeks == 3) {
    date += "三";
  } else if (weeks == 4) {
    date += "四";
  } else if (weeks == 5) {
    date += "五";
  } else if (weeks == 6) {
    date += "六";
  } else if (weeks == 7) {
    date += "日";
  }
  setFont(eAscii);
  drawString(x, y, date, fontSize, color, bgColor);
}

DFRobot_LcdDisplay::sControlinf_t* DFRobot_LcdDisplay::creatLineMeter(uint16_t x, uint16_t y, uint8_t width, uint8_t height, uint16_t color)
{
  sControlinf_t* lineMeter = (sControlinf_t*)malloc(sizeof(sControlinf_t));
  if (lineMeter == NULL) {
    DBG("BAR malloc fail !");
  }
  lineMeter->x = x;
  lineMeter->y = y;
  lineMeter->width = width;
  lineMeter->height = height;
  lineMeter->color = color;
  lineMeter->id = 5;
  lineMeter->number = getNumber(1);
  lineMeter->inf = NULL;
  sControlinf_t* obj = &head;
  while (obj->inf != NULL) {
    obj = obj->inf;
  }
  obj->inf = lineMeter;

  uint8_t* cmd = creatCommand(CMD_DRAW_LVGLLINEMETER, CMDLEN_DRAW_LVGLMETER);
  cmd[4] = lineMeter->number;
  cmd[5] = 0;
  cmd[6] = x >> 8;
  cmd[7] = x & 0xFF;
  cmd[8] = y >> 8;
  cmd[9] = y & 0xFF;
  cmd[10] = width;
  cmd[11] = height;
  cmd[12] = color >> 8;
  cmd[13] = color & 0xFF;

  writeCommand(cmd, CMDLEN_DRAW_LVGLMETER);
  free(cmd);

  return lineMeter;
}

DFRobot_LcdDisplay::sControlinf_t* DFRobot_LcdDisplay::creatChart(String strX, String strY, uint8_t type)
{
  sControlinf_t* chart = (sControlinf_t*)malloc(sizeof(sControlinf_t));
  if (chart == NULL) {
    DBG("BAR malloc fail !");
  }
  chart->x = 0;   // Chart position 
  chart->y = 0;
  chart->width = 320;   // Chart length and width 
  chart->height = 240;
  chart->color = 0;   
  chart->id = 1;
  chart->number = getNumber(1);

  chart->inf = NULL;
  sControlinf_t* obj = &head;
  while (obj->inf != NULL) {
    obj = obj->inf;
  }
  obj->inf = chart;

  setChartTickTexts(chart, strX, strY);
  delay(20);

  uint8_t* cmd = creatCommand(CMD_DRAW_LVGLCHART, CMDLEN_DRAW_LVGLCHART);
  cmd[4] = chart->number;
  cmd[5] = 0;   // 0 : The type of instruction to create the chart
  cmd[6] = 0;   
  cmd[7] = 0;   
  cmd[8] = chart->x;
  cmd[9] = chart->y;
  cmd[10] = (chart->width >> 8) & 0xff;
  cmd[11] = chart->width & 0xff;
  cmd[12] = chart->height;
  cmd[13] = type;


  writeCommand(cmd, CMDLEN_DRAW_LVGLCHART);
  free(cmd);

  return chart;
}

uint8_t DFRobot_LcdDisplay::creatChartSerie(sControlinf_t* obj, uint16_t color)
{

  uint8_t* cmd = creatCommand(CMD_DRAW_LVGLCHART, CMDLEN_CHANGE_LVGLCHART_SERIE);
  cmd[4] = obj->number;
  cmd[5] = 1;   // 1 : Type of instruction to create a chart series
  cmd[6] = obj->id;
  obj->id = obj->id + 1;
  cmd[7] = color >> 8;
  cmd[8] = color & 0xFF;

  writeCommand(cmd, CMDLEN_CHANGE_LVGLCHART_SERIE);
  free(cmd);

  return cmd[6];
}

uint8_t DFRobot_LcdDisplay::setChartTickTexts(sControlinf_t* obj, String xtext, String ytext)
{
  uint8_t len_x = xtext.length();
  uint8_t len_y = ytext.length();
  uint8_t* cmd = creatCommand(CMD_DRAW_LVGLCHART, len_x + 7);
  cmd[4] = obj->number;
  cmd[5] = 3;   // 3 : The type of instruction that stores label information
  cmd[6] = 1;   // Add the X-axis label
  for (uint8_t i = 0;i < len_x;i++) {
    cmd[7 + i] = xtext[i];
  }
  writeCommand(cmd, len_x + 7);
  free(cmd);


  delay(10);

  uint8_t* cmd1 = creatCommand(CMD_DRAW_LVGLCHART, len_y + 7);
  cmd1[4] = obj->number;
  cmd1[5] = 3;
  cmd1[6] = 2;   // Add the Y-axis label
  for (uint8_t i = 0;i < len_y;i++) {
    cmd1[7 + i] = ytext[i];
  }

  writeCommand(cmd1, len_y + 7);
  free(cmd1);
  return 1;
}

uint8_t DFRobot_LcdDisplay::addChartPoint(sControlinf_t* obj, uint8_t id, uint16_t value)
{
  uint8_t* cmd = creatCommand(CMD_DRAW_LVGLCHART, CMDLEN_CHANGE_LVGLCHART_POINT);
  cmd[4] = obj->number;
  cmd[5] = 2;   // 2 : Added instruction type for chart series points
  cmd[6] = id;
  cmd[7] = value >> 8;
  cmd[8] = value & 0xFF;

  writeCommand(cmd, CMDLEN_CHANGE_LVGLCHART_POINT);
  free(cmd);
  return 1;
}

uint8_t DFRobot_LcdDisplay::addChart(sControlinf_t* obj, uint8_t id, uint16_t point[], uint8_t len)
{

  for (uint8_t i = 0; i < len;i++) {
    addChartPoint(obj, id, point[i]);
    delay(200);
  }
  return 1;
}

void DFRobot_LcdDisplay::setMeterValue(sControlinf_t* obj, uint16_t value)
{

  uint8_t* cmd = creatCommand(CMD_DRAW_LVGLLINEMETER, CMDLEN_CHANGE_LVGLMETER_VALUE);
  cmd[4] = obj->number;
  cmd[5] = 2;
  cmd[6] = value >> 8;
  cmd[7] = value & 0xFF;

  writeCommand(cmd, CMDLEN_CHANGE_LVGLMETER_VALUE);
  free(cmd);
}

void DFRobot_LcdDisplay::setMeterScale(sControlinf_t* obj, uint16_t angle, int16_t start, int16_t end)
{
  uint8_t* cmd = creatCommand(CMD_DRAW_LVGLLINEMETER, CMDLEN_CHANGE_LVGLMETER_SCALE);
  cmd[4] = obj->number;
  cmd[5] = 3;
  cmd[6] = angle >> 8;
  cmd[7] = angle & 0xFF;
  cmd[8] = 18;

  writeCommand(cmd, CMDLEN_CHANGE_LVGLMETER_SCALE);
  free(cmd);

  uint8_t* cmd1 = creatCommand(CMD_DRAW_LVGLLINEMETER, CMDLEN_CHANGE_LVGLMETER_RANGE);
  cmd1[4] = obj->number;
  cmd1[5] = 1;
  cmd1[6] = start >> 8;
  cmd1[7] = start & 0xFF;
  cmd1[8] = end >> 8;
  cmd1[9] = end & 0xFF;
  writeCommand(cmd1, CMDLEN_CHANGE_LVGLMETER_RANGE);
  free(cmd1);
}

void DFRobot_LcdDisplay::lvglDelete(sControlinf_t* obj)
{
  if (obj == NULL) {
    DBG("NULL pointer");
    return;
  }
  uint8_t* cmd = creatCommand(CMD_DEINIT_LVGL, CMDLEN_DEINIT_LVGL);
  cmd[4] = obj->number;
  writeCommand(cmd, CMDLEN_DEINIT_LVGL);
  free(cmd);

  // uint16_t number = 1;
  sControlinf_t* objDel = &head;
  sControlinf_t* last;
  while (objDel->inf != NULL) {
    last = objDel;
    objDel = objDel->inf;
    if (obj->number == objDel->number) {
      last->inf = objDel->inf;
      free(objDel);
      break;
    }
  }
  delay(500);   // Make sure to delete succeed

}

uint8_t* DFRobot_LcdDisplay::creatCommand(uint8_t cmd, uint8_t len)
{
  uint8_t* data = (uint8_t*)malloc(sizeof(uint8_t) * len);
  if (data == NULL) {
    DBG("malloc FAIL");
    return NULL;
  }
  data[0] = CMD_HEADER_HIGH;
  data[1] = CMD_HEADER_LOW;
  data[2] = len - CMDLEN_OF_HEAD_LEN;
  data[3] = cmd;
  return data;
}

DFRobot_Lcd_IIC::DFRobot_Lcd_IIC(TwoWire* pWire, uint8_t addr)
{
  _deviceAddr = addr;
  _pWire = pWire;

}

bool DFRobot_Lcd_IIC::begin()
{
  _pWire->begin();
  if (_pWire == NULL) return false;
  _pWire->begin();
  _pWire->setClock(100000);
  _pWire->beginTransmission(_deviceAddr);
  if (_pWire->endTransmission() != 0) return false;

  setBackLight(true);
  return true;
}

void DFRobot_Lcd_IIC::writeCommand(uint8_t* pBuf, uint16_t len)
{

  if (pBuf == NULL) {
    DBG("pBuf ERROR!! : null pointer");
  }

  DBG(len);
  uint8_t* _pBuf = (uint8_t*)pBuf;
  _pWire->beginTransmission(_deviceAddr);
  _pWire->write(_pBuf, len);
  _pWire->write(0xAA);
  _pWire->write(0x55);
  _pWire->endTransmission();
  delay(50);

}

void DFRobot_Lcd_IIC::readACK(uint8_t* pBuf, uint16_t len)
{
  if (pBuf == NULL) {
    DBG("pBuf ERROR!! : null pointer");
  }
  uint8_t* _pBuf = (uint8_t*)pBuf;
  _pWire->requestFrom(_deviceAddr, (uint8_t)len);
  for (uint16_t i = 0; i < len; i++) {

    _pBuf[i] = _pWire->read();
  }

}


DFRobot_Lcd_UART::DFRobot_Lcd_UART(Stream& s)
{
  _s = &s;
}

bool DFRobot_Lcd_UART::begin()
{
  // warning: the compiler can assume that the address of 's' will never be NULL
  if (_s == NULL) {
    return false;
  }
  return true;
}

void DFRobot_Lcd_UART::writeCommand(uint8_t* pBuf, uint16_t len)
{
  uint8_t* _pBuf = (uint8_t*)pBuf;
  _s->write((uint8_t*)_pBuf, len);
  delay(50);
}

void DFRobot_Lcd_UART::readACK(uint8_t* pBuf, uint16_t len)
{
  LCD_UNUSED(pBuf);
  LCD_UNUSED(len);

  long long current = millis();

  while (true) {

    if (_s->available()) {
      uint8_t data = _s->read();
      LCD_UNUSED(data);
    }
    if ((millis() - current) > 1000) break;
  }
  DBG("read error");
}
