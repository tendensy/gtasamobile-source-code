#ifndef CAUTOMOBILE_H
#define CAUTOMOBILE_H

#include "../CVehicle.h"

class CBouncingPanel {
public:
	unsigned short m_nFrameId;
	unsigned short m_nAxis;
	float		   m_fAngleLimit;
	RwV3D		   m_vecRotation;
	RwV3D		   m_vecPos;
};

VALIDATE_SIZE( CBouncingPanel, 0x20 );

class CAutomobile : public CVehicle {
public:
	CDamageManager m_damageManager;	  // 1440
	CDoor		   m_doors[6];		  // 1464
	RwFrame *	   m_aCarNodes[25];	  // 1584
	CBouncingPanel m_panels[3];		  // 1684
	CDoor		   m_swingingChassis; // 1780
	CColPoint	   m_wheelColPoint[4];
	float		   wheelsDistancesToGround1[4];
	float		   wheelsDistancesToGround2[4];
	float		   field_7F4[4];
	float		   field_800;
	float		   field_804;
	float		   field_80C;
	int			   field_810[4];
	char		   field_81C[4];
	int			   field_820;
	float		   m_fWheelRotation[4];
	float		   field_838[4];
	float		   m_fWheelSpeed[4];
	int			   field_858[4];
	char		   taxiAvaliable;
	char		   field_869;
	char		   field_86A;
	char		   field_867;
	short		   m_wMiscComponentAngle;
	short		   m_wVoodooSuspension;
	int			   m_dwBusDoorTimerEnd;
	int			   m_dwBusDoorTimerStart;
	float		   field_878;
	float		   wheelOffsetZ[4];
	int			   field_88C[3];
	float		   m_fFrontHeightAboveRoad;
	float		   m_fRearHeightAboveRoad;
	float		   m_fCarTraction;
	float		   m_fNitroValue; // [0.0, 1.0] - reload, [0.0, -1.0] - usage
	int			   field_8A4;
	int			   m_fRotationBalance; // used in CHeli::TestSniperCollision
	float		   m_fMoveDirection;
	int			   field_8B4[6];
	int			   field_8C8[6];
	int			   m_dwBurnTimer;
	CEntity *	   m_pWheelCollisionEntity[4];
	CVector		   m_vWheelCollisionPos[4];
	char		   field_924;
	char		   field_925;
	char		   field_926;
	char		   field_927;
	char		   field_928;
	char		   field_929;
	char		   field_92A;
	char		   field_92B;
	char		   field_92C;
	char		   field_92D;
	char		   field_92E;
	char		   field_92F;
	char		   field_930;
	char		   field_931;
	char		   field_932;
	char		   field_933;
	char		   field_934;
	char		   field_935;
	char		   field_936;
	char		   field_937;
	char		   field_938;
	char		   field_939;
	char		   field_93A;
	char		   field_93B;
	char		   field_93C;
	char		   field_93D;
	char		   field_93E;
	char		   field_93F;
	int			   field_940;
	int			   field_944;
	float		   m_fDoomVerticalRotation;
	float		   m_fDoomHorizontalRotation;
	float		   m_fForcedOrientation;
	float		   m_fUpDownLightAngle[2];
	unsigned char  m_nNumContactWheels;
	unsigned char  m_nWheelsOnGround;
	char		   field_962;
	char		   field_963;
	float		   field_964;
	int			   field_968[4];
	void *		   pNitroParticle[2];
	char		   field_980;
	char		   field_981;
	short		   field_982;
	float		   field_984;

	virtual int ProcessAI();
	virtual int ResetSuspension();
	virtual int ProcessFlyingCarStuff();
	virtual int DoHoverSuspensionRatios();
	virtual int ProcessSuspension();

	int	 fixTire( int nWheel );
	int	 setTaxiLight( bool enable );
	void setAllTaxiLights( bool enable );
	void createNitroParticle( float a2 );
	void processNitro( char slot );
	bool hydraulicControl();
};

VALIDATE_SIZE( CAutomobile, 0x988 );

#endif // CAUTOMOBILE_H
