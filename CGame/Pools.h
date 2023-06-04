#ifndef POOLS_H
#define POOLS_H

//#include "Pools/CPool.h"
#include "CBuilding.h"
#include "Pools/CIntelligencePool.h"
#include "Pools/CObjectPool.h"
#include "Pools/CPedPool.h"
#include "Pools/CVehiclePool.h"

/// Содержит в себе указатели на игровые пулы
namespace Pools {
	/// Возвращает пул людей
	static CPedPool *peds() { return *(CPedPool **)0xB74490; }
	/// Возвращает пул транспорта
	static CVehiclePool *vehicles() { return *(CVehiclePool **)0xB74494; }
	static CPool<CBuilding> *buildings() { return *(CPool<CBuilding> **)0xB74498; }
	/// Возвращает пул объектов
	static CObjectPool *objects() { return *(CObjectPool **)0xB7449C; }
	static CPool<CBuilding> *dummy() { return *(CPool<CBuilding> **)0xB744A0; }
	//	static CPool<class CColModel> colModels(){
	//		return *(CPool<class CColModel>**)0xB744A4;
	//	}
	//	static CPool<class CTask> tasks(){
	//		return *(CPool<class CTask>**)0xB744A8;
	//	}
	//	static CPool<class CEvent> events(){
	//		return *(CPool<class CEvent>**)0xB744AC;
	//	}
	/// Возвращает пул интеллигенции
	static CIntelligencePool *intelligence() { return *(CIntelligencePool **)0xB744C0; }
}; // namespace Pools

#endif // POOLS_H
