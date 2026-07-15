/*

File:   matrix.h
Author: Isaac Pawley

*/

#ifndef INC_MATRIX_H_
#define INC_MATRIX_H_

#include <stdint.h>

typedef enum {
    MATRIX_OFF = 0,
    MATRIX_ON  = 1
} MatrixBrightness_t;

void matrix_setPixel(uint8_t physX, uint8_t physY, MatrixBrightness_t value);
void matrix_updateMultiplex_NonBlocking(void);

#endif /* INC_MATRIX_H_ */