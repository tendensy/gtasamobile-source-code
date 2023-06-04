#ifndef COBJECTPOOL
#define COBJECTPOOL

#include "CPhysicalPool.h"
#include "../CObject.h"

class CObjectPool : public CPhysicalPool<CObject>
{
public:
	int getScmHandle(CObject *obj);
};

#endif // COBJECTPOOL
