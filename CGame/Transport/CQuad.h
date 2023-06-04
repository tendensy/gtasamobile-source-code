#ifndef CQUAD_H
#define CQUAD_H

#include "CAutomobile.h"

class CQuad : public CAutomobile {
public:
	void *		  m_pHandling;
	CRideAnimData m_rideAnimData;
	float		  field_9A8;
	int			  field_9AC;
	int			  field_9B0;
	int			  field_9B4;
	unsigned char m_nQuadFlags;
	char		  _pad1[3];
};

VALIDATE_SIZE( CQuad, 0x9BC );

#endif // CQUAD_H
