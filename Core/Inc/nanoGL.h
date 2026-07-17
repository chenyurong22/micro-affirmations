/*

File:   nanoGL.h
Author: Isaac Pawley

*/

#ifndef INC_NANOGL_H_
#define INC_NANOGL_H_

#include "fonts.h"

uint16_t nanoGL_stringWidth(const char *text, const Font_t *font);
void nanoGL_drawString(int16_t x, int16_t y, const char *text, const Font_t *font);
void nanoGL_clear(void);

#endif /* INC_NANOGL_H_ */