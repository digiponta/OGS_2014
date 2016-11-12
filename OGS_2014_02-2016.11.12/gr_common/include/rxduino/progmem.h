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

#ifndef __H_PROGMEM
#define __H_PROGMEM

/**************************************************************************//**
 * @file    progmem.h
 * @brief   コード領域にデータを格納するためのマクロ定義
 ******************************************************************************/

#ifdef __cplusplus
	extern "C" {
#endif

/*! @def	PROGMEM
	@brief	コード領域にデータを格納する
*/
#define PROGMEM __attribute__ ((section (".text")))

//typedef void          PROGMEM prog_void;     //!< @brief void型
//typedef char          PROGMEM prog_char;     //!< @brief char型
//typedef unsigned char PROGMEM prog_uchar;    //!< @brief unsigned char型
//typedef int8_t        PROGMEM prog_int8_t;   //!< @brief int8_t型
//typedef uint8_t       PROGMEM prog_uint8_t;  //!< @brief uint8_t型
//typedef int16_t       PROGMEM prog_int16_t;  //!< @brief int16_t型
//typedef uint16_t      PROGMEM prog_uint16_t; //!< @brief uint16_t型
//typedef int32_t       PROGMEM prog_int32_t;  //!< @brief int32_t型
//typedef uint32_t      PROGMEM prog_uint32_t; //!< @brief uint32_t型
//typedef int64_t       PROGMEM prog_int64_t;  //!< @brief int64_t型
//typedef uint64_t      PROGMEM prog_uint64_t; //!< @brief uint64_t型

#ifdef __cplusplus
	}
#endif

#endif // __H_PROGMEM

