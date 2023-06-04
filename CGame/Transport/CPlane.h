#ifndef CPLANE_H
#define CPLANE_H

#include "CAutomobile.h"

class CPlane : public CAutomobile {
public:
	float			   field_988;
	int				   field_98C;
	int				   field_990;
	int				   field_994;
	float			   field_998;
	int				   field_99C;
	int				   field_9A0;
	int				   field_9A4;
	float			   field_9A8;
	float			   field_9AC;
	float			   field_9B0;
	float			   field_9B4;
	int				   field_9B8;
	int				   field_9BC;
	unsigned int	   m_nStartedFlyingTime;
	int				   field_9C4;
	float			   field_9C8;
	float			   m_fLandingGearStatus;
	int				   field_9D0;
	class FxSystem_c **m_pGunParticles;
	unsigned char	   m_nFiringMultiplier;
	int				   field_9DC;
	int				   field_9E0;
	int				   field_9E4;
	class FxSystem_c * m_apJettrusParticles[4];
	class FxSystem_c * m_pSmokeParticle;
	unsigned int	   m_nSmokeTimer;
	bool			   m_bSmokeEjectorEnabled;
	char			   _pad[3];
};

VALIDATE_SIZE( CPlane, 0xA04 );

#endif // CPLANE_H
