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

#ifndef __H_TKDN_VERSION
#define __H_TKDN_VERSION
/**************************************************************************//**
 * @file    tkdn_version.h
 * @brief   バージョン情報を管理する
 * @details このライブラリは低レベルなイーサネットフレームの送受信を行う。
 *          TCP/IPレベルでの送受信は、 tkdnip.h を参照すること。
 ******************************************************************************/

#ifdef __cplusplus
	extern "C" {
#endif

//! @brief バージョン情報構造体
typedef struct version_info
{
	//! @brief ライブラリが生成された日時のUNIX時刻 (本来はtime_t型)
	int    time;         
	//! @brief 詳細な説明が格納された文字配列へのポインタ
	char   *description; 
	//! @brief 著作権情報が格納された文字配列へのポインタ
	char   *copyright;   
	//! @brief 作者名が格納された文字配列へのポインタ
	char   *author;      
	//! @brief ライセンス名が格納された文字配列へのポインタ
	char   *license;     
} version_info;

/*********************************************************************//**
 * @brief		特電HALライブラリのバージョンを得る
 * @param[out]  vi 拡張情報が必要ならばversion_info構造体へのポインタを与える。<BR>
 *              構造体の各フィールドがセットされて戻る。各フィールドは文字列へのポインタだが、<BR>
 *              static constな文字列を指すので、ユーザプログラムでfreeしてはならない。<BR>
 *              拡張情報が不要ならばNULLを指定してもよい
 * @return		バージョン番号を1バイトずつ詰めた16進数で返す
 *              例えば、バージョン1.00ならば、0x01000000を返す
 *              バージョン1.23ならば0x010203となる。
 *              メジャーバージョン.マイナーバージョン.サブバージョン.デバッグバージョン
 **********************************************************************/
unsigned long tkhal_get_version(version_info *vi);

#ifdef __cplusplus
	}
#endif

#endif // __H_TKDN_VERSION

