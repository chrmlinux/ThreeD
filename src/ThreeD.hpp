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

class ThreeD {

  public:

    //============================================
    // Constructor
    //============================================
    ThreeD(void) {
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
    void rot(uint16_t mode, uint16_t s, uint16_t dtcnt, MDL3D_T *src, MDL3D_T *dst) {
			float rs = radians(s);
			float cr = cos(rs);
			float sr = sin(rs);
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

  private:

};

#endif
