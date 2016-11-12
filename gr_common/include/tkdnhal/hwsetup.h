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

/**************************************************************************//**
 * @file    hwsetup.h
 * @brief   ハードウェアの初期化に関するプログラム
 ******************************************************************************/

#include <stdio.h>

//#include "vect.h"
#ifdef __GNUC__
  #ifdef CPU_IS_RX62N
    #include "iodefine_gcc62n.h"
  #endif
  #ifdef CPU_IS_RX63N
    #include "iodefine_gcc63n.h"
  #endif
#endif
#ifdef __RENESAS__
  #include "iodefine.h"
#endif

//const int PCLK       = 48000000;
//const int TIMER_FREQ = 125;
extern int tim_1ms;

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************//**
 * @brief		内蔵ペリフェラルレジスタをセットして、main()を呼ぶ準備をする
 * @details		この関数では以下のことを行う
 *				- クロックの設定(メインクロックはPLL 192MHz,ICLK 96MHz,BCLK 48MHz,PCLK 48MHz)
 *				- CMT0を1ms周期に設定してタイマー割り込みを仕掛ける
 *				- 各種のプロテクションレジスタ解除
 *				- ファームウェアが設定してしまった各種内蔵レジスタの値を戻す
 *				- SDRAMを持っているボードではSDRAMの使用開始準備
 * @param		なし
 * @return		なし
 * @warning		この関数はユーザアプリから呼び出してはいけない。<BR>
 * 				この説明はtkdn_hwsetupの処理内容を記すためのものである。
 * @note		最初hwsetupという名前にしていたが、あるユーザが同じ名前の関数を作ってしまい、<BR>
 * 				動かなくなったことがある。そのため、名前の先頭にtkdn_を付けた。
 **********************************************************************/
void tkdn_hwsetup(void);

#ifdef __cplusplus
}
#endif
