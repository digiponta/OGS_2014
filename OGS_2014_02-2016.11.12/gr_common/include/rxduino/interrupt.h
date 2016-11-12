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

#ifndef	__H_RXDUINO_INTERRUPT
#define	__H_RXDUINO_INTERRUPT
/**************************************************************************//**
 * @file    interrupt.h
 * @brief   割り込みに関するライブラリ
 ******************************************************************************/
#include "rxduino.h"

#ifdef __cplusplus
	extern "C" {
#endif

/*********************************************************************//**
 * @brief		グローバルな割り込み許可
 * @details		noInterrupts関数によって停止した割り込みを有効にする。<BR>
 * @param[in]	なし
 *
 * @return		なし
 **********************************************************************/
void interrupts(void);

/*********************************************************************//**
 * @brief		割り込みをグローバルに禁止する。
 * @details     interrupts関数で再度有効にできる。<BR>
 *              割り込みはデフォルトで有効であり、バックグラウンドで重要なタスクを処理するので、原則的に禁止してはならない。
 * @note		クリティカルなセクションで割り込みを禁止することでタイミングの乱れなどをなくすためなどに使う。
 * @warning     RXduinoの多くの機能は割り込みを禁止すると動作しない。シリアル通信やUSB通信ができなくなる。<BR>
 *              システムのクラッシュを引き起こすので、できるだけ使わないこと。
 * @param[in]	なし
 *
 * @return		なし
 **********************************************************************/
void noInterrupts();

/*********************************************************************//**
 * @brief		外部割り込みが発生したときに実行する関数を指定する。
 * @details		RXduino(RaXino,GRSAKURA)は割り込み0(P10)と割り込み1(P11),割り込み2(P12),<BR>
 * 				割り込み3(P13),割り込み4(P14),割り込み5(P15),割り込み6(P16),割り込み7(P17)<BR>
 * 				が使用可能です.呼び出せる関数は引数と戻り値が不要なものだけです.<BR>
 *
 * @param[in]	interrupt 割り込み番号(0 - 7)
 * - 0 : ポートP10 (IRQ0) ※TQFP100ピンにはない
 * - 1 : ポートP11 (IRQ1) ※TQFP100ピンにはない
 * - 2 : ポートP12 (IRQ2)
 * - 3 : ポートP13 (IRQ3)
 * - 4 : ポートP14 (IRQ4)
 * - 5 : ポートP15 (IRQ5)
 * - 6 : ポートP16 (IRQ6)
 * - 7 : ポートP17 (IRQ7)
 * @param[in]	func 割り込み発生時に呼び出す関数
 * @param[in]	mode 割り込みを発生させるトリガ条件
 * 				- LOW     (0): ピンがLOWのとき発生
 * 				- CHANGE  (1): ピンの状態が変化したときに発生
 * 				- FALLING (2): ピンの状態がHIGHからLOWに変わったときに発生
 * 				- RISING  (3): ピンの状態がLOWからHIGHに変わったときに発生
 *
 * @return		なし
 **********************************************************************/
void attachInterrupt(unsigned char interrupt, void (*func)(void), int mode);

/*********************************************************************//**
 * @brief		指定した割り込みを停止する.
 * @param[in]	interrupt 割り込み番号(0 - 7)
 * - 0 ポートP10 (IRQ0) ※TQFP100ピンにはない
 * - 1 ポートP11 (IRQ1) ※TQFP100ピンにはない
 * - 2 ポートP12 (IRQ2)
 * - 3 ポートP13 (IRQ3)
 * - 4 ポートP14 (IRQ4)
 * - 5 ポートP15 (IRQ5)
 * - 6 ポートP16 (IRQ6)
 * - 7 ポートP17 (IRQ7)
 * @return		なし
 **********************************************************************/
void detachInterrupt(unsigned char interrupt);

#ifdef __cplusplus
	}
#endif

#endif // __H_RXDUINO_INTERRUPT

