// I2Cdev library collection - MPU9250 I2C device class
// Based on InvenSense MPU-9150 register map document rev. 2.0, 5/19/2011 (RM-MPU-6000A-00)
// 10/3/2011 by Jeff Rowberg <jeff@rowberg.net>
// Updates should (hopefully) always be available at https://github.com/jrowberg/i2cdevlib
//
// Changelog:
//     ... - ongoing debug release

// NOTE: THIS IS ONLY A PARIAL RELEASE. THIS DEVICE CLASS IS CURRENTLY UNDERGOING ACTIVE
// DEVELOPMENT AND IS STILL MISSING SOME IMPORTANT FEATURES. PLEASE KEEP THIS IN MIND IF
// YOU DECIDE TO USE THIS PARTICULAR CODE FOR ANYTHING.

/* ============================================
 I2Cdev device library code is placed under the MIT license
 Copyright (c) 2012 Jeff Rowberg

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ===============================================
 */

#ifndef _MPU9250_H_
#define _MPU9250_H_

#include "I2Cdev.h"

// supporting link:  http://forum.arduino.cc/index.php?&topic=143444.msg1079517#msg1079517
// also: http://forum.arduino.cc/index.php?&topic=141571.msg1062899#msg1062899s
#ifndef __arm__
#include <avr/pgmspace.h>
#else
#define PROGMEM /* empty */
#define pgm_read_byte(x) (*(x))
#define pgm_read_word(x) (*(x))
#define pgm_read_float(x) (*(x))
#define PSTR(STR) STR
#endif

//Magnetometer Registers
#define MPU9250_RA_MAG_ADDRESS		0x0C
#define MPU9250_RA_MAG_WHO_AM_I		0x00
#define MPU9250_RA_MAG_INFO			0x01
#define MPU9250_RA_MAG_ST1			0x02
#define MPU9250_RA_MAG_XOUT_L		0x03
#define MPU9250_RA_MAG_XOUT_H		0x04
#define MPU9250_RA_MAG_YOUT_L		0x05
#define MPU9250_RA_MAG_YOUT_H		0x06
#define MPU9250_RA_MAG_ZOUT_L		0x07
#define MPU9250_RA_MAG_ZOUT_H		0x08
#define MPU9250_RA_MAG_ST2			0x09
#define MPU9250_RA_MAG_CNTL1		0x0A
#define MPU9250_RA_MAG_CNTL2		0x0B
#define MPU9250_RA_MAG_ATSC			0x0C
#define MPU9250_RA_MAG_I2CDIS		0x0F
#define MPU9250_RA_MAG_FUSE_ASAX	0x10
#define MPU9250_RA_MAG_FUSE_ASAY	0x11
#define MPU9250_RA_MAG_FUSE_ASAZ	0x12


#define MPU9250_ADDRESS_AD0_LOW     0x68 // address pin low (GND), default for InvenSense evaluation board
#define MPU9250_ADDRESS_AD0_HIGH    0x69 // address pin high (VCC)
#define MPU9250_DEFAULT_ADDRESS     MPU9250_ADDRESS_AD0_LOW

#define MPU9250_RA_SELF_TEST_X_GYRO	0x00 //[7:0] xg_st_data
#define MPU9250_RA_SELF_TEST_Y_GYRO	0x01 //[7:0] xg_st_data
#define MPU9250_RA_SELF_TEST_Z_GYRO	0x02 //[7:0] xg_st_data
#define MPU9250_RA_X_FINE_GAIN      0x03 //[7:0] X_FINE_GAIN
#define MPU9250_RA_Y_FINE_GAIN      0x04 //[7:0] Y_FINE_GAIN
#define MPU9250_RA_Z_FINE_GAIN      0x05 //[7:0] Z_FINE_GAIN
#define MPU9250_RA_SELF_TEST_X_ACCEL	0x0D //[7:0] XA_ST_DATA
#define MPU9250_RA_SELF_TEST_Y_ACCEL	0x0E //[7:0] YA_ST_DATA
#define MPU9250_RA_SELF_TEST_Z_ACCEL	0x0F //[7:0] ZA_ST_DATA
#define MPU9250_RA_XG_OFFS_H     	0x13 //[15:0] XG_OFFS_USR
#define MPU9250_RA_XG_OFFS_L     	0x14
#define MPU9250_RA_YG_OFFS_H     	0x15 //[15:0] YG_OFFS_USR
#define MPU9250_RA_YG_OFFS_L     	0x16
#define MPU9250_RA_ZG_OFFS_H     	0x17 //[15:0] ZG_OFFS_USR
#define MPU9250_RA_ZG_OFFS_L     	0x18
#define MPU9250_RA_SMPLRT_DIV       0x19
#define MPU9250_RA_CONFIG           0x1A
#define MPU9250_RA_GYRO_CONFIG      0x1B
#define MPU9250_RA_ACCEL_CONFIG     0x1C
#define MPU9250_RA_ACCEL_CONFIG2    0x1D
#define MPU9250_RA_LP_ACCEL_ODR     0x1E
#define MPU9250_RA_WOM_THR          0x1F
//#define MPU9250_RA_MOT_DUR          0x20	//?
//#define MPU9250_RA_ZRMOT_THR        0x21	//?
//#define MPU9250_RA_ZRMOT_DUR        0x22	//?
#define MPU9250_RA_FIFO_EN          0x23
#define MPU9250_RA_I2C_MST_CTRL     0x24
#define MPU9250_RA_I2C_SLV0_ADDR    0x25
#define MPU9250_RA_I2C_SLV0_REG     0x26
#define MPU9250_RA_I2C_SLV0_CTRL    0x27
#define MPU9250_RA_I2C_SLV1_ADDR    0x28
#define MPU9250_RA_I2C_SLV1_REG     0x29
#define MPU9250_RA_I2C_SLV1_CTRL    0x2A
#define MPU9250_RA_I2C_SLV2_ADDR    0x2B
#define MPU9250_RA_I2C_SLV2_REG     0x2C
#define MPU9250_RA_I2C_SLV2_CTRL    0x2D
#define MPU9250_RA_I2C_SLV3_ADDR    0x2E
#define MPU9250_RA_I2C_SLV3_REG     0x2F
#define MPU9250_RA_I2C_SLV3_CTRL    0x30
#define MPU9250_RA_I2C_SLV4_ADDR    0x31
#define MPU9250_RA_I2C_SLV4_REG     0x32
#define MPU9250_RA_I2C_SLV4_DO      0x33
#define MPU9250_RA_I2C_SLV4_CTRL    0x34
#define MPU9250_RA_I2C_SLV4_DI      0x35
#define MPU9250_RA_I2C_MST_STATUS   0x36
#define MPU9250_RA_INT_PIN_CFG      0x37
#define MPU9250_RA_INT_ENABLE       0x38
#define MPU9250_RA_DMP_INT_STATUS   0x39	//?
#define MPU9250_RA_INT_STATUS       0x3A
#define MPU9250_RA_ACCEL_XOUT_H     0x3B
#define MPU9250_RA_ACCEL_XOUT_L     0x3C
#define MPU9250_RA_ACCEL_YOUT_H     0x3D
#define MPU9250_RA_ACCEL_YOUT_L     0x3E
#define MPU9250_RA_ACCEL_ZOUT_H     0x3F
#define MPU9250_RA_ACCEL_ZOUT_L     0x40
#define MPU9250_RA_TEMP_OUT_H       0x41
#define MPU9250_RA_TEMP_OUT_L       0x42
#define MPU9250_RA_GYRO_XOUT_H      0x43
#define MPU9250_RA_GYRO_XOUT_L      0x44
#define MPU9250_RA_GYRO_YOUT_H      0x45
#define MPU9250_RA_GYRO_YOUT_L      0x46
#define MPU9250_RA_GYRO_ZOUT_H      0x47
#define MPU9250_RA_GYRO_ZOUT_L      0x48
#define MPU9250_RA_EXT_SENS_DATA_00 0x49
#define MPU9250_RA_EXT_SENS_DATA_01 0x4A
#define MPU9250_RA_EXT_SENS_DATA_02 0x4B
#define MPU9250_RA_EXT_SENS_DATA_03 0x4C
#define MPU9250_RA_EXT_SENS_DATA_04 0x4D
#define MPU9250_RA_EXT_SENS_DATA_05 0x4E
#define MPU9250_RA_EXT_SENS_DATA_06 0x4F
#define MPU9250_RA_EXT_SENS_DATA_07 0x50
#define MPU9250_RA_EXT_SENS_DATA_08 0x51
#define MPU9250_RA_EXT_SENS_DATA_09 0x52
#define MPU9250_RA_EXT_SENS_DATA_10 0x53
#define MPU9250_RA_EXT_SENS_DATA_11 0x54
#define MPU9250_RA_EXT_SENS_DATA_12 0x55
#define MPU9250_RA_EXT_SENS_DATA_13 0x56
#define MPU9250_RA_EXT_SENS_DATA_14 0x57
#define MPU9250_RA_EXT_SENS_DATA_15 0x58
#define MPU9250_RA_EXT_SENS_DATA_16 0x59
#define MPU9250_RA_EXT_SENS_DATA_17 0x5A
#define MPU9250_RA_EXT_SENS_DATA_18 0x5B
#define MPU9250_RA_EXT_SENS_DATA_19 0x5C
#define MPU9250_RA_EXT_SENS_DATA_20 0x5D
#define MPU9250_RA_EXT_SENS_DATA_21 0x5E
#define MPU9250_RA_EXT_SENS_DATA_22 0x5F
#define MPU9250_RA_EXT_SENS_DATA_23 0x60
#define MPU9250_RA_MOT_DETECT_STATUS    0x61	//?
#define MPU9250_RA_I2C_SLV0_DO      0x63
#define MPU9250_RA_I2C_SLV1_DO      0x64
#define MPU9250_RA_I2C_SLV2_DO      0x65
#define MPU9250_RA_I2C_SLV3_DO      0x66
#define MPU9250_RA_I2C_MST_DELAY_CTRL   0x67
#define MPU9250_RA_SIGNAL_PATH_RESET    0x68
#define MPU9250_RA_MOT_DETECT_CTRL      0x69
#define MPU9250_RA_USER_CTRL        0x6A
#define MPU9250_RA_PWR_MGMT_1       0x6B
#define MPU9250_RA_PWR_MGMT_2       0x6C
#define MPU9250_RA_BANK_SEL         0x6D	//?
#define MPU9250_RA_MEM_START_ADDR   0x6E	//?
#define MPU9250_RA_MEM_R_W          0x6F	//?
#define MPU9250_RA_DMP_CFG_1        0x70	//?
#define MPU9250_RA_DMP_CFG_2        0x71	//?
#define MPU9250_RA_FIFO_COUNTH      0x72
#define MPU9250_RA_FIFO_COUNTL      0x73
#define MPU9250_RA_FIFO_R_W         0x74
#define MPU9250_RA_WHO_AM_I         0x75
#define MPU9250_RA_XA_OFFS_H        0x77 //[15:0] XA_OFFS
#define MPU9250_RA_XA_OFFS_L	    0x78
#define MPU9250_RA_YA_OFFS_H        0x7A //[15:0] YA_OFFS
#define MPU9250_RA_YA_OFFS_L     	0x7B
#define MPU9250_RA_ZA_OFFS_H        0x7D //[15:0] ZA_OFFS
#define MPU9250_RA_ZA_OFFS_L     	0x7E

#define MPU9250_TC_PWR_MODE_BIT     7
#define MPU9250_TC_OFFSET_BIT       6
#define MPU9250_TC_OFFSET_LENGTH    6
#define MPU9250_TC_OTP_BNK_VLD_BIT  0

#define MPU9250_VDDIO_LEVEL_VLOGIC  0
#define MPU9250_VDDIO_LEVEL_VDD     1

#define MPU9250_CFG_EXT_SYNC_SET_BIT    5
#define MPU9250_CFG_EXT_SYNC_SET_LENGTH 3
#define MPU9250_CFG_DLPF_CFG_BIT    2
#define MPU9250_CFG_DLPF_CFG_LENGTH 3

#define MPU9250_EXT_SYNC_DISABLED       0x0
#define MPU9250_EXT_SYNC_TEMP_OUT_L     0x1
#define MPU9250_EXT_SYNC_GYRO_XOUT_L    0x2
#define MPU9250_EXT_SYNC_GYRO_YOUT_L    0x3
#define MPU9250_EXT_SYNC_GYRO_ZOUT_L    0x4
#define MPU9250_EXT_SYNC_ACCEL_XOUT_L   0x5
#define MPU9250_EXT_SYNC_ACCEL_YOUT_L   0x6
#define MPU9250_EXT_SYNC_ACCEL_ZOUT_L   0x7

#define MPU9250_DLPF_BW_256         0x00
#define MPU9250_DLPF_BW_188         0x01
#define MPU9250_DLPF_BW_98          0x02
#define MPU9250_DLPF_BW_42          0x03
#define MPU9250_DLPF_BW_20          0x04
#define MPU9250_DLPF_BW_10          0x05
#define MPU9250_DLPF_BW_5           0x06

#define MPU9250_GCONFIG_FS_SEL_BIT      4
#define MPU9250_GCONFIG_FS_SEL_LENGTH   2

#define MPU9250_GYRO_FS_250         0x00
#define MPU9250_GYRO_FS_500         0x01
#define MPU9250_GYRO_FS_1000        0x02
#define MPU9250_GYRO_FS_2000        0x03

#define MPU9250_ACONFIG_XA_ST_BIT           7
#define MPU9250_ACONFIG_YA_ST_BIT           6
#define MPU9250_ACONFIG_ZA_ST_BIT           5
#define MPU9250_ACONFIG_AFS_SEL_BIT         4
#define MPU9250_ACONFIG_AFS_SEL_LENGTH      2
#define MPU9250_ACONFIG_ACCEL_HPF_BIT       2
#define MPU9250_ACONFIG_ACCEL_HPF_LENGTH    3

#define MPU9250_ACCEL_FS_2          0x00
#define MPU9250_ACCEL_FS_4          0x01
#define MPU9250_ACCEL_FS_8          0x02
#define MPU9250_ACCEL_FS_16         0x03

#define MPU9250_DHPF_RESET          0x00
#define MPU9250_DHPF_5              0x01
#define MPU9250_DHPF_2P5            0x02
#define MPU9250_DHPF_1P25           0x03
#define MPU9250_DHPF_0P63           0x04
#define MPU9250_DHPF_HOLD           0x07

#define MPU9250_TEMP_FIFO_EN_BIT    7
#define MPU9250_XG_FIFO_EN_BIT      6
#define MPU9250_YG_FIFO_EN_BIT      5
#define MPU9250_ZG_FIFO_EN_BIT      4
#define MPU9250_ACCEL_FIFO_EN_BIT   3
#define MPU9250_SLV2_FIFO_EN_BIT    2
#define MPU9250_SLV1_FIFO_EN_BIT    1
#define MPU9250_SLV0_FIFO_EN_BIT    0

#define MPU9250_MULT_MST_EN_BIT     7
#define MPU9250_WAIT_FOR_ES_BIT     6
#define MPU9250_SLV_3_FIFO_EN_BIT   5
#define MPU9250_I2C_MST_P_NSR_BIT   4
#define MPU9250_I2C_MST_CLK_BIT     3
#define MPU9250_I2C_MST_CLK_LENGTH  4

#define MPU9250_CLOCK_DIV_348       0x0
#define MPU9250_CLOCK_DIV_333       0x1
#define MPU9250_CLOCK_DIV_320       0x2
#define MPU9250_CLOCK_DIV_308       0x3
#define MPU9250_CLOCK_DIV_296       0x4
#define MPU9250_CLOCK_DIV_286       0x5
#define MPU9250_CLOCK_DIV_276       0x6
#define MPU9250_CLOCK_DIV_267       0x7
#define MPU9250_CLOCK_DIV_258       0x8
#define MPU9250_CLOCK_DIV_500       0x9
#define MPU9250_CLOCK_DIV_471       0xA
#define MPU9250_CLOCK_DIV_444       0xB
#define MPU9250_CLOCK_DIV_421       0xC
#define MPU9250_CLOCK_DIV_400       0xD
#define MPU9250_CLOCK_DIV_381       0xE
#define MPU9250_CLOCK_DIV_364       0xF

#define MPU9250_I2C_SLV_RW_BIT      7
#define MPU9250_I2C_SLV_ADDR_BIT    6
#define MPU9250_I2C_SLV_ADDR_LENGTH 7
#define MPU9250_I2C_SLV_EN_BIT      7
#define MPU9250_I2C_SLV_BYTE_SW_BIT 6
#define MPU9250_I2C_SLV_REG_DIS_BIT 5
#define MPU9250_I2C_SLV_GRP_BIT     4
#define MPU9250_I2C_SLV_LEN_BIT     3
#define MPU9250_I2C_SLV_LEN_LENGTH  4

#define MPU9250_I2C_SLV4_RW_BIT         7
#define MPU9250_I2C_SLV4_ADDR_BIT       6
#define MPU9250_I2C_SLV4_ADDR_LENGTH    7
#define MPU9250_I2C_SLV4_EN_BIT         7
#define MPU9250_I2C_SLV4_INT_EN_BIT     6
#define MPU9250_I2C_SLV4_REG_DIS_BIT    5
#define MPU9250_I2C_SLV4_MST_DLY_BIT    4
#define MPU9250_I2C_SLV4_MST_DLY_LENGTH 5

#define MPU9250_MST_PASS_THROUGH_BIT    7
#define MPU9250_MST_I2C_SLV4_DONE_BIT   6
#define MPU9250_MST_I2C_LOST_ARB_BIT    5
#define MPU9250_MST_I2C_SLV4_NACK_BIT   4
#define MPU9250_MST_I2C_SLV3_NACK_BIT   3
#define MPU9250_MST_I2C_SLV2_NACK_BIT   2
#define MPU9250_MST_I2C_SLV1_NACK_BIT   1
#define MPU9250_MST_I2C_SLV0_NACK_BIT   0

#define MPU9250_MST_I2C_DELAY_ES_SHADOW_BIT	7
#define MPU9250_MST_I2C_SLV4_DLY_EN_BIT		4
#define MPU9250_MST_I2C_SLV3_DLY_EN_BIT  	3
#define MPU9250_MST_I2C_SLV2_DLY_EN_BIT   	2
#define MPU9250_MST_I2C_SLV1_DLY_EN_BIT   	1
#define MPU9250_MST_I2C_SLV0_DLY_EN_BIT   	0

#define MPU9250_MST_I2C_READ_FLAG		0x80
#define MPU9250_MST_I2C_WRITE_FLAG		0x00

#define MPU9250_INTCFG_INT_LEVEL_BIT        7
#define MPU9250_INTCFG_INT_OPEN_BIT         6
#define MPU9250_INTCFG_LATCH_INT_EN_BIT     5
#define MPU9250_INTCFG_INT_RD_CLEAR_BIT     4
#define MPU9250_INTCFG_FSYNC_INT_LEVEL_BIT  3
#define MPU9250_INTCFG_FSYNC_INT_EN_BIT     2
#define MPU9250_INTCFG_I2C_BYPASS_EN_BIT    1
#define MPU9250_INTCFG_CLKOUT_EN_BIT        0

#define MPU9250_INTMODE_ACTIVEHIGH  0x00
#define MPU9250_INTMODE_ACTIVELOW   0x01

#define MPU9250_INTDRV_PUSHPULL     0x00
#define MPU9250_INTDRV_OPENDRAIN    0x01

#define MPU9250_INTLATCH_50USPULSE  0x00
#define MPU9250_INTLATCH_WAITCLEAR  0x01

#define MPU9250_INTCLEAR_STATUSREAD 0x00
#define MPU9250_INTCLEAR_ANYREAD    0x01

#define MPU9250_INTERRUPT_FF_BIT            7
#define MPU9250_INTERRUPT_MOT_BIT           6
#define MPU9250_INTERRUPT_ZMOT_BIT          5
#define MPU9250_INTERRUPT_FIFO_OFLOW_BIT    4
#define MPU9250_INTERRUPT_I2C_MST_INT_BIT   3
#define MPU9250_INTERRUPT_PLL_RDY_INT_BIT   2
#define MPU9250_INTERRUPT_DMP_INT_BIT       1
#define MPU9250_INTERRUPT_DATA_RDY_BIT      0

// TODO: figure out what these actually do
// UMPL source code is not very obivous
#define MPU9250_DMPINT_5_BIT            5
#define MPU9250_DMPINT_4_BIT            4
#define MPU9250_DMPINT_3_BIT            3
#define MPU9250_DMPINT_2_BIT            2
#define MPU9250_DMPINT_1_BIT            1
#define MPU9250_DMPINT_0_BIT            0

#define MPU9250_MOTION_MOT_XNEG_BIT     7
#define MPU9250_MOTION_MOT_XPOS_BIT     6
#define MPU9250_MOTION_MOT_YNEG_BIT     5
#define MPU9250_MOTION_MOT_YPOS_BIT     4
#define MPU9250_MOTION_MOT_ZNEG_BIT     3
#define MPU9250_MOTION_MOT_ZPOS_BIT     2
#define MPU9250_MOTION_MOT_ZRMOT_BIT    0

#define MPU9250_DELAYCTRL_DELAY_ES_SHADOW_BIT   7
#define MPU9250_DELAYCTRL_I2C_SLV4_DLY_EN_BIT   4
#define MPU9250_DELAYCTRL_I2C_SLV3_DLY_EN_BIT   3
#define MPU9250_DELAYCTRL_I2C_SLV2_DLY_EN_BIT   2
#define MPU9250_DELAYCTRL_I2C_SLV1_DLY_EN_BIT   1
#define MPU9250_DELAYCTRL_I2C_SLV0_DLY_EN_BIT   0

#define MPU9250_PATHRESET_GYRO_RESET_BIT    2
#define MPU9250_PATHRESET_ACCEL_RESET_BIT   1
#define MPU9250_PATHRESET_TEMP_RESET_BIT    0

#define MPU9250_DETECT_ACCEL_ON_DELAY_BIT       5
#define MPU9250_DETECT_ACCEL_ON_DELAY_LENGTH    2
#define MPU9250_DETECT_FF_COUNT_BIT             3
#define MPU9250_DETECT_FF_COUNT_LENGTH          2
#define MPU9250_DETECT_MOT_COUNT_BIT            1
#define MPU9250_DETECT_MOT_COUNT_LENGTH         2

#define MPU9250_DETECT_DECREMENT_RESET  0x0
#define MPU9250_DETECT_DECREMENT_1      0x1
#define MPU9250_DETECT_DECREMENT_2      0x2
#define MPU9250_DETECT_DECREMENT_4      0x3

#define MPU9250_USERCTRL_DMP_EN_BIT             7
#define MPU9250_USERCTRL_FIFO_EN_BIT            6
#define MPU9250_USERCTRL_I2C_MST_EN_BIT         5
#define MPU9250_USERCTRL_I2C_IF_DIS_BIT         4
#define MPU9250_USERCTRL_DMP_RESET_BIT          3
#define MPU9250_USERCTRL_FIFO_RESET_BIT         2
#define MPU9250_USERCTRL_I2C_MST_RESET_BIT      1
#define MPU9250_USERCTRL_SIG_COND_RESET_BIT     0

#define MPU9250_PWR1_DEVICE_RESET_BIT   7
#define MPU9250_PWR1_SLEEP_BIT          6
#define MPU9250_PWR1_CYCLE_BIT          5
#define MPU9250_PWR1_TEMP_DIS_BIT       3
#define MPU9250_PWR1_CLKSEL_BIT         2
#define MPU9250_PWR1_CLKSEL_LENGTH      3

#define MPU9250_CLOCK_INTERNAL          0x00
#define MPU9250_CLOCK_PLL_XGYRO         0x01
#define MPU9250_CLOCK_PLL_YGYRO         0x02
#define MPU9250_CLOCK_PLL_ZGYRO         0x03
#define MPU9250_CLOCK_PLL_EXT32K        0x04
#define MPU9250_CLOCK_PLL_EXT19M        0x05
#define MPU9250_CLOCK_KEEP_RESET        0x07

#define MPU9250_PWR2_LP_WAKE_CTRL_BIT       7
#define MPU9250_PWR2_LP_WAKE_CTRL_LENGTH    2
#define MPU9250_PWR2_STBY_XA_BIT            5
#define MPU9250_PWR2_STBY_YA_BIT            4
#define MPU9250_PWR2_STBY_ZA_BIT            3
#define MPU9250_PWR2_STBY_XG_BIT            2
#define MPU9250_PWR2_STBY_YG_BIT            1
#define MPU9250_PWR2_STBY_ZG_BIT            0

#define MPU9250_WAKE_FREQ_1P25      0x0
#define MPU9250_WAKE_FREQ_2P5       0x1
#define MPU9250_WAKE_FREQ_5         0x2
#define MPU9250_WAKE_FREQ_10        0x3

#define MPU9250_BANKSEL_PRFTCH_EN_BIT       6
#define MPU9250_BANKSEL_CFG_USER_BANK_BIT   5
#define MPU9250_BANKSEL_MEM_SEL_BIT         4
#define MPU9250_BANKSEL_MEM_SEL_LENGTH      5

#define MPU9250_WHO_AM_I_BIT        6
#define MPU9250_WHO_AM_I_LENGTH     6

#define MPU9250_DMP_MEMORY_BANKS        8
#define MPU9250_DMP_MEMORY_BANK_SIZE    256
#define MPU9250_DMP_MEMORY_CHUNK_SIZE   16

#define MPU9250_SMPLRT_DIV1		0x0
#define MPU9250_SMPLRT_DIV2		0x1
#define MPU9250_SMPLRT_DIV4		0x3
#define MPU9250_SMPLRT_DIV5		0x4
#define MPU9250_SMPLRT_DIV8		0x7
#define MPU9250_SMPLRT_DIV10	0x9

#define MPU9250_DMP_SMPLRT_DIV1		0x0
#define MPU9250_DMP_SMPLRT_DIV2		0x1
#define MPU9250_DMP_SMPLRT_DIV4		0x3
#define MPU9250_DMP_SMPLRT_DIV5		0x4
#define MPU9250_DMP_SMPLRT_DIV8		0x7
#define MPU9250_DMP_SMPLRT_DIV10	0x9
#define MPU9250_DMP_SMPLRT_DIV20	0x13
#define MPU9250_DMP_SMPLRT_DIV50	0x31
#define MPU9250_DMP_SMPLRT_DIV100	0x63
#define MPU9250_DMP_SMPLRT_DIV200	0xC7


#define MPU9250_MAG_MODE_SLEEP			0x0
#define MPU9250_MAG_MODE_SINGLE			0x1
#define MPU9250_MAG_MODE_CONTINOUS_8	0x2
#define MPU9250_MAG_MODE_CONTINOUS_100	0x6
#define MPU9250_MAG_MODE_EXT_TRIGGER	0x4
#define MPU9250_MAG_MODE_SELFTEST		0x8
#define MPU9250_MAG_MODE_FUSE_ROM		0xF

#define MPU9250_MAG_RESOLUTION_14BIT	0x00
#define MPU9250_MAG_RESOLUTION_16BIT	0x10

#define MPU9250_MAG_RESET		0x1



// note: DMP code memory blocks defined at end of header file

void MPU9250_setAddress(uint8_t address);

void MPU9250_initialize();
bool MPU9250_testConnection();

// AUX_VDDIO register
uint8_t MPU9250_getAuxVDDIOLevel();
void MPU9250_setAuxVDDIOLevel(uint8_t level);

// SMPLRT_DIV register
uint8_t MPU9250_getRate();
void MPU9250_setRate(uint8_t rate);

// CONFIG register
uint8_t MPU9250_getExternalFrameSync();
void MPU9250_setExternalFrameSync(uint8_t sync);
uint8_t MPU9250_getDLPFMode();
void MPU9250_setDLPFMode(uint8_t bandwidth);

// GYRO_CONFIG register
uint8_t MPU9250_getFullScaleGyroRange();
void MPU9250_setFullScaleGyroRange(uint8_t range);

// ACCEL_CONFIG register
bool MPU9250_getAccelXSelfTest();
void MPU9250_setAccelXSelfTest(bool enabled);
bool MPU9250_getAccelYSelfTest();
void MPU9250_setAccelYSelfTest(bool enabled);
bool MPU9250_getAccelZSelfTest();
void MPU9250_setAccelZSelfTest(bool enabled);
uint8_t MPU9250_getFullScaleAccelRange();
void MPU9250_setFullScaleAccelRange(uint8_t range);
uint8_t MPU9250_getDHPFMode();
void MPU9250_setDHPFMode(uint8_t mode);

// FF_THR register
//uint8_t MPU9250_getFreefallDetectionThreshold();
//void MPU9250_setFreefallDetectionThreshold(uint8_t threshold);

// FF_DUR register
//uint8_t MPU9250_getFreefallDetectionDuration();
//void MPU9250_setFreefallDetectionDuration(uint8_t duration);

// MOT_THR register
uint8_t MPU9250_getMotionDetectionThreshold();
void MPU9250_setMotionDetectionThreshold(uint8_t threshold);

// MOT_DUR register
uint8_t MPU9250_getMotionDetectionDuration();
void MPU9250_setMotionDetectionDuration(uint8_t duration);

// ZRMOT_THR register
uint8_t MPU9250_getZeroMotionDetectionThreshold();
void MPU9250_setZeroMotionDetectionThreshold(uint8_t threshold);

// ZRMOT_DUR register
uint8_t MPU9250_getZeroMotionDetectionDuration();
void MPU9250_setZeroMotionDetectionDuration(uint8_t duration);

// FIFO_EN register
bool MPU9250_getTempFIFOEnabled();
void MPU9250_setTempFIFOEnabled(bool enabled);
bool MPU9250_getXGyroFIFOEnabled();
void MPU9250_setXGyroFIFOEnabled(bool enabled);
bool MPU9250_getYGyroFIFOEnabled();
void MPU9250_setYGyroFIFOEnabled(bool enabled);
bool MPU9250_getZGyroFIFOEnabled();
void MPU9250_setZGyroFIFOEnabled(bool enabled);
bool MPU9250_getAccelFIFOEnabled();
void MPU9250_setAccelFIFOEnabled(bool enabled);
bool MPU9250_getSlave2FIFOEnabled();
void MPU9250_setSlave2FIFOEnabled(bool enabled);
bool MPU9250_getSlave1FIFOEnabled();
void MPU9250_setSlave1FIFOEnabled(bool enabled);
bool MPU9250_getSlave0FIFOEnabled();
void MPU9250_setSlave0FIFOEnabled(bool enabled);

// I2C_MST_CTRL register
bool MPU9250_getMultiMasterEnabled();
void MPU9250_setMultiMasterEnabled(bool enabled);
bool MPU9250_getWaitForExternalSensorEnabled();
void MPU9250_setWaitForExternalSensorEnabled(bool enabled);
bool MPU9250_getSlave3FIFOEnabled();
void MPU9250_setSlave3FIFOEnabled(bool enabled);
bool MPU9250_getSlaveReadWriteTransitionEnabled();
void MPU9250_setSlaveReadWriteTransitionEnabled(bool enabled);
uint8_t MPU9250_getMasterClockSpeed();
void MPU9250_setMasterClockSpeed(uint8_t speed);

// I2C_SLV* registers (Slave 0-3)
uint8_t MPU9250_getSlaveAddress(uint8_t num);
void MPU9250_setSlaveAddress(uint8_t num, uint8_t address);
uint8_t MPU9250_getSlaveRegister(uint8_t num);
void MPU9250_setSlaveRegister(uint8_t num, uint8_t reg);
bool MPU9250_getSlaveEnabled(uint8_t num);
void MPU9250_setSlaveEnabled(uint8_t num, bool enabled);
bool MPU9250_getSlaveWordByteSwap(uint8_t num);
void MPU9250_setSlaveWordByteSwap(uint8_t num, bool enabled);
bool MPU9250_getSlaveWriteMode(uint8_t num);
void MPU9250_setSlaveWriteMode(uint8_t num, bool mode);
bool MPU9250_getSlaveWordGroupOffset(uint8_t num);
void MPU9250_setSlaveWordGroupOffset(uint8_t num, bool enabled);
uint8_t MPU9250_getSlaveDataLength(uint8_t num);
void MPU9250_setSlaveDataLength(uint8_t num, uint8_t length);

// I2C_SLV* registers (Slave 4)
uint8_t MPU9250_getSlave4Address();
void MPU9250_setSlave4Address(uint8_t address);
uint8_t MPU9250_getSlave4Register();
void MPU9250_setSlave4Register(uint8_t reg);
void MPU9250_setSlave4OutputByte(uint8_t data);
bool MPU9250_getSlave4Enabled();
void MPU9250_setSlave4Enabled(bool enabled);
bool MPU9250_getSlave4InterruptEnabled();
void MPU9250_setSlave4InterruptEnabled(bool enabled);
bool MPU9250_getSlave4WriteMode();
void MPU9250_setSlave4WriteMode(bool mode);
uint8_t MPU9250_getSlave4MasterDelay();
void MPU9250_setSlave4MasterDelay(uint8_t delay);
uint8_t MPU9250_getSlate4InputByte();

// I2C_MST_STATUS register
bool MPU9250_getPassthroughStatus();
bool MPU9250_getSlave4IsDone();
bool MPU9250_getLostArbitration();
bool MPU9250_getSlave4Nack();
bool MPU9250_getSlave3Nack();
bool MPU9250_getSlave2Nack();
bool MPU9250_getSlave1Nack();
bool MPU9250_getSlave0Nack();

// INT_PIN_CFG register
bool MPU9250_getInterruptMode();
void MPU9250_setInterruptMode(bool mode);
bool MPU9250_getInterruptDrive();
void MPU9250_setInterruptDrive(bool drive);
bool MPU9250_getInterruptLatch();
void MPU9250_setInterruptLatch(bool latch);
bool MPU9250_getInterruptLatchClear();
void MPU9250_setInterruptLatchClear(bool clear);
bool MPU9250_getFSyncInterruptLevel();
void MPU9250_setFSyncInterruptLevel(bool level);
bool MPU9250_getFSyncInterruptEnabled();
void MPU9250_setFSyncInterruptEnabled(bool enabled);
bool MPU9250_getI2CBypassEnabled();
void MPU9250_setI2CBypassEnabled(bool enabled);
bool MPU9250_getClockOutputEnabled();
void MPU9250_setClockOutputEnabled(bool enabled);

// INT_ENABLE register
uint8_t MPU9250_getIntEnabled();
void MPU9250_setIntEnabled(uint8_t enabled);
bool MPU9250_getIntFreefallEnabled();
void MPU9250_setIntFreefallEnabled(bool enabled);
bool MPU9250_getIntMotionEnabled();
void MPU9250_setIntMotionEnabled(bool enabled);
bool MPU9250_getIntZeroMotionEnabled();
void MPU9250_setIntZeroMotionEnabled(bool enabled);
bool MPU9250_getIntFIFOBufferOverflowEnabled();
void MPU9250_setIntFIFOBufferOverflowEnabled(bool enabled);
bool MPU9250_getIntI2CMasterEnabled();
void MPU9250_setIntI2CMasterEnabled(bool enabled);
bool MPU9250_getIntDataReadyEnabled();
void MPU9250_setIntDataReadyEnabled(bool enabled);

// INT_STATUS register
uint8_t MPU9250_getIntStatus();
bool MPU9250_getIntFreefallStatus();
bool MPU9250_getIntMotionStatus();
bool MPU9250_getIntZeroMotionStatus();
bool MPU9250_getIntFIFOBufferOverflowStatus();
bool MPU9250_getIntI2CMasterStatus();
bool MPU9250_getIntDataReadyStatus();

// ACCEL_*OUT_* registers
void MPU9250_getMotion9Real(float* ax, float* ay, float* az, float* gx,
		float* gy, float* gz, float* mx, float* my, float* mz);
void MPU9250_getMotion9(int16_t* ax, int16_t* ay, int16_t* az, int16_t* gx,
		int16_t* gy, int16_t* gz, int16_t* mx, int16_t* my, int16_t* mz);
void MPU9250_getMotion6(int16_t* ax, int16_t* ay, int16_t* az, int16_t* gx,
		int16_t* gy, int16_t* gz);
void MPU9250_getAcceleration(int16_t* x, int16_t* y, int16_t* z);
int16_t MPU9250_getAccelerationX();
int16_t MPU9250_getAccelerationY();
int16_t MPU9250_getAccelerationZ();

// TEMP_OUT_* registers
int16_t MPU9250_getTemperature();

// GYRO_*OUT_* registers
void MPU9250_getRotation(int16_t* x, int16_t* y, int16_t* z);
int16_t MPU9250_getRotationX();
int16_t MPU9250_getRotationY();
int16_t MPU9250_getRotationZ();

// EXT_SENS_DATA_* registers
uint8_t MPU9250_getExternalSensorByte(int position);
uint16_t MPU9250_getExternalSensorWord(int position);
uint32_t MPU9250_getExternalSensorDWord(int position);

// MOT_DETECT_STATUS register
bool MPU9250_getXNegMotionDetected();
bool MPU9250_getXPosMotionDetected();
bool MPU9250_getYNegMotionDetected();
bool MPU9250_getYPosMotionDetected();
bool MPU9250_getZNegMotionDetected();
bool MPU9250_getZPosMotionDetected();
bool MPU9250_getZeroMotionDetected();

// I2C_SLV*_DO register
void MPU9250_setSlaveOutputByte(uint8_t num, uint8_t data);

// I2C_MST_DELAY_CTRL register
bool MPU9250_getExternalShadowDelayEnabled();
void MPU9250_setExternalShadowDelayEnabled(bool enabled);
bool MPU9250_getSlaveDelayEnabled(uint8_t num);
void MPU9250_setSlaveDelayEnabled(uint8_t num, bool enabled);

// SIGNAL_PATH_RESET register
void MPU9250_resetGyroscopePath();
void MPU9250_resetAccelerometerPath();
void MPU9250_resetTemperaturePath();

// MOT_DETECT_CTRL register
uint8_t MPU9250_getAccelerometerPowerOnDelay();
void MPU9250_setAccelerometerPowerOnDelay(uint8_t delay);
uint8_t MPU9250_getFreefallDetectionCounterDecrement();
void MPU9250_setFreefallDetectionCounterDecrement(uint8_t decrement);
uint8_t MPU9250_getMotionDetectionCounterDecrement();
void MPU9250_setMotionDetectionCounterDecrement(uint8_t decrement);

// USER_CTRL register
bool MPU9250_getFIFOEnabled();
void MPU9250_setFIFOEnabled(bool enabled);
bool MPU9250_getI2CMasterModeEnabled();
void MPU9250_setI2CMasterModeEnabled(bool enabled);
void MPU9250_switchSPIEnabled(bool enabled);
void MPU9250_resetFIFO();
void MPU9250_resetI2CMaster();
void MPU9250_resetSensors();

// PWR_MGMT_1 register
void MPU9250_reset();
bool MPU9250_getSleepEnabled();
void MPU9250_setSleepEnabled(bool enabled);
bool MPU9250_getWakeCycleEnabled();
void MPU9250_setWakeCycleEnabled(bool enabled);
bool MPU9250_getTempSensorEnabled();
void MPU9250_setTempSensorEnabled(bool enabled);
uint8_t MPU9250_getClockSource();
void MPU9250_setClockSource(uint8_t source);

// PWR_MGMT_2 register
uint8_t MPU9250_getWakeFrequency();
void MPU9250_setWakeFrequency(uint8_t frequency);
bool MPU9250_getStandbyXAccelEnabled();
void MPU9250_setStandbyXAccelEnabled(bool enabled);
bool MPU9250_getStandbyYAccelEnabled();
void MPU9250_setStandbyYAccelEnabled(bool enabled);
bool MPU9250_getStandbyZAccelEnabled();
void MPU9250_setStandbyZAccelEnabled(bool enabled);
bool MPU9250_getStandbyXGyroEnabled();
void MPU9250_setStandbyXGyroEnabled(bool enabled);
bool MPU9250_getStandbyYGyroEnabled();
void MPU9250_setStandbyYGyroEnabled(bool enabled);
bool MPU9250_getStandbyZGyroEnabled();
void MPU9250_setStandbyZGyroEnabled(bool enabled);

// FIFO_COUNT_* registers
uint16_t MPU9250_getFIFOCount();

// FIFO_R_W register
uint8_t MPU9250_getFIFOByte();
void MPU9250_setFIFOByte(uint8_t data);
void MPU9250_getFIFOBytes(uint8_t *data, uint8_t length);

// WHO_AM_I register
uint8_t MPU9250_getDeviceID();
void MPU9250_setDeviceID(uint8_t id);

// ======== UNDOCUMENTED/DMP REGISTERS/METHODS ========

// XG_OFFS_TC register
uint8_t MPU9250_getOTPBankValid();
void MPU9250_setOTPBankValid(bool enabled);
int8_t MPU9250_getXGyroOffsetTC();
void MPU9250_setXGyroOffsetTC(int8_t offset);

// YG_OFFS_TC register
int8_t MPU9250_getYGyroOffsetTC();
void MPU9250_setYGyroOffsetTC(int8_t offset);

// ZG_OFFS_TC register
int8_t MPU9250_getZGyroOffsetTC();
void MPU9250_setZGyroOffsetTC(int8_t offset);

// X_FINE_GAIN register
int8_t MPU9250_getXFineGain();
void MPU9250_setXFineGain(int8_t gain);

// Y_FINE_GAIN register
int8_t MPU9250_getYFineGain();
void MPU9250_setYFineGain(int8_t gain);

// Z_FINE_GAIN register
int8_t MPU9250_getZFineGain();
void MPU9250_setZFineGain(int8_t gain);

// XA_OFFS_* registers
int16_t MPU9250_getXAccelOffset();
void MPU9250_setXAccelOffset(int16_t offset);

// YA_OFFS_* register
int16_t MPU9250_getYAccelOffset();
void MPU9250_setYAccelOffset(int16_t offset);

// ZA_OFFS_* register
int16_t MPU9250_getZAccelOffset();
void MPU9250_setZAccelOffset(int16_t offset);

// XG_OFFS_USR* registers
int16_t MPU9250_getXGyroOffset();
void MPU9250_setXGyroOffset(int16_t offset);

// YG_OFFS_USR* register
int16_t MPU9250_getYGyroOffset();
void MPU9250_setYGyroOffset(int16_t offset);

// ZG_OFFS_USR* register
int16_t MPU9250_getZGyroOffset();
void MPU9250_setZGyroOffset(int16_t offset);

// INT_ENABLE register (DMP functions)
bool MPU9250_getIntPLLReadyEnabled();
void MPU9250_setIntPLLReadyEnabled(bool enabled);
bool MPU9250_getIntDMPEnabled();
void MPU9250_setIntDMPEnabled(bool enabled);

// DMP_INT_STATUS
bool MPU9250_getDMPInt5Status();
bool MPU9250_getDMPInt4Status();
bool MPU9250_getDMPInt3Status();
bool MPU9250_getDMPInt2Status();
bool MPU9250_getDMPInt1Status();
bool MPU9250_getDMPInt0Status();

// INT_STATUS register (DMP functions)
bool MPU9250_getIntPLLReadyStatus();
bool MPU9250_getIntDMPStatus();

// USER_CTRL register (DMP functions)
bool MPU9250_getDMPEnabled();
void MPU9250_setDMPEnabled(bool enabled);
void MPU9250_resetDMP();

// BANK_SEL register
void MPU9250_setMemoryBank(uint8_t bank, bool prefetchEnabled, bool userBank);

// MEM_START_ADDR register
void MPU9250_setMemoryStartAddress(uint8_t address);

// MEM_R_W register
uint8_t MPU9250_readMemoryByte();
void MPU9250_writeMemoryByte(uint8_t data);
void MPU9250_readMemoryBlock(uint8_t *data, uint16_t dataSize, uint8_t bank,
		uint8_t address);
bool MPU9250_writeMemoryBlock(const uint8_t *data, uint16_t dataSize,
		uint8_t bank, uint8_t address, bool verify, bool useProgMem);
bool MPU9250_writeProgMemoryBlock(const uint8_t *data, uint16_t dataSize,
		uint8_t bank, uint8_t address, bool verify);
bool MPU9250_writeDMPConfigurationSet(const uint8_t *data, uint16_t dataSize,
		bool useProgMem);
bool MPU9250_writeProgDMPConfigurationSet(const uint8_t *data,
		uint16_t dataSize);

// DMP_CFG_1 register
uint8_t MPU9250_getDMPConfig1();
void MPU9250_setDMPConfig1(uint8_t config);

// DMP_CFG_2 register
uint8_t MPU9250_getDMPConfig2();
void MPU9250_setDMPConfig2(uint8_t config);

// special methods for MotionApps 2.0 implementation
#ifdef MPU9250_INCLUDE_DMP_MOTIONAPPS20
uint8_t *MPU9250_dmpPacketBuffer;
uint16_t MPU9250_dmpPacketSize;

uint8_t MPU9250_dmpInitialize();
bool MPU9250_dmpPacketAvailable();

uint8_t MPU9250_dmpSetFIFORate(uint8_t fifoRate);
uint8_t MPU9250_dmpGetFIFORate();
uint8_t MPU9250_dmpGetSampleStepSizeMS();
uint8_t MPU9250_dmpGetSampleFrequency();
int32_t MPU9250_dmpDecodeTemperature(int8_t tempReg);

// Register callbacks after a packet of FIFO data is processed
//uint8_t MPU9250_dmpRegisterFIFORateProcess(inv_obj_func func, int16_t priority);
//uint8_t MPU9250_dmpUnregisterFIFORateProcess(inv_obj_func func);
uint8_t MPU9250_dmpRunFIFORateProcesses();

// Setup FIFO for various output
uint8_t MPU9250_dmpSendQuaternion(uint_fast16_t accuracy);
uint8_t MPU9250_dmpSendGyro(uint_fast16_t elements, uint_fast16_t accuracy);
uint8_t MPU9250_dmpSendAccel(uint_fast16_t elements, uint_fast16_t accuracy);
uint8_t MPU9250_dmpSendLinearAccel(uint_fast16_t elements, uint_fast16_t accuracy);
uint8_t MPU9250_dmpSendLinearAccelInWorld(uint_fast16_t elements, uint_fast16_t accuracy);
uint8_t MPU9250_dmpSendControlData(uint_fast16_t elements, uint_fast16_t accuracy);
uint8_t MPU9250_dmpSendSensorData(uint_fast16_t elements, uint_fast16_t accuracy);
uint8_t MPU9250_dmpSendExternalSensorData(uint_fast16_t elements, uint_fast16_t accuracy);
uint8_t MPU9250_dmpSendGravity(uint_fast16_t elements, uint_fast16_t accuracy);
uint8_t MPU9250_dmpSendPacketNumber(uint_fast16_t accuracy);
uint8_t MPU9250_dmpSendQuantizedAccel(uint_fast16_t elements, uint_fast16_t accuracy);
uint8_t MPU9250_dmpSendEIS(uint_fast16_t elements, uint_fast16_t accuracy);

// Get Fixed Point data from FIFO
//uint8_t MPU9250_dmpGetAccel(int32_t *data, const uint8_t* packet=0);
uint8_t MPU9250_dmpGetAccel(int16_t *data, const uint8_t* packet=0);
uint8_t MPU9250_dmpGetAccelV(VectorInt16 *v, const uint8_t* packet=0);
//uint8_t MPU9250_dmpGetQuaternion(int32_t *data, const uint8_t* packet=0);
uint8_t MPU9250_dmpGetQuaternion(int16_t *data, const uint8_t* packet=0);
uint8_t MPU9250_dmpGetQuaternionQ(Quaternion *q, const uint8_t* packet=0);
//uint8_t MPU9250_dmpGet6AxisQuaternion(int32_t *data, const uint8_t* packet=0);
//uint8_t MPU9250_dmpGet6AxisQuaternion(int16_t *data, const uint8_t* packet=0);
//uint8_t MPU9250_dmpGet6AxisQuaternion(Quaternion *q, const uint8_t* packet=0);
//uint8_t MPU9250_dmpGetRelativeQuaternion(int32_t *data, const uint8_t* packet=0);
//uint8_t MPU9250_dmpGetRelativeQuaternion(int16_t *data, const uint8_t* packet=0);
//uint8_t MPU9250_dmpGetRelativeQuaternion(Quaternion *data, const uint8_t* packet=0);
//uint8_t MPU9250_dmpGetGyro(int32_t *data, const uint8_t* packet=0);
uint8_t MPU9250_dmpGetGyro(int16_t *data, const uint8_t* packet=0);
uint8_t MPU9250_dmpGetGyroV(VectorInt16 *v, const uint8_t* packet=0);
//uint8_t MPU9250_dmpSetLinearAccelFilterCoefficient(float coef);
//uint8_t MPU9250_dmpGetLinearAccel(int32_t *data, const uint8_t* packet=0);
//uint8_t MPU9250_dmpGetLinearAccel(int16_t *data, const uint8_t* packet=0);
//uint8_t MPU9250_dmpGetLinearAccel(VectorInt16 *v, const uint8_t* packet=0);
uint8_t MPU9250_dmpGetLinearAccel(VectorInt16 *v, VectorInt16 *vRaw, VectorFloat *gravity);
//uint8_t MPU9250_dmpGetLinearAccelInWorld(int32_t *data, const uint8_t* packet=0);
//uint8_t MPU9250_dmpGetLinearAccelInWorld(int16_t *data, const uint8_t* packet=0);
//uint8_t MPU9250_dmpGetLinearAccelInWorld(VectorInt16 *v, const uint8_t* packet=0);
uint8_t MPU9250_dmpGetLinearAccelInWorld(VectorInt16 *v, VectorInt16 *vReal, Quaternion *q);
//uint8_t MPU9250_dmpGetGyroAndAccelSensor(int32_t *data, const uint8_t* packet=0);
//uint8_t MPU9250_dmpGetGyroAndAccelSensor(int16_t *data, const uint8_t* packet=0);
//uint8_t MPU9250_dmpGetGyroAndAccelSensor(VectorInt16 *g, VectorInt16 *a, const uint8_t* packet=0);
//uint8_t MPU9250_dmpGetGyroSensor(int32_t *data, const uint8_t* packet=0);
//uint8_t MPU9250_dmpGetGyroSensor(int16_t *data, const uint8_t* packet=0);
//uint8_t MPU9250_dmpGetGyroSensor(VectorInt16 *v, const uint8_t* packet=0);
//uint8_t MPU9250_dmpGetControlData(int32_t *data, const uint8_t* packet=0);
//uint8_t MPU9250_dmpGetTemperature(int32_t *data, const uint8_t* packet=0);
//uint8_t MPU9250_dmpGetGravity(int32_t *data, const uint8_t* packet=0);
//uint8_t MPU9250_dmpGetGravity(int16_t *data, const uint8_t* packet=0);
//uint8_t MPU9250_dmpGetGravity(VectorInt16 *v, const uint8_t* packet=0);
uint8_t MPU9250_dmpGetGravity(VectorFloat *v, Quaternion *q);
//uint8_t MPU9250_dmpGetUnquantizedAccel(int32_t *data, const uint8_t* packet=0);
//uint8_t MPU9250_dmpGetUnquantizedAccel(int16_t *data, const uint8_t* packet=0);
//uint8_t MPU9250_dmpGetUnquantizedAccel(VectorInt16 *v, const uint8_t* packet=0);
//uint8_t MPU9250_dmpGetQuantizedAccel(int32_t *data, const uint8_t* packet=0);
//uint8_t MPU9250_dmpGetQuantizedAccel(int16_t *data, const uint8_t* packet=0);
//uint8_t MPU9250_dmpGetQuantizedAccel(VectorInt16 *v, const uint8_t* packet=0);
//uint8_t MPU9250_dmpGetExternalSensorData(int32_t *data, uint16_t size, const uint8_t* packet=0);
//uint8_t MPU9250_dmpGetEIS(int32_t *data, const uint8_t* packet=0);

uint8_t MPU9250_dmpGetEuler(float *data, Quaternion *q);
uint8_t MPU9250_dmpGetYawPitchRoll(float *data, Quaternion *q, VectorFloat *gravity);

// Get Floating Point data from FIFO
uint8_t MPU9250_dmpGetAccelFloat(float *data, const uint8_t* packet=0);
uint8_t MPU9250_dmpGetQuaternionFloat(float *data, const uint8_t* packet=0);

uint8_t MPU9250_dmpProcessFIFOPacket(const unsigned char *dmpData);
uint8_t MPU9250_dmpReadAndProcessFIFOPacket(uint8_t numPackets, uint8_t *processed=NULL);

uint8_t MPU9250_dmpSetFIFOProcessedCallback(void (*func) (void));

uint8_t MPU9250_dmpInitFIFOParam();
uint8_t MPU9250_dmpCloseFIFO();
uint8_t MPU9250_dmpSetGyroDataSource(uint8_t source);
uint8_t MPU9250_dmpDecodeQuantizedAccel();
uint32_t MPU9250_dmpGetGyroSumOfSquare();
uint32_t MPU9250_dmpGetAccelSumOfSquare();
void MPU9250_dmpOverrideQuaternion(long *q);
uint16_t MPU9250_dmpGetFIFOPacketSize();
#endif

// special methods for MotionApps 4.1 implementation
#ifdef MPU9250_INCLUDE_DMP_MOTIONAPPS41
uint8_t *MPU9250_dmpPacketBuffer;
uint16_t MPU9250_dmpPacketSize;

uint8_t MPU9250_dmpInitialize();
bool MPU9250_dmpPacketAvailable();

uint8_t MPU9250_dmpSetFIFORate(uint8_t fifoRate);
uint8_t MPU9250_dmpGetFIFORate();
uint8_t MPU9250_dmpGetSampleStepSizeMS();
uint8_t MPU9250_dmpGetSampleFrequency();
int32_t MPU9250_dmpDecodeTemperature(int8_t tempReg);

// Register callbacks after a packet of FIFO data is processed
//uint8_t MPU9250_dmpRegisterFIFORateProcess(inv_obj_func func, int16_t priority);
//uint8_t MPU9250_dmpUnregisterFIFORateProcess(inv_obj_func func);
uint8_t MPU9250_dmpRunFIFORateProcesses();

// Setup FIFO for various output
uint8_t MPU9250_dmpSendQuaternion(uint_fast16_t accuracy);
uint8_t MPU9250_dmpSendGyro(uint_fast16_t elements, uint_fast16_t accuracy);
uint8_t MPU9250_dmpSendAccel(uint_fast16_t elements, uint_fast16_t accuracy);
uint8_t MPU9250_dmpSendLinearAccel(uint_fast16_t elements, uint_fast16_t accuracy);
uint8_t MPU9250_dmpSendLinearAccelInWorld(uint_fast16_t elements, uint_fast16_t accuracy);
uint8_t MPU9250_dmpSendControlData(uint_fast16_t elements, uint_fast16_t accuracy);
uint8_t MPU9250_dmpSendSensorData(uint_fast16_t elements, uint_fast16_t accuracy);
uint8_t MPU9250_dmpSendExternalSensorData(uint_fast16_t elements, uint_fast16_t accuracy);
uint8_t MPU9250_dmpSendGravity(uint_fast16_t elements, uint_fast16_t accuracy);
uint8_t MPU9250_dmpSendPacketNumber(uint_fast16_t accuracy);
uint8_t MPU9250_dmpSendQuantizedAccel(uint_fast16_t elements, uint_fast16_t accuracy);
uint8_t MPU9250_dmpSendEIS(uint_fast16_t elements, uint_fast16_t accuracy);

// Get Fixed Point data from FIFO
uint8_t MPU9250_dmpGetAccel(int32_t *data, const uint8_t* packet=0);
uint8_t MPU9250_dmpGetAccel(int16_t *data, const uint8_t* packet=0);
uint8_t MPU9250_dmpGetAccel(VectorInt16 *v, const uint8_t* packet=0);
uint8_t MPU9250_dmpGetQuaternion(int32_t *data, const uint8_t* packet=0);
uint8_t MPU9250_dmpGetQuaternion(int16_t *data, const uint8_t* packet=0);
uint8_t MPU9250_dmpGetQuaternion(Quaternion *q, const uint8_t* packet=0);
uint8_t MPU9250_dmpGet6AxisQuaternion(int32_t *data, const uint8_t* packet=0);
uint8_t MPU9250_dmpGet6AxisQuaternion(int16_t *data, const uint8_t* packet=0);
uint8_t MPU9250_dmpGet6AxisQuaternion(Quaternion *q, const uint8_t* packet=0);
uint8_t MPU9250_dmpGetRelativeQuaternion(int32_t *data, const uint8_t* packet=0);
uint8_t MPU9250_dmpGetRelativeQuaternion(int16_t *data, const uint8_t* packet=0);
uint8_t MPU9250_dmpGetRelativeQuaternion(Quaternion *data, const uint8_t* packet=0);
uint8_t MPU9250_dmpGetGyro(int32_t *data, const uint8_t* packet=0);
uint8_t MPU9250_dmpGetGyro(int16_t *data, const uint8_t* packet=0);
uint8_t MPU9250_dmpGetGyro(VectorInt16 *v, const uint8_t* packet=0);
uint8_t MPU9250_dmpGetMag(int16_t *data, const uint8_t* packet=0);
uint8_t MPU9250_dmpSetLinearAccelFilterCoefficient(float coef);
uint8_t MPU9250_dmpGetLinearAccel(int32_t *data, const uint8_t* packet=0);
uint8_t MPU9250_dmpGetLinearAccel(int16_t *data, const uint8_t* packet=0);
uint8_t MPU9250_dmpGetLinearAccel(VectorInt16 *v, const uint8_t* packet=0);
uint8_t MPU9250_dmpGetLinearAccel(VectorInt16 *v, VectorInt16 *vRaw, VectorFloat *gravity);
uint8_t MPU9250_dmpGetLinearAccelInWorld(int32_t *data, const uint8_t* packet=0);
uint8_t MPU9250_dmpGetLinearAccelInWorld(int16_t *data, const uint8_t* packet=0);
uint8_t MPU9250_dmpGetLinearAccelInWorld(VectorInt16 *v, const uint8_t* packet=0);
uint8_t MPU9250_dmpGetLinearAccelInWorld(VectorInt16 *v, VectorInt16 *vReal, Quaternion *q);
uint8_t MPU9250_dmpGetGyroAndAccelSensor(int32_t *data, const uint8_t* packet=0);
uint8_t MPU9250_dmpGetGyroAndAccelSensor(int16_t *data, const uint8_t* packet=0);
uint8_t MPU9250_dmpGetGyroAndAccelSensor(VectorInt16 *g, VectorInt16 *a, const uint8_t* packet=0);
uint8_t MPU9250_dmpGetGyroSensor(int32_t *data, const uint8_t* packet=0);
uint8_t MPU9250_dmpGetGyroSensor(int16_t *data, const uint8_t* packet=0);
uint8_t MPU9250_dmpGetGyroSensor(VectorInt16 *v, const uint8_t* packet=0);
uint8_t MPU9250_dmpGetControlData(int32_t *data, const uint8_t* packet=0);
uint8_t MPU9250_dmpGetTemperature(int32_t *data, const uint8_t* packet=0);
uint8_t MPU9250_dmpGetGravity(int32_t *data, const uint8_t* packet=0);
uint8_t MPU9250_dmpGetGravity(int16_t *data, const uint8_t* packet=0);
uint8_t MPU9250_dmpGetGravity(VectorInt16 *v, const uint8_t* packet=0);
uint8_t MPU9250_dmpGetGravity(VectorFloat *v, Quaternion *q);
uint8_t MPU9250_dmpGetUnquantizedAccel(int32_t *data, const uint8_t* packet=0);
uint8_t MPU9250_dmpGetUnquantizedAccel(int16_t *data, const uint8_t* packet=0);
uint8_t MPU9250_dmpGetUnquantizedAccel(VectorInt16 *v, const uint8_t* packet=0);
uint8_t MPU9250_dmpGetQuantizedAccel(int32_t *data, const uint8_t* packet=0);
uint8_t MPU9250_dmpGetQuantizedAccel(int16_t *data, const uint8_t* packet=0);
uint8_t MPU9250_dmpGetQuantizedAccel(VectorInt16 *v, const uint8_t* packet=0);
uint8_t MPU9250_dmpGetExternalSensorData(int32_t *data, uint16_t size, const uint8_t* packet=0);
uint8_t MPU9250_dmpGetEIS(int32_t *data, const uint8_t* packet=0);

uint8_t MPU9250_dmpGetEuler(float *data, Quaternion *q);
uint8_t MPU9250_dmpGetYawPitchRoll(float *data, Quaternion *q, VectorFloat *gravity);

// Get Floating Point data from FIFO
uint8_t MPU9250_dmpGetAccelFloat(float *data, const uint8_t* packet=0);
uint8_t MPU9250_dmpGetQuaternionFloat(float *data, const uint8_t* packet=0);

uint8_t MPU9250_dmpProcessFIFOPacket(const unsigned char *dmpData);
uint8_t MPU9250_dmpReadAndProcessFIFOPacket(uint8_t numPackets, uint8_t *processed=NULL);

uint8_t MPU9250_dmpSetFIFOProcessedCallback(void (*func) (void));

uint8_t MPU9250_dmpInitFIFOParam();
uint8_t MPU9250_dmpCloseFIFO();
uint8_t MPU9250_dmpSetGyroDataSource(uint8_t source);
uint8_t MPU9250_dmpDecodeQuantizedAccel();
uint32_t MPU9250_dmpGetGyroSumOfSquare();
uint32_t MPU9250_dmpGetAccelSumOfSquare();
void MPU9250_dmpOverrideQuaternion(long *q);
uint16_t MPU9250_dmpGetFIFOPacketSize();
#endif

#endif /* _MPU9250_H_ */
