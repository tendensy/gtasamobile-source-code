#ifndef CPEDIK_H
#define CPEDIK_H

#include "Types.h"

class CPedIK
{
public:
	class CPed				 *thisPed;
	float					RotationZ;		/* radians */
	float					RotationX;		/* radians */
	float				m_fSlopePitch;
	float	   m_fSlopePitchLimitMult;
	float				 m_fSlopeRoll;
	float				  m_fBodyRoll;
	DWORD						flags;
	// 	1 = PEDIK_GUN_REACHED_TARGET
	// 	2 = PEDIK_TORSO_USED
	// 	4 = PEDIK_USE_ARM
	// 	8 = PEDIK_SLOPE_PITCH
	// 	16 = PEDIK_EVERYTHING_USED
};

#endif // CPEDIK_H
