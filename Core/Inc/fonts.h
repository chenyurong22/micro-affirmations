/*

File:   fonts.h
Author: Isaac Pawley

*/

#ifndef INC_FONTS_H_
#define INC_FONTS_H_

#include <stdint.h>

typedef struct {
	const uint8_t width;
	const uint8_t height;
	const uint16_t *const data;
    const uint8_t *const char_width;
} Font_t;

extern const Font_t Font_5x5;

#endif /* INC_FONTS_H_ */