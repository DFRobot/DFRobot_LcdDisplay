# DFRobot_LcdDisplay
- [English Version](./README.md)

  该产品是一块I2C驱动和UART的tft显示屏,屏幕里面内置固件,集成了部分lvgl控件,和GDL图形显示
并在硬件上集成了一块GT30L24A3W字库芯片,支持多个国家的语言显示,并且在固件芯片上内置
了大量常用的图标。
![产品效果图](./resources/images/DFR0997.png)

## 产品链接（https://www.dfrobot.com.cn）
    SKU: DFR0997
   
## 目录

* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits)

## 概述
提供一个Arduino库,来驱动显示屏(DFR0997)

## 库安装
要使用此库，请先下载库文件，并将其粘贴到\Arduino\libraries目录，然后打开示例文件夹并在文件夹中运行演示。

## 方法

```C++
  /**
   * @fn drawPixel
   * @brief 绘制像素点
   * @param x 像素点的x坐标位置
   * @param y 像素点的y坐标位置
   * @param color 像素点的色彩，RGB565格式
   */
  void drawPixel(int16_t x, int16_t y, uint16_t color);
  
  /**
   * @fn lvglInit
   * @brief 初始化lvgl,但是用lvgl的控件或者图标时,需要调用此函数 
   * @param bg_color lvgl背景颜色
   */
  void lvglInit(uint16_t bg_color = 0xffee);

  /**
   * @fn setFont
   * @brief 设置字体, 方便计算一连串字体的显示位置
   * @param font 字体种类, eLcdFont_t
   */
  void setFont(eLcdFont_t font);
  /**
   * @fn fillScreen
   * @brief 填充整个屏幕
   * @param color屏幕填充的色彩，RGB565格式
   */
  void fillScreen(uint16_t color);
  
  /**
   * @fn setBackLight
   * @brief 设置屏幕背光
   * @param on true(打开)/false(关闭)
   */
  void setBackLight(bool on);
  
  /**
   * @fn drawLine
   * @brief 在屏幕上画一条直线
   * @param x0 直线起点x坐标
   * @param y0 直线起点y坐标
   * @param x1 直线终点x坐标
   * @param y1 直线终点y坐标
   * @param color 线段的颜色，RGB565格式
   */
  void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
  
  /**
   * @fn drawRect
   * @brief 在屏幕上画矩形
   * @param x 矩形起点x坐标
   * @param y 矩形起点y坐标
   * @param w  矩形的宽度
   * @param h  矩形的高度
   * @param color 矩形颜色
   */
  void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
  
  /**
   * @fn fillRect
   * @brief 在屏幕上填充矩形
   * @param x 矩形起点x坐标
   * @param y 矩形起点y坐标
   * @param w  矩形的宽度
   * @param h  矩形的高度
   * @param color 矩形颜色
   */
  void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
  
  /**
   * @fn drawRoundRect
   * @brief 在屏幕上画圆角矩形
   * @param x0 矩形起点x坐标
   * @param y0 矩形起点y坐标
   * @param w  矩形的宽度
   * @param h  矩形的高度
   * @param radius  圆角半径
   * @param color 矩形颜色
   */
  void drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,
      int16_t radius, uint16_t color);

  /**
   * @fn fillRoundRect
   * @brief 在屏幕上填充圆角矩形
   * @param x0 矩形起点x坐标
   * @param y0 矩形起点y坐标
   * @param w  矩形的宽度
   * @param h  矩形的高度
   * @param radius  圆角半径
   * @param color 矩形颜色
   */
  void fillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,
      int16_t radius, uint16_t color);
  
  /**
   * @fn drawCircle
   * @brief 在屏幕画圆
   * @param x0 圆心x坐标
   * @param y0 圆心y坐标
   * @param r  圆的半径
   * @param color 圆的颜色
   */
  void drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);

  /**
   * @fn fillCircle
   * @brief 在屏幕填充圆
   * @param x0 圆心x坐标
   * @param y0 圆心y坐标
   * @param r  圆的半径
   * @param color 圆的颜色
   */
  void fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);

  /**
   * @fn drawTriangle
   * @brief 在屏幕画一个三角形
   * @param x0 三角形第一个点的x坐标
   * @param y0 三角形第一个点的y坐标
   * @param x1 三角形第二个点的x坐标
   * @param y1 三角形第二个点的y坐标
   * @param x2 三角形第三个点的x坐标
   * @param y2 三角形第三个点的y坐标
   * @param color 圆的颜色
   */
  void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
      int16_t x2, int16_t y2, uint16_t color);

  /**
   * @fn fillTriangle
   * @brief 在屏幕填充一个三角形
   * @param x0 三角形第一个点的x坐标
   * @param y0 三角形第一个点的y坐标
   * @param x1 三角形第二个点的x坐标
   * @param y1 三角形第二个点的y坐标
   * @param x2 三角形第三个点的x坐标
   * @param y2 三角形第三个点的y坐标
   * @param color 圆的颜色
   */
  void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
      int16_t x2, int16_t y2, uint16_t color);

  /**
   * @fn drawIcon
   * @brief 绘制一个图标
   * @param x 三角形第一个点的x坐标
   * @param y 三角形第一个点的y坐标
   * @param id 三角形第二个点的x坐标
   * @param size 三角形第二个点的y坐标
   * @return 图标控件的对象
   */
  sControlinf_t * drawIcon(int16_t x,int16_t y,uint8_t id,uint16_t size = 255);
  
  /**
   * @fn drawDiskImg
   * @brief 绘制u盘里面的图片(bmp或者png)
   * @param x 图片第一个点的x坐标
   * @param y 图片第一个点的y坐标
   * @param str 图片完整文件名, 如 "/img/cat.bmp"
   * @param size 图片大小缩放系数
   * @return 图片控件的对象
   * @note 因ram较小, bmp 和 png 的规格有限制
   */
  sControlinf_t* drawDiskImg(int16_t x, int16_t y, String str, uint16_t size = 255);

  /**
   * @fn creatSlider
   * @brief 创建一个滑条控件
   * @param x 滑条的x坐标
   * @param y 滑条的y坐标
   * @param width 滑条的宽度
   * @param height 滑条的高度
   * @param color 滑条的颜色
   * @return 滑条控件的对象
   */
  sControlinf_t *creatSlider(uint16_t x,uint16_t y,uint8_t width,uint8_t height, uint16_t color);
  
  /**
   * @fn setSliderValue
   * @brief 设置滑条的值
   * @param obj 滑条控件的对象
   * @param value 滑条的值
   */
  void setSliderValue(sControlinf_t* obj,uint8_t value);
  
  /**
   * @fn creatBar
   * @brief 创建一个进度条控件
   * @param x 进度条的x坐标
   * @param y 进度条的y坐标
   * @param width 进度条的宽度
   * @param height 进度条的高度
   * @param color 进度条的颜色
   * @return 进度条控件的对象
   */
  sControlinf_t *creatBar(uint16_t x,uint16_t y,uint16_t width,uint8_t height, uint16_t color);
  
  /**
   * @fn setBar
   * @brief 创建一个滑条控件
   * @param obj 滑条控件的对象
   * @param str 滑条的值
   */
  void setBar(sControlinf_t* obj,String str);
  
  /**
   * @fn creatChart
   * @brief 创建一个图表控件
   * @param strX 图表x轴上的标签
   * @param strY 图表y轴上的标签
   * @param type 图表的类型(折线图/柱状图)
   * @return 图表控件的对象
   */
  sControlinf_t *creatChart(String strX,String strY, uint8_t type);
  
  /**
   * @fn creatChartSerie
   * @brief 在图表中创建折线图或柱状图
   * @param obj 图表控件的对象
   * @param color 折线图/柱状图的颜色
   * @return 返回图的编号
   */
  uint8_t creatChartSerie(sControlinf_t* obj,uint16_t color);
  
  
  /**
   * @fn creatGauge
   * @brief 创建一个表盘控件
   * @param x 控件所在x轴坐标
   * @param y 控件所在y轴坐标
   * @param width  控件的宽度
   * @param height 控件的高度
   * @param color 控件的颜色
   * @return 表盘控件的对象
   */
  sControlinf_t *creatGauge(uint16_t x,uint16_t y,uint8_t width,uint8_t height, uint16_t color);
  
  
  /**
   * @fn setCompassScale
   * @brief 设置指南针指针的角度
   * @param obj 指南针的对象
   * @param scale 指针角度(0~360)
   */
  void setCompassScale(sControlinf_t* obj,uint16_t scale);
  
  /**
   * @fn setGaugeScale
   * @brief 设置表盘的参数
   * @param obj 表盘的对象
   * @param angle 刻度角 (0..360)
   * @param start 起始值
   * @param end 终止值
   */
  void setGaugeScale(sControlinf_t* obj,uint16_t angle,int16_t start,int16_t end);

  /**
   * @fn setGaugeValue
   * @brief 设置表盘指针的值
   * @param obj 表盘对象
   * @param value 新的指针值
   */
  void setGaugeValue(sControlinf_t* obj,uint16_t value);

  /**
   * @fn creatCompass
   * @brief 创建一个指南针控件
   * @param x 控件所在x轴坐标
   * @param y 控件所在y轴坐标
   * @param width  控件的宽度
   * @param height 控件的高度
   * @param color 控件的颜色
   * @return 指南针控件的对象
   */
  sControlinf_t *creatCompass(uint16_t x,uint16_t y,uint8_t width,uint8_t height, uint16_t color);

  /**
   * @fn creatArc
   * @brief 创建一个角度控件
   * @param x 控件所在x轴坐标
   * @param y 控件所在y轴坐标
   * @param width  控件的宽度
   * @param height 控件的高度
   * @return 角度控件的对象
   */
  sControlinf_t *creatArc(uint16_t x,uint16_t y,uint8_t width,uint8_t height);
  
  /**
   * @fn setArcRotation
   * @brief 设置角度控件数值
   * @param obj 角度控件的对象
   * @param rotation 新的角度值
   */
  void setArcRotation(sControlinf_t* obj,uint16_t rotation);

  /**
   * @fn addChart
   * @brief 分配并添加一个数据序列到图表中
   * @param obj 图表控件的对象
   * @param id 分配的数据序列
   * @param point 曲线图/柱状图需要数据的数组
   * @param len  数组长度
   */
  uint8_t addChart(sControlinf_t* obj,uint8_t id,uint16_t point[],uint8_t len);

  /**
   * @fn creatLineMeter
   * @brief 创建一个线形仪表控件
   * @param x 控件所在x轴坐标
   * @param y 控件所在y轴坐标
   * @param width  控件的宽度
   * @param height 控件的高度
   * @param color 控件的颜色
   * @return 线形仪表控件的对象
   */
  sControlinf_t *creatLineMeter(uint16_t x,uint16_t y,uint8_t width,uint8_t height, uint16_t color);

  /**
   * @fn setMeterValue
   * @brief 在线形仪表控件上设置一个新值
   * @param obj 指向线形仪表控件对象的指针
   * @param value 新的值
   */
  void setMeterValue(sControlinf_t* obj,uint16_t value);
  
  /**
   * @fn setMeterScale
   * @brief 设置线形仪表控件的刻度
   * @param obj 指向线形仪表控件对象的指针
   * @param angle 刻度角 (0..360)
   * @param start 起始值
   * @param end 终止值
   */
  void setMeterScale(sControlinf_t* obj,uint16_t angle,int16_t start,int16_t end);

  /**
   * @fn drawString
   * @brief 在屏幕上显示文字
   * @param x 起始位置的x坐标
   * @param y 起始位置的y坐标
   * @param str 要显示的文字
   * @param type 文字大小(只适用于eChinse和eAscii),0(24大小),1(12大小)
   * @param color 文字的颜色
   * @param bgColor 文字背景的颜色 (0: 表示不绘制背景颜色)
   */
  void drawString(uint8_t x,uint8_t y,String str,uint8_t type,uint16_t color,uint16_t bgColor);
  
  /**
   * @fn drawLcdTime
   * @brief 在屏幕上显示设置的时间
   * @param x 起始位置的x坐标
   * @param y 起始位置的y坐标
   * @param hour 小时
   * @param Minute 分钟
   * @param seconds 秒
   * @param fontSize 字体大小
   * @param color 字体颜色
   * @param bgColor 字体背景颜色
   */
  void drawLcdTime(uint8_t x,uint8_t y,uint8_t hour,uint8_t Minute,uint8_t seconds,uint8_t fontSize ,uint16_t color,uint16_t bgColor);

  /**
   * @fn drawLcdDate
   * @brief 在屏幕上显示设置的日期
   * @param x 起始位置的x坐标
   * @param y 起始位置的y坐标
   * @param month 月份
   * @param day 天数
   * @param weeks 星期数
   * @param fontSize 字体大小
   * @param color 字体颜色
   * @param bgColor 字体背景颜色
   */
  void drawLcdDate(uint8_t x,uint8_t y,uint8_t month,uint8_t day,uint8_t weeks,uint8_t fontSize,uint16_t color,uint16_t bgColor);

  /**
   * @fn reset
   * @brief 复位显示屏,显示屏复位后,创建的lvlg控件全部删除,显示的内容也一并清楚
   */
  void reset();
  /**
   * @fn lvglDelete
   * @brief 指定某个已创建的控件进行删除
   * @param obj 要删除对象的控件
   */
  void lvglDelete(sControlinf_t* obj);
```

## 兼容性

MCU                | Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | -----
Arduino Uno        |      √       |              |             | 
FireBeetle-ESP8266        |      √       |              |             | 
FireBeetle-ESP32        |      √       |              |             | 
Arduino MEGA2560        |      √       |              |             | 
Arduino Leonardo|      √       |              |             | 
Micro:bit        |      √       |              |             | 
FireBeetle-M0        |      √       |              |             | 



## 历史

- 2023/05/29 - 1.0.0 版本
- 2023/08/17 - 1.0.1 版本

## 创作者

Written by fengli(li.feng@dfrobot.com), 2022.08.08 (Welcome to our [website](https://www.dfrobot.com/))


