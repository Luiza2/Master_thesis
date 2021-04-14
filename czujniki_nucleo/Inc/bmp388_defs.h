/**
 * Copyright (C) 2016 - 2017 Bosch Sensortec GmbH
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * Neither the name of the copyright holder nor the names of the
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDER
 * OR CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
 * OR CONSEQUENTIAL DAMAGES(INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE
 *
 * The information provided is believed to be accurate and reliable.
 * The copyright holder assumes no responsibility
 * for the consequences of use
 * of such information nor for any infringement of patents or
 * other rights of third parties which may result from its use.
 * No license is granted by implication or otherwise under any patent or
 * patent rights of the copyright holder.
 *
 * @file	bmp388_defs.h
 * @date	14 Feb 2018
 * @version	3.3.4
 * @brief
 *
 */

/*! @file bmp388_defs.h
    @brief Sensor driver for BMP388 sensor */
/*!
 * @defgroup BMP388 SENSOR API
 * @brief
 * @{*/
#ifndef BMP388_DEFS_H_
#define BMP388_DEFS_H_

/********************************************************/
/* header includes */
#ifdef __KERNEL__
#include <linux/types.h>
#include <linux/kernel.h>
#else
#include <stdint.h>
#include <stddef.h>
#endif

/********************************************************/
/*! @name		Common macros		        */
/********************************************************/

#if !defined(UINT8_C) && !defined(INT8_C)
#define INT8_C(x)       S8_C(x)
#define UINT8_C(x)      U8_C(x)
#endif

#if !defined(UINT16_C) && !defined(INT16_C)
#define INT16_C(x)      S16_C(x)
#define UINT16_C(x)     U16_C(x)
#endif

#if !defined(INT32_C) && !defined(UINT32_C)
#define INT32_C(x)      S32_C(x)
#define UINT32_C(x)     U32_C(x)
#endif

#if !defined(INT64_C) && !defined(UINT64_C)
#define INT64_C(x)      S64_C(x)
#define UINT64_C(x)     U64_C(x)
#endif

/**@}*/

/**\name C standard macros */
#ifndef NULL
#ifdef __cplusplus
#define NULL   0
#else
#define NULL   ((void *) 0)
#endif
#endif
/********************************************************/

#ifndef BMP388_FLOAT_ENABLE
/* #define BMP388_FLOAT_ENABLE */
#endif

#ifndef BMP388_FLOAT_ENABLE
#ifndef BMP388_64BIT_ENABLE
#define BMP388_64BIT_ENABLE
#endif
#endif

#ifndef TRUE
#define TRUE                UINT8_C(1)
#endif
#ifndef FALSE
#define FALSE               UINT8_C(0)
#endif

/**\name I2C addresses */
#define BMP388_I2C_ADDR_PRIM	UINT8_C(0x76)
#define BMP388_I2C_ADDR_SEC		UINT8_C(0x77)

/**\name BMP388 chip identifier */
#define BMP388_CHIP_ID  UINT8_C(0x60)

/**\name Register Address */
#define BMP388_CHIP_ID_ADDR					UINT8_C(0xD0)
#define BMP388_RESET_ADDR					UINT8_C(0xE0)
#define BMP388_TEMP_PRESS_CALIB_DATA_ADDR	UINT8_C(0x88)
#define BMP388_HUMIDITY_CALIB_DATA_ADDR		UINT8_C(0xE1)
#define BMP388_PWR_CTRL_ADDR				UINT8_C(0x1B)
#define BMP388_CTRL_HUM_ADDR				UINT8_C(0xF2)
#define BMP388_CTRL_MEAS_ADDR				UINT8_C(0xF4)
#define BMP388_CONFIG_ADDR					UINT8_C(0xF5)
#define BMP388_DATA_ADDR					UINT8_C(0x04)

/**\name API success code */
#define BMP388_OK					INT8_C(0)

/**\name API error codes */
#define BMP388_E_NULL_PTR			INT8_C(-1)
#define BMP388_E_DEV_NOT_FOUND		INT8_C(-2)
#define BMP388_E_INVALID_LEN		INT8_C(-3)
#define BMP388_E_COMM_FAIL			INT8_C(-4)
#define BMP388_E_SLEEP_MODE_FAIL	INT8_C(-5)

/**\name API warning codes */
#define BMP388_W_INVALID_OSR_MACRO      INT8_C(1)

/**\name Macros related to size */
#define BMP388_TEMP_PRESS_CALIB_DATA_LEN	UINT8_C(26)
#define BMP388_HUMIDITY_CALIB_DATA_LEN		UINT8_C(7)
#define BMP388_P_T_H_DATA_LEN				UINT8_C(6)

/**\name Sensor power modes */
#define	BMP388_SLEEP_MODE		UINT8_C(0x00)
#define	BMP388_FORCED_MODE		UINT8_C(0x01)
#define	BMP388_NORMAL_MODE		UINT8_C(0x03)

/**\name Macro to combine two 8 bit data's to form a 16 bit data */
#define BMP388_CONCAT_BYTES(msb, lsb)     (((uint16_t)msb << 8) | (uint16_t)lsb)

#define BMP388_SET_BITS(reg_data, bitname, data) \
				((reg_data & ~(bitname##_MSK)) | \
				((data << bitname##_POS) & bitname##_MSK))
#define BMP388_SET_BITS_POS_0(reg_data, bitname, data) \
				((reg_data & ~(bitname##_MSK)) | \
				(data & bitname##_MSK))

#define BMP388_GET_BITS(reg_data, bitname)  ((reg_data & (bitname##_MSK)) >> \
							(bitname##_POS))
#define BMP388_GET_BITS_POS_0(reg_data, bitname)  (reg_data & (bitname##_MSK))

/**\name Macros for bit masking */
#define BMP388_SENSOR_MODE_MSK	UINT8_C(0x30)
#define BMP388_SENSOR_MODE_POS	UINT8_C(0x10)

#define BMP388_CTRL_HUM_MSK		UINT8_C(0x07)
#define BMP388_CTRL_HUM_POS		UINT8_C(0x00)

#define BMP388_CTRL_PRESS_MSK	UINT8_C(0x1C)
#define BMP388_CTRL_PRESS_POS	UINT8_C(0x02)

#define BMP388_CTRL_TEMP_MSK	UINT8_C(0xE0)
#define BMP388_CTRL_TEMP_POS	UINT8_C(0x05)

#define BMP388_FILTER_MSK		UINT8_C(0x1C)
#define BMP388_FILTER_POS		UINT8_C(0x02)

#define BMP388_STANDBY_MSK		UINT8_C(0xE0)
#define BMP388_STANDBY_POS		UINT8_C(0x05)

/**\name Sensor component selection macros
   These values are internal for API implementation. Don't relate this to
   data sheet.*/
#define BMP388_PRESS		UINT8_C(1)
#define BMP388_TEMP			UINT8_C(1 << 1)
#define BMP388_HUM			UINT8_C(1 << 2)
#define BMP388_ALL			UINT8_C(0x07)

/**\name Settings selection macros */
#define BMP388_OSR_PRESS_SEL		UINT8_C(1)
#define BMP388_OSR_TEMP_SEL			UINT8_C(1 << 1)
#define BMP388_OSR_HUM_SEL			UINT8_C(1 << 2)
#define BMP388_FILTER_SEL			UINT8_C(1 << 3)
#define BMP388_STANDBY_SEL			UINT8_C(1 << 4)
#define BMP388_ALL_SETTINGS_SEL		UINT8_C(0x1F)

/**\name Oversampling macros */
#define BMP388_NO_OVERSAMPLING		UINT8_C(0x00)
#define BMP388_OVERSAMPLING_1X		UINT8_C(0x01)
#define BMP388_OVERSAMPLING_2X		UINT8_C(0x02)
#define BMP388_OVERSAMPLING_4X		UINT8_C(0x03)
#define BMP388_OVERSAMPLING_8X		UINT8_C(0x04)
#define BMP388_OVERSAMPLING_16X		UINT8_C(0x05)

/**\name Standby duration selection macros */
#define BMP388_STANDBY_TIME_1_MS              (0x00)
#define BMP388_STANDBY_TIME_62_5_MS           (0x01)
#define BMP388_STANDBY_TIME_125_MS			  (0x02)
#define BMP388_STANDBY_TIME_250_MS            (0x03)
#define BMP388_STANDBY_TIME_500_MS            (0x04)
#define BMP388_STANDBY_TIME_1000_MS           (0x05)
#define BMP388_STANDBY_TIME_10_MS             (0x06)
#define BMP388_STANDBY_TIME_20_MS             (0x07)

/**\name Filter coefficient selection macros */
#define BMP388_FILTER_COEFF_OFF               (0x00)
#define BMP388_FILTER_COEFF_2                 (0x01)
#define BMP388_FILTER_COEFF_4                 (0x02)
#define BMP388_FILTER_COEFF_8                 (0x03)
#define BMP388_FILTER_COEFF_16                (0x04)

/*!
 * @brief Interface selection Enums
 */
enum bmp388_intf {
	/*! SPI interface */
	BMP388_SPI_INTF,
	/*! I2C interface */
	BMP388_I2C_INTF
};

/*!
 * @brief Type definitions
 */
typedef int8_t (*bmp388_com_fptr_t)(uint8_t dev_id, uint8_t reg_addr,
		uint8_t *data, uint16_t len);

typedef void (*bmp388_delay_fptr_t)(uint32_t period);

/*!
 * @brief Calibration data
 */
struct bmp388_calib_data {
 /**
 * @ Trim Variables
 */
/**@{*/
	uint16_t dig_T1;
	int16_t dig_T2;
	int16_t dig_T3;
	uint16_t dig_P1;
	int16_t dig_P2;
	int16_t dig_P3;
	int16_t dig_P4;
	int16_t dig_P5;
	int16_t dig_P6;
	int16_t dig_P7;
	int16_t dig_P8;
	int16_t dig_P9;
	uint8_t  dig_H1;
	int16_t dig_H2;
	uint8_t  dig_H3;
	int16_t dig_H4;
	int16_t dig_H5;
	int8_t  dig_H6;
	int32_t t_fine;
/**@}*/
};

/*!
 * @brief bmp388 sensor structure which comprises of temperature, pressure and
 * humidity data
 */
#ifdef BMP388_FLOAT_ENABLE
struct bmp388_data {
	/*! Compensated pressure */
	double pressure;
	/*! Compensated temperature */
	double temperature;
	/*! Compensated humidity */
	double humidity;
};
#else
struct bmp388_data {
	/*! Compensated pressure */
	uint32_t pressure;
	/*! Compensated temperature */
	int32_t temperature;
	/*! Compensated humidity */
	uint32_t humidity;
};
#endif /* BMP388_USE_FLOATING_POINT */

/*!
 * @brief bmp388 sensor structure which comprises of uncompensated temperature,
 * pressure and humidity data
 */
struct bmp388_uncomp_data {
	/*! un-compensated pressure */
	uint32_t pressure;
	/*! un-compensated temperature */
	uint32_t temperature;
	/*! un-compensated humidity */
	uint32_t humidity;
};

/*!
 * @brief bmp388 sensor settings structure which comprises of mode,
 * oversampling and filter settings.
 */
struct bmp388_settings {
	/*! pressure oversampling */
	uint8_t osr_p;
	/*! temperature oversampling */
	uint8_t osr_t;
	/*! humidity oversampling */
	uint8_t osr_h;
	/*! filter coefficient */
	uint8_t filter;
	/*! standby time */
	uint8_t standby_time;
};

/*!
 * @brief bmp388 device structure
 */
struct bmp388_dev {
	/*! Chip Id */
	uint8_t chip_id;
	/*! Device Id */
	uint8_t dev_id;
	/*! SPI/I2C interface */
	enum bmp388_intf intf;
	/*! Read function pointer */
	bmp388_com_fptr_t read;
	/*! Write function pointer */
	bmp388_com_fptr_t write;
	/*! Delay function pointer */
	bmp388_delay_fptr_t delay_ms;
	/*! Trim data */
	struct bmp388_calib_data calib_data;
	/*! Sensor settings */
	struct bmp388_settings settings;
};

#endif /* BMP388_DEFS_H_ */
/** @}*/
/** @}*/
