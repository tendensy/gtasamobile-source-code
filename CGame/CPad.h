#ifndef CPAD_H
#define CPAD_H

#pragma pack( push, 8 )
struct CControllerState {
	unsigned short LeftStickX;
	unsigned short LeftStickY;
	unsigned short RightStickX;
	unsigned short RightStickY;
	unsigned short LeftShoulder1;
	unsigned short LeftShoulder2;
	unsigned short RightShoulder1;
	unsigned short RightShoulder2;
	unsigned short DPadUp;
	unsigned short DPadDown;
	unsigned short DPadLeft;
	unsigned short DPadRight;
	unsigned short Start;
	unsigned short Select;
	unsigned short ButtonSquare;
	unsigned short ButtonTriangle;
	unsigned short ButtonCross;
	unsigned short ButtonCircle;
	unsigned short ShockButtonL;
	unsigned short ShockButtonR;
	unsigned short m_bChatIndicated;
	unsigned short m_bPedWalk;
	unsigned short m_bVehicleMouseLook;
	unsigned short m_bRadioTrackSkip;
};
struct CPad {
	CControllerState NewState;
	CControllerState OldState;
	unsigned short	 SteeringLeftRightBuffer[10];
	int				 DrunkDrivingBufferUsed;
	CControllerState PCTempKeyState;
	CControllerState PCTempJoyState;
	CControllerState PCTempMouseState;
	char			 Phase;
	unsigned short	 Mode;
	short			 ShakeDur;
	unsigned short	 DisablePlayerControls;
	unsigned char	 ShakeFreq;
	char			 bHornHistory[5];
	unsigned char	 iCurrHornHistory;
	unsigned char	 JustOutOfFrontEnd;
	unsigned char	 bApplyBrakes;
	unsigned char	 bDisablePlayerEnterCar;
	unsigned char	 bDisablePlayerDuck;
	unsigned char	 bDisablePlayerFireWeapon;
	unsigned char	 bDisablePlayerFireWeaponWithL1;
	unsigned char	 bDisablePlayerCycleWeapon;
	unsigned char	 bDisablePlayerJump;
	unsigned char	 bDisablePlayerDisplayVitalStats;
	int				 LastTimeTouched;
	int				 AverageWeapon;
	int				 AverageEntries;
	unsigned long	 NoShakeBeforeThis;
	char			 NoShakeFreq;
	char			 __pad[3];

	static CPad *get( int playerId = 0 );
};
struct CControllerConfigManager_ActionName {
	char name[40];
};
enum class keyPriority : int { keyboard_alias, keyboard, mouse, joystick };
struct pair {
	int			keycode;
	keyPriority priority;
};
struct CControllerConfigManager_Action {
	pair data[4];
};
struct DIJOYSTATE2 {
	long		  lX;
	long		  lY;
	long		  lZ;
	long		  lRx;
	long		  lRy;
	long		  lRz;
	long		  rglSlider[2];
	unsigned long rgdwPOV[4];
	unsigned char rgbButtons[128];
	long		  lVX;
	long		  lVY;
	long		  lVZ;
	long		  lVRx;
	long		  lVRy;
	long		  lVRz;
	long		  rglVSlider[2];
	long		  lAX;
	long		  lAY;
	long		  lAZ;
	long		  lARx;
	long		  lARy;
	long		  lARz;
	long		  rglASlider[2];
	long		  lFX;
	long		  lFY;
	long		  lFZ;
	long		  lFRx;
	long		  lFRy;
	long		  lFRz;
	long		  rglFSlider[2];
};
struct CControllerConfigManager {
	bool								bForcePadDataRefresh;
	char								field_1;
	char								field_2;
	char								field_3;
	DIJOYSTATE2							OldJoyState;
	DIJOYSTATE2							NewJoyState;
	CControllerConfigManager_ActionName ActionName[59];
	char								field_B5C[17];
	CControllerConfigManager_Action		Action[59];
	char								field_12D0[16];
	char								bHasMouse;
	char								__pad[3];

	static CControllerConfigManager *get();

	const char *keyName( int action, int id );
};
#pragma pack( pop )

#endif // CPAD_H
