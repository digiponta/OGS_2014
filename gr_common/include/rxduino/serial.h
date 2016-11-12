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

#ifndef	__H_RXDUINO_SERIAL
#define	__H_RXDUINO_SERIAL

/**************************************************************************//**
 * @file    serial.h
 * @brief   UARTやUSB仮想COMポートを使うためのライブラリ
 ******************************************************************************/

#include <stdlib.h>
#include "rxduino.h"
#include "rxstring.h"
//#include "Print.h"
#include "../tkdnhal/tkdn_sci.h"

#ifdef __cplusplus
	extern "C" {
#endif

extern SCI_PORT SCI_DEFAULT_PORT;
class String;

//------------------------------------------------------------------
// シリアルポート
//------------------------------------------------------------------


/*! @class   CSerial
    @brief   シリアル通信を制御するクラス。このクラスのインスタンスは、何らかのシリアルポートを制御する。
    @details レガシーなUARTや、USB仮想COMポートを統一の取れた手段で扱うことができる。
    @note    システム起動時に既に、Serial、Serial1、Serial2、Serial3という4つのグローバルな<BR>
             インスタンスが宣言されている。これらのインスタンスはデフォルトでは物理的にどこかのポートに<BR>
              関連付けられているわけではない。Serail?.beginを行って、はじめて実際のポートに関連づけられる。<BR>
*/
class CSerial {
//class CSerial: public Print {
private:
	SCI_PORT port; /* ポート番号。 SCI_SCI0P2x SCI_SCI1JTAG SCI_SCI2A SCI_SCI2B SCI_SCI6A SCI_SCI6B SCI_USB0の中から指定 */  
	sci_str sci;
	size_t print_number(unsigned long val,int base);

public:
	CSerial(SCI_PORT port=SCI_NONE); // 
	~CSerial();

	//! シリアル通信ポートの初期化 デフォルトのポート(SCI_USB0)が使用される
	/*!
		@param bps ボーレート
		@note  ボーレートには任意の値を設定してよいが、9600,38400,115200などが無難である
		@return なし
		@include serial1.cpp
	*/
	void begin(int bps);

	//! ポートを指定して、シリアル通信ポートの初期化
	/*!
		@param bps ボーレート
		@param port
			- SCI_NONE : SCIポートを使用しない
			- SCI_AUTO : SCIを自動選択
			- SCI_USB0 : USB0 の仮想COMポートを使う
			- SCI_USB1 : USB1 の仮想COMポートを使う （未実装）
			- SCI_SCI0P2x : SCI0 (ポートP20,P21と兼用) を使う
			- SCI_SCI1JTAG : SCI1 (ポートPF0,PF2,JTAGと兼用) を使う
			- SCI_SCI2A : SCI2A (ポートP13,P12)を使う
			- SCI_SCI2B : SCI2B (ポートP50,P52)を使う
			- SCI_SCI6A : SCI6A (ポートP00,P01)を使う ※SAKURAでは使えない
			- SCI_SCI6B : SCI6B (ポートP32,P33)を使う
		@warning SCI_AUTOを指定した場合、SCI0,SCI1,USB0から最初に何かを受信するまで制御を返しません。
		@return なし
		@note 通常のシリアルポートオープンの例
		@include serial2.cpp
		@note 複数のシリアルポートをオープンする例
		@include serial3.cpp
	*/
	void begin(int bps,SCI_PORT port);

	//! シリアル通信ポートのクローズ
	/*!
		@param なし
		@return なし
	*/
	void end();

	/*!
	@brief    このシリアルをデフォルトのシリアルとして設定し、printf等の出力先にする
	@details  printf()など、標準出力がSerialから出力されるようになります。
	@note     printf()は\\nが来るまで内部でバッファしてしまうので、改行のない文字列を即座に出力するには、
	          setvbuf()も必要です。
	@param    なし
	@return   なし
	@include  serial_setdefault.cpp
	*/
	void setDefault();

	//! シリアルポートから何バイトのデータが読み取れるかを返す
	/*!
	@param なし
	@return シリアルバッファにあるデータのバイト数。0の場合はデータなし
	*/
	int available();

	//! シリアルポートの受信バッファから１バイトのデータを読み出します
	/*!
	@param なし
	@return 先頭のデータ。データなしの場合は-1が返る
	*/
	int read();

	//! シリアルポートの受信バッファにある先頭のデータを読みます。バッファ中の読み込み位置は変更しないので、バッファを覗くだけです。CRLFの変換は行われません。
	/*!
	@param なし
	@return 先頭のデータ。データなしの場合は-1が返る
	*/
	int peek();

	//! シリアルポートの送信バッファが空になるまで待ちます。受信バッファをどうするかは、Arduinoの仕様が変わっているので、検討中です。
	/*!
	@param なし
	@return なし
	*/
	void flush();

	//! この関数は実装していない
//	void serialEvent();

	//! シリアルポートに1文字出力する
	/*!
	@param val 文字コード
	@return 実際に出力した文字数
	*/
	size_t write(unsigned char val);

	//! シリアルポートに文字列を出力する
	/*!
	@param str ヌル(\\0)で終わる文字列
	@return 実際に出力した文字数
	*/
	size_t write(const char *str);

	//! シリアルポートにString型を出力する
	/*!
	@param str String型のオブジェクト
	@return 実際に出力したバイト数
	*/
	size_t write(const String str);

	//! シリアルポートに指定した長さのデータ列を出力する
	/*!
	@param buf 出力データ
	@param len 出力データの長さ
	@return 実際に出力したバイト数
	*/
	size_t write(const unsigned char *buf,int len);

	//! シリアルポートに文字列を出力する
	/*!
	@param str ヌル(\\0)で終わる文字列
	@return 実際に出力したバイト数
	*/
	size_t print(const char str[]);

	//! シリアルポートにString型を出力する
	/*!
	@param str String型のオブジェクト
	@return 実際に出力したバイト数
	*/
	size_t print(const String str);

	//! シリアルポートに文字を出力する
	/*!
	@param c 出力したい文字コード
	@return 実際に出力したバイト数
	*/
	size_t print(char c);

	//! シリアルポートに値(数字)を出力する
	/*!
	@param c 出力したい値
	@param print_type 基数
	       - 2:  二進数
	       - 8:  8進数
	       - 10: 10進数 (デフォルト)
	       - 16: 16進数
	@return 実際に出力したバイト数
	*/
	size_t print(unsigned char c, int print_type=DEC);

	//! シリアルポートに値(数字)を出力する
	/*!
	@param val 出力したい値
	@param print_type 基数
	       - 2:  二進数
	       - 8:  8進数
	       - 10: 10進数 (デフォルト)
	       - 16: 16進数
	@return 実際に出力したバイト数
	*/
	size_t print(int val, int print_type=DEC);

	//! シリアルポートに値(数字)を出力する
	/*!
	@param val 出力したい値
	@param print_type 基数
	       - 2:  二進数
	       - 8:  8進数
	       - 10: 10進数 (デフォルト)
	       - 16: 16進数
	@return 実際に出力したバイト数
	*/
	size_t print(unsigned int val, int print_type=DEC);

	//! シリアルポートに値(数字)を出力する
	/*!
	@param val 出力したい値
	@param print_type 基数
	       - 2:  二進数
	       - 8:  8進数
	       - 10: 10進数 (デフォルト)
	       - 16: 16進数
	@return 実際に出力したバイト数
	*/
	size_t print(long val, int print_type=DEC);

	//! シリアルポートに値(数字)を出力する
	/*!
	@param val 出力したい値
	@param print_type 基数
	       - 2:  二進数
	       - 8:  8進数
	       - 10: 10進数 (デフォルト)
	       - 16: 16進数
	@return 実際に出力したバイト数
	*/
	size_t print(unsigned long val, int print_type=DEC);

	//! シリアルポートに浮動小数点数を出力する
	/*!
	@param val 出力したい値
	@param fpdigit 桁数
	@return 実際に出力したバイト数
	*/
	size_t print(double val, int fpdigit=2);

	//! シリアルポートに文字列を出力して改行コード(\\n\\r)を出力する
	/*!
	@param str ヌル(\\0)で終わる文字列
	@return 実際に出力した文字数
	*/
	size_t println(const char str[]);

	//! シリアルポートにString型を出力して改行コード(\\n\\r)を出力する
	/*!
	@param str ヌル(\\0)で終わる文字列
	@return 実際に出力した文字数
	*/
	size_t println(const String str);

	//! シリアルポートに文字を出力して改行コード(\\n\\r)を出力する
	/*!
	@param c 出力したい文字コード
	@return 実際に出力したバイト数
	*/
	size_t println(char c);

	//! シリアルポートに値(数字)を出力して改行コード(\\n\\r)を出力する
	/*!
	@param c 出力したい値
	@param print_type 基数
	       - 2:  二進数
	       - 8:  8進数
	       - 10: 10進数 (デフォルト)
	       - 16: 16進数
	@return 実際に出力したバイト数
	*/
	size_t println(unsigned char c, int print_type=DEC);

	//! シリアルポートに値(数字)を出力して改行コード(\\n\\r)を出力する
	/*!
	@param val 出力したい値
	@param print_type 基数
	       - 2:  二進数
	       - 8:  8進数
	       - 10: 10進数 (デフォルト)
	       - 16: 16進数
	@return 実際に出力したバイト数
	*/
	size_t println(int val, int print_type=DEC);

	//! シリアルポートに値(数字)を出力して改行コード(\\n\\r)を出力する
	/*!
	@param val 出力したい値
	@param print_type 基数
	       - 2:  二進数
	       - 8:  8進数
	       - 10: 10進数 (デフォルト)
	       - 16: 16進数
	@return 実際に出力したバイト数
	*/
	size_t println(unsigned int val, int print_type=DEC);

	//! シリアルポートに値(数字)を出力して改行コード(\\n\\r)を出力する
	/*!
	@param val 出力したい値
	@param print_type 基数
	       - 2:  二進数
	       - 8:  8進数
	       - 10: 10進数 (デフォルト)
	       - 16: 16進数
	@return 実際に出力したバイト数
	*/
	size_t println(long val, int print_type=DEC);

	//! シリアルポートに値(数字)を出力して改行コード(\\n\\r)を出力する
	/*!
	@param val 出力したい値
	@param print_type 基数
	       - 2:  二進数
	       - 8:  8進数
	       - 10: 10進数 (デフォルト)
	       - 16: 16進数
	@return 実際に出力したバイト数
	*/
	size_t println(unsigned long val, int print_type=DEC);

	//! シリアルポートに浮動小数点数を出力して改行コード(\\n\\r)を出力する
	/*!
	@param val 出力したい値
	@param fpdigit 桁数
	@return 実際に出力したバイト数
	*/
	size_t println(double val, int fpdigit=2);

	//! シリアルポートに改行コードのみ出力して改行コード(\\n\\r)を出力する
	/*!
	@param なし
	@return 実際に出力したバイト数
	*/
	size_t println(void);
		
	//! このクラスに結びつけられている特電HALのシリアル構造体へのハンドルを得る
	/*!
	@param なし
	@details より低レベルなシリアル操作を行うときに使います
	@return シリアルクラスのハンドル
	*/
	sci_str *get_handle();
};

extern CSerial Serial;
extern CSerial Serial1;
extern CSerial Serial2;
extern CSerial Serial3;

#ifdef __cplusplus
	}
#endif

#endif // __H_RXDUINO_SERIAL

