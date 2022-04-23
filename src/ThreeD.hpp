//================================================================
// program name : ThreeD.hpp
// date/author  : 2022/04/23 @chromlinux03
// version      : 0.0.3
// license      : MIT
//================================================================

#ifndef _THREED_HPP_
#define _THREED_HPP_

#include <Arduino.h>

typedef struct {
  float x;
  float y;
  float z;
} MDL3D_T;

typedef struct {
  float x;
  float y;
} MDL2D_T;

typedef struct {
  uint16_t start;
  uint16_t end;
  uint32_t color;
} LNK_T;

enum {ROTX = 0, ROTY, ROTZ};
#define MAX_SINTBL  (91)
float tsin[MAX_SINTBL] = {0.0};
// 90-180:sin(180-deg) 180-270:-sin(deg-180) 270-360:-sin(360-deg)
// cos(deg):sin(deg+90)

class ThreeD {

  public:

    //============================================
    // Constructor
    //============================================
    ThreeD(void) {
      for (register int i = 0; i < MAX_SINTBL; i++) {
        tsin[i] = sin(radians(i));
      }
    }

    //============================================
    // begin
    //============================================
    uint16_t begin(void) {
      uint16_t rtn = 0;
      return rtn;
    }

    //============================================
    // end
    //============================================
    void end(void) {

    }

    //============================================
    // cnv
    //============================================
    uint16_t cnv(MDL3D_T vw, uint16_t dtcnt, MDL3D_T *src, MDL2D_T *dst) {
      uint16_t rtn = 0;
      for (register int i = 0; i < dtcnt; i++) {
        float inverted = 1.0f / (src[i].z + vw.z);
        dst[i].x = (src[i].x + vw.x) * inverted;
        dst[i].y = (src[i].y + vw.y) * inverted;
      }
      return rtn;
    }

    //============================================
    // rot
    //============================================
    void rot(uint16_t mode, uint16_t deg, uint16_t dtcnt, MDL3D_T *src, MDL3D_T *dst) {
      float sr = Sin(deg);
      float cr = Cos(deg);
      for (register int i = 0; i < dtcnt; i++) {
        switch (mode) {
          case ROTX:
            dst[i].x = src[i].x;
            dst[i].y = src[i].y * cr - src[i].z * sr;
            dst[i].z = src[i].y * sr + src[i].z * cr;
            break;
          case ROTY:
            dst[i].x = src[i].x * cr - src[i].z * sr;
            dst[i].y = src[i].y;
            dst[i].z = src[i].x * sr + src[i].z * cr;
            break;
          case ROTZ:
            dst[i].x = src[i].x * cr - src[i].y * sr;
            dst[i].y = src[i].x * sr + src[i].y * cr;
            dst[i].z = src[i].z;
            break;
        }
      }
    }

    //============================================
    // mov
    //============================================
    void mov(MDL3D_T mv, uint16_t dtcnt, MDL3D_T *src, MDL3D_T *dst) {
      for (register int i = 0; i < dtcnt; i++) {
        dst[i].x = src[i].x + mv.x;
        dst[i].y = src[i].y + mv.y;
        dst[i].z = src[i].z + mv.z;
      }
    }

    //============================================
    // update
    //============================================
    void update(void) {

    }

    //============================================
    // Sin
    //============================================
    float Sin(uint16_t deg) {
			float rtn = 0.0;
      deg = deg % 360;
      if (deg <=  90) return  tsin[      deg];
      if (deg <= 180) return  tsin[180 - deg];
      if (deg <= 270) return -tsin[deg - 180];
      if (deg <= 360) return -tsin[360 - deg];
			return rtn;
    }

    //============================================
    // Cos
    //============================================
    float Cos(uint16_t deg) {
      return Sin(deg + 90);
    }

    //============================================
    // getfps
    //============================================
    uint32_t getfps(void)
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

  private:

};

#endif
