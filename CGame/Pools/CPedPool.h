#ifndef CPEDPOOL_H
#define CPEDPOOL_H

#include "CPhysicalPool.h"
#include "../CPed.h"

class CPedPool : public CPhysicalPool<CPed>
{
public:
	int getScmHandle(CPed *ped);
};

#endif // CPEDPOOL_H
