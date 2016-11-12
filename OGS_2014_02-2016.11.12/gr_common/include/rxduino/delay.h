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

#ifndef __H_RXDUINO_DELAY
#define __H_RXDUINO_DELAY
/**************************************************************************//**
 * @file    delay.h
 * @brief   タイマーと遅延に関するライブラリ
 ******************************************************************************/
#include "rxduino.h"

#ifdef __cplusplus
	extern "C" {
#endif

//------------------------------------------------------------------
// 時間関数
//------------------------------------------------------------------

/*********************************************************************//**
 * @brief		起動してからの時間をミリ秒単位で返す
 * @param[in]	なし
 * @return		起動してからの時間
 * @include     example1.cpp
 **********************************************************************/
unsigned long millis();

/*********************************************************************//**
 * @brief		起動してからの時間をマイクロ秒単位で返す
 * @param[in]	なし
 * @return		起動してからの時間(unsigned long型)
 **********************************************************************/
unsigned long micros();

/*********************************************************************//**
 * @brief		プログラムを指定した時間だけ一時停止します。単位はミリ秒
 * @param[in]	ms 一時停止する時間。単位はミリ秒
 * @return		なし
 **********************************************************************/
void delay(unsigned long ms);

/*********************************************************************//**
 * @brief		プログラムを指定した時間だけ一時停止します。単位はマイクロ秒
 * @param[in]	us 一時停止する時間。単位はマイクロ秒
 * @return		なし
 * @warning		この関数はシステムをハングアップさせるかもしれない。(たぶん大丈夫だが)
 **********************************************************************/
RXDUINO_API
void delayMicroseconds(unsigned long us);

#ifdef __cplusplus
	}
#endif

#endif // __H_RXDUINO_DELAY


