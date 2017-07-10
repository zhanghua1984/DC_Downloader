/****************************************************************************/
/* * Copyright (c) 2012, 北京大成通号轨道交通设备有限公司					*/
/* * All rights reserved.													*/
/*																			*/
/*	该文件定义全部常量，且全部常量长度为1byte，全部取不同值，避免相互混淆	*/
/*	变量相对取值为异或值为0xFF 例:A = 0x0F ,-A = 0xF0	单值为: B = 0xAA	*/
/*																			*/
/*	文件名称：ATP_ATO_Macro.h												*/
/*	内容描述：宏定义头文件													*/
/*	当前版本：V0.1															*/
/*	作者:张华																*/
/*	日期:2012.04.01															*/
/*																			*/
/* 更改记录：无																*/
/****************************************************************************/

#ifndef __ATP_ATO_MACRO_H__
#define __ATP_ATO_MACRO_H__
#endif
/************************************************************************/
/*	道岔类型															*/
/*																		*/
/*	道岔定位	POINT_NOML                                              */
/*	道岔反位	POINT_REVES                                             */
/************************************************************************/


#ifndef POINT_NOML
#define POINT_NOML 0xF0
#endif

#ifndef POINT_REVES
#define POINT_REVES 0x0F
#endif


/************************************************************************/
/*	轨道类型															*/
/*																		*/
/*	上行轨	TRACK_UP									                */
/*	下行轨	TRACK_DOWN												    */
/*	站台上行轨	TRACK_STATION_UP										*/
/*	站台下行轨	TRACK_STATION_DOWN										*/
/*	出入段轨	TRACK_PARK											    */
/*	渡线	TRACK_FERRY													*/
/*	折返轨	TRACK_TURNBK											    */
/************************************************************************/


#ifndef TRACK_UP
#define TRACK_UP 0x27
#endif

#ifndef TRACK_DOWN
#define TRACK_DOWN 0x72
#endif

#ifndef TRACK_STATION_UP
#define TRACK_STATION_UP 0x37
#endif

#ifndef TRACK_STATION_DOWN
#define TRACK_STATION_DOWN 0x73
#endif

#ifndef TRACK_PARK
#define TRACK_PARK 0xCC
#endif

#ifndef TRACK_FERRY
#define TRACK_FERRY 0xEE
#endif

#ifndef TRACK_TURNBK
#define TRACK_TURNBK 0xDD
#endif

#ifndef TRACK_STATION
#define TRACK_STATION 0xAA
#endif


/************************************************************************/
/*	开门门侧															*/
/*																		*/
/*	开左门	DOOR_LEFT									                */
/*	开右门	DOOR_RIGHT												    */
/*	开双门	DOOR_ALL													*/
/*	不开门	DOOR_FORBID													*/
/*	未定义开门侧	DATA_UNDEF										    */
/************************************************************************/


#ifndef DOOR_LEFT
#define DOOR_LEFT 0xF3
#endif

#ifndef DOOR_RIGHT
#define DOOR_RIGHT 0x3F
#endif

#ifndef DOOR_ALL
#define DOOR_ALL 0x33
#endif

#ifndef DOOR_FORBID
#define DOOR_FORBID 0xBB
#endif

#ifndef DATA_UNDEF
#define DATA_UNDEF 0xAA
#endif


/************************************************************************/
/*	信号机类型															*/
/*																		*/
/*	信号机有效	SIGLAMP_VALID									        */
/*	信号机无效	SIGLAMP_INVALID											*/
/************************************************************************/

#ifndef SIGLAMP_VALID
#define SIGLAMP_VALID 0xF4
#endif

#ifndef SIGLAMP_INVALID
#define SIGLAMP_INVALID 0x4F
#endif


/************************************************************************/
/*	跳停定义															*/
/*																		*/
/*	允许跳停	SKIP_VALID											    */
/*	禁止跳停	SKIP_INVALID											*/
/*	未定义跳停	DATA_UNDEF												*/
/************************************************************************/

#ifndef SKIP_VALID
#define SKIP_VALID 0x5F
#endif

#ifndef SKIP_INVALID
#define SKIP_INVALID 0xF5
#endif

#ifndef DATA_UNDEF
#define DATA_UNDEF 0x55
#endif


/************************************************************************/
/*	码表	数值前后相加后转成16进制数									*/
/*																		*/
/*	74/73码	FBSS7473													*/
/*	74/58码	FBSS7458													*/
/*	59/58码	FBSS5958													*/
/*	59/37码	FBSS5937													*/
/*	38/37码	FBSS3837													*/
/*	38/27码	FBSS3827													*/
/*	38/0码	FBSS3800													*/
/*	28/27码	FBSS2827													*/
/*	28/19码	FBSS2819													*/
/*	28/0码	FBSS2800													*/
/*	20/0码	FBSS2000													*/
/*	0/0码	FBSS0000													*/
/*	定义原则两个码数字相加后，看末尾，如果为N，加0，R1加100				*/
/*	 R2加200，NS为50													*/
/*	4/4N码	DTG4_4N														*/
/*	3/3N码	DTG3_3N														*/
/*	2/2N码	DTG2_2N														*/
/*	1/1N码	DTG1_1N														*/
/*	0/0N码	DTG0_0N														*/
/*	2/2R1码	DTG2_2R1													*/
/*	2/1R2码	DTG2_1R2													*/
/*	1/0R1码	DTG1_0R1													*/
/*	1N码	DTG2_1N														*/
/*	1/0N码	DTG1_0N														*/
/*	2/2NS码	DTG2_2NS													*/
/*	1/1NS码	DTG1_1NS													*/
/*	RM 模式	RM2523U			RM2018U										*/
/*	错误码	CODEERROR													*/
/************************************************************************/


#ifndef FBSS7473
#define FBSS7473 147
#endif

#ifndef FBSS7458
#define FBSS7458 132
#endif

#ifndef FBSS5958
#define FBSS5958 117
#endif

#ifndef FBSS5937
#define FBSS5937 96
#endif

#ifndef FBSS3837
#define FBSS3837 75
#endif

#ifndef FBSS3827
#define FBSS3827 65
#endif

#ifndef FBSS3800
#define FBSS3800 38
#endif

#ifndef FBSS2827
#define FBSS2827 55
#endif

#ifndef FBSS2819
#define FBSS2819 47
#endif

#ifndef FBSS2800
#define FBSS2800 28
#endif

#ifndef FBSS2000
#define FBSS2000 20
#endif



#ifndef DTG4_4N
#define DTG4_4N 1
#endif

#ifndef DTG3_3N
#define DTG3_3N 2
#endif

#ifndef DTG2_2N
#define DTG2_2N 3
#endif

#ifndef DTG1_1N
#define DTG1_1N 4
#endif

#ifndef DTG0_0N
#define DTG0_0N 5
#endif

#ifndef DTG2_2R1
#define DTG2_2R1 6
#endif

#ifndef DTG2_1R2
#define DTG2_1R2 7
#endif

#ifndef DTG1_0R1
#define DTG1_0R1 8
#endif

#ifndef DTG2_1N
#define DTG2_1N 9
#endif

#ifndef DTG1_0N
#define DTG1_0N 10
#endif

#ifndef DTG2_2NS
#define DTG2_2NS 11
#endif

#ifndef DTG1_1NS
#define DTG1_1NS 12
#endif


#ifndef RM2523U
#define RM2523U 0x48
#endif

#ifndef RM2018U
#define RM2018U 0x38
#endif

#ifndef CODEERROR
#define CODEERROR 0xFF
#endif




/************************************************************************/
/*	上下行方向															*/
/*																		*/
/*	上行	UPDIR														*/
/*	下行	DOWNDIR														*/
/*	未知或错误	ERRORDIR												*/
/************************************************************************/

#ifndef UPDIR
#define UPDIR 0x27
#endif

#ifndef DOWNDIR
#define DOWNDIR 0x72
#endif

#ifndef DOWNDIR
#define DOWNDIR 0x77
#endif

/************************************************************************/
/*	AB机不一致															*/
/*																		*/
/*	AB机不一致	ABDISACCORD												*/
/************************************************************************/

#ifndef ABDISACCORD
#define ABDISACCORD 0x11
#endif

/************************************************************************/
/*	信号模式															*/
/*																		*/
/*	FBSS信号模式	SIGNLFBSS											*/
/*	DTG信号模式		SIGNLDTG											*/
/************************************************************************/

#ifndef SIGNLFBSS
#define SIGNLFBSS 0xFB
#endif

#ifndef SIGNLDTG
#define SIGNLDTG 0xBF
#endif


/************************************************************************/
/*	驾驶模式															*/
/*																		*/
/*	DTGCM模式	MODEDTGCM 												*/
/*	FBSSCM模式	MODEFBSSCM 												*/
/*	RM模式		MODERM 													*/
/*	EUM模式		MODEEUM 												*/
/*	00模式		MODE00 													*/
/*	模式错误	MODEERROR 												*/
/************************************************************************/


#ifndef MODEDTGCM
#define MODEDTGCM 0xAA
#endif

#ifndef MODEFBSSCM
#define MODEFBSSCM 0xBB
#endif

#ifndef MODERM
#define MODERM 0xCC
#endif

#ifndef MODEEUM
#define MODEEUM 0xDD
#endif

#ifndef MODE00
#define MODE00 0x00
#endif

#ifndef MODEERROR
#define MODEERROR 0xFF
#endif


/************************************************************************/
/*	主控																*/
/*																		*/
/*	头车 HEADTRAIN														*/	
/*	尾车 TAILTRAIN														*/
/************************************************************************/

#ifndef HEADTRAIN
#define HEADTRAIN 0xFA
#endif

#ifndef TAILTRAIN
#define TAILTRAIN 0xAF
#endif


/************************************************************************/
/*	控制手柄状态														*/
/*																		*/
/*	 HANDSHANKS															*/
/*	 HANDSHANKT															*/
/*	 HANDSHANKB															*/
/*	 HANDSHANKE															*/
/************************************************************************/

#ifndef HANDSHANKS
#define HANDSHANKS 0x96
#endif

#ifndef HANDSHANKT
#define HANDSHANKT 0x97
#endif

#ifndef HANDSHANKB
#define HANDSHANKB 0x98
#endif

#ifndef HANDSHANKE
#define HANDSHANKE 0x99
#endif


/************************************************************************/
/*	其它数据定义														*/
/*																		*/
/*	对应项没有	DATA_NONE												*/
/*	数据终止	DATA_END												*/
/*	未定义		UNDEFINE												*/
/************************************************************************/

#ifndef DATA_END
#define DATA_END 0xFF
#endif

#ifndef DATA_NONE
#define DATA_NONE 0x00
#endif

#ifndef UNDEFINE
#define UNDEFINE 0x00
#endif

/************************************************************************/
/*	数据类型定义														*/
/*																		*/
/************************************************************************/


typedef unsigned char UINT8;

typedef unsigned short int UINT16;	

typedef unsigned int UINT32;

/************************************************************************/
/*	继电器定义															*/
/*																		*/
/************************************************************************/

#ifndef SAFERELAYEB
#define SAFERELAYEB 0x01
#endif

#ifndef SAFERELAYB7
#define SAFERELAYB7 0x02
#endif

#ifndef SAFERELAYZERO
#define SAFERELAYZERO 0x03
#endif

#ifndef SAFERELAYFAULT
#define SAFERELAYFAULT 0x04
#endif

#ifndef SAFERELAYTRACTION
#define SAFERELAYTRACTION 0x05
#endif

#ifndef SAFERELAYOPENDOOR_L
#define SAFERELAYOPENDOOR_L 0x06
#endif

#ifndef SAFERELAYOPENDOOR_R
#define SAFERELAYOPENDOOR_R 0x07
#endif

/************************************************************************/
/*	颜色定义															*/
/*																		*/
/*	红	STATE_RED														*/
/*	绿	STATE_GREEN 													*/
/*	灰	STATE_GRAY 														*/
/************************************************************************/

#ifndef STATE_RED
#define STATE_RED RGB(255U,0U,0U)
#endif

#ifndef STATE_GREEN
#define STATE_GREEN RGB(0U,255U,0U)
#endif

#ifndef STATE_GRAY
#define STATE_GRAY RGB(200U,200U,200U)
#endif


/************************************************************************/
/*	错误定义															*/
/*																		*/
/* MAX_ELESELFTESTERROR 		系统上电自检错误						*/
/* MAX_PERIODSELFTESTERROR		系统周期性自检错误						*/
/* MAX_CONDATAERROR 			配置数据错误							*/
/* MAX_GEODATAERROR 			地理数据错误							*/
/* MAX_CALCERROR				计算错误								*/
/* MAX_CULLBACKERROR 			回采错误								*/
/* MAX_ERRORNUM					最大错误数								*/
/************************************************************************/

#ifndef ZEROSPEED
#define ZEROSPEED 0xFF
#endif

#ifndef MAX_TIMERGAP
#define MAX_TIMERGAP 60000U
#endif

#ifndef UINT32ERROR
#define UINT32ERROR 0xFFFFFFFFU
#endif

#ifndef UINT16ERROR
#define UINT16ERROR 0xFFFFU
#endif

#ifndef UINT8ERROR
#define UINT8ERROR 0xFFU
#endif

#ifndef MAX_ELESELFTESTERROR
#define MAX_ELESELFTESTERROR 0xFF
#endif

#ifndef MAX_PERIODSELFTESTERROR
#define MAX_PERIODSELFTESTERROR 0xFF
#endif

#ifndef MAX_CONDATAERROR
#define MAX_CONDATAERROR 0xFF
#endif

#ifndef MAX_GEODATAERROR
#define MAX_GEODATAERROR 0xFF
#endif

#ifndef MAX_CALCERROR
#define MAX_CALCERROR 0xFF
#endif

#ifndef MAX_CULLBACKERROR
#define MAX_CULLBACKERROR 0xFF
#endif

#ifndef MAX_ERRORNUM
#define MAX_ERRORNUM 1000U
#endif


/************************************************************************/
/*	制动定义															*/
/*																		*/
/*	B1制动	BRAKE_B1													*/
/*	B2制动	BRAKE_B2													*/
/*	B3制动	BRAKE_B3													*/
/*	B4制动	BRAKE_B4													*/
/*	B5制动	BRAKE_B5													*/
/*	B6制动	BRAKE_B6													*/
/*	B7制动	BRAKE_B7													*/
/*	EB制动	BRAKE_EB													*/
/************************************************************************/

#ifndef BRAKE_B1
#define BRAKE_B1 0xB1
#endif

#ifndef BRAKE_B2
#define BRAKE_B2 0xB2
#endif

#ifndef BRAKE_B3
#define BRAKE_B3 0xB3
#endif

#ifndef BRAKE_B4
#define BRAKE_B4 0xB4
#endif

#ifndef BRAKE_B5
#define BRAKE_B5 0xB5
#endif

#ifndef BRAKE_B6
#define BRAKE_B6 0xB6
#endif

#ifndef BRAKE_B7
#define BRAKE_B7 0xB7
#endif

#ifndef BRAKE_EB
#define BRAKE_EB 0xEB
#endif


/************************************************************************/
/*	牵引定义															*/
/*																		*/
/*	P1牵引	TRACTION_P1													*/
/*	P2牵引	TRACTION_P2													*/
/*	P3牵引	TRACTION_P3													*/
/*	P4牵引	TRACTION_P4													*/
/*	空挡	TRACTION_P0													*/
/************************************************************************/

#ifndef TRACTION_P0
#define TRACTION_P0 0xC0
#endif

#ifndef TRACTION_P1
#define TRACTION_P1 0xC1
#endif

#ifndef TRACTION_P2
#define TRACTION_P2 0xC2
#endif

#ifndef TRACTION_P3
#define TRACTION_P3 0xC3
#endif

#ifndef TRACTION_P4
#define TRACTION_P4 0xC4
#endif


/************************************************************************/
/*	测速电机和多普勒雷达												*/
/*																		*/
/*	测速相位A	TACHO_PHASEA											*/
/*	测速相位B	TACHO_PHASEB											*/
/*	相位A在B前	TACHO_PHASEA_AHEAD										*/
/*	相位B在A前	TACHO_PHASEB_AHEAD										*/
/*	多普勒前行	DOPPLER_FORWARD											*/
/*	多普勒后退	DOPPLER_BACKWARD										*/
/*	测速机/多普勒单位时间脉冲	TACHO_DOPPLER_PULSE_TTMS				*/
/*	测速机/多普勒10ms脉冲	TACHO_DOPPLER_PULSE_10MS					*/
/*	测速机/多普勒20ms脉冲	TACHO_DOPPLER_PULSE_20MS					*/
/*	测速机/多普勒30ms脉冲	TACHO_DOPPLER_PULSE_30MS					*/
/*	测速机/多普勒40ms脉冲	TACHO_DOPPLER_PULSE_40MS					*/
/*	测速机/多普勒50ms脉冲	TACHO_DOPPLER_PULSE_50MS					*/
/*	测速机/多普勒100ms脉冲	TACHO_DOPPLER_PULSE_100MS					*/
/************************************************************************/

#ifndef TACHO_PHASEA
#define TACHO_PHASEA 0xCA
#endif

#ifndef TACHO_PHASEB
#define TACHO_PHASEB 0xCB
#endif

#ifndef TACHO_PHASEA_AHEAD
#define TACHO_PHASEA_AHEAD 0xAB
#endif

#ifndef TACHO_PHASEB_AHEAD
#define TACHO_PHASEB_AHEAD 0xBA
#endif

#ifndef DOPPLER_FORWARD
#define DOPPLER_FORWARD 0xCD
#endif

#ifndef DOPPLER_BACKWARD
#define DOPPLER_BACKWARD 0xDC
#endif

#ifndef TACHO_DOPPLER_PULSE_TTMS
#define TACHO_DOPPLER_PULSE_TTMS 0xCC
#endif

#ifndef TACHO_DOPPLER_PULSE_10MS
#define TACHO_DOPPLER_PULSE_10MS 10
#endif

#ifndef TACHO_DOPPLER_PULSE_20MS
#define TACHO_DOPPLER_PULSE_20MS 20
#endif

#ifndef TACHO_DOPPLER_PULSE_30MS
#define TACHO_DOPPLER_PULSE_30MS 30
#endif

#ifndef TACHO_DOPPLER_PULSE_40MS
#define TACHO_DOPPLER_PULSE_40MS 40
#endif

#ifndef TACHO_DOPPLER_PULSE_50MS
#define TACHO_DOPPLER_PULSE_50MS 50
#endif

#ifndef TACHO_DOPPLER_PULSE_100MS
#define TACHO_DOPPLER_PULSE_100MS 100
#endif

/************************************************************************/
/*	板																	*/
/*																		*/
/*	TCM	ATPATO_TCMBOARD													*/
/*	SLM	ATPATO_SLMBOARD													*/
/*	CIOM-1	ATPATO_CIOM1BOARD											*/
/*	CIOM-2	ATPATO_CIOM2BOARD											*/
/*	MPM	ATPATO_MPMBOARD													*/
/*	DIM	ATPATO_DIMBOARD													*/
/*	Demo_Board	ATPATO_DEMOBOARD										*/
/*	单板正常	BOARD_STATEOK											*/
/*	单板故障	BOARD_STATEFAIL											*/
/************************************************************************/


#ifndef ATPATO_TCMBOARD
#define ATPATO_TCMBOARD 101
#endif

#ifndef ATPATO_SLMBOARD
#define ATPATO_SLMBOARD 102
#endif

#ifndef ATPATO_CIOM1BOARD
#define ATPATO_CIOM1BOARD 103
#endif

#ifndef ATPATO_CIOM2BOARD
#define ATPATO_CIOM2BOARD 104
#endif

#ifndef ATPATO_MPMBOARD
#define ATPATO_MPMBOARD 105
#endif

#ifndef ATPATO_DIMBOARD
#define ATPATO_DIMBOARD 106
#endif

#ifndef ATPATO_DEMOBOARD
#define ATPATO_DEMOBOARD 107
#endif

#ifndef BOARD_STATEOK
#define BOARD_STATEOK 0xEC
#endif

#ifndef BOARD_STATEFAIL
#define BOARD_STATEFAIL 0xCE
#endif



/************************************************************************/
/*	软件版本号															*/
/*																		*/
/*	取后两位，依次递增													*/
/*	SOFTWAREV01															*/
/*	SOFTWAREV02															*/
/*	SOFTWAREV03															*/
/*	SOFTWAREV04															*/
/*	SOFTWAREV05															*/
/************************************************************************/


#ifndef SOFTWAREV01
#define SOFTWAREV01 01
#endif

#ifndef SOFTWAREV02
#define SOFTWAREV02 02
#endif

#ifndef SOFTWAREV03
#define SOFTWAREV03 03
#endif

#ifndef SOFTWAREV04
#define SOFTWAREV04 04
#endif

#ifndef SOFTWAREV05
#define SOFTWAREV05 05
#endif


/************************************************************************/
/*	TCE																	*/
/*																		*/
/************************************************************************/

#ifndef TCE
#define TCE 0xCE
#endif

#ifndef NOTCE
#define NOTCE 0x0C
#endif