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

#ifndef __H_TKDN_TONE
#define __H_TKDN_TONE
/**************************************************************************//**
 * @file    tkdn_tone.h
 * @brief   任意の周波数の矩形波を出して、圧電ブザーなどから音を鳴らすためのライブラリ
 * @details このライブラリはCMT1～CMT3を使用し、最大3つのポートで同時に音を鳴らすことができる。
 * @todo    CMTのカウントクロックは、
 *          出力したい矩形波の周波数が50Hz、200Hz、800Hzで切り替わるので、
 *          その近辺で音階の調整が連続的に行えるかどうかは検証しなければならない。
 ******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************//**
 * @brief     任意のポートから矩形波を出力する
 * @param     pinnum 矩形波を出力したいピン番号。
 * @param     frequency 周波数。単位はHz
 * @param     duration 矩形波を出力する時間をms単位で指定する。
 * @note      引数durationに0以外を指定すると、指定した時間が経過するまでこの関数は制御を返さない。
 * @todo      この関数はRX62Nでは使えない。RX62Nに対応させることが急務。
 **********************************************************************/
void tone_start(int pinnum,int frequency, int duration);

/*********************************************************************//**
 * @brief     任意のポートから矩形波を出力する(チャネル指定あり)
 * @details   この関数を呼び出すと、最大3つのチャネルで矩形波を出すことができる
 * @param     pinnum 矩形波を出力したいピン番号。
 * @param     frequency 周波数。単位はHz
 * @param     duration 矩形波を出力する時間をms単位で指定する。
 * @param     ch 矩形波を出すチャネル番号を0～2で指定する。 CMT 1～3を使用することに対応する。
 * @note      引数durationに0以外を指定すると、指定した時間が経過するまでこの関数は制御を返さない。
 * @todo      この関数はRX62Nでは使えない。RX62Nに対応させることが急務。
 **********************************************************************/
void tone_start_ex(int pinnum,int frequency, int duration,int ch);

/*********************************************************************//**
 * @brief     矩形波の出力を停止する
 * @param     pinnum 矩形波を停止したいピン番号。実際には効果がない。
 * @todo      ピン番号を指定して出力を停止できるようにすべき。
 **********************************************************************/
void tone_stop(int pinnum);

#ifdef __cplusplus
		}
#endif

#endif
