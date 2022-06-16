static const uint16_t mdlpt = 8;
static const uint16_t lnkpt = 13;

#define RED     (0xFF0000)
#define GREEN   (0x00FF00)
#define BLUE    (0x0000FF)
#define YELLOW  (0xFFFF00)

MDL3D_T mdl[mdlpt] = {
  -1.0, -1.0,  1.0,
  1.0, -1.0,  1.0,
  1.0,  1.0,  1.0,
  -1.0,  1.0,  1.0,
  -1.0, -1.0, -1.0,
  1.0, -1.0, -1.0,
  1.0,  1.0, -1.0,
  -1.0,  1.0, -1.0,
};
LNK_T lnk[lnkpt] = {
  0, 1, TFT_RED,
  1, 2, TFT_RED,
  2, 3, TFT_RED,
  3, 0, TFT_RED,
  4, 5, TFT_GREEN,
  5, 6, TFT_GREEN,
  6, 7, TFT_GREEN,
  7, 4, TFT_GREEN,
  0, 4, TFT_BLUE,
  1, 5, TFT_BLUE,
  2, 6, TFT_BLUE,
  3, 7, TFT_BLUE,
  0, 6, TFT_YELLOW,
};
MDL3D_T dst3d[mdlpt];
MDL2D_T dst2d[mdlpt];
MDL3D_T mv = {
  0.0,
  0.0,
  0.0
};
MDL3D_T view = {
  0.0,
  0.0,
 -5.0
};
