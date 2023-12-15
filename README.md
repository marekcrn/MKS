## Periferie

### LEDs 
LED1 = GPIO_Output @ PA4
LED2 = GPIO_Output @ PB0

### Buttons
S1 = GPIO_Input @ PC1 + Pull-up
S2 = GPIO_EXTI0 @ PC0 + Pull-up
povolení přerušení EXTI0: System Core / NVIC / NVIC / EXTI line 0 and 1 interrupts

### LED displej
SCT_NLA = GPIO_Output @ PB5
SCT_SDI = GPIO_Output @ PB4
SCT_CLK = GPIO_Output @ PB3
SCT_NOE = GPIO_Output @ PB10
#include "sct.h" sct.c; sct.h 
inicializaci LED driveru v USER CODE 2: sct_init();

### Rotační enkodér
časovač TIM1 = Combined Channels na Encoder Mode
Tím se aktivují piny PA8 a PA9, na které je enkodér připojený
inverze směru = Polarity na Falling Edge
omezení =  Counter Period (AutoReload)
aktivace v USER CODE 2: HAL_TIM_Encoder_Start(&htim1, htim1.Channel);
hodnota = __HAL_TIM_GET_COUNTER(&htim1);

### ADC - trimer R2
vstup ADC (IN0)
Zvolte kontinuální režim převodu (Continuous Conversion Mode)
maximální dobu vzorkování (Sampling Time = 239.5 Cycles)
vhodné zvolit přepisování dat při přetečení (Overrun data overwritten, nastává během ladění)
Povolte ADC global interrupt
USER CODE 0:
static volatile uint32_t raw_pot;
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
 raw_pot = HAL_ADC_GetValue(hadc);
}
USER CODE 2:
HAL_ADCEx_Calibration_Start(&hadc);
HAL_ADC_Start_IT(&hadc);

### Čidla
USER CODE 2:
/* Temperature sensor calibration value address */
#define TEMP110_CAL_ADDR ((uint16_t*) ((uint32_t) 0x1FFFF7C2))
#define TEMP30_CAL_ADDR ((uint16_t*) ((uint32_t) 0x1FFFF7B8))
/* Internal voltage reference calibration value address */
#define VREFINT_CAL_ADDR ((uint16_t*) ((uint32_t) 0x1FFFF7BA))

## Cvičení

1) Blikání LED
2) ISR, tlačítka se zákmity, časovač SysTick
3) LED displej na posuvném registru
4) A/D převodník a bargraf, čidla
5) UART komunikace s DMA, EEPROM na I2C
6) Teplotní čidla DS18B20 a NTC
7) Systém FreeRTOS a obsluha akcelerometru
8) NXP
9) NXP
10) Maticová klávesnice a kódový zámek
11) USB myš standardu HID
12) Ethernet, TCP klient a server