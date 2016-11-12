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

#ifndef RXSTRING_H_
#define RXSTRING_H_
/**************************************************************************//**
 * @file    rxstring.h
 * @brief   文字列を使いやすくするためのライブラリ
 * @todo    いろいろできていない。まだ作り始め
 ******************************************************************************/

#include "rxduino.h"

#ifdef __cplusplus
	extern "C" {
#endif

#define STRING_LIBRARY_VERSION 0x01080000 // Version 1.08
#define STRING_LIBRARY_TIME    1380466335 // 2013/09/29 23:52:15 

/**************************************************************************//**
 * @class   STRING
 * @brief   Stringクラス
******************************************************************************/

class String {
private:
	char *core;
	unsigned int bufsize;
	void CreateCore();
	void BufMore(int newsize);
	void create_number(long val,int print_type);
	void create_fpnumber(double val, int fpdigit);

public:
/*********************************************************************//**
 * @brief		このクラスのバージョンを取得する
 * @param[in]	vi 値をセットしたいバージョン情報構造体へのポインタ
 * @return		バージョン番号
 **********************************************************************/
	static unsigned long getVersion(version_info *vi);

	//! 空の文字列を作るコンストラクタ
	String();
	//! 文字からStringを作るコンストラクタ
	String(char c);
	//! 文字列からStringを作るコンストラクタ
	String(const char str[]);
	//! StringからStringを作るコピーコンストラクタ
	String(const String &str);
	//! 数値からStringを作るコンストラクタ
	String(unsigned char val,int print_type=DEC);
	//! 数値からStringを作るコンストラクタ
	String(unsigned long val,int print_type=DEC);
	//! 数値からStringを作るコンストラクタ
	String(unsigned int val,int print_type=DEC);
	//! 数値からStringを作るコンストラクタ
	String(long val,int print_type=DEC);
	//! 数値からStringを作るコンストラクタ
	String(int val,int print_type=DEC);
	//! 数値からStringを作るコンストラクタ
	String(double val,int digit=2);

	//! デストラクタ
	~String();
	
	//! 先頭からn+1番目の文字を返す
	char charAt(int n) const;

	//! 文字列を比較する
	int compareTo(const String &str2) const;

	//! 元の文字列の末尾にString2を連結する。元の文字列は変更される。
	String concat(const String &string2);

	//!
	bool endsWith(const String &string2) const;

	//! 
	bool equals(const String &string2) const;

	//! 
	bool equalsIgnoreCase(const String &string2) const;

	//! 
	void getBytes(char *buf,int len) const;

	//! 文字または文字列を探す
	int indexOf(char c,int from=0) const;
	int indexOf(const char str[],int from=0) const ;
	int lastIndexOf(char c,int from=-1) const;
	int lastIndexOf(const char str[],int from=-1) const ;

	//! 
	size_t length() const;

	//! 置換した文字列を返す。元の文字列は変更しない。
	String replace(const String &from,const String &to) const;

	//! 
	void setCharAt(int index,char c);

	//! 
	bool startsWith(const String &string2) const;

	//! 
	String substring(int from,int to=-1) const;

	//! 
	void toCharArray(char *buf,int len) const;

	//! 小文字にした文字列を返す。元の文字列は変化しない。
	String toLowerCase() const;

	//! 大文字にした文字列を返す。元の文字列は変化しない。
	String toUpperCase() const;

	//! 先頭と末尾の空白や制御文字を取り除いた文字列を返す。元の文字列は変化しない。
	String trim() const;

	//! いかにも危険そうな中身を見る関数
	char *c_str() const;

	// 結合の演算子
	String operator+(const String& str2);  // +演算子オーバーロード
	// 結合と代入の演算子
	String& operator+=(const String& str2); // +=演算子オーバーロード
	// 比較の演算子
	bool operator==(const String& str2);  // ==演算子オーバーロード
	// 代入の演算子
	String& operator=(const String& str2);  // =演算子オーバーロード
	// 添え字の演算子
	char& operator[] (unsigned int index);

};

#ifdef __cplusplus
	}
#endif

#endif /* RXSTRING_H_ */
