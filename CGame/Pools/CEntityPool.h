#ifndef CENTITYPOOL_H
#define CENTITYPOOL_H

#include "CPlaceablePool.h"
#include <algorithm>
#include <deque>

template<class C> class CEntityPool : public CPlaceablePool<C> {
public:
	/**
	 * @brief Изменение модели сущностям
	 * @param index Номер модели
	 */
	void setModelIndex( eModelIndex index ) {
		for ( int i = 0; i < this->getSize(); ++i )
			if ( this->atIndex( i ) != nullptr ) this->atIndex( i )->setModelIndex( index );
	}

	/**
	 * @brief Телепортирует сущности
	 * @details Телепорт от перемещения отличается тем, что при телепорте сбрасываются скорость, анимация, вращение (опционально), повороты (кроме Z)
	 * @param X Координата X
	 * @param Y Координата Y
	 * @param Z Координата Z
	 * @param lockRotate Блокировка вращения при телепорте
	 * @return Успешность телепортации?
	 */
	void teleport( float X, float Y, float Z, bool lockRotate = true ) {
		for ( int i = 0; i < this->getSize(); ++i )
			if ( this->atIndex( i ) != nullptr ) this->atIndex( i )->teleport( X, Y, Z, lockRotate );
	}
	/**
	 * @brief Телепортирует сущности
	 * @details Телепорт от перемещения отличается тем, что при телепорте сбрасываются скорость, анимация, вращение (опционально), повороты (кроме Z)
	 * @param pos Координаты
	 * @param lockRotate Блокировка вращения при телепорте
	 * @return Успешность телепортации?
	 */
	void teleport( RwV3D pos, bool lockRotate = true ) {
		for ( int i = 0; i < this->getSize(); ++i )
			if ( this->atIndex( i ) != nullptr ) this->atIndex( i )->teleport( pos, lockRotate );
	}

	/**
	 * @brief Устанавливает видимость сущностям
	 * @param visible Видимость
	 */
	void setVisible( bool visible ) {
		for ( int i = 0; i < this->getSize(); ++i )
			if ( this->atIndex( i ) != nullptr ) this->atIndex( i )->setVisible( visible );
	}

	/**
	 * @brief Устанавливает наличие коллизии сущностям
	 * @param collision Наличие коллизии
	 */
	void setUsesCollision( bool collision, const std::deque<C *> &exclude = {} ) {
		for ( int i = 0; i < this->getSize(); ++i ) {
			if ( !this->atIndex( i ) ) continue;
			if ( std::find( exclude.begin(), exclude.end(), this->atIndex( i ) ) != exclude.end() ) continue;
			this->atIndex( i )->setUsesCollision( collision );
		}
	}
};

#endif // CENTITYPOOL_H
