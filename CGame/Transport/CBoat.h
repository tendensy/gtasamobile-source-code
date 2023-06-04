#ifndef CBOAT_H
#define CBOAT_H

#include "../CVehicle.h"

class CBoat : public CVehicle {
public:
	float m_fMovingHiRotation; // works as counter also 1440
	float m_fPropSpeed;		   // propeller speed 1444
	float m_fPropRotation;	   // propeller rotation (radians) 1448
	struct {
		unsigned char bOnWater : 1; // is placed on water
		unsigned char bMovingOnWater : 1;
		unsigned char bAnchored : 1;	 // is anchored
	} m_nBoatFlags;						 // 1452
	char			_pad5AD[3];			 // 1453
	struct RwFrame *m_aBoatNodes[12];	 // 1456
	CDoor			m_boatFlap;			 // for marquis model 1504
	CHandlingBoat * m_pBoatHandling;	 // 1528
	float			m_fAnchoredAngle;	 // radians, initialised with -9999.99 1532
	int				m_nAttackPlayerTime; // 1536
	int				field_604;			 // initialised with 0, not used 1540
	float	 m_fBurningTimer; // starts when vehicle health is lower than 250.0, boat blows up when it hits 5000.0 1544
	CEntity *m_pWhoDestroyedMe;				// 1548
	CVector	 m_vecBoatMoveForce;			// m_vecBoatMoveForce = m_vecMoveForce + m_vecFrictionMoveForce 1552
	CVector	 m_vecBoatTurnForce;			// m_vecBoatTurnForce = m_vecTurnForce + m_vecFrictionTurnForce 1564
	struct FxSystem_c *m_apPropSplashFx[2]; // 1576
	CVector			   m_vecWaterDamping;	// { 0.0f, 0.0f, DampingPower } 1584
	char field_63C; // initialised with 0, maybe boat handling type (@CBoat::DebugCode), possibly a leftover 1596
	unsigned char m_nPadNumber;				 // 0 - 3 // 1597
	char		  _pad63E[2];				 // 1598
	float		  m_fWaterResistance;		 // initialised with 7.0f, 0.0f - not in water 1600
	short		  m_nNumWaterTrailPoints;	 // 1604
	char		  _pad646[2];				 // 1606
	CVector2D	  m_avecWakePoints[32];		 // 1608
	float		  m_afWakePointLifeTime[32]; // 1992
	unsigned char
		m_anWakePointIntensity[32]; // m_anWakePointIntensity[i] = boat->m_vecMoveForce.Magnitude() * 100.0f; 2120
};

VALIDATE_SIZE( CBoat, 0x7E8 );

#endif // CBOAT_H
