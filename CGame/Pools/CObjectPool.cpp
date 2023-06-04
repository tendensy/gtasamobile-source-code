#include "CObjectPool.h"

int CObjectPool::getScmHandle(CObject *obj)
{
	typedef int(__thiscall *CObjectPool__getHandle)(CObjectPool *_this, CObject *obj);
	return (CObjectPool__getHandle(0x465070))(this, obj);
}
