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

#ifndef __H_TKDN_HAL
#define __H_TKDN_HAL

/**************************************************************************//**
 * @file    tkdn_hal.h
 * @brief   特電HALのヘッダファイル
 ******************************************************************************/

// オブジェクトコードを節約したい場合は以下のマクロを有効にしてライブラリを再ビルドすること
// ※ 下記の2つをコメントアウトすると約6kB節約できる
//#define DISABLE_USBVCOM // USB仮想COMポートを使わない場合
//#define DISABLE_ETHER   // イーサネットコントローラを使わない場合


// これ以降、ユーザがカスタマイズする場所はない

#define TKDN_HAL 
#define TKDN_HAL_VERSION 0x01080000 // Version 1.08
#define TKDN_HAL_TIME    1380466335 // 2013/09/29 23:52:15 

#ifdef __GNUC__
  #define __INTTERUPT_FUNC __attribute__ ((interrupt))
#endif
#ifdef __RENESAS
  #define __INTTERUPT_FUNC
#endif

#ifndef TRUE
 #ifdef __cplsuplus
 #define TRUE true
 #else
 #define TRUE 1
 #endif
#endif

#ifndef FALSE
 #ifdef __cplsuplus
 #define FALSE false
 #else
 #define FALSE 0
 #endif
#endif

#ifndef NULL
 #ifdef __cplsuplus
 #define NULL __null
 #else
 #define NULL ((void*)0)
 #endif
#endif

////////////////////////////////////////////////////////////////
// 以下の番号は特殊電子回路㈱によって割り当てられる
// 勝手に変更してはならない
#define RX62N                0x00000062
#define RX63N                0x00000063
#define BOARD_ULT62N0_SDRAM  0x56280001 //!< @brief ボードIDの定義。究極RX62Nボード初期版 SDRAM使用
#define BOARD_ULT62N0_MMC    0x56280002 //!< @brief ボードIDの定義。究極RX62Nボード初期版 SDMMCカード使用
#define BOARD_ULT62N         0x56280003 //!< @brief ボードIDの定義。究極RX62NボードRevA版
#define BOARD_RXMEGA         0x56280004 //!< @brief ボードIDの定義。RX-MEGA
#define BOARD_RAXINO         0x56280005 //!< @brief ボードIDの定義。RAXINO
#define BOARD_FRKRX62N       0x56270006 //!< @brief ボードIDの定義。FRK-RX62N
#define BOARD_YRDKRX62N      0x56280007 //!< @brief ボードIDの定義。YRDKRX62N
#define BOARD_GRSAKURA       0x56310531 //!< @brief ボードIDの定義。GR-SAKURA
#define BOARD_GRUME          0x56310541 //!< @brief ボードIDの定義。GR-UME
#define BOARD_NP1055         0x56310551 //!< @brief ボードIDの定義。 future project
#define BOARD_YRDKRX63N      0x56300008 //!< @brief ボードIDの定義。YRDKRX63N
////////////////////////////////////////////////////////////////

#define _PINDEF(port,bit) ((port) << 8 | (bit))

#define _PORT0 0
#define _PORT1 1
#define _PORT2 2
#define _PORT3 3
#define _PORT4 4
#define _PORT5 5
#define _PORT6 6
#define _PORT7 7
#define _PORT8 8
#define _PORT9 9
#define _PORTA 10
#define _PORTB 11
#define _PORTC 12
#define _PORTD 13
#define _PORTE 14
#define _PORTF 15
#define _PORTG 16
#define _PORTJ 18

#define _BIT0 (1 << 0)
#define _BIT1 (1 << 1)
#define _BIT2 (1 << 2)
#define _BIT3 (1 << 3)
#define _BIT4 (1 << 4)
#define _BIT5 (1 << 5)
#define _BIT6 (1 << 6)
#define _BIT7 (1 << 7)

#include "boarddef.h" // ボード番号定義を読み込み
#include "tkdn_sci.h"
#include "tkdn_spi.h"
#include "tkdn_i2c.h"
#include "tkdn_dac.h"
#include "tkdn_adc.h"
#include "tkdn_gpio.h"
#include "tkdn_rtc.h"
#include "tkdn_timer.h"
#include "tkdn_ether.h"
#include "tkdn_version.h"

#ifdef __cplusplus
	extern "C" {
#endif

#define REBOOT_USERAPP  0
#define REBOOT_FIRMWARE 1

/*********************************************************************//**
 * @brief     ソフトリセットを行い、システムをリブートする
 * @param     mode リブート後の状態
 *             - REBOOT_USERAPP : リセット後にユーザアプリを起動する
 *             - REBOOT_FIRMWARE : リセット後にファームウェアを起動する
 *            上記以外の値を指定した場合の動作は保証されない
 * @return    なし
 * @note      ファームウェア起動は、がじぇるねプロジェクトのボードが対象
 **********************************************************************/
void system_reboot(int mode); 

#ifdef __cplusplus
	}
#endif

#endif // __H_TKDN_HAL

