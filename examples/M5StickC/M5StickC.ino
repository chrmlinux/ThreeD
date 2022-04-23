#include <M5StickC.h>
TFT_eSprite spr(&M5.Lcd);

#include "ThreeD.hpp"
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
    spr.drawLine(x1, y1, x2, y2, lnk[i].color);
    spr.setCursor(x1, y1); spr.print(lnk[i].start);
  }
}

void setup(void)
{
  M5.begin();
  Serial.begin( 115200 ); delay(500);
  M5.Lcd.setRotation(1);
  spr.createSprite(M5.Lcd.width(), M5.Lcd.height());
  td.begin();
  _hw = spr.width() / 2;
  _hh = spr.height() / 2;
}

void loop(void)
{
  float fact = 100.0;
  static uint16_t deg = 0;

  M5.update();

  td.rot(ROTY, deg, mdlpt,   mdl, dst3d); 
  td.rot(ROTZ,  24, mdlpt, dst3d, dst3d); 
//  td.rot(ROTX,  15, mdlpt, dst3d, dst3d); 
  td.cnv(view,      mdlpt, dst3d, dst2d);
    draw(fact,      mdlpt, dst2d, lnkpt, lnk);

  spr.setCursor(8, 8); spr.print(td.getfps()); spr.print("fps");  
  spr.setCursor(8,18); spr.print("y:"); spr.print(deg);
  spr.pushSprite(0, 0);

  deg = (deg + 1) % 360;
}
