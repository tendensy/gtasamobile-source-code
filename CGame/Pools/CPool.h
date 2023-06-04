#ifndef CPOOL_H
#define CPOOL_H

#include "../Types.h"

template<class C> class CPool {
	uint8_t *objects;
	uint8_t *flags;
	uint32_t size; // count?
	C *		 top;
	uint8_t	 hasInitialized;
	uint8_t	 lock;
	uint16_t _pad;

public:
	void lockPool() {
		while ( lock ) Sleep( 0 );
		lock = true;
	}
	void unlockPool() { lock = false; }
	bool isLockedPool() { return lock; }
	bool tryLockPool() {
		if ( isLockedPool() ) return false;
		lock = true;
		return true;
	}

	/// Проверяет был ли пул инициализирован
	bool isInitialized() { return hasInitialized; }

	/**
	 * @brief Возвращает объект по handle
	 * @param h handle
	 * @return объект
	 */
	C *atHandle( int h ) {
		if ( flags[h >> 8] == h ) return (C *)( objects + sizeof( C ) * ( h >> 8 ) );
		return nullptr;
	}
	/**
	 * @brief Принудительно возвращает объект по handle
	 * @param h handle
	 * @return объект
	 */
	C *atHandleForce( int h ) { return (C *)( objects + sizeof( C ) * ( h >> 8 ) ); }
	/**
	 * @brief Возвращает объект по номеру
	 * @details Проверяет флаги
	 * @param id номер
	 * @return объект
	 */
	C *atIndexSafe( int id ) {
		if ( id < 0 || id > getSize() ) return nullptr;
		if ( isIndexFree( id ) ) return nullptr;
		if ( ( flags[id] & 0x80 ) == 0 ) return (C *)( objects + sizeof( C ) * id );
		// if ( flags[id] >= 0 ) return (C *)( objects + sizeof( C ) * id );
		return nullptr;
	}
	/**
	 * @brief Возвращает объект по номеру
	 * @details Игнорирует флаги
	 * @param id номер
	 * @return объект
	 */
	C *atIndex( int id ) {
		if ( id < 0 || id > getSize() ) return nullptr;
		return (C *)( objects + sizeof( C ) * id );
	}
	/**
	 * @brief Принудительно возвращает объект по номеру
	 * @param id номер
	 * @return объект
	 */
	C *atIndexForce( int id ) { return (C *)( objects + sizeof( C ) * id ); }

	/**
	 * @brief Проверяет, что объект находится в пуле и не выгружен
	 * @param p объект
	 * @return наличие в пуле
	 */
	bool isAllocatedAtIndex( C *p ) {
		int id = getIndex( p );
		if ( id < 0 || id >= size ) return false;
		return !isIndexFree( id ) & 1;
	}

	/**
	 * @brief Проверяет, что объект выгружен
	 * @param id номер объекта
	 */
	bool isIndexFree( int id ) { return flags[id] >> 7; }

	/**
	 * @brief Получает номер объекта в пуле по объекту
	 * @param p объект
	 * @return номер объекта
	 */
	int getIndex( C *p ) { return (int)( (unsigned)p - (unsigned)( objects ) ) / sizeof( C ); }

	/**
	 * @brief Помечает номер объекта в пуле как выгруженный/не выгруженный
	 * @param id номер объека
	 * @param isFree выгружен(true)/не выгружен(false)
	 */
	void setFreeAt( int id, bool isFree ) {
		if ( isFree )
			flags[id] |= 0x80;
		else
			flags[id] &= 0x7F;
	}

	/// Возвращает размер пула
	int getSize() { return size; }

	/// Возвращает первый объект из пула
	C *getTop() { return top; }

	uint8_t *getFlags() { return flags; }
	uint8_t *getObjects() { return objects; }
};

#endif // CPOOL_H
