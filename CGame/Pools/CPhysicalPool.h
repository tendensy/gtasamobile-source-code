#ifndef CPHYSICALPOOL_H
#define CPHYSICALPOOL_H

#include "CEntityPool.h"

template<class C> class CPhysicalPool : public CEntityPool<C> {
public:
	/**
	 * @brief Установливает скорость объектам
	 * @param spd скорость
	 */
	void setSpeed( RwV3D spd ) {
		for ( int i = 0; i < this->getSize(); ++i )
			if ( this->atIndex( i ) != nullptr ) this->atIndex( i )->setSpeed( spd );
	}
	/**
	 * @brief Добавляет скорость объектам
	 * @param spd скорость
	 */
	void addSpeed( RwV3D spd ) {
		for ( int i = 0; i < this->getSize(); ++i )
			if ( this->atIndex( i ) != nullptr ) this->atIndex( i )->addSpeed( spd );
	}

	/**
	 * @brief Установливает вращение объектам
	 * @param rot вращение
	 */
	void setSpinRot( RwV3D rot ) {
		for ( int i = 0; i < this->getSize(); ++i )
			if ( this->atIndex( i ) != nullptr ) this->atIndex( i )->setSpinRot( rot );
	}
	/**
	 * @brief Добавляет вращение объектам
	 * @param rot вращение
	 */
	void addSpinRot( RwV3D rot ) {
		for ( int i = 0; i < this->getSize(); ++i )
			if ( this->atIndex( i ) != nullptr ) this->atIndex( i )->addSpinRot( rot );
	}

	/**
	 * @brief Принудительное движение объектов
	 * @param mov назначение
	 */
	void applyMoveForce( RwV3D mov ) {
		for ( int i = 0; i < this->getSize(); ++i )
			if ( this->atIndex( i ) != nullptr ) this->atIndex( i )->applyMoveForce( mov );
	}
	/**
	 * @brief Принудительное указание гравитации объектам
	 * @param a Максимальное значение гравитации
	 * @param b Минимальное значение гравитации
	 * @param a4 хз
	 */
	void applyGravityForce( RwV3D a, CVector b, char a4 = 1 ) {
		for ( int i = 0; i < this->getSize(); ++i )
			if ( this->atIndex( i ) != nullptr ) this->atIndex( i )->applyGravityForce( a, b, a4 );
	}

	/// Прикрепляет объекты к поверхности под ногами/колесами
	void stickToPlace() {
		for ( int i = 0; i < this->getSize(); ++i )
			if ( this->atIndex( i ) != nullptr ) this->atIndex( i )->stickToPlace();
	}

	/// Блокирует движение объектов
	void lock() {
		for ( int i = 0; i < this->getSize(); ++i )
			if ( this->atIndex( i ) != nullptr ) this->atIndex( i )->lock();
	}
	/// Разблокирует движение объектов
	void unlock() {
		for ( int i = 0; i < this->getSize(); ++i )
			if ( this->atIndex( i ) != nullptr ) this->atIndex( i )->unlock();
	}
	/**
	 * @brief Изменяет состояние блокировки объектов
	 * @param state Новое состояние
	 */
	void toggleLock( bool state ) {
		for ( int i = 0; i < this->getSize(); ++i )
			if ( this->atIndex( i ) != nullptr ) this->atIndex( i )->toggleLock( state );
	}

	/**
	 * @brief Устанавливает использование гравитации объектам
	 * @param use_gravity состояние гравитации для объектов
	 */
	void setUsesGravity( bool use_gravity ) {
		for ( int i = 0; i < this->getSize(); ++i )
			if ( this->atIndex( i ) != nullptr ) this->atIndex( i )->setUsesGravity( use_gravity );
	}

	/**
	 * @brief Устанавливает скорость вращения объектов по оси Z
	 * @param speed скорость вращения по оси Z
	 */
	void setSpeedRotationZ( float speed ) {
		for ( int i = 0; i < this->getSize(); ++i )
			if ( this->atIndex( i ) != nullptr ) this->atIndex( i )->setSpeedRotationZ( speed );
	}
};

#endif // CPHYSICALPOOL_H
