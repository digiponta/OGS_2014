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

#ifndef	__H_RXDUINO_ANALOGIO
#define	__H_RXDUINO_ANALOGIO
/**************************************************************************//**
 * @file    analogio.h
 * @brief   内蔵ADC、内蔵DAC、PWMに関するライブラリ
 ******************************************************************************/
#include "rxduino.h"

#ifdef __cplusplus
	extern "C" {
#endif

//------------------------------------------------------------------
// アナログ入出力
//------------------------------------------------------------------

// 
/*********************************************************************//**
 * @brief		内蔵ADCからアナログ値を読み込む
 * @param[in]	analog_portnum アナログ値を読み込むピン番号。<BR>
 *              ピン番号は、0～7のチャネル番号でも、
 *              14～21のピン番号でもどちらでも指定できる。<BR>
 *              0～7を指定した場合は、AN0～AN7の端子の値が読まれる。<BR>
 *              14～21を指定した場合は、引数から14を引いて、AN0～AN7として解釈される。<BR>
 *              それ以外の値を指定した場合は常に0を返す。
 * @return		読み込んだアナログ値を、analogReferenceの型式に従って変換して返す。<BR>
 * @note        Vrefは常に3.3Vである。
 * @note        RX62Nでは内蔵10bit ADCが使われる。RX63Nでは12bit ADCが使われる。<BR>
 *              analogReference関数も参照すること
 **********************************************************************/
int analogRead(int analog_portnum);

/*********************************************************************//**
 * @brief		指定したピンからアナログ値(PWM波)を出力する。
 * @details     LEDの明るさをじわじわ変えたいときやDCモータの回転スピードを調整したいときに使える。
 * @details     デフォルトのPWM周波数は490Hz。analogWriteFrequency()で変更できる。
 * @details     関数内部で使用するピンの登録がされるのでpinModeなどの初期化は必要ない。
 * @param[in]	analog_portnum 任意のピン番号。
 * @param[in]	val8bit 出力するPWMのデューティ(0～255)
 * @return		なし
 * @note        先着15個のポートまで使用可能。Servoやtone関数とは別のタイマを使っているので、同時使用ができる。
 * @note        このPWMはソフトウェアでエミュレートしているので、各チャネルの出力タイミングには若干の差が存在する。
 * @include     analogwrite1.cpp
 **********************************************************************/
void analogWrite(int analog_portnum,int val8bit);

// DACを使って10bitアナログ値の出力
// dac_portnumは0か1を指定すること
/*********************************************************************//**
 * @brief		内蔵DACを使ってアナログ値を出力する。
 * @param[in]	dac_portnum アナログ値を出力するピン番号
 * 				0か1を出力する。RX62N/63Nの100ピンではチャネル1のみ使用できる。
 * @param[in]	val10bit 変換値(10bit整数値)
 * @note        PWMではなく、DACによる出力です。
 * @return		なし
 **********************************************************************/
void analogWriteDAC(int dac_portnum,int val10bit);

/*********************************************************************//**
 * @brief		アナログ入力で使われる基準電圧(Vref)と変換形式を指定する。
 * @param[in]	mode 次のうち一つを指定します
 *				- DEFAULT  (0): 電源電圧(3.3V)
 *				- INTERNAL (1): 内蔵基準電圧(1.1V)
 *				- EXTERNAL (2): AREFピンに供給される電圧を基準電圧とする
 *				- RAW12BIT (3): 計測値を加工せずに12bitで出力する
 *
 * @note        実際にRXマイコンのVrefを変更しているわけではない。
 *              変換した値を以下の式でArduinoのADCをエミュレートしているにすぎない。
 *              - DEFAULT   val * (1024. / 4096. * 3.3 / 5)
 *              - INTERNAL  val * (1024. / 4096. * 3.3 / 1.1) ただし1023以上になるならば1023
 *              - EXTERNAL  val >> 2
 *              - RAW12BIT  val
 * @todo        RX62Nは12bit非対応。なんとかする。
 * @return		なし
 **********************************************************************/
void analogReference(int mode);


/*********************************************************************//**
 * @brief		アナログ出力(PWM)の周期を設定する.
 * @param[in]	Hz 設定する周波数.単位はHz.引数に指定できるのは12～184999 [Hz]
 *
 * @return		なし
 * @warning		すべての範囲で動作するかは未検証。60kHzくらいまでが限度。PWMのチャネル数が増えると当然ながら最大周波数は下がる。
 * @include     analogwrite1.cpp
 **********************************************************************/
void analogWriteFrequency(int Hz);

#ifdef __cplusplus
	}
#endif

#endif // __H_RXDUINO_ANALOGIO

