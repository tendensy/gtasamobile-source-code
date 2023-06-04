#ifndef CVEHICLEPOOL_H
#define CVEHICLEPOOL_H

#include "../Transport/CHeli.h"
#include "CPhysicalPool.h"

class CVehiclePool : public CPhysicalPool<CHeli> {
public:
	CVehicle *atIndex( int id );
	int		  handleOf( CVehicle *veh );
	CVehicle *atHandle( int handle );

	/// Чинит транспорт. Не восстанавливает HP
	void fix();
	/// Воспроизведение гудка
	void playCarHorn();

	/**
	 * @brief Устанавливает количество ХП транспорту
	 * @param hp количество ХП
	 */
	void setHitpoints( float hp );

	/// Чинит транспорт с восстановлением ХП до 1000
	void repair();

	/// Закрывает машины?
	void lockCar();

	void lockIfEmpty();
	void unlockNotEmpty();

	void processAntiCollision( const std::deque<CVehicle *> &exclude, const RwV3D &pos = RwV3D( 0, 0, 0 ),
							   const float &dist = 10.0f );

	void setAngularVelocity( RwV3D angularVelocity );

	int getScmHandle( CVehicle *veh );

	void kickOffDrivers();
	void kickOffPassengers();
	void kickOffAll();
};

#endif // CVEHICLEPOOL_H
