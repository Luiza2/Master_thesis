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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "bme280.h"
#include "bmp388.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

SPI_HandleTypeDef hspi2;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_I2C1_Init(void);
static void MX_SPI2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
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

float temperatura;
int temperatura_setki;
float wilgotnosc;
int wilgotnosc_setki;
float cisnienie;
int cisnienie_tysiace;
int cisnienie_dziesiatki;
int cisnienie_przecinek;
float reszta;
float roznica;
float roznica_setki;
float bezposrednio;


void user_delay_ms(uint32_t period_ms);
int8_t user_i2c_write(uint8_t i2c_addr, uint8_t reg_addr, uint8_t *reg_data, uint16_t length);
int8_t user_i2c_read(uint8_t i2c_addr, uint8_t reg_addr, uint8_t *reg_data, uint16_t length);


int8_t user_i2c_read(uint8_t id, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
  if(HAL_I2C_Master_Transmit(&hi2c1, (id << 1), &reg_addr, 1, 10) != HAL_OK) return -1;
  if(HAL_I2C_Master_Receive(&hi2c1, (id << 1) | 0x01, data, len, 10) != HAL_OK) return -1;

  return 0;
}

int8_t user_i2c_write(uint8_t id, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
  int8_t *buf;
  buf = malloc(len +1);
  buf[0] = reg_addr;
  memcpy(buf +1, data, len);

  if(HAL_I2C_Master_Transmit(&hi2c1, (id << 1), (uint8_t*)buf, len + 1, HAL_MAX_DELAY) != HAL_OK) return -1;

  free(buf);
  return 0;
}

void user_delay_ms(uint32_t period)
{
  HAL_Delay(period);
}
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
  MX_USART2_UART_Init();
  MX_I2C1_Init();
  MX_SPI2_Init();
  /* USER CODE BEGIN 2 */
  uint8_t configuration[] = "AT+SETPANID ABCD";
  uint8_t wysylanie[20] = "OK";
  struct bme280_dev dev;
  struct bme280_data comp_data;
  struct bmp388_dev dev388;
  struct bmp388_data comp_data388;
  int8_t rslt = BME280_OK;
  int8_t rslt388 = BMP388_OK;

  dev.dev_id = BME280_I2C_ADDR_SEC;
  dev.intf = BME280_I2C_INTF;
  dev.read = user_i2c_read;
  dev.write = user_i2c_write;
  dev.delay_ms = user_delay_ms;

  dev388.dev_id = BMP388_I2C_ADDR_PRIM;
  dev388.intf = BMP388_I2C_INTF;
  dev388.read = user_i2c_read;
  dev388.write = user_i2c_write;
  dev388.delay_ms = user_delay_ms;

  rslt = bme280_init(&dev);
  rslt388 = bmp388_init(&dev388);

  //HAL_UART_Transmit(&huart2, wysylanie, sizeof(wysylanie), 100);

  dev.settings.osr_h = BME280_OVERSAMPLING_1X;
  dev.settings.osr_p = BME280_OVERSAMPLING_16X;
  dev.settings.osr_t = BME280_OVERSAMPLING_2X;
  dev.settings.filter = BME280_FILTER_COEFF_16;
  rslt = bme280_set_sensor_settings(BME280_OSR_PRESS_SEL | BME280_OSR_TEMP_SEL | BME280_OSR_HUM_SEL | BME280_FILTER_SEL, &dev);
  /*
  //dev388.settings.osr_h = BMP388_OVERSAMPLING_1X;
  //dev388.settings.osr_p = BMP388_OVERSAMPLING_16X;
  //dev388.settings.osr_t = BMP388_OVERSAMPLING_2X;
  //dev388.settings.filter = BMP388_FILTER_COEFF_16;
  //rslt388 = bmp388_set_sensor_settings(BMP388_OSR_PRESS_SEL | BMP388_OSR_TEMP_SEL | BMP388_OSR_HUM_SEL | BMP388_FILTER_SEL, &dev388);

*/
  HAL_StatusTypeDef status = 0;
  uint8_t data = 0x13;
  uint8_t result;
  uint32_t data_xlsb;
  uint32_t data_lsb;
  uint32_t data_msb;

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

  float par_t1 = 0;
  float par_t2 = 0;
  float par_t3 = 0;

  uint8_t temp0 = 0;
  uint8_t temp1 = 0;
  uint8_t temp2 = 0;

  uint8_t press0 = 0;
  uint8_t press1 = 0;
  uint8_t press2 = 0;
  uint32_t temperature = 0;
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

  status = HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, 0x31, 1, &T1_reg1, 1, 100);
  status = HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, 0x32, 1, &T1_reg2, 1, 100);
  status = HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, 0x33, 1, &T2_reg1, 1, 100);
  status = HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, 0x34, 1, &T2_reg2, 1, 100);
  status = HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, 0x35, 1, &T3_reg1, 1, 100);

  uint8_t config = 0x2D;
  HAL_I2C_Mem_Write(&hi2c1, BMP388_ADDRESS, BMP388_OSR, 1, &config, 1, 100);

//////////////////////////
  status = HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, 0x36, 1, &P1_reg1, 1, 100);
  status = HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, 0x37, 1, &P1_reg2, 1, 100);
  status = HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, 0x38, 1, &P2_reg1, 1, 100);
  status = HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, 0x39, 1, &P2_reg2, 1, 100);
  status = HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, 0x3A, 1, &P3_reg1, 1, 100);
  status = HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, 0x3B, 1, &P4_reg1, 1, 100);
  status = HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, 0x3C, 1, &P5_reg1, 1, 100);
  status = HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, 0x3D, 1, &P5_reg2, 1, 100);
  status = HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, 0x3E, 1, &P6_reg1, 1, 100);
  status = HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, 0x3F, 1, &P6_reg2, 1, 100);
  status = HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, 0x40, 1, &P7_reg1, 1, 100);
  status = HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, 0x41, 1, &P8_reg1, 1, 100);
  status = HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, 0x42, 1, &P9_reg1, 1, 100);
  status = HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, 0x43, 1, &P9_reg2, 1, 100);
  status = HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, 0x44, 1, &P10_reg1, 1, 100);
  status = HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, 0x45, 1, &P11_reg1, 1, 100);
  //HAL_UART_Transmit(&huart2, &P2_reg2, sizeof(P2_reg2), 100);
/////////////////////
  NVM_PAR_T1 = (((uint16_t)T1_reg2 << 8) | (uint16_t)T1_reg1);
  NVM_PAR_T2 = (((uint16_t)T2_reg2 << 8) | (uint16_t)T2_reg1);
  NVM_PAR_T3 = (uint16_t)T3_reg1;



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

  par_t1 = (float)NVM_PAR_T1*pow(2,8);//7103488
  par_t2 = (float)NVM_PAR_T2/pow(2,30);
  par_t3 = (float)NVM_PAR_T3/pow(2,48);

  //sprintf(wysylanie, "%u ", NVM_PAR_P2);
  //HAL_UART_Transmit(&huart2, &wysylanie, sizeof(wysylanie), 100);

  float par_p1 = ((float)NVM_PAR_P1-pow(2,14))/pow(2,20);
  float par_p2 = ((float)NVM_PAR_P2-pow(2,14))/pow(2,29);
  float par_p3 = (float)NVM_PAR_P3/pow(2,32);
  float par_p4 = (float)NVM_PAR_P4/pow(2,37);
  float par_p5 = (float)NVM_PAR_P5*pow(2,3);
  float par_p6 = (float)NVM_PAR_P6/pow(2,6);
  float par_p7 = (float)NVM_PAR_P7/pow(2,8);
  float par_p8 = (float)NVM_PAR_P8/pow(2,15);
  float par_p9 = (float)NVM_PAR_P9/pow(2,48);
  float par_p10 = (float)NVM_PAR_P10/pow(2,48);
  float par_p11 = (float)NVM_PAR_P11/pow(2,65);

  uint8_t odbior = 0, ustawienia = 0x06;


  HAL_I2C_Master_Transmit(&hi2c1, 0x70, &ustawienia, 1, 100);

  HAL_I2C_Mem_Write(&hi2c1, 0x70, 0x70, 1, &ustawienia, 1, 100);
  HAL_I2C_Mem_Read(&hi2c1, 0x70, 0x70, 1, &odbior, 1, 100);
  HAL_UART_Transmit(&huart2, &odbior, sizeof(odbior), 100);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  HAL_Delay(1000);
	  HAL_I2C_Master_Receive(&hi2c1, 0x71, &odbior, 1, 100);
	  //HAL_UART_Transmit(&huart2, &odbior, sizeof(odbior), 100);

	  HAL_I2C_Master_Receive(&hi2c1, 0x73, &odbior, 1, 100);
	  //HAL_UART_Transmit(&huart2, &odbior, sizeof(odbior), 100);


	  //status = HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, BMP388_CHIP_ID, 1, &result, 1, 100);
	  //HAL_UART_Transmit(&huart2, &result, sizeof(result), 100);

	  //status = HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, BMP388_STATUS, 1, &result, 1, 100);
	  //HAL_UART_Transmit(&huart2, &result, sizeof(result), 100);

	  //status = HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, BMP388_PWR_CTRL, 1, &result, 1, 100);
	  //HAL_UART_Transmit(&huart2, &result, sizeof(result), 100);

	  HAL_I2C_Mem_Write(&hi2c1, BMP388_ADDRESS, BMP388_PWR_CTRL, 1, &data, 1, 100);

	  status = HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, BMP388_TEMP_XLSB, 1, &temp0, 1, 100);
	  //HAL_UART_Transmit(&huart2, &temp0, sizeof(temp0), 100);

	  status = HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, BMP388_TEMP_LSB, 1, &temp1, 1, 100);
	  //HAL_UART_Transmit(&huart2, &temp1, sizeof(temp1), 100);

	  status = HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, BMP388_TEMP_MSB, 1, &temp2, 1, 100);
	  //HAL_UART_Transmit(&huart2, &temp2, sizeof(temp2), 100);

	  data_msb = (uint32_t)temp2 << 16;
	  data_lsb = (uint32_t)temp1 << 8;
	  data_xlsb = (uint32_t)temp0;
	  temperature = data_msb | data_lsb | data_xlsb;

      temp = (float)temperature;


	  partial_data1 = (float)(temp - par_t1);
	  partial_data2 = (float)(partial_data1 * par_t2);

	  wynik = partial_data2 +(partial_data1*partial_data1) * par_t3;

	  sprintf(wysylanie, "temp%0.2f ", wynik);
	  HAL_UART_Transmit(&huart2, &wysylanie, sizeof(wysylanie), 100);

	  status = HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, BMP388_PRESS_XLSB, 1, &press0, 1, 100);
	  //HAL_UART_Transmit(&huart2, &press0, sizeof(press0), 100);

	  status = HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, BMP388_PRESS_LSB, 1, &press1, 1, 100);
	  //HAL_UART_Transmit(&huart2, &press1, sizeof(press1), 100);

	  status = HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, BMP388_PRESS_MSB, 1, &press2, 1, 100);
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

	  sprintf(wysylanie, "cisn%0.2f ", comp_press);
	  HAL_UART_Transmit(&huart2, &wysylanie, sizeof(wysylanie), 100);

	  HAL_Delay(1000);

	  rslt = bme280_set_sensor_mode(BME280_FORCED_MODE, &dev);
	  dev.delay_ms(20);
	  //sprintf(configuration, "%d \n", rslt);
	  //HAL_UART_Transmit(&huart2, configuration, sizeof(configuration), 100);
	  rslt = bme280_get_sensor_data(BME280_ALL, &comp_data, &dev);
	  if(rslt == BME280_OK)
	  {
	      	temperatura = comp_data.temperature / 100.0;       //�C
	      	wilgotnosc = comp_data.humidity / 1024.0;            //%
	      	cisnienie = comp_data.pressure / 10000.0;           //hPa
	      	//temperatura_setki = (temperatura - (int)(comp_data.temperature/100)) * 100;
	      	//wilgotnosc_setki = (wilgotnosc - (int)(comp_data.humidity/1024))*100;
	      	//cisnienie_tysiace = (int)cisnienie / 100;
	      	//cisnienie_dziesiatki = (int)(((cisnienie / 100.0) - (int)(cisnienie / 100.0))*100);
	      	//cisnienie_przecinek = (cisnienie - (int)cisnienie) * 100;

	      	//sprintf(wysylanie, "HUMID: %0.2f ", wilgotnosc);
	      	//HAL_UART_Transmit(&huart2, wysylanie, sizeof(wysylanie), 100);

	      	sprintf(wysylanie, "TEMP: %0.2f ", temperatura);
	      	HAL_UART_Transmit(&huart2, wysylanie, sizeof(wysylanie), 100);

	      	sprintf(wysylanie, "PRES: %0.2f ", cisnienie);
	      	HAL_UART_Transmit(&huart2, wysylanie, sizeof(wysylanie), 100);
	   }
	  /*
	  HAL_Delay(1000);
	  rslt388 = bmp388_set_sensor_mode(BMP388_FORCED_MODE, &dev388);
	  dev388.delay_ms(20);

	  rslt388 = bmp388_get_sensor_data(BMP388_ALL, &comp_data388, &dev388);
	  if(rslt388 == BMP388_OK)
	  {
	  	   temperatura = comp_data388.temperature / 100.0;       //�C
	  	   wilgotnosc = comp_data388.humidity / 1024.0;            //%
	  	   cisnienie = comp_data388.pressure / 10000.0;           //hPa
	  	   //temperatura_setki = (temperatura - (int)(comp_data388.temperature/100)) * 100;
	  	   //wilgotnosc_setki = (wilgotnosc - (int)(comp_data388.humidity/1024))*100;
	  	   //cisnienie_tysiace = (int)cisnienie / 100;
	  	   //cisnienie_dziesiatki = (int)(((cisnienie / 100.0) - (int)(cisnienie / 100.0))*100);
	  	   //cisnienie_przecinek = (cisnienie - (int)cisnienie) * 100;

	  	   sprintf(wysylanie, "HUMID: %0.2f ", wilgotnosc);
	  	   HAL_UART_Transmit(&huart2, wysylanie, sizeof(wysylanie), 100);

	  	   sprintf(wysylanie, "TEMP: %0.2f ", temperatura);
	  	   HAL_UART_Transmit(&huart2, wysylanie, sizeof(wysylanie), 100);

	  	   sprintf(wysylanie, "PRES: %0.2f \n", cisnienie);
	  	   HAL_UART_Transmit(&huart2, wysylanie, sizeof(wysylanie), 100);
	  }
	   */
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

  /**Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);
  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
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
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

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

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(SPI2_GPIO_Port, SPI2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : SPI2_Pin */
  GPIO_InitStruct.Pin = SPI2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(SPI2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

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
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
