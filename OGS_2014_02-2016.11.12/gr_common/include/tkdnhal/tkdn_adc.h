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

#ifndef __H_TKDN_ADC
#define __H_TKDN_ADC
/**************************************************************************//**
 * @file    tkdn_adc.h
 * @brief   内蔵ADCを使用するためのルーチン
 * @details このライブラリをC++で使いやすくした関数が analogio.h で定義されています。
 * @todo	現在はRX63Nでは12bit ADC、RX62Nでは10bit ADCが使われている。RX62Nでも12bitADCが使われるようにしたい
 ******************************************************************************/

#include "tkdn_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

//■■■■■■■■■■■■■■■■■■■■■■■■■
//  ユーザがカスタマイズする場所はありません
//■■■■■■■■■■■■■■■■■■■■■■■■■

/*********************************************************************//**
 * @brief		ADCを初期化して使えるようにする
 * @param		なし
 * @return		なし
 * @details		内蔵ADCモジュールを有効にしサンプリングクロックを48MHzにセットする。<BR>
 *              RX62Nでは10bitの内蔵ADCを使う。<BR>
 *              RX63Nでは12bitの内蔵ADCを使い、CH0～CH7をスキャン対象にする。また、内蔵温度センサも有効にする。<BR>
 *              この関数ではポートのモードレジスタは変更されない。
 * @note		この関数は明示的に呼び出さなくてもよい。<BR>最初にadc_sampleを呼び出したときに内部で自動的に呼び出される。
 **********************************************************************/
void adc_init(void);

/*********************************************************************//**
 * @brief		ADCを終了する
 * @details		ADCモジュールをストップ状態する。
 *              ポートのモードレジスタは変更しない
 * @param		なし
 * @return		なし
 **********************************************************************/
void adc_terminate(void);

/*********************************************************************//**
 * @brief		ADCからアナログ値を入力する
 * @details		指定されたチャネルのAD変換を行う。AD変換は1chのみ行われる。
 * @param		analog_ch_num 変換したアナログチャネル番号(0～7,8～20,100,101)
 *              - 0～7  : ADCチャネル0～7
 *              - 8～20 : ADCチャネル8～20 但し未実装
 *              - 100   : 内蔵温度センサ(RX63Nのみ)
 *              - 101   : 内蔵基準電源(RX63Nのみ)
 * @return		10bit(RX62N)または12bit(RX63N)の変換値。LSB詰め。
 * @note		RX63Nの場合、PORT4.nをGPIOモード、入力、アナログモード、プルダウン抵抗は無効になる。
 * @todo        変換時間は未測定。計測してここに記すべき
 **********************************************************************/
unsigned short adc_sample(int analog_ch_num);

#ifdef __cplusplus
 }
#endif

#endif // __H_TKDN_ADC
