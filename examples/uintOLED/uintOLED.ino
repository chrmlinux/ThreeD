#include <Wire.h>
#include <M5UnitOLED.h>
M5UnitOLED lcd;
M5Canvas spr(&lcd);

#include <ThreeD.hpp>
#include "mdl.h"
static ThreeD td;

uint16_t _hw;
uint16_t _hh;

void draw(float fact, uint16_t mdlpt, MDL2D_T *mdl, uint16_t lnkpt, LNK_T *lnk)
{
  spr.fillRect(0, 0, spr.width(), spr.height(), TFT_BLACK);
  for (int i=0; i<lnkpt; i++) {
    uint16_t x1 = _hw + (mdl[lnk[i].start].x * fact);
    uint16_t y1 = _hh + (mdl[lnk[i].start].y * fact);
    uint16_t x2 = _hw + (mdl[lnk[i].end].x * fact);
    uint16_t y2 = _hh + (mdl[lnk[i].end].y * fact);
    spr.drawLine(x1, y1, x2, y2, TFT_WHITE);
    spr.setCursor(x1, y1); spr.print(lnk[i].start);
  }
}

void setup(void)
{
  Serial.begin( 115200 ); delay(500);
  lcd.init();
  lcd.setRotation(1);
  lcd.setTextColor(TFT_WHITE, TFT_BLACK);
  lcd.fillRect(0, 0, lcd.width(), lcd.height(), TFT_BLACK);
  spr.setColorDepth(1);
  spr.createSprite(lcd.width()>>1, lcd.height());
  spr.setTextColor(TFT_WHITE, TFT_BLACK);
  _hw = spr.width() / 2;
  _hh = spr.height() / 2;
  td.begin();
}

void loop(void)
{
  float fact = 75.0;
  static uint16_t deg = 0;

  td.rot(ROTY, deg, mdlpt,   mdl, dst3d); 
  td.rot(ROTZ,  24, mdlpt, dst3d, dst3d); 
  td.cnv(view,      mdlpt, dst3d, dst2d);
    draw(fact,      mdlpt, dst2d, lnkpt, lnk);

  lcd.setCursor(2, 2); lcd.printf("%2dfps", td.getfps());
  lcd.setCursor(2,10); lcd.printf("y:%3d", deg);
  spr.pushSprite(_hw, 0);

  deg = (deg + 2) % 360;
}
