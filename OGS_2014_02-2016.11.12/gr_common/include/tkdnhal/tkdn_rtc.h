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

#ifndef __H_TKDN_RTC
#define __H_TKDN_RTC
/**************************************************************************//**
 * @file    tkdn_rtc.h
 * @brief   RXマイコンの内蔵時計機能を使うためのルーチン
 * @details このライブラリは時刻の値がBCDだったりと使いやすくないので RTC クラスを使うとよい。<BR>
 *          RTCクラスはこのルーチンをC++でカプセル化して使いやすくしたものである。
 ******************************************************************************/

#include "tkdn_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

//■■■■■■■■■■■■■■■■■■■■■■■■■
//  ユーザがカスタマイズする場所はありません
//■■■■■■■■■■■■■■■■■■■■■■■■■

/**************************************************************************//**
 * @brief   RX62N/63Nの内蔵RTCの時刻を扱うための構造体
 * @note    RX63NでもRX62N***という名前
 * @warning 各フィールドはBCDである。
 ******************************************************************************/
typedef struct RX62N_RTC_TIME {
	unsigned short year;    //!< @brief 年。RX63Nでは西暦とみなして下2桁だけ指定する。
	unsigned char  mon;     //!< @brief 月。BCDで表す。0x01～0x12
	unsigned char  day;     //!< @brief 日。BCDで表す。0x01～0x31
	unsigned char  weekday; //!< @brief 曜日。特に使用されていない。
	unsigned char  hour;    //!< @brief 時。BCDで表す。0x00～0x23 24時間制
	unsigned char  min;     //!< @brief 分。BCDで表す。0x00～0x59
	unsigned char  second;  //!< @brief 秒。BCDで表す。0x00～0x59
} RX62N_RTC_TIME;

/**************************************************************************//**
 * @brief   RTCのハードウェアを初期化する
 * @return  戻り値は以下のとおり
 *          - 0 : RTCの起動に失敗した (水晶が発振しない)
 *          - 1 : RTCの起動に成功
 *          - 2 : RTCはすでに起動していた (エラーではない)
 * @warning RX63Nではサブ水晶を起動するため3秒ほどかかる。一瞬、ハングアップしたように見えるので驚くかもしれない。
 ******************************************************************************/
int rtc_init(void);

/**************************************************************************//**
 * @brief     RTCに時刻を設定する
 * @param[in] time 設定したい時刻が格納された構造体
 * @note      rtc_init() を呼び出して初期化していなければ、この関数の中で自動的に呼び出される
 * @return    成功すると1を返す。失敗すると0を返す。
 ******************************************************************************/
int rtc_set_time(RX62N_RTC_TIME *time);

/**************************************************************************//**
 * @brief     RTCの時刻を取得する
 * @param[in] time 設定したい時刻を格納する構造体。構造体の実体は呼び出し元で用意しておくこと。
 * @note      RX62Nではrtc_init() を呼び出して初期化していなければ、この関数の中で自動的に呼び出される<BR>
 *            RX63Nでは初期化していなければ、エラーとなる。
 * @return    成功すると1を返す。失敗すると0を返す。
 ******************************************************************************/
int rtc_get_time(RX62N_RTC_TIME *time);

#ifdef __cplusplus
 }
#endif

#endif
