static const uint16_t mdlpt = 8;
static const uint16_t lnkpt = 13;

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
  0, 1, RED,
  1, 2, RED,
  2, 3, RED,
  3, 0, RED,
  4, 5, GREEN,
  5, 6, GREEN,
  6, 7, GREEN,
  7, 4, GREEN,
  0, 4, BLUE,
  1, 5, BLUE,
  2, 6, BLUE,
  3, 7, BLUE,
  0, 6, YELLOW,
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
