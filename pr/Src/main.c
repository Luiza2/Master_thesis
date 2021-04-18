/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2021 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "math.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define BMP388_ADDRESS 0xEC
#define BMP388_CHIP_ID 0x00
#define BMP388_STATUS 0x03
#define BMP388_PRESS_XLSB 0x04
#define BMP388_PRESS_LSB 0x05
#define BMP388_PRESS_MSB 0x06
#define BMP388_TEMP_XLSB 0x07
#define BMP388_TEMP_LSB 0x08
#define BMP388_TEMP_MSB 0x09
#define BMP388_PWR_CTRL 0x1B
#define BMP388_OSR 0x1C


#define CLK_FREQ 8000000
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
uint8_t T1_reg1 = 0;
	uint8_t T1_reg2 = 0;
	uint8_t T2_reg1 = 0;
	uint8_t T2_reg2 = 0;
	uint8_t T3_reg1 = 0;
	uint8_t P1_reg1 = 0;
	uint8_t P1_reg2 = 0;
	uint8_t P2_reg1 = 0;
	uint8_t P2_reg2 = 0;
	uint8_t P3_reg1 = 0;
	uint8_t P4_reg1 = 0;
	uint8_t P5_reg1 = 0;
	uint8_t P5_reg2 = 0;
	uint8_t P6_reg1 = 0;
	uint8_t P6_reg2 = 0;
	uint8_t P7_reg1 = 0;
	uint8_t P8_reg1 = 0;
	uint8_t P9_reg1 = 0;
	uint8_t P9_reg2 = 0;
	uint8_t P10_reg1 = 0;
	uint8_t P11_reg1 = 0;
	int16_t NVM_PAR_T1 = 0;//27748;
		int16_t NVM_PAR_T2 = 0;//18555;
		int16_t NVM_PAR_T3 = 0;//246;
		int16_t NVM_PAR_P1 = 0;
		uint16_t NVM_PAR_P2 = 0;
		int16_t NVM_PAR_P3 = 0;
		int16_t NVM_PAR_P4 = 0;
		int16_t NVM_PAR_P5 = 0;
		int16_t NVM_PAR_P6 = 0;
		int16_t NVM_PAR_P7 = 0;
		int16_t NVM_PAR_P8 = 0;
		int16_t NVM_PAR_P9 = 0;
		int16_t NVM_PAR_P10 = 0;
		int16_t NVM_PAR_P11 = 0;

		uint8_t wyslij[20] = "OK";

		float par_t1 = 0;
		  float par_t2 = 0;
		  float par_t3 = 0;

		  uint8_t temp0 = 0;
		  uint8_t temp1 = 0;
		  uint8_t temp2 = 0;

		  uint8_t press0 = 0;
		  uint8_t press1 = 0;
		  uint8_t press2 = 0;
		  float temperature = 0;
		  uint32_t pressure = 0;
		  float wynik = 0;
		  float partial_data1 = 0;
		  float partial_data2 = 0;
		  float partial_data3 = 0;
		  float partial_data4 = 0;
		  float comp_press = 0;
		  float partial_out1 = 0;
		  float partial_out2 = 0;
		  float temp = 0;
		  float pres = 0;

		  float par_p1 = 0;
		  	    float par_p2 = 0;
		  	    float par_p3 = 0;
		  	    float par_p4 = 0;
		  	    float par_p5 = 0;
		  	    float par_p6 = 0;
		  	    float par_p7 = 0;
		  	    float par_p8 = 0;
		  	    float par_p9 = 0;
		  	    float par_p10 = 0;
		  	    float par_p11 = 0;
		 volatile 	  float srednia = 0, srednia1 = 0, srednia2 = 0, srednia3;
volatile uint32_t licznik = 0;
		  	  uint32_t data_xlsb;
		  	        uint32_t data_lsb;
		  	        uint32_t data_msb;

		  	      struct bmp388_calib_data{
		  	        	uint8_t T1_reg1;
		  	        	uint8_t T1_reg2;
		  	        	uint8_t T2_reg1;
		  	        	uint8_t T2_reg2;
		  	        	uint8_t T3_reg1;
		  	        };



/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart5;
UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */



/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_UART5_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */
void BMP388_read_temp_reg(struct bmp388_calib_data *calib){
	HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, 0x31, 1, &T1_reg1 , 1, 100);
	HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, 0x32, 1, &T1_reg2, 1, 100);
	HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, 0x33, 1, &T2_reg1, 1, 100);
	HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, 0x34, 1, &T2_reg2, 1, 100);
	HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, 0x35, 1, &T3_reg1, 1, 100);
	calib->T1_reg1 = 1;
	calib->T1_reg2 = 2;
	calib->T2_reg1 = 3;
	calib->T2_reg2 = 4;

}

void BMP388_read_press_reg(void){
	HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, 0x36, 1, &P1_reg1, 1, 100);
	HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, 0x37, 1, &P1_reg2, 1, 100);
	HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, 0x38, 1, &P2_reg1, 1, 100);
	HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, 0x39, 1, &P2_reg2, 1, 100);
	HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, 0x3A, 1, &P3_reg1, 1, 100);
	HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, 0x3B, 1, &P4_reg1, 1, 100);
	HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, 0x3C, 1, &P5_reg1, 1, 100);
	HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, 0x3D, 1, &P5_reg2, 1, 100);
	HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, 0x3E, 1, &P6_reg1, 1, 100);
	HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, 0x3F, 1, &P6_reg2, 1, 100);
	HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, 0x40, 1, &P7_reg1, 1, 100);
	HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, 0x41, 1, &P8_reg1, 1, 100);
	HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, 0x42, 1, &P9_reg1, 1, 100);
	HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, 0x43, 1, &P9_reg2, 1, 100);
	HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, 0x44, 1, &P10_reg1, 1, 100);
	HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, 0x45, 1, &P11_reg1, 1, 100);
}

void BMP388_oversampling(void){
	//ustawienie oversampling temeratury i ci�nienia na x32
	uint8_t config = 0x2D;
	HAL_I2C_Mem_Write(&hi2c1, BMP388_ADDRESS, BMP388_OSR, 1, &config, 1, 100);
}

void BMP388_read_temp_coef(struct bmp388_calib_data *calib){
	NVM_PAR_T1 = (((uint16_t)T1_reg2 << 8) | (uint16_t)T1_reg1);
	NVM_PAR_T2 = (((uint16_t)T2_reg2 << 8) | (uint16_t)T2_reg1);
	NVM_PAR_T3 = (uint16_t)T3_reg1;
}

void BMP388_read_pres_coef(void){
	NVM_PAR_P1 = (((uint16_t)P1_reg2 << 8) | (uint16_t)P1_reg1);
	NVM_PAR_P2 = (((uint16_t)P2_reg2 << 8) | (uint16_t)P2_reg1);
	NVM_PAR_P3 = ((uint16_t)P3_reg1);
	NVM_PAR_P4 = ((uint16_t)P4_reg1);
	NVM_PAR_P5 = (((uint16_t)P5_reg2 << 8) | (uint16_t)P5_reg1);
	NVM_PAR_P6 = (((uint16_t)P6_reg2 << 8) | (uint16_t)P6_reg1);
	NVM_PAR_P7 = ((uint16_t)P7_reg1);
    NVM_PAR_P8 = ((uint16_t)P8_reg1);
	NVM_PAR_P9 = (((uint16_t)P9_reg2 << 8) | (uint16_t)P9_reg1);
	NVM_PAR_P10 = ((uint16_t)P10_reg1);
	NVM_PAR_P11 = ((uint16_t)P11_reg1);
}

void BMP388_calculate_temp_coef(void){
	par_t1 = (float)NVM_PAR_T1*pow(2,8);//7103488
	par_t2 = (float)NVM_PAR_T2/pow(2,30);
	par_t3 = (float)NVM_PAR_T3/pow(2,48);
}

void BMP388_calculate_pres_coef(void){
	par_p1 = ((float)NVM_PAR_P1-pow(2,14))/pow(2,20);
	par_p2 = ((float)NVM_PAR_P2-pow(2,14))/pow(2,29);
	par_p3 = (float)NVM_PAR_P3/pow(2,32);
	par_p4 = (float)NVM_PAR_P4/pow(2,37);
	par_p5 = (float)NVM_PAR_P5*pow(2,3);
	par_p6 = (float)NVM_PAR_P6/pow(2,6);
	par_p7 = (float)NVM_PAR_P7/pow(2,8);
	par_p8 = (float)NVM_PAR_P8/pow(2,15);
	par_p9 = (float)NVM_PAR_P9/pow(2,48);
	par_p10 = (float)NVM_PAR_P10/pow(2,48);
	par_p11 = (float)NVM_PAR_P11/pow(2,65);
}

void BMP_check_ID(void){
	uint8_t result = 0;
	HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, BMP388_CHIP_ID, 1, &result, 1, 100);
	HAL_UART_Transmit(&huart5, &result, sizeof(result), 100);
}

float BMP388_measure_temp(void){
	uint8_t data = 0x13;

	HAL_I2C_Mem_Write(&hi2c1, BMP388_ADDRESS, BMP388_PWR_CTRL, 1, &data, 1, 100);

	HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, BMP388_TEMP_XLSB, 1, &temp0, 1, 100);
	//HAL_UART_Transmit(&huart5, &temp0, sizeof(temp0), 100);

	HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, BMP388_TEMP_LSB, 1, &temp1, 1, 100);
	//HAL_UART_Transmit(&huart5, &temp1, sizeof(temp1), 100);

	HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, BMP388_TEMP_MSB, 1, &temp2, 1, 100);
	//HAL_UART_Transmit(&huart5, &temp2, sizeof(temp2), 100);

	data_msb = (uint32_t)temp2 << 16;
	data_lsb = (uint32_t)temp1 << 8;
	data_xlsb = (uint32_t)temp0;
	temperature = data_msb | data_lsb | data_xlsb;

	//sprintf(wyslij, "rejestr %u ", temperature);
	//HAL_UART_Transmit(&huart5, &wyslij, sizeof(wyslij), 100);

	temp = (float)temperature;

	partial_data1 = (float)(temp - par_t1);
	partial_data2 = (float)(partial_data1 * par_t2);

	//sprintf(wyslij, "partial1 %f ", partial_data1);
	//HAL_UART_Transmit(&huart5, &wyslij, sizeof(wyslij), 100);

	//sprintf(wyslij, "partial2 %f ", partial_data2);
	//HAL_UART_Transmit(&huart5, &wyslij, sizeof(wyslij), 100);

	wynik = partial_data2 +(partial_data1*partial_data1) * par_t3;

	//sprintf(wyslij, "wynik %f ", wynik);
	//HAL_UART_Transmit(&huart5, &wyslij, sizeof(wyslij), 100);

	return wynik;
}

float BMP388_measure_press(void){
	HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, BMP388_PRESS_XLSB, 1, &press0, 1, 100);
	//HAL_UART_Transmit(&huart2, &press0, sizeof(press0), 100);

	HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, BMP388_PRESS_LSB, 1, &press1, 1, 100);
	//HAL_UART_Transmit(&huart2, &press1, sizeof(press1), 100);

	HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, BMP388_PRESS_MSB, 1, &press2, 1, 100);
	//HAL_UART_Transmit(&huart2, &press2, sizeof(press2), 100);

	data_msb = (uint32_t)press2 << 16;
	data_lsb = (uint32_t)press1 << 8;
	data_xlsb = (uint32_t)press0;
	pressure = data_msb | data_lsb | data_xlsb;//ok

	pres = (float)pressure;//ok policzone dla cisnienia 1000 i temp 25

	partial_data1 = par_p6*wynik;//ok 11833,59375
	partial_data2 = par_p7*(wynik*wynik);//ok 593,261719
	partial_data3 = par_p8*(wynik*wynik*wynik);//ok 117,301941
	partial_out1 = par_p5 + partial_data1 + partial_data2 + partial_data3;//ok 210312,15625

	partial_data1 = par_p2*wynik;//ok 0,002192
	partial_data2 = par_p3*(wynik*wynik);//ok 0,00000509317
	partial_data3 = par_p4*(wynik*wynik*wynik);//ok 0
	partial_out2 = pres *(par_p1 +  partial_data1 + partial_data2 + partial_data3);//ok -12,75555896759

	partial_data1 = pres * pres;// 1000000
	partial_data2 = par_p9 + par_p10 * wynik;//ok 6,05*10^(-11)
	partial_data3 = partial_data1 * partial_data2;//ok 0,000060584425
	partial_data4 = partial_data3 + (pres *pres*pres)*par_p11;//ok 0,000060589737
	comp_press = (partial_out1+partial_out2+partial_data4);

	return comp_press;
}

void BMP388_init(struct bmp388_calib_data *calib){
	//odczyt rejestr�w temperatury
	BMP388_read_temp_reg(calib);
	//ustawienie oversampling temeratury i ci�nienia na x32
	BMP388_oversampling();
	//odczyt rejestr�w ci�nienia
	BMP388_read_press_reg();
	//odczyt wsp�czynnik�w temperatury
	BMP388_read_temp_coef(calib);
	//odczyt wsp�czynnik�w ci�nienia
	BMP388_read_pres_coef();
	//obliczenie temperatury
	BMP388_calculate_temp_coef();
	//obliczenie ci�nienia
	BMP388_calculate_pres_coef();
}

void GPIO_stage1_method1(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};


  //pb1 output high
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);

  //pb0 input high impedance
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void GPIO_stage2_method1(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  //pb1 input high impedance - interrupt
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  //uruchomienie przerwania
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  //PB0 output 0
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);

  //zerowanie timera
  __HAL_TIM_SET_COUNTER(&htim2, 0);
  //uruchomienie timera
  HAL_TIM_Base_Start(&htim2);
}

void pt1000_temp_meas_method1(void){
	uint32_t suma = 0;
	float resistance = 0;
	srednia = 0;
	float time_us = 0, time = 0;
	float delta = 0;
	for(int i = 0 ; i < 20; i++){
		GPIO_stage1_method1();//T1 output high, T2 input high impedance
		HAL_Delay(1);
		GPIO_stage2_method1();
		HAL_Delay(1);
		suma += licznik;
		srednia = (float)suma/20;
	}
	time_us = 1000000*srednia/CLK_FREQ;
	time = srednia/CLK_FREQ;
	//sprintf(wyslij, "time_us %f ", time_us);
	//HAL_UART_Transmit(&huart5, &wyslij, sizeof(wyslij), 100);

	resistance = (time+0.000013)/0.00000010116;
	//sprintf(wyslij, "resistance %f ", resistance);
	//HAL_UART_Transmit(&huart5, &wyslij, sizeof(wyslij), 100);

	delta = 0.0000152748 + 0.00000231 * (1-resistance/1000);
	temperature = (0.0039083-sqrt(delta))/(0.000001155);

	//sprintf(wyslij, "delta %f ", sqrt(delta));
	//HAL_UART_Transmit(&huart5, &wyslij, sizeof(wyslij), 100);

	sprintf(wyslij, "temp PT1000 %f ", temperature);
	HAL_UART_Transmit(&huart5, &wyslij, sizeof(wyslij), 100);
}

void GPIO_stage1_method2(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  //pb1 output high
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);

  //pb0 input high impedance
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  //pc5 input high impedance
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

void GPIO_stage2_method2(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  //pb1 input high impedance - interrupt
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  //uruchomienie przerwania
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  //PB0 output 0
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);

  //zerowanie timera
  __HAL_TIM_SET_COUNTER(&htim2, 0);
  //uruchomienie timera
  HAL_TIM_Base_Start(&htim2);
}

void GPIO_stage3_method2(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  //pb1 input high impedance - interrupt
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  //uruchomienie przerwania
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  //PC5 output 0
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);

  //zerowanie timera
  __HAL_TIM_SET_COUNTER(&htim2, 0);
  //uruchomienie timera
  HAL_TIM_Base_Start(&htim2);
}

void pt1000_temp_meas_method2(void){
	float time_us1 = 0, time_us2 = 0, resistance = 0, suma1 = 0, suma2 = 0;

	for(int i = 0 ; i < 20; i++){
		GPIO_stage1_method2();
		HAL_Delay(1);
		GPIO_stage2_method2();
		HAL_Delay(1);

		time_us1 = 1000000*(float)licznik/CLK_FREQ;

		suma1 += licznik;

		//sprintf(wyslij, "time_us1 %f ", time_us1);
		//HAL_UART_Transmit(&huart5, &wyslij, sizeof(wyslij), 100);
		//HAL_Delay(100);

		GPIO_stage1_method2();
		HAL_Delay(1);
		GPIO_stage3_method2();
		HAL_Delay(1);

		suma2 += licznik;


		time_us2 = 1000000*(float)licznik/CLK_FREQ;

		//sprintf(wyslij, "time_us2 %f ", time_us2);
		//HAL_UART_Transmit(&huart5, &wyslij, sizeof(wyslij), 100);
		//HAL_Delay(100);
	}
	srednia1 = (float)suma1/20;
	srednia2 = (float)suma2/20;
	resistance = srednia1/srednia2*1100;
	sprintf(wyslij, "res2 %f ", resistance);
	HAL_UART_Transmit(&huart5, &wyslij, sizeof(wyslij), 100);
}

void GPIO_stage1_method3(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  //pb1 output high
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);

  //pb0 input high impedance
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  //pc5 input high impedance
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  //pc4 input high impedance
  GPIO_InitStruct.Pin = GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

void GPIO_stage2_method3(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  //pb1 input high impedance - interrupt
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  //uruchomienie przerwania
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  //PB0 output 0
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);

  //zerowanie timera
  __HAL_TIM_SET_COUNTER(&htim2, 0);
  //uruchomienie timera
  HAL_TIM_Base_Start(&htim2);
}

void GPIO_stage3_method3(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  //pb1 input high impedance - interrupt
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  //uruchomienie przerwania
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  //PC5 output 0
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);

  //zerowanie timera
  __HAL_TIM_SET_COUNTER(&htim2, 0);
  //uruchomienie timera
  HAL_TIM_Base_Start(&htim2);
}

void GPIO_stage4_method3(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  //pb1 input high impedance - interrupt
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  //uruchomienie przerwania
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  //PC4 output 0
  GPIO_InitStruct.Pin = GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);

  //zerowanie timera
  __HAL_TIM_SET_COUNTER(&htim2, 0);
  //uruchomienie timera
  HAL_TIM_Base_Start(&htim2);
}

void pt1000_temp_meas_method3(void){
	float time_us1 = 0, time_us2 = 0, time_us3 = 0, resistance = 0, suma1 = 0, suma2 = 0, suma3 = 0;
	for(int i = 0 ; i < 20; i++){
		GPIO_stage1_method3();
		HAL_Delay(1);
		GPIO_stage2_method3();
		HAL_Delay(1);

		suma1 += licznik;
		time_us1 = 1000000*(float)licznik/CLK_FREQ;

		GPIO_stage1_method3();
		HAL_Delay(1);
		GPIO_stage3_method3();
		HAL_Delay(1);

		suma2 += licznik;
		time_us2 = 1000000*(float)licznik/CLK_FREQ;

		GPIO_stage1_method3();
		HAL_Delay(1);
		GPIO_stage4_method3();
		HAL_Delay(1);

		suma3 += licznik;
		time_us3 = 1000000*(float)licznik/CLK_FREQ;
	}
	srednia1 = (float)suma1/20;
	srednia2 = (float)suma2/20;
	srednia3 = (float)suma3/20;

	//resistance = (srednia1 - srednia2)/(srednia3 - srednia2)*(1330 - 950) + 950;//two point calibration
	resistance = (srednia1 - srednia2)/(srednia3 - srednia2)*1330;//three signal measurement version

	sprintf(wyslij, "resistance %f ", resistance);
	HAL_UART_Transmit(&huart5, &wyslij, sizeof(wyslij), 100);
	HAL_Delay(100);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	if(GPIO_Pin == GPIO_PIN_0){
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_2);
	}else if(GPIO_Pin == GPIO_PIN_1)
	{
	    HAL_TIM_Base_Stop(&htim2);
	    licznik = __HAL_TIM_GET_COUNTER(&htim2);

	    //sprintf(wyslij, "przerwanie %u ", licznik);
	    //HAL_UART_Transmit(&huart5, &wyslij, sizeof(wyslij), 100);
	}
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_USART1_UART_Init();
  MX_UART5_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */

  uint8_t wysylanie[20] = "                    ";
  uint32_t licznik = 0;

  struct bmp388_calib_data calib_data;
  BMP388_init(&calib_data);
  HAL_Delay(2000);

  pt1000_temp_meas_method1();


  /*
  HAL_TIM_Base_Start(&htim2);
  HAL_TIM_Base_Stop(&htim2);
  licznik = __HAL_TIM_GET_COUNTER(&htim2);
  sprintf(wyslij, "licznik: %u ", licznik);
  HAL_UART_Transmit(&huart5, &wyslij, sizeof(wyslij), 100);
  __HAL_TIM_SET_COUNTER(&htim2, 0);

  licznik = __HAL_TIM_GET_COUNTER(&htim2);
    sprintf(wyslij, "po zerowaniu: %u ", licznik);
    HAL_UART_Transmit(&huart5, &wyslij, sizeof(wyslij), 100);
  */
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  pt1000_temp_meas_method3();

	  //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);
	  //HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
	  //HAL_Delay(1000);

	  //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET);
	  //HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
	  //HAL_Delay(1000);



	  //licznik = __HAL_TIM_GET_COUNTER(&htim2);

	  //sprintf(wysylanie, "%u ", licznik);
	  //HAL_UART_Transmit(&huart5, &wysylanie, sizeof(wysylanie), 100);

/*
	  wynik = BMP388_measure_temp();
	  wynik -= 4;

	  sprintf(wysylanie, "temp%0.2f ", wynik);
	  HAL_UART_Transmit(&huart5, &wysylanie, sizeof(wysylanie), 100);

	  wynik = BMP388_measure_press();
	  wynik /= 128;

	  sprintf(wysylanie, "cisn%0.2f ", wynik);
	  HAL_UART_Transmit(&huart5, &wysylanie, sizeof(wysylanie), 100);*/

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_UART5
                              |RCC_PERIPHCLK_I2C1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInit.Uart5ClockSelection = RCC_UART5CLKSOURCE_PCLK1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
  /**Configure the main internal regulator output voltage 
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x00707CBB;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /**Configure Analogue filter 
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /**Configure Digital filter 
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 4294967295;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief UART5 Initialization Function
  * @param None
  * @retval None
  */
static void MX_UART5_Init(void)
{

  /* USER CODE BEGIN UART5_Init 0 */

  /* USER CODE END UART5_Init 0 */

  /* USER CODE BEGIN UART5_Init 1 */

  /* USER CODE END UART5_Init 1 */
  huart5.Instance = UART5;
  huart5.Init.BaudRate = 115200;
  huart5.Init.WordLength = UART_WORDLENGTH_8B;
  huart5.Init.StopBits = UART_STOPBITS_1;
  huart5.Init.Parity = UART_PARITY_NONE;
  huart5.Init.Mode = UART_MODE_TX_RX;
  huart5.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart5.Init.OverSampling = UART_OVERSAMPLING_16;
  huart5.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart5.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart5) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN UART5_Init 2 */

  /* USER CODE END UART5_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED3_Pin|LED2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, T4_Pin|T3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, T2_Pin|HUM_AC_Pin|HUM_PIN_Pin|STM_KEY_Pin 
                          |BLE_ON_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LED3_Pin LED2_Pin */
  GPIO_InitStruct.Pin = LED3_Pin|LED2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PA4 */
  GPIO_InitStruct.Pin = GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : T4_Pin T3_Pin */
  GPIO_InitStruct.Pin = T4_Pin|T3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : T2_Pin HUM_AC_Pin HUM_PIN_Pin STM_KEY_Pin 
                           BLE_ON_Pin */
  GPIO_InitStruct.Pin = T2_Pin|HUM_AC_Pin|HUM_PIN_Pin|STM_KEY_Pin 
                          |BLE_ON_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PB1 */
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PB11 */
  GPIO_InitStruct.Pin = GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
