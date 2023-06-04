#ifndef CPLACEABLE_H
#define CPLACEABLE_H

#include "Types.h"

class CPlaceable {
public:
	// uint32_t*	vtbl;   // Указатель на виртуальную таблицу методов для этого объекта
	virtual void _destruct() = 0;
	RwV3D		 pos;	 // Позиция RwV3D +4
	float		 angle;	 // Угол по оси Z +16
	RwMatrix *	 matrix; // Указатель на матрицу позиции и вращения +20

	/**
	 * @brief Возвращает указатель на матрицу объекта
	 * @details Если указатель не валиден, но не нулевой, то вернет nullptr
	 * @return указатель на матрицу
	 */
	RwMatrix *getMatrix();

	/**
	 * @brief Поворачивает объект
	 * @param X
	 * @param Y
	 * @param Z
	 * @return Угол Z?
	 */
	float setRotation( float X, float Y, float Z );
	/**
	 * @brief Поворачивает объект
	 * @param rot
	 * @return Угол Z?
	 */
	float setRotation( RwV3D rot );
	int	  setHeading( float Zangle );
	/**
	 * @brief Получает текущий поворот объекта
	 * @return Угол Z
	 */
	long double getRotation();
	/**
	 * @brief Получает позицию объекта из матрицы
	 * @return Координаты объекта
	 */
	RwV3D getPosition();
	/**
	 * @brief Получает смещение относительно текущего объекта
	 * @details Координаты в векторе смещения: слева/справа, спереди/сзади, сверху/снизу
	 * @param offset вектор смещения
	 * @return Координаты смещенные на вектор
	 */
	RwV3D getPositionOffset( RwV3D offset );
	/**
	 * @brief Устанавливает позицию объекта в мире
	 * @param pos Координаты объекта
	 */
	void setPosition( RwV3D pos );
	/**
	 * @brief Смещает позицию объекта относительно мира
	 * @param pos Вектор смещения
	 */
	void addPosition( RwV3D pos );
	/**
	 * @brief Смещает позицию объекта относительно самого объекта
	 * @param pos Вектор смещения
	 */
	void addOffsetPosition( RwV3D pos );
	/**
	 * @brief Возвращает угол Z
	 * @return Угол Z
	 */
	float getAngleZ();
	/**
	 * @brief Устанавливает угол Z
	 * @param angle Угол Z
	 */
	void setAngleZ( float angle );
	/**
	 * @brief Поворачивает объект по Z
	 * @param angle Угол поворота
	 */
	void addAngleZ( float angle );

	bool isValid();
};

#endif // CPLACEABLE_H
