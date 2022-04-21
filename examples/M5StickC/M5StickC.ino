#include <M5StickC.h>
TFT_eSprite spr(&M5.Lcd);

#include <ThreeD.hpp>
#include "mdl.h"
static ThreeD td;

uint32_t getfps()
{
  static uint32_t psec = 0;
  static uint32_t cnt = 0;
  static uint32_t fps = 0;
  uint32_t sec = 0;

  sec = millis() / 1000;
  ++cnt;
  if (psec != sec) {
    psec = sec;
    fps = cnt;
    cnt = 0;
  }
  return fps;
}

void draw(float fact, uint16_t mdlpt, MDL2D_T *mdl, uint16_t lnkpt, LNK_T *lnk)
{
  spr.fillRect(0, 0, spr.width(), spr.height(), TFT_BLACK);
  uint16_t hw = spr.width() / 2;
  uint16_t hh = spr.height() / 2;
  for (int i=0; i<lnkpt; i++) {
    uint16_t x1 = hw + (mdl[lnk[i].start].x * fact);
    uint16_t y1 = hh + (mdl[lnk[i].start].y * fact);
    uint16_t x2 = hw + (mdl[lnk[i].end].x * fact);
    uint16_t y2 = hh + (mdl[lnk[i].end].y * fact);
    spr.setCursor(x1, y1); spr.print(lnk[i].start);
    spr.drawLine(x1, y1, x2, y2, lnk[i].color);
  }
}

void setup(void)
{
  M5.begin();
  Serial.begin( 115200 ); delay(500);
  M5.Lcd.setRotation(1);
  spr.createSprite(M5.Lcd.width(), M5.Lcd.height());
  td.begin();
}

void loop(void)
{
  float fact = 100.0;
  static uint16_t s = 0;

  M5.update();

  td.rot(ROTY, s, mdlpt,   mdl, dst3d); 
  td.rot(ROTZ,15, mdlpt, dst3d, dst3d); 
  td.cnv(view, mdlpt, dst3d, dst2d);
  draw(fact, mdlpt, dst2d, lnkpt, lnk);

  spr.setCursor(8, 8); spr.print(getfps()); spr.print("fps");  
  spr.setCursor(8,18); spr.print("y:"); spr.print(s);
  spr.pushSprite(0, 0);

  s = (s + 1) % 360;
}
