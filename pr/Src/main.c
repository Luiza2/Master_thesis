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



#define CLK_FREQ 80000000
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
uint8_t kasowanie_flasha1 = 0, kasowanie_flasha2 = 0, ble1 = 0, ble2 = 0, wlacz_ble = 0;
uint8_t wysylanie[20] = "              ";
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
volatile float srednia = 0, srednia1 = 0, srednia2 = 0, srednia3;
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
COMP_HandleTypeDef hcomp1;

DAC_HandleTypeDef hdac1;

I2C_HandleTypeDef hi2c1;

RTC_HandleTypeDef hrtc;

SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart5;
UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
RTC_TimeTypeDef RtcTime;
RTC_DateTypeDef RtcDate;


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_UART5_Init(void);
static void MX_TIM2_Init(void);
static void MX_DAC1_Init(void);
static void MX_COMP1_Init(void);
static void MX_RTC_Init(void);
static void MX_SPI1_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

uint8_t	M25P32_Spi(uint8_t	Data)
{
	uint8_t	ret;
	HAL_SPI_TransmitReceive(&hspi1,&Data,&ret,1,100);
	return ret;
}

uint8_t * M25P32_ReadID(void)
{
  static uint8_t temp[10];
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
  M25P32_Spi(0x9F);
  temp[0] = M25P32_Spi(0x00);
  temp[1] = M25P32_Spi(0x00);
  temp[2] = M25P32_Spi(0x00);
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
  HAL_UART_Transmit(&huart5, temp, sizeof(temp), 100);

  return temp;
}

void M25P32_WriteByte(uint32_t address, uint8_t byte)
{
	uint8_t adres[3] = {0x00, 0x00, 0x00};
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
	M25P32_Spi(0x06);//write enable
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
	M25P32_Spi(0x02);//page program

	adres[0] = address>>16;
	adres[1] = address>>8;
	adres[2] = address;

	M25P32_Spi(adres[0]);
	M25P32_Spi(adres[1]);
	M25P32_Spi(adres[2]);
	M25P32_Spi(byte);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
	HAL_Delay(1);
}

void M25P32_ReadByte(uint32_t address, uint32_t value)
{
	uint8_t odczyt[10] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
	M25P32_Spi(0x0B);
	M25P32_Spi(address>>16);
	M25P32_Spi(address>>8);
	M25P32_Spi(address);
	M25P32_Spi(0);
	for(int i = 0 ; i < value; i++)
	{
		odczyt[0] = W25P32_Spi(0x00);
		HAL_UART_Transmit(&huart5, odczyt, 1, 100);
	}
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
	/*odczyt[0] = W25P32_Spi(0x00);
	odczyt[1] = W25P32_Spi(0x00);
	odczyt[2] = W25P32_Spi(0x00);
	odczyt[3] = W25P32_Spi(0x00);
	odczyt[4] = W25P32_Spi(0x00);
	odczyt[5] = W25P32_Spi(0x00);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
	HAL_UART_Transmit(&huart5, odczyt, sizeof(odczyt), 100);*/
}

void M25P32_ReadBluetoothByte(uint32_t address, uint32_t value)
{
	float temperatura, cisnienie, wilgotnosc;
	uint32_t cisn = 0;
	uint16_t temp = 0, wilg = 0, nat_osw = 0;
	uint8_t odczyt[15], send[60] = {"                                                                                "};
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
	M25P32_Spi(0x0B);
	M25P32_Spi(address>>16);
	M25P32_Spi(address>>8);
	M25P32_Spi(address);
	M25P32_Spi(0);
	for(int i = 0 ; i < value; i++)
	{
		odczyt[i] = M25P32_Spi(0x00);
		//HAL_UART_Transmit(&huart5, odczyt, 1, 100);
	}

	//formatowanie danych
	temp = odczyt[5];
	temp <<= 8;
	temp |= odczyt[6];
	temperatura = (float)temp;
	temperatura /= 100;

	cisn = odczyt[7];
	cisn <<= 8;
	cisn |= odczyt[8];
	cisn <<= 8;
	cisn |= odczyt[9];
	cisnienie = (float)cisn;
	cisnienie /= 100;

	wilg = odczyt[10];
	wilg <<= 8;
	wilg |= odczyt[11];
	wilgotnosc = (float)wilg;
	wilgotnosc /= 100;

	nat_osw = odczyt[13];
	nat_osw <<= 8;
	nat_osw |= odczyt[14];

	sprintf(send, "%d-%d-%d,%d:%d,%0.2f,%0.2f,%0.2f,%d,%d\n", odczyt[0], odczyt[1], odczyt[2], odczyt[3], odczyt[4], temperatura, cisnienie, wilgotnosc, odczyt[12], nat_osw);
	HAL_UART_Transmit(&huart5, send, sizeof(send), 100);
	HAL_UART_Transmit(&huart1, send, sizeof(send), 100);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
}

uint8_t M25P32_ReadOneByte(uint32_t address)
{
	uint8_t odczyt[10] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
	M25P32_Spi(0x0B);
	M25P32_Spi(address>>16);
	M25P32_Spi(address>>8);
	M25P32_Spi(address);
	M25P32_Spi(0);
	odczyt[0] = M25P32_Spi(0x00);
	//HAL_UART_Transmit(&huart5, odczyt, 1, 100);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);

	return odczyt[0];
}

uint32_t M25P32_CheckFreeAddress()
{
	uint8_t first, second, wyslij[30];
	uint32_t free = 0;

	for(uint32_t i = 0; i < 0x400000; i++)
	{
		first = M25P32_ReadOneByte(i);
		//HAL_UART_Transmit(&huart5, wyslij, 1, 100);
		//HAL_Delay(2);
		second = M25P32_ReadOneByte(i+1);
		//HAL_Delay(300);
		if(first == 0xFF && second == 0xFF)
		{
			free = i;
			sprintf(wyslij, " Pierwszy wolny adres to %d ", i);
			//HAL_UART_Transmit(&huart5, wyslij, sizeof(wyslij), 100);
			return free;
			break;
		}
	}
}

void M25P32_WaitForWriteEnd()
{
	uint8_t status = 0, wyslij[10];
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
	M25P32_Spi(0x05);//read status register
	do
	{
		status = M25P32_Spi(0x00);//nic nie znaczacy bajt
		//sprintf(wyslij, " zajete %d ", 0x00);
		//HAL_UART_Transmit(&huart5, wyslij, sizeof(wyslij), 100);
		HAL_Delay(1);
	} while((status & 0x01) == 0x01);//bit 1 odpowiada za status pamieci, 1 oznacza write in progress
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
}

void M25P32_Erase()
{
	uint8_t wyslij[10] = {"kasowanie"};
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
	M25P32_Spi(0x06);//write enable
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
	M25P32_Spi(0xC7);//bulk erase
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
	HAL_UART_Transmit(&huart5, wyslij, sizeof(wyslij), 100);
	M25P32_WaitForWriteEnd();
}

void M25P32_DeepPowerDown()
{
	uint8_t wyslij[10];
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
	M25P32_Spi(0xB9);//deep power down
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
	sprintf(wyslij, " power down", 0x00);
	HAL_UART_Transmit(&huart5, wyslij, sizeof(wyslij), 100);
}

void M25P32_WakeUp()
{
	uint8_t wyslij[10];
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_RESET);
	M25P32_Spi(0xAB);//release from deep power down
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_4,GPIO_PIN_SET);
	sprintf(wyslij, " wakeup %d ", 0x00);
	HAL_UART_Transmit(&huart5, wyslij, sizeof(wyslij), 100);
}

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
	//HAL_UART_Transmit(&huart5, &P1_reg1, sizeof(P1_reg1), 100);
	HAL_I2C_Mem_Read(&hi2c1, BMP388_ADDRESS, 0x37, 1, &P1_reg2, 1, 100);
	//HAL_UART_Transmit(&huart5, &P1_reg2, sizeof(P1_reg2), 100);
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
	//ustawienie oversampling temeratury i ciśnienia na x32
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
	//wynik to temperatura z PT1000
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
	//odczyt rejestrów temperatury
	BMP388_read_temp_reg(calib);
	//ustawienie oversampling temeratury i ciśnienia na x32
	BMP388_oversampling();
	//odczyt rejestrów ciśnienia
	BMP388_read_press_reg();
	//odczyt współczynników temperatury
	BMP388_read_temp_coef(calib);
	//odczyt współczynników ciśnienia
	BMP388_read_pres_coef();
	//obliczenie temperatury
	BMP388_calculate_temp_coef();
	//obliczenie ciśnienia
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
	float resistance = 0;
	float  time = 0;
	float delta = 0;

	GPIO_stage1_method1();//T1 output high, T2 input high impedance
	HAL_Delay(10);
	GPIO_stage2_method1();
	HAL_Delay(10);

	time = (float)licznik/CLK_FREQ;
	//sprintf(wyslij, "time_us %0.10f ", time);
	//HAL_UART_Transmit(&huart5, &wyslij, sizeof(wyslij), 100);

	resistance = (time)/0.00000009157261323;
	sprintf(wyslij, "%f ", resistance);
	HAL_UART_Transmit(&huart5, &wyslij, 10, 100);

	delta = 0.0000152748 + 0.00000231 * (1-resistance/1000);
	temperature = (0.0039083-sqrt(delta))/(0.000001155);

	//sprintf(wyslij, "delta %f ", sqrt(delta));
	//HAL_UART_Transmit(&huart5, &wyslij, sizeof(wyslij), 100);

	//sprintf(wyslij, "%f", temperature);
	//HAL_UART_Transmit(&huart5, &wyslij, 9, 100);
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
	float licznik1 = 0, licznik2 = 0;

	GPIO_stage1_method2();
	HAL_Delay(10);
	GPIO_stage2_method2();
	HAL_Delay(10);
	licznik1 = (float)licznik;

	//sprintf(wyslij, "time_us1 %f ", time_us1);
	//HAL_UART_Transmit(&huart5, &wyslij, sizeof(wyslij), 100);
	//HAL_Delay(100);

	GPIO_stage1_method2();
	HAL_Delay(10);
	GPIO_stage3_method2();
	HAL_Delay(10);
	licznik2= (float)licznik;

	//sprintf(wyslij, "time_us2 %f ", time_us2);
	//HAL_UART_Transmit(&huart5, &wyslij, sizeof(wyslij), 100);
	//HAL_Delay(100);

	resistance = licznik1/licznik2*1100.1;
	sprintf(wyslij, "%f ", resistance);
	HAL_UART_Transmit(&huart5, &wyslij, 10, 100);
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

void GPIO_stage5_method3(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  //pb1 input high impedance
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

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

void pt1000_temp_meas_method3(void){//funkcja którą badałam dokładnośc metod
	float time_us1 = 0, time_us2 = 0, time_us3 = 0, resistance = 0, suma1 = 0, suma2 = 0, suma3 = 0;
	float licznik1=0, licznik2=0, licznik3=0;

	GPIO_stage1_method3();
	HAL_Delay(2);
	GPIO_stage2_method3();
	HAL_Delay(2);
	licznik1 = (float)licznik;

	GPIO_stage1_method3();
	HAL_Delay(2);
	GPIO_stage3_method3();
	HAL_Delay(2);

	licznik2 = (float)licznik;

	GPIO_stage1_method3();
	HAL_Delay(2);
	GPIO_stage4_method3();
	HAL_Delay(2);

	licznik3 = (float)licznik;

	resistance = (licznik1 - licznik2)/(licznik3 - licznik2)*(1330.07 - 942.25) + 942.25;//two point calibration
	//resistance = (licznik1 - licznik2)/(licznik3 - licznik2)*1330.07;//three signal measurement version

	sprintf(wyslij, " %f ", resistance);
	HAL_UART_Transmit(&huart5, &wyslij, 10, 100);
}

float pt1000_temp_meas_method32(void){//funkcja do programu, wylicza srednia z x pomiarow
	float time_us1 = 0, time_us2 = 0, time_us3 = 0, resistance = 0, suma1 = 0, suma2 = 0, suma3 = 0;
	float licznik1=0, licznik2=0, licznik3=0;
	float  time = 0;
	float delta = 0;
	uint16_t petle = 64;

	for(int i = 0 ; i < petle; i++)
	  {
		GPIO_stage1_method3();
		HAL_Delay(1);
		GPIO_stage2_method3();
		HAL_Delay(1);
		licznik1 = (float)licznik;
		suma1 += licznik1;

		GPIO_stage1_method3();
		HAL_Delay(1);
		GPIO_stage3_method3();
		HAL_Delay(1);
		licznik2 = (float)licznik;
		suma2 += licznik2;

		GPIO_stage1_method3();
		HAL_Delay(1);
		GPIO_stage4_method3();
		HAL_Delay(1);
		licznik3 = (float)licznik;
		suma3 += licznik3;
	  }
	GPIO_stage5_method3();
	licznik1 = suma1/petle;
	licznik2 = suma2/petle;
	licznik3 = suma3/petle;

	resistance = (licznik1 - licznik2)/(licznik3 - licznik2)*(1330.07 - 942.25) + 942.25;//two point calibration
	//resistance = (licznik1 - licznik2)/(licznik3 - licznik2)*1330.07;//three signal measurement version

	//sprintf(wyslij, " %f ", resistance);
	//HAL_UART_Transmit(&huart5, &wyslij, 10, 100);

	delta = 0.0000152748 + 0.00000231 * (1-resistance/1000);
	temperature = (0.0039083-sqrt(delta))/(0.000001155);

	//sprintf(wyslij, "temp %f ", temperature);
	//HAL_UART_Transmit(&huart5, &wyslij, 20, 100);

	return temperature;
}

void HSL1101_hum_meas(void){
	//obecnie metoda z komparatorem
	float time = 0, pojemnosc = 0;

	//zerowanie timera
	__HAL_TIM_SET_COUNTER(&htim2, 0);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);
	//uruchomienie timera
	HAL_TIM_Base_Start(&htim2);
	HAL_Delay(1);

	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET);
	HAL_Delay(1);
	//pierwsza wersja czyli liczenie wszystkiego na piechote
	time = (float)licznik*1000000/CLK_FREQ;

	pojemnosc = time/1.667485266;//pojemnosc


	//kompensacja pojemnosci na podstawie samego licznika
	//pojemnosc = licznik*0.0074-12.859;

	//sprintf(wyslij, "%u ", licznik);
	//HAL_UART_Transmit(&huart5, &wyslij, 6, 100);

	//sprintf(wyslij, "%.12f ", pojemnosc);
	//HAL_UART_Transmit(&huart5, &wyslij, 16, 100);
}

void HAL_COMP_TriggerCallback(COMP_HandleTypeDef *hcomp){
	//HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_3);
	HAL_TIM_Base_Stop(&htim2);
	licznik = __HAL_TIM_GET_COUNTER(&htim2);
	//sprintf(wyslij, "%u ", licznik);
	//HAL_UART_Transmit(&huart5, &wyslij, 6, 100);
}

uint8_t VEML6070(void){
	uint8_t data1 = 0x06, read = 0, MSB = 0, LSB = 0, UV_index = 0, low_power = 0x02;
	uint16_t light_data = 0;
	HAL_I2C_Master_Receive(&hi2c1, 0x19, &read, sizeof(read),100);
	HAL_I2C_Master_Transmit(&hi2c1, 0x70, &data1, sizeof(data1), 100);
	HAL_I2C_Master_Receive(&hi2c1, 0x71, &LSB, sizeof(LSB),100);
	HAL_I2C_Master_Receive(&hi2c1, 0x73, &MSB, sizeof(MSB),100);

	light_data = MSB << 8 | LSB;

	//sprintf(wyslij, "%u ", light_data);
	//HAL_UART_Transmit(&huart5, &wyslij, sizeof(wyslij), 100);
	//HAL_Delay(1);

	if(light_data >= 0 && light_data <=560){
		UV_index = 0;//Low
	}else if(light_data >= 561 && light_data <=1120){
		UV_index = 1;//Moderate
	}else if(light_data >= 1121 && light_data <=1494){
		UV_index = 2;//High
	}else if(light_data >= 1495 && light_data <=2054){
		UV_index = 3;//Very High
	}else if(light_data >= 2055){
		UV_index = 4;//Extreme
	}
	//HAL_I2C_Master_Receive(&hi2c1, 0x19, &read, sizeof(read),100);
	//HAL_I2C_Master_Transmit(&hi2c1, 0x70, &low_power, sizeof(low_power), 100);
	//sprintf(wyslij, "index UV: %u ", UV_index);
	//HAL_UART_Transmit(&huart5, &wyslij, sizeof(wyslij), 100);
	return UV_index;
}

uint16_t BH1750(void){
	uint8_t data1 = 0x21, value[2] = {0, 0};
	uint16_t light_value = 0;
	HAL_I2C_Master_Transmit(&hi2c1, 0xB8, &data1, sizeof(data1), 100);
	HAL_I2C_Master_Receive(&hi2c1, 0xB9, value, 2, 100);

	light_value = value[0] << 8 | value[1];

	//sprintf(wyslij, "%u[lx]", light_value);
	//HAL_UART_Transmit(&huart5, &wyslij, sizeof(wyslij), 100);
	return light_value;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	GPIO_PinState status;
	if(GPIO_Pin == GPIO_PIN_0){

		ble1++;
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_3);
		sprintf(wyslij, "zmienna BLE 1 %d ", ble1);
		HAL_UART_Transmit(&huart5, &wyslij, sizeof(wyslij), 100);
		if(ble1 == 3) ble1 = 0;
	}
	if(GPIO_Pin == GPIO_PIN_1)
	{
	    HAL_TIM_Base_Stop(&htim2);
	    licznik = __HAL_TIM_GET_COUNTER(&htim2);
	    //HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_3);
	    //sprintf(wyslij, "przerwanie %u ", licznik);
	    //HAL_UART_Transmit(&huart5, &wyslij, sizeof(wyslij), 100);
	}else if(GPIO_Pin == GPIO_PIN_2)
	{
	    HAL_TIM_Base_Stop(&htim2);
	    licznik = __HAL_TIM_GET_COUNTER(&htim2);

	    sprintf(wyslij, "przerwanie %u ", licznik);
	    HAL_UART_Transmit(&huart5, &wyslij, sizeof(wyslij), 100);
	}else if(GPIO_Pin == GPIO_PIN_13)
	{

		ble2++;
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_2);
		sprintf(wyslij, "zmienna BLE 2 %d ", ble1);
		HAL_UART_Transmit(&huart5, &wyslij, sizeof(wyslij), 100);
		if(ble2 == 3) ble2 = 0;
	}
}

void GPIO_stage1_humidity(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  //pb2 output high
  GPIO_InitStruct.Pin = GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);

  //pb10 input high impedance
  GPIO_InitStruct.Pin = GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void GPIO_stage2_humidity(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  //pb2 input high impedance - interrupt
  GPIO_InitStruct.Pin = GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  //uruchomienie przerwania
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);
  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  //PB10 output 0
  GPIO_InitStruct.Pin = GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET);

  //zerowanie timera
  __HAL_TIM_SET_COUNTER(&htim2, 0);
  //uruchomienie timera
  HAL_TIM_Base_Start(&htim2);
}

float measure_humidity(void){//pomiar metoda z komparatorem
	//pomiar wilgotnosci
	uint32_t suma = 0, srednia = 0;
	float pojemnosc = 0, wilgotnosc = 0;
	uint16_t petla = 32;
	for(int i = 0 ; i < petla; i++)
	{
	 //pt1000_temp_meas_method1();
	 HSL1101_hum_meas();
	  if(i == (petla-1))
	  	continue;
	  suma += licznik;
	  //sprintf(wyslij, "%u ", suma);
	  //  HAL_UART_Transmit(&huart5, &wyslij, 6, 100);
	}
	srednia = (float)suma/petla;
	pojemnosc = srednia*0.0074-12.859;
	wilgotnosc = -3465.6*(pojemnosc/180)*(pojemnosc/180)*(pojemnosc/180)+10732*(pojemnosc/180)*(pojemnosc/180)-10457*(pojemnosc/180)+3245.9;
	//sprintf(wyslij, "poj %f ", pojemnosc);
	//HAL_UART_Transmit(&huart5, &wyslij, 12, 100);
	//sprintf(wyslij, "wilg %f ", wilgotnosc);
	//HAL_UART_Transmit(&huart5, &wyslij, 20, 100);
	return wilgotnosc;
}

void Enter_LowPowerMode(void)
{
  /*## Enter STOP low power Mode ##########################################*/
  /**
  RTC Wakeup Interrupt Generation:
  Wakeup Time Base = (RTC_WAKEUPCLOCK_RTCCLK_DIV /(LSE or LSI))
  Wakeup Time = Wakeup Time Base * WakeUpCounter
              = (RTC_WAKEUPCLOCK_RTCCLK_DIV /(LSE or LSI)) * WakeUpCounter
  ==> WakeUpCounter = Wakeup Time / Wakeup Time Base
  To configure the wake up timer to 5 s the WakeUpCounter is set to 0x2FA8:
  RTC_WAKEUPCLOCK_RTCCLK_DIV = RTCCLK_Div16 = 16
  Wakeup Time Base = 16 /(~32.000KHz) = ~0,5 ms
  Wakeup Time = 5 s = 0,5ms  * WakeUpCounter
  ==> WakeUpCounter = 5/0,5ms = 0x2710
	**/
  HAL_RTCEx_SetWakeUpTimer_IT(&hrtc, 0x0003, RTC_WAKEUPCLOCK_CK_SPRE_16BITS);

  HAL_SuspendTick();      			/* To Avoid timer wake-up. */

  /**
	In PWR_MAINREGULATOR_ON mode, we measure 13.8/15.2uA on JP6
	**/
  HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON,PWR_STOPENTRY_WFE);

  /**
  In PWR_LOWPOWERREGULATOR_ON mode, we measure 1.3/2.7uA on JP6
  HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON,PWR_STOPENTRY_WFI);
	**/

  /* We are now waiting for TAMPERF1 or WAKEUP interrupts (or Reset) */

  HAL_ResumeTick();       /* Needed in case of Timer usage. */
  HAL_RTCEx_DeactivateWakeUpTimer(&hrtc);

  SystemClock_Config();   /* Re-configure the system clock */
}

void BluetoothSendData()
{
	uint8_t dane[10] = {"info"};
	uint32_t address = 0;
	address = M25P32_CheckFreeAddress();
	//HAL_UART_Transmit(&huart5, dane, sizeof(dane), 100);
	for(int i = 0; i < address; i+=15)
	{
		//sprintf(dane, "%d", i);
		//HAL_UART_Transmit(&huart5, dane, sizeof(dane), 100);
		M25P32_ReadBluetoothByte(i, 15);
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
  MX_UART5_Init();
  MX_TIM2_Init();
  MX_DAC1_Init();
  MX_COMP1_Init();
  MX_RTC_Init();
  MX_SPI1_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

  struct bmp388_calib_data calib_data;
  BMP388_init(&calib_data);
  HAL_Delay(2000);

  HAL_DAC_Start(&hdac1, DAC_CHANNEL_1);
  HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 2188);

  uint8_t wysylanie[20] = "              ";
  uint8_t MessageLen = 40;
  uint8_t Message[60];
  uint8_t seconds = 0;
  HAL_COMP_Start_IT(&hcomp1);
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_SET);//flash HOLD
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);//flash WP
/*
  uint8_t liczba_pomiarow = 128;
  sprintf(wyslij, "Metoda_4=[", licznik);
  HAL_UART_Transmit(&huart5, &wyslij, 10, 100);
  for(int i = 0 ; i < liczba_pomiarow; i++)
  {
	  pt1000_temp_meas_method3();
	  //HSL1101_hum_meas();
	  if(i == (liczba_pomiarow-1))
		  continue;
	  sprintf(wyslij, ";\n", licznik);
	  HAL_UART_Transmit(&huart5, &wyslij, 2, 100);
  }
  sprintf(wyslij, "];", licznik);
  HAL_UART_Transmit(&huart5, &wyslij, 2, 100);*/

  //HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
  uint8_t dane[10]={"info"};
  uint8_t dane1[10]={"wysylam dane"};
  uint8_t dane2[10]={"ble_off"};
  uint8_t odczyt[16]={0x00, 0x00, 0x00, 0x00}, UV_index = 0;
  float temperature = 0, cisnienie = 0, wilgotnosc = 0;
  uint16_t temperatura = 0x0000, wilg = 0x0000, light_value = 0x0000;
  uint32_t cisn = 0x000000;
  uint32_t free_memory_address = 0;
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
  //BluetoothSendData();
  // W25P32_ReadID();
  //W25P32_ReadByte(0x00000000, 120);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */



	  if(ble1 == 1 && ble2 == 2)//wyczysc pamiec
	  {
		  ble1 = 0;
		  ble2 = 0;
		  M25P32_Erase();
		  for(int i = 0 ; i < 20; i++)
		  {
			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
			  HAL_Delay(500);
			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
			  HAL_Delay(500);
		  }
	  }

	  if(ble1 == 0 && ble2 == 2)//wylacz ble
	  {
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
		  //HAL_UART_Transmit(&huart5, dane2, sizeof(dane2), 100);
		  ble1 = 0;
		  ble2 = 0;
		  wlacz_ble = 0;
	  }

	  if(ble1 == 2 && ble2 == 0)//wlacz ble
	  {
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
		  ble1 = 0;
		  ble2 = 0;
		  wlacz_ble = 1;
		  //HAL_UART_Transmit(&huart5, dane1, sizeof(dane1), 100);
	  }

	  if(ble1 == 2 && ble2 == 1)//wyslij dane
	  {
		  BluetoothSendData();
		  ble1 = 0;
		  ble2 = 0;
	  }

	  if(wlacz_ble == 0)
	  {
		  //sleep
		  Enter_LowPowerMode();

		  //data
		  HAL_RTC_GetDate(&hrtc, &RtcDate, RTC_FORMAT_BIN);
		  odczyt[0] = RtcDate.Date;
		  odczyt[1] = RtcDate.Month;
		  odczyt[2] = RtcDate.Year;
		  MessageLen = sprintf((char*)Message, "Data: %02d:%02d:%02d\n\r", RtcDate.Date, RtcDate.Month, RtcDate.Year);
		  HAL_UART_Transmit(&huart5, Message, MessageLen, 100);

		  //godzina
		  HAL_RTC_GetTime(&hrtc, &RtcTime, RTC_FORMAT_BIN);
		  odczyt[3] = RtcTime.Hours;
		  odczyt[4] = RtcTime.Minutes;
		  MessageLen = sprintf((char*)Message, "Godzina: %02d:%02d:%02d\n\r", RtcTime.Hours, RtcTime.Minutes, RtcTime.Seconds);
		  HAL_UART_Transmit(&huart5, Message, MessageLen, 100);

		  //temperatura PT1000 OK
		  temperature = pt1000_temp_meas_method32();
		  temperature *= 100;
		  temperatura = (uint16_t)temperature;
		  odczyt[5] = temperatura>>8;
		  odczyt[6] = temperatura;
		  sprintf(wysylanie, "temp%0.2f ", temperature);
		  HAL_UART_Transmit(&huart5, &wysylanie, sizeof(wysylanie), 100);
		  //HAL_UART_Transmit(&huart5, odczyt, sizeof(odczyt), 100);

		  //cisnienie BMP388 OK
		  wynik = 25;
		  wynik = BMP388_measure_press();
		  wynik /= 128;
		  cisnienie = wynik * 100;
		  cisn = (uint32_t)cisnienie;
		  odczyt[7] = cisn>>16;
		  odczyt[8] = cisn>>8;
		  odczyt[9] = cisn;
		  sprintf(wysylanie, "cisn%0.2f ", cisnienie);
		  HAL_UART_Transmit(&huart5, &wysylanie, sizeof(wysylanie), 100);
		  //HAL_UART_Transmit(&huart5, odczyt, sizeof(odczyt), 100);
		  //wilgotnosc HSL1101 OK
		  wilgotnosc = measure_humidity();
		  wilgotnosc *= 100;
		  wilg = (uint16_t)wilgotnosc;
		  odczyt[10] = wilg>>8;
		  odczyt[11] = wilg;
		  sprintf(wysylanie, "wilg%0.2f ", wilgotnosc);
		  HAL_UART_Transmit(&huart5, &wysylanie, sizeof(wysylanie), 100);
		  //HAL_UART_Transmit(&huart5, odczyt, sizeof(odczyt), 100);

		  //index UV VEML6070 OK
		  UV_index = VEML6070();
		  odczyt[12] = UV_index;
		  sprintf(wyslij, "index UV: %u ", UV_index);
		  HAL_UART_Transmit(&huart5, &wyslij, sizeof(wyslij), 100);

		  //nat. osw. BH1750 OK
		  light_value = BH1750();
		  odczyt[13] = light_value>>8;
		  odczyt[14] = light_value;
		  sprintf(wyslij, "%u[lx]", light_value);
		  HAL_UART_Transmit(&huart5, &wyslij, sizeof(wyslij), 100);
		  //HAL_UART_Transmit(&huart5, odczyt, sizeof(odczyt), 100);

		  HAL_RTC_GetTime(&hrtc, &RtcTime, RTC_FORMAT_BIN);
		  MessageLen = sprintf((char*)Message, "\n\rTryb sleep o: %02d:%02d:%02d\n\r", RtcTime.Hours, RtcTime.Minutes, RtcTime.Seconds);
		  HAL_UART_Transmit(&huart5, Message, MessageLen, 100);

		  //szukanie niezapisanych komorek pamieci
		  free_memory_address = M25P32_CheckFreeAddress();
		  for(int i = 0 ; i < 15; i++)//zapis 30 bajtow z pomiaru
		  {
			  M25P32_WriteByte((free_memory_address+i), odczyt[i]);
		  }

	  }

	  //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);
	  // HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
	  //HAL_Delay(1000);
	  //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET);
	  //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);

	  //W25P32_CheckFreeAddress();
	  //HAL_Delay(1000);
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

  /**Configure LSE Drive Capability 
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);
  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 10;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC|RCC_PERIPHCLK_USART1
                              |RCC_PERIPHCLK_UART5|RCC_PERIPHCLK_I2C1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInit.Uart5ClockSelection = RCC_UART5CLKSOURCE_PCLK1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
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
  * @brief COMP1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_COMP1_Init(void)
{

  /* USER CODE BEGIN COMP1_Init 0 */

  /* USER CODE END COMP1_Init 0 */

  /* USER CODE BEGIN COMP1_Init 1 */

  /* USER CODE END COMP1_Init 1 */
  hcomp1.Instance = COMP1;
  hcomp1.Init.InvertingInput = COMP_INPUT_MINUS_DAC1_CH1;
  hcomp1.Init.NonInvertingInput = COMP_INPUT_PLUS_IO2;
  hcomp1.Init.OutputPol = COMP_OUTPUTPOL_NONINVERTED;
  hcomp1.Init.Hysteresis = COMP_HYSTERESIS_NONE;
  hcomp1.Init.BlankingSrce = COMP_BLANKINGSRC_NONE;
  hcomp1.Init.Mode = COMP_POWERMODE_HIGHSPEED;
  hcomp1.Init.WindowMode = COMP_WINDOWMODE_DISABLE;
  hcomp1.Init.TriggerMode = COMP_TRIGGERMODE_IT_RISING;
  if (HAL_COMP_Init(&hcomp1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN COMP1_Init 2 */

  /* USER CODE END COMP1_Init 2 */

}

/**
  * @brief DAC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_DAC1_Init(void)
{

  /* USER CODE BEGIN DAC1_Init 0 */

  /* USER CODE END DAC1_Init 0 */

  DAC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN DAC1_Init 1 */

  /* USER CODE END DAC1_Init 1 */
  /**DAC Initialization 
  */
  hdac1.Instance = DAC1;
  if (HAL_DAC_Init(&hdac1) != HAL_OK)
  {
    Error_Handler();
  }
  /**DAC channel OUT1 config 
  */
  sConfig.DAC_SampleAndHold = DAC_SAMPLEANDHOLD_DISABLE;
  sConfig.DAC_Trigger = DAC_TRIGGER_NONE;
  sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_DISABLE;
  sConfig.DAC_ConnectOnChipPeripheral = DAC_CHIPCONNECT_ENABLE;
  sConfig.DAC_UserTrimming = DAC_TRIMMING_FACTORY;
  if (HAL_DAC_ConfigChannel(&hdac1, &sConfig, DAC_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN DAC1_Init 2 */

  /* USER CODE END DAC1_Init 2 */

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
  hi2c1.Init.Timing = 0x10909CEC;
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
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */
  /**Initialize RTC Only 
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutRemap = RTC_OUTPUT_REMAP_NONE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */
    
  /* USER CODE END Check_RTC_BKUP */

  /**Initialize RTC and set the Time and Date 
  */
  sTime.Hours = 0x11;
  sTime.Minutes = 0x16;
  sTime.Seconds = 0x0;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  sDate.WeekDay = RTC_WEEKDAY_SUNDAY;
  sDate.Month = RTC_MONTH_AUGUST;
  sDate.Date = 0x1;
  sDate.Year = 0x21;

  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  /**Enable the WakeUp 
  */
  if (HAL_RTCEx_SetWakeUpTimer_IT(&hrtc, 0, RTC_WAKEUPCLOCK_CK_SPRE_16BITS) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

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
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0|T4_Pin|T3_Pin|GPIO_PIN_8 
                          |GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED3_Pin|LED2_Pin|GPIO_PIN_4, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, T2_Pin|T1_Pin|GPIO_PIN_10|STM_KEY_Pin 
                          |BLE_ON_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PC0 T4_Pin T3_Pin PC8 
                           PC9 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|T4_Pin|T3_Pin|GPIO_PIN_8 
                          |GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : B1_Pin B2_Pin PA13 */
  GPIO_InitStruct.Pin = B1_Pin|B2_Pin|GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LED3_Pin LED2_Pin PA4 */
  GPIO_InitStruct.Pin = LED3_Pin|LED2_Pin|GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : T2_Pin T1_Pin PB10 STM_KEY_Pin 
                           BLE_ON_Pin */
  GPIO_InitStruct.Pin = T2_Pin|T1_Pin|GPIO_PIN_10|STM_KEY_Pin 
                          |BLE_ON_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : BMP_CS_Pin */
  GPIO_InitStruct.Pin = BMP_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BMP_CS_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

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
