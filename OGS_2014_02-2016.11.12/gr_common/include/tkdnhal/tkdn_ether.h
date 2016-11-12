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

#ifndef	__H_TKDN_ETHER
#define	__H_TKDN_ETHER
/**************************************************************************//**
 * @file    tkdn_ether.h
 * @brief   内蔵データフラッシュを使用するためのルーチン
 * @details このライブラリは低レベルなイーサネットフレームの送受信を行う。
 *          TCP/IPレベルでの送受信は、 tkdnip.h を参照すること。
 ******************************************************************************/

#include "tkdn_hal.h"

#ifdef __cplusplus
	extern "C" {
#endif

//! @brief イーサネット割り込みが発生したときに呼び出される関数の型
typedef void (*ETHER_USER_INTERRUPT_FUNCTION)(void);

/*********************************************************************//**
 * @brief		PHYをソフトリセットする
 * @param		なし
 * @return		なし
 **********************************************************************/
void ether_phy_softreset();

/*********************************************************************//**
 * @brief		MACアドレスをセットして、内蔵イーサネットPHYをセットアップする
 * @param		mac_addr[] MACアドレスが格納された6バイトの配列
 * @return		成功すると1を返す。失敗すると0を返す。PHYエラーの場合は失敗する。
 **********************************************************************/
int  ether_open(unsigned char mac_addr[]);

/*********************************************************************//**
 * @brief		内蔵イーサネットPHYを終了する。
 * @param		なし
 * @return		なし
 **********************************************************************/
void ether_close(void);

/*********************************************************************//**
 * @brief		イーサネットフレームを送信する
 * @param[in]   buf 送信したいデータが格納されたバッファへのポインタ
 * @param       len 送信したいイーサネットフレームの長さ。プリアンプル、FCS、CRC等は含まない。
 * @return		送信した長さ(バイト数)を返す
 * @note        送信データは、宛先MACアドレスから、最終データまでを格納しておいてください。プリアンプル、FCS、CRC等の制御コードは不要です。
 * @note        60バイト未満だと、末尾に00をパディングしてしまう？
 **********************************************************************/
int  ether_write(unsigned char *buf,int len);

/*********************************************************************//**
 * @brief		受信したイーサネットフレームを取得する
 * @details		受信したイーサネットフレームは、DMAによってRAM上の専用領域に格納されています。<BR>
 *              この関数を呼び出すと、専用領域からユーザバッファへデータを転送します。<BR>
 *              また、受信エラーをチェックし、エラーが発生していれば解除します。
 * @param[in]   buf データを格納するユーザが用意したバッファへのポインタ
 * @return		受信した長さ(バイト数)を返す。0の場合はデータがないことを示す
 * @note        RAM上の受信バッファはデフォルトでは2KBしかないので、受信したら早く取り出すこと。
 * @note        内蔵MACは受信エラー(バッファオーバーラン等)が発生すると以後の受信が不可能になる。<BR>
 *              この関数を呼び出すことでクリアされるので、必要がなくても繰り返し呼び出すこと。
 **********************************************************************/
int  ether_read(unsigned char *buf);

/*********************************************************************//**
 * @brief		リンクアップしているかどうかを調べる
 * @details		PHYのレジスタを参照し、リンクアップを調べる。LINK_STAの端子は使っていない。
 * @param       なし
 * @return		リンクアップしていれば1を返す。リンクダウンしていれば0を返す。
 **********************************************************************/
int  ether_is_linkup(void);

/*********************************************************************//**
 * @brief		リンクが100Mかどうかを調べる
 * @param       なし
 * @return		100Mモードならば1を返す。10Mモードならば0を返す。
 **********************************************************************/
int  ether_is_100M(void);

/*********************************************************************//**
 * @brief		リンクが全二重かどうかを調べる
 * @param       なし
 * @return		全二重ならば1を返す。半二重ならば0を返す。
 **********************************************************************/
int  ether_is_fullduplex(void);

/*********************************************************************//**
 * @brief		オートネゴーシエーションを実行する
 * @param       なし
 * @return		なし
 * @note        結果は ether_is_100M(), ether_is_fullduplex() 関数で調べること。
 **********************************************************************/
void ether_autonegotiate(void);

/*********************************************************************//**
 * @brief		リンクの状態が変化したかどうかを調べる
 * @details     前回呼び出したときからリンクの状態が変化したかどうかを調べる
 * @param       なし
 * @return		変化していれば1を返す。変化していなければ0を返す
 * @note        結果は ether_is_100M(), ether_is_fullduplex() 関数で調べること。
 **********************************************************************/
int  ether_link_changed(void);

/*********************************************************************//**
 * @brief		フレームを受信したときに呼び出される関数を登録する
 * @param[in]   func 呼び出される関数へのポインタ
 * @return		なし
 * @note        登録された関数は割り込みのコンテキストで呼び出される
 **********************************************************************/
void ether_regist_user_rx_procedure(ETHER_USER_INTERRUPT_FUNCTION func);

/*********************************************************************//**
 * @brief		受信バッファをチェックするとともに、受信エラーを解除する
 * @param       なし
 * @return		受信エラーがあれば-1、データがなければ0、データがあれば正の数を返す。
 * @note        実際の受信は行わない。返す値はデータ長とは必ずしも一致しない。
 **********************************************************************/
int ether_check_recv(void);

/*********************************************************************//**
 * @brief		MACアドレスを変更する
 * @param[in]   macaddr MACアドレス
 * @return		なし
 **********************************************************************/
void ether_change_macaddr(const unsigned char macaddr[6]);

/*********************************************************************//**
 * @brief		プロミスキャスモードへの移行と解除
 * @param       enable 0:プロミスキャスモード解除 1:プロミスキャスモード設定
 * @return		なし
 **********************************************************************/
void ether_enable_promis(int enable);

#ifdef __cplusplus
	}
#endif

#endif /* R_ETHER_H */

