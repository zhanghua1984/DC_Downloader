/****************************************************************************/
/* * Copyright (c) 2012, �������ͨ�Ź����ͨ�豸���޹�˾					*/
/* * All rights reserved.													*/
/*																			*/
/*	���ļ�����ȫ����������ȫ����������Ϊ1byte��ȫ��ȡ��ֵͬ�������໥����	*/
/*	�������ȡֵΪ���ֵΪ0xFF ��:A = 0x0F ,-A = 0xF0	��ֵΪ: B = 0xAA	*/
/*																			*/
/*	�ļ����ƣ�ATP_ATO_Macro.h												*/
/*	�����������궨��ͷ�ļ�													*/
/*	��ǰ�汾��V0.1															*/
/*	����:�Ż�																*/
/*	����:2012.04.01															*/
/*																			*/
/* ���ļ�¼����																*/
/****************************************************************************/

#ifndef __ATP_ATO_MACRO_H__
#define __ATP_ATO_MACRO_H__
#endif
/************************************************************************/
/*	��������															*/
/*																		*/
/*	����λ	POINT_NOML                                              */
/*	����λ	POINT_REVES                                             */
/************************************************************************/


#ifndef POINT_NOML
#define POINT_NOML 0xF0
#endif

#ifndef POINT_REVES
#define POINT_REVES 0x0F
#endif


/************************************************************************/
/*	�������															*/
/*																		*/
/*	���й�	TRACK_UP									                */
/*	���й�	TRACK_DOWN												    */
/*	վ̨���й�	TRACK_STATION_UP										*/
/*	վ̨���й�	TRACK_STATION_DOWN										*/
/*	����ι�	TRACK_PARK											    */
/*	����	TRACK_FERRY													*/
/*	�۷���	TRACK_TURNBK											    */
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
/*	�����Ų�															*/
/*																		*/
/*	������	DOOR_LEFT									                */
/*	������	DOOR_RIGHT												    */
/*	��˫��	DOOR_ALL													*/
/*	������	DOOR_FORBID													*/
/*	δ���忪�Ų�	DATA_UNDEF										    */
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
/*	�źŻ�����															*/
/*																		*/
/*	�źŻ���Ч	SIGLAMP_VALID									        */
/*	�źŻ���Ч	SIGLAMP_INVALID											*/
/************************************************************************/

#ifndef SIGLAMP_VALID
#define SIGLAMP_VALID 0xF4
#endif

#ifndef SIGLAMP_INVALID
#define SIGLAMP_INVALID 0x4F
#endif


/************************************************************************/
/*	��ͣ����															*/
/*																		*/
/*	������ͣ	SKIP_VALID											    */
/*	��ֹ��ͣ	SKIP_INVALID											*/
/*	δ������ͣ	DATA_UNDEF												*/
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
/*	���	��ֵǰ����Ӻ�ת��16������									*/
/*																		*/
/*	74/73��	FBSS7473													*/
/*	74/58��	FBSS7458													*/
/*	59/58��	FBSS5958													*/
/*	59/37��	FBSS5937													*/
/*	38/37��	FBSS3837													*/
/*	38/27��	FBSS3827													*/
/*	38/0��	FBSS3800													*/
/*	28/27��	FBSS2827													*/
/*	28/19��	FBSS2819													*/
/*	28/0��	FBSS2800													*/
/*	20/0��	FBSS2000													*/
/*	0/0��	FBSS0000													*/
/*	����ԭ��������������Ӻ󣬿�ĩβ�����ΪN����0��R1��100				*/
/*	 R2��200��NSΪ50													*/
/*	4/4N��	DTG4_4N														*/
/*	3/3N��	DTG3_3N														*/
/*	2/2N��	DTG2_2N														*/
/*	1/1N��	DTG1_1N														*/
/*	0/0N��	DTG0_0N														*/
/*	2/2R1��	DTG2_2R1													*/
/*	2/1R2��	DTG2_1R2													*/
/*	1/0R1��	DTG1_0R1													*/
/*	1N��	DTG2_1N														*/
/*	1/0N��	DTG1_0N														*/
/*	2/2NS��	DTG2_2NS													*/
/*	1/1NS��	DTG1_1NS													*/
/*	RM ģʽ	RM2523U			RM2018U										*/
/*	������	CODEERROR													*/
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
/*	�����з���															*/
/*																		*/
/*	����	UPDIR														*/
/*	����	DOWNDIR														*/
/*	δ֪�����	ERRORDIR												*/
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
/*	AB����һ��															*/
/*																		*/
/*	AB����һ��	ABDISACCORD												*/
/************************************************************************/

#ifndef ABDISACCORD
#define ABDISACCORD 0x11
#endif

/************************************************************************/
/*	�ź�ģʽ															*/
/*																		*/
/*	FBSS�ź�ģʽ	SIGNLFBSS											*/
/*	DTG�ź�ģʽ		SIGNLDTG											*/
/************************************************************************/

#ifndef SIGNLFBSS
#define SIGNLFBSS 0xFB
#endif

#ifndef SIGNLDTG
#define SIGNLDTG 0xBF
#endif


/************************************************************************/
/*	��ʻģʽ															*/
/*																		*/
/*	DTGCMģʽ	MODEDTGCM 												*/
/*	FBSSCMģʽ	MODEFBSSCM 												*/
/*	RMģʽ		MODERM 													*/
/*	EUMģʽ		MODEEUM 												*/
/*	00ģʽ		MODE00 													*/
/*	ģʽ����	MODEERROR 												*/
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
/*	����																*/
/*																		*/
/*	ͷ�� HEADTRAIN														*/	
/*	β�� TAILTRAIN														*/
/************************************************************************/

#ifndef HEADTRAIN
#define HEADTRAIN 0xFA
#endif

#ifndef TAILTRAIN
#define TAILTRAIN 0xAF
#endif


/************************************************************************/
/*	�����ֱ�״̬														*/
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
/*	�������ݶ���														*/
/*																		*/
/*	��Ӧ��û��	DATA_NONE												*/
/*	������ֹ	DATA_END												*/
/*	δ����		UNDEFINE												*/
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
/*	�������Ͷ���														*/
/*																		*/
/************************************************************************/


typedef unsigned char UINT8;

typedef unsigned short int UINT16;	

typedef unsigned int UINT32;

/************************************************************************/
/*	�̵�������															*/
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
/*	��ɫ����															*/
/*																		*/
/*	��	STATE_RED														*/
/*	��	STATE_GREEN 													*/
/*	��	STATE_GRAY 														*/
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
/*	������															*/
/*																		*/
/* MAX_ELESELFTESTERROR 		ϵͳ�ϵ��Լ����						*/
/* MAX_PERIODSELFTESTERROR		ϵͳ�������Լ����						*/
/* MAX_CONDATAERROR 			�������ݴ���							*/
/* MAX_GEODATAERROR 			�������ݴ���							*/
/* MAX_CALCERROR				�������								*/
/* MAX_CULLBACKERROR 			�زɴ���								*/
/* MAX_ERRORNUM					��������								*/
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
/*	�ƶ�����															*/
/*																		*/
/*	B1�ƶ�	BRAKE_B1													*/
/*	B2�ƶ�	BRAKE_B2													*/
/*	B3�ƶ�	BRAKE_B3													*/
/*	B4�ƶ�	BRAKE_B4													*/
/*	B5�ƶ�	BRAKE_B5													*/
/*	B6�ƶ�	BRAKE_B6													*/
/*	B7�ƶ�	BRAKE_B7													*/
/*	EB�ƶ�	BRAKE_EB													*/
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
/*	ǣ������															*/
/*																		*/
/*	P1ǣ��	TRACTION_P1													*/
/*	P2ǣ��	TRACTION_P2													*/
/*	P3ǣ��	TRACTION_P3													*/
/*	P4ǣ��	TRACTION_P4													*/
/*	�յ�	TRACTION_P0													*/
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
/*	���ٵ���Ͷ������״�												*/
/*																		*/
/*	������λA	TACHO_PHASEA											*/
/*	������λB	TACHO_PHASEB											*/
/*	��λA��Bǰ	TACHO_PHASEA_AHEAD										*/
/*	��λB��Aǰ	TACHO_PHASEB_AHEAD										*/
/*	������ǰ��	DOPPLER_FORWARD											*/
/*	�����պ���	DOPPLER_BACKWARD										*/
/*	���ٻ�/�����յ�λʱ������	TACHO_DOPPLER_PULSE_TTMS				*/
/*	���ٻ�/������10ms����	TACHO_DOPPLER_PULSE_10MS					*/
/*	���ٻ�/������20ms����	TACHO_DOPPLER_PULSE_20MS					*/
/*	���ٻ�/������30ms����	TACHO_DOPPLER_PULSE_30MS					*/
/*	���ٻ�/������40ms����	TACHO_DOPPLER_PULSE_40MS					*/
/*	���ٻ�/������50ms����	TACHO_DOPPLER_PULSE_50MS					*/
/*	���ٻ�/������100ms����	TACHO_DOPPLER_PULSE_100MS					*/
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
/*	��																	*/
/*																		*/
/*	TCM	ATPATO_TCMBOARD													*/
/*	SLM	ATPATO_SLMBOARD													*/
/*	CIOM-1	ATPATO_CIOM1BOARD											*/
/*	CIOM-2	ATPATO_CIOM2BOARD											*/
/*	MPM	ATPATO_MPMBOARD													*/
/*	DIM	ATPATO_DIMBOARD													*/
/*	Demo_Board	ATPATO_DEMOBOARD										*/
/*	��������	BOARD_STATEOK											*/
/*	�������	BOARD_STATEFAIL											*/
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
/*	����汾��															*/
/*																		*/
/*	ȡ����λ�����ε���													*/
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