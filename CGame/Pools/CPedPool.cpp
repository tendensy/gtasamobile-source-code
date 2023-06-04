#include "CPedPool.h"

int CPedPool::getScmHandle(CPed *ped)
{
	typedef int(__thiscall *CPedPool__getHandle)(CPedPool *_this, CPed *ped);
	return (CPedPool__getHandle(0x4442D0))(this, ped);
}
