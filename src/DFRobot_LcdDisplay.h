/*!
 * @file DFRobot_LcdDisplay.h
 * @brief Define the infrastructure of the DFRobot_LcdDisplay class
 * @details The library supports driving DFR0997 screens through both I2C and UART interfaces. It provides convenient functions to control and drive the color screen.
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @License     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @maintainer [qsjhyy](yihuan.huang@dfrobot.com)
 * @version  V1.0
 * @date  2023-05-29
 * @url https://github.com/DFRobot/DFRobot_LcdDisplay
 */
#ifndef DFROBOT_LCDDISPLAY_H_
#define DFROBOT_LCDDISPLAY_H_
#include <Wire.h>
#include <Arduino.h>
#include <String.h>

#ifndef ENABLE_DBG
//  # define ENABLE_DBG   //!< Open this macro and you can see the details of the program
# ifdef ENABLE_DBG
#   ifdef DBG
#    undef DBG
#   endif
#   define DBG(...) {Serial.print("["); Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
# elif !defined(DBG)
#   define DBG(...)
# endif
#endif

// color
#define BLACK_RGB565        0x0000
#define BLUE_RGB565         0x001F
#define RED_RGB565          0xF800
#define GREEN_RGB565        0x07E0
#define CYAN_RGB565         0x07FF
#define MAGENTA_RGB565      0xF81F
#define YELLOW_RGB565       0xFFE0
#define WHITE_RGB565        0xFFFF
#define NAVY_RGB565         0x000F
#define DARKGREEN_RGB565    0x03E0
#define DARKCYAN_RGB565     0x03EF
#define MAROON_RGB565       0x7800
#define PURPLE_RGB565       0x780F
#define OLIVE_RGB565        0x7BE0
#define LIGHTGREY_RGB565    0xC618
#define DARKGREY_RGB565     0x7BEF
#define ORANGE_RGB565       0xFD20
#define GREENYELLOW_RGB565  0xAFE5
#define DCYAN_RGB565        0x03EF

// cmd len
#define CMDLEN_OF_DRAWPIXEL        10
#define CMDLEN_OF_FILLSCREEN       6
#define CMDLEN_OF_SETBACKLIGHT     5
#define CMDLEN_OF_DRAWLINE         14
#define CMDLEN_OF_DRAWRECT         14
#define CMDLEN_OF_FILLRECT         14
#define CMDLEN_OF_DRAWROUNDRECT    15
#define CMDLEN_OF_FILLROUNDRECT    15
#define CMDLEN_OF_DRAWCIRCLE       11
#define CMDLEN_OF_FILLCIRCLE       11
#define CMDLEN_OF_DRAWTRIANGLE     18
#define CMDLEN_OF_FILLTRIANGLE     18
#define CMDLEN_OF_DRAWICON         13
#define CMDLEN_OF_DRAWSTRING       36
#define CMDLEN_OF_HEAD_LEN         3

#define CMDLEN_DRAW_LVGLSLIDER       14
#define CMDLEN_DRAW_LVGLBAR          15
#define CMDLEN_DRAW_LVGLARC          14
#define CMDLEN_DRAW_LVGLGAUGE        14
#define CMDLEN_DRAW_LVGLSTATION      14
#define CMDLEN_DRAW_LVGLCOMPASS      14
#define CMDLEN_DRAW_LVGLMETER        14
#define CMDLEN_DRAW_LVGLCHART        14

#define CMDLEN_CHANGE_LVGLARC_ROTATION       9
#define CMDLEN_CHANGE_LVGLBAR_VALUE          9
#define CMDLEN_CHANGE_LVGLSLIDER_VALUE       9
#define CMDLEN_CHANGE_LVGLGAUGE_SCALE        10
#define CMDLEN_CHANGE_LVGLGAUGE_RANGE        10
#define CMDLEN_CHANGE_LVGLGAUGE_VALUE        8
#define CMDLEN_CHANGE_LVGLCOMPASS_VALUE      8
#define CMDLEN_CHANGE_LVGLMETER_SCALE        9
#define CMDLEN_CHANGE_LVGLMETER_RANGE        10
#define CMDLEN_CHANGE_LVGLMETER_VALUE        8
#define CMDLEN_CHANGE_LVGLCHART_SERIE        9
#define CMDLEN_CHANGE_LVGLCHART_POINT        9
#define CMDLEN_CHANGE_LVGLSTATION_VALUE      9

#define CMDLEN_DEINIT_LVGL          5
#define CMDLEN_RESET_LVGL           4
#define CMDLEN_INIT_LVGL            7

// cmd
#define CMD_OF_DRAWPIXEL        2
#define CMD_OF_DRAWLINE         3
#define CMD_OF_DRAWRECT         4
#define CMD_OF_DRAWROUNDRECT    5
#define CMD_OF_DRAWCIRCLE       6
#define CMD_OF_DRAWTRIANGLE     7
#define CMD_OF_SETBACKLIGHT     8
#define CMD_OF_FILLSCREEN       9
#define CMD_OF_FILLRECT         10
#define CMD_OF_FILLROUNDRECT    11
#define CMD_OF_FILLCIRCLE       12
#define CMD_OF_FILLTRIANGLE     13

#define CMD_OF_DRAWICON         20
#define CMD_OF_DRAWSTRING       21
#define CMD_OF_DRAWSTRING2      22
#define CMD_OF_DRAWDISKIMG      23

#define CMD_DRAW_LVGLSLIDER     31
#define CMD_DRAW_LVGLBAR        32
#define CMD_DRAW_LVGLSLIDER     31
#define CMD_DRAW_LVGLARC        33
#define CMD_DRAW_LVGLGAUGE      34
#define CMD_DRAW_LVGLSTATION    35
#define CMD_DRAW_LVGLCOMPASS    36
#define CMD_DRAW_LVGLLINEMETER  37
#define CMD_DRAW_LVGLCHART      38

#define CMD_RESET_LVGL          0x80
#define CMD_INIT_LVGL           0x81
#define CMD_DEINIT_LVGL         0x82

#define CMD_HEADER_HIGH         0x55
#define CMD_HEADER_LOW          0xaa

#ifndef LCD_UNUSED
#define LCD_UNUSED(x) ((void) x)
#endif


class DFRobot_LcdDisplay
{
public:

  /**
   * @enum sLcdIcon_t
   * @brief To display different icons using the library, you can select the corresponding enum for the desired icon.
   */
  typedef enum {
    // safe icons
    eIconDial,
    eIconDisabledAccess,
    eIconDown,
    eIconExit,
    eIconExitLeft,
    eIconExportRight,
    eIconFireescapeStairs,
    eIconFireExtinguisher,
    eIconFire,
    eIconHydrant,
    eIconLeft,
    eIconLifeladder,
    eIconMedicalCare,
    eIconRight,
    eIconUp,

    // expression icons
    eIconAngry,
    eIconBlink,
    eIconCry,
    eIconCute,
    eIconDepressed,
    eIconDizzy,
    eIconEmbarrassed,
    eIconFunny,
    eIconHappy,
    eIconKind,
    eIconLike,
    eIconPlayful,
    eIconResentful,
    eIconSad,
    eIconSerious,
    eIconShy,
    eIconSmile,
    eIconSurprised,
    eIconTear,
    eIconTired,

    // sensor icons
    eIconAlcohol,
    eIconAntennaReceiver,
    eIconAntenna,
    eIconBattery,
    eIconBluetooth,
    eIconBulb,
    eIconCarbonDioxide,
    eIconColor,
    eIconCompass,
    eIconDistance,
    eIconDust,
    eIconHeartRate,
    eIconLiquid,
    eIconMicrophone,
    eIconMountain,
    eIconPressure,
    eIconRaindrops,
    eIconThermometer,
    eIconWeigh,
    eIconWifi,
    eIconWind,
    eIconLight,
    eIconUVLight,

    // animal icons
    eIconBee,
    eIconBird,
    eIconButterfly,
    eIconCaterpillar,
    eIconChick,
    eIconChicken,
    eIconChipmunk,
    eIconCoccinellaSeptempunctata,
    eIconCow,
    eIconDog,
    eIconDolphin,
    eIconDragon,
    eIconElephant,
    eIconHorse,
    eIconMonkey,
    eIconOwl,
    eIconPig,
    eIconRabbit,
    eIconRooster,
    eIconSheep,
    eIconSnail,
    eIconSnake,
    eIconTurtle,
    eIconUnicorn,
    eIconWasp,
    eIconWorm,

    // Environment and Nature icons
    eIconBiofuel,
    eIconCarElectric,
    eIconDesertLandscape,
    eIconDirections,
    eIconEarth,
    eIconEcoAccumulatorBattery,
    eIconGlassRecycle,
    eIconGlobalWarming,
    eIconGreenPower,
    eIconGreenEnergy,
    eIconGreenhouse,
    eIconIcebergMelting,
    eIconLandscape,
    eIconNoPlastic,
    eIconNoSewage,
    eIconProtectEarth,
    eIconRainLandscape,
    eIconRecyclingCar,
    eIconRelaxLandscape,
    eIconSolar,
    eIconTap,
    eIconTrash,
    eIconTreeLandscape,
    eIconWaterRecycle,
    eIconWinterForest,

    // season icons
    eIconBeachBed,
    eIconBeachUmbrella8,
    eIconChristmasStocking,
    eIconCoconut,
    eIconFan,
    eIconFireplace,
    eIconGlove,
    eIconHat,
    eIconIceCream,
    eIconLifeBuoy,
    eIconSanta,
    eIconShorts,
    eIconSlipper,
    eIconSnowman,
    eIconSunny,
    eIconSweater,
    eIconSwimming,
    eIconSwimwear,
    eIconThanksgiving,
    eIconThermometerSnow,
    eIconWatermelon,

    // transport icons
    eIconAirplane,
    eIconAmbulance,
    eIconAutomobile,
    eIconBicycle,
    eIconBus,
    eIconBusStop,
    eIconDeliveryTruck,
    eIconFireEngine,
    eIconHelicopter,
    eIconHighSpeedRailway,
    eIconHorizontalTrafficLight,
    eIconKickScooter,
    eIconMotorScooter,
    eIconMotorway,
    eIconOncomingTaxi,
    eIconPoliceCar,
    eIconTractor,
    eIconVerticalTrafficLight,

    // Agriculture icons
    eIconBarn,
    eIconBarrier,
    eIconBoots,
    eIconCutWood,
    eIconEggs,
    eIconFertilizer,
    eIconFruits,
    eIconMilkContainer,
    eIconPlant,
    eIconSheafOfRice,
    eIconSprout,
    eIconStorageBucket,
    eIconTool,
    eIconTractor2,
    eIconVegetables,
    eIconWateringCan,
    eIconWellWater,
    eIconWheelbarrow,

    // people icons
    eIconDesigner,
    eIconDiver,
    eIconDoctor,
    eIconLabScientist,
    eIconMagicianMale,
    eIconNurse,
    eIconPhotographerMale,
    eIconPolice,
    eIconProgrammerMale,
    eIconSoldier,
    eIconSuccessGoalBusinessman,
    eIconSurgeon,
    eIconTeacher,

    // food icons
    eIconAvocado,
    eIconBanana,
    eIconBeerMug,
    eIconBentoBox,
    eIconBirthdayCake,
    eIconBread,
    eIconCake,
    eIconCarrot,
    eIconCheeseWedge,
    eIconCherry,
    eIconChocolateBar,
    eIconCutOfMeat,
    eIconEarOfCorn,
    eIconEgg,
    eIconFrenchFries,
    eIconGrapes,
    eIconGreenSalad,
    eIconHamburger,
    eIconHotBeverage,
    eIconPeach,
    eIconPineapple,
    eIconPopcorn,
    eIconPotato,
    eIconRedApple,
    eIconSalad,
    eIconShaomai,
    eIconSandwich,
    eIconShortcake,
    eIconStrawberry,

    // Numeric graphic icons
    eIconArrowDown,
    eIconArrowLeft,
    eIconArrowRight,
    eIconArrowUp,
    eIconDiamond,
    eIconEight,
    eIconFive,
    eIconFivePointedStar,
    eIconHeart,
    eIconNine,
    eIconFour,
    eIconOctagon,
    eIconOne,
    eIconPentagon,
    eIconRectangle,
    eIconSeven,
    eIconSix,
    eIconSquare,
    eIconThree,
    eIconTriangle,
    eIconTwo,
    eIconWindmillShape,
    eIconZero,

    // Weather icons
    eIconCloudy,
    eIconMoon,
    eIconLightning,
    eIconMoonCloudy,
    eIconRainUmbrella,
    eIconRainbow1,
    eIconRainbow2,
    eIconRainy,
    eIconSnow,
    eIconSnowy,
    eIconSunnyCloudy,
    eIconWhirlwind,

    // Music icons
    eIconAccordion,
    eIconBassDrum,
    eIconCDDiskDVD,
    eIconCello,
    eIconElectricGuitar,
    eIconFlute,
    eIconGuitar,
    eIconHarmonica,
    eIconHarp,
    eIconHeadphones,
    eIconMelodica,
    eIconMusic,
    eIconMusicStereo,
    eIconMusicTurntable,
    eIconMuteSoundOff,
    eIconPiano,
    eIconSaxophone,
    eIconSpeakerAudio,
    eIconTrumpet,
    eIconXylophone,

    // Sports icons
    eIconBadminton,
    eIconBasketball,
    eIconBowling,
    eIconChess,
    eIconCycling,
    eIconDarts,
    eIconDiving,
    eIconDumbbell,
    eIconGolf,
    eIconIceHockey,
    eIconKarate,
    eIconPingPong,
    eIconRunning,
    eIconSoccer,
    eIconTennis,
    eIconYoga,

    // Plant icons
    eIconBranch,
    eIconCactus1,
    eIconCactus2,
    eIconCactus3,
    eIconDeciduousTree,
    eIconDecorativePottedPlants,
    eIconFlower,
    eIconGrass,
    eIconGrass1,
    eIconLeaf,
    eIconPalmTree,
    eIconPottedPlantFlower,
    eIconRose,
    eIconRose1,
    eIconSunflower,
    eIconSunflower1,
    eIconTulips,

  }sLcdIcon_t;

  /**
   * @enum eLcdFont_t
   * @brief When using fonts, pass the following enums to the setFont() function to select different fonts
   */
  typedef enum {
    eChinese,/**<Chinese*/
    eShiftJis,/**<Japanese*/
    eAscii,/**<ACSII*/
    eGreece,/**<Greek*/
    eCyrillic,/**<Cyrillic*/
    eHebrew,/**<Hebrew*/
    eThailand,/**<Greek for unequal width*/
    eAlb,/**<Arabic*/
    eKhmer,/**<khmer*/
    eKorean,/**<Korean*/
  }eLcdFont_t;

  /**
    * @struct sControlinf_t
    * @brief Objects that point to different controls
    */
  typedef struct controlinf {
    uint32_t number; /**<Control ID */
    uint16_t id; /**<Control ID, different controls have different functionalities.*/
    int16_t x; /**<X coordinate of the control's position.*/
    int16_t y; /**<Y coordinate of the control's position.*/
    int16_t width; /**<Control width */
    int16_t height; /**<Control height*/
    uint16_t color; /**<Color Control*/
    struct controlinf* inf; /**<The next control pointer */
  }sControlinf_t;

public:
  /**
   * @fn DFRobot_LcdDisplay
   * @brief constructor
   * @return None
   */
  DFRobot_LcdDisplay();

  /**
   * @fn begin
   * @brief initialization function
   * @return Boolean type, initialized state
   * @retval true succeed
   * @retval false failed
   */
  bool begin();
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
   * @brief To initialize LVGL
   * @param bg_color The color of the screen after initialization
   */
  void lvglInit(uint16_t bg_color = 0xffee);

  /**
   * @fn setFont
   * @brief Set font for easy calculation of consecutive font display positions.
   * @param font font type, eLcdFont_t
   */
  void setFont(eLcdFont_t font);
  /**
   * @fn fillScreen
   * @brief Fill the entire screen
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
   * @param x Start of rectangle x coordinate
   * @param y Start of rectangle y coordinate
   * @param w  Width of a rectangle
   * @param h  Height of rectangle
   * @param color Rectangular color
   */
  void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);

  /**
   * @fn fillRect
   * @brief Fill a rectangle on the screen
   * @param x Start of rectangle x coordinate
   * @param y Start of rectangle y coordinate
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
   * @brief Fill the circle on the screen
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
  sControlinf_t* drawIcon(int16_t x, int16_t y, uint16_t id, uint16_t size = 255);

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
   * @param height The height of the slide bar
   * @param color The color of the slider
   * @return Slider control handle
   */
  sControlinf_t* creatSlider(uint16_t x, uint16_t y, uint8_t width, uint8_t height, uint16_t color);

  /**
   * @fn setSliderValue
   * @brief Sets the slider value
   * @param obj Slider control handle
   * @param value The value of the slider
   */
  void setSliderValue(sControlinf_t* obj, uint8_t value);

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
  sControlinf_t* creatBar(uint16_t x, uint16_t y, uint16_t width, uint8_t height, uint16_t color);

  /**
   * @fn setBar
   * @brief Set the value of the progress bar, which can include a unit but must start with a number
   * @param obj Progress bar control handle
   * @param str Value of the progress bar
   */
  void setBar(sControlinf_t* obj, String str);

  /**
   * @fn creatChart
   * @brief Create a chart control
   * @param strX Label on the x axis of the chart
   * @param strY Label on the y axis of the chart
   * @param type Type of chart (line chart / bar chart)
   * @return chart control handle
   */
  sControlinf_t* creatChart(String strX, String strY, uint8_t type);

  /**
   * @fn creatChartSerie
   * @brief Create a line chart or bar chart sequence in the chart
   * @param obj chart control handle
   * @param color Color of line chart/bar chart
   * @return Return the index of the series
   */
  uint8_t creatChartSerie(sControlinf_t* obj, uint16_t color);

  /**
   * @fn addChart
   * @brief Assign a data sequence and add it to the chart
   * @param obj chart control handle
   * @param id the allocated data series
   * @param point A graph/bar chart requires an array of data
   * @param len  array length
   */
  uint8_t addChart(sControlinf_t* obj, uint8_t id, uint16_t point[], uint8_t len);

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
  sControlinf_t* creatGauge(uint16_t x, uint16_t y, uint8_t width, uint8_t height, uint16_t color);

  /**
   * @fn setGaugeScale
   * @brief Setting the parameters of the dial control
   * @param obj dial control handle
   * @param angle angle of the scale (0..360)
   * @param start minimum value
   * @param end maximum value
   */
  void setGaugeScale(sControlinf_t* obj, uint16_t angle, int16_t start, int16_t end);

  /**
   * @fn setGaugeValue
   * @brief Sets the value indicated by the dial
   * @param obj dial control handle
   * @param value the new value
   */
  void setGaugeValue(sControlinf_t* obj, uint16_t value);

  /**
   * @fn creatCompass
   * @brief Creating a compass control
   * @param x The x-axis coordinate of the control
   * @param y The y-axis coordinate of the control
   * @param width  Control width
   * @param height Control height
   * @return compass control handle
   */
  sControlinf_t* creatCompass(uint16_t x, uint16_t y, uint8_t width, uint8_t height);

  /**
   * @fn setCompassScale
   * @brief Setting the angle of the compass pointer
   * @param obj compass control handle
   * @param scale Pointer angle(0~360)
   */
  void setCompassScale(sControlinf_t* obj, uint16_t scale);

  /**
   * @fn creatArc
   * @brief Creating an angle control
   * @param x The x-axis coordinate of the control
   * @param y The y-axis coordinate of the control
   * @param width  Control width
   * @param height Control height
   * @return Handle of the angle control
   */
  sControlinf_t* creatArc(uint16_t x, uint16_t y, uint8_t width, uint8_t height);

  /**
   * @fn setArcRotation
   * @brief Set the value of the angle control
   * @param obj Handle of the angle control
   * @param rotation the new value
   */
  void setArcRotation(sControlinf_t* obj, uint16_t rotation);

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
  sControlinf_t* creatLineMeter(uint16_t x, uint16_t y, uint8_t width, uint8_t height, uint16_t color);

  /**
   * @fn setMeterScale
   * @brief Sets parameters for the linear meter control
   * @param obj pointer to a line meter object
   * @param angle angle of the scale (0..360)
   * @param start minimum value
   * @param end maximum value
   */
  void setMeterScale(sControlinf_t* obj, uint16_t angle, int16_t start, int16_t end);

  /**
   * @fn setMeterValue
   * @brief Set a new value on the line meter
   * @param obj pointer to a line meter object
   * @param value new value
   */
  void setMeterValue(sControlinf_t* obj, uint16_t value);

  /**
   * @fn drawString(uint8_t x, uint8_t y, String str, uint8_t type, uint16_t color)
   * @brief Display text on the screen
   * @param x The x-coordinate of the starting position
   * @param y The y-coordinate of the starting position
   * @param str The text to display
   * @param type Text size (only applicable to eChinese and eAscii): 0 (24px size), 1 (12px size)
   * @param color Color of text
   */
  void drawString(uint16_t x, uint8_t y, String str, uint8_t type, uint16_t color);

  /**
   * @fn drawString(uint8_t x, uint8_t y, String str, uint8_t type, uint16_t color, uint16_t bgColor)
   * @brief Display text on the screen
   * @param x The x-coordinate of the starting position
   * @param y The y-coordinate of the starting position
   * @param str The text to display
   * @param type Text size (only applicable to eChinese and eAscii): 0 (24px size), 1 (12px size)
   * @param color Color of text
   * @param bgColor The color of the text background
   */
  void drawString(uint16_t x, uint8_t y, String str, uint8_t type, uint16_t color, uint16_t bgColor);

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
  void drawLcdTime(uint8_t x, uint8_t y, uint8_t hour, uint8_t Minute, uint8_t seconds, uint8_t fontSize, uint16_t color, uint16_t bgColor);

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
  void drawLcdDate(uint8_t x, uint8_t y, uint8_t month, uint8_t day, uint8_t weeks, uint8_t fontSize, uint16_t color, uint16_t bgColor);

  /**
   * @fn lvglDelete
   * @brief Delete a specific control that has been created.
   * @param obj Delete the handle of a control object
   */
  void lvglDelete(sControlinf_t* obj);

  /**
   * @fn reset
   * @brief Reset the display screen. After the display screen is reset, all the created lvgl controls will be deleted, and the displayed content will be cleared as well.
   */
  void reset();

private:
  /**
   * @fn creatStations
   * @brief Create a weather station control
   * @param x The x-axis coordinate of the control
   * @param y The y-axis coordinate of the control
   * @param zoo  Control size scaling index(128~512)
   * @param color Control color
   * @param str The text inside the weather station icon
   * @return Weather station control of the object
   */
  sControlinf_t* creatStations(uint16_t x, uint16_t y, uint16_t zoo, uint16_t color, String str);

  /**
   * @fn setStationValue
   * @brief Set the weather station control
   * @param obj Weather station control of the object
   * @param value Meteorological monitoring values, such as temperature
   */
  void setStationValue(sControlinf_t* obj, String value);

  TwoWire* _pWire;
  sControlinf_t head;
  eLcdFont_t _font = eAscii;
  uint8_t _deviceAddr;
  uint16_t getWordLen(uint8_t* utf8, uint8_t len);
  uint8_t addChartPoint(sControlinf_t* obj, uint8_t id, uint16_t value);
  uint8_t utf8toUnicode(uint8_t* utf8, uint16_t& uni);
  uint8_t setChartTickTexts(sControlinf_t* obj, String xtext, String ytext);
  void drawStringHepler(uint16_t x, uint8_t y, uint8_t* uni, uint8_t lenght, uint8_t type, uint16_t color, uint16_t fgColor);
  void drawStringHepler(uint16_t x, uint8_t y, uint8_t* uni, uint8_t lenght, uint8_t type, uint16_t color);
  uint8_t getNumber(uint8_t id);
  uint8_t* creatCommand(uint8_t cmd, uint8_t len);
  virtual void    writeCommand(uint8_t* pBuf, uint16_t len) = 0;
  virtual void    readACK(uint8_t* pBuf, uint16_t len) = 0;
};


class DFRobot_Lcd_IIC: public DFRobot_LcdDisplay
{
public:
  /**
   * @fn DFRobot_Lcd_IIC
   * @brief constructor
   * @param pWire I2C controller object
   * @param addr I2C address. The default value is 0x2c
   * @return None
   */
  DFRobot_Lcd_IIC(TwoWire* pWire = &Wire, uint8_t addr = 0x2c);

  /**
   * @fn begin
   * @brief Initialize the function to initialize the I2C controller and turn on the screen backlight
   * @return Boolean type, initialized state
   * @retval true succeed
   * @retval false failed
   */
  bool begin();

private:
  uint8_t _deviceAddr;
  TwoWire* _pWire;
  void    writeCommand(uint8_t* pBuf, uint16_t len);
  void    readACK(uint8_t* pBuf, uint16_t len);
};

class DFRobot_Lcd_UART: public DFRobot_LcdDisplay
{
public:
  /**
   * @fn DFRobot_Lcd_UART
   * @brief constructor
   * @return None
   */
  DFRobot_Lcd_UART(Stream& s);
  /**
   * @fn begin
   * @brief Initialize the function to initialize the UART controller and turn on the screen backlight
   * @param s Passing a UART object
   * @return Boolean type, initialized state
   * @retval true succeed
   * @retval false failed
   */
  bool begin();

private:
  Stream* _s;
  void writeCommand(uint8_t* pBuf, uint16_t len);
  void readACK(uint8_t* pBuf, uint16_t len);
};

#endif