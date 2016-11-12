/*******************************************************************************
* GR-SAKURA LIBRARY LICENSE.  LIMITATION and DISCLAIMER of WARRANTY
*
* This software is supplied by Tokushu Denshi Kairo Inc. and is only intended 
* for use with Gadget Renesas projects. No other uses are authorized.
* This software is owned by Tokuden and is protected under all applicable laws,
* including copyright laws. Disclosure or redistribution to others this headder
* file and related library file alone is not allowed.
* You can redistribute the executable object file (only SREC or BIN file) which
* is generated as a result of compilation and link your program.
* Of cource the limitation of this library license does not effect to your code.
* THIS SOFTWARE IS PROVIDED "AS IS" AND TOKUDEN MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* Tokuden reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the
* http://rx.tokudenkairo.co.jp/
* (C) Copyright 2011-2012 Tokushu Denshi Kairo Inc.
*******************************************************************************/

#ifndef BOARDDEF_H
#define BOARDDEF_H

////////////////////////////////////////////////////////////
// GR-UME Board definition
// Version 0.80   H24/6/1
// 
////////////////////////////////////////////////////////////

// これはボード固有のカスタマイズを行うためのヘッダファイルです
// トップディレクトリでmake use_***を実行すると自動的に書き換わります
// RXduinoのSerialクラスが使うデフォルトのポート番号

#define  CPU_IS_RX63N
#define  ROMSIZE           (1024*1024)
#define  RAMSIZE           (128*1024)
#define  DEFAULT_SERIAL     SCI_USB0
#define  USBVCOM_VID        0x2129
#define  USBVCOM_PID        0x0541
#define  USB_STRING_DESCRIPTOR_DATA \
	'G', 0x00, 'a', 0x00, 'd', 0x00, 'g', 0x00, \
	'e', 0x00, 't', 0x00, ' ', 0x00, 'R', 0x00, \
	'e', 0x00, 'n', 0x00, 'e', 0x00, 's', 0x00, \
	'a', 0x00, 's', 0x00, ' ', 0x00, 'U', 0x00, \
	'M', 0x00, 'E', 0x00, ' ', 0x00, ' ', 0x00, \
	' ', 0x00,

#include "tkdn_hal.h"

// ボードに応じた定数の設定
#ifndef TARGET_BOARD
  #define TARGET_BOARD      BOARD_GRUME
#endif
#define CPU_TYPE            RX63N
#define  BOARD_NAME        "GR-UME"

#define  EXISTS_SDMMC
//#define  EXISTS_SDRAM
//#define  EXISTS_SPIROM

// ピン番号マクロ
#define PIN_PD4      1 // LED0
#define PIN_PD5      2 // LED1
#define PIN_PD6      3 // LED2
#define PIN_PD7      4 // LED3
#define PIN_PC6      5
#define PIN_PC7      6
#define PIN_PC5      7
#define PIN_PC4      8
#define PIN_PC3      9
#define PIN_PC2      10
#define PIN_PE6      11
#define PIN_PE7      12
#define PIN_PE1      13
#define PIN_PE2      14
#define PIN_P45      15
#define PIN_P44      16
#define PIN_P43      17
#define PIN_P42      18
#define PIN_P41      19
#define PIN_P40      20
#define PIN_PE4      21
#define PIN_PE5      22
#define PIN_PE3      23
#define PIN_P24      24
#define PIN_P23      25
#define PIN_P17      26
#define PIN_P21      27
#define PIN_P20      28
#define PIN_PD1      29
#define PIN_PD2      30

// 各種ライブラリで使われる
#define PIN_SDMMC_CS    PIN_PC0
#define SDMMC_RSPI_CH   0
#define PHY_ADDR        0x00
#define ETH_PORT_IS_AB
#define USB_HOST_CH     0
#define USB_FUNC_CH     0

#endif /* BOARDDEF_H */

// 以下、ボード上のピン配置を定義する

#ifdef COMPILE_TKDNGPIO
const unsigned char GPIO_PINMAP[] =
{
	_PORTD , _BIT4, // LED0と兼用
	_PORTD , _BIT4, // LED0と兼用
	_PORTD , _BIT5, // LED1と兼用
	_PORTD , _BIT6, // LED2と兼用
	_PORTD , _BIT7, // LED3と兼用
	_PORTC , _BIT6, // 5番ピン
	_PORTC , _BIT7, // 6番ピン
	_PORTC , _BIT5, // 7番ピン
	_PORTC , _BIT4, // 8番ピン
	_PORTC , _BIT3, // 9番ピン
	_PORTC , _BIT2, // 10番ピン
	_PORTE , _BIT6, // 11番ピン
	_PORTE , _BIT7, // 12番ピン
	_PORTE , _BIT1, // 13番ピン
	_PORTE , _BIT2, // 14番ピン
	_PORT4 , _BIT5, // 15番ピン
	_PORT4 , _BIT4, // 16番ピン
	_PORT4 , _BIT3, // 17番ピン
	_PORT4 , _BIT2, // 18番ピン
	_PORT4 , _BIT1, // 19番ピン
	_PORT4 , _BIT0, // 20番ピン
	_PORTE , _BIT4, // 21番ピン
	_PORTE , _BIT5, // 22番ピン
	_PORTE , _BIT3, // 23番ピン
	_PORT2 , _BIT4, // 24番ピン
	_PORT2 , _BIT3, // 25番ピン
	_PORT1 , _BIT7, // 26番ピン
	_PORT2 , _BIT1, // 27番ピン
	_PORT2 , _BIT0, // 28番ピン
	_PORTD , _BIT1, // 29番ピン
	_PORTD , _BIT2, // 30番ピン
};

const unsigned char SFP_PINMAP[] =
{
	_PORTD , _BIT4, //          LED0
	_PORTD , _BIT5, //          LED1
	_PORTD , _BIT6, //          LED2
	_PORTD , _BIT7, //          LED3
	_PORTD , _BIT7, //          BUZZ
	_PORT3 , _BIT5, //          SW(NMI端子を使う)
	_PORTC , _BIT4, //          SPI_CS0
	_PORTC , _BIT0, //          SPI_CS1
	_PORTC , _BIT1, //          SPI_CS2
	_PORTC , _BIT2, //          SPI_CS3
};

#endif
