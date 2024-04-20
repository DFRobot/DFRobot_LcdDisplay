# DFRobot_LcdDisplay
- [中文版](./README_CN.md)

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
   * @fn begin
   * @brief 初始化函数
   * @return bool类型，初始化状态
   * @retval true 成功
   * @retval false 失败
   */
  bool begin();

  /**
   * @fn setBackgroundColor
   * @brief 设置背景颜色对象
   * @param bg_color RGB888格式
   */
  void setBackgroundColor(uint32_t bg_color = 0xFF0000);

  /**
   * @fn setBackgroundImg
   * @brief 设置背景图片对象
   * @param location 内置或外置图片
   * @param str 图片路径
   */
  void setBackgroundImg(uint8_t location, String str);

  /**
   * @fn cleanScreen
   * @brief 清屏，清除屏幕中的所有控件对象
   */
  void cleanScreen();

  /**
   * @fn drawPixel
   * @brief 在屏幕上画一个像素点
   * @param x 像素点的x坐标
   * @param y 像素点的y坐标
   * @param color 像素点的颜色
   */
  void drawPixel(int16_t x, int16_t y, uint32_t color);

  /**
   * @fn drawLine
   * @brief 在屏幕上画一条直线
   * @param x0 直线的起点x坐标
   * @param y0 直线的起点y坐标
   * @param x1 直线的终点x坐标
   * @param y1 直线的终点y坐标
   * @param width 线宽
   * @param color 直线颜色，RGB888格式
   * @return 直线控件句柄
   */
  uint8_t drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint8_t width, uint32_t color);

  /**
   * @fn updateLine
   * @brief 在屏幕上更新一条直线
   * @param id 直线控件句柄
   * @param x0 直线的起点x坐标
   * @param y0 直线的起点y坐标
   * @param x1 直线的终点x坐标
   * @param y1 直线的终点y坐标
   * @param width 线宽
   * @param color 直线颜色，RGB888格式
   */
  void updateLine(uint8_t id, int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint8_t width, uint32_t color);

  /**
   * 
   * @fn deleteLine
   * @brief 删除直线对象
   * @param id 直线控件句柄
   */
  void deleteLine(uint8_t id);

  /**
   * @fn drawRect
   * @brief 在屏幕上画一个矩形
   * @param x 矩形的起点x坐标
   * @param y 矩形的起点y坐标
   * @param w  矩形的宽度
   * @param h  矩形的高度
   * @param borderWidth 边框宽度
   * @param borderColor 边框颜色
   * @param fill 是否填充
   * @param fillColor 填充颜色
   * @param rounded 是否圆角
   * @return 矩形控件句柄
   * 
   */
  uint8_t drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t borderWidth, uint32_t borderColor, uint8_t fill, uint32_t fillColor, uint8_t rounded);

  /**
   * @fn updateRect
   * @brief 更新屏幕上的矩形
   * @param id 矩形控件的id
   * @param x 矩形的起点x坐标
   * @param y 矩形的起点y坐标
   * @param w  矩形的宽度
   * @param h  矩形的高度
   * @param borderWidth 边框宽度
   * @param borderColor 边框颜色
   * @param fill 是否填充
   * @param fillColor 填充颜色
   * @param rounded 是否圆角
   * 
   */
  void updateRect(uint8_t id, int16_t x, int16_t y, int16_t w, int16_t h, uint8_t borderWidth, uint32_t borderColor, uint8_t fill, uint32_t fillColor, uint8_t rounded);
  
  /**
   * 
   * @fn deleteRect
   * @brief 删除矩形控件对象
   * @param id 矩形控件的id
   */
  void deleteRect(uint8_t id);

  /**
   * @fn drawCircle
   * @brief 在屏幕上画圆圈
   * @param x 圆心x坐标
   * @param y 圆心y坐标
   * @param r  圆的半径
   * @param borderWidth 边框宽度
   * @param borderColor 边框颜色
   * @param fill 是否填充
   * @param fillColor 填充颜色
   * @return 圆形控件句柄
   */
  uint8_t drawCircle(int16_t x, int16_t y, int16_t r, uint8_t borderWidth, uint32_t borderColor, uint8_t fill, uint32_t fillColor);

  /**
   * @fn updateCircle
   * @brief 更新屏幕上的圆圈
   * @param id 圆形控件句柄
   * @param x 圆心x坐标
   * @param y 圆心y坐标
   * @param r  圆的半径
   * @param borderWidth 边框宽度
   * @param borderColor 边框颜色
   * @param fill 是否填充
   * @param fillColor 填充颜色
   */
  void updateCircle(uint8_t id, int16_t x, int16_t y, int16_t r, uint8_t borderWidth, uint32_t borderColor, uint8_t fill, uint32_t fillColor);

  /**
   * 
   * @fn deleteCircle
   * @brief 删除圆形控件
   * @param id 圆形控件句柄
   */
  void deleteCircle(uint8_t id);

  /**
   * @fn drawTriangle
   * @brief 在屏幕上画一个三角形
   * @param x0 三角形第一个点的x坐标
   * @param y0 三角形第一个点的y坐标
   * @param x1 三角形第二个点的x坐标
   * @param y1 三角形第二个点的y坐标
   * @param x2 三角形第三个点的x坐标
   * @param y2 三角形第三个点的y坐标
   * @param borderWidth 边框宽度
   * @param borderColor 边框颜色
   * @param fill 是否填充
   * @param fillColor 填充颜色
   * @return 三角形控件句柄
   */
  uint8_t drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t borderWidth, uint32_t borderColor, uint8_t fill, uint32_t fillColor);

 /**
   * @fn updateTriangle
   * @brief Draw a triangle on the screen
   * @param id 三角形控件的id
   * @param x0 三角形第一个点的x坐标
   * @param y0 三角形第一个点的y坐标
   * @param x1 三角形第二个点的x坐标
   * @param y1 三角形第二个点的y坐标
   * @param x2 三角形第三个点的x坐标
   * @param y2 三角形第三个点的y坐标
   * @param borderWidth 边框宽度
   * @param borderColor 边框颜色
   * @param fill 是否填充
   * @param fillColor 填充颜色
   */
  void updateTriangle(uint8_t id, int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t borderWidth, uint32_t borderColor, uint8_t fill, uint32_t fillColor);

  /**
   * 
   * @fn deleteTriangle
   * @brief 删除三角形控件
   * @param id 三角形控件句柄
   */
  void deleteTriangle(uint8_t id);

  /**
   * @fn drawIcon
   * @brief 绘制图标
   * @param x 图标第一个点的x坐标
   * @param y 图标第一个点的y坐标
   * @param id 图标对应的枚举值
   * @param size 图标缩放系数
   * @return 图标控件句柄
   */
  uint8_t drawIcon(int16_t x, int16_t y, uint16_t id, uint16_t size = 255);

  /**
   * @fn drawIcon
   * @brief 绘制U盘中的图标
   * @param x 图标第一个点的x坐标
   * @param y 图标第一个点的y坐标
   * @param str 图片路径
   * @param zoom 图标缩放系数
   * @return 图标控件句柄
   */
  uint8_t drawIcon(int16_t x, int16_t y, String str, uint16_t zoom);

  /**
   * @fn setAngleIcon
   * @brief 设置图标的角度
   * @param id 图标控件句柄
   * @param angle 旋转角度
   */
  void setAngleIcon(uint8_t id, int16_t angle);

  /**
   * @fn updateIcon
   * @brief 更新图标
   * @param x 图标第一个点的x坐标
   * @param y 图标第一个点的y坐标
   * @param iconNum 图标对应的枚举值
   * @param size 图标缩放系数
   */
  void updateIcon(uint8_t iconId, int16_t x, int16_t y, uint16_t iconNum, uint16_t size);

  /**
   * @fn updateIcon
   * @brief 更新图标
   * @param x 图标第一个点的x坐标
   * @param y 图标第一个点的y坐标
   * @param str 图片路径
   * @param zoom 图标缩放系数
   */
  void updateIcon(uint8_t iconId, int16_t x, int16_t y, String str, uint16_t zoom);

  /**
   * @fn deleteIcon
   * @brief 删除图标
   * @param id 图标控件句柄
   */
  void deleteIcon(uint8_t id);

  /**
   * @fn drawIcon
   * @brief 绘制动图
   * @param x 动图第一个点的x坐标
   * @param y 动图第一个点的y坐标
   * @param id 动图对应的枚举值
   * @param size 动图缩放系数
   * @return 动图控件句柄
   */
  uint8_t drawGif(int16_t x, int16_t y, uint16_t id, uint16_t size = 255);

  /**
   * @fn drawGif
   * @brief 绘制外置动图
   * @param x 动图第一个点的x坐标
   * @param y 动图第一个点的y坐标
   * @param str 动图路径
   * @param zoom 动图缩放系数
   * @return 动图控件句柄
   */
  uint8_t drawGif(int16_t x, int16_t y, String str, uint16_t zoom);

  /**
   * @fn updateIcon
   * @brief 删除动图控件
   * @param id 动图控件句柄
   */
  void deleteGif(uint8_t id);

  /**
   * @fn creatSlider
   * @brief 创建一个滑块控件
   * @param x 滑块的x坐标
   * @param y 滑块的y坐标
   * @param width 滑块的宽度
   * @param height 滑动杆的高度
   * @param color 滑块的颜色
   * @return 滑块控件句柄
   */
  uint8_t creatSlider(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color);

    /**
   * @fn updateSlider
   * @brief 更改一个滑块控件
   * @param id 滑块控件句柄
   * @param x 滑块的x坐标
   * @param y 滑块的y坐标
   * @param width 滑块的宽度
   * @param height 滑动杆的高度
   * @param color 滑块的颜色
   */
  void updateSlider(uint8_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color);

  /**
   * @fn setSliderValue
   * @brief 设置滑动条的值
   * @param sliderId 滑块控件句柄
   * @param value 滑块的值
   */
  void setSliderValue(uint8_t sliderId, uint16_t value);

  /**
   * 
   * @fn deleteSlider
   * @brief 删除滑块控件
   * @param id 滑块控件句柄
   */
  void deleteSlider(uint8_t id);

  /**
   * @fn creatBar
   * @brief 创建进度条控件
   * @param x 进度条的x坐标
   * @param y 进度条的y坐标
   * @param width 进度条的宽度
   * @param height 进度条的高度
   * @param color 进度条的颜色
   * @return 进度条句柄
   */
  uint8_t creatBar(uint16_t x, uint16_t y, uint16_t width, uint8_t height, uint32_t color);

  /**
   * @fn updateBar
   * @brief 更新进度条控件
   * @param id 进度条句柄
   * @param x 进度条的x坐标
   * @param y 进度条的y坐标
   * @param width 进度条的宽度
   * @param height 进度条的高度
   * @param color 进度条的颜色
   */
  void updateBar(uint8_t id, uint16_t x, uint16_t y, uint16_t width, uint8_t height, uint32_t color);

  /**
   * @fn setBarValue
   * @brief 设置进度条的值，进度条可以包含一个单位，但必须以数字开头
   * @param barId 进度条控件句柄
   * @param value 进度条的值
   */
  void setBarValue(uint8_t barId, uint16_t value);

  /**
   * 
   * @fn deleteBar
   * @brief 删除进度条
   * @param id 进度条控件的句柄
   */
  void deleteBar(uint8_t id);

  /**
   * @fn creatChart
   * @brief 创建一个图表控件
   * @param strX 在图表的x轴上标记
   * @param strY 在图表的y轴上标记
   * @param bgColor 背景颜色
   * @param type 图表类型(折线图/条形图)
   * @return 图表控件句柄
   */
  uint8_t creatChart(String strX, String strY, uint32_t bgColor, uint8_t type);

  /**
   * @fn updateChart
   * @brief 更新图表控件
   * @param id 图表控件句柄
   * @param bgColor 背景颜色
   * @param type 图表类型(折线图/条形图)
   */
  void updateChart(uint8_t id, uint32_t bgColor, uint8_t type);

  /**
   * @fn creatChartSeries
   * @brief 在图表中创建折线图或条形图序列
   * @param chartId 图表控件句柄
   * @param color 折线图/条形图的颜色
   * @return 返回序列的索引
   */
  uint8_t creatChartSeries(uint8_t chartId, uint32_t color);

  /**
   * @fn updateChartSeries
   * @brief 更新图表中的折线图或条形图序列
   * @param chartId 图表控件句柄
   * @param seriesId 数据序列的索引
   * @param color 折线图/条形图的颜色
   */
  void updateChartSeries(uint8_t chartId, uint8_t seriesId, uint32_t color);

  /**
   * @fn addChart
   * @brief 分配一个数据序列并将其添加到图表中
   * @param chartId 图表控件句柄
   * @param SeriesId 分配的数据序列
   * @param point 曲线图/条形图需要一组数据
   * @param len  数组长度
   * @return 返回序列的索引
   */
  uint8_t addChartSeriesData(uint8_t chartId, uint8_t SeriesId, uint16_t point[], uint8_t len);

  /**
   * @fn updateChartPoint
   * @brief 更新图表中某点的值
   * @param chartId 图表控件句柄
   * @param SeriesId 分配的数据序列号
   * @param pointNum 点编号
   * @param value  值
   */
  void updateChartPoint(uint8_t chartId, uint8_t SeriesId, uint8_t pointNum, uint16_t value);
  
  /**
   * 
   * @fn setTopChart
   * @brief 设置图表控件在最顶层的图层
   * @param id 图表控件句柄
   */
  void setTopChart(uint8_t id);

  /**
   * 
   * @fn deleteChart
   * @brief 删除图表控件
   * @param id 图表控件句柄
   */
  void deleteChart(uint8_t id);

  /**
   * @fn creatGauge
   * @brief 创建一个仪表盘控件
   * @param x 控件的x轴坐标
   * @param y 控件的y轴坐标
   * @param diameter  仪表盘的直径
   * @param start 初始值
   * @param end 终值
   * @param pointerColor 指针颜色
   * @param bgColor 背景颜色
   * @return 仪表盘控件句柄
   */
  uint8_t creatGauge(uint16_t x, uint16_t y, uint16_t diameter, uint16_t start, uint16_t end, uint32_t pointerColor, uint32_t bgColor);

  /**
   * @fn updateGauge
   * @brief 更新仪表盘控件
   * @param x 控件的x轴坐标
   * @param y 控件的y轴坐标
   * @param diameter  仪表盘的直径
   * @param start 初始值
   * @param end 终值
   * @param pointerColor 指针颜色
   * @param bgColor 背景颜色
   */
  void updateGauge(uint8_t id, uint16_t x, uint16_t y, uint16_t diameter, uint16_t start, uint16_t end, uint32_t pointerColor, uint32_t bgColor);

  /**
   * @fn setGaugeValue
   * @brief设置表盘指示的值
   * @param gaugeId 仪表盘控件句柄
   * @param value 新值
   */
  void setGaugeValue(uint8_t gaugeId, uint16_t value);

  /**
   * 
   * @fn deleteGauge
   * @brief 删除仪表盘
   * @param id 仪表盘控件句柄
   */
  void deleteGauge(uint8_t id);

  /**
   * @fn creatCompass
   * @brief 创建一个指南针控件
   * @param x 控件的x轴坐标
   * @param y 控件的y轴坐标
   * @param diameter  指南针控件直径
   * @return 指南针控件句柄
   */
  uint8_t creatCompass(uint16_t x, uint16_t y, uint16_t diameter);

  /**
   * @fn updateCompass
   * @brief 更新指南针控件
   * @param id 指南针控件句柄
   * @param x 控件的x轴坐标
   * @param y 控件的y轴坐标
   * @param diameter  指南针控件直径
   */
  void updateCompass(uint8_t id, uint16_t x, uint16_t y, uint16_t diameter);

  /**
   * @fn setCompassScale
   * @brief 设置罗盘指针的角度
   * @param compassId 指南针控件的id
   * @param scale 指针角度(0~360)
   */
  void setCompassScale(uint8_t compassId, uint16_t scale);

  /**
   * 
   * @fn deleteCompass
   * @brief 删除指南针
   * @param id 指南针控件句柄
   */
  void deleteCompass(uint8_t id);

  /**
   * @fn creatLineMeter
   * @brief 创建一个线性仪表控件
   * @param x 控件的x轴坐标
   * @param y 控件的y轴坐标
   * @param size  线性仪表的大小
   * @param start 最小值
   * @param end 最大值
   * @param pointerColor 指针颜色
   * @param bgColor 背景颜色
   * @return 线性仪表句柄
   */
  uint8_t creatLineMeter(uint16_t x, uint16_t y, uint16_t size, uint16_t start, uint16_t end, uint32_t pointerColor, uint32_t bgColor);

  /**
   * @fn updateLineMeter
   * @brief 更新一个线性仪表控件
   * @param id 线性仪表句柄
   * @param x 控件的x轴坐标
   * @param y 控件的y轴坐标
   * @param size  线性仪表的大小
   * @param start 最小值
   * @param end 最大值
   * @param pointerColor 指针颜色
   * @param bgColor 背景颜色
   */
  void updateLineMeter(uint8_t id, uint16_t x, uint16_t y, uint16_t size, uint16_t start, uint16_t end, uint32_t pointerColor, uint32_t bgColor);

  /**
   * @fn setMeterValue
   * @brief 在线形仪表控件上设置指定值
   * @param lineMeterId 线形仪表控件句柄
   * @param value 新值
   */
  void setMeterValue(uint8_t lineMeterId, uint16_t value);

  /**
   * @fn deleteLineMeter
   * @brief 删除线性仪表控件
   * @param id 线性仪表控件的id
   */
  void deleteLineMeter(uint8_t id);

  /**
   * @fn setTopLineMeter
   * @brief 设置线性仪表在最顶层的图层显示
   * @param id 线性仪表控件的id
   */
  void setTopLineMeter(uint8_t id);

  /**
   * @fn drawString(uint8_t x, uint8_t y, String str, uint8_t type, uint16_t color, uint16_t bgColor)
   * @brief 在屏幕上显示文本
   * @param x 起始位置的x坐标
   * @param y 起始位置的y坐标
   * @param str 要显示的文本
   * @param fontSize 文字大小(只适用于中文及英文):0 (24px大小)，1 (12px大小)
   * @param color 文本颜色
   * @return 文本控件句柄
   */
  uint8_t drawString(uint16_t x, uint16_t y, String str, uint8_t fontSize, uint32_t color);

  /**
   * @fn updateString
   * @brief 在屏幕上更新显示的文本
   * @param id 控件id
   * @param x 起始位置的x坐标
   * @param y 起始位置的y坐标
   * @param str 要显示的文本
   * @param fontSize 文字大小(只适用于中文及英文):0 (24px大小)，1 (12px大小)
   * @param color 文本颜色
   */
  void updateString(uint8_t id, uint16_t x, uint16_t y, String str, uint8_t fontSize, uint32_t color);

  /**
   * @fn deleteString
   * @brief 在屏幕上删除文本
   * @param id 文本控件句柄
   */
  void deleteString(uint8_t id);

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
   * @return 时间控件句柄
   */
  uint8_t drawLcdTime(uint8_t x, uint8_t y, uint8_t hour, uint8_t Minute, uint8_t seconds, uint8_t fontSize, uint16_t color);

  /**
   * @fn updateLcdTime
   * @brief 在屏幕上显示更新的时间
   * @param id 
   * @param x 起始位置的x坐标
   * @param y 起始位置的y坐标
   * @param hour 小时
   * @param Minute 分钟
   * @param seconds 秒
   * @param fontSize 字体大小
   * @param color 字体颜色
   */
  void updateLcdTime(uint8_t id, uint8_t x, uint8_t y, uint8_t hour, uint8_t Minute, uint8_t seconds, uint8_t fontSize, uint16_t color);

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
   */
  void drawLcdDate(uint8_t x, uint8_t y, uint8_t month, uint8_t day, uint8_t weeks, uint8_t fontSize, uint16_t color);

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


