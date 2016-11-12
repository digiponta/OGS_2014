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

#ifndef __H_RXDUINO
#define __H_RXDUINO

/**************************************************************************//**
 * @file    rxduino.h
 * @brief   Renesas RX62N/63N用のArduino互換ライブラリ
 ******************************************************************************/
#define RXDUINO_API

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../tkdnhal/tkdn_hal.h"
#ifdef __cplusplus
	extern "C" {
#endif

// 型の定義
typedef bool  boolean;           //!< @brief 真(true)か偽(false)を表す型
typedef unsigned char  byte;     //!< @brief 8bitの符号無し数値(0～255)を表わす
typedef unsigned short word;     //!< @brief 16bitの符号無し数値(0～65535)を表わす
typedef unsigned char  uint8_t;  //!< @brief 8bitの符号無し数値(0～255)を表わす
typedef unsigned short uint16_t; //!< @brief 16bitの符号無し数値(0～65535)を表わす
typedef unsigned int   uint32_t; //!< @brief 32bitの符号無し数値(0～4294967295)を表わす
typedef unsigned long long uint64_t; //!< @brief 64bitの符号無し数値(0～18446744073709551615)を表わす
typedef          char   int8_t;  //!< @brief 8bitの符号付き数値(-128～127)を表わす
typedef          short  int16_t; //!< @brief 16bitの符号付き数値(-32768～32767)を表わす
typedef          int    int32_t; //!< @brief 32bitの符号付き数値(-2147483648～2147483647)を表わす
typedef          long long int64_t; //!< @brief 64bitの符号付き数値(-9223372036854775808～9223372036854775807)を表わす

// 定数の定義
#define F_CPU      96000000UL    //!< @brief CPUの動作周波数。96MHz

// A某互換の定数
#define LOW          0           //!< @brief GPIOの操作とピン割り込みで使う定数。ローレベルを表す
#define HIGH         1           //!< @brief GPIOの操作で使う定数。信号の状態がハイレベルを表す
#define INPUT        0           //!< @brief GPIOの方向設定で使う定数。指定されたピンを入力にする。
#define OUTPUT       1           //!< @brief GPIOの方向設定で使う定数。指定されたピンを出力にする。
#define INPUT_PULLUP 2           //!< @brief GPIOの方向設定で使う定数。指定されたピンを入力にして内蔵プルアップを有効にする。
#define OUTPUT_HIGH  3           //!< @brief GPIOの方向設定で使う定数。指定されたピンを出力にして、高出力駆動モードにする。

#define LSBFIRST     0           //!< @brief SPIで使う定数。LSBを先に入出力する。
#define MSBFIRST     1           //!< @brief SPIで使う定数。LSBを先に入出力する。

#define CHANGE       1            //!< @brief ピン割り込みで使う定数。端子の状態がどちらかに変化したことを表す。
#define FALLING      2            //!< @brief ピン割り込みで使う定数。端子の状態が立ち下がったことを表す。
#define RISING       3            //!< @brief ピン割り込みで使う定数。端子の状態が立ち上がったことを表す。

#define DEFAULT      0            //!< @brief アナログ変換で使う
#define EXTERNAL     1            //!< @brief アナログ変換で使う
#define INTERNAL     2            //!< @brief アナログ変換で使う
#define RAW12BIT     3            //!< @brief アナログ変換で使う

#define IO_DDR0        (*(volatile unsigned char *)0x0008C000) //!< PORT0.PDRへの高速なアクセス
#define IO_DDR1        (*(volatile unsigned char *)0x0008C001) //!< PORT1.PDRへの高速なアクセス
#define IO_DDR2        (*(volatile unsigned char *)0x0008C002) //!< PORT2.PDRへの高速なアクセス
#define IO_DDR3        (*(volatile unsigned char *)0x0008C003) //!< PORT3.PDRへの高速なアクセス
#define IO_DDR4        (*(volatile unsigned char *)0x0008C004) //!< PORT4.PDRへの高速なアクセス
#define IO_DDR5        (*(volatile unsigned char *)0x0008C005) //!< PORT5.PDRへの高速なアクセス
#define IO_DDR6        (*(volatile unsigned char *)0x0008C006) //!< PORT6.PDRへの高速なアクセス
#define IO_DDR7        (*(volatile unsigned char *)0x0008C007) //!< PORT7.PDRへの高速なアクセス
#define IO_DDR8        (*(volatile unsigned char *)0x0008C008) //!< PORT8.PDRへの高速なアクセス
#define IO_DDR9        (*(volatile unsigned char *)0x0008C009) //!< PORT9.PDRへの高速なアクセス
#define IO_DDRA        (*(volatile unsigned char *)0x0008C00a) //!< PORTA.PDRへの高速なアクセス
#define IO_DDRB        (*(volatile unsigned char *)0x0008C00b) //!< PORTB.PDRへの高速なアクセス
#define IO_DDRC        (*(volatile unsigned char *)0x0008C00c) //!< PORTC.PDRへの高速なアクセス
#define IO_DDRD        (*(volatile unsigned char *)0x0008C00d) //!< PORTD.PDRへの高速なアクセス
#define IO_DDRE        (*(volatile unsigned char *)0x0008C00e) //!< PORTE.PDRへの高速なアクセス
#define IO_DDRF        (*(volatile unsigned char *)0x0008C00f) //!< PORTF.PDRへの高速なアクセス

#define IO_PORT0       (*(volatile unsigned char *)0x0008C020) //!< PORT0.PODRへの高速なアクセス
#define IO_PORT1       (*(volatile unsigned char *)0x0008C021) //!< PORT1.PODRへの高速なアクセス
#define IO_PORT2       (*(volatile unsigned char *)0x0008C022) //!< PORT2.PODRへの高速なアクセス
#define IO_PORT3       (*(volatile unsigned char *)0x0008C023) //!< PORT3.PODRへの高速なアクセス
#define IO_PORT4       (*(volatile unsigned char *)0x0008C024) //!< PORT4.PODRへの高速なアクセス
#define IO_PORT5       (*(volatile unsigned char *)0x0008C025) //!< PORT5.PODRへの高速なアクセス
#define IO_PORT6       (*(volatile unsigned char *)0x0008C026) //!< PORT6.PODRへの高速なアクセス
#define IO_PORT7       (*(volatile unsigned char *)0x0008C027) //!< PORT7.PODRへの高速なアクセス
#define IO_PORT8       (*(volatile unsigned char *)0x0008C028) //!< PORT8.PODRへの高速なアクセス
#define IO_PORT9       (*(volatile unsigned char *)0x0008C029) //!< PORT9.PODRへの高速なアクセス
#define IO_PORTA       (*(volatile unsigned char *)0x0008C02A) //!< PORTA.PODRへの高速なアクセス
#define IO_PORTB       (*(volatile unsigned char *)0x0008C02B) //!< PORTB.PODRへの高速なアクセス
#define IO_PORTC       (*(volatile unsigned char *)0x0008C02C) //!< PORTC.PODRへの高速なアクセス
#define IO_PORTD       (*(volatile unsigned char *)0x0008C02D) //!< PORTD.PODRへの高速なアクセス
#define IO_PORTE       (*(volatile unsigned char *)0x0008C02E) //!< PORTE.PODRへの高速なアクセス
#define IO_PORTF       (*(volatile unsigned char *)0x0008C02F) //!< PORTF.PODRへの高速なアクセス

#define IO_PIN0        (*(volatile unsigned char *)0x0008C040) //!< PORT0.PIDRへの高速なアクセス
#define IO_PIN1        (*(volatile unsigned char *)0x0008C041) //!< PORT1.PIDRへの高速なアクセス
#define IO_PIN2        (*(volatile unsigned char *)0x0008C042) //!< PORT2.PIDRへの高速なアクセス
#define IO_PIN3        (*(volatile unsigned char *)0x0008C043) //!< PORT3.PIDRへの高速なアクセス
#define IO_PIN4        (*(volatile unsigned char *)0x0008C044) //!< PORT4.PIDRへの高速なアクセス
#define IO_PIN5        (*(volatile unsigned char *)0x0008C045) //!< PORT5.PIDRへの高速なアクセス
#define IO_PIN6        (*(volatile unsigned char *)0x0008C046) //!< PORT6.PIDRへの高速なアクセス
#define IO_PIN7        (*(volatile unsigned char *)0x0008C047) //!< PORT7.PIDRへの高速なアクセス
#define IO_PIN8        (*(volatile unsigned char *)0x0008C048) //!< PORT8.PIDRへの高速なアクセス
#define IO_PIN9        (*(volatile unsigned char *)0x0008C049) //!< PORT9.PIDRへの高速なアクセス
#define IO_PINA        (*(volatile unsigned char *)0x0008C04A) //!< PORTA.PIDRへの高速なアクセス
#define IO_PINB        (*(volatile unsigned char *)0x0008C04B) //!< PORTB.PIDRへの高速なアクセス
#define IO_PINC        (*(volatile unsigned char *)0x0008C04C) //!< PORTC.PIDRへの高速なアクセス
#define IO_PIND        (*(volatile unsigned char *)0x0008C04D) //!< PORTD.PIDRへの高速なアクセス
#define IO_PINE        (*(volatile unsigned char *)0x0008C04E) //!< PORTE.PIDRへの高速なアクセス
#define IO_PINF        (*(volatile unsigned char *)0x0008C04F) //!< PORTF.PIDRへの高速なアクセス

static const int BIN  = 2;   //!< @brief Serial.print等で基数の指定に使う
static const int OCT  = 8;   //!< @brief Serial.print等で基数の指定に使う
static const int DEC  = 10;  //!< @brief Serial.print等で基数の指定に使う
static const int HEX  = 16;  //!< @brief Serial.print等で基数の指定に使う
static const int BYTE = 256; //!< @brief Serial.print等で基数の指定に使う

// 次の2つの関数はユーザが作るもの
/**
* @brief  ユーザが作る関数。システム起動時に1回だけ呼び出される。
* @param  なし
* @return なし
*/ 
extern void setup(void);

/**
* @brief  ユーザが作る関数。システム起動後に繰り返し呼び出される。
* @param  なし
* @return なし
* @warning ユーザはこの関数は必ずreturnさせること。<BR>
*          システムはloopの後で、イーサネットの処理など重要な処理を行っているので、<BR>
*          loopが制御を戻さないと重要な処理ができなくなる。
*/ 
extern void loop(void);

/*********************************************************************//**
 * @brief     ソフトリセットを行い、システムをリブートする
 * @param     run_userapp リブート後の状態
 *             - false: リセット後にファームウェアを起動する
 *             - true : リセット後にユーザアプリを起動する
 *            上記以外の値を指定した場合の動作は保証されない
 * @return    なし
 * @note      ファームウェア起動は、がじぇるねプロジェクトのボードが対象
 **********************************************************************/
void Reboot(bool run_userapp);

// イーサネット用の受信処理関数を登録するための型
typedef void (*FUNCTYPE_ETHER_HANDLER)(void);

// イーサネット用の受信処理関数を登録する
void registEthernetHandler(FUNCTYPE_ETHER_HANDLER func);

#define RXDUINO_VERSION 0x01080000 // Version 1.08

const char RXDUINO_COPYRIGHT[] = "(C)Copyright 2012-2013 Tokushu Denshi Kairo Inc.";

#ifdef __cplusplus
	}
#endif

#include "serial.h"
#include "digitalio.h"
#include "delay.h"
#include "analogio.h"
#include "tone.h"
#include "shiftout.h"
#include "wiring.h"
#include "progmem.h"
#include "interrupt.h"
#include "random.h"
#include "binary.h"
#include "rxstring.h"

#endif // __H_RXDUINO

