#ifndef BOARDDEF_H
#define BOARDDEF_H

/**************************************************************************//**
 * @file    brd_grsakura.h
 * @brief   GR-SAKURA Board definition
 * @version	V1.00
 * @date	26. July 2012.
 * @author	Tokushu Denshi Kairo Inc.
 * @note	Copyright &copy; 2011-2012 Tokushu Denshi Kairo Inc. All rights reserved.
 * @details これはボード固有のカスタマイズを行うためのヘッダファイルです
 ******************************************************************************/


#define  CPU_IS_RX63N                   //!< @brief CPUがRX63Nである
#define  ROMSIZE           (1024*1024)  //!< @brief ROMの容量(1MB)
#define  RAMSIZE           (128*1024)   //!< @brief RAMの容量(128kB)
#define  DEFAULT_SERIAL     SCI_USB0    //!< @brief Serial.beginで使うデフォルトのシリアルポート
#define  USBVCOM_VID        0x2129      //!< @brief USB仮想COMポートのベンダID
#define  USBVCOM_PID        0x0531      //!< @brief USB仮想COMポートのデバイスID

#define  USB_STRING_DESCRIPTOR_DATA \
	'G', 0x00, 'a', 0x00, 'd', 0x00, 'g', 0x00, \
	'e', 0x00, 't', 0x00, ' ', 0x00, 'R', 0x00, \
	'e', 0x00, 'n', 0x00, 'e', 0x00, 's', 0x00, \
	'a', 0x00, 's', 0x00, ' ', 0x00, 'S', 0x00, \
	'A', 0x00, 'K', 0x00, 'U', 0x00, 'R', 0x00, \
	'A', 0x00,

#include "tkdn_hal.h"

// ボードに応じた定数の設定
#ifndef TARGET_BOARD
  #define TARGET_BOARD      BOARD_GRSAKURA
#endif
#define CPU_TYPE            RX63N       //!< @brief CPUの種類
#define  BOARD_NAME        "GR-SAKURA"  //!< @brief ボードの名前

#define  EXISTS_SDMMC                   //!< @brief SDMMCカード用ソケットを持っている
//#define  EXISTS_SDRAM
//#define  EXISTS_SPIROM

// ピン番号マクロ
#define PIN_P21      0  //!< @brief PORT2.1 RXD0と共有
#define PIN_P20      1  //!< @brief PORT2.0 TXD0と共有
#define PIN_P22      2  //!< @brief PORT2.2 
#define PIN_P23      3  //!< @brief PORT2.3 
#define PIN_P24      4  //!< @brief PORT2.4 
#define PIN_P25      5  //!< @brief PORT2.5 
#define PIN_P32      6  //!< @brief PORT3.2 TXD6と共有
#define PIN_P33      7  //!< @brief PORT3.3 RXD6と共有
#define PIN_PC2      8  //!< @brief PORTC.2 SPI_CS3と共有
#define PIN_PC3      9  //!< @brief PORTC.3 
#define PIN_PC4      10 //!< @brief PORTC.4 SPI_CS0と共有
#define PIN_PC6      11 //!< @brief PORTC.6 SPI_MOSIと共有
#define PIN_PC7      12 //!< @brief PORTC.7 SPI_MISOと共有
#define PIN_PC5      13 //!< @brief PORTC.5 SPI_CLKと共有
#define PIN_P40      14 //!< @brief PORT4.0 ADCのCH0と共有
#define PIN_P41      15 //!< @brief PORT4.1 ADCのCH1と共有
#define PIN_P42      16 //!< @brief PORT4.2 ADCのCH2と共有
#define PIN_P43      17 //!< @brief PORT4.3 ADCのCH3と共有
#define PIN_P44      18 //!< @brief PORT4.4 ADCのCH4と共有
#define PIN_P45      19 //!< @brief PORT4.5 ADCのCH5と共有
#define PIN_P46      20 //!< @brief PORT4.6 ADCのCH6と共有
#define PIN_P47      21 //!< @brief PORT4.7 ADCのCH7と共有
#define PIN_PC0      22 //!< @brief PORTC.0 SPI_CS1と共有
#define PIN_PC1      23 //!< @brief PORTC.1 SPI_CS2と共有
#define PIN_P50      24 //!< @brief PORT5.0 TXD2と共有
#define PIN_P51      25 //!< @brief PORT5.1 
#define PIN_P52      26 //!< @brief PORT5.2 RXD2と共有
#define PIN_P53      27 //!< @brief PORT5.3 BCLKと共有
#define PIN_P54      28 //!< @brief PORT5.4 
#define PIN_P55      29 //!< @brief PORT5.5 
#define PIN_P12      30 //!< @brief PORT1.2 IRQ2/RXD2と共有
#define PIN_P13      31 //!< @brief PORT1.3 IRQ3
#define PIN_P14      32 //!< @brief PORT1.4 IRQ4/USB_DPUPEと共有
#define PIN_P15      33 //!< @brief PORT1.5 IRQ5/メモリカードの挿入信号(挿入でL)と共有
#define PIN_P16      34 //!< @brief PORT1.6 IRQ6/USB_VBUSと共有
#define PIN_P17      35 //!< @brief PORT1.7 IRQ7
#define PIN_PD0      36 //!< @brief PORTD.0 
#define PIN_PD1      37 //!< @brief PORTD.1 
#define PIN_PD2      38 //!< @brief PORTD.2 
#define PIN_PD3      39 //!< @brief PORTD.3 
#define PIN_PD4      40 //!< @brief PORTD.4 
#define PIN_PD5      41 //!< @brief PORTD.5 
#define PIN_PD6      42 //!< @brief PORTD.6 
#define PIN_PD7      43 //!< @brief PORTD.7 
#define PIN_PE0      44 //!< @brief PORTE.0 
#define PIN_PE1      45 //!< @brief PORTE.1 
#define PIN_PE2      46 //!< @brief PORTE.2 
#define PIN_PE3      47 //!< @brief PORTE.3 
#define PIN_PE4      48 //!< @brief PORTE.4 
#define PIN_PE5      49 //!< @brief PORTE.5 
#define PIN_PE6      50 //!< @brief PORTE.6 
#define PIN_PE7      51 //!< @brief PORTE.7 
#define PIN_P07      52 //!< @brief PORT0.7 
#define PIN_P05      53 //!< @brief PORT0.5 DA1と共有
#define PIN_P35      54 //!< @brief PORT3.5 NMIの別名
#define PIN_NMI      54 //!< @brief PORT3.5の別名
#define PIN_PJ3      55 //!< @brief PORTJ.3 ジャンクなI/Oポート

// 各種ライブラリで使われる
#define PIN_SDMMC_CS    PIN_PC0  //!< @def なに
#define SDMMC_RSPI_CH   0        //!< 
#define PHY_ADDR        0x00     //!< 
#define ETH_PORT_IS_AB           //!< 
#define USB_HOST_CH     0        //!< 
#define USB_FUNC_CH     0        //!< 
#define PIN_SDMMC_KEY   PIN_P15  //!< @def SDMMCカードの挿入検出用端子

#define NUM_DIGITAL_PINS            56 //!< @brief ディジタルI/Oの数。Arduinoとの互換用のマクロ
#define NUM_ANALOG_INPUTS           8  //!< @brief アナログ入力の数。Arduinoとの互換用のマクロ
#define analogInputToDigitalPin(p)  ((p < 8) ? (p) + 14 : -1) //!< @brief Arduinoとの互換用
#define digitalPinHasPWM(p)         (true) //!< @brief Arduinoとの互換用 すべてのピンでPWM使用可

static const unsigned char SS   = 10; //!< @brief Arduinoとの互換用マクロ SPIのCS端子の番号
static const unsigned char MOSI = 11; //!< @brief Arduinoとの互換用マクロ SPIのMOSI端子の番号
static const unsigned char MISO = 12; //!< @brief Arduinoとの互換用マクロ SPIのMISO端子の番号
static const unsigned char SCK  = 13; //!< @brief Arduinoとの互換用マクロ SPIのSCK端子の番号

static const unsigned char SDA = 18; //!< @brief Arduinoとの互換用マクロ I2CのSDA端子の番号
static const unsigned char SCL = 19; //!< @brief Arduinoとの互換用マクロ I2CのSCL端子の番号
static const unsigned char LED_BUILTIN = 100; //!< @brief Arduinoとの互換用マクロ LEDの端子番号

static const unsigned char A0 = 14; //!< @brief Arduinoとの互換用マクロ AN0の端子番号
static const unsigned char A1 = 15; //!< @brief Arduinoとの互換用マクロ AN1の端子番号
static const unsigned char A2 = 16; //!< @brief Arduinoとの互換用マクロ AN2の端子番号
static const unsigned char A3 = 17; //!< @brief Arduinoとの互換用マクロ AN3の端子番号
static const unsigned char A4 = 18; //!< @brief Arduinoとの互換用マクロ AN4の端子番号
static const unsigned char A5 = 19; //!< @brief Arduinoとの互換用マクロ AN5の端子番号
static const unsigned char A6 = 20; //!< @brief Arduinoとの互換用マクロ AN6の端子番号
static const unsigned char A7 = 21; //!< @brief Arduinoとの互換用マクロ AN7の端子番号

#endif /* BOARDDEF_H */

// 以下、ボード上のピン配置を定義する

#ifdef COMPILE_TKDNGPIO
const unsigned char GPIO_PINMAP[] =
{
	_PORT2 , _BIT1, // Arduino-D0  : P21
	_PORT2 , _BIT0, // Arduino-D1  : P20
	_PORT2 , _BIT2, // Arduino-D2  : P22
	_PORT2 , _BIT3, // Arduino-D3  : P23
	_PORT2 , _BIT4, // Arduino-D4  : P24
	_PORT2 , _BIT5, // Arduino-D5  : P25
	_PORT3 , _BIT2, // Arduino-D6  : P32
	_PORT3 , _BIT3, // Arduino-D7  : P33
	_PORTC , _BIT2, // Arduino-D8  : PC2
	_PORTC , _BIT3, // Arduino-D9  : PC3
	_PORTC , _BIT4, // Arduino-D10 : PC4
	_PORTC , _BIT6, // Arduino-D11 : PC6
	_PORTC , _BIT7, // Arduino-D12 : PC7
	_PORTC , _BIT5, // Arduino-D13 : PC5
	_PORT4 , _BIT0, // Arduino-D14 : P40
	_PORT4 , _BIT1, // Arduino-D15 : P41
	_PORT4 , _BIT2, // Arduino-D16 : P42
	_PORT4 , _BIT3, // Arduino-D17 : P43
	_PORT4 , _BIT4, // Arduino-D18 : P44
	_PORT4 , _BIT5, // Arduino-D19 : P45
	_PORT4 , _BIT6, //          20 : P46
	_PORT4 , _BIT7, //          21 : P47
	_PORTC , _BIT0, //          22 : PC0
	_PORTC , _BIT1, //          23 : PC1
	_PORT5 , _BIT0, //          24 : P50
	_PORT5 , _BIT1, //          25 : P51
	_PORT5 , _BIT2, //          26 : P52
	_PORT5 , _BIT3, //          27 : P53
	_PORT5 , _BIT4, //          28 : P54
	_PORT5 , _BIT5, //          29 : P55
	_PORT1 , _BIT2, //          30 : P12
	_PORT1 , _BIT3, //          31 : P13
	_PORT1 , _BIT4, //          32 : P14
	_PORT1 , _BIT5, //          33 : P15
	_PORT1 , _BIT6, //          34 : P16
	_PORT1 , _BIT7, //          35 : P17
	_PORTD , _BIT0, //          36 : PD0
	_PORTD , _BIT1, //          37 : PD1
	_PORTD , _BIT2, //          38 : PD2
	_PORTD , _BIT3, //          39 : PD3
	_PORTD , _BIT4, //          40 : PD4
	_PORTD , _BIT5, //          41 : PD5
	_PORTD , _BIT6, //          42 : PD6
	_PORTD , _BIT7, //          43 : PD7
	_PORTE , _BIT0, //          44 : PE0
	_PORTE , _BIT1, //          45 : PE1
	_PORTE , _BIT2, //          46 : PE2
	_PORTE , _BIT3, //          47 : PE3
	_PORTE , _BIT4, //          48 : PE4
	_PORTE , _BIT5, //          49 : PE5
	_PORTE , _BIT6, //          50 : PE6
	_PORTE , _BIT7, //          51 : PE7
	_PORT0 , _BIT7, //          52 : P07
	_PORT0 , _BIT5, //          53 : P05
	_PORT3 , _BIT5, //          54 : P35/NMI
	_PORTJ , _BIT3, //          55 : PJ3
};

const unsigned char SFP_PINMAP[] =
{
	_PORTA , _BIT0, //          LED0
	_PORTA , _BIT1, //          LED1
	_PORTA , _BIT2, //          LED2
	_PORTA , _BIT6, //          LED3
	_PORTA , _BIT6, //          BUZZ
	_PORTA , _BIT7, //          SW
	_PORTC , _BIT4, //          SPI_CS0
	_PORTC , _BIT0, //          SPI_CS1
	_PORTC , _BIT1, //          SPI_CS2
	_PORTC , _BIT2, //          SPI_CS3
};

#endif
