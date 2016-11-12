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

#ifndef __H_TKDN_USB
#define __H_TKDN_USB
/**************************************************************************//**
 * @file    tkdn_usb.h
 * @brief   RXマイコンの内蔵USBをUSBファンクションとして使い、仮想COMポートを実現する
 ******************************************************************************/

#include "tkdn_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

//■■■■■■■■■■■■■■■■■■■■■■■■■
//  ユーザがカスタマイズする場所はありません
//■■■■■■■■■■■■■■■■■■■■■■■■■

//==================================================
// USBのベースとなる関数
//==================================================

/*********************************************************************//**
 * @brief     USB仮想COMポートを初期化する
 * @return    成功すれば0を返す。失敗したら負の数を返す。
 **********************************************************************/
int           TKUSB_Init(void);

/*********************************************************************//**
 * @brief     USB仮想COMポートがホストPCに接続されているかどうかを調べる
 * @return    接続されていれば1を返す。そうでなければ0を返す。
 **********************************************************************/
int           TKUSB_IsConnected(void);

/*********************************************************************//**
 * @brief     USB仮想COMポートに1バイト送信する
 * @param     data 送信データ (0x00～0xff)
 * @return    成功したら1を返す。失敗(バッファフル)したら-1を返す。
 * @note      この関数は送信バッファに溜めるだけで、即座に送信するとは限らない。<BR>
 *            実際の送信は送信バッファエンプティ割り込みを使って行われるので、そのタイミングは調節できない。
 **********************************************************************/
int           TKUSB_SendByte(unsigned char data);

/*********************************************************************//**
 * @brief     送信バッファに溜まっているデータ数を返す
 * @return    送信バッファに格納されているデータ数(バイト単位)
 * @note      送信バッファは256バイトある
 **********************************************************************/
int           TKUSB_SendDataCount(void);

/*********************************************************************//**
 * @brief     USB仮想COMポートの受信バッファから1バイト取り出す
 * @return    受信したデータ (0x00～0xff)
 * @note      受信バッファにデータがないときには即座に0を返す。
 *            受信データの有無を調べるために、あらかじめ TKUSB_RecvDataCount() を呼ぶこと。
 * @note      実際の受信処理はUSB割り込みで行われる。この関数は受信バッファから取り出すにすぎない。
 **********************************************************************/
unsigned char TKUSB_RecvByte(void);

/*********************************************************************//**
 * @brief     USB仮想COMポートの受信バッファに格納されている先頭の1文字を覗き見る
 * @return    受信バッファの先頭のデータ (0x00～0xff)
 * @note      受信バッファにデータがないときには0を返す。
 **********************************************************************/
unsigned char TKUSB_PeekByte(void);

/*********************************************************************//**
 * @brief     受信バッファに溜まっているデータ数を返す
 * @return    受信バッファに格納されているデータ数(バイト単位)
 * @note      受信バッファは256バイトある
 **********************************************************************/
int           TKUSB_RecvDataCount(void);

#ifdef __cplusplus
 }
#endif

#endif /*__H_TKDN_USB*/