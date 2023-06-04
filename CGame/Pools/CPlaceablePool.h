#ifndef CPLACEABLEPOOL_H
#define CPLACEABLEPOOL_H

#include "CPool.h"

template<class C> class CPlaceablePool : public CPool<C> {
public:
	/**
	 * @brief Поворачивает объекты
	 * @param rot
	 */
	void setRotation( RwV3D rot ) {
		for ( int i = 0; i < this->getSize(); ++i )
			if ( this->atIndex( i ) != nullptr ) this->atIndex( i )->setRotation( rot );
	}

	/**
	 * @brief Устанавливает позицию объектам в мире
	 * @param pos Координаты
	 */
	void setPosition( RwV3D pos ) {
		for ( int i = 0; i < this->getSize(); ++i )
			if ( this->atIndex( i ) != nullptr ) this->atIndex( i )->setPosition( pos );
	}
	/**
	 * @brief Смещает позицию объектов относительно мира
	 * @param pos Вектор смещения
	 */
	void addPosition( RwV3D pos ) {
		for ( int i = 0; i < this->getSize(); ++i )
			if ( this->atIndex( i ) != nullptr ) this->atIndex( i )->addPosition( pos );
	}
	/**
	 * @brief Смещает позицию объектов относительно самих объектов
	 * @param pos Вектор смещения
	 */
	void addOffsetPosition( RwV3D pos ) {
		for ( int i = 0; i < this->getSize(); ++i )
			if ( this->atIndex( i ) != nullptr ) this->atIndex( i )->addOffsetPosition( pos );
	}

	/**
	 * @brief Устанавливает угол Z
	 * @param angle Угол Z
	 */
	void setAngleZ( float angle ) {
		for ( int i = 0; i < this->getSize(); ++i )
			if ( this->atIndex( i ) != nullptr ) this->atIndex( i )->setAngleZ( angle );
	}
	/**
	 * @brief Поворачивает объекты по Z
	 * @param angle Угол поворота
	 */
	void addAngleZ( float angle ) {
		for ( int i = 0; i < this->getSize(); ++i )
			if ( this->atIndex( i ) != nullptr ) this->atIndex( i )->addAngleZ( angle );
	}
};

#endif // CPLACEABLEPOOL_H
