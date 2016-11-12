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

#ifndef TKDN_I2C_H_
#define TKDN_I2C_H_
/**************************************************************************//**
 * @file    tkdn_i2c.h
 * @brief   RXマイコンに、I2Cの周辺デバイスを接続してアクセスするためのルーチン
 * @details このライブラリは、RXマイコンの任意の端子を通じて、I2C周辺デバイスと接続できます。<BR>
 *          RXマイコンに内蔵されたRIICモジュールではなく、GPIOを使っているので、任意の端子を通じて操作できます。
 ******************************************************************************/

#include "tkdn_hal.h"

#ifdef __cplusplus
	extern "C" {
#endif

#define I2C_BUFSIZE 260

typedef struct i2c_info
{
	
	int				sda_pin;
	int				scl_pin;
	unsigned char	address;
	unsigned char   buf[I2C_BUFSIZE];
	int             wptr;
	int             rptr;
	int             ack_nack;
} i2c_info;

/*********************************************************************//**
 * @brief     I2C(マスター)を操作するための初期化
 * @details   この関数を呼び出すと、引数i2cで指定された構造体のメンバを初期化し、I2Cを使用する準備をします。<BR>
 *            RXマイコンがI2Cマスターになります。<BR>
 *            引数に指定するI2C構造体は、この関数を呼び出すユーザアプリ側で用意してください。
 * @param[in] i2c 初期化したいi2c構造体へのポインタ
 * @param     sda SDA(データ端子)のピンの番号。任意のピンが使用できる。
 * @param     scl SCL(クロック端子)のピンの番号。任意のピンが使用できる。
 * @note      SDA端子はACKを受信する時に内蔵プルアップが有効になるので、外付けのプルアップ抵抗がなくてもそれなりに通信はできるが、より安定した高速動作のためにはプルアップ抵抗を外付けすることが望ましい
 **********************************************************************/
void i2c_init(i2c_info *i2c,int sda, int scl);

/*********************************************************************//**
 * @brief     I2C(スレーブ)を操作するための初期化
 * @details   この関数を呼び出すと、引数i2cで指定された構造体のメンバを初期化し、I2Cを使用する準備をします。<BR>
 *            RXマイコンがI2Cスレーブになります。<BR>
 *            引数に指定するI2C構造体は、この関数を呼び出すユーザアプリ側で用意してください。
 * @param[in] i2c 初期化したいi2c構造体へのポインタ
 * @param     sda SDA(データ端子)のピンの番号
 * @param     scl SCL(クロック端子)のピンの番号
 * @param     addr 自身のI2Cアドレス
 * @note      この関数は作成されていない。すなわちI2Cスレーブモードは使用できない。
 * @todo      いずれI2Cスレーブモードを作る必要があるだろう
 **********************************************************************/
void i2c_init_slave(i2c_info *i2c,int sda, int scl,unsigned char addr);

/*********************************************************************//**
 * @brief     I2Cデバイスに対して受信シーケンスを発行し、データを読み出す
 * @details   読み出したデータ数は i2c_available() 関数で確認する。バッファ中のデータ i2c_read() 関数で読み出す。
 * @param[in] i2c i2c_init() 関数でセットアップされた構造体へのポインタ
 * @param     address ターゲットデバイスのアドレス(7bit)<BR>RD/WRを示すビットは含まず、0～0x7Fまでの純粋なアドレスを与えること。
 * @param     count 読み出したいデータのバイト数。範囲は0～260。260以上の値を指定した場合は260に切り捨てられる。
 * @return    実際に受信したバイト数。ターゲットデバイスがNACKを返した場合は、countで指定した値に満たなくても終了する。
 **********************************************************************/
int i2c_request_from(i2c_info *i2c,unsigned char address, int count);

/*********************************************************************//**
 * @brief     受信バッファ内に格納されているデータ数を返す
 * @param[in] i2c i2c_init() 関数でセットアップされた構造体へのポインタ
 * @return    データ数(バイト単位)
 **********************************************************************/
int i2c_available(i2c_info *i2c);

/*********************************************************************//**
 * @brief     受信バッファからデータを1バイト取り出す
 * @param[in] i2c i2c_init() 関数でセットアップされた構造体へのポインタ
 * @return    データがある場合は0～255を返す。データがない場合は-1を返す。
 **********************************************************************/
int i2c_read(i2c_info *i2c);

/*********************************************************************//**
 * @brief     I2Cデバイスに対して送信を開始するための準備をする
 * @note      この関数は送信バッファを初期化するだけで、実際の動作は行わない。繰り返し呼ぶと、送信バッファが先頭に戻る。
 * @param[in] i2c i2c_init() 関数でセットアップされた構造体へのポインタ
 * @param     address ターゲットデバイスのアドレス(7bit)<BR>RD/WRを示すビットは含まず、0～0x7Fまでの純粋なアドレスを与えること。
 * @return    なし
 **********************************************************************/
void i2c_begin_transmission(i2c_info *i2c,unsigned char address);

/*********************************************************************//**
 * @brief     送信バッファの末尾に1バイトのデータを追加する
 * @note      この関数は送信バッファにデータを溜めるだけで、実際の動作は行わない
 * @param[in] i2c i2c_init() 関数でセットアップされた構造体へのポインタ
 * @param     data 送信したでデータ
 * @return    成功したら1を返す。送信バッファ(260バイト)に空き容量が無ければ失敗して0を返す
 **********************************************************************/
int i2c_write(i2c_info *i2c,unsigned char data);

/*********************************************************************//**
 * @brief     ターゲットデバイスに対してI2Cの送信シーケンスを発行する
 * @details   I2Cの送信はこの関数を実行して初めて実際に行われる。<BR>
 *            送信されるターゲットアドレスは i2c_begin_transmission() 関数で指定したもの。
 *            送信データは i2c_write() 関数でバッファに格納されたもの。
 * @param[in] i2c i2c_init() 関数でセットアップされた構造体へのポインタ
 * @return    戻り値は以下のとおり
 *             - 0: 成功
 *             - 1: 送信バッファ溢れ
 *             - 2: スレーブアドレス送信時にNACKを受信
 *             - 3: データ送信時にNACKを受信
 *             - 4: その他のエラー
 **********************************************************************/
unsigned char i2c_end_transmission(i2c_info *i2c);

/*********************************************************************//**
 * @brief     I2Cの周波数を変更する
 * @details   空ループで測っている。タイマを使ってキャリブレーションしているので、それなりに正確な値が出るはず。
 * @param[in] freq クロックの周波数をHz単位で指定する。有効な値は1～200000程度。基本的にソフトでやっているので400kHzは出ない。
 * @return    なし
 **********************************************************************/
void i2c_set_freq(int freq);

#ifdef __cplusplus
	}
#endif

#endif /* TKDN_I2C_H_ */
