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

#ifndef __H_TKDN_DAC
#define __H_TKDN_DAC
/**************************************************************************//**
 * @file    tkdn_dac.h
 * @brief   内蔵DACを使用するためのルーチン
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
 * @brief		内蔵DACを初期化して使えるようにする
 * @details		RX63Nでは、PORT0.3とPORT0.5のポートをアナログモードに変更する<BR>
 *              RX62Nでは、ポートのモード設定は変更されない
 * @note		最初にdac_sampleを呼び出したときに内部で自動的に呼び出されるので、この関数は明示的に呼び出さなくてもよい。
 **********************************************************************/
void dac_init(void);

/*********************************************************************//**
 * @brief		内蔵DACを終了して、モジュールスタンバイ状態に戻す
 * @details		ポートのモード設定は変更されない
 **********************************************************************/
void dac_terminate(void);

/*********************************************************************//**
 * @brief		DACからアナログ値を出力する
 * @details		ポートのモード設定は変更されない
 * @note        valの値は
 * @param       dac_portnum DACチャネル 0または1。
 *              - 0 : DA0(PORT0.3)から出力(100pin版には存在しない)
 *              - 1 : DA1(PORT0.5)から出力
 * @param       val10bit 出力したい値、または-1
 *              - 0～1023 : 0V～3.3Vが出力される
 *              - -1 : チャネルのDA変換を禁止(ポートになる)
 * @todo        変換時間は未測定。計測してここに記すべき
 **********************************************************************/
void dac_output(int dac_portnum,int val10bit);

#ifdef __cplusplus
 }
#endif

#endif // __H_TKDN_TIMER
