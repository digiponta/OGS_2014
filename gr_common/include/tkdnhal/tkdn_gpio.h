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

#ifndef __H_TKDN_GPIO
#define __H_TKDN_GPIO
/**************************************************************************//**
 * @file    tkdn_gpio.h
 * @brief   RX62N/RX63NのGPIOを操作するための低レベルなルーチン
 * @todo	このライブラリはRX63N用に作られてしまったのでRX62Nでは使えない。RX62Nでも使えるようにしなければならない。
 ******************************************************************************/

#include "tkdn_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

//■■■■■■■■■■■■■■■■■■■■■■■■■
//  ユーザがカスタマイズする場所はありません
//■■■■■■■■■■■■■■■■■■■■■■■■■

// Arduino互換ピン
#define PIN_ARD0       0    //!< @brief Arduino互換ピンのデジタル0番を指定するためのピン名
#define PIN_ARD1       1    //!< @brief  Arduino互換ピンのデジタル1番を指定するためのピン名
#define PIN_ARD2       2    //!< @brief  Arduino互換ピンのデジタル2番を指定するためのピン名
#define PIN_ARD3       3    //!< @brief  Arduino互換ピンのデジタル3番を指定するためのピン名
#define PIN_ARD4       4    //!< @brief  Arduino互換ピンのデジタル4番を指定するためのピン名
#define PIN_ARD5       5    //!< @brief  Arduino互換ピンのデジタル5番を指定するためのピン名
#define PIN_ARD6       6    //!< @brief  Arduino互換ピンのデジタル6番を指定するためのピン名
#define PIN_ARD7       7    //!< @brief  Arduino互換ピンのデジタル7番を指定するためのピン名
#define PIN_ARD8       8    //!< @brief  Arduino互換ピンのデジタル8番を指定するためのピン名
#define PIN_ARD9       9    //!< @brief  Arduino互換ピンのデジタル9番を指定するためのピン名
#define PIN_ARD10      10   //!< @brief  Arduino互換ピンのデジタル10番を指定するためのピン名
#define PIN_ARD11      11   //!< @brief  Arduino互換ピンのデジタル11番を指定するためのピン名
#define PIN_ARD12      12   //!< @brief  Arduino互換ピンのデジタル12番を指定するためのピン名
#define PIN_ARD13      13   //!< @brief  Arduino互換ピンのデジタル13番を指定するためのピン名
#define PIN_ARD14      14   //!< @brief  Arduino互換ピンのデジタル14番/アナログ0番を指定するためのピン名
#define PIN_ARD15      15   //!< @brief  Arduino互換ピンのデジタル15番/アナログ1番を指定するためのピン名
#define PIN_ARD16      16   //!< @brief  Arduino互換ピンのデジタル16番/アナログ2番を指定するためのピン名
#define PIN_ARD17      17   //!< @brief  Arduino互換ピンのデジタル17番/アナログ3番を指定するためのピン名
#define PIN_ARD18      18   //!< @brief  Arduino互換ピンのデジタル18番/アナログ4番を指定するためのピン名
#define PIN_ARD19      19   //!< @brief  Arduino互換ピンのデジタル19番/アナログ5番を指定するためのピン名

// ボード上のコンポーネント
#define PIN_FIRST_BOARDPIN 100  // ボード上のコンポーネントの最初のピン番号
#define PIN_LED0           100  //!< @brief ボード上のLED0を操作するためのピン名
#define PIN_LED1           101  //!< @brief ボード上のLED1を操作するためのピン名
#define PIN_LED2           102  //!< @brief ボード上のLED2を操作するためのピン名
#define PIN_LED3           103  //!< @brief ボード上のLED3を操作するためのピン名
#define PIN_BUZZ           104  //!< @brief ボード上のブザーを操作するためのピン名
#define PIN_SW             105  //!< @brief ボード上の青色SWを操作するためのピン名
#define PIN_SPI_CS0        106  //!< @brief ボード上のSPIのCS0番を操作するためのピン名
#define PIN_SPI_CS1        107  //!< @brief ボード上のSPIのCS1番を操作するためのピン名
#define PIN_SPI_CS2        108  //!< @brief ボード上のSPIのCS2番を操作するためのピン名
#define PIN_SPI_CS3        109  //!< @brief ボード上のSPIのCS3番を操作するためのピン名
#define PIN_LAST_BOARDPIN  109  // ボード上のコンポーネントの最後のピン番号

#ifndef INPUT
#define INPUT        0           //!< @brief GPIOの方向設定で使う定数。指定されたピンを入力にする。
#endif
#ifndef OUTPUT
#define OUTPUT       1           //!< @brief GPIOの方向設定で使う定数。指定されたピンを出力にする。
#endif
#ifndef INPUT_PULLUP
#define INPUT_PULLUP 2           //!< @brief GPIOの方向設定で使う定数。指定されたピンを入力にして内蔵プルアップを有効にする。
#endif
#ifndef OUTPUT_HIGH
#define OUTPUT_HIGH  3           //!< @brief GPIOの方向設定で使う定数。指定されたピンを出力にして、高出力駆動モードにする。
#endif

/*********************************************************************//**
 * @brief     ピンの入出力方向を設定する
 * @param     pinnum 操作したい目的のピンの番号
 * @param     isoutput 
 *             - INPUT (0):入力 
 *             - OUTPUT (1):出力
 *             - INPUT_PULLUP (2):入力で内蔵プルアップ抵抗有効
 *             - OUTPUT_HIGH (3):出力で高出力駆動モード (RX63Nのみ)
 * @note      RX63Nの場合、ADC入力に設定されている端子を指定すると、デジタルモードに切り替わる
 * @note      存在しないピン番号を指定した場合は、安全に終了する
 **********************************************************************/
void gpio_set_pinmode(int pinnum,int isoutput);

/*********************************************************************//**
 * @brief     指定されたピンから出力する
 * @param     pinnum 操作したい目的のピンの番号
 * @param     state 
 *             - LOW (0):LOWレベル
 *             - HIGH (1):HIGHレベル
 * @return    なし
 * @note      入力ピンに対してHIGHレベルを出力しようとした場合、入力状態のまま内蔵プルアップ抵抗がONになる
 * @note      存在しないピン番号を指定した場合は、安全に終了する
 **********************************************************************/
void gpio_write_port(int pinnum,int state);

/*********************************************************************//**
 * @brief     指定されたピンの状態を入力する
 * @param     pinnum 操作したい目的のピンの番号
 * @return    ピンの入力状態 0:LOWレベル、1:HIGHレベル
 * @note      存在しないピン番号を指定した場合は、安全に終了する
 **********************************************************************/
int  gpio_read_port(int pinnum);

#ifdef __cplusplus
 }
#endif

#endif // __H_TKDN_GPIO
