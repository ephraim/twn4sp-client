// ******************************************************************
//
//    File: twn4.sys.h
//    Date: 2015-05-13
// Version: 10
//
// Purpose:
//
// Include file for Apps for TWN4. Define system datatypes, macros
// prototypes.
//
// V2:
// ---
// - Match firmware version 1.23
//
// V3:
// ---
// - Match firmware version 1.40
//
// V4:
// ---
// - Match firmware version 1.41
// - Support new API AT55
//
// V5:
// ---
// - Match firmware version 1.57
//
// V6:
// ---
// - Match firmware version 1.64
// - New functions for API ISO14443
// - Re-arrangement of API ISO7816
// - New sys function GetLastError and new definitions for error codes
// - New sys functions for storage
//
// V7:
// ---
// - Match firmware version 1.68
//
// V8:
// ---
// - Match firmware version 1.70
// - New API FELICA
//
// V9:
// ---
// - Match firmware version 1.82
//
// V10:
// ---
// - Match firmware version 3.00
//
// ******************************************************************

#if !defined(__TWN4_SYS_H__) || defined(__TWN4_SYS_C__)
#ifndef __TWN4_SYS_H__
#define __TWN4_SYS_H__
#endif

// Best viewed with tab width set to 4

// ******************************************************************
// ****** Common Definitions ****************************************
// ******************************************************************

#ifndef __TWN4_SYS_C__

#include <stdint.h>
#include <string.h>

#define true 			1
#define false 			0

typedef unsigned char byte;

#define MAX(a,b)    	((a) > (b) ? (a) : (b))
#define MIN(a,b)    	((a) < (b) ? (a) : (b))
#define ABS(a)      	((a) > 0 ? (a) : (-(a)))

#define ON          	1
#define OFF         	0

#define BYTE0(x)       	((uint8_t) (x)     )
#define BYTE1(x)       	((uint8_t)((x)>> 8))
#define BYTE2(x)       	((uint8_t)((x)>>16))
#define BYTE3(x)       	((uint8_t)((x)>>24))

#define LOBYTE(x)       BYTE0(x)
#define HIBYTE(x)       BYTE1(x)

#define USB_WORD(x)     BYTE0(x),BYTE1(x)
#define USB_DWORD(x)    BYTE0(x),BYTE1(x),BYTE2(x),BYTE3(x)


#endif

// ******************************************************************
// ****** Error Codes ***********************************************
// ******************************************************************

#ifndef __TWN4_SYS_C__

// ------ General Errors --------------------------------------------

#define ERR_NONE						0
#define ERR_OUTOFMEMORY					1
#define ERR_ISALREADYINIT				2
#define ERR_NOTINIT						3
#define ERR_ISALREADYOPEN				4
#define ERR_NOTOPEN						5
#define ERR_RANGE						6
#define ERR_PARAMETER					7
#define ERR_GENERAL                     8

// ------ Storage Errors --------------------------------------------

#define ERR_UNKNOWNSTORAGEID			100
#define ERR_WRONGINDEX					101
#define ERR_FLASHERASE					102
#define ERR_FLASHWRITE					103
#define ERR_SECTORNOTFOUND				104
#define ERR_STORAGEFULL					105
#define ERR_STORAGEINVALID				106
#define ERR_TRANSACTIONLIMIT			107

// ------ File Errors -----------------------------------------------

#define ERR_UNKNOWNFS					200
#define ERR_FILENOTFOUND				201
#define ERR_FILEALREADYEXISTS			202
#define ERR_ENDOFFILE                   203
#define ERR_STORAGENOTFOUND				204
#define ERR_STORAGEALREADYMOUNTED		205
#define ERR_ACCESSDENIED				206
#define ERR_FILECORRUPT					207
#define ERR_INVALIDFILEENV				208
#define ERR_INVALIDFILEID				209
#define ERR_RESOURCELIMIT				210

#endif

// ******************************************************************
// ****** Parameters ************************************************
// ******************************************************************

#ifndef __TWN4_SYS_C__

#define TLV_END							0

#define OPEN_PORTS						1
  #define OPEN_PORT_USB_MSK						0x01
  #define OPEN_PORT_COM1_MSK					0x02
  #define OPEN_PORT_COM2_MSK					0x04
  #define OPEN_PORTS_DEFAULT            		(OPEN_PORT_USB_MSK | OPEN_PORT_COM1_MSK | OPEN_PORT_COM2_MSK)

#define EXECUTE_APP						2
  #define EXECUTE_APP_AUTO						0
  #define EXECUTE_APP_ALWAYS					1
  #define EXECUTE_APP_DEFAULT					EXECUTE_APP_AUTO

#define INDITAG_READMODE				3
  #define INDITAG_READMODE_1					1
  #define INDITAG_READMODE_2					2
  #define INDITAG_READMODE_3					3
  #define INDITAG_READMODE_DEFAULT				INDITAG_READMODE_1

#define COTAG_READMODE					4
  #define COTAG_READMODE_HASH					0
  #define COTAG_READMODE_1						1	// Read 32 bits
  #define COTAG_READMODE_2						2	// Read 48 bits
  #define COTAG_READMODE_DEFAULT				COTAG_READMODE_1

#define COTAG_VERIFY					5
  #define COTAG_VERIFY_OFF						OFF
  #define COTAG_VERIFY_ON						ON
  #define COTAG_VERIFY_DEFAULT					COTAG_VERIFY_ON

#define HONEYTAG_READMODE				6
  #define HONEYTAG_READMODE_HASH				0
  #define HONEYTAG_READMODE_1					1
  #define HONEYTAG_READMODE_DEFAULT				HONEYTAG_READMODE_1

#define ICLASS_READMODE					7
  #define ICLASS_READMODE_UID					0
  #define ICLASS_READMODE_PAC					1
  #define ICLASS_READMODE_DEFAULT				ICLASS_READMODE_UID

#define AT55_BITRATE					11
  #define AT55_BITRATE_DEFAULT          		64

#define AT55_OPTIONS					12
  #define AT55_OPT_SEQUENCEMASK					0x03
  #define AT55_OPT_SEQUENCENONE					0x00
  #define AT55_OPT_SEQUENCETERMINATOR			0x01
  #define AT55_OPT_SEQUENCESTARTMARKER			0x02
  #define AT55_OPTIONS_DEFAULT          		AT55_OPT_SEQUENCENONE

#define CCID_MAXSLOTINDEX				13
  #define CCID_MAXSLOTINDEX_DEFAULT				0

#define HOST_CHANNEL					14

#define HITAG1S_T0						15
  #define HITAG1S_T0_DEFAULT					21
#define HITAG1S_T1						16
  #define HITAG1S_T1_DEFAULT					29
#define HITAG1S_TGAP					17
  #define HITAG1S_TGAP_DEFAULT					10

#define HITAG2_T0						18
  #define HITAG2_T0_DEFAULT						22
#define HITAG2_T1						19
  #define HITAG2_T1_DEFAULT						28
#define HITAG2_TGAP						20
  #define HITAG2_TGAP_DEFAULT					12

#define ISO14443_BITRATE_TX				21
#define ISO14443_BITRATE_RX				22
  #define ISO14443_BITRATE_106					0
  #define ISO14443_BITRATE_212					1
  #define ISO14443_BITRATE_424					2
  #define ISO14443_BITRATE_848					3
  #define ISO14443_BITRATE_DEFAULT          	ISO14443_BITRATE_106

#define HITAG2_READMODE					23
  #define HITAG2_READMODE_1						1
  #define HITAG2_READMODE_2						2
  #define HITAG2_READMODE_DEFAULT				HITAG2_READMODE_1

#define USB_SUPPORTREMOTEWAKEUP			25
  #define USB_SUPPORTREMOTEWAKEUP_OFF			OFF
  #define USB_SUPPORTREMOTEWAKEUP_ON			ON
  #define USB_SUPPORTREMOTEWAKEUP_DEFAULT		USB_SUPPORTREMOTEWAKEUP_OFF

#define EM4102_OPTIONS					26
  #define EM4102_OPTIONS_F64                	0x01
  #define EM4102_OPTIONS_F32                	0x02
  #define EM4102_OPTIONS_DEFAULT				(EM4102_OPTIONS_F64 | EM4102_OPTIONS_F32)

#define EM4150_OPTIONS					27
  #define EM4150_OPTIONS_F64                	0x01
  #define EM4150_OPTIONS_F40                	0x02
  #define EM4150_OPTIONS_F32                	0x04
  #define EM4150_OPTIONS_DEFAULT				(EM4150_OPTIONS_F64 | EM4150_OPTIONS_F40)

#define USB_SERIALNUMBER				28
  #define USB_SERIALNUMBER_OFF					0
  #define USB_SERIALNUMBER_ON					1
  #define USB_SERIALNUMBER_DEFAULT				USB_SERIALNUMBER_OFF

#define USB_KEYBOARDREPEATRATE			29
  #define USB_KEYBOARDREPEATRATE_DEFAULT		10

#define SEOS_TREATMENT					30
  #define SEOS_TREATMENT_DEFAULT				SEOS_TREATMENT_ICLASS
  #define SEOS_TREATMENT_ICLASS					1
  #define SEOS_TREATMENT_ISO14443A          	2

#define SUPPORT_CONFIGCARD				31
  #define SUPPORT_CONFIGCARD_OFF				OFF
  #define SUPPORT_CONFIGCARD_ON					ON
  #define SUPPORT_CONFIGCARD_DEFAULT			OFF

#define USB_VID							32
  #define USB_VID_ELATEC						0x09D8

#define USB_PID							33
  #define USB_PID_KEYBOARD						0x0410
  #define USB_PID_CDC							0x0420
  #define USB_PID_CCID_HID						0x0425
  #define USB_PID_REPORTS						0x0426
  #define USB_PID_CCID_CDC						0x0427
  #define USB_PID_CCID							0x0428

#define ISO14443_3_TDX_CRCCONTROL		34
  #define ISO14443_3_TDX_CRCCTRL_DEFAULT		0x00
  #define ISO14443_3_TDX_CRCCTRL_TX				0x02
  #define ISO14443_3_TDX_CRCCTRL_RX				0x01

#endif

// ******************************************************************
// ****** Invoke System Function ************************************
// ******************************************************************

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreturn-type"

#ifdef __TWN4_SYS_C__

#define xstr(s) str(s)
#define str(s) #s

#undef SYSFUNC
#define SYSFUNC(ApiNo,FuncNo,Prototype)  \
    Prototype                            \
    {                                    \
        __asm("push {r4,r5,lr}");        \
        __asm("mov r4,#" xstr(ApiNo));   \
        __asm("mov r5,#" xstr(FuncNo));  \
        __asm("svc 0x80");               \
        __asm("pop {r4,r5,pc}");         \
    }

#else

typedef struct
{
    unsigned int ApiNo;
    unsigned int FuncNo;
    unsigned int *Param;
    unsigned int *Result;
} TEnvSysCall;

#ifdef MAKEFIRMWARE
#define SYSFUNC(ApiNo,FuncNo,Prototype) Prototype;
#else
#define SYSFUNC(ApiNo,FuncNo,Prototype) Prototype __attribute__( ( naked ) );
#endif

#define API_SYS                 0
#define API_IO                  1
#define API_MEM                 2
#define API_CONV                3
#define API_PERIPH              4
#define API_RF                  5
#define API_TILF                6
#define API_HITAG1S             7
#define API_HITAG2              8
#define API_SM4X00              9
#define API_I2C                 10
#define API_MIFARECLASSIC       11
#define API_MIFAREULTRALIGHT    12
#define API_ISO15693            13
#define API_CRYPTO              14
#define API_DESFIRE             15
#define API_ISO7816				16
#define API_ICLASS				17
#define API_ISO14443			18
#define API_LF					19
#define API_HF					20
#define API_AT55				21
#define API_NFCIP				22
#define API_NFCLLCP				23
#define API_NFCSNEP				24
#define API_EM4150				25
#define API_FILESYS				26
#define API_MIFAREPLUS			27
#define API_ADC					28
#define API_FELICA				29

#define API_SLE44XX				31
#define API_NTAG				32
#define API_SRX					33
#define API_SAMAVX				34
#define API_EM4102              35
#define API_SPI                 36
#define API_BLE                 37
#endif

// ******************************************************************
// ****** System Function ******************************************
// ******************************************************************

#ifndef __TWN4_SYS_C__

#define USBTYPE_NONE			0
#define USBTYPE_CDC				1
#define USBTYPE_KEYBOARD		4

#define DEVTYPE_LEGICNFC 		10
#define DEVTYPE_MIFARENFC 		11

#define WAKEUPMASK(WakeupSource)  (1 << WakeupSource)
#define WAKEUP_SOURCE_NONE      -1
#define WAKEUP_SOURCE_USB       0
#define WAKEUP_SOURCE_COM1      1
#define WAKEUP_SOURCE_COM2      2
#define WAKEUP_SOURCE_TIMEOUT   4
#define WAKEUP_SOURCE_LPCD      5

#define WAKEUP_BY_USB_MSK       WAKEUPMASK(WAKEUP_SOURCE_USB)
#define WAKEUP_BY_COM1_MSK      WAKEUPMASK(WAKEUP_SOURCE_COM1)
#define WAKEUP_BY_COM2_MSK      WAKEUPMASK(WAKEUP_SOURCE_COM2)
#define WAKEUP_BY_TIMEOUT_MSK   WAKEUPMASK(WAKEUP_SOURCE_TIMEOUT)
#define WAKEUP_BY_LPCD_MSK      WAKEUPMASK(WAKEUP_SOURCE_LPCD)

#define SLEEPMODE_MSK			0x0F00
#define SLEEPMODE_SLEEP			0x0000
#define SLEEPMODE_STOP			0x0100

#endif

SYSFUNC(API_SYS, 0,bool SysCall(TEnvSysCall *Env))
SYSFUNC(API_SYS, 1,void Reset(void))
SYSFUNC(API_SYS, 2,void StartBootloader(void))
SYSFUNC(API_SYS, 3,unsigned long GetSysTicks(void))
SYSFUNC(API_SYS, 4,int GetVersionString(char *VersionString,int MaxLen))
SYSFUNC(API_SYS, 5,int GetUSBType(void))
SYSFUNC(API_SYS, 6,int GetDeviceType(void))
SYSFUNC(API_SYS, 7,int Sleep(unsigned long Ticks,unsigned long Flags))
SYSFUNC(API_SYS, 8,void GetDeviceUID(byte *UID))
SYSFUNC(API_SYS, 9,bool SetParameters(const byte *TLV,int ByteCount))
SYSFUNC(API_SYS,10,unsigned int GetLastError(void))
SYSFUNC(API_SYS,11,int Diagnostic(int Mode,const void *In,int InLen,void *Out,int *OutLen,int MaxOutLen))
SYSFUNC(API_SYS,12,bool ProgramApp(const byte *AppData,int AppDataLength))

// ******************************************************************
// ****** Standard I/O Functions ************************************
// ******************************************************************

#ifndef __TWN4_SYS_C__

#define CHANNEL_NONE        0
#define CHANNEL_USB         1		// CDC or keyboard
#define CHANNEL_COM1        2
#define CHANNEL_COM2        3
#define CHANNEL_I2C         4
#define CHANNEL_CCID_DATA   0x10
#define CHANNEL_CCID_CTRL   0x11
#define CHANNEL_SAM1		0x20
#define CHANNEL_SAM2		0x21
#define CHANNEL_SAM3		0x22
#define CHANNEL_SAM4		0x23
#define CHANNEL_SC1			0x28
#define CHANNEL_RNG			0x30
#define CHANNEL_BLUETOOTH	0x40

#define DIR_OUT             0
#define DIR_IN              1

#define COM_WORDLENGTH_8        ((byte)8)

#define COM_PARITY_NONE         ((byte)0)
#define COM_PARITY_ODD          ((byte)1)
#define COM_PARITY_EVEN         ((byte)2)

#define COM_STOPBITS_0_5        ((byte)1)
#define COM_STOPBITS_1          ((byte)2)
#define COM_STOPBITS_1_5        ((byte)3)
#define COM_STOPBITS_2          ((byte)4)

#define COM_FLOWCONTROL_NONE    ((byte)0)

typedef struct __attribute__((__packed__))
{
    unsigned long BaudRate;
    byte WordLength;
    byte Parity;
    byte StopBits;
    byte FlowControl;
} TCOMParameters;

#define USB_DEVICE_STATE_DEFAULT        1
#define USB_DEVICE_STATE_ADDRESSED      2
#define USB_DEVICE_STATE_CONFIGURED     3
#define USB_DEVICE_STATE_SUSPENDED      4
#endif

SYSFUNC(API_IO, 0,void WriteByte(int Channel,byte Byte))
SYSFUNC(API_IO, 1,byte ReadByte(int Channel))
SYSFUNC(API_IO, 2,bool TestEmpty(int Channel,int Dir))
SYSFUNC(API_IO, 3,bool TestFull(int Channel,int Dir))
SYSFUNC(API_IO, 4,int  GetBufferSize(int Channel,int Dir))
SYSFUNC(API_IO, 5,int  GetByteCount(int Channel,int Dir))

SYSFUNC(API_IO, 9,bool SetCOMParameters(int Channel,TCOMParameters *COMParameters))
SYSFUNC(API_IO,10,int  GetUSBDeviceState(void))
SYSFUNC(API_IO,11,int  GetHostChannel(void))
SYSFUNC(API_IO,12,void USBRemoteWakeup(void))
SYSFUNC(API_IO,13,int  WriteBytes(int Channel, const byte* Bytes, int ByteCount))
SYSFUNC(API_IO,14,int  ReadBytes(int Channel, byte* Bytes, int ByteCount))

// ******************************************************************
// ****** Memory Functions ******************************************
// ******************************************************************

SYSFUNC(API_MEM, 0,bool CompBytes(const byte *Data1,const byte *Data2,int ByteCount))
SYSFUNC(API_MEM, 1,void CopyBytes(byte *DestBytes,const byte *SourceBytes,int ByteCount))
SYSFUNC(API_MEM, 2,void FillBytes(byte *Dest,byte Value,int ByteCount))
SYSFUNC(API_MEM, 3,void SwapBytes(byte *Data,int ByteCount))
SYSFUNC(API_MEM, 4,bool ReadBit(const byte *Byte,int BitNr))
SYSFUNC(API_MEM, 5,void WriteBit(byte *Byte,int BitNr,bool Value))
SYSFUNC(API_MEM, 6,void CopyBit(byte *Dest,int DestBitNr,const byte *Source,int SourceBitNr))
SYSFUNC(API_MEM, 7,bool CompBits(const byte *Data1,int Data1StartBit,const byte *Data2,int Data2StartBit,int BitCount))
SYSFUNC(API_MEM, 8,void CopyBits(byte *DestBits,int StartDestBit,const byte *SourceBits,int StartSourceBit,int BitCount))
SYSFUNC(API_MEM, 9,void FillBits(byte *Dest,int StartBit,bool Value,int BitCount))
SYSFUNC(API_MEM,10,void SwapBits(byte *Data,int StartBit,int BitCount))
SYSFUNC(API_MEM,11,int  CountBits(const byte *Data,int StartBit,bool Value,int BitCount))

// ******************************************************************
// ****** Conversion Functions **************************************
// ******************************************************************

SYSFUNC(API_CONV, 0,int ScanHexChar(byte Char))
SYSFUNC(API_CONV, 1,int ScanHexString(byte *ASCII,int ByteCount))
SYSFUNC(API_CONV, 2,int ConvertBinaryToString(const byte *SourceBits,int StartBit,int BitCnt,char *String,int Radix,int MinDigits,int MaxDigits))

// ******************************************************************
// ****** Peripheral Functions **************************************
// ******************************************************************

#ifndef __TWN4_SYS_C__

// ****** GPIOs *****************************************************

// Bitmasks of GPIOs
#define GPIO0                   0x01
#define GPIO1                   0x02
#define GPIO2                   0x04
#define GPIO3                   0x08
#define GPIO4                   0x10
#define GPIO5                   0x20
#define GPIO6                   0x40
#define GPIO7                   0x80

// GPIO Pullup/Pulldown
#define GPIO_PUPD_NOPULL        0
#define GPIO_PUPD_PULLUP        1
#define GPIO_PUPD_PULLDOWN      2

// GPIO Output Type
#define GPIO_OTYPE_PUSHPULL     0
#define GPIO_OTYPE_OPENDRAIN    1

// ****** Access to LEDs ********************************************

#define REDLED                  GPIO0
#define GREENLED                GPIO1
#define YELLOWLED               GPIO2

#define LEDInit(LEDs)           GPIOConfigureOutputs(LEDs,GPIO_PUPD_NOPULL,GPIO_OTYPE_PUSHPULL)
#define LEDOn(LEDs)             GPIOSetBits(LEDs)
#define LEDOff(LEDs)            GPIOClearBits(LEDs)
#define LEDToggle(LEDs)         GPIOToggleBits(LEDs)
#define LEDBlink(LEDs,TimeOn,TimeOff) GPIOBlinkBits(LEDs,TimeOn,TimeOff)
#define LEDIsOn(LED)            GPIOTestBit(LED)

// ****** Beeper ****************************************************

#define BEEP_FREQUENCY_HIGH     2400
#define BEEP_FREQUENCY_LOW      2057

// ****** Sequencer *************************************************

#define SEQ_FUNC(x)			( x         << 24)
#define SEQ_CTRL(x)			((x | 0x80) << 24)

#define SEQ_SETBITS			SEQ_FUNC(2)
#define SEQ_CLEARBITS		SEQ_FUNC(3)
#define SEQ_TOGGLEBITS		SEQ_FUNC(4)

#define SEQ_STOP			SEQ_CTRL(0)
#define SEQ_WAIT			SEQ_CTRL(1)
#define SEQ_SETCOUNTER		SEQ_CTRL(2)
#define SEQ_JUMP			SEQ_CTRL(3)
#define SEQ_DECJMPNZ		SEQ_CTRL(4)

#endif

SYSFUNC(API_PERIPH, 0,void GPIOConfigureOutputs(int Bits,int PullUpDown,int OutputType))
SYSFUNC(API_PERIPH, 1,void GPIOConfigureInputs(int Bits,int PullUpDown))
SYSFUNC(API_PERIPH, 2,void GPIOSetBits(int Bits))
SYSFUNC(API_PERIPH, 3,void GPIOClearBits(int Bits))
SYSFUNC(API_PERIPH, 4,void GPIOToggleBits(int Bits))
SYSFUNC(API_PERIPH, 5,void GPIOBlinkBits(int Bits,int TimeHi,int TimeLo))
SYSFUNC(API_PERIPH, 6,int GPIOTestBit(int Bit))
SYSFUNC(API_PERIPH, 7,void Beep(int Volume,int Frequency,int OnTime,int OffTime))
SYSFUNC(API_PERIPH, 8,void DiagLEDOn(void))
SYSFUNC(API_PERIPH, 9,void DiagLEDOff(void))
SYSFUNC(API_PERIPH,10,void DiagLEDToggle(void))
SYSFUNC(API_PERIPH,11,bool DiagLEDIsOn(void))
SYSFUNC(API_PERIPH,12,void SendWiegand(int GPIOData0,int GPIOData1,int PulseTime,int IntervalTime,byte *Bits,int BitCount))
SYSFUNC(API_PERIPH,13,void SendOmron(int GPIOClock,int GPIOData,int T1,int T2,int T3,byte *Bits,int BitCount))
SYSFUNC(API_PERIPH,14,bool GPIOPlaySequence(const int *NewSequence,int ByteCount))
SYSFUNC(API_PERIPH,15,void GPIOStopSequence(void))

// ******************************************************************
// ****** RF Tag Functions ******************************************
// ******************************************************************

#ifndef __TWN4_SYS_C__

#define NOTAG               0
// LF Tags
#define LFTAG_EM4102        0x40    // "EM4x02/CASI-RUSCO" (=IDRO_A)
#define LFTAG_HITAG1S       0x41    // "HITAG 1/HITAG S"   (=IDRW_B)
#define LFTAG_HITAG2        0x42    // "HITAG 2"           (=IDRW_C)
#define LFTAG_EM4150        0x43    // "EM4x50"            (=IDRW_D)
#define LFTAG_AT5555        0x44    // "T55x7"             (=IDRW_E)
#define LFTAG_ISOFDX        0x45    // "ISO FDX-B"         (=IDRO_G)
#define LFTAG_EM4026        0x46    // N/A                 (=IDRO_H)
#define LFTAG_HITAGU        0x47    // N/A                 (=IDRW_I)
#define LFTAG_EM4305        0x48    // N/A                 (=IDRW_K)
#define LFTAG_HIDPROX       0x49	// "HID Prox"
#define LFTAG_TIRIS         0x4A	// "ISO HDX/TIRIS"
#define LFTAG_COTAG         0x4B	// "Cotag"
#define LFTAG_IOPROX        0x4C	// "ioProx"
#define LFTAG_INDITAG       0x4D	// "Indala"
#define LFTAG_HONEYTAG      0x4E	// "NexWatch"
#define LFTAG_AWID      	0x4F	// "AWID"
#define LFTAG_GPROX      	0x50	// "G-Prox"
#define LFTAG_PYRAMID      	0x51	// "Pyramid"
#define LFTAG_KERI      	0x52	// "Keri"
#define LFTAG_DEISTER		0x53	// N/A
#define LFTAG_CARDAX		0x54	// N/A
#define LFTAG_NEDAP			0x55	// N/A
// HF Tags
#define HFTAG_MIFARE        0x80	// "ISO14443A/MIFARE"
#define HFTAG_ISO14443B     0x81	// "ISO14443B"
#define HFTAG_ISO15693      0x82	// "ISO15693"
#define HFTAG_LEGIC         0x83	// "LEGIC"
#define HFTAG_HIDICLASS     0x84	// "HID iCLASS"
#define HFTAG_FELICA        0x85	// "FeliCa"
#define HFTAG_SRX           0x86	// "SRX"
#define HFTAG_NFCP2P        0x87	// "NFC Peer-to-Peer"
#define HFTAG_BLE        	0x88	// "Bluetooth Low Energy"

#define TAGMASK(Tagtype)    (1 << (Tagtype & 0x1F))

#define ALL_LFTAGS          0xFFFFFFFF
#define ALL_HFTAGS          0xFFFFFFFF

#endif

SYSFUNC(API_RF, 0,bool SearchTag(int *TagType,int *IDBitCount,byte *ID,int MaxIDBytes))
SYSFUNC(API_RF, 1,void SetRFOff(void))
SYSFUNC(API_RF, 2,void SetTagTypes(unsigned int LFTagTypes,unsigned int HFTagTypes))
SYSFUNC(API_RF, 3,void GetTagTypes(unsigned int *LFTagTypes,unsigned int *HFTagTypes))
SYSFUNC(API_RF, 4,void GetSupportedTagTypes(unsigned int *LFTagTypes,unsigned int *HFTagTypes))

// ******************************************************************
// ****** TILF Functions ********************************************
// ******************************************************************

SYSFUNC(API_TILF, 0,bool TILF_SearchTag(int *IDBitCount,byte *ID,int MaxIDBytes))
SYSFUNC(API_TILF, 1,bool TILF_ChargeOnlyRead(byte *ReadData))
SYSFUNC(API_TILF, 2,bool TILF_ChargeOnlyReadLo(byte *ReadData))
SYSFUNC(API_TILF, 3,bool TILF_SPProgramPage(const byte *WriteData,byte *ReadData))
SYSFUNC(API_TILF, 4,bool TILF_SPProgramPageLo(const byte *WriteData,byte *ReadData))
SYSFUNC(API_TILF, 5,bool TILF_MPGeneralReadPage(int Address,byte *ReadData))
SYSFUNC(API_TILF, 6,bool TILF_MPSelectiveReadPage(int Address,const byte *SelectiveAddress,byte *ReadData))
SYSFUNC(API_TILF, 7,bool TILF_MPProgramPage(int Address,const byte *WriteData,byte *ReadData))
SYSFUNC(API_TILF, 8,bool TILF_MPSelectiveProgramPage(int Address,const byte *SelectiveAddress,const byte *WriteData,byte *ReadData))
SYSFUNC(API_TILF, 9,bool TILF_MPLockPage(int Address,byte *ReadData))
SYSFUNC(API_TILF,10,bool TILF_MPSelectiveLockPage(int Address,const byte *SelectiveAddress,byte *ReadData))
SYSFUNC(API_TILF,11,bool TILF_MPGeneralReadPageLo(int Address,byte *ReadData))
SYSFUNC(API_TILF,12,bool TILF_MPSelectiveReadPageLo(int Address,const byte *SelectiveAddress,byte *ReadData))
SYSFUNC(API_TILF,13,bool TILF_MPProgramPageLo(int Address,const byte *WriteData,byte *ReadData))
SYSFUNC(API_TILF,14,bool TILF_MPSelectiveProgramPageLo(int Address,const byte *SelectiveAddress,const byte *WriteData,byte *ReadData))
SYSFUNC(API_TILF,15,bool TILF_MPLockPageLo(int Address,byte *ReadData))
SYSFUNC(API_TILF,16,bool TILF_MPSelectiveLockPageLo(int Address,const byte *SelectiveAddress,byte *ReadData))
SYSFUNC(API_TILF,17,bool TILF_MUGeneralReadPage(int Address,byte *ReadData))
SYSFUNC(API_TILF,18,bool TILF_MUSelectiveReadPage(int Address,int SelectiveAddress,byte *ReadData))
SYSFUNC(API_TILF,19,bool TILF_MUSpecialReadPage(int Address,const byte *SpecialAddress1,const byte *SpecialAddress2,byte *ReadData))
SYSFUNC(API_TILF,20,bool TILF_MUProgramPage(int Address,const byte *WriteData,byte *ReadData))
SYSFUNC(API_TILF,21,bool TILF_MUSelectiveProgramPage(int Address,int SelectiveAddress,const byte *WriteData,byte *ReadData))
SYSFUNC(API_TILF,22,bool TILF_MUSpecialProgramPage(int Address,const byte *SpecialAddress1,const byte *SpecialAddress2,const byte *WriteData,byte *ReadData))
SYSFUNC(API_TILF,23,bool TILF_MULockPage(int Address,byte *ReadData))
SYSFUNC(API_TILF,24,bool TILF_MUSelectiveLockPage(int Address,int SelectiveAddress,byte *ReadData))
SYSFUNC(API_TILF,25,bool TILF_MUSpecialLockPage(int Address,const byte *SpecialAddress1,const byte *SpecialAddress2,byte *ReadData))

// ******************************************************************
// ****** Hitag 1/S Functions ***************************************
// ******************************************************************

SYSFUNC(API_HITAG1S, 0,bool Hitag1S_SearchTag(int *IDBitCount,byte *ID,int MaxIDBytes))
SYSFUNC(API_HITAG1S, 1,bool Hitag1S_ReadPage(int PageAddress,byte *Page))
SYSFUNC(API_HITAG1S, 2,bool Hitag1S_ReadBlock(int BlockAddress,byte *Block,byte *BytesRead))
SYSFUNC(API_HITAG1S, 3,bool Hitag1S_WritePage(int PageAddress,const byte *Page))
SYSFUNC(API_HITAG1S, 4,bool Hitag1S_WriteBlock(int BlockAddress,const byte *Block,byte *BytesWritten))
SYSFUNC(API_HITAG1S, 5,bool Hitag1S_Halt(void))

// ******************************************************************
// ****** Hitag 2 Functions *****************************************
// ******************************************************************

SYSFUNC(API_HITAG2, 0,bool Hitag2_SearchTag(int *IDBitCount,byte *ID,int MaxIDBytes))
SYSFUNC(API_HITAG2, 1,bool Hitag2_ReadPage(int PageAddress,byte *Page))
SYSFUNC(API_HITAG2, 2,bool Hitag2_WritePage(int PageAddress,const byte *Page))
SYSFUNC(API_HITAG2, 3,bool Hitag2_Halt(void))
SYSFUNC(API_HITAG2, 4,void Hitag2_SetPassword(const byte *Password))

// ******************************************************************
// ****** SM4X00 Functions ******************************************
// ******************************************************************

#ifndef __TWN4_SYS_C__

// Provide macros for obsolete name of function
#define SM4200_GenericRaw(TXData,TXDataLength,RXData,RXDataLength,MaxRXDataLength,Timeout)  SM4X00_GenericRaw(TXData,TXDataLength,RXData,RXDataLength,MaxRXDataLength,Timeout)
#define SM4200_Generic(TXData,TXDataLength,RXData,RXDataLength,MaxRXDataLength,Timeout)     SM4X00_Generic(TXData,TXDataLength,RXData,RXDataLength,MaxRXDataLength,Timeout)
#define SM4200_StartBootloader(TLV,TLVLength,MaxTLVLength)                                  SM4X00_StartBootloader(TLV,TLVLength,MaxTLVLength)
#define SM4200_EraseFlash()                                                                 SM4X00_EraseFlash()
#define SM4200_ProgramBlock(Data,Done)                                                      SM4X00_ProgramBlock(Data,Done)

#endif

SYSFUNC(API_SM4X00, 0,bool SM4X00_GenericRaw(const byte *TXData,int TXDataLength,byte *RXData,int *RXDataLength,int MaxRXDataLength,int Timeout))
SYSFUNC(API_SM4X00, 1,bool SM4X00_Generic(const byte *TXData,int TXDataLength,byte *RXData,int *RXDataLength,int MaxRXDataLength,int Timeout))
SYSFUNC(API_SM4X00, 2,bool SM4X00_StartBootloader(byte *TLV,int *TLVLength,int MaxTLVLength))
SYSFUNC(API_SM4X00, 3,bool SM4X00_EraseFlash(void))
SYSFUNC(API_SM4X00, 4,bool SM4X00_ProgramBlock(byte *Data,bool *Done))

// ******************************************************************
// ****** I2C Functions *********************************************
// ******************************************************************

#ifndef __TWN4_SYS_C__

#define I2CMODE_MASTER              0x0000
#define I2CMODE_SLAVE               0x1000
#define I2CMODE_CHANNEL             0x2000
#define I2CMODE_ADDRESS_MASK        0x007F

#endif

SYSFUNC(API_I2C, 0,bool I2CInit(int Mode))
SYSFUNC(API_I2C, 1,void I2CDeInit(void))
SYSFUNC(API_I2C, 2,void I2CMasterStart(void))
SYSFUNC(API_I2C, 3,void I2CMasterStop(void))
SYSFUNC(API_I2C, 4,void I2CMasterTransmitByte(byte Byte))
SYSFUNC(API_I2C, 5,byte I2CMasterReceiveByte(void))
SYSFUNC(API_I2C, 6,void I2CMasterBeginWrite(int Address))
SYSFUNC(API_I2C, 7,void I2CMasterBeginRead(int Address))
SYSFUNC(API_I2C, 8,void I2CMasterSetAck(bool SetOn))

// ******************************************************************
// ****** Mifare Classic Functions **********************************
// ******************************************************************

#ifndef __TWN4_SYS_C__

#define KEYA    0
#define KEYB    1

#endif

SYSFUNC(API_MIFARECLASSIC, 0, bool MifareClassic_Login(const byte* Key, byte KeyType, int Sector))
SYSFUNC(API_MIFARECLASSIC, 1, bool MifareClassic_ReadBlock(int Block, byte* Data))
SYSFUNC(API_MIFARECLASSIC, 2, bool MifareClassic_WriteBlock(int Block, const byte* Data))
SYSFUNC(API_MIFARECLASSIC, 3, bool MifareClassic_ReadValueBlock(int Block, int* Value))
SYSFUNC(API_MIFARECLASSIC, 4, bool MifareClassic_WriteValueBlock(int Block, int Value))
SYSFUNC(API_MIFARECLASSIC, 5, bool MifareClassic_IncrementValueBlock(int Block, int Value))
SYSFUNC(API_MIFARECLASSIC, 6, bool MifareClassic_DecrementValueBlock(int Block, int Value))
SYSFUNC(API_MIFARECLASSIC, 7, bool MifareClassic_CopyValueBlock(int SourceBlock, int DestBlock))

// ******************************************************************
// ****** Mifare Ultralight Functions *******************************
// ******************************************************************

SYSFUNC(API_MIFAREULTRALIGHT, 0, bool MifareUltralight_ReadPage(int Page, byte* Data))
SYSFUNC(API_MIFAREULTRALIGHT, 1, bool MifareUltralight_WritePage(int Page, const byte* Data))
SYSFUNC(API_MIFAREULTRALIGHT, 2, bool MifareUltralightC_Authenticate(const byte* Key))
SYSFUNC(API_MIFAREULTRALIGHT, 3, bool MifareUltralightC_SAMAuthenticate(int KeyNo, int KeyVersion, const byte* DIVInput, int DIVByteCnt))
SYSFUNC(API_MIFAREULTRALIGHT, 4, bool MifareUltralightC_WriteKeyFromSAM(int KeyNo, int KeyVersion, const byte* DIVInput, int DIVByteCnt))
SYSFUNC(API_MIFAREULTRALIGHT, 5, bool MifareUltralightEV1_FastRead(int StartPage, int NumberOfPages, byte* Data))
SYSFUNC(API_MIFAREULTRALIGHT, 6, bool MifareUltralightEV1_IncCounter(int CounterAddr, int IncrValue))
SYSFUNC(API_MIFAREULTRALIGHT, 7, bool MifareUltralightEV1_ReadCounter(int CounterAddr, int* CounterValue))
SYSFUNC(API_MIFAREULTRALIGHT, 8, bool MifareUltralightEV1_ReadSig(byte* ECCSig))
SYSFUNC(API_MIFAREULTRALIGHT, 9, bool MifareUltralightEV1_GetVersion(byte* Version))
SYSFUNC(API_MIFAREULTRALIGHT, 10, bool MifareUltralightEV1_PwdAuth(const byte* Password, const byte* PwdAck))
SYSFUNC(API_MIFAREULTRALIGHT, 11, bool MifareUltralightEV1_CheckTearingEvent(int CounterAddr, byte* ValidFlag))

// ******************************************************************
// ****** ISO15693 Functions ****************************************
// ******************************************************************

#ifndef __TWN4_SYS_C__

// ISO15693 Tag Types
#define ISO15693_TAGTYPE_ICODESL2			0x00
#define ISO15693_TAGTYPE_ICODESL2S			0x01
#define ISO15693_TAGTYPE_UNKNOWNNXP			0x0F
#define ISO15693_TAGTYPE_TAGITHFIPLUSINLAY	0x10
#define ISO15693_TAGTYPE_TAGITHFIPLUSCHIP	0x11
#define ISO15693_TAGTYPE_TAGITHFISTD		0x12
#define ISO15693_TAGTYPE_TAGITHFIPRO		0x13
#define ISO15693_TAGTYPE_UNKNOWNTI			0x1F
#define ISO15693_TAGTYPE_MB89R118			0x20
#define ISO15693_TAGTYPE_MB89R119			0x21
#define ISO15693_TAGTYPE_MB89R112			0x22
#define ISO15693_TAGTYPE_UNKNOWNFUJI		0x2F
#define ISO15693_TAGTYPE_24LR16				0x30
#define ISO15693_TAGTYPE_24LR64				0x31
#define ISO15693_TAGTYPE_LRI1K				0x40
#define ISO15693_TAGTYPE_LRI2K				0x41
#define ISO15693_TAGTYPE_LRIS2K				0x42
#define ISO15693_TAGTYPE_LRIS64K			0x43
#define ISO15693_TAGTYPE_UNKNOWNST			0x4F
#define ISO15693_TAGTYPE_SRF55V02P			0x50
#define ISO15693_TAGTYPE_SRF55V10P			0x51
#define ISO15693_TAGTYPE_SRF55V02S			0x52
#define ISO15693_TAGTYPE_SRF55V10S			0x53
#define ISO15693_TAGTYPE_UNKNOWNINFINEON	0x5F
#define ISO15693_TAGTYPE_UNKNOWN			0xFF

typedef struct __attribute__((__packed__))
{
	byte DSFID_Present:1;
	byte AFI_Present:1;
	byte VICC_Memory_Size_Present:1;
	byte IC_Reference_Present:1;
	byte Res1:4;
	byte UID[8];
	byte DSFID;
	byte AFI;
	byte BlockSize;
	uint16_t Number_of_Blocks;
	byte IC_Reference;
} TISO15693_SystemInfo;

#endif

SYSFUNC(API_ISO15693, 0, bool ISO15693_GenericCommand(byte Flags, byte Command, byte* Data, int* Length, int BufferSize))
SYSFUNC(API_ISO15693, 1, bool ISO15693_GetSystemInformation(TISO15693_SystemInfo* SystemInfo))
SYSFUNC(API_ISO15693, 2, bool ISO15693_GetSystemInformationExt(TISO15693_SystemInfo* SystemInfo))
SYSFUNC(API_ISO15693, 3, int  ISO15693_GetTagTypeFromUID(byte* UID))
SYSFUNC(API_ISO15693, 4, int  ISO15693_GetTagTypeFromSystemInfo(TISO15693_SystemInfo* SystemInfo))
SYSFUNC(API_ISO15693, 5, bool ISO15693_ReadSingleBlock(int BlockNumber, byte* BlockData, int* Length, int BufferSize))
SYSFUNC(API_ISO15693, 6, bool ISO15693_ReadSingleBlockExt(int BlockNumber, byte* BlockData, int* Length, int BufferSize))
SYSFUNC(API_ISO15693, 7, bool ISO15693_WriteSingleBlock(int BlockNumber, const byte* BlockData, int Length))
SYSFUNC(API_ISO15693, 8, bool ISO15693_WriteSingleBlockExt(int BlockNumber, const byte* BlockData, int Length))

// ******************************************************************
// ****** Crypto Functions ******************************************
// ******************************************************************

#ifndef __TWN4_SYS_C__

#define CRYPTO_ENV0         		0
#define CRYPTO_ENV1         		1
#define CRYPTO_ENV2         		2
#define CRYPTO_ENV3         		3
#define CRYPTO_ENV_CNT      		4

#define CRYPTOMODE_AES128			0
#define CRYPTOMODE_AES192			1
#define CRYPTOMODE_AES256			2
#define CRYPTOMODE_3DES				3
#define CRYPTOMODE_3K3DES			4
#define CRYPTOMODE_CBC_DES			5
#define CRYPTOMODE_CBC_DFN_DES		6
#define CRYPTOMODE_CBC_3DES			7
#define CRYPTOMODE_CBC_DFN_3DES		8
#define CRYPTOMODE_CBC_3K3DES		9
#define CRYPTOMODE_CBC_AES128		10

#endif

SYSFUNC(API_CRYPTO, 0, void Crypto_Init(int CryptoEnv, int CryptoMode, const byte* Key, int KeyByteCnt))
SYSFUNC(API_CRYPTO, 1, void Encrypt(int CryptoEnv, const byte* PlainBlock, byte* CipheredBlock, int BlockByteCnt))
SYSFUNC(API_CRYPTO, 2, void Decrypt(int CryptoEnv, const byte* CipheredBlock, byte* PlainBlock, int BlockByteCnt))
SYSFUNC(API_CRYPTO, 3, void CBC_ResetInitVector(int CryptoEnv))
SYSFUNC(API_CRYPTO, 4, bool DecryptSecrets(const byte *CipheredData,byte *PlainData,int ByteCnt))


// ******************************************************************
// ****** DESFire Functions *****************************************
// ******************************************************************

#ifndef __TWN4_SYS_C__

#define DESF_FILETYPE_STDDATAFILE           0
#define DESF_FILETYPE_BACKUPDATAFILE        1
#define DESF_FILETYPE_VALUEFILE             2
#define DESF_FILETYPE_LINEARRECORDFILE      3
#define DESF_FILETYPE_CYCLICRECORDFILE      4

#define DESF_COMMSET_PLAIN                  0
#define DESF_COMMSET_PLAIN_MACED            1
#define DESF_COMMSET_FULLY_ENC              3

#define DESF_AUTHMODE_COMPATIBLE            0
#define DESF_AUTHMODE_EV1                   1

#define DESF_KEYTYPE_3DES                   0
#define DESF_KEYTYPE_3K3DES                 1
#define DESF_KEYTYPE_AES                    2

#define DESF_KEYLEN_3DES                   	16
#define DESF_KEYLEN_3K3DES                 	24
#define DESF_KEYLEN_AES                    	16

typedef struct __attribute__((__packed__))
{
	struct TDESFireKeySettings
	{
		byte AllowChangeMasterKey:1;
		byte FreeDirectoryList:1;
		byte FreeCreateDelete:1;
		byte ConfigurationChangeable:1;
		byte ChangeKeyAccessRights:4;
	} KeySettings;
	int NumberOfKeys;
	int KeyType;
} TDESFireMasterKeySettings;

typedef struct __attribute__((__packed__))
{
	byte FileType;
	byte CommSet;
	uint16_t AccessRights;
	union TDESFireSpecificFileInfo
	{
		struct TDESFireDataFileSettings
		{
			uint32_t FileSize;
		} DataFileSettings;
		struct TDESFireValueFileSettings
		{
			uint32_t LowerLimit;
			uint32_t UpperLimit;
			uint32_t LimitedCreditValue;
			bool LimitedCreditEnabled;
		} ValueFileSettings;
		struct TDESFireRecordFileSettings
		{
			uint32_t RecordSize;
			uint32_t MaxNumberOfRecords;
			uint32_t CurrentNumberOfRecords;
		} RecordFileSettings;
	}	SpecificFileInfo;
} TDESFireFileSettings;

typedef struct __attribute__((__packed__))
{
	byte VendorID;
	byte Type;
	byte SubType;
	byte VersionMajor;
	byte VersionMinor;
	uint32_t StorageSize;
	byte CommunicationProtocol;
} TDESFireTagInfo;

typedef struct __attribute__((__packed__))
{
	byte UID[7];
	byte ProdBatchNumber[5];
	byte CalendarWeekOfProduction;
	byte YearOfProduction;
} TDESFireProdInfo;

typedef struct __attribute__((__packed__))
{
	TDESFireTagInfo HWInfo;
	TDESFireTagInfo SWInfo;
	TDESFireProdInfo ProdInfo;
} TDESFireVersion;

#endif

SYSFUNC(API_DESFIRE, 0, bool DESFire_GetApplicationIDs(int CryptoEnv, int* AIDs, int* NumberOfAIDs, int MaxAIDCnt))
SYSFUNC(API_DESFIRE, 1, bool DESFire_CreateApplication(int CryptoEnv, int AID, const TDESFireMasterKeySettings* MasterKeySettings))
SYSFUNC(API_DESFIRE, 2, bool DESFire_DeleteApplication(int CryptoEnv, int AID))
SYSFUNC(API_DESFIRE, 3, bool DESFire_SelectApplication(int CryptoEnv, int AID))
SYSFUNC(API_DESFIRE, 4, bool DESFire_Authenticate(int CryptoEnv, int KeyNoTag, const byte* Key, int KeyByteCount, int KeyType, int Mode))
SYSFUNC(API_DESFIRE, 5, bool DESFire_GetKeySettings(int CryptoEnv, TDESFireMasterKeySettings* MasterKeySettings))
SYSFUNC(API_DESFIRE, 6, bool DESFire_GetFileIDs(int CryptoEnv, byte* FileIDList, int* FileIDCount, int MaxFileIDCount))
SYSFUNC(API_DESFIRE, 7, bool DESFire_GetFileSettings(int CryptoEnv, int FileNo, TDESFireFileSettings* FileSettings))
SYSFUNC(API_DESFIRE, 8, bool DESFire_ReadData (int CryptoEnv, int FileNo, byte* Data, int Offset, int Length, int CommSet))
SYSFUNC(API_DESFIRE, 9, bool DESFire_WriteData(int CryptoEnv, int FileNo, const byte* Data, int Offset, int Length, int CommSet))
SYSFUNC(API_DESFIRE,10, bool DESFire_GetValue(int CryptoEnv, int FileNo, int* Value, int CommSet))
SYSFUNC(API_DESFIRE,11, bool DESFire_Credit(int CryptoEnv, int FileNo, const int Value, int CommSet))
SYSFUNC(API_DESFIRE,12, bool DESFire_Debit(int CryptoEnv, int FileNo, const int Value, int CommSet))
SYSFUNC(API_DESFIRE,13, bool DESFire_LimitedCredit(int CryptoEnv, int FileNo, const int Value, int CommSet))
SYSFUNC(API_DESFIRE,14, bool DESFire_FreeMem(int CryptoEnv, int* FreeMemory))
SYSFUNC(API_DESFIRE,15, bool DESFire_FormatTag(int CryptoEnv))
SYSFUNC(API_DESFIRE,16, bool DESFire_CreateDataFile(int CryptoEnv, int FileNo, const TDESFireFileSettings* FileSettings))
SYSFUNC(API_DESFIRE,17, bool DESFire_CreateValueFile(int CryptoEnv, int FileNo, const TDESFireFileSettings* FileSettings))
SYSFUNC(API_DESFIRE,18, bool DESFire_GetVersion(int CryptoEnv, TDESFireVersion* Version))
SYSFUNC(API_DESFIRE,19, bool DESFire_DeleteFile(int CryptoEnv, int FileNo))
SYSFUNC(API_DESFIRE,20, bool DESFire_CommitTransaction(int CryptoEnv))
SYSFUNC(API_DESFIRE,21, bool DESFire_AbortTransaction(int CryptoEnv))
SYSFUNC(API_DESFIRE,22, bool DESFire_GetUID(int CryptoEnv, byte* UID, int* Length, int BufferSize))
SYSFUNC(API_DESFIRE,23, bool DESFire_GetKeyVersion(int CryptoEnv, int KeyNo, byte* KeyVer))
SYSFUNC(API_DESFIRE,24, bool DESFire_ChangeKeySettings(int CryptoEnv, const TDESFireMasterKeySettings* MasterKeySettings))
SYSFUNC(API_DESFIRE,25, bool DESFire_ChangeKey(int CryptoEnv, int KeyNo, const byte* OldKey, int OldKeyByteCount, const byte* NewKey, int NewKeyByteCount, byte KeyVersion, const TDESFireMasterKeySettings* MasterKeySettings))
SYSFUNC(API_DESFIRE,26, bool DESFire_ChangeFileSettings(int CryptoEnv, int FileNo, int NewCommSet, int OldAccessRights, int NewAccessRights))
SYSFUNC(API_DESFIRE,27, bool DESFire_DisableFormatTag(int CryptoEnv))
SYSFUNC(API_DESFIRE,28, bool DESFire_EnableRandomID(int CryptoEnv))
SYSFUNC(API_DESFIRE,29, bool DESFire_SetDefaultKey(int CryptoEnv, const byte* Key, int KeyByteCount, byte KeyVersion))
SYSFUNC(API_DESFIRE,30, bool DESFire_SetATS(int CryptoEnv, const byte* ATS, int Length))
SYSFUNC(API_DESFIRE,31, bool DESFire_CreateRecordFile(int CryptoEnv, int FileNo, const TDESFireFileSettings* FileSettings))
SYSFUNC(API_DESFIRE,32, bool DESFire_ReadRecords(int CryptoEnv, int FileNo, byte* RecordData, int* RecDataByteCnt, int Offset, int NumberOfRecords, int RecordSize, int CommSet))
SYSFUNC(API_DESFIRE,33, bool DESFire_WriteRecord(int CryptoEnv, int FileNo, const byte* Data, int Offset, int Length, int CommSet))
SYSFUNC(API_DESFIRE,34, bool DESFire_ClearRecordFile(int CryptoEnv, int FileNo))

// ******************************************************************
// ****** SAM Functions *********************************************
// ******************************************************************

#ifndef __TWN4_SYS_C__

#define ISO7816_PROTOCOL_T0				0
#define ISO7816_PROTOCOL_T1				1

#define ISO7816_APDU_MAXDATASIZE		256

#define ISO7816_ERR_ICC_MUTE			0xFE
#define ISO7816_ERR_XFR_PARITY			0xFD
#define ISO7816_ERR_HW_ERROR			0xFB
#define ISO7816_ERR_BADATRTS			0xF8
#define ISO7816_ERR_BADATRTCK			0xF7
#define ISO7816_ERR_CMD_SLOT_BUSY		0xE0

#define ISO7816_CLOCKSTATUS_RUNNING		0
#define ISO7816_CLOCKSTATUS_CLKSTPL		1
#define ISO7816_CLOCKSTATUS_CLKSTPH		2
#define ISO7816_CLOCKSTATUS_CLKSTPU		3

#define ISO7816_POWERSELECT_AUTO		0
#define ISO7816_POWERSELECT_5V			1
#define ISO7816_POWERSELECT_3V			2
#define ISO7816_POWERSELECT_1V8			3

#define ISO7816_ICCPRESENTANDACTIVE		0
#define ISO7816_ICCPRESENTANDINACTIVE	1
#define ISO7816_NOICCPRESENT			2

#define ISO7816_FREQUENCY_15000000		7
#define ISO7816_FREQUENCY_7500000		6
#define ISO7816_FREQUENCY_5000000		5
#define ISO7816_FREQUENCY_3750000		4
#define ISO7816_FREQUENCY_2500000		3
#define ISO7816_FREQUENCY_1875000		2
#define ISO7816_FREQUENCY_1250000		1
#define ISO7816_FREQUENCY_1000000		0
#define ISO7816_FREQUENCY_DEFAULT		ISO7816_FREQUENCY_5000000

typedef	struct __attribute__((__packed__))
{
	byte bmICCStatus:2;
	byte bmRFU:4;
	byte bmCommandStatus:2;
} TISO7816StatusReg; // Size = 1

typedef struct __attribute__((__packed__))
{
	TISO7816StatusReg bStatus;
	byte bError;
	byte bClockStatus;
} TISO7816SlotStatus; // Size = 3

typedef struct __attribute__((__packed__))
{
	byte bmFindexDindex;
	byte bmTCCKS;
	byte bGuardTime;
	byte bWaitingInteger;
	byte bClockStop;
} TProtocolDataT0; // Size = 5

typedef struct __attribute__((__packed__))
{
	byte bmFindexDindex;
	byte bmTCCKS;
	byte bGuardTime;
	byte bmWaitingIntegers;
	byte bClockStop;
	byte bIFSC;
	byte bNadValue;
	byte bWTX;
} TProtocolDataT1; // Size = 8

typedef struct __attribute__((__packed__))
{
	byte Protocol;
	byte Freq;
	uint16_t F;
	uint16_t D;
	union TProtocolData
	{
		TProtocolDataT0 T0;
		TProtocolDataT1 T1;
	} ProtocolData;
} TISO7816CommSettings; // Size = 14

typedef struct __attribute__((__packed__))
{
	byte CLA;
	byte INS;
	byte P1;
	byte P2;
	uint16_t Lc;
	uint16_t Le;
	struct TISO7816_ProtocolHeaderFlags
	{
		byte LePresent:1;
		byte ExtendedAPDU:1;
		byte RFU:6;
	} Flags;
} TISO7816_ProtocolHeader; // Size = 9

typedef struct __attribute__((__packed__))
{
	byte CLA;
	byte INS;
	byte P1;
	byte P2;
	byte P3;
} TISO7816_T0_Header; // Size = 5

#endif

SYSFUNC(API_ISO7816, 0, bool ISO7816_GetSlotStatus(int Channel, TISO7816SlotStatus* SlotStatus))
SYSFUNC(API_ISO7816, 1, bool ISO7816_IccPowerOn(int Channel, byte* ATR, int* ATRByteCnt, int MaxATRByteCnt, byte bPowerSelect, TISO7816StatusReg* bStatus, byte* bError))
SYSFUNC(API_ISO7816, 2, bool ISO7816_IccPowerOff(int Channel, TISO7816SlotStatus* SlotStatus))
SYSFUNC(API_ISO7816, 3, bool ISO7816_SetCommSettings(int Channel, const TISO7816CommSettings* CommSettings))
SYSFUNC(API_ISO7816, 4, bool ISO7816_Transceive(int Channel,const byte* TX, int LenTX, byte* RX, int* LenRX, int MaxRXByteCnt, TISO7816StatusReg* bStatus, byte* bError))
SYSFUNC(API_ISO7816, 5, bool ISO7816_ExchangeAPDU(int Channel, const TISO7816_ProtocolHeader* Header, const byte* TXData, int TXByteCnt, byte* RXData, int* RXByteCnt, int MaxRXByteCnt, uint16_t* StatusWord))
SYSFUNC(API_ISO7816, 6, bool ISO7816_T0_TPDU(int Channel, const TISO7816_T0_Header* Header, const byte* TXData, int TXByteCnt, byte* RXData, int* RXByteCnt, int MaxRXByteCnt, uint16_t* StatusWord))

// ******************************************************************
// ****** ICLASS SIO Functions **************************************
// ******************************************************************

SYSFUNC(API_ICLASS, 0, bool ICLASS_GetPACBits(byte* PACBits, int* PACBitCnt, int MaxPACBytes))

// ******************************************************************
// ****** ISO14443 Transparent Transponder Access Functions *********
// ******************************************************************

SYSFUNC(API_ISO14443, 0, bool ISO14443A_GetATS(byte* ATS, int* ATSByteCnt, int MaxATSByteCnt))
SYSFUNC(API_ISO14443, 1, bool ISO14443B_GetATQB(byte* ATQB, int* ATQBByteCnt, int MaxATQBByteCnt))
SYSFUNC(API_ISO14443, 2, bool ISO14443_4_CheckPresence(void))
SYSFUNC(API_ISO14443, 3, bool ISO14443_4_TDX(byte* TXRX, int TXByteCnt, int* RXByteCnt, int MaxRXByteCnt))
SYSFUNC(API_ISO14443, 4, bool ISO14443A_GetATQA(byte* ATQA))
SYSFUNC(API_ISO14443, 5, bool ISO14443A_GetSAK(byte* SAK))
SYSFUNC(API_ISO14443, 6, bool ISO14443B_GetAnswerToATTRIB(byte* AnswerToATTRIB, int* AnswerToATTRIBByteCnt, int MaxAnswerToATTRIBByteCnt))
SYSFUNC(API_ISO14443, 7, bool ISO14443_3_TDX(byte* TXRX, int TXByteCnt, int* RXByteCnt, int MaxRXByteCnt, int Timeout))
SYSFUNC(API_ISO14443, 8, bool ISO14443A_SearchMultiTag(int* UIDCnt, int* UIDListByteCnt, byte *UIDList, int MaxUIDListByteCnt))
SYSFUNC(API_ISO14443, 9, bool ISO14443A_SelectTag(const byte* UID, int UIDByteCnt))

// ******************************************************************
// ****** LF Functions **********************************************
// ******************************************************************

#ifndef __TWN4_SYS_C__

#define LFSEQCMD_END			0
#define LFSEQCMD_TUNE			1

#define LFSEQCMD_TXBEGIN		2
#define LFSEQCMD_TXOFF			3
#define LFSEQCMD_TXON			4
#define LFSEQCMD_TXKEEPOFF		5
#define LFSEQCMD_TXKEEPON		6
#define LFSEQCMD_TXSAMPLES		7

#define LFSEQCMD_RXBEGIN		8
#define LFSEQCMD_RXSKIP			9
#define LFSEQCMD_RXSAMPLES		10

#endif

SYSFUNC(API_LF,0,bool LFSequencer(const byte *Sequence,int SequenceByteCnt,byte *ReadBytes,int *ReadByteCnt,int MaxReadByteCnt))

// ******************************************************************
// ****** HF Functions **********************************************
// ******************************************************************

// Coming later...

// ******************************************************************
// ****** AT55 Functions ********************************************
// ******************************************************************

#ifndef __TWN4_SYS_C__


#endif

SYSFUNC(API_AT55,0,void AT55_Begin(void))
SYSFUNC(API_AT55,1,bool AT55_ReadBlock(int Address,byte *Data))
SYSFUNC(API_AT55,2,bool AT55_ReadBlockProtected(int Address,byte *Data,const byte *Password))
SYSFUNC(API_AT55,3,bool AT55_WriteBlock(int Address,const byte *Data))
SYSFUNC(API_AT55,4,bool AT55_WriteBlockProtected(int Address,const byte *Data,const byte *Password))
SYSFUNC(API_AT55,5,bool AT55_WriteBlockAndLock(int Address,const byte *Data))
SYSFUNC(API_AT55,6,bool AT55_WriteBlockProtectedAndLock(int Address,const byte *Data,const byte *Password))

// ******************************************************************
// ****** NFC-P2P: NFCIP Functions **********************************
// ******************************************************************

#ifndef __TWN4_SYS_C__

#define NFCIPDEP_STATE_DISCONNECTED			0
#define NFCIPDEP_STATE_CONNECTING			1
#define NFCIPDEP_STATE_CONNECTEDTARGET		2
#define NFCIPDEP_STATE_CONNECTEDINITIATOR	3

#endif

SYSFUNC(API_NFCIP, 0, bool NFCIP_Init(const byte* GeneralBytes, int GeneralBytesCnt))
SYSFUNC(API_NFCIP, 1, int  NFCIP_DEP_GetConnectionState(void))
SYSFUNC(API_NFCIP, 2, int  NFCIP_DEP_TestIPDU(int Direction))
SYSFUNC(API_NFCIP, 3, bool NFCIP_DEP_SendIPDU(const byte* IPDU, int IPDUByteCnt))
SYSFUNC(API_NFCIP, 4, bool NFCIP_DEP_ReceiveIPDU(byte* IPDU, int* IPDUByteCnt, int MaxIPDUByteCnt))

// ******************************************************************
// ****** NFC-P2P: LLCP Functions ***********************************
// ******************************************************************

#ifndef __TWN4_SYS_C__

#define LLCP_LISTEN			0
#define LLCP_CONNECTING		1
#define LLCP_ACCEPT			2
#define LLCP_ESTABLISHED	3
#define LLCP_CLOSED			4

#endif

SYSFUNC(API_NFCLLCP, 0, bool LLCP_Init(int ServiceEndPoint, byte LocalSAP, byte RemoteSAP, const char* ServiceNameURI, int ServiceNameByteCnt))
SYSFUNC(API_NFCLLCP, 1, int  LLCP_GetConnectionState(int ServiceEndPoint))
SYSFUNC(API_NFCLLCP, 2, int  LLCP_TestIPDU(int ServiceEndPoint, int Direction))
SYSFUNC(API_NFCLLCP, 3, bool LLCP_SendIPDU(int ServiceEndPoint, const byte* IPDU, int IPDUByteCnt))
SYSFUNC(API_NFCLLCP, 4, bool LLCP_ReceiveIPDU(int ServiceEndPoint, byte* IPDU, int* IPDUByteCnt, int MaxIPDUByteCnt))
SYSFUNC(API_NFCLLCP, 5, int  LLCP_Listen(int ServiceEndPoint))
SYSFUNC(API_NFCLLCP, 6, int  LLCP_Connect(int ServiceEndPoint))
SYSFUNC(API_NFCLLCP, 7, int  LLCP_Accept(int ServiceEndPoint))
SYSFUNC(API_NFCLLCP, 8, int  LLCP_Close(int ServiceEndPoint))

// ******************************************************************
// ****** NFC-P2P: SNEP Functions ***********************************
// ******************************************************************

#ifndef __TWN4_SYS_C__

#define SNEP_STATE_DEINIT		0
#define SNEP_STATE_SLEEP		1
#define SNEP_STATE_IDLE			2
#define SNEP_STATE_CONNCLIENT	3
#define SNEP_STATE_CONNSERVER	4
#define SNEP_STATE_ACTIVE		5

#endif

SYSFUNC(API_NFCSNEP, 0, bool SNEP_Init(void))
SYSFUNC(API_NFCSNEP, 1, int  SNEP_GetConnectionState(void))
SYSFUNC(API_NFCSNEP, 2, int  SNEP_GetFragmentByteCount(int Direction))
SYSFUNC(API_NFCSNEP, 3, bool SNEP_BeginMessage(uint32_t MsgByteCnt))
SYSFUNC(API_NFCSNEP, 4, bool SNEP_SendMessageFragment(const byte* MsgFrag, int FragByteCnt))
SYSFUNC(API_NFCSNEP, 5, bool SNEP_TestMessage(uint32_t* MsgByteCnt))
SYSFUNC(API_NFCSNEP, 6, bool SNEP_ReceiveMessageFragment(byte* MsgFrag, int FragByteCnt))
SYSFUNC(API_NFCSNEP, 7, bool SNEP_RequestMessage(uint32_t MsgByteCnt, uint32_t AcceptableLength))

// ******************************************************************
// ****** EM4150 Functions ******************************************
// ******************************************************************

#ifndef __TWN4_SYS_C__

#define EM4150_BITRATE_UNKNOWN             	0
#define EM4150_BITRATE_F64                 	1
#define EM4150_BITRATE_F40                	2
#define EM4150_BITRATE_F32                	3

#endif

SYSFUNC(API_EM4150,0,bool EM4150_Login(const byte *Password))
SYSFUNC(API_EM4150,1,bool EM4150_ReadWord(int Address,byte *Word))
SYSFUNC(API_EM4150,2,bool EM4150_WriteWord(int Address,const byte *Word))
SYSFUNC(API_EM4150,3,bool EM4150_WritePassword(const byte *ActualPassword,const byte *NewPassword))
SYSFUNC(API_EM4150,4,int  EM4150_GetTagInfo(void))

// ******************************************************************
// ****** File System ***********************************************
// ******************************************************************

#ifndef __TWN4_SYS_C__

#define SID_INTERNALFLASH		1

#define FS_MOUNT_NONE			0
#define FS_MOUNT_READONLY		1
#define FS_MOUNT_READWRITE		2

#define FS_FORMATMAGICVALUE		0x74496F44

#define FS_READ                 0
#define FS_WRITE                1
#define FS_APPEND               2

#define FILE_ENV0         		0
#define FILE_ENV1         		1
#define FILE_ENV2         		2
#define FILE_ENV3         		3
#define FILE_ENV_CNT      		4

#define	FS_POSABS				0
#define	FS_POSREL				1
#define	FS_POSEND				2

typedef struct __attribute__((__packed__))
{
	uint32_t ID;
	uint32_t Length;
} TFileInfo; // Size = 8

typedef struct __attribute__((__packed__))
{
	byte ID;
	uint32_t Size;
	uint32_t Free;
} TStorageInfo; // Size = 13

#endif

SYSFUNC(API_FILESYS, 0,bool FSMount(int StorageID,int Mode))
SYSFUNC(API_FILESYS, 1,bool FSFormat(int StorageID,int MagicValue))
SYSFUNC(API_FILESYS, 2,bool FSOpen(int FileEnv,int StorageID,uint32_t FileID,int Mode))
SYSFUNC(API_FILESYS, 3,bool FSClose(int FileEnv))
SYSFUNC(API_FILESYS, 4,void FSCloseAll(void))
SYSFUNC(API_FILESYS, 5,bool FSSeek(int FileEnv,int Origin,int Pos))
SYSFUNC(API_FILESYS, 6,bool FSTell(int FileEnv,int Origin,int *Pos))
SYSFUNC(API_FILESYS, 7,bool FSReadBytes(int FileEnv,void *Data,int ByteCount,int *BytesRead))
SYSFUNC(API_FILESYS, 8,bool FSWriteBytes(int FileEnv,const void *Data,int ByteCount,int *BytesWritten))
SYSFUNC(API_FILESYS, 9,bool FSFindFirst(int StorageID,TFileInfo *pFileInfo))
SYSFUNC(API_FILESYS,10,bool FSFindNext(TFileInfo *pFileInfo))
SYSFUNC(API_FILESYS,11,bool FSDelete(int StorageID,uint32_t FileID))
SYSFUNC(API_FILESYS,12,bool FSRename(int StorageID,uint32_t OldFileID,uint32_t NewFileID))
SYSFUNC(API_FILESYS,13,bool FSGetStorageInfo(int StorageID,TStorageInfo *pStorageInfo))

// ******************************************************************
// ****** Mifare Plus ***********************************************
// ******************************************************************

#ifndef __TWN4_SYS_C__

#endif

SYSFUNC(API_MIFAREPLUS, 0, bool MFP_WritePerso(int BlockNr, const byte* Data))
SYSFUNC(API_MIFAREPLUS, 1, bool MFP_CommitPerso(void))
SYSFUNC(API_MIFAREPLUS, 2, bool MFP_Authenticate(int CryptoEnv, int KeyBNr, const byte* Key))
SYSFUNC(API_MIFAREPLUS, 3, bool MFP_ReadBlock(int CryptoEnv, int Block, byte* Data))
SYSFUNC(API_MIFAREPLUS, 4, bool MFP_WriteBlock(int CryptoEnv, int Block, const byte* Data))
SYSFUNC(API_MIFAREPLUS, 5, bool MFP_ReadValueBlock(int CryptoEnv, int Block, int* Value))
SYSFUNC(API_MIFAREPLUS, 6, bool MFP_WriteValueBlock(int CryptoEnv, int Block, int Value))
SYSFUNC(API_MIFAREPLUS, 7, bool MFP_IncrementValueBlock(int CryptoEnv, int Block, int Value))
SYSFUNC(API_MIFAREPLUS, 8, bool MFP_DecrementValueBlock(int CryptoEnv, int Block, int Value))
SYSFUNC(API_MIFAREPLUS, 9, bool MFP_CopyValueBlock(int CryptoEnv, int SourceBlock, int DestBlock))

// ******************************************************************
// ****** ADC *******************************************************
// ******************************************************************

#ifndef __TWN4_SYS_C__

#define ADC_CHANNEL_0			0
#define ADC_CHANNEL_1			1

#endif

SYSFUNC(API_ADC, 0,bool ADCInitChannel(int ADCChannel))
SYSFUNC(API_ADC, 1,int ADCGetConversionValue(int ADCChannel))

// ******************************************************************
// ****** FeliCa ****************************************************
// ******************************************************************

#ifndef __TWN4_SYS_C__

#endif

SYSFUNC(API_FELICA, 0, bool FeliCa_TDX(byte* TXRX, int TXByteCnt, int* RXByteCnt, int MaxRXByteCnt, byte MaximumResponseTime, byte NumberOfBlocks))
SYSFUNC(API_FELICA, 1, bool FeliCa_ReadWithoutEncryption(int NumberOfServices, const uint16_t* ServiceCodeList, int NumberOfBlocks, const uint16_t* BlockList, byte* Data))
SYSFUNC(API_FELICA, 2, bool FeliCa_WriteWithoutEncryption(int NumberOfServices, const uint16_t* ServiceCodeList, int NumberOfBlocks, const uint16_t* BlockList, const byte* Data))
SYSFUNC(API_FELICA, 3, bool FeliCa_RequestSystemCode(int* NumberOfSystemCodes, uint16_t* SystemCodeList, int MaxNumberOfSystemCodes))
SYSFUNC(API_FELICA, 4, bool FeliCa_Poll(uint16_t SystemCode, byte* IDm, byte* PMm))
SYSFUNC(API_FELICA, 5, bool FeliCa_RequestService(int NumberOfServices, const uint16_t* ServiceCodeList, uint16_t* KeyVersionList))

// ******************************************************************
// ****** SLE44XX Cards *********************************************
// ******************************************************************

#ifndef __TWN4_SYS_C__

#endif

SYSFUNC(API_SLE44XX, 0, bool SLE_GetATR(int Channel, byte* ATR))
SYSFUNC(API_SLE44XX, 1, bool SLE_ReadMainMemory(int Channel, int Address, byte* Data, int ByteCnt))
SYSFUNC(API_SLE44XX, 2, bool SLE_UpdateMainMemory(int Channel, int Address, byte Value))
SYSFUNC(API_SLE44XX, 3, bool SLE_ReadSecurityMemory(int Channel, byte* SecMemData))
SYSFUNC(API_SLE44XX, 4, bool SLE_UpdateSecurityMemory(int Channel, int Address, byte SecMemData))
SYSFUNC(API_SLE44XX, 5, bool SLE_ReadProtectionMemory(int Channel, byte* ProtMemData))
SYSFUNC(API_SLE44XX, 6, bool SLE_WriteProtectionMemory(int Channel, int Address, byte ProtMemData))
SYSFUNC(API_SLE44XX, 7, bool SLE_CompareVerificationData(int Channel, int Address, byte VerificationData))

// ******************************************************************
// ****** NTAG2XX ***************************************************
// ******************************************************************

#ifndef __TWN4_SYS_C__

#endif

SYSFUNC(API_NTAG, 0, bool NTAG_Read(int Page, byte* Data))
SYSFUNC(API_NTAG, 1, bool NTAG_Write(int Page, const byte* Data))
SYSFUNC(API_NTAG, 2, bool NTAG_FastRead(int StartPage, int NumberOfPages, byte* Data))
SYSFUNC(API_NTAG, 3, bool NTAG_ReadCounter(int* CounterValue))
SYSFUNC(API_NTAG, 4, bool NTAG_ReadSig(byte* ECCSig))
SYSFUNC(API_NTAG, 5, bool NTAG_GetVersion(byte* Version))
SYSFUNC(API_NTAG, 6, bool NTAG_PwdAuth(const byte* Password, const byte* PwdAck))
SYSFUNC(API_NTAG, 7, bool NTAG_SectorSelect(int Sector))

// ******************************************************************
// ****** SRX *******************************************************
// ******************************************************************

#ifndef __TWN4_SYS_C__

#endif

SYSFUNC(API_SRX, 0, bool SRX_ReadBlock(int Block, byte* Data))
SYSFUNC(API_SRX, 1, bool SRX_WriteBlock(int Block, const byte* Data))

// ******************************************************************
// ****** SAMAVX ****************************************************
// ******************************************************************

#ifndef __TWN4_SYS_C__

typedef struct __attribute__((__packed__))
{
	byte VersionKeyA;
	byte VersionKeyB;
	byte VersionKeyC;
	uint32_t DF_AID;
	byte DF_KeyNo;
	byte KeyNoCEK;
	byte KeyVCEK;
	byte RefNoKUC;
	uint16_t SET;
} TSAMAVxKeyEntryData; // Size = 13

#endif

SYSFUNC(API_SAMAVX, 0, bool SAMAVx_AuthenticateHost(int CryptoEnv, int KeyNo, const byte* Key, int KeyByteCount, int KeyType))
SYSFUNC(API_SAMAVX, 1, bool SAMAVx_GetKeyEntry(int KeyNo, TSAMAVxKeyEntryData* KeyEntryData))

// ******************************************************************
// ****** EM4102 Functions ******************************************
// ******************************************************************

#ifndef __TWN4_SYS_C__

#define EM4102_BITRATE_UNKNOWN            	0
#define EM4102_BITRATE_F64                 	1
#define EM4102_BITRATE_F32                	2

#endif

SYSFUNC(API_EM4102, 0,int EM4102_GetTagInfo(void))

// ******************************************************************
// ****** SPI Functions *********************************************
// ******************************************************************

#ifndef __TWN4_SYS_C__

#define SPI_MODE_MASTER           	1		// Only master is supported today
#define SPI_MODE_SLAVE            	0

#define SPI_CPOL_LOW              	0
#define SPI_CPOL_HIGH             	1

#define SPI_CPHA_EDGE1            	0
#define SPI_CPHA_EDGE2            	1

#define SPI_CLOCKRATE_15_MHZ   		0
#define SPI_CLOCKRATE_7_5_MHZ      	1
#define SPI_CLOCKRATE_3_75_MHZ     	2
#define SPI_CLOCKRATE_1_88_MHZ     	3
#define SPI_CLOCKRATE_938_KHZ      	4
#define SPI_CLOCKRATE_469_KHZ      	5
#define SPI_CLOCKRATE_234_KHZ      	6
#define SPI_CLOCKRATE_117_KHZ      	7

#define SPI_FIRSTBIT_MSB            0
#define SPI_FIRSTBIT_LSB            1

typedef struct __attribute__((__packed__))
{
    byte Mode;
    byte CPOL;
    byte CPHA;
    byte ClockRate;
    byte BitOrder;
} TSPIParameters;

#endif

SYSFUNC(API_SPI, 0, bool SPIInit(const TSPIParameters *SPIParameters))
SYSFUNC(API_SPI, 1, void SPIDeInit(void))
SYSFUNC(API_SPI, 2, void SPIMasterBeginTransfer(void))
SYSFUNC(API_SPI, 3, void SPIMasterEndTransfer(void))
SYSFUNC(API_SPI, 4, bool SPITransmit(const byte *TXData,int ByteCount))
SYSFUNC(API_SPI, 5, bool SPIReceive(byte *RXData,int ByteCount))
SYSFUNC(API_SPI, 6, bool SPITransceive(const byte *TXData,byte *RXData,int ByteCount))

// ******************************************************************
// ****** BLE Functions *********************************************
// ******************************************************************

#ifndef __TWN4_SYS_C__

#define BLE_MODE_CUSTOM							0
#define BLE_MODE_ADVERTISEMENT					1
#define BLE_MODE_BEACON							2

#define BLE_EVENT_NONE 							0x00
#define BLE_EVENT_ENDPOINT_CLOSING 				0x21
#define BLE_EVENT_ENDPOINT_DATA 				0x22
#define BLE_EVENT_ENDPOINT_STATUS 				0x23
#define BLE_EVENT_ENDPOINT_SYNTAX_ERROR 		0x24
#define BLE_EVENT_GATT_SERVER_ATTRIBUTE_VALUE 	0x51
#define BLE_EVENT_CONNECTION_CLOSED 			0x71
#define BLE_EVENT_CONNECTION_OPENED 			0x72
#define BLE_EVENT_CONNECTION_PARAMETERS 		0x73
#define BLE_EVENT_CONNECTION_RSSI 				0x74
#define BLE_EVENT_SM_BONDED 					0x91
#define BLE_EVENT_SM_BONDING_FAILED 			0x92
#define BLE_EVENT_SM_PASSKEY_DISPLAY 			0x95
#define BLE_EVENT_SM_PASSKEY_REQUEST 			0x96
#define BLE_EVENT_SYSTEM_BOOT 					0xA2

// BLE configuration structure
typedef struct __attribute__((__packed__))
{
	uint32_t ConnectTimeout;
	byte Power;
	byte BondableMode;
	uint16_t AdvInterval;
	byte ChannelMap;
	byte DiscoverMode;
	byte ConnectMode;
	byte SecurityFlags;
	byte IOCapabilities;
	uint32_t Passkey;
} TBLEConfig;

#endif

SYSFUNC(API_BLE, 0, bool BLEPresetConfig(TBLEConfig* BLEConfig))
SYSFUNC(API_BLE, 1, bool BLEPresetUserData(byte ScanResp, const byte* UserData, int UserDataLength))
SYSFUNC(API_BLE, 2, bool BLEInit(int Mode))
SYSFUNC(API_BLE, 3, int  BLECheckEvent(void))
SYSFUNC(API_BLE, 4, bool BLEGetAddress(byte* DeviceAddress, byte* RemoteAddress, byte* Type))
SYSFUNC(API_BLE, 5, bool BLEGetVersion(byte* HWVersion, byte* BootString))
SYSFUNC(API_BLE, 6, bool BLEGetEnvironment(byte* DeviceRole, byte* SecurityMode, byte* Rssi))
SYSFUNC(API_BLE, 7, bool BLEGetGattServerAttributeValue(int AttrHandle, byte *Data, int *Len, int MaxLen))
SYSFUNC(API_BLE, 8, bool BLESetGattServerAttributeValue(int AttrHandle, int Offset, const byte *Data, int Len))
SYSFUNC(API_BLE, 9, bool BLERequestRssi(void))
SYSFUNC(API_BLE, 10,bool BLERequestEndpointClose(void))

// ******************************************************************
// ******* End of System Functions **********************************
// ******************************************************************

#pragma GCC diagnostic pop

#endif
