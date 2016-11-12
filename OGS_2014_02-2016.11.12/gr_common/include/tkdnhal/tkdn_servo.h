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

#ifndef TKDN_SERVO_H_
#define TKDN_SERVO_H_
/**************************************************************************//**
 * @file    tkdn_servo.h
 * @brief   一般的なサーボモータを制御するためのルーチン
 * @details 一般的に、サーボモータと呼ばれる部品は、電源、GNDのほかに「制御入力」と呼ばれる信号を持ち、
 *          このライブラリはRX62N/RX63Nの内蔵MTUを6個使い、20チャネルのサーボを同時に制御します。<BR><BR>
 *          この信号に与えられたパルスの幅に応じた角度で静止します。<BR>
 *          ごく一般的なサーボモータではパルスの周期は20msで、与えるパルスの幅が544usの場合に角度は0°となり、
 *          パルスの幅が2400usの場合に角度は180°となります。角度とパルス幅の関係は自由に設定でき、
 *          パルス幅が長ければながいほど回転角度が大きくなります。<BR>
 *          このライブラリをC++で使いやすくしたものが servo.h で定義される Servo クラスです。
 * @todo	このライブラリはRX63N用に作られてしまったのでRX62Nでは使えない。RX62Nでも使えるようにしなければならない。
 ******************************************************************************/

#include "tkdn_hal.h"

#define MIN_PULSE_WIDTH       544
#define MAX_PULSE_WIDTH       2400

//#define SERVO_MIN() (MIN_PULSE_WIDTH - min * 4)
//#define SERVO_MAX() (MAX_PULSE_WIDTH - max * 4)

#ifdef __cplusplus
extern "C" {
#endif

typedef struct servo_str
{
	int  ch;
	int  pinnum;
	int  ontime;
	int  angle_value;
	int  min_pulse_width;
	int  max_pulse_width;
} servo_str;

typedef struct servo_str servo_t;

/*********************************************************************//**
 * @brief     サーボライブラリの初期化と、任意のピンへの割り当て
 * @details   最初に呼び出されたとき、MTUを初期化する。<BR>
 *            回転角を0°にしたいときのパルス幅を引数 min で与え、180°にしたいときのパルス幅を引数 max で与える。<BR>
 *            同じ番号のピンを指定して二回以上呼び出すと、そのピンに関してminとmaxの値が変更される。<BR>
 *            異なる番号のピンを指定して呼び出すと、新しいサーボチャネルが割り当てられる。(最大20個まで)
 * @param[in] servo 初期化したいサーボ構造体へのポインタ
 * @param     pin サーボ信号を出力したいピン番号。指定するピンはライブラリ内部で
 *            出力モードに変更されるので、 gpio_set_pinmode() 関数で出力にしておかなくてもよい。
 * @param     min 角度を0°にしたいときのON時間(単位 us)
 * @param     max 角度を180°のときのON時間(単位 us)
 * @return    成功したらサーボのチャネル番号(0～19)を返す。
 *            失敗したら-1を返す。
 * @note      20個以上のピンにサーボを割り当てようとすると失敗する
 * @note      ライブラリの次のバージョンではサーボ構造体は廃止される予定
 * @note      minとmaxの両方に同じ値を入れるか、minに負の値を設定すると、デフォルト値(min=544,max=2400)が採用される
 **********************************************************************/
int servo_attach(servo_t *servo, int pin,int min,int max);

/*********************************************************************//**
 * @brief     指定された角度に相当する幅のパルスをサーボモータに送る
 * @details   この関数を呼び出すと、指定された回転角になるような幅のパルスが、<BR>
 *            servo_attach() 関数で指定したピンから出力される。
 * @param[in] servo サーボ構造体へのポインタ
 * @param     angle 静止させたい角度 (0-180の範囲)
 * @return    なし
 * @note      ライブラリの次のバージョンではサーボ構造体は廃止される予定
 **********************************************************************/
void servo_write(servo_t *servo, int angle);

/*********************************************************************//**
 * @brief     指定された時間の幅のパルスをサーボモータに送る
 * @details   この関数を呼び出すと、出力パルスの幅を角度ではなく時間で指定できる。<BR>
 *            パルスは servo_attach() 関数で指定したピンから出力される。
 * @param[in] servo サーボ構造体へのポインタ
 * @param     us 出力したいパルスの幅をus単位で指定する。範囲は1～19999。<BR>
 *            0を指定すると出力はOFFになる。
 * @return    なし
 * @note      ライブラリの次のバージョンではサーボ構造体は廃止される予定
 **********************************************************************/
void servo_write_us(servo_t *servo,int us);

/*********************************************************************//**
 * @brief     最後に設定された角度を読み出す
 * @param[in] servo サーボ構造体へのポインタ
 * @return    servo_write() 関数で指定した角度
 * @note      ライブラリの次のバージョンではサーボ構造体は廃止される予定
 **********************************************************************/
int  servo_read(servo_t *servo);

/*********************************************************************//**
 * @brief     サーボの動作を止め、割り込みを禁止する
 * @details   目的のチャネルのサーボ動作を停止し、割り込みを禁止する。<BR>
 *            指定されたピンのみ停止し、他のピンの動作には影響を与えない
 * @param[in] servo サーボ構造体へのポインタ
 * @return    なし
 * @note      ライブラリの次のバージョンではサーボ構造体は廃止される予定
 **********************************************************************/
void servo_detach(servo_t *servo);

#ifdef __cplusplus
 }
#endif

#endif /* TKDN_SERVO_H_ */
