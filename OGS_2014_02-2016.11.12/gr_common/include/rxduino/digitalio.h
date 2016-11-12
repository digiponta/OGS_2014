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

#ifndef	__H_RXDUINO_DIGITALIO
#define	__H_RXDUINO_DIGITALIO
/**************************************************************************//**
 * @file    digitalio.h
 * @brief   GPIOの操作に関するライブラリ
 ******************************************************************************/
#include "rxduino.h"

#ifdef __cplusplus
	extern "C" {
#endif

#if 0
// digitaiWrite関数で使う定数
/*!
@def  LOW
@brief digitaiWrite関数で使う定数(論理ゼロ:LOW)
*/
#define LOW  0

/*!
@def  HIGH
@brief digitaiWrite関数で使う定数(論理1:HIGH)
*/
#define HIGH 1

// pinMode関数で使う定数
#define INPUT        0           //!< @brief GPIOの方向設定で使う定数。指定されたピンを入力にする。
#define OUTPUT       1           //!< @brief GPIOの方向設定で使う定数。指定されたピンを出力にする。
#define INPUT_PULLUP 2           //!< @brief GPIOの方向設定で使う定数。指定されたピンを入力にして内蔵プルアップを有効にする。
#define OUTPUT_HIGH  3           //!< @brief GPIOの方向設定で使う定数。指定されたピンを出力にして、高出力駆動モードにする。
#endif

//------------------------------------------------------------------
// デジタル入出力
//------------------------------------------------------------------

/*********************************************************************//**
 * @brief		指定したピンから、HIGHまたはLOWを出力する
 * @param[in]	pin ピン番号(@ref grsakura_pin で宣言したピン番号)
 * @param[in]	value 出力状態の選択
 * 				- 0 : 指定したピンからLOWを出力
 * 				- 1 : 指定したピンからHIGHを出力
 * @note        この関数を呼び出す前に、pinMode()を使ってOUTPUTにしておくこと。デフォルトではINPUTでもOUTPUTでもない。
 * @note        INPUTに指定された端子からHIGHを出すと、内蔵プルアップ抵抗が有効になる。
 * @warning     RXの内蔵ペリフェラルの出力として使用されている端子は、この関数では出力を変更できない。
 * @return		なし
 **********************************************************************/
void digitalWrite(int pin,int value);

// ----------------------------------------
// pinMode(pin, mode)
// ピンの動作を入力か出力に設定します。
// [パラメータ]
// pin: 設定したいピンの番号
// mode: INPUTかOUTPUT
// [戻り値]
// なし
// ----------------------------------------
/*********************************************************************//**
 * @brief		指定したピンを入力または出力に設定する
 * @param[in]	pin ピン番号(@ref grsakura_pin で宣言したピン番号)
 * @param[in]	mode 出力状態の選択
 * 				- INPUT        0: 指定したピンは入力モード
 *				- OUTPUT       1: 指定したピンは出力モード
 *				- INPUT_PULLUP 2: 入力でプルアップ有効。未実装
 *				- OUTPUT_HIGH  3: 高駆動出力
 * @return		なし
 * @note        この関数は、アナログ入力に設定された端子をデジタル入出力に戻す働きがある。
 * @note        内蔵ペリフェラルの出力モードとして設定されている端子は出力に設定できない。
 **********************************************************************/
void pinMode(int pin, int mode);

/*********************************************************************//**
 * @brief		指定したピンの値を読み取る
 * @param[in]	pin ピン番号(@ref grsakura_pin で宣言したピン番号)
 *
 * @return		HIGHまたはLOW
 **********************************************************************/
int digitalRead(int pin);

/*********************************************************************//**
 * @brief		ピンに入力されるパルスを検出する。
 * @details     たとえば、パルスの種類(value)をHIGHに指定した場合、pulseIn関数は入力がHIGHに変わると同時に時間の計測を始め、<BR>
 * 				またLOWに戻ったら、そこまでの時間(つまりパルスの長さ)をマイクロ秒単位で返す。<BR>
 * 				あまりに長いパルスに対してはエラーとなる可能性がある。
 * @param[in]	pin ピン番号(tkdn-gpioで宣言したピン番号)
 * @param[in]	val 測定するパルスの種類。HIGHまたはLOW
 * @param[in]	timeout タイムアウトまでの時間(単位・マイクロ秒) デフォルトは1秒
 *
 * @return		パルスの長さ(マイクロ秒)。パルスがスタートする前にタイムアウトとなった場合は0 (unsigned long)
 **********************************************************************/
unsigned long pulseIn(int pin, int val, unsigned long timeout = 1000000);


#ifdef __cplusplus
	}
#endif

#endif // __H_RXDUINO_DIGITALIO

