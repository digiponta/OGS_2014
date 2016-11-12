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

#ifndef	__H_RXDUINO_SHIFTOUT
#define	__H_RXDUINO_SHIFTOUT
/**************************************************************************//**
 * @file    shiftout.h
 * @brief   単純なシリアル・パラレル変換
 ******************************************************************************/
#include "rxduino.h"

#ifdef __cplusplus
	extern "C" {
#endif


/*********************************************************************//**
 * @brief		1バイト分のデータを1ビットずつ出力する.
 * @details		最上位ビット(MSB)と最下位ビット(LSB)のどちらからもスタートできます。
 * 				各ビットはまずdataPinに出力され、その後clockPinが反転して、そのビットが有効になったことが示されます。
 * @param[in]	dataPin データ出力ピン
 * @param[in]	clockPin クロック入力ピン
 * @param[in]	bitOrder ビットオーダの指定
 * 				- MSBFIRST : 最上位ビットから送る
 * 				- LSBFIRST : 最下位ビットから送る
 * @param[in]	value 送信したいデータ(unsigned char)
 *
 * @return		なし
 **********************************************************************/
void shiftOut(int dataPin,int clockPin,int bitOrder, unsigned char value);

/*********************************************************************//**
 * @brief		1バイトのデータを1ビットずつ取り込む。
 * @details		最上位ビット(MSB)と最下位ビット(LSB)のどちらからもスタートできます。
 * 				各ビットについて次のように動作します。
 * 				まずclockPinがHIGHになり、dataPinから次のビットが読み込まれ、clockPinがLOWに戻ります。
 * @param[in]	dataPin データ出力ピン
 * @param[in]	clockPin クロック入力ピン
 * @param[in]	bitOrder ビットオーダの指定
 * 				- MSBFIRST : 最上位ビットから送る
 * 				- LSBFIRST : 最下位ビットから送る
 *
 * @return	value 読み取った値(unsigned char)
 **********************************************************************/
unsigned char shiftIn(unsigned char dataPin, unsigned char clockPin, SPI_BIT_ORDER bitOrder);

/*********************************************************************//**
 * @brief		複数バイト分のデータを1ビットずつ出力する.
 * 				shiftOut関数のRXduinoオリジナル拡張で32bitまで1bit単位で指定できます。
 * 				最上位ビット(MSB)と最下位ビット(LSB)のどちらからもスタートできます。
 * 				各ビットはまずdataPinに出力され、その後clockPinが反転して、そのビットが有効になったことが示されます。
 *
 * @param[in]	dataPin データ出力ピン
 * @param[in]	clockPin クロック入力ピン
 * @param[in]	bitOrder ビットオーダの指定
 * 				- MSBFIRST : 最上位ビットから送る.32bit未満のデータの場合,valueはMSB詰めで設定してください
 * 				- LSBFIRST : 最下位ビットから送る.32bit未満のデータの場合,valueはLSB詰めで設定してください
 * @param[in]	len 出力するデータのビット数。
 * @param[in]	value 送信したいデータ(unsigned char)
 *
 * @return		なし
 **********************************************************************/
void shiftOutEx(int dataPin,int clockPin,int bitOrder, int len,unsigned long value);

#ifdef __cplusplus
	}
#endif

#endif // __H_RXDUINO_SHIFTOUT

