/*!
 * @file DFRobot_LcdDisplay.cpp
 * @brief Define the infrastructure of the DFRobot_LcdDisplay class
 * @details This library can drive the DFR0997 display, and it can easily drive the color screen through both the I2C interface and UART interface
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @License     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @maintainer [qsjhyy](yihuan.huang@dfrobot.com)
 * @maintainer [GDuang](yonglei.ren@dfrobot.com)
 * @version  V2.0
 * @date  2024-03-20
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

void DFRobot_LcdDisplay::drawPixel(int16_t x, int16_t y, uint32_t color)
{
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_PIXEL, CMD_DRAW_PIXEL_LEN);
  if (320 <= x) {
    x = 319;
  }
  if (240 <= y) {
    y = 239;
  }
  cmd[4] = color >> 16;
  cmd[5] = color >> 8;
  cmd[6] = color & 0xFF;
  cmd[7] = x >> 8;
  cmd[8] = x & 0xFF;
  cmd[9] = y >> 8;
  cmd[10] = y & 0xFF;
  /*
  cmd[4] = x >> 8;
  cmd[5] = x & 0xFF;
  cmd[6] = y >> 8;
  cmd[7] = y & 0xFF;
  cmd[8] = color >> 16;
  cmd[9] = color >> 8;
  cmd[10] = color & 0xFF;
  */
  writeCommand(cmd, CMD_DRAW_PIXEL_LEN);
  free(cmd);
}

void DFRobot_LcdDisplay::cleanScreen()
{
  uint8_t* cmd = creatCommand(0x1D, 0x04);
  writeCommand(cmd, 4);
  delay(1500);
  free(cmd);
}

uint8_t DFRobot_LcdDisplay::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint8_t width, uint32_t color)
{
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_LINE, CMD_DRAW_LINE_LEN);
  uint8_t id = getID(CMD_OF_DRAW_LINE);
  cmd[4] = id;
  cmd[5] = width;
  cmd[6] = color >> 16;
  cmd[7] = color >> 8;
  cmd[8] = color & 0xFF;
  cmd[9] = x0 >> 8;
  cmd[10] = x0 & 0xFF;
  cmd[11] = y0 >> 8;
  cmd[12] = y0 & 0xFF;
  cmd[13] = x1 >> 8;
  cmd[14] = x1 & 0xFF;
  cmd[15] = y1 >> 8;
  cmd[16] = y1 & 0xFF;
  writeCommand(cmd, CMD_DRAW_LINE_LEN);
  free(cmd);
  return id;
}

void DFRobot_LcdDisplay::updateLine(uint8_t id, int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint8_t width, uint32_t color){
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_LINE, CMD_DRAW_LINE_LEN);
  cmd[4] = id;
  cmd[5] = width;
  cmd[6] = color >> 16;
  cmd[7] = color >> 8;
  cmd[8] = color & 0xFF;
  cmd[9] = x0 >> 8;
  cmd[10] = x0 & 0xFF;
  cmd[11] = y0 >> 8;
  cmd[12] = y0 & 0xFF;
  cmd[13] = x1 >> 8;
  cmd[14] = x1 & 0xFF;
  cmd[15] = y1 >> 8;
  cmd[16] = y1 & 0xFF;
  writeCommand(cmd, CMD_DRAW_LINE_LEN);
  delay(10);
  free(cmd);
}

void DFRobot_LcdDisplay::deleteLine(uint8_t id){
  uint8_t* cmd = creatCommand(CMD_DELETE_OBJ, CMD_DELETE_OBJ_LEN);
  cmd[4] = CMD_OF_DRAW_LINE;
  cmd[5] = id;
  writeCommand(cmd, CMD_DELETE_OBJ_LEN);
  free(cmd);
  deleteNodeByID((GenericNode**)&line_head,id);
}

uint8_t DFRobot_LcdDisplay::drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t borderWidth, uint32_t borderColor, uint8_t fill, uint32_t fillColor, uint8_t rounded)
{
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_RECT, CMD_OF_DRAW_RECT_LEN);
  uint8_t id = getID(CMD_OF_DRAW_RECT);
  cmd[4] = id;
  cmd[5] = borderWidth;
  cmd[6] = borderColor >> 16;
  cmd[7] = borderColor >> 8;
  cmd[8] = borderColor & 0xFF;
  cmd[9] = fill;
  cmd[10] = fillColor >> 16;
  cmd[11] = fillColor >> 8;
  cmd[12] = fillColor & 0xFF;
  cmd[13] = rounded;
  cmd[14] = x >> 8;
  cmd[15] = x & 0xFF;
  cmd[16] = y >> 8;
  cmd[17] = y & 0xFF;
  cmd[18] = w >> 8;
  cmd[19] = w & 0xFF;
  cmd[20] = h >> 8;
  cmd[21] = h & 0xFF;
  writeCommand(cmd, CMD_OF_DRAW_RECT_LEN);
  free(cmd);
  return id;
}

void DFRobot_LcdDisplay::updateRect(uint8_t id, int16_t x, int16_t y, int16_t w, int16_t h, uint8_t borderWidth, uint32_t borderColor, uint8_t fill, uint32_t fillColor, uint8_t rounded)
{
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_RECT, CMD_OF_DRAW_RECT_LEN);
  cmd[4] = id;
  cmd[5] = borderWidth;
  cmd[6] = borderColor >> 16;
  cmd[7] = borderColor >> 8;
  cmd[8] = borderColor & 0xFF;
  cmd[9] = fill;
  cmd[10] = fillColor >> 16;
  cmd[11] = fillColor >> 8;
  cmd[12] = fillColor & 0xFF;
  cmd[13] = rounded;
  cmd[14] = x >> 8;
  cmd[15] = x & 0xFF;
  cmd[16] = y >> 8;
  cmd[17] = y & 0xFF;
  cmd[18] = w >> 8;
  cmd[19] = w & 0xFF;
  cmd[20] = h >> 8;
  cmd[21] = h & 0xFF;
  writeCommand(cmd, CMD_OF_DRAW_RECT_LEN);
  free(cmd);
}

void DFRobot_LcdDisplay::deleteRect(uint8_t id){
  uint8_t* cmd = creatCommand(CMD_DELETE_OBJ, CMD_DELETE_OBJ_LEN);
  cmd[4] = CMD_OF_DRAW_RECT;
  cmd[5] = id;
  writeCommand(cmd, CMD_DELETE_OBJ_LEN);
  free(cmd);
  deleteNodeByID((GenericNode**)&rect_head,id);
}

uint8_t DFRobot_LcdDisplay::drawCircle(int16_t x, int16_t y, int16_t r, uint8_t borderWidth, uint32_t borderColor, uint8_t fill, uint32_t fillColor)
{
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_CIRCLE, CMD_OF_DRAW_CIRCLE_LEN);
  uint8_t id = getID(CMD_OF_DRAW_CIRCLE);
  cmd[4] = id;
  cmd[5] = borderWidth;
  cmd[6] = borderColor >> 16;
  cmd[7] = borderColor >> 8;
  cmd[8] = borderColor & 0xFF;
  cmd[9] = fill;
  cmd[10] = fillColor >> 16;
  cmd[11] = fillColor >> 8;
  cmd[12] = fillColor & 0xFF;
  cmd[13] = r >> 8;
  cmd[14] = r & 0xFF;
  cmd[15] = x >> 8;
  cmd[16] = x & 0xFF;
  cmd[17] = y >> 8;
  cmd[18] = y & 0xFF;
  writeCommand(cmd, CMD_OF_DRAW_CIRCLE_LEN);
  free(cmd);
  return id;
}

void DFRobot_LcdDisplay::updateCircle(uint8_t id, int16_t x, int16_t y, int16_t r, uint8_t borderWidth, uint32_t borderColor, uint8_t fill, uint32_t fillColor)
{
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_CIRCLE, CMD_OF_DRAW_CIRCLE_LEN);
  cmd[4] = id;
  cmd[5] = borderWidth;
  cmd[6] = borderColor >> 16;
  cmd[7] = borderColor >> 8;
  cmd[8] = borderColor & 0xFF;
  cmd[9] = fill;
  cmd[10] = fillColor >> 16;
  cmd[11] = fillColor >> 8;
  cmd[12] = fillColor & 0xFF;
  cmd[13] = r >> 8;
  cmd[14] = r & 0xFF;
  cmd[15] = x >> 8;
  cmd[16] = x & 0xFF;
  cmd[17] = y >> 8;
  cmd[18] = y & 0xFF;
  writeCommand(cmd, CMD_OF_DRAW_CIRCLE_LEN);
  free(cmd);
}

void DFRobot_LcdDisplay::deleteCircle(uint8_t id){
  uint8_t* cmd = creatCommand(CMD_DELETE_OBJ, CMD_DELETE_OBJ_LEN);
  cmd[4] = CMD_OF_DRAW_CIRCLE;
  cmd[5] = id;
  writeCommand(cmd, CMD_DELETE_OBJ_LEN);
  free(cmd);
  deleteNodeByID((GenericNode**)&circle_head,id);
}

uint8_t DFRobot_LcdDisplay::drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
  int16_t x2, int16_t y2, uint8_t borderWidth, uint32_t borderColor, uint8_t fill, uint32_t fillColor)
{
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_TRIANGLE, CMD_OF_DRAW_TRIANGLE_LEN);
  uint8_t id = getID(CMD_OF_DRAW_TRIANGLE);
  cmd[4] = id;
  cmd[5] = borderWidth;
  cmd[6] = borderColor >> 16;
  cmd[7] = borderColor >> 8;
  cmd[8] = borderColor & 0xFF;
  cmd[9] = fill;
  cmd[10] = fillColor >> 16;
  cmd[11] = fillColor >> 8;
  cmd[12] = fillColor & 0xFF;
  cmd[13] = x0 >> 8;
  cmd[14] = x0 & 0xFF;
  cmd[15] = y0 >> 8;
  cmd[16] = y0 & 0xFF;
  cmd[17] = x1 >> 8;
  cmd[18] = x1 & 0xFF;
  cmd[19] = y1 >> 8;
  cmd[20] = y1 & 0xFF;
  cmd[21] = x2 >> 8;
  cmd[22] = x2 & 0xFF;
  cmd[23] = y2 >> 8;
  cmd[24] = y2 & 0xFF;
  writeCommand(cmd, CMD_OF_DRAW_TRIANGLE_LEN);
  free(cmd);
  return id;
}

void DFRobot_LcdDisplay::updateTriangle(uint8_t id, int16_t x0, int16_t y0, int16_t x1, int16_t y1,
  int16_t x2, int16_t y2, uint8_t borderWidth, uint32_t borderColor, uint8_t fill, uint32_t fillColor)
{
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_TRIANGLE, CMD_OF_DRAW_TRIANGLE_LEN);
  cmd[4] = id;
  cmd[5] = borderWidth;
  cmd[6] = borderColor >> 16;
  cmd[7] = borderColor >> 8;
  cmd[8] = borderColor & 0xFF;
  cmd[9] = fill;
  cmd[10] = fillColor >> 16;
  cmd[11] = fillColor >> 8;
  cmd[12] = fillColor & 0xFF;
  cmd[13] = x0 >> 8;
  cmd[14] = x0 & 0xFF;
  cmd[15] = y0 >> 8;
  cmd[16] = y0 & 0xFF;
  cmd[17] = x1 >> 8;
  cmd[18] = x1 & 0xFF;
  cmd[19] = y1 >> 8;
  cmd[20] = y1 & 0xFF;
  cmd[21] = x2 >> 8;
  cmd[22] = x2 & 0xFF;
  cmd[23] = y2 >> 8;
  cmd[24] = y2 & 0xFF;
  writeCommand(cmd, CMD_OF_DRAW_TRIANGLE_LEN);
  free(cmd);
}

void DFRobot_LcdDisplay::deleteTriangle(uint8_t id){
  uint8_t* cmd = creatCommand(CMD_DELETE_OBJ, CMD_DELETE_OBJ_LEN);
  cmd[4] = CMD_OF_DRAW_TRIANGLE;
  cmd[5] = id;
  writeCommand(cmd, CMD_DELETE_OBJ_LEN);
  free(cmd);
  deleteNodeByID((GenericNode**)&triangle_head,id);
}

uint8_t DFRobot_LcdDisplay::drawIcon(int16_t x, int16_t y, uint16_t iconNum, uint16_t size)
{
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_ICON_INTERNAL, CMD_OF_DRAW_ICON_INTERNAL_LEN);
  uint8_t id = getID(CMD_OF_DRAW_ICON_INTERNAL);
  cmd[4] = id;
  cmd[5] = iconNum >> 8;
  cmd[6] = iconNum & 0xFF;
  cmd[7] = size >> 8;
  cmd[8] = size & 0xFF;
  cmd[9] = x >> 8;
  cmd[10] = x & 0xFF;
  cmd[11] = y >> 8;
  cmd[12] = y & 0xFF;
  writeCommand(cmd, CMD_OF_DRAW_ICON_INTERNAL_LEN);
  free(cmd);
  return id;
}

uint8_t DFRobot_LcdDisplay::drawIcon(int16_t x, int16_t y, String str, uint16_t zoom){
  const char* data = str.c_str();
  uint8_t length = strlen(data);
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_ICON_EXTERNAL, length + 11);
  uint8_t id = getID(CMD_OF_DRAW_ICON_INTERNAL);
  cmd[4] = id;
  cmd[5] = zoom >> 8;
  cmd[6] = zoom & 0xFF;
  cmd[7] = x >> 8;
  cmd[8] = x & 0xFF;
  cmd[9] = y >> 8;
  cmd[10] = y & 0xFF;
  memcpy(cmd+11, data, length);
  writeCommand(cmd, length + 11);
  free(cmd);
  return id;
}

void DFRobot_LcdDisplay::setAngleIcon(uint8_t id, int16_t angle){
  uint8_t* cmd = creatCommand(CMD_SET_ANGLE_OBJ, CMD_SET_ANGLE_OBJ_LEN);
  cmd[4] = CMD_OF_DRAW_ICON_INTERNAL;
  cmd[5] = id;
  cmd[6] = angle >> 8;
  cmd[7] = angle & 0xFF;
  writeCommand(cmd, CMD_SET_ANGLE_OBJ_LEN);
  free(cmd);
}

void DFRobot_LcdDisplay::updateIcon(uint8_t iconId, int16_t x, int16_t y, uint16_t iconNum, uint16_t size)
{
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_ICON_INTERNAL, CMD_OF_DRAW_ICON_INTERNAL_LEN);
  cmd[4] = iconId;
  cmd[5] = iconNum >> 8;
  cmd[6] = iconNum & 0xFF;
  cmd[7] = size >> 8;
  cmd[8] = size & 0xFF;
  cmd[9] = x >> 8;
  cmd[10] = x & 0xFF;
  cmd[11] = y >> 8;
  cmd[12] = y & 0xFF;
  writeCommand(cmd, CMD_OF_DRAW_ICON_INTERNAL_LEN);
  free(cmd);
}

void DFRobot_LcdDisplay::updateIcon(uint8_t iconId, int16_t x, int16_t y, String str, uint16_t zoom){
  const char* data = str.c_str();
  uint8_t length = strlen(data);
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_ICON_EXTERNAL, length + 11);
  cmd[4] = iconId;
  cmd[5] = zoom >> 8;
  cmd[6] = zoom & 0xFF;
  cmd[7] = x >> 8;
  cmd[8] = x & 0xFF;
  cmd[9] = y >> 8;
  cmd[10] = y & 0xFF;
  memcpy(cmd+11, data, length);
  writeCommand(cmd, length + 11);
  free(cmd);
}

void DFRobot_LcdDisplay::deleteIcon(uint8_t id){
  uint8_t* cmd = creatCommand(CMD_DELETE_OBJ, CMD_DELETE_OBJ_LEN);
  cmd[4] = CMD_OF_DRAW_ICON_INTERNAL;
  cmd[5] = id;
  writeCommand(cmd, CMD_DELETE_OBJ_LEN);
  free(cmd);
  deleteNodeByID((GenericNode**)&icon_head, id);
}

uint8_t DFRobot_LcdDisplay::drawGif(int16_t x, int16_t y, uint16_t gifNum, uint16_t size)
{
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_GIF_INTERNAL, CMD_OF_DRAW_GIF_INTERNAL_LEN);
  uint8_t id = getID(CMD_OF_DRAW_GIF_INTERNAL);
  cmd[4] = id;
  cmd[5] = gifNum >> 8;
  cmd[6] = gifNum & 0xFF;
  cmd[7] = size >> 8;
  cmd[8] = size & 0xFF;
  cmd[9] = x >> 8;
  cmd[10] = x & 0xFF;
  cmd[11] = y >> 8;
  cmd[12] = y & 0xFF;
  writeCommand(cmd, CMD_OF_DRAW_GIF_INTERNAL_LEN);
  free(cmd);
  return id;
}

uint8_t DFRobot_LcdDisplay::drawGif(int16_t x, int16_t y, String str, uint16_t zoom)
{
  const char* data = str.c_str();
  uint8_t length = strlen(data);
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_GIF_EXTERNAL, length + 11);
  uint8_t id = getID(CMD_OF_DRAW_GIF_INTERNAL);
  cmd[4] = id;
  cmd[5] = zoom >> 8;
  cmd[6] = zoom & 0xFF;
  cmd[7] = x >> 8;
  cmd[8] = x & 0xFF;
  cmd[9] = y >> 8;
  cmd[10] = y & 0xFF;
  memcpy(cmd+11, data, length);
  writeCommand(cmd, length + 11);
  free(cmd);
  return id;
}

void DFRobot_LcdDisplay::deleteGif(uint8_t id){
  uint8_t* cmd = creatCommand(CMD_DELETE_OBJ, CMD_DELETE_OBJ_LEN);
  cmd[4] = CMD_OF_DRAW_GIF_INTERNAL;
  cmd[5] = id;
  writeCommand(cmd, CMD_DELETE_OBJ_LEN);
  free(cmd);
  deleteNodeByID((GenericNode**)&gif_head, id);
}

uint8_t DFRobot_LcdDisplay::creatSlider(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color)
{
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_SLIDER, CMD_OF_DRAW_SLIDER_LEN);
  uint8_t id = getID(CMD_OF_DRAW_SLIDER);
  cmd[4] = id;
  cmd[5] = color >> 16;
  cmd[6] = color >> 8;
  cmd[7] = color & 0xFF;
  cmd[8] = x >> 8;
  cmd[9] = x & 0xFF;
  cmd[10] = y >> 8;
  cmd[11] = y & 0xFF;
  cmd[12] = width >> 8;
  cmd[13] = width & 0xFF;
  cmd[14] = height >> 8;
  cmd[15] = height & 0xFF;
  writeCommand(cmd, CMD_OF_DRAW_SLIDER_LEN);
  free(cmd);
  return id;
}

void DFRobot_LcdDisplay::updateSlider(uint8_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color)
{
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_SLIDER, CMD_OF_DRAW_SLIDER_LEN);
  cmd[4] = id;
  cmd[5] = color >> 16;
  cmd[6] = color >> 8;
  cmd[7] = color & 0xFF;
  cmd[8] = x >> 8;
  cmd[9] = x & 0xFF;
  cmd[10] = y >> 8;
  cmd[11] = y & 0xFF;
  cmd[12] = width >> 8;
  cmd[13] = width & 0xFF;
  cmd[14] = height >> 8;
  cmd[15] = height & 0xFF;
  writeCommand(cmd, CMD_OF_DRAW_SLIDER_LEN);
  free(cmd);
}

void DFRobot_LcdDisplay::setSliderValue(uint8_t sliderId, uint16_t value)
{
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_SLIDER_VALUE, CMD_SET_SLIDER_VALUE_LEN);
  cmd[4] = sliderId;
  cmd[5] = value >> 8;
  cmd[6] = value & 0xFF;
  writeCommand(cmd, CMD_SET_SLIDER_VALUE_LEN);
  free(cmd);
}

void DFRobot_LcdDisplay::deleteSlider(uint8_t id){
  uint8_t* cmd = creatCommand(CMD_DELETE_OBJ, CMD_DELETE_OBJ_LEN);
  cmd[4] = CMD_OF_DRAW_SLIDER;
  cmd[5] = id;
  writeCommand(cmd, CMD_DELETE_OBJ_LEN);
  free(cmd);
  deleteNodeByID((GenericNode**)&slider_head, id);
}

uint8_t DFRobot_LcdDisplay::creatBar(uint16_t x, uint16_t y, uint16_t width, uint8_t height, uint32_t color)
{
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_BAR, CMD_OF_DRAW_BAR_LEN);
  uint8_t id = getID(CMD_OF_DRAW_BAR);
  cmd[4] = id;
  cmd[5] = color >> 16;
  cmd[6] = color >> 8;
  cmd[7] = color & 0xFF;
  cmd[8] = x >> 8;
  cmd[9] = x & 0xFF;
  cmd[10] = y >> 8;
  cmd[11] = y & 0xFF;
  cmd[12] = width >> 8;
  cmd[13] = width & 0xFF;
  cmd[14] = height >> 8;
  cmd[15] = height & 0xFF;
  writeCommand(cmd, CMD_OF_DRAW_BAR_LEN);
  free(cmd);
  return id;
}

void DFRobot_LcdDisplay::updateBar(uint8_t id, uint16_t x, uint16_t y, uint16_t width, uint8_t height, uint32_t color)
{
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_BAR, CMD_OF_DRAW_BAR_LEN);
  cmd[4] = id;
  cmd[5] = color >> 16;
  cmd[6] = color >> 8;
  cmd[7] = color & 0xFF;
  cmd[8] = x >> 8;
  cmd[9] = x & 0xFF;
  cmd[10] = y >> 8;
  cmd[11] = y & 0xFF;
  cmd[12] = width >> 8;
  cmd[13] = width & 0xFF;
  cmd[14] = height >> 8;
  cmd[15] = height & 0xFF;
  writeCommand(cmd, CMD_OF_DRAW_BAR_LEN);
  free(cmd);
}

void DFRobot_LcdDisplay::setBarValue(uint8_t barId, uint16_t value)
{
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_BAR_VALUE, CMD_SET_BAR_VALUE_LEN);
  if (cmd == NULL) {
    DBG("cmd null");
    return;
  }
  cmd[4] = barId;
  cmd[5] = value >> 8;
  cmd[6] = value;
  writeCommand(cmd, CMD_SET_BAR_VALUE_LEN);
  free(cmd);
}

void DFRobot_LcdDisplay::deleteBar(uint8_t id){
  uint8_t* cmd = creatCommand(CMD_DELETE_OBJ, CMD_DELETE_OBJ_LEN);
  cmd[4] = CMD_OF_DRAW_BAR;
  cmd[5] = id;
  writeCommand(cmd, CMD_DELETE_OBJ_LEN);
  free(cmd);
  deleteNodeByID((GenericNode**)&bar_head,id);
}

uint8_t DFRobot_LcdDisplay:: getNewID(sGenericNode_t** head) {
    uint8_t id = 1;
    sGenericNode_t* temp = *head;
    if(temp == NULL){}

    while (temp) {
        id = temp->id + 1; 
        if (!temp->next) {
            break;
        }
        temp = (sGenericNode_t*)temp->next;
    }

    sGenericNode_t* new_node = (sGenericNode_t*)malloc(sizeof(sGenericNode_t));
    if (new_node) {
        new_node->id = id;
        new_node->next = NULL;

        if (temp) {
            temp->next = new_node;
        } else {
            *head = new_node;
        }
    } else {
        id = 0; 
    }
    return id;
}

void DFRobot_LcdDisplay::deleteNodeByID(sGenericNode_t** head, uint8_t id) {
    if (head == NULL || *head == NULL) {
        return;
    }
    sGenericNode_t* temp = *head;
    sGenericNode_t* prev = NULL;

    if (temp != NULL && temp->id == id) {
        // *head = temp->next; 
        *head = static_cast<DFRobot_LcdDisplay::sGenericNode_t*>(temp->next);
        free(temp); 
        if (*head == NULL) {
            return;
        }
    } else {
        while (temp != NULL && temp->id != id) {
            prev = temp;
            temp = (sGenericNode_t*)temp->next;
        }
        if (temp == NULL) return;

        prev->next = temp->next;

        free(temp);
    }

    if (*head == NULL) {
        return;
    }

    temp = *head;
    while (temp) {
        if (temp->next != NULL) {
            return; 
        }
        temp = (sGenericNode_t*)temp->next;
    }
    
    *head = NULL;
}

uint8_t DFRobot_LcdDisplay::getID(uint8_t type)
{
  LCD_UNUSED(type);
  uint8_t id = 0;
  switch(type){
    case CMD_OF_DRAW_LINE_CHART:
      id = getNewID((GenericNode**)&line_chart_head);
      break;
    case CMD_OF_DRAW_SERIE:
      id = getNewID((GenericNode**)&series_head);
      break;
    case CMD_OF_DRAW_COMPASS:
      id = getNewID((GenericNode**)&compass_head);
      break;
    case CMD_OF_DRAW_TEXT:
      id = getNewID((GenericNode**)&text_head);
      break;
    case CMD_OF_DRAW_GAUGE:
      id = getNewID((GenericNode**)&gauge_head);
      break;
    case CMD_OF_DRAW_LINE:
      id = getNewID((GenericNode**)&line_head);
      break;
    case CMD_OF_DRAW_RECT:
      id = getNewID((GenericNode**)&rect_head);
      break;
    case CMD_OF_DRAW_TRIANGLE:
      id = getNewID((GenericNode**)&triangle_head);
      break;
    case CMD_OF_DRAW_CIRCLE:
      id = getNewID((GenericNode**)&circle_head);
      break;
    case CMD_OF_DRAW_LINE_METER:
      id = getNewID((GenericNode**)&lineMeter_head);
      break;
    case CMD_OF_DRAW_BAR:
      id = getNewID((GenericNode**)&bar_head);
      break;
    case CMD_OF_DRAW_SLIDER:
      id = getNewID((GenericNode**)&slider_head);
      break;
    case CMD_OF_DRAW_ICON_INTERNAL:
      id = getNewID((GenericNode**)&icon_head);
      break;
    case CMD_OF_DRAW_GIF_INTERNAL:
      id = getNewID((GenericNode**)&gif_head);
      break;
    default:
      break;
  }
  return id;
}

uint8_t DFRobot_LcdDisplay::creatGauge(uint16_t x, uint16_t y, uint16_t diameter, uint16_t start, uint16_t end, uint32_t pointerColor, uint32_t bgColor)
{
  uint8_t id = getID(CMD_OF_DRAW_GAUGE);
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_GAUGE, CMD_OF_DRAW_GAUGE_LEN);
  cmd[4] = id;
  cmd[5] = diameter >> 8;
  cmd[6] = diameter & 0xFF;
  cmd[7] = start >> 8;
  cmd[8] = start & 0xFF;
  cmd[9] = end >> 8;
  cmd[10] = end & 0xFF;
  cmd[11] = pointerColor >>16;
  cmd[12] = pointerColor >> 8;
  cmd[13] = pointerColor & 0xFF;
  cmd[14] = bgColor >>16;
  cmd[15] = bgColor >> 8;
  cmd[16] = bgColor & 0xFF;
  cmd[17] = x >> 8;
  cmd[18] = x & 0xFF;
  cmd[19] = y >> 8;
  cmd[20] = y & 0xFF;
  writeCommand(cmd, CMD_OF_DRAW_GAUGE_LEN);
  free(cmd);
 return id;
}

void DFRobot_LcdDisplay::updateGauge(uint8_t id, uint16_t x, uint16_t y, uint16_t diameter, uint16_t start, uint16_t end, uint32_t pointerColor, uint32_t bgColor)
{
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_GAUGE, CMD_OF_DRAW_GAUGE_LEN);
  cmd[4] = id;
  cmd[5] = diameter >> 8;
  cmd[6] = diameter & 0xFF;
  cmd[7] = start >> 8;
  cmd[8] = start & 0xFF;
  cmd[9] = end >> 8;
  cmd[10] = end & 0xFF;
  cmd[11] = pointerColor >>16;
  cmd[12] = pointerColor >> 8;
  cmd[13] = pointerColor & 0xFF;
  cmd[14] = bgColor >>16;
  cmd[15] = bgColor >> 8;
  cmd[16] = bgColor & 0xFF;
  cmd[17] = x >> 8;
  cmd[18] = x & 0xFF;
  cmd[19] = y >> 8;
  cmd[20] = y & 0xFF;
  writeCommand(cmd, CMD_OF_DRAW_GAUGE_LEN);
  free(cmd);
}

void DFRobot_LcdDisplay::setGaugeValue(uint8_t gaugeId, uint16_t value)
{
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_GAUGE_VALUE, CMD_SET_GAUGE_VALUE_LEN);
  cmd[4] = gaugeId;
  cmd[5] = value >> 8;
  cmd[6] = value & 0xFF;
  writeCommand(cmd, CMD_SET_GAUGE_VALUE_LEN);
  free(cmd);
}

void DFRobot_LcdDisplay::deleteGauge(uint8_t id){
  uint8_t* cmd = creatCommand(CMD_DELETE_OBJ, CMD_DELETE_OBJ_LEN);
  cmd[4] = CMD_OF_DRAW_GAUGE;
  cmd[5] = id;
  writeCommand(cmd, CMD_DELETE_OBJ_LEN);
  free(cmd);
  deleteNodeByID((GenericNode**)&gauge_head,id);
}

uint8_t DFRobot_LcdDisplay::creatCompass(uint16_t x, uint16_t y, uint16_t diameter)
{
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_COMPASS,CMD_DRAW_COMPASS_LEN);
  uint8_t compassId = getID(CMD_OF_DRAW_COMPASS);
  cmd[4] = compassId;
  cmd[5] = diameter >> 8;
  cmd[6] = diameter & 0xFF;
  cmd[7] = x >> 8;
  cmd[8] = x & 0xFF;
  cmd[9] = y >> 8;
  cmd[10] = y & 0xFF;
  writeCommand(cmd, CMD_DRAW_COMPASS_LEN);
  free(cmd);
  return compassId;
}

void DFRobot_LcdDisplay::updateCompass(uint8_t id, uint16_t x, uint16_t y, uint16_t diameter)
{
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_COMPASS,CMD_DRAW_COMPASS_LEN);
  cmd[4] = id;
  cmd[5] = diameter >> 8;
  cmd[6] = diameter & 0xFF;
  cmd[7] = x >> 8;
  cmd[8] = x & 0xFF;
  cmd[9] = y >> 8;
  cmd[10] = y & 0xFF;
  writeCommand(cmd, CMD_DRAW_COMPASS_LEN);
  free(cmd);
}

void DFRobot_LcdDisplay::setCompassScale(uint8_t compassId, uint16_t scale)
{
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_COMPASS_VALUE, CMD_SET_COMPASS_VALUE_LEN);
  cmd[4] = compassId;
  cmd[5] = scale >> 8;
  cmd[6] = scale & 0xFF;

  writeCommand(cmd, CMD_SET_COMPASS_VALUE_LEN);
  free(cmd);
}

void DFRobot_LcdDisplay::deleteCompass(uint8_t id){
  uint8_t* cmd = creatCommand(CMD_DELETE_OBJ, CMD_DELETE_OBJ_LEN);
  cmd[4] = CMD_OF_DRAW_COMPASS;
  cmd[5] = id;
  writeCommand(cmd, CMD_DELETE_OBJ_LEN);
  free(cmd);
  deleteNodeByID((GenericNode**)&compass_head,id);
}

void DFRobot_LcdDisplay::setBackgroundColor(uint32_t bg_color)
{
  uint8_t* cmd = creatCommand(CMD_SET_BACKGROUND_COLOR, CMD_SET_LEN);
  cmd[4] = bg_color >> 16;
  cmd[5] = bg_color >> 8;
  cmd[6] = bg_color & 0xFF;
  writeCommand(cmd, CMD_SET_LEN);
  free(cmd);
  delay(300);
}

void DFRobot_LcdDisplay::setBackgroundImg(uint8_t location, String str){
  const char* data = str.c_str();
  uint8_t length = strlen(data);
  uint8_t* cmd = creatCommand(CMD_SET_BACKGROUND_IMG, length + 5);
  cmd[4] = location;
  memcpy(cmd+5, data, length);
  writeCommand(cmd, length + 5);
  free(cmd);
}


uint8_t DFRobot_LcdDisplay::drawString(uint16_t x, uint16_t y, String str, uint8_t fontSize, uint32_t color)
{
  const char* data = str.c_str();
  uint8_t length = strlen(data);
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_TEXT, length + 13);
  uint8_t id = getID(CMD_OF_DRAW_TEXT);
  cmd[4] = id;
  cmd[5] = fontSize;
  cmd[6] = color >> 16;
  cmd[7] = color >> 8;
  cmd[8] = color & 0xFF;
  cmd[9] = x >> 8;
  cmd[10] = x & 0xFF;
  cmd[11] = y >> 8;
  cmd[12] = y & 0xFF;
  memcpy(cmd+13, data, length);
  writeCommand(cmd, length + 13);
  free(cmd);
  return id;
}

void DFRobot_LcdDisplay::updateString(uint8_t id, uint16_t x, uint16_t y, String str, uint8_t fontSize, uint32_t color)
{
  const char* data = str.c_str();
  uint16_t length = strlen(data);
  if(length > 242){
    length = 242;
  }
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_TEXT, length + 13);
  if(cmd != NULL){
    cmd[4] = id;
    cmd[5] = fontSize;
    cmd[6] = color >> 16;
    cmd[7] = color >> 8;
    cmd[8] = color & 0xFF;
    cmd[9] = x >> 8;
    cmd[10] = x & 0xFF;
    cmd[11] = y >> 8;
    cmd[12] = y & 0xFF;
    memcpy(cmd+13, data, length);
    writeCommand(cmd, length + 13);
    free(cmd);
  }
}

void DFRobot_LcdDisplay::deleteString(uint8_t id){
  uint8_t* cmd = creatCommand(CMD_DELETE_OBJ, CMD_DELETE_OBJ_LEN);
  cmd[4] = CMD_OF_DRAW_TEXT;
  cmd[5] = id;
  writeCommand(cmd, CMD_DELETE_OBJ_LEN);
  free(cmd);
  deleteNodeByID((GenericNode**)&text_head,id);
}

uint8_t DFRobot_LcdDisplay::drawLcdTime(uint8_t x, uint8_t y, uint8_t hour, uint8_t Minute, uint8_t seconds, uint8_t fontSize, uint16_t color)
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

  return drawString(x, y, time1, fontSize, color);
}

void DFRobot_LcdDisplay::updateLcdTime(uint8_t id, uint8_t x, uint8_t y, uint8_t hour, uint8_t Minute, uint8_t seconds, uint8_t fontSize, uint16_t color)
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

  updateString(id, x, y, time1, fontSize, color);
}

void DFRobot_LcdDisplay::drawLcdDate(uint8_t x, uint8_t y, uint8_t month, uint8_t day, uint8_t weeks, uint8_t fontSize, uint16_t color)
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
  drawString(x, y, date, fontSize, color);
}

uint8_t DFRobot_LcdDisplay::creatLineMeter(uint16_t x, uint16_t y, uint16_t size, uint16_t start, uint16_t end, uint32_t pointerColor, uint32_t bgColor)
{
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_LINE_METER, CMD_OF_DRAW_LINE_METER_LEN);
  uint8_t id = getID(CMD_OF_DRAW_LINE_METER);
  cmd[4] = id;
  cmd[5] = size >> 8;
  cmd[6] = size & 0xFF;
  cmd[7] = start >> 8;
  cmd[8] = start & 0xFF;
  cmd[9] = end >> 8;
  cmd[10] = end & 0xFF;
  cmd[11] = pointerColor >> 16;
  cmd[12] = pointerColor >> 8;
  cmd[13] = pointerColor & 0xFF;
  cmd[14] = bgColor >> 16;
  cmd[15] = bgColor >> 8;
  cmd[16] = bgColor & 0xFF;
  cmd[17] = x >> 8;
  cmd[18] = x & 0xFF;
  cmd[19] = y >> 8;
  cmd[20] = y & 0xFF;
  writeCommand(cmd, CMD_OF_DRAW_LINE_METER_LEN);
  free(cmd);
  return id;
}

void DFRobot_LcdDisplay::updateLineMeter(uint8_t id, uint16_t x, uint16_t y, uint16_t size, uint16_t start, uint16_t end, uint32_t pointerColor, uint32_t bgColor)
{
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_LINE_METER, CMD_OF_DRAW_LINE_METER_LEN);
  cmd[4] = id;
  cmd[5] = size >> 8;
  cmd[6] = size & 0xFF;
  cmd[7] = start >> 8;
  cmd[8] = start & 0xFF;
  cmd[9] = end >> 8;
  cmd[10] = end & 0xFF;
  cmd[11] = pointerColor >> 16;
  cmd[12] = pointerColor >> 8;
  cmd[13] = pointerColor & 0xFF;
  cmd[14] = bgColor >> 16;
  cmd[15] = bgColor >> 8;
  cmd[16] = bgColor & 0xFF;
  cmd[17] = x >> 8;
  cmd[18] = x & 0xFF;
  cmd[19] = y >> 8;
  cmd[20] = y & 0xFF;
  writeCommand(cmd, CMD_OF_DRAW_LINE_METER_LEN);
  free(cmd);
}

void DFRobot_LcdDisplay::deleteLineMeter(uint8_t id){
  uint8_t* cmd = creatCommand(CMD_DELETE_OBJ, CMD_DELETE_OBJ_LEN);
  cmd[4] = CMD_OF_DRAW_LINE_METER;
  cmd[5] = id;
  writeCommand(cmd, CMD_DELETE_OBJ_LEN);
  free(cmd);
  deleteNodeByID((GenericNode**)&lineMeter_head,id);
}

void DFRobot_LcdDisplay::setTopLineMeter(uint8_t id){
  uint8_t* cmd = creatCommand(CMD_SET_TOP_OBJ, CMD_SET_TOP_OBJ_LEN);
  cmd[4] = CMD_OF_DRAW_LINE_METER;
  cmd[5] = id;
  writeCommand(cmd, CMD_DELETE_OBJ_LEN);
  free(cmd);
}

uint8_t DFRobot_LcdDisplay::creatChart(String strX, String strY, uint32_t bgColor, uint8_t type)
{
  uint8_t * creatCmd = creatCommand(CMD_OF_DRAW_LINE_CHART, CMD_DRAW_CHART_LEN);
  uint8_t id = getID(CMD_OF_DRAW_LINE_CHART);
  creatCmd[4] = id;
  creatCmd[5] = type;
  creatCmd[6] = bgColor >> 16;
  creatCmd[7] = bgColor >> 8;
  creatCmd[8] = bgColor;
  writeCommand(creatCmd, CMD_DRAW_CHART_LEN);
  free(creatCmd);
  delay(100);
  setChartAxisTexts(id, 0, strX);
  delay(100);
  setChartAxisTexts(id, 1, strY);
  return id;
}

void DFRobot_LcdDisplay::updateChart(uint8_t id, uint32_t bgColor, uint8_t type)
{
  uint8_t * creatCmd = creatCommand(CMD_OF_DRAW_LINE_CHART, CMD_DRAW_CHART_LEN);
  creatCmd[4] = id;
  creatCmd[5] = type;
  creatCmd[6] = bgColor >> 16;
  creatCmd[7] = bgColor >> 8;
  creatCmd[8] = bgColor;
  writeCommand(creatCmd, CMD_DRAW_CHART_LEN);
  free(creatCmd);
}

uint8_t DFRobot_LcdDisplay::creatChartSeries(uint8_t chartId, uint32_t color)
{

  uint8_t* cmd = creatCommand(CMD_OF_DRAW_SERIE, CMD_DRAW_SERIE_LEN);
  uint8_t serieId = getID(CMD_OF_DRAW_SERIE);
  cmd[4] = serieId;
  cmd[5] = chartId;   
  cmd[6] = color >> 16;
  cmd[7] = color >> 8;
  cmd[8] = color ;
  writeCommand(cmd, CMD_DRAW_SERIE_LEN);
  free(cmd);
  return serieId;
}

void DFRobot_LcdDisplay::updateChartSeries(uint8_t chartId, uint8_t seriesId, uint32_t color){
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_SERIE, CMD_DRAW_SERIE_LEN);
  cmd[4] = seriesId;
  cmd[5] = chartId;   
  cmd[6] = color >> 16;
  cmd[7] = color >> 8;
  cmd[8] = color ;
  writeCommand(cmd, CMD_DRAW_SERIE_LEN);
  free(cmd);
}

uint8_t DFRobot_LcdDisplay::setChartAxisTexts(uint8_t chartId, uint8_t axis, String text)
{
  uint8_t textLen = text.length();
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_LINE_CHART_TEXT, textLen + 6);
  cmd[4] = chartId;
  cmd[5] = axis;
  for (uint8_t i = 0;i < textLen;i++) {
    cmd[6 + i] = text[i];
  }
  writeCommand(cmd, textLen + 6);
  free(cmd);
  return 1;
}


void DFRobot_LcdDisplay::updateChartPoint(uint8_t chartId, uint8_t SeriesId, uint8_t pointNum, uint16_t value){
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_SERIE_DATA, 10);
  cmd[4] = chartId;
  cmd[5] = SeriesId;
  cmd[6] = 1;
  cmd[7] = pointNum;
  cmd[8] = value >> 8;
  cmd[9] = value & 0xFF;
  writeCommand(cmd,  10);
  free(cmd);
}

uint8_t DFRobot_LcdDisplay::addChartSeriesData(uint8_t chartId, uint8_t SeriesId, uint16_t point[], uint8_t len)
{
  uint8_t* cmd = creatCommand(CMD_OF_DRAW_SERIE_DATA, len*2 + 8);
  cmd[4] = chartId;
  cmd[5] = SeriesId;
  cmd[6] = 0;
  cmd[7] = 0;
  for(uint8_t i = 0; i < len; i++){
    cmd[8 + 2*i]     = point[i]>>8;
    cmd[8 + 2*i + 1] = point[i];
  }
  writeCommand(cmd,  len*2 + 8);
  free(cmd);
  return 1;
}

void DFRobot_LcdDisplay::setTopChart(uint8_t id){
  uint8_t* cmd = creatCommand(CMD_SET_TOP_OBJ, CMD_SET_TOP_OBJ_LEN);
  cmd[4] = CMD_OF_DRAW_LINE_CHART;
  cmd[5] = id;
  writeCommand(cmd, CMD_SET_TOP_OBJ_LEN);
  free(cmd);
}

void DFRobot_LcdDisplay::deleteChart(uint8_t id){
  uint8_t* cmd = creatCommand(CMD_DELETE_OBJ, CMD_DELETE_OBJ_LEN);
  cmd[4] = CMD_OF_DRAW_LINE_CHART;
  cmd[5] = id;
  writeCommand(cmd, CMD_DELETE_OBJ_LEN);
  free(cmd);
  deleteNodeByID((GenericNode**)&line_chart_head,id);
}

void DFRobot_LcdDisplay::setMeterValue(uint8_t lineMeterId, uint16_t value)
{

  uint8_t* cmd = creatCommand(CMD_OF_DRAW_LINE_METER_VALUE, CMD_SET_LINE_METER_VALUE_LEN);
  cmd[4] = lineMeterId;
  cmd[5] = value >> 8;
  cmd[6] = value & 0xFF;
  writeCommand(cmd, CMD_SET_LINE_METER_VALUE_LEN);
  free(cmd);
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

  return true;
}

void DFRobot_Lcd_IIC::writeCommand(uint8_t* pBuf, uint16_t len)
{
  uint16_t bytesSent = 0; // The number of bytes sent
  uint16_t bytesToSend = len; // The number of bytes to be sent
  if (pBuf == NULL) {
    DBG("pBuf ERROR!! : null pointer");
  }

  while (bytesToSend > 0) {
    uint16_t currentTransferSize = (bytesToSend < 32) ? bytesToSend : 32;
    
    _pWire->beginTransmission(_deviceAddr);
    
    _pWire->write(&pBuf[bytesSent], currentTransferSize);
    
    _pWire->endTransmission();
    
    bytesSent += currentTransferSize;
    bytesToSend -= currentTransferSize;

    delay(50);
  }
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
