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

#ifndef	__H_RXDUINO_TONE
#define	__H_RXDUINO_TONE
/**************************************************************************//**
 * @file    tone.h
 * @brief   矩形波を発生させ、圧電ブザーから音を鳴らす
 ******************************************************************************/
#include "rxduino.h"

#ifdef __cplusplus
	extern "C" {
#endif

//------------------------------------------------------------------
// トーン出力
//------------------------------------------------------------------

/*********************************************************************//**
 * @brief		矩形波を生成する
 * @param[in]	pin digitalWrite関数で指定するピン番号と同じです
 * @param[in]	frequency 出力したい周波数[Hz]
 * @param[in]	duration_ms 持続時間を指定する[ms]。0を指定すると鳴り続ける。省略すると0になる。
 * @note        analogWrite関数(PWM)とは別のタイマを使っているので、同時使用ができる。
 * @note        duration_msに0を指定すると、即座に制御を返す。<BR>
 *              duration_msに0以外を指定すると、終わるまで制御を返さない。<BR>
 * @return		なし
 **********************************************************************/
void tone(int pin, int frequency, int duration_ms = 0);

/*********************************************************************//**
 * @brief		矩形波の出力を止める
 * @param[in]	pin 出力を止めたいピン番号であるが、実際には効力を持たない
 * @return		なし
 **********************************************************************/
void noTone(int pin);

#ifdef __cplusplus
	}
#endif

#endif // __H_RXDUINO_TONE

