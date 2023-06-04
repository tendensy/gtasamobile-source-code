#ifndef CHELI_H
#define CHELI_H

#include "CAutomobile.h"

struct tHeliLight {
	CVector m_vecOrigin;
	CVector m_vecTarget;
	float	m_fTargetRadius;
	float	m_fPower;
	int		m_nCoronaIndex;
	bool	field_24; // unknown flag
	bool	m_bDrawShadow;
	char	_pad[2];
	CVector field_28[3];
};

VALIDATE_SIZE( tHeliLight, 0x4C );

class CHeli : public CAutomobile {
public:
	char			   m_nHeliFlags;			   // 2440
	char			   _pad1[3];				   // 2441
	float			   m_fLeftRightSkid;		   // 2444
	float			   m_fSteeringUpDown;		   // 2448
	float			   m_fSteeringLeftRight;	   // 2452
	float			   m_fAccelerationBreakStatus; // 2456
	int				   field_99C;				   // 2460
	int				   m_fRotorZ;				   // 2464
	int				   m_fSecondRotorZ;			   // 2468
	float			   m_fMaxAltitude;			   // 2472
	float			   field_9AC;				   // 2476
	float			   m_fMinAltitude;			   // 2480
	int				   field_9B4;				   // 2484
	char			   field_9B8;				   // 2488
	char			   m_nNumSwatOccupants;		   // 2489
	char			   m_anSwatIDs[4];			   // 2490
	char			   _pad2[2];				   // 2494
	int				   field_9C0[4];			   // 2496
	int				   field_9D0;				   // 2512
	class FxSystem_c **m_pParticlesList;		   // 2516
	char			   field_9D8[24];			   // 2520
	int				   field_9F0;				   // 2544
	CVector			   m_vecSearchLightTarget;	   // 2548
	float			   m_fSearchLightIntensity;	   // 2560
	int				   field_A04;				   // 2564
	int				   field_A08;				   // 2568
	class FxSystem_c **m_ppGunflashFx;			   // 2572
	char			   m_nFiringMultiplier;		   // 2576
	bool			   m_bSearchLightEnabled;	   // 2577
	char			   _pad3[2];				   // 2578
	float			   field_A14;				   // 2580
};

VALIDATE_SIZE( CHeli, 0xA18 );

#endif // CHELI_H
