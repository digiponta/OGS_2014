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

#ifndef __H_TKDN_PWM
#define __H_TKDN_PWM

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************//**
 * @brief	指定したピンからアナログ値(PWM波)を出力します.
 * @details LEDの明るさを変えたいときや,モータの回転スピードを調整したいときに使えます.
 * 			PWM信号の周波数は約490Hzです.<BR>
 *          このライブラリをC++で使いやすくした関数が analogio.h で定義されています。
 * @param[in]	analog_portnum アナログ値を読み込むピン番号
 * 				ボード上のLEDを含む任意のピン番号を指定することができます.最大6ピンまで割り当て可能
 *
 * @return		読み込んだアナログ値
 **********************************************************************/

// 使用できるPWMチャネルは6個までです。
// 早い者勝ちで使われます。pwm_stopを行っても開放されません。
TKDN_HAL
void pwm_output(int analog_portnum,int val8bit);


/*********************************************************************//**
 * @brief		PWMに使用するタイマー設定を行います.pwm_outputを呼び出した際に
 * 				初期化がおこなわれていない場合,自動でこの関数を呼び出すので,こちらの関数を
 * 				明示的に呼び出す必要はありません.
 * @param[in]	なし
 *
 * @return
 **********************************************************************/

// パラメータ freq 周波数 (単位はHz。12Hz～185000Hz)
// 周波数が高いときっと動かない
TKDN_HAL
void pwm_init(int freq);

// 指定されたチャネルのPWMを停止する
// PWMのリソースは開放されない
TKDN_HAL
void pwm_stop(int pinnum);


// 下記の変数はシステムで使うので、ユーザーは書き換えてはいけない
extern int pwmpincount; // 何個のPWMのピンが使われているか

#ifdef __cplusplus
		}
#endif

#endif
