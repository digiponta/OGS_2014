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

#ifndef __H_TKDN_INTERRUPT
#define __H_TKDN_INTERRUPT
/**************************************************************************//**
 * @file    tkdn_interrupt.h
 * @brief   RXマイコンの割り込み機能を使うためのルーチン
 ******************************************************************************/

#include "tkdn_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

//! @brief 割り込み処理ルーチンの型
typedef void (*FUNC_INTERRPUT_HANDLER) (void);

extern FUNC_INTERRPUT_HANDLER USBI0_handler;
extern FUNC_INTERRPUT_HANDLER USBI1_handler;

//! @brief 割り込み発生条件
typedef enum 
{
	INTTRIG_LOW      = 0, //!< @brief Lowレベル割り込みを意味する。数値は0。
	INTTRIG_CHANGE   = 1, //!< @brief 信号が変化したことを意味する。数値は1。
	INTTRIG_FALLING  = 2, //!< @brief 立ち下がりエッジを意味する。数値は2。@note 2012/7/13以降、2と3が入れ替わった
	INTTRIG_RISING   = 3, //!< @brief 立ち上がりエッジを意味する。数値は3。@note 2012/7/13以降、2と3が入れ替わった
} InterruptTrigger;

/*********************************************************************//**
 * @brief     CPUのPSWレジスタを変更してグローバルに割り込みを許可する
 * @return    なし
 **********************************************************************/
void enable_interrupt(void);

/*********************************************************************//**
 * @brief     CPUのPSWレジスタを変更してグローバルに割り込みを禁止する
 * @return    なし
 * @warning   割り込みを禁止するとUSBやSCIたタイマーが使えなくなって、ハングアップする危険がある。<BR>
 *            基本的に使わないこと。どうしても使う場合は細心の注意が必要。
 **********************************************************************/
void disable_interrupt(void);

/*********************************************************************//**
 * @brief     ピン割り込みの割り当て
 * @param     interrupt 割り込み番号 (0～7) 
 *             - 0 : P10端子 (IRQ0) ※TQFP100ピンにはない
 *             - 1 : P11端子 (IRQ1) ※TQFP100ピンにはない
 *             - 2 : P12端子 (IRQ2)
 *             - 3 : P13端子 (IRQ3)
 *             - 4 : P14端子 (IRQ4) ※USBの制御信号と共有
 *             - 5 : P15端子 (IRQ5) ※メモリカードの挿入検出と共有の可能性
 *             - 6 : P16端子 (IRQ6) ※USBの制御信号と共有
 *             - 7 : P17端子 (IRQ7)
 * @param     func ユーザが定義する割り込み処理関数
 * @param     mode 割り込み発生条件
 * @return    なし
 * @note      実際に使えるのはIRQ2とIRQ3とIRQ7
 * @todo      IRQ8以降も使えるようにしたい。IRQ0～IRQ7に関してはもう1つのピンも使えるようにしたい。
 **********************************************************************/
void attach_interrupt(unsigned char interrupt, FUNC_INTERRPUT_HANDLER func, InterruptTrigger mode);


/*********************************************************************//**
 * @brief     ピン割り込みの解除
 * @param     interrupt attach_interrupt() 関数で割り当てたIRQ番号
 * @return    なし
 **********************************************************************/
void detach_interrupt(unsigned char interrupt);

#ifdef __cplusplus
}
#endif

#endif
