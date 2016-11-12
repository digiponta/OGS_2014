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

#ifndef __H_TKDN_SPI
#define __H_TKDN_SPI
/**************************************************************************//**
 * @file    tkdn_spi.h
 * @brief   RXマイコンの内蔵RSPIモジュールを利用して、SPI機能を実現する
 ******************************************************************************/

#include "tkdn_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

//■■■■■■■■■■■■■■■■■■■■■■■■■
//  ユーザがカスタマイズする場所はありません
//■■■■■■■■■■■■■■■■■■■■■■■■■

//各種関数

//! @brief SCIポートのCSが出力される場所
typedef enum {
	SPI_PORT_NONE         = 255, //!< @brief CSは自動では出力されない
	SPI_PORT_CS0_DUINO    = 0,   //!< @brief CS0
	SPI_PORT_CS1_MARY1    = 1,   //!< @brief CS1
	SPI_PORT_CS2_MARY2    = 2,   //!< @brief CS2
	SPI_PORT_CS3_ROM      = 3,   //!< @brief CS3
	SPI_PORT_SDMMC        = 4,   //!< @brief ext
	SPI_SSLB0             = 0,   //!< @brief CS0
	SPI_SSLB1             = 1,   //!< @brief CS1
	SPI_PORT_RAXINO_EXT   = 0,   //!< @brief Arduino互換ポートのCS端子
	SPI_PORT_RAXINO_SDMMC = 1,   //!< @brief メモリカードソケット
	SPI_PORT_RAXINO_ROM   = 2,   //!< @brief RaXinoの場合のオンボードSPI ROM
	SPI_PORT_RAXINO_ACCEL = 3,   //!< @brief RaXinoの場合のオンボード加速度センサ
} SPI_PORT;

//! @brief シリアル変換の際のビットの並び
typedef enum {
	SPI_LSBFIRST, //!< @brief LSBを先に送出する
	SPI_MSBFIRST  //!< @brief MSBを先に送出する
} SPI_BIT_ORDER;

//! @brief SPIクロックの速度
typedef enum {
	SPI_CLOCK_DIV2,  //!< @brief PCLK/2   (24MHz)
	SPI_CLOCK_DIV4,  //!< @brief PCLK/4   (12MHz)
	SPI_CLOCK_DIV8,  //!< @brief PCLK/8   (6MHz)
	SPI_CLOCK_DIV16, //!< @brief PCLK/16  (3MHz)
	SPI_CLOCK_DIV32, //!< @brief PCLK/32  (1.5MHz)
	SPI_CLOCK_DIV64, //!< @brief PCLK/64  (750kHz)
	SPI_CLOCK_DIV128 //!< @brief PCLK/128 (375kHz)
} SPI_CLK_DIVIDER;

//! @brief SPIモード
typedef enum { 
	SPI_MODE0, //!< @brief アイドル時のクロックがL、立ち上がりでサンプリング
	SPI_MODE1, //!< @brief アイドル時のクロックがL、立ち下がりでサンプリング
	SPI_MODE2, //!< @brief アイドル時のクロックがH、立ち上がりでサンプリング
	SPI_MODE3  //!< @brief アイドル時のクロックがH、立ち下がりでサンプリング
} SPI_DATA_MODE;

/*********************************************************************//**
 * @brief     SPIのモジュールスタンバイ状態を解除し、各種レジスタをセットアップする
 * @note      該当するI/O端子は周辺機能モードになる
 * @warning   すべてのSPI関数に先だって、この関数を呼び出さなければならない
 * @return    なし
 **********************************************************************/
void spi_init(void);

/*********************************************************************//**
 * @brief     SPIライブラリを終了する
 * @note      該当するI/O端子はGPIOモードになる。モジュールスタンバイ状態には戻さない。
 * @return    なし
 **********************************************************************/
void spi_terminate(void);

/*********************************************************************//**
 * @brief     SPIの使用するポートを設定する
 * @param     port 使用するポート
 * @return    なし
 **********************************************************************/
void spi_set_port(SPI_PORT port);

/*********************************************************************//**
 * @brief     SPIのビット長を設定する
 * @param     bit_length 8～16,20,24,32のいずれかの値を指定する。
 * @note      SPIの送受信はハードウェア的に行っているので、上記以外の長さは設定できない。
 * @return    なし
 **********************************************************************/
void spi_set_bit_length(int bit_length);

/*********************************************************************//**
 * @brief     SPIのビットオーダーを設定する
 * @param     bit_order SPI_MSBFIRST または SPI_LSBFIRST のいずれか
 * @return    なし
 **********************************************************************/
void spi_set_bit_order(SPI_BIT_ORDER bit_order) ;

/*********************************************************************//**
 * @brief     SPIのクロック速度(PCLKに対する分周比)を指定する
 * @param     divider 次の値のいずれかを指定する
 *             - SPI_CLOCK_DIV2   : PCLK/2   (24MHz)
 *             - SPI_CLOCK_DIV4   : PCLK/4   (12MHz)
 *             - SPI_CLOCK_DIV8   : PCLK/8   (6MHz)
 *             - SPI_CLOCK_DIV16  : PCLK/16  (3MHz)
 *             - SPI_CLOCK_DIV32  : PCLK/32  (1.5MHz)
 *             - SPI_CLOCK_DIV64  : PCLK/64  (750kHz)
 *             - SPI_CLOCK_DIV128 : PCLK/128 (375kHz)
 *            これ以外の値を指定しないこと
 * @note      デフォルトの分周比は不明
 * @return    なし
 **********************************************************************/
void spi_set_clock_divider(SPI_CLK_DIVIDER divider);

/*********************************************************************//**
 * @brief     SPIのデータモードを指定する
 * @param     mode データモード
 *             - SPI_MODE0 アイドル時のクロックがL、立ち上がりでサンプリング
 *             - SPI_MODE1 アイドル時のクロックがL、立ち下がりでサンプリング
 *             - SPI_MODE2 アイドル時のクロックがH、立ち上がりでサンプリング
 *             - SPI_MODE3 アイドル時のクロックがH、立ち下がりでサンプリング
 * @note      デフォルトのモードは0
 * @return    なし
 **********************************************************************/
void spi_set_data_mode(SPI_DATA_MODE mode);

/*********************************************************************//**
 * @brief     SPIの送受信を行う
 * @param     txbyte 8～32bitのデータ。リトルエンディアン。実際に送信される長さは spi_set_bit_length() で指定する。
 * @return    受信したデータ
 **********************************************************************/
unsigned long spi_transfer(unsigned long txbyte);

#ifdef __cplusplus
 }
#endif

#endif // __H_TKDN_SPI
