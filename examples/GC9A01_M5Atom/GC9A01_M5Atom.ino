#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include "gc9a01.h"
static LGFX lcd;
static LGFX_Sprite spr(&lcd);

#include <ThreeD.hpp>
#include "mdl.h"
static ThreeD td;

static uint16_t _w;
static uint16_t _h;
static uint16_t _hw;
static uint16_t _hh;
static uint16_t fsize = 8;

void draw(float fact, uint16_t mdlpt, MDL2D_T *mdl, uint16_t lnkpt, LNK_T *lnk)
{
  for (int i = 0; i < lnkpt; i++) {
    uint16_t x1 = _hw + (mdl[lnk[i].start].x * fact);
    uint16_t y1 = _hh + (mdl[lnk[i].start].y * fact);
    uint16_t x2 = _hw + (mdl[lnk[i].end].x * fact);
    uint16_t y2 = _hh + (mdl[lnk[i].end].y * fact);
    spr.drawLine(x1, y1, x2, y2, (uint16_t)lnk[i].color);
    spr.setCursor(x1, y1); 
    spr.setTextColor(TFT_WHITE);
    spr.print(lnk[i].start);
  }
}

void px(int x, int y, int h, int c) {
  spr.setCursor(x * h, y * h);
  spr.setTextColor(c);
  spr.print(random(0, 9));
}
void textRain(int x, int y, int h) {
  static int yp[40] = {1};
  for (int i = 0; i < x; i++) {
    px(i, yp[i], h, TFT_WHITE);
    int p = 0;
    for (int j = yp[i] - y; j < yp[i]; j++) {
      px(i, j, h, p<<6);
      p++;
    }
    if (yp[i] > y) {
      if (random(1000) > 975) yp[i] = 0;
    }
    yp[i]++;
  }
}

void setup(void)
{
  lcd.init();
  lcd.setRotation(0);
  lcd.fillScreen(TFT_BLACK);
  lcd.setTextColor(TFT_WHITE, TFT_BLACK);

  _w = lcd.width();
  _h = lcd.height();
  _hw = _w >> 1;
  _hh = _h >> 1;

  spr.setColorDepth(16);
  spr.createSprite(_w, _h);
  td.begin();
}

void loop(void)
{
  float fact = 240.0;
  static uint16_t deg = 0;

  td.rot(ROTY, deg, mdlpt,   mdl, dst3d);
  td.rot(ROTZ,  24, mdlpt, dst3d, dst3d);
  //  td.rot(ROTX,  15, mdlpt, dst3d, dst3d);
  td.cnv(view,      mdlpt, dst3d, dst2d);
  
  spr.fillScreen(TFT_BLACK);
  textRain(_w / fsize, _h / fsize, fsize);
  draw(fact,      mdlpt, dst2d, lnkpt, lnk);

  spr.setCursor(_hw,  8); spr.print(td.getfps()); spr.print("fps");
  spr.setCursor(_hw, 18); spr.print("y:"); spr.print(deg);

  spr.pushSprite(0, 0);
  deg = (deg + 2) % 360;
}
