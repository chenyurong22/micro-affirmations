/*

File:   matrix.h
Author: Isaac Pawley

*/

#include "matrix.h"

#include "stm32c0xx_hal.h"

#define ELECTRICAL_ROWS 10
#define ELECTRICAL_COLS 10

MatrixBrightness_t frame[ELECTRICAL_ROWS][ELECTRICAL_COLS] = {0};

typedef struct {
	GPIO_TypeDef* const port;
	const uint16_t pin;
	const GPIO_PinState activeState;
} LedPinConfig_t;

LedPinConfig_t rows[ELECTRICAL_ROWS] = {
    {GPIOB, GPIO_PIN_11, GPIO_PIN_SET},
    {GPIOB, GPIO_PIN_10, GPIO_PIN_SET},
    {GPIOB, GPIO_PIN_2, GPIO_PIN_SET},
    {GPIOB, GPIO_PIN_1, GPIO_PIN_SET},
    {GPIOB, GPIO_PIN_0, GPIO_PIN_SET},
    {GPIOA, GPIO_PIN_7, GPIO_PIN_SET},
    {GPIOA, GPIO_PIN_6, GPIO_PIN_SET},
    {GPIOA, GPIO_PIN_5, GPIO_PIN_SET},
    {GPIOA, GPIO_PIN_4, GPIO_PIN_SET},
    {GPIOA, GPIO_PIN_3, GPIO_PIN_SET}
};

LedPinConfig_t columns[ELECTRICAL_COLS] = {
    {GPIOA, GPIO_PIN_12, GPIO_PIN_RESET},
    {GPIOA, GPIO_PIN_11, GPIO_PIN_RESET},
    {GPIOA, GPIO_PIN_10, GPIO_PIN_RESET},
    {GPIOC, GPIO_PIN_7, GPIO_PIN_RESET},
    {GPIOC, GPIO_PIN_6, GPIO_PIN_RESET},
    {GPIOA, GPIO_PIN_9, GPIO_PIN_RESET},
    {GPIOA, GPIO_PIN_8, GPIO_PIN_RESET},
    {GPIOB, GPIO_PIN_15, GPIO_PIN_RESET},
    {GPIOB, GPIO_PIN_14, GPIO_PIN_RESET},
    {GPIOB, GPIO_PIN_13, GPIO_PIN_RESET}
};

void matrix_setPixel(uint8_t physX, uint8_t physY, MatrixBrightness_t value) {
    if (physX >= PHYSICAL_COLS || physY >= PHYSICAL_ROWS) {
        return;
    }

    uint8_t elecRow = 0;
    uint8_t elecCol = 0;

    if (physX < 10) {
        elecRow = physY;
        elecCol = physX;
    } else {
        elecRow = physY + 5;
        elecCol = 19 - physX;
    }

    frame[elecRow][elecCol] = value;
}


void matrix_updateMultiplex(void) {
    static uint8_t currentElecRow = 0;

    HAL_GPIO_WritePin(rows[currentElecRow].port, rows[currentElecRow].pin, rows[currentElecRow].activeState == GPIO_PIN_SET ? GPIO_PIN_RESET : GPIO_PIN_SET);

    currentElecRow++;
    if (currentElecRow >= ELECTRICAL_ROWS) {
        currentElecRow = 0;
    }

    for (uint8_t col = 0; col < ELECTRICAL_COLS; col++) {
        GPIO_PinState state;
        
        if (frame[currentElecRow][col] == MATRIX_ON) {
            state = columns[col].activeState;
        } else {
            state = (columns[col].activeState == GPIO_PIN_SET) ? GPIO_PIN_RESET : GPIO_PIN_SET;
        }
        
        HAL_GPIO_WritePin(columns[col].port, columns[col].pin, state);
    }

    HAL_GPIO_WritePin(rows[currentElecRow].port, rows[currentElecRow].pin, rows[currentElecRow].activeState);
}


