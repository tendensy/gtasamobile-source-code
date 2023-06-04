#ifndef CMONSTERTRUCK_H
#define CMONSTERTRUCK_H

#include "CAutomobile.h"

class CMonsterTruck : public CAutomobile {
public:
	float field_988;
	float field_98C;
	float field_990;
	float field_994;
	float field_998;
};

VALIDATE_SIZE( CMonsterTruck, 0x99C );

#endif // CMONSTERTRUCK_H
