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

#ifndef RANDOM_H_
#define RANDOM_H_
/**************************************************************************//**
 * @file    random.h
 * @brief   乱数生成ライブラリ
 ******************************************************************************/

#ifndef __cplusplus
	#error This library can be used with C++.
#endif

/*********************************************************************//**
 * @brief		乱数の種を初期化する。種が同じ場合、毎回同じ順番で乱数が生成される。
 * @param[in]	seed	乱数の種の値
 * @return		なし
 **********************************************************************/
void randomSeed(unsigned int seed);

/*********************************************************************//**
 * @brief		乱数を生成する。
 * @param[in]	なし
 * @note        randomSeedを呼び出していない場合、種の初期値として123459876Lが用いられる。
 * @return		乱数の値(long)
 * @details     計算式は以下のとおり<PRE>
 	int hi,lo,x;
 	x = random_seed;
 	if(x == 0)x = 123459876L;
 	hi = x / 127773L;
 	lo = x % 127773L;
 	x = 16807L * lo - 2836L * hi;
 	if(x < 0)x += 0x7FFFFFFFL;
 	random_seed = x;
 	return (x % ((unsigned long int)0x7FFFFFFFL + 1));</PRE>

 **********************************************************************/
long random(void);

/*********************************************************************//**
 * @brief		上限を指定して乱数を生成する。
 * @param[in]	max_num 乱数の取りうる最大値
 *
 * @note        randomSeedを呼び出していない場合、種の初期値として123459876Lが用いられる。
 * @return		乱数の値(long)
 **********************************************************************/
long random(long max_num);

/*********************************************************************//**
 * @brief		上限および下限を指定して乱数を生成する。
 * @param[in]	min_num 乱数の取りうる最小値
 * @param[in]	max_num 乱数の取りうる最大値
 *
 * @note        randomSeedを呼び出していない場合、種の初期値として123459876Lが用いられる。
 * @return		乱数の値(long)
 **********************************************************************/
long random(long min_num, long max_num);

#endif /* RANDOM_H_ */
