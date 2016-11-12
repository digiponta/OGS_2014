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

#ifndef __H_TKDN_DFLASH
#define __H_TKDN_DFLASH
/**************************************************************************//**
 * @file    tkdn_dflash.h
 * @brief   内蔵データフラッシュを使用するためのルーチン
 * @details RX62N/RX63Nには、データフラッシュという32kBの不揮発性メモリが内蔵されています。<BR>
 *          MACアドレスやホスト名、各種IDなど、ボード固有の情報を格納しておくのに使えます。<BR>
 *          このライブラリは、内蔵データフラッシュを使いやすくするためのものです。
 * @todo	このライブラリはRX63N用に作られてしまったのでRX62Nでは使えない。RX62Nでも使えるようにしなければならない。
 ******************************************************************************/

#include "tkdn_dflash.h"

#ifdef __cplusplus
extern "C" {
#endif

//■■■■■■■■■■■■■■■■■■■■■■■■■
//  ユーザがカスタマイズする場所はありません
//■■■■■■■■■■■■■■■■■■■■■■■■■

/*********************************************************************//**
 * @brief		内蔵データフラッシュの任意の位置に指定した長さのデータを書き込む
 * @details		内蔵データフラッシュに2バイトずつ書き込んでいく。
 * @param		offset 書き込みたいデータフラッシュのアドレス。必ず偶数番地から始めること。範囲は0～32766。
 * @param[in]   buf 書き込みたいデータが格納されているバッファへのポインタ
 * @param		len 書き込みたいデータの長さ。offset + lenが32768を超えるとエラーを返す
 * @return		書き込み結果を示す。
 *				 - 0 : 書き込み失敗(何らかのエラー)
 *				 - -1 : アドレスや長さの範囲のエラー。セットアップのエラーが発生したことを示す。
 *				 - 1～32768 : 書き込まれたデータの長さ(バイト数)
 * @warning		この関数を呼び出した後は、データフラッシュはアクティブ(内蔵高電圧ON)になっているので、<BR>
 *              最後のアクセスの場合は、tkdn_dflash_terminateを呼び出すこと。
 * @todo		RX62Nでも使えるようにしたい。
 **********************************************************************/
int tkdn_dflash_write(unsigned long offset,unsigned char *buf,int len);

/*********************************************************************//**
 * @brief		内蔵データフラッシュの任意の位置のデータを読み出し、バッファに格納する
 * @param		offset 書き込みたいデータフラッシュのアドレス。0～32767の範囲。
 * @param[out]  buf 読み出しデータを格納するバッファへのポインタ
 * @param		len 読み出したいデータの長さ。
 * @return		読み出したデータの長さ(バイト数)
 * @note		この関数は内部でtkdn_dflash_terminateを行っているので、内蔵高電圧はOFFになる。
 * @warning		この関数を呼び出した後は、データフラッシュはアクティブ(内蔵高電圧ON)になっているので、<BR>
 *              最後のアクセスの場合は、tkdn_dflash_terminateを呼び出すこと。
 * @todo		RX62Nでも使えるようにしたい。
 **********************************************************************/
int tkdn_dflash_read(unsigned long offset,unsigned char *buf,int len);

/*********************************************************************//**
 * @brief		内蔵データフラッシュの任意の位置のブロックを消去する
 * @param		offset 消去したいデータフラッシュのアドレス。32の倍数であること。0～32736の範囲。
 * @param		len 消去したいデータの長さ。32の倍数であること。offset + lenが32768を超えるとエラーを返す
 * @return		消去結果
 *				 - 0 : 消去失敗(何らかのエラー)
 *				 - 1 : 消去成功
 *				 - -1 : アドレスや長さの範囲のエラー。セットアップのエラーが発生したことを示す。
 * @note		RX63Nでは消去は32バイト単位
 * @warning		この関数を呼び出した後は、データフラッシュはアクティブ(内蔵高電圧ON)になっているので、<BR>
 *              最後のアクセスの場合は、tkdn_dflash_terminateを呼び出すこと。
 * @todo		RX62Nでも使えるようにしたい。
 **********************************************************************/
int tkdn_dflash_erase(unsigned long offset,int len);

/*********************************************************************//**
 * @brief		フラッシュ書き込みモードを終了する
 * @details		書き込み/消去不可能な初期状態に戻す。内蔵高電圧がOFFになり、消費電力が減る。<BR>
 * 				内蔵フラッシュのアクセスを終了する際には必ず呼び出すこと。
 * @param		なし
 * @return		なし
 **********************************************************************/
void tkdn_dflash_terminate(void);

/*********************************************************************//**
 * @brief		内蔵データフラッシュの任意の領域をブランクチェックする
 * @details		書き込み/消去不可能な初期状態に戻す。内蔵高電圧がOFFになり、消費電力が減る。<BR>
 * 				内蔵フラッシュのアクセスを終了する際には必ず呼び出すこと。
 * @param		offset 検査したいデータフラッシュのアドレス。32の倍数であること。0～32736の範囲。
 * @param		len 検査したい長さ
 * @return		検査結果
 *				 - 0 : 指定された領域には書き込まれたデータがある
 *				 - 1 : 指定された領域はブランクである
 *				 - -1 : エラーのため検査できなかったことを示す
 * @note		RXの内蔵データフラッシュは、消去後に1、書き込み後に0なるような普通のフラッシュメモリではない。<BR>
 *              消去時(未書き込み時)は「不定」なデータとなる。したがって、読み出した値がFFだからといって未書き込みとは判断できない。
 *              ブランクチェックを行う場合は、必ずこの関数を使うこと。
 * @return		なし
 **********************************************************************/
int tkdn_dflash_blank(unsigned long offset,int len);

#ifdef __cplusplus
 }
#endif

#endif // __H_TKDN_TIMER
