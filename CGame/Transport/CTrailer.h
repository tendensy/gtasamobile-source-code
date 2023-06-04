#ifndef CTRAILER_H
#define CTRAILER_H

#include "CAutomobile.h"

class CTrailer : public CAutomobile {
public:
	CColPoint field_988[2];
	float	  field_9E0;
	float	  field_9E4;
	char	  field_9E8[4];
	float	  field_9EC;
	float	  field_9F0;
};

VALIDATE_SIZE( CTrailer, 0x9F4 );

#endif // CTRAILER_H
