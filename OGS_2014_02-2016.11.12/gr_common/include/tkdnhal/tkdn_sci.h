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

#ifndef __H_TKDN_SCI
#define __H_TKDN_SCI
/**************************************************************************//**
 * @file    tkdn_sci.h
 * @brief   RXマイコンのシリアル通信を扱う
 * @details Serial クラスはこのルーチンをC++でカプセル化したものである。
 ******************************************************************************/

#include "tkdn_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SCI_TXINTERRUPT_NOTUSE  0
#define SCI_TXINTERRUPT_USE     1

/*********************************************************************//**
 * @brief     SCIの動作ポート定数
 **********************************************************************/
typedef enum {
	SCI_NONE,     //!< @brief SCIを使わない
	SCI_AUTO,     //!< @brief SCIを自動選択
	SCI_USB0,     //!< @brief USB0 の仮想COMポートを使う 
	SCI_USB1,     //!< @brief USB1 の仮想COMポートを使う  ※ 未実装
	SCI_SCI0P2x,  //!< @brief SCI0 (ポートP20,P21と兼用) を使う
	SCI_SCI1JTAG, //!< @brief SCI1 (ポートPF0,PF2,JTAGと兼用) を使う 
	SCI_SCI2A,    //!< @brief SCI2A (ポートP13,P12)を使う  
	SCI_SCI2B,    //!< @brief SCI2B (ポートP50,P52)を使う  
	SCI_SCI6A,    //!< @brief SCI6A (ポートP00,P01)を使う  ※100ピンデバイスにはない
	SCI_SCI6B,    //!< @brief SCI6B (ポートP32,P33)を使う  
} SCI_PORT;

/*********************************************************************//**
 * @brief     CR(\\r == 0x0d)やLF(\\n == 0x0a)の取り扱い方法
 **********************************************************************/
typedef enum {
	CRLF_NONE, //!< @brief CRやLFを変換しない
	CRLF_CR,   //!< @brief 改行はCRのみである
	CRLF_CRLF, //!< @brief 改行はCRとLFである
} CRLFMODE;


//■■■■■■■■■■■■■■■■■■■■■■■■■
//  ユーザがカスタマイズする場所

#define SCI_BUFSIZE  256          // 受信・送信があるので実際にはこの2倍のメモリを使う
                                  // 2^nの値を指定すること

// SCI TX割り込みを使うならここを書き換える
#define SCI_TXINTERRUPT_MODE    SCI_TXINTERRUPT_USE

//  カスタマイズはここまで
//■■■■■■■■■■■■■■■■■■■■■■■■■

typedef struct sci_str
{
	// 送受信バッファ
	char rxbuf[SCI_BUFSIZE];
	char txbuf[SCI_BUFSIZE];
	
	// 送受信バッファのポインタ
	volatile int     tx_rptr;
	volatile int     tx_wptr;
	volatile int     rx_rptr;
	volatile int     rx_wptr;
	
	SCI_PORT port;
	CRLFMODE crlf_tx;
	CRLFMODE crlf_rx;
} sci_str;

//! @brief   SCI情報構造体のハンドラ(拡張版SCIルーチンで使用する)
//! @note    構造体の実際の中身は気にしなくてよい
typedef struct sci_str sci_t; 

//各種関数

/*********************************************************************//**
 * @brief     デフォルトのSCIポートを初期化する
 * @param     _port 使いたいポートを指定する
 * @param     bps ボーレート(bps)
 * @return    実際に使用されたポートが SCI_PORT 型で返る
 * @note      SCI_AUTOを指定した場合は、実際にオープンされたポート番号が返る
 * @warning   SCI_AUTOを指定した場合は、SCI_USB0とSCI0、SCI1で待ちうけて何かデータが送られてくるまで待機し、制御を返さない。
 **********************************************************************/
SCI_PORT sci_init(SCI_PORT _port,int bps);

/*********************************************************************//**
 * @brief     デフォルトのSCIポートの使用ポートを取得する
 * @return    実際に使用されているポートが SCI_PORT 型で返る
 **********************************************************************/
SCI_PORT sci_getport(void);

/*********************************************************************//**
 * @brief     デフォルトのSCIポートに１文字送信する
 * @param     c 送信した文字コード
 * @return    失敗(送信バッファFULL)したら0を返す。成功したら1を返す。
 * @note      送信する改行コードは sci_convert_crlf() 関数で指定した方法で変換される
 * @note      実際には即座に送信するのではなく、送信バッファに溜めるのみである。実際の送信動作は割り込み処理で行われる。
 * @note      \\nを送信しようとして、\\n\\rに変換されても、戻り値は1である。
 **********************************************************************/
int sci_putc(char c);

/*********************************************************************//**
 * @brief     デフォルトのSCIポートに文字列を送信する
 * @param[in] str 送信したい文字列 ヌル文字で終了すること
 * @return    失敗(送信バッファFULL)したら0を返す。成功したら1を返す。
 * @note      送信する改行コードは sci_convert_crlf() 関数で指定した方法で変換される
 * @note      実際には即座に送信するのではなく、送信バッファに溜めるのみである。実際の送信動作は割り込み処理で行われる。
 * @note      \\nを送信しようとして、\\n\\rに変換されても、戻り値は1加算されるのみである。
 **********************************************************************/
int sci_puts(const char *str);

/*********************************************************************//**
 * @brief     デフォルトのSCIポートから受信した文字をバッファから1文字読み出して返す
 * @return    受信した文字コード。バッファにデータがなければ\\0を返す
 * @note      受信した改行コードは sci_convert_crlf() 関数で指定した方法で変換される
 **********************************************************************/
char sci_getc(void);

/*********************************************************************//**
 * @brief     デフォルトのSCIポートから受信した文字を、文字列として読み出す。エコーバックも行う。
 * @details   この関数は受信した文字が指定した文字数に達するか、改行コードを受け取るまで待機する。<BR>
 *            格納される文字列の最後にヌルターミネータを付け加えられるが、最大文字数に達した場合はヌルターミネータはつけない。
 *            バックスペースを受信した場合は、格納された文字列の末尾を1つ削除する。
 * @param[in] s 文字列が格納されるバッファへのポインタ
 * @param     max 受信する最大の文字数
 * @return    受信した文字コード。バッファにデータがなければ\\0を返す
 * @note      受信した改行コードは sci_convert_crlf() 関数で指定した方法で変換される
 * @warning   この関数の中でループするため、この関数が終了するまでイーサネットの処理が止まる。
 **********************************************************************/
char *sci_gets(char *s,int max);

/*********************************************************************//**
 * @brief     デフォルトのSCIポートにバイナリデータを送信する
 * @details   指定した長さのデータを送信する。
 *            この関数は改行コードの変換を行わない。
 * @param[in] data 送信したいデータを格納したバッファへのポインタ
 * @param     len 送信したいデータ長
 * @note      実際には即座に送信するのではなく、送信バッファに溜めるのみである。実際の送信動作は割り込み処理で行われる。
 **********************************************************************/
void sci_writedata(const unsigned char *data,int len);

/*********************************************************************//**
 * @brief     デフォルトのSCIポートからバイナリデータを受信する
 * @warning   この関数は実装されていない
 **********************************************************************/
void sci_readdata(unsigned char *data,int len);

/*********************************************************************//**
 * @brief     デフォルトのSCIポートから受信したデータがバッファに溜まっている量を調べる
 * @return    受信したデータの量をバイト単位で返す
 **********************************************************************/
int  sci_rxcount(void);

/*********************************************************************//**
 * @brief     デフォルトのSCIポートで送受信するデータのCRやLFの変換方法を指定する
 * @details   C言語の改行コードは\\nであるが、通信系は\\nだったり\\rだったり\\n\\rだったりする。<BR>
 *            それらの変換を適切に行い、送受信するデータがC言語のプログラムで扱えるようにする。
 * @param     tx 送信データの改行コード。 
 * @param     rx 受信データの改行コード。 
 * @return    なし
 **********************************************************************/
void sci_convert_crlf(CRLFMODE tx,CRLFMODE rx);

/*********************************************************************//**
 * @brief     デフォルトのSCIポートの受信データを覗き見る
 * @details   受信した文字を受信バッファから取り出すことなく、先頭にある1文字を覗き見る
 * @note      受信データがないときの挙動は不定である。先に sci_rxcount() 関数を呼び出しておくこと。
 * @return    受信バッファの先頭にある文字
 **********************************************************************/
char sci_peek(void);

/*********************************************************************//**
 * @brief     デフォルトのSCIポートの送信データをフラッシュする
 * @return    なし
 **********************************************************************/
void sci_flush(void);


// 拡張版SCIルーチン

// SCIの初期化
TKDN_HAL
void sci_init_ex(sci_t *sci,SCI_PORT _port,int bps);

// SCIの使用ポートを取得
TKDN_HAL
SCI_PORT sci_getport_ex(sci_t *sci);

// １文字送信
//   ※失敗(送信バッファFULL)したら0を返す
TKDN_HAL
int sci_putc_ex(sci_t *sci,char c);

// 文字列送信
//   ※失敗(送信バッファFULL)したら0を返す
TKDN_HAL
int sci_puts_ex(sci_t *sci,const char *str);

// １文字受信
//  ※受信した文字がなければ\0を返す
TKDN_HAL
char sci_getc_ex(sci_t *sci);

// 文字列受信
// 最大max文字受信する
// 最後にヌルターミネータをつけるが、最大文字数に達した場合はヌルターミネータはつけない
TKDN_HAL
char *sci_gets_ex(sci_t *sci,char *s,int max);

// バイナリデータ送信
TKDN_HAL
void sci_writedata_ex(sci_t *sci,const unsigned char *data,int len);

// バイナリデータ受信
//  ※指定されたデータ量を受信するまで制御を返さない
TKDN_HAL
void sci_readdata_ex(sci_t *sci,unsigned char *data,int len);

// 受信バッファに溜まっているデータ数を調べる
TKDN_HAL
int  sci_rxcount_ex(sci_t *sci);

// CRやLFの変換をSCIライブラリ内で行う
TKDN_HAL
void sci_convert_crlf_ex(sci_t *sci,CRLFMODE tx,CRLFMODE rx);

// データを覗き見る
TKDN_HAL
char sci_peek_ex(sci_t *sci);

// 送信データをフラッシュする
TKDN_HAL
void sci_flush_ex(sci_t *sci);

// 
TKDN_HAL
void sci_regist_default(sci_t *sci);

#ifdef __cplusplus
}
#endif

#endif // __H_TKDN_SCI

