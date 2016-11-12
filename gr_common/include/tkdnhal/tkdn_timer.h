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

#ifndef __H_TKDN_TIMER
#define __H_TKDN_TIMER
/**************************************************************************//**
 * @file    tkdn_timer.h
 * @brief   RXマイコンの内蔵タイマーを利用して、経過時間を計測したり、waitを行うためのライブラリ
 * @details このライブラリはCMT0を使用する。
 * @todo    CMTのカウントクロックは、
 *          出力したい矩形波の周波数が50Hz、200Hz、800Hzで切り替わるので、
 *          その近辺で音階の調整が連続的に行えるかどうかは検証しなければならない。
 ******************************************************************************/

#include "tkdn_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

//■■■■■■■■■■■■■■■■■■■■■■■■■
//  ユーザがカスタマイズする場所はありません
//■■■■■■■■■■■■■■■■■■■■■■■■■

//! @brief ユーザが登録するタイマ割り込み関数の型。ユーザの関数はvoid func()のように引数と戻り値ののない関数。
typedef void (* USER_TIMER_FUNC)(void);

/*********************************************************************//**
 * @brief     タイマーを初期化する
 * @details   ユーザが登録するタイマ割り込み関数を解除し、経過時間が返す値を0にリセットする。
 * @return    なし
 * @warning   この関数を使うと、 timer_get_ms() や、 millis() micros() に影響がある。
 **********************************************************************/
void timer_init(void);

/*********************************************************************//**
 * @brief     指定された時間、待つ
 * @param     ms 待ち時間。ミリ秒単位
 * @return    なし
 * @note      時間が正確でないというバグはV1.08で修正された
 **********************************************************************/
void timer_wait_ms(unsigned long ms);

/*********************************************************************//**
 * @brief     指定された時間、待つ
 * @param     us 待ち時間。マイクロ秒単位
 * @return    なし
 * @warning   この関数はマイクロ秒タイマが32bitの値をオーバーフローするであろう約1時間経過後にクラッシュする可能性がある。
 * @note      時間が正確でないというバグはV1.08で修正された
 **********************************************************************/
void timer_wait_us(unsigned long us);

/*********************************************************************//**
 * @brief     システムが起動してからの経過時間をミリ秒単位で返す
 * @return    経過時間(マイクロ秒)
 * @warning   返す値は、ミリ秒なので約49日でオーバーフローする
 **********************************************************************/
unsigned long timer_get_ms(void);

/*********************************************************************//**
 * @brief     システムが起動してからの経過時間をマイクロ秒単位で返す
 * @return    経過時間(マイクロ秒) 1マイクロ秒の精度がある
 * @warning   返す値は、（経過時間(ミリ秒部分)*1000 + 経過時間(マイクロ秒部分)）なので約1.2時間でオーバーフローする
 * @note      時間が正確でないというバグはV1.08で修正された
 **********************************************************************/
unsigned long timer_get_us(void);

/*********************************************************************//**
 * @brief     タイマー割り込みで呼び出されるユーザ関数を登録する
 * @details   登録されたユーザ関数は1msごとに呼び出される
 * @param     func 呼び出したいユーザ処理関数
 * @return    常に1を返す
 **********************************************************************/
unsigned long timer_regist_userfunc(USER_TIMER_FUNC func);

// 以下の関数はシステムライブラリが使用する。ユーザは実行しないこと
TKDN_HAL
unsigned long timer_regist_disktimer(USER_TIMER_FUNC func);

TKDN_HAL
unsigned long timer_regist_ethertimer(USER_TIMER_FUNC func);

#ifdef __cplusplus
 }
#endif

#endif // __H_TKDN_TIMER
