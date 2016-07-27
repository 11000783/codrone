/*
  CoDrone.h - CoDrone library
  Copyright (C) 2014 RoboLink.  All rights reserved.
  LastUpdate : 2016-04-20
*/

#ifndef CoDrone_h
#define CoDrone_h
#include "Arduino.h"
#include <avr/interrupt.h>

/***********************************************************************/


/***********************************************************************/
//////////////////////////typedef///////////////////////////////////////
/***********************************************************************/

typedef int32_t s32;
typedef int16_t s16;
typedef int8_t s8;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

/***********************************************************************/
////////////////////////Serial Select////////////////////////////////////
/***********************************************************************/
#if defined(UBRRH) || defined(UBRR0H)
#define FIND_HWSERIAL0
#endif

#if defined(UBRR1H)
#define FIND_HWSERIAL1
#endif

#if defined (FIND_HWSERIAL1)	//Serial Other Setting
#define DRONE_SERIAL 		Serial1		//drone serial
#define DEBUG_SERIAL    Serial		//debug serial1

#else	//Serial Smart Setting
#define DRONE_SERIAL 		Serial		//drone serial	
#define DEBUG_SERIAL    Serial1		//debug serial1

#endif

/***********************************************************************/
////////////////////////////HEADER///////////////////////////////////////
/***********************************************************************/
//START CODE
#define START1    	0x0A
#define START2   		0x55

/***********************************************************************/

#define MAX_PACKET_LENGTH 	100

/***********************************************************************/

#define	SEND_CHECK_TIME    		3

/***********************************************************************/

#define ROLL								CoDrone.roll
#define PITCH								CoDrone.pitch
#define YAW									CoDrone.yaw
#define THROTTLE						CoDrone.throttle

#define STATE								CoDrone.state
#define SEND_INTERVAL				CoDrone.SendInterval
#define ANALOG_OFFSET				CoDrone.analogOffset
#define BATTERY							CoDrone.battery
#define RSSI								CoDrone.rssi

#define AttitudeROLL				CoDrone.attitudeRoll
#define AttitudePITCH				CoDrone.attitudePitch
#define AttitudeYAW					CoDrone.attitudeYaw

/***********************************************************************/

#define DiscoverStop  			cType_LinkDiscoverStop
#define DiscoverStart  			cType_LinkDiscoverStart

#define PollingStop					cType_LinkRssiPollingStop
#define PollingStart				cType_LinkRssiPollingStart

#define	PAIRING							CoDrone.pairing

#define LinkModeMute 				LinkBroadcast_Mute
#define LinkModeActive			LinkBroadcast_Active
#define LinkModePassive 		LinkBroadcast_Passive

#define	NearbyDrone    			1
#define	ConnectedDrone  		2
#define AddressInputDrone 	3

//eeprom address
#define	EEP_AddressCheck   	10
#define	EEP_AddressFirst  	11
#define	EEP_AddressEnd  		15

/////////////////////////////////////////////////////////////////////////

#define FREE_PLAY					0
#define TEAM_RED					1
#define TEAM_BLUE					2
#define TEAM_GREEN				3
#define TEAM_YELLOW				4

#define MAX_ENERGY				8
/**********************	IR DATA****************************************/

#define FREE_MISSILE			0xaa01
#define RED_MISSILE				0xbb01
#define BLUE_MISSILE			0xcc01
#define GREEN_MISSILE			0xdd01
#define YELLOW_MISSILE		0xee01

/***********************************************************************/

#define Flight 						dMode_Flight
#define FlightNoGuard			dMode_FlightNoGuard,
#define FlightFPV					dMode_FlightFPV
#define Drive 				 		dMode_Drive
#define DriveFPV					dMode_DriveFPV

#define Absolute 					cSet_Absolute
#define Relative		 			cSet_Relative

#define TakeOff 					fEvent_TakeOff
#define FlipFront					fEvent_FlipFront
#define FlipRear					fEvent_FlipRear
#define FlipLeft					fEvent_flipLeft
#define FlipRight					fEvent_FlipRight
#define Stop							fEvent_Stop
#define Landing						fEvent_Landing
#define TurnOver					fEvent_TurnOver
#define Shot							fEvent_Shot
#define UnderAttack				fEvent_UnderAttack
#define Square						fEvent_Square
#define CircleLeft				fEvent_CircleLeft
#define CircleRight				fEvent_CircleRight
#define Rotate180					fEvent_Rotate180

#define RollIncrease			trim_RollIncrease
#define RollDecrease			trim_RollDecrease
#define PitchIncrease			trim_PitchIncrease
#define PitchDecrease			trim_PitchDecrease
#define YawIncrease				trim_YawIncrease
#define YawDecrease				trim_YawDecrease
#define ThrottleIncrease	trim_ThrottleIncrease
#define ThrottleDecrease	trim_ThrottleDecrease

/***********************************************************************/
/////////////////////////LINK MODULE/////////////////////////////////////
/***********************************************************************/
enum ModeLink
{
	linkMode_None = 0,	 	 	///< ����
	linkMode_Boot,	 	 	 		///< ���� 	 	
	linkMode_Ready,	 		 		///< ���(���� ��)
	linkMode_Connecting,	 	///< ��ġ ���� ��
	linkMode_Connected,	 	 	///< ��ġ ���� �Ϸ�
	linkMode_Disconnecting,	///< ��ġ ���� ���� ��
	linkMode_ReadyToReset,	///< ���� ���(1�� �ڿ� ��ġ ����)	
	linkMode_EndOfType
};

enum ModeLinkBroadcast
{
	LinkBroadcast_None = 0, ///< ����
	LinkBroadcast_Mute, 		///< LINK ��� ������ �۽� �ߴ� . �Ƶ��̳� �߿��� �ٿ�ε�
	LinkBroadcast_Active, 	///< ��Ʈ�� ���� ��� . ��� ��ȯ �޼��� ����
	LinkBroadcast_Passive, 	///< ��Ʈ�� ���� ��� . ��� ��ȯ �޼��� �������� ����
	LinkBroadcast_EndOfType
};

enum EventLink
	{
		linkEvent_None = 0,									///< ����
		
		linkEvent_SystemReset,							///< �ý��� ����
		
		linkEvent_Initialized,							///< ��ġ �ʱ�ȭ �Ϸ�
		
		linkEvent_Scanning,									///< ��ġ �˻� ����
		linkEvent_ScanStop,									///< ��ġ �˻� �ߴ�

		linkEvent_FoundDroneService,				///< ��� ���� �˻� �Ϸ�

		linkEvent_Connecting,								///< ��ġ ���� ����		
		linkEvent_Connected,								///< ��ġ ����

		linkEvent_ConnectionFaild,					///< ���� ����
		linkEvent_ConnectionFaildNoDevices,	///< ���� ���� - ��ġ�� ����
		linkEvent_ConnectionFaildNotReady,	///< ���� ���� - ��� ���°� �ƴ�

		linkEvent_PairingStart,							///< �� ����
		linkEvent_PairingSuccess,						///< �� ����
		linkEvent_PairingFaild,							///< �� ����

		linkEvent_BondingSuccess,						///< Bonding ����

		linkEvent_LookupAttribute,					///< ��ġ ���� �� �Ӽ� �˻�(GATT Event ����)

		linkEvent_RssiPollingStart,					///< RSSI Ǯ�� ����
		linkEvent_RssiPollingStop,					///< RSSI Ǯ�� ����

		linkEvent_DiscoverService,										///< ���� �˻�
		linkEvent_DiscoverCharacteristic,							///< �Ӽ� �˻�
		linkEvent_DiscoverCharacteristicDroneData,		///< �Ӽ� �˻�
		linkEvent_DiscoverCharacteristicDroneConfig,	///< �Ӽ� �˻�
		linkEvent_DiscoverCharacteristicUnknown,			///< �Ӽ� �˻�
		linkEvent_DiscoverCCCD,				///< CCCD �˻�

		linkEvent_ReadyToControl,			///< ���� �غ� �Ϸ�

		linkEvent_Disconnecting,			///< ��ġ ���� ���� ����
		linkEvent_Disconnected,				///< ��ġ ���� ���� �Ϸ�

		linkEvent_GapLinkParamUpdate,	///< GAP_LINK_PARAM_UPDATE_EVENT

		linkEvent_RspReadError,				///< RSP �б� ����
		linkEvent_RspReadSuccess,			///< RSP �б� ����

		linkEvent_RspWriteError,			///< RSP ���� ����
		linkEvent_RspWriteSuccess,		///< RSP ���� ����

		linkEvent_SetNotify,					///< Notify Ȱ��ȭ

		linkEvent_Write,							///< ������ ���� �̺�Ʈ

		EndOfType
	};


/***********************************************************************/
//////////////////////////////DRONE/////////////////////////////////////
/***********************************************************************/
enum DataType
{
	dType_None = 0, 					///< ����
	
	// �ý��� ����
	dType_Ping, 							///< ��� Ȯ��(reserve)
	dType_Ack, 								///< ������ ���ſ� ���� ����
	dType_Error, 							///< ����(reserve, ��Ʈ �÷��״� ���Ŀ� ����)
	dType_Request, 						///< ������ Ÿ���� ������ ��û
	dType_DeviceName, 				///< ��ġ�� �̸� ����
	
	// ����, ���
	dType_Control = 0x10, 		///< ����
	dType_Command, 						///< ���
	dType_Command2, 					///< ���� ���(2���� ������ ���ÿ� ����)
	DType_Command3, 					///< ���� ���(3���� ������ ���ÿ� ����)
	
	// LED
	dType_LedMode = 0x20, 		///< LED ��� ����
	dType_LedMode2, 					///< LED ��� 2�� ����
	dType_LedModeCommand, 		///< LED ���, Ŀ�ǵ�
	dType_LedModeCommandIr, 	///< LED ���, Ŀ�ǵ�, IR ������ �۽�
	dType_LedModeColor, 			///< LED ��� 3�� ���� ����
	dType_LedModeColor2, 			///< LED ��� 3�� ���� ���� 2��
	dType_LedEvent, 					///< LED �̺�Ʈ
	dType_LedEvent2, 					///< LED �̺�Ʈ 2��,
	dType_LedEventCommand, 		///< LED �̺�Ʈ, Ŀ�ǵ�
	dType_LedEventCommandIr,	///< LED �̺�Ʈ, Ŀ�ǵ�, IR ������ �۽�
	dType_LedEventColor, 			///< LED �̺�Ʈ 3�� ���� ����
	dType_LedEventColor2, 		///< LED �̺�Ʈ 3�� ���� ���� 2��
	
	// ����
	dType_Address = 0x30, 		///< IEEE address
	dType_State, 							///< ����� ����(���� ���, ��������, ���͸���)
	dType_Attitude, 					///< ����� �ڼ�(Vector)
	dType_GyroBias,						///< ���̷� ���̾ ��(Vector)
	dType_TrimAll, 						///< ��ü Ʈ�� (����+����)�
	dType_TrimFlight,					///< ���� Ʈ��
	dType_TrimDrive, 					///< ���� Ʈ��
			
	// ������ �ۼ���	
	dType_IrMessage = 0x40, 			///< IR ������ �ۼ���
		
	// ����
	dType_ImuRawAndAngle = 0x50, 	///< IMU Raw + Angle
	dType_Pressure, 							///< �з� ���� ������
	dType_ImageFlow, 							///< ImageFlow
	dType_Button, 								///< ��ư �Է�
	dType_Batery, 								///< ���͸�
	dType_Motor, 									///< ���� ���� �� ���� ���� �� Ȯ��
	dType_Temperature, 						///< �µ�
	
	// ��ũ ����
	dType_LinkState = 0xE0,				///< ��ũ ����� ����
	dType_LinkEvent,							///< ��ũ ����� �̺�Ʈ
	dType_LinkEventAddress,				///< ��ũ ����� �̺�Ʈ + �ּ�
	dType_LinkRssi,								///< ��ũ�� ����� ��ġ�� RSSI��
	dType_LinkDiscoveredDevice,		///< �˻��� ��ġ
	dType_LinkPasscode,          	///< ������ ��� ��ġ�� ��ȣ ����
	dType_StringMessage = 0xD0, 	///< ���ڿ� �޼���
	dType_EndOfType
};

/***********************************************************************/
enum CommandType
{
	cType_None = 0, 								///< �̺�Ʈ ����
	
	// ����	
	cType_ModeDrone = 0x10, 				///< ��� ���� ��� ��ȯ
	
	// ����
	cType_Coordinate = 0x20, 				///< ���� ���� ����
	cType_Trim, 										///< Ʈ�� ����
	cType_FlightEvent, 							///< ���� �̺�Ʈ ����
	cType_DriveEvent, 							///< ���� �̺�Ʈ ����
	cType_Stop, 										///< ����
	cType_ResetHeading = 0x50, 			///< ������ ����(�ۼַ�Ʈ ��� �� �� ���� heading�� 0���� ����)
	cType_ClearGyroBiasAndTrim, 		///< ���̷� ���̾�� Ʈ�� ���� �ʱ�ȭ
	
	// ���
	cType_PairingActivate = 0x80, 	///< �� Ȱ��ȭ
	cType_PairingDeactivate, 				///< �� ��Ȱ��ȭ
	cType_TerminateConnection, 			///< ���� ����
	
	// ��û
	cType_Request = 0x90, 					///< ������ Ÿ���� ������ ��û
	
	// ��ũ ����
	cType_LinkModeBroadcast = 0xE0, ///< LINK �ۼ��� ��� ��ȯ
	cType_LinkSystemReset, 					///< �ý��� �����
	cType_LinkDiscoverStart, 				///< ��ġ �˻� ����
	cType_LinkDiscoverStop, 				///< ��ġ �˻� �ߴ�
	cType_LinkConnect, 							///< ����
	cType_LinkDisconnect, 					///< ���� ����
	cType_LinkRssiPollingStart, 		///< RSSI ���� ����
	cType_LinkRssiPollingStop, 			///< RSSI ���� �ߴ�

	cType_EndOfType
};

/***********************************************************************/
enum ModeDrone
{
	dMode_None = 0, 			///< ����
	dMode_Flight = 0x10, 	///< ���� ���(���� ����)
	dMode_FlightNoGuard, 	///< ���� ���(���� ����)
	dMode_FlightFPV, 			///< ���� ���(FPV)
	dMode_Drive = 0x20, 	///< ���� ���
	dMode_DriveFPV, 			///< ���� ���(FPV)
	dMode_Test = 0x30, 		///< �׽�Ʈ ���
	dMode_EndOfType
};

/***********************************************************************/
enum ModeVehicle
{
	vMode_None = 0,
	vMode_Boot, 					///< ����
	vMode_Wait, 					///< ���� ��� ����
	vMode_Ready, 					///< ��� ����
	vMode_Running, 				///< ���� �ڵ� ����
	vMode_Update, 				///< �߿��� ������Ʈ
	vMode_UpdateComplete,	///< �߿��� ������Ʈ �Ϸ�
	vMode_Error, 					///< ����
	vMode_EndOfType
};

/***********************************************************************/
enum ModeFlight
{
	fMode_None = 0,
	fMode_Ready, 					///< ���� �غ�
	fMode_TakeOff, 				///< �̷� (Flight�� �ڵ���ȯ)
	fMode_Flight, 				///< ����
	fMode_Flip, 					///< ȸ��
	fMode_Stop, 					///< ���� ����
	fMode_Landing, 				///< ����
	fMode_Reverse, 				///< ������
	fMode_Accident, 			///< ��� (Ready�� �ڵ���ȯ)
	fMode_Error, 					///< ����
	fMode_EndOfType
};

/***********************************************************************/
enum ModeDrive
{
	dvMode_None = 0,
	dvMode_Ready, 				///< �غ�
	dvMode_Start, 				///< ���
	dvMode_Drive, 				///< ����
	dvMode_Stop, 					///< ���� ����
	dvMode_Accident, 			///< ��� (Ready�� �ڵ���ȯ)
	dvMode_Error, 				///< ����
	dvMode_EndOfType
};

/***********************************************************************/
enum SensorOrientation
{
	senOri_None = 0,
	senOri_Normal, 				///< ����
	senOri_ReverseStart, 	///< �������� ����
	senOri_Reverse, 			///< ������
	senOri_EndOfType
};

/***********************************************************************/
enum Coordinate
{
	cSet_None = 0, 				///< ����
	cSet_Absolute, 				///< ���� ��ǥ��
	cSet_Relative, 				///< ��� ��ǥ��
	cSet_EndOfType
};

/***********************************************************************/

enum Trim
{
	trim_None = 0, 					///< ����
	trim_RollIncrease, 			///< Roll ����
	trim_RollDecrease, 			///< Roll ����
	trim_PitchIncrease, 		///< Pitch ����
	trim_PitchDecrease, 		///< Pitch ����
	trim_YawIncrease, 			///< Yaw ����
	trim_YawDecrease, 			///< Yaw ����
	trim_ThrottleIncrease, 	///< Throttle ����
	trim_ThrottleDecrease, 	///< Throttle ����
	trim_EndOfType
};

/***********************************************************************/

enum FlightEvent
{
	fEvent_None = 0, 			///< ����
	fEvent_TakeOff, 			///< �̷�
	fEvent_FlipFront, 		///< ȸ��
	fEvent_FlipRear, 			///< ȸ��
	fEvent_flipLeft, 			///< ȸ��
	fEvent_FlipRight, 		///< ȸ��
	fEvent_Stop, 					///< ����
	fEvent_Landing, 			///< ����
	fEvent_TurnOver, 			///< ������
	fEvent_Shot, 					///< �̻����� �� �� ������
	fEvent_UnderAttack, 	///< �̻����� ���� �� ������
	fEvent_Square, 				///< ������ ����
	fEvent_CircleLeft, 		///< �������� ȸ��
	fEvent_CircleRight, 	///< ���������� ȸ��
	fEvent_Rotate180,			///< 180�� ȸ��
	fEvent_EndOfType
};

enum DriveEvent
{
	dEvent_None = 0,
	dEvent_Ready, 				///< �غ�
	dEvent_Start, 				///< ���
	dEvent_Drive, 				///< ����
	dEvent_Stop, 					///< ���� ����
	dEvent_Accident, 			///< ��� (Ready�� �ڵ���ȯ)
	dEvent_Error, 				///< ����
	dEvent_EndOfType
};

/***********************************************************************/
enum Request
{		
	// ����
	Req_Address = 0x30, 				///< IEEE address
	Req_State, 									///< ����� ����(���� ���, ��������, ���͸���)
	Req_Attitude, 							///< ����� �ڼ�(Vector)
	Req_GyroBias, 							///< ���̷� ���̾ ��(Vector)
	Req_TrimAll, 								///< ��ü Ʈ��
	Req_TrimFlight, 						///< ���� Ʈ��
	Req_TrimDrive, 							///< ���� Ʈ��
		
	// ����
	Req_ImuRawAndAngle = 0x50, 	///< IMU Raw + Angle
	Req_Pressure, 							///< �з� ���� ������
	Req_ImageFlow, 							///< ImageFlow
	Req_Button, 								///< ��ư �Է�
	Req_Batery, 								///< ���͸�
	Req_Motor, 									///< ���� ���� �� ���� ���� �� Ȯ��
	Req_Temperature, 						///< �µ�
	Req_EndOfType
};

/***********************************************************************/
enum ModeLight
{
  Light_None,
  WaitingForConnect, 					///< ���� ��� ����
  Connected,
  
  EyeNone = 0x10,
  EyeHold, 										///< ������ ������ ��� ��
  EyeMix, 										///< ���������� LED �� ����
  EyeFlicker, 								///< ������
  EyeFlickerDouble, 					///< ������(�� �� �����̰� ������ �ð���ŭ ����)
  EyeDimming, 								///< ��� �����Ͽ� õõ�� ������
  
  ArmNone = 0x40,
  ArmHold, 										///< ������ ������ ��� ��
  ArmMix, 										///< ���������� LED �� ����
  ArmFlicker, 								///< ������
  ArmFlickerDouble, 					///< ������(�� �� �����̰� ������ �ð���ŭ ����)
  ArmDimming, 								///< ��� �����Ͽ� õõ�� ������
  ArmFlow, 										///< �տ��� �ڷ� �帧
  ArmFlowReverse, 						///< �ڿ��� ������ �帧
  EndOfLedMode
};

/***********************************************************************/
enum Colors
{
	AliceBlue, AntiqueWhite, Aqua,
	Aquamarine, Azure, Beige,
	Bisque, Black, BlanchedAlmond,
	Blue, BlueViolet, Brown,
	BurlyWood, CadetBlue, Chartreuse,
	Chocolate, Coral, CornflowerBlue,
	Cornsilk, Crimson, Cyan,
	DarkBlue, DarkCyan, DarkGoldenRod,
	DarkGray, DarkGreen, DarkKhaki,
	DarkMagenta, DarkOliveGreen, DarkOrange,
	DarkOrchid, DarkRed, DarkSalmon,
	DarkSeaGreen, DarkSlateBlue, DarkSlateGray,
	DarkTurquoise, DarkViolet, DeepPink,
	DeepSkyBlue, DimGray, DodgerBlue,
	FireBrick, FloralWhite, ForestGreen,
	Fuchsia, Gainsboro, GhostWhite,
	Gold, GoldenRod, Gray,
	Green, GreenYellow, HoneyDew,
	HotPink, IndianRed, Indigo,
	Ivory, Khaki, Lavender,
	LavenderBlush, LawnGreen, LemonChiffon,
	LightBlue, LightCoral, LightCyan,
	LightGoldenRodYellow, LightGray, LightGreen,
	LightPink, LightSalmon, LightSeaGreen,
	LightSkyBlue, LightSlateGray, LightSteelBlue,
	LightYellow, Lime, LimeGreen,
	Linen, Magenta, Maroon,
	MediumAquaMarine, MediumBlue, MediumOrchid,
	MediumPurple, MediumSeaGreen, MediumSlateBlue,
	MediumSpringGreen, MediumTurquoise, MediumVioletRed,
	MidnightBlue, MintCream, MistyRose,
	Moccasin, NavajoWhite, Navy,
	OldLace, Olive, OliveDrab,
	Orange, OrangeRed, Orchid,
	PaleGoldenRod, PaleGreen, PaleTurquoise,
	PaleVioletRed, PapayaWhip, PeachPuff,
	Peru, Pink, Plum,
	PowderBlue, Purple, RebeccaPurple,
	Red, RosyBrown, RoyalBlue,
	SaddleBrown, Salmon, SandyBrown,
	SeaGreen, SeaShell, Sienna,
	Silver, SkyBlue, SlateBlue,
	SlateGray, Snow, SpringGreen,
	SteelBlue, Tan, Teal,
	Thistle, Tomato, Turquoise,
	Violet, Wheat, White,
	WhiteSmoke, Yellow, YellowGreen,
	EndOfColor
};

/***********************************************************************/

class CoDroneClass
{
public:

	CoDroneClass(void);

/////////////////////////////////////////////////////////////////////////

	void begin(long baud);
	
	void Receive(void);
	
	void Control();
	void Control(int interval);

	void Send_Command(int sendCommand, int sendOption);	
	void Send_Processing(byte _data[], byte _length, byte _crc[]);
	
/////////////////////////////////////////////////////////////////////////

	void LinkReset();
	void Send_LinkState();
	void Send_LinkModeBroadcast(byte mode);
	
/////////////////////////////////////////////////////////////////////////
	
	void AutoConnect(byte mode);
  void AutoConnect(byte mode, byte address[]);	
	void Send_ConnectAddressInputDrone(byte address[]);
	void Send_ConnectConnectedDrone();
	void Send_ConnectNearbyDrone();	
	void Send_Connect(byte index);
	void Send_Disconnect();		
	void Send_Discover(byte action);
	void Send_Check(byte _data[], byte _length, byte _crc[]);

/////////////////////////////////////////////////////////////////////////

	void Send_Ping();
	void Send_ResetHeading();			
	void Send_RSSI_Polling(byte action);	
	void Send_DroneMode(byte event);
	void Send_Coordinate(byte mode);	
	void Send_ClearGyroBiasAndTrim();		
	void DroneModeChange(byte event);			
	void FlightEvent(byte event);
	void DriveEvent(byte event);
	
/////////////////////////////////////////////////////////////////////////

	void BattleShooting();
	void BattleReceive();
	void BattleBegin(byte teamSelect);	
	void BattleDamageProcess();	
	
/////////////////////////////////////////////////////////////////////////
		
	void Request_DroneState();	
	void Request_DroneAttitude();
	void Request_DroneGyroBias();	
	
	void Request_TrimAll();
	void Request_TrimFlight();
	void Request_TrimDrive();	
	
	void Request_ImuRawAndAngle();
	void Request_Pressure();
	void Request_ImageFlow();
	void Request_Button();	
	void Request_Battery();	
	void Request_Motor();	
	void Request_Temperature();
	
/////////////////////////////////////////////////////////////////////////

	void Set_Trim(byte event);
	void Set_TrimReset();
	void Set_TrimAll(int _roll, int _pitch, int _yaw, int _throttle, int _wheel);
	void Set_TrimFlight(int _roll, int _pitch, int _yaw, int _throttle);
	void Set_TrimDrive(int _wheel);

/////////////////////////////////////////////////////////////////////////

	void LedColor(byte sendMode, byte sendColor, byte sendInterval);
	void LedColor(byte sendMode, byte r, byte g, byte b, byte sendInterval);
	void LedColor(byte sendMode, byte sendColor[], byte sendInterval);
	
	void LedEvent(byte sendMode, byte sendColor, byte sendInterval, byte sendRepeat);
	void LedEvent(byte sendMode, byte sendColor[], byte sendInterval, byte sendRepeat);
	void LedEvent(byte sendMode, byte r, byte g, byte b, byte sendInterval, byte sendRepeat);
	
/////////////////////////////////////////////////////////////////////////
			
	void LinkStateCheck();
	void ReceiveEventCheck();
	int LowBatteryCheck(byte value);
	void DisplayRSSI();
	
/////////////////////////////////////////////////////////////////////////

	void LED_PORTC(int value);
	void LED_DDRC(int value);
	void LED_Move_Radar(byte display);
	void LED_Start();
	void LED_Move_Slide();
	void LED_Connect();
	void LED_Standard();
	void LED_Blink(int time, int count);
	
/////////////////////////////////////////////////////////////////////////

	unsigned short CRC16_Make(unsigned char *buf, int len); //CRC16-CCITT Format
	boolean CRC16_Check(unsigned char data[], int len, unsigned char crc[]);
	
/////////////////////////////////////////////////////////////////////////

	void PrintDroneAddress();	
	void DisplayAddress(byte count);
	
	void ReadSensor(void);
	void PrintSensor(void);
	
/////////////////////////////////////////////////////////////////////////
	
	void ButtonPreesHoldWait(int button);
	void ButtonPreesHoldWait(int button1, int button2);	
	
	int AnalogScaleChange(int analogValue);			

/////////////////////////////////////////////////////////////////////////

	boolean TimeCheck(word interval); 						//milliseconds
	boolean TimeOutSendCheck(word interval); //milliseconds		
	boolean TimeCheckBuzz(word interval); 				//microseconds
	
/////////////////////////////////////////////////////////////////////////

	void Buzz(long frequency, int tempo);
	void BeepWarning(int count);

/////////////////////////////////////////////////////////////////////////

	byte cmdBuff[MAX_PACKET_LENGTH];
	byte dataBuff[MAX_PACKET_LENGTH];
	byte crcBuff[2];
	
	byte checkHeader;
	int cmdIndex;
	int receiveDtype;
	int receiveLength;
	int receiveEventState;
	int receiveLinkState;
	int receiveLikMode;
	int receiveComplete;
	int receiveCRC;
			
/////////////////////////////////////////////////////////////////////////

	byte displayMode;	//smar inventor : default 1
	byte debugMode;		//smar inventor : default 0
	
	byte discoverFlag;
	byte connectFlag;
			
	boolean pairing;
	
	int SendInterval; //millis seconds		
	int analogOffset;
	byte displayLED;

	byte timeOutRetry;
	
	byte sendCheckFlag;
	
	byte receiveAttitudeSuccess;
	
	int energy;
	
	byte team;
	unsigned long weapon;
	
/////////////////////////////////////////////////////////////////////////
	
	byte devCount;
	byte devFind[3];
	
	int devRSSI0;
	int devRSSI1;
	int devRSSI2;
		
	byte devName0[20];
	byte devName1[20];
	byte devName2[20];
		
	byte devAddress0[6];
	byte devAddress1[6];
	byte devAddress2[6];
	
	byte devAddressBuf[6];
	byte devAddressConnected[6];
	
/////////////////////////////////////////////////////////////////////////
	
	int roll;
	int pitch;
	int yaw;
	int throttle;
		
	int attitudeRoll;
	int attitudePitch;
	int attitudeYaw;
	
/////////////////////////////////////////////////////////////////////////
	
	int linkState;
	int rssi;
	byte battery;
		
	byte irMassageDirection;
  unsigned long	irMassageReceive;
	
	byte droneState[7];	
	byte droneIrMassage[5];	
	
	byte droneAttitude[6];
	byte droneGyroBias[6];
	byte droneTrimAll[10];		
	byte droneTrimFlight[8];
	byte droneTrimDrive[2];
	byte droneImuRawAndAngle[9];
	byte dronePressure[16];	
	byte droneImageFlow[8];
	byte droneButton[1];
	byte droneBattery[16];
	byte droneMotor[4];
	byte droneTemperature[8];

/////////////////////////////////////////////////////////////////////////

		long PreviousMillis;
		
/////////////////////////////////////////////////////////////////////////
private:
	long PreviousBuzz;		

	long timeOutSendPreviousMillis;
};

extern CoDroneClass CoDrone;

#endif 