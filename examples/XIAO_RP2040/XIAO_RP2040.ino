#include <Wire.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
Adafruit_SH1107 lcd = Adafruit_SH1107(64, 128, &Wire);

#include <ThreeD.hpp>
#include "mdl.h"
static ThreeD td;

uint16_t _hw;
uint16_t _hh;

void draw(float fact, uint16_t mdlpt, MDL2D_T *mdl, uint16_t lnkpt, LNK_T *lnk)
{
  for (int i=0; i<lnkpt; i++) {
    uint16_t x1 = _hw + (mdl[lnk[i].start].x * fact);
    uint16_t y1 = _hh + (mdl[lnk[i].start].y * fact);
    uint16_t x2 = _hw + (mdl[lnk[i].end].x * fact);
    uint16_t y2 = _hh + (mdl[lnk[i].end].y * fact);
    lcd.drawLine(x1, y1, x2, y2, lnk[i].color);
    lcd.setCursor(x1, y1); lcd.print(lnk[i].start);
  }
}

void setup(void)
{
  Serial.begin( 115200 ); delay(500);
  Wire.begin();
  lcd.begin(0x3c, true);
  lcd.clearDisplay();
  lcd.setRotation(1);
  lcd.setTextColor(1);
  _hw = lcd.width() / 2;
  _hh = lcd.height() / 2;
  td.begin();
}

void loop(void)
{
  lcd.clearDisplay();
  float fact = 100.0;
  static uint16_t deg = 0;

  td.rot(ROTY, deg, mdlpt,   mdl, dst3d); 
  td.rot(ROTZ,  24, mdlpt, dst3d, dst3d); 
//  td.rot(ROTX,  15, mdlpt, dst3d, dst3d); 
  td.cnv(view,      mdlpt, dst3d, dst2d);
    draw(fact,      mdlpt, dst2d, lnkpt, lnk);

  lcd.setCursor(8, 8); lcd.print(td.getfps()); lcd.print("fps");  
  lcd.setCursor(8,18); lcd.print("y:"); lcd.print(deg);

  deg = (deg + 2) % 360;
  lcd.display();
}
