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

#ifndef RXRTC_H_
#define RXRTC_H_
/**************************************************************************//**
 * @file    rtc.h
 * @brief   内蔵RTCを使いやすくするためのライブラリ
 * @todo    RTCのアラーム機能とか、曜日の自動計算とかができたら面白いだろうな
 ******************************************************************************/

#ifdef __cplusplus
	extern "C" {
#endif

#include "rxduino.h"

#define RTC_LIBRARY_VERSION 0x01080000 // Version 1.08
#define RTC_LIBRARY_TIME    1380466335 // 2013/09/29 23:52:15 

/**************************************************************************//**
 * @class   RXRTC
 * @brief   内蔵RTCクラス
 * @note    このクラスにはスタティックなメンバ関数しかない。<BR>
 *          つまり、オブジェクトを作成する必要はない。
 * @note    RTCというクラス名だとiodefine中のRTCと干渉するので、V1.06でRXRTCに変更した
 ******************************************************************************/

class RXRTC {
public:
/*********************************************************************//**
 * @brief		このクラスのバージョンを取得する
 * @param[in]	vi 値をセットしたいバージョン情報構造体へのポインタ
 * @return		バージョン番号
 **********************************************************************/
	static unsigned long getVersion(version_info *vi);
	
/*********************************************************************//**
 * @brief		32.768KHz水晶を発振させて、RTCを起動する
 * @param       なし
 * @warning     この関数は、発振の起動待ちのために、3秒ほどブロッキングする。
 *              まるでシステムがハングアップしたように見えるので驚くかもしれない
 * @return		- 0 : 起動失敗
 *              - 1 : 起動成功
 *              - 2 : RTCは既に起動していた(成功)
 **********************************************************************/
	static int begin();

/*********************************************************************//**
 * @brief		RTCの時計をセットする
 * @param       year 年 RX63Nでは0-99。RX62Nでは0-9999。
 * @param       mon 月 1-12
 * @param       day 日 0-31 
 * @param       hour 時 0-23
 * @param       min 分 0-59
 * @param       sec 秒 0-59
 * @note        この関数の前にbeginを呼ばなくても、内部でbeginを呼び出すので心配ない
 * @note        内蔵RTCはBCDで値を扱うが、このライブラリはint→BCDへ変換するので気にしなくてよい
 * @note        24時間制である
 * @warning     RX63Nでは西暦20xx年代を想定しているため、年は2桁しか意味を持たない
 * @return		関数が成功したかどうか
 *				- true : 成功
 *				- false : 失敗
 **********************************************************************/
	static bool setDateTime(int year,int mon,int day,int hour,int min,int sec);

/*********************************************************************//**
 * @brief		RTCの時計を取得する
 * @param[out]  year 年 RX63Nでは2000-2099。RX62Nでは0-9999。
 * @param[out]  mon 月
 * @param[out]  day 日
 * @param[out]  hour 時
 * @param[out]  min 分
 * @param[out]  sec 秒
 * @note        この関数の前にbeginを呼ばなくても、内部でbeginを呼び出すので心配ない
 * @note        内蔵RTCはBCDで値を扱うが、このライブラリはBCD→intへ変換するので気にしなくてよい
 * @note        24時間制である
 * @warning     RX63Nでは西暦20xx年代を想定しているため年は2桁しか意味を持たない。内部で2000を足している。
 * @return		関数が成功したかどうか
 *				- true : 成功
 *				- false : 失敗
 **********************************************************************/
	static bool getDateTime(int &year,int &mon,int &day,int &hour,int &min,int &sec);
};

#ifdef __cplusplus
	}
#endif

#endif /* RXRTC_H_ */
