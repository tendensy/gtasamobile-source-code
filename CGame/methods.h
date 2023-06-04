#ifndef METHODS_H
#define METHODS_H

#include "Types.h"
#include <deque>
#include <tlhelp32.h>

/// Ширина окна в пикселях
#define SCREEN_X *(int *)0x00C9C040
/// Высота окна в пикселях
#define SCREEN_Y *(int *)0x00C9C044

/// Хуй знает что и для чего. Выдрал из соба, когда пытался гравитацию машине изменить
void GetMatrixForGravity( CVector &vecGravity, CMatrix &mat );
/**
 * @brief Проверка, что на пути между двух точек \bнет заданных объектов
 * @param start Начальная точка
 * @param end Конечная точка
 * @param buildings Проверять наличие построек
 * @param vehicles Проверять наличие транспорта
 * @param peds Проверять наличие людей
 * @param objects Проверять наличие объектов
 * @param dummies Проверять наличие заглушек?
 * @param seeThroughStuff хз
 * @param ignoreSomeObjectsForCamera хз
 * @return Отсутствие преград (true)
 */
bool IsLineOfSightClear( RwV3D start, RwV3D end, bool buildings, bool vehicles, bool peds, bool objects, bool dummies,
						 bool seeThroughStuff, bool ignoreSomeObjectsForCamera );
/**
 * @brief Находит CPed игрока по handle
 * @details Аналог опкода 0A96
 * @param handle
 * @return CPed
 */
class CPed *findPlayerPed( int handle );
/**
 * @brief Нахождение угла Z между точками
 * @details Аналог опкода 05A4
 * @param x1
 * @param y1
 * @param x2
 * @param y2
 * @return Угол Z в радианах
 */
float getAngleBetweenPoints( float x1, float y1, float x2, float y2 );
/**
 * @brief Нахождение угла Z между точками (градусы)
 * @details Аналог опкода 05A4
 * @param x1
 * @param y1
 * @param x2
 * @param y2
 * @return Угол Z в градусах
 */
float getAngleBetweenPointsDeg( float x1, float y1, float x2, float y2 );
/**
 * @brief Конвертирование пиксельных координат экрана в игровые коордианы экрана
 * @param X
 * @param Y
 * @return игровые координаты точки (от 0*0 до 640*448)
 */
RwV2D WindowScreenToGameScreen( float X, float Y );
/**
 * @brief Конвертирование игровых координат экрана в пиксельные координаты экрана
 * @param X
 * @param Y
 * @return Координаты точки в пикселях
 */
RwV2D GameScreenToWindowScreen( float X, float Y );
/**
 * @brief Конвертация координат 3D-мира в пиксельные координаты экрана
 * @param world Координаты 3D-мира
 * @return пиксельные координаты экрана
 */
RwV2D ConvertGlobalXYZToWindowScreenXY( RwV3D world );
/**
 * @brief Конвертация координат 3D-мира в игровые координаты экрана
 * @param world Координаты 3D-мира
 * @return игровые координаты экрана
 */
RwV2D ConvertGlobalXYZToGameScreenXY( RwV3D world );

/**
 * @brief Проверка, что модель загружена
 * @param modelID Номер модели
 * @return Статус загруженности модели
 */
int isModelLoaded( eModelIndex modelID );
/**
 * @brief Добавление модели в очередь на загрузку
 * @param modelID Номер модели
 * @return Успешность добавления
 */
bool requestModelLoad( eModelIndex modelID );
/// Загрузка моделей из очереди на загрузку
void loadRequestedModels( void );
/**
 * @brief Загрузка одной модели без очереди
 * @param modelID Номер модели
 */
void loadModel( eModelIndex modelID );
/**
 * @brief Нахождение модели оружия, по его номеру
 * @param weaponId Номер оружия
 * @return Номер модели
 */
eModelIndex getWeaponModel( int weaponId );
/**
 * @brief Загрузка модели оружия по номеру оружия
 * @param weaponId Номер оружия
 */
void loadWeaponModel( int weaponId );
/// Загрузка всех моделий оружия
void loadAllWeaponModels();

const char *GetFrameNodeName( class RwFrame *frame );

#endif // METHODS_H
