/*
 * sct.c
 *
 *  Created on: Oct 11, 2023
 *      Author: xcerny76
 */
#include "sct.h"
#include "main.h"

// array with translation table
// first index chooses display (first, second or third)
// second index chooses requested digit (0,1,2,3,4,5,6,7,8,9)
static const uint32_t reg_values[4][10] = {
		{
		//PCDE--------GFAB @ DIS1
		0b0111000000000111 << 16,
		0b0100000000000001 << 16,
		0b0011000000001011 << 16,
		0b0110000000001011 << 16,
		0b0100000000001101 << 16,
		0b0110000000001110 << 16,
		0b0111000000001110 << 16,
		0b0100000000000011 << 16,
		0b0111000000001111 << 16,
		0b0110000000001111 << 16,
	},
	{
		//----PCDEGFAB---- @ DIS2
		0b0000011101110000 << 0,
		0b0000010000010000 << 0,
		0b0000001110110000 << 0,
		0b0000011010110000 << 0,
		0b0000010011010000 << 0,
		0b0000011011100000 << 0,
		0b0000011111100000 << 0,
		0b0000010000110000 << 0,
		0b0000011111110000 << 0,
		0b0000011011110000 << 0,
	},
	{
		//PCDE--------GFAB @ DIS3
		0b0111000000000111 << 0,
		0b0100000000000001 << 0,
		0b0011000000001011 << 0,
		0b0110000000001011 << 0,
		0b0100000000001101 << 0,
		0b0110000000001110 << 0,
		0b0111000000001110 << 0,
		0b0100000000000011 << 0,
		0b0111000000001111 << 0,
		0b0110000000001111 << 0,
	},
	{
		//----43215678---- @ Knight rider LED
		0b0000000100000000 << 16,
		0b0000001100000000 << 16,
		0b0000011100000000 << 16,
		0b0000111000000000 << 16,
		0b0000110010000000 << 16,
		0b0000100011000000 << 16,
		0b0000000011100000 << 16,
		0b0000000001110000 << 16,
		0b0000000000110000 << 16,
		0b0000000000010000 << 16,
	},
};

static void tick(void)
{
	HAL_GPIO_WritePin(SCT_CLK_GPIO_Port, SCT_CLK_Pin, 1);
	HAL_GPIO_WritePin(SCT_CLK_GPIO_Port, SCT_CLK_Pin, 0);
}

static void tickLatch(void)
{
	HAL_GPIO_WritePin(SCT_NLA_GPIO_Port, SCT_NLA_Pin, 1);
	HAL_GPIO_WritePin(SCT_NLA_GPIO_Port, SCT_NLA_Pin, 0);
}

void sct_init(void)
{
	sct_led(0);
}

void sct_led(uint32_t value)
{

	for (uint8_t i = 0; i < 32; i++) {
		HAL_GPIO_WritePin(SCT_SDI_GPIO_Port, SCT_SDI_Pin, (value & 1));
		value >>= 1;
		tick();
	}
	tickLatch();
}

// sets 7seg display to display requested value and light requested number of leds
void sct_value(uint32_t value, uint32_t led)
{
	uint32_t reg = 0;
	// find digit for 1st display (hundreds)
	reg |= reg_values[0][value / 100 % 10];
	// find digit for 2nd display (tenths)
	reg |= reg_values[1][value / 10 % 10];
	// find digit for 3rd display (ones)
	reg |= reg_values[2][value / 1 % 10];
	// add LEDs above display
	reg |= reg_values[3][led];
	//send calculated req value to sct_led to display it
	sct_led(reg);
}
