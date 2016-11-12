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

#ifndef TKUSBHOST_H
#define TKUSBHOST_H
/**************************************************************************//**
 * @file    tkusbhost.h
 * @brief   RXマイコンの内蔵USBを利用して、USBホスト機能を実現する
 ******************************************************************************/

#define TIMEOUT         1000  //1000ms
#define TIMEOUT_INFINITE -1

#define DEVICE_DESCRIPTOR_TYPE    0x01
#define CONFIG_DESCRIPTOR_TYPE    0x02
#define STRING_DESCRIPTOR_TYPE    0x03
#define INTERFACE_DESCRIPTOR_TYPE 0x04
#define ENDPOINT_DESCRIPTOR_TYPE  0x05

#ifdef __cplusplus
extern "C" {
#endif

//! @brief デバイスディスクリプタ構造体
typedef struct DeviceDesc_t
{
	unsigned char  bLength;
	unsigned char  bDescriptorType;
	unsigned short bcdUSB;
	unsigned char  bDeviceClass;
	unsigned char  bDeviceSubClass;
	unsigned char  bDeviceProtocol;
	unsigned char  bMaxPacketSize0;
	unsigned short idVendor;
	unsigned short idProduct;
	unsigned short bcdDevice;
	unsigned char  iManufacture;
	unsigned char  iProduct;
	unsigned char  iSerialNumber;
	unsigned char  bNumConfigurations;
} DeviceDesc_t;

//! @brief コンフィグディスクリプタ構造体
typedef struct ConfigDesc_t
{
	unsigned char  bLength;
	unsigned char  bDescriptorType;
	unsigned short wTotalLength;
	unsigned char  bNumInterfaces;
	unsigned char  bConfigurationValue;
	unsigned char  iConfiguraion;
	unsigned char  bmAttributes;
	unsigned char  bMaxPower;
} ConfigDesc_t;

//! @brief エンドポイントディスクリプタ構造体
typedef struct EndpointDesc_t
{
    unsigned char  bLength;
    unsigned char  bDescriptorType;
    unsigned char  bEndpointAddress;
    unsigned char  bmAttributes;
    unsigned short wMaxPacketSize;
    unsigned char  bInterval;
    unsigned char  bRefresh;
    unsigned char  bSynchAddress;
} EndpointDesc_t;

//! @brief インタフェースディスクリプタ構造体
typedef struct InterfaceDesc_t
{
    unsigned char  bLength;
    unsigned char  bDescriptorType;
    unsigned char  bInterfaceNumber;
    unsigned char  bAlternateSetting;
    unsigned char  bNumEndpoints;
    unsigned char  bInterfaceClass;
    unsigned char  bInterfaceSubClass;
    unsigned char  bInterfaceProtocol;
    unsigned char  iInterface;
} InterfaceDesc_t;

//! @brief USBホストの情報が格納された構造体
typedef struct USBHostInfo_t
{
	DeviceDesc_t    DeviceDesc;    //!< @brief ターゲットデバイスのデバイスディスクリプタ
	ConfigDesc_t    ConfigDesc;    //!< @brief ターゲットデバイスのコンフィグディスクリプタ
	EndpointDesc_t  EndpointDesc;  //!< @brief ターゲットデバイスのエンドポイントディスクリプタ
	InterfaceDesc_t InterfaceDesc; //!< @brief ターゲットデバイスのインタフェースディスクリプタ
	unsigned short  LangId;        //!< @brief ターゲットデバイスの言語ID
	unsigned char   FullSpeed;     //!< @brief 1:Fullspeed, 0:Lowspeed
	unsigned char   FlagAttach;    //!< @brief 
	unsigned char   DCPMaxSize;    //!< @brief デフォルトコントロールパイプの最大サイズ
} USBHostInfo_t;

//! @brief USBホスト関数が返すエラーコード
typedef enum TKUSBH_RESULT
{
	TKUSBH_OK      = 0, //!< @brief エラーなし
	TKUSBH_NOSUPPORT,   //!< @brief USBホストはサポートされていない
	TKUSBH_DISCONNECT,  //!< @brief ターゲットが接続されていない
	TKUSBH_NOINIT,      //!< @brief 初期化されていない
	TKUSBH_TIMEOUT,     //!< @brief タイムアウト(NAK)
	TKUSBH_STALL,       //!< @brief STALLが返された
	TKUSBH_ERROR,       //!< @brief その他のエラー
} TKUSBH_RESULT;

extern USBHostInfo_t USBHostInfo;

/*********************************************************************//**
 * @brief GR-SAKURAのUSBホスト初期化時に、IO2(USB0_DRPD)とIO5(USB0_DPRPD)をどう扱うかを決める
 *         - 0: GPIOのままであり、プログラムで自由に使用できる。(デフォルト)
 *              この場合、基板裏面のJ13,J15をジャンパすること。
 *         - 1: 周辺機器モードにし、CPU内部でプルダウンする(USBホストの規格としては正しい動作)
 *              この場合、基板裏面のJ12,J14をジャンパすること。
 * @note    この関数はH24/8/2に、V1.01への更新で追加された
 * @warning この変数は、 tkusbh_init() を呼び出す前に設定すること
 **********************************************************************/
extern int gUsbHostGpioPulldown; 

/****************************************************************************************
                   USB Hostの関数
****************************************************************************************/

/*********************************************************************//**
 * @brief     USBホストモジュールを初期化する。
 * @note      GR-SAKURAのUSBホストモード使用時にIO2とIO5をどうするかは、
 *            変数 @ref gUsbHostGpioPulldown によって設定する。
 * @return    成功すると TKUSBH_OK を返す。<BR>USBホストをサポートしていないボードでは TKUSB_NOSUPPORT を返す
 * @warning   USB仮想COMポートをUSBホストを同じポートで開くことはできない
 **********************************************************************/
TKUSBH_RESULT tkusbh_init(void);

/*********************************************************************//**
 * @brief     ターゲットが接続されているかどうかを調べる
 * @return    接続されていれば TKUSBH_OK を返す。<BR>接続されていなければ TKUSBH_DISCONNECT を返す。
 **********************************************************************/
TKUSBH_RESULT tkusbh_is_connected();

/*********************************************************************//**
 * @brief     ターゲットに接続する
 * @param     timeout_ms 接続をタイムアウトまでの時間。ms単位で指定する。<BR>-1を指定すると無限に待つ。
 * @return    成功したら TKUSBH_OK を返す。<BR>
 *            タイムアウトしたら TKUSBH_TIMEOUT を返す。<BR>
 *            何らかの接続エラーが発生して失敗したら TKUSBH_ERROR を返す。<BR>
 *            USBホストをサポートしていないボードではTKUSB_NOSUPPORTを返す
 * @note      タイムアウトは実装されていないかもしれない。
 **********************************************************************/
TKUSBH_RESULT tkusbh_connect(int timeout_ms);

/*********************************************************************//**
 * @brief     ターゲットに接続する。ただしenumerationはSET_ADDRESSまでしか実行しない。
 * @param     timeout_ms 接続をタイムアウトまでの時間。ms単位で指定する。<BR>-1を指定すると無限に待つ。
 * @return    成功したら TKUSBH_OK を返す。<BR>
 *            タイムアウトしたら TKUSBH_TIMEOUT を返す。<BR>
 *            何らかの接続エラーが発生して失敗したら TKUSBH_ERROR を返す。<BR>
 *            USBホストをサポートしていないボードではTKUSB_NOSUPPORTを返す
 * @note      タイムアウトは実装されていないかもしれない。
 **********************************************************************/
TKUSBH_RESULT tkusbh_halfway_connect(int timeout_ms);

/*********************************************************************//**
 * @brief     ターゲットを切断する。切断されるまで待つ。
 * @param     timeout_ms タイムアウトはms単位で指定する。-1を指定すると無限に待つ。
 * @return    成功したら TKUSBH_DISCONNECT を返す。<BR>
 *            タイムアウトしたら TKUSBH_TIMEOUT を返す。<BR>
 *            USBホストをサポートしていないボードではTKUSB_NOSUPPORTを返す
 **********************************************************************/
TKUSBH_RESULT tkusbh_disconnect(int timeout_ms);

/*********************************************************************//**
 * @brief     接続されているターゲットのディスクリプタを取得する
 * @param     type ディスクリプタのタイプ (USB規格で定義されている値)
 * @param     index 取得したいディスクリプタのインデックス値
 * @param     buf 取得したディスクリプタが格納されるバッファへのポインタ
 * @param     size バッファのサイズ
 * @return    成功したら取得したディスクリプタの長さを返す<BR>
 *            失敗(STALL)したら-1を返す
 * @note      指定したsizeよりも実際のディスクリプタのほうが長ければ切り捨てられる
 **********************************************************************/
int  tkusbh_get_descriptor(unsigned char type,unsigned char index, void *buf, int size);

/*********************************************************************//**
 * @brief     接続されているターゲットのストリングディスクリプタを取得する
 * @param     index 取得したいストリングディスクリプタのインデックス
 * @param     langid 言語ID。 USBHostInfo.landId を指定すること。
 * @param     buf 取得したディスクリプタが格納されるバッファへのポインタ
 * @param     buflen バッファのサイズ
 * @return    成功したら取得したディスクリプタの長さを返す。<BR>
 *            失敗(STALL)したら-1を返す
 * @note      指定したbuflenよりも実際のディスクリプタのほうが長ければ切り捨てられる
 **********************************************************************/
int  tkusbh_get_string(unsigned short index, unsigned short langid, char *buf,int buflen);

/*********************************************************************//**
 * @brief     コントロールトランザクションを発行する
 * @param     req 送信するreqフィールド
 * @param     val 送信するvalフィールド
 * @param     index 送信するindexフィールド
 * @param     len 送信するlenフィールド
 * @param     buf 送受信するデータが格納されたバッファ
 * @param     timeout タイムアウトするまでの時間。ms単位で指定する。<BR>-1を指定すると無限に待つ。
 * @return    成功したら送受信したデータの長さを返す。<BR>
 *            失敗(STALL)したら-1を返す
 **********************************************************************/
int  tkusbh_control_msg(unsigned short req,unsigned short val,
                        unsigned short index,unsigned short len,
                        unsigned char *buf, int timeout);

/*********************************************************************//**
 * @brief     SET CONFIGURATIONを実行する
 * @param     configuration コンフィギュレーション番号
 * @return    成功したら、TKUSBH_OKを返す。<BR>
 *            失敗(STALL)したらTKUSBH_ERRを返す。<BR>
 *            USBホストをサポートしていないボードではTKUSB_NOSUPPORTを返す
 **********************************************************************/
TKUSBH_RESULT tkusbh_set_configuration(int configuration);

/*********************************************************************//**
 * @brief     バルクOUT転送を実行する
 * @param     ep エンドポイント番号
 * @param     bytes 送信するデータが格納されたバッファ
 * @param     size 送信するデータの長さ
 * @param     timeout タイムアウトするまでの時間。ms単位で指定する。<BR>-1を指定すると無限に待つ。
 * @return    成功したら送信したデータの長さを返す。<BR>
 *            失敗(STALL)したら-1を返す
 * @warning   現在のバージョンではにより、使用できるエンドポイントは１種類
 **********************************************************************/
int  tkusbh_bulk_write(int ep, unsigned char *bytes, int size,int timeout);

/*********************************************************************//**
 * @brief     バルクIN転送を実行する
 * @param     ep エンドポイント番号
 * @param     bytes 受信したデータが格納されるバッファ
 * @param     size 受信したいデータの最大長さ
 * @param     timeout タイムアウトするまでの時間。ms単位で指定する。<BR>-1を指定すると無限に待つ。
 * @return    成功したら受信したデータの長さを返す。<BR>
 *            失敗(STALL)したら-1を返す
 * @warning   現在のバージョンではにより、使用できるエンドポイントは１種類
 **********************************************************************/
int  tkusbh_bulk_read(int ep, unsigned char *bytes, int size,int timeout);

//! @brief インタラプト転送のタイプ
typedef enum {
	INTERRUPT_IN, //!< @brief インタラプトIN転送
	INTERRUPT_OUT //!< @brief インタラプトOUT転送
} INTTRANS_TYPE;

/*********************************************************************//**
 * @brief     インタラプト転送を行う
 * @details   この関数を呼ぶと、インタラプト転送がシステムに登録され、自動的にINまたはOUTパケットが送出される。<BR>
 *            ただし、受信バッファに空きがない場合や、送信バッファにデータがない場合には発行されないので、<BR>
 *            tkusbh_interrupt_write() や tkusbh_interrupt_read() を使って適宜データを補充したり読み出さなければ<BR>
 *            連続してインタラプト転送が行われない。
 * @param     ep エンドポイント番号
 * @param     time 転送間隔 (単位 ms)
 * @param     type インタラプト転送の種類
 * @param     callback インタラプト転送が発行されたときに呼び出されるユーザ関数(この機能は未実装)
 **********************************************************************/
void tkusbh_start_interrupt_trans(int ep, int time,INTTRANS_TYPE type, void *callback);

/*********************************************************************//**
 * @brief     インタラプトOUT転送で送信されるデータを登録する
 * @param     ep エンドポイント番号
 * @param     buf 送信するデータが格納されたバッファ
 * @param     size 送信するデータの長さ
 * @return    成功したらデータの長さを返す。
 * @warning   現在のバージョンでは使用できるエンドポイントは１種類
 **********************************************************************/
int  tkusbh_interrupt_write(int ep, unsigned char *buf, int size);

/*********************************************************************//**
 * @brief     インタラプトIN転送で受信したデータを取得する
 * @param     ep エンドポイント番号
 * @param     buf 受信したデータが格納されるバッファ
 * @param     size 受信したいデータの最大長さ
 * @return    成功したら受信したデータの長さを返す。<BR>
 *            失敗(STALL)したら-1を返す
 * @warning   現在のバージョンでは使用できるエンドポイントは１種類
 **********************************************************************/
int  tkusbh_interrupt_read(int ep, unsigned char *buf, int size);


// 以下の関数はまだ作っていない
// int  tkusbh_clear_halt(unsigned int ep);
// int  tkusbh_resetep(unsigned int ep);
// int  tkusbh_reset();

/****************************************************************************************
                   USBホストユーティリティ
****************************************************************************************/

#ifdef __cplusplus
 }
#endif

#endif
