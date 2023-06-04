#ifndef CPHYSICAL_H
#define CPHYSICAL_H

#include "CEntity.h"
#include "Types.h"
#include <deque>

class CPhysical : public CEntity {
public:
	// CEntity entity;
	union {
		struct {
			union {
				struct {
					uint8_t __unk1_nImmunities : 1;
					uint8_t bUsesVelocityGravity : 1;
					uint8_t bUsesGravity : 1; // used for lock in 0519:
					uint8_t bCollidable : 1;  // used for lock in 0519:
					uint8_t bDisableTurnForce : 1;
					uint8_t bDisableMoveForce : 1; // if true - skip some gravityes
					uint8_t bSkipGravity : 1;
					uint8_t bForceGravity : 1;
				};
				uint8_t nImmunities; // 64
			};
			union {
				struct {
					uint8_t bIsColised : 1;
					uint8_t bIsOnPlace : 1;
					uint8_t bBroken : 1;
					uint8_t __unk4__unknown_66 : 1;
					uint8_t __unk5__unknown_66 : 1;
					uint8_t bLock : 1;
					uint8_t __unk7__unknown_66 : 1;
					uint8_t __unk8__unknown_66 : 1;
				};
				uint8_t states; // 65
			};
			union {
				struct {
					uint8_t soft : 1;
					uint8_t pedFreeze : 1;
					uint8_t bullet_proof : 1;
					uint8_t fire_proof : 1;
					uint8_t collision_proof : 1;
					uint8_t melee_proof : 1;
					uint8_t bInvulnerable : 1;
					uint8_t explosion_proof : 1;
				};
				uint8_t flags; /* 66 immunities */
			};
			union {
				struct {
					uint8_t __unk1__unknown_68 : 1;
					uint8_t bAttachedToEntity : 1;
					uint8_t __unk3__unknown_68 : 1;
					uint8_t bTouchingWater : 1;
					uint8_t bCanBeCollidedWith : 1;
					uint8_t bDestroyed : 1;
					uint8_t __unk7__unknown_68 : 1;
					uint8_t __unk8__unknown_68 : 1;
				};
				uint8_t __unknown_68; /* 67 */
			};
		};
		uint32_t immunities; // 64
	};
	RwV3D speed; // 68
	RwV3D spin;
	RwV3D speed_acceleration;
	RwV3D spin_acceleration;
	RwV3D m_vForce;
	RwV3D m_vTorque;
	float mass;
	float massWhenTurning;
	float gripDivider;
	// 1.0 = 1 x gGrip
	// 10.1 = 10 x gGrip
	// 100.0 = g / 100Grip
	float	massToGrip;
	float	Elasticity;
	float	Buoyancy;
	RwV3D	massCenter;
	void *	m_pCollisionList; /* 176 - pointer to a "entry node info" pool item */
	void *	m_pMovingList;	  /* 180 - pointer to a "ptr node Double" pool item */
	uint8_t __unknown_184;
	WORD	m_nNumEntitiesCollided;
	//	unsigned char m_nContactSurface;
	uint8_t	   __unknown_187;
	CPhysical *last_collided_object[6];
	float	   speed_z;		/* 212 */
	float	   damageValue; /* 216 мб это таймер коллизии */
	CPhysical *damagedBy;	/* 220 он может быть CPed'ом */
	RwV3D	   collided_pos_local;
	RwV3D	   collided_pos;
	WORD	   collided_part; // TODO: захерачить метод в CPed и в наследниках CVehicle
	// ѕримечание: ƒл€ автомобилей используютс€ следующие номера частей :
	// 		1 - капот ? (лева€ передн€€ фара ? )
	// 		2 - багажник ?
	// 		3 - передний бампер ?
	// 		4 - задний бампер ?
	// 		5 - лева€ передн€€ дверь
	// 		6 - права€ передн€€ дверь
	// 		7 - лева€ задн€€ дверь
	// 		8 - права€ задн€€ дверь
	// 		9 - левое крыло ?
	// 		10 - правое крыло ?
	// 		17 - права€ передн€€ фара ?
	CPhysical *attachedEntity;
	RwV3D	   attachedPos;
	RwV3D	   attachedRot;
	RtQuat	   attachedQuat;
	CPhysical *collideIgnored;
	float	   lightLevel;
	float	   lighting;
	DWORD *	   CShadowData;

	virtual int processEntityCollision( CEntity *pEntity, char *pColPoint ) = 0;

	/**
	 * @brief Возвращает скорость объекта
	 * @return скорость
	 */
	float getSpeed();
	/**
	 * @brief Установливает скорость объекта
	 * @param spd скорость
	 */
	void setSpeed( RwV3D spd );
	/**
	 * @brief Добавляет скорость объекту
	 * @param spd скорость
	 */
	void addSpeed( RwV3D spd );

	/**
	 * @brief Установливает вращение объекта
	 * @param rot вращение
	 */
	void setSpinRot( RwV3D rot );
	/**
	 * @brief Добавляет вращение объекту
	 * @param rot вращение
	 */
	void addSpinRot( RwV3D rot );

	/**
	 * @brief Принудительное движение объекта
	 * @param mov назначение
	 */
	void applyMoveForce( RwV3D mov );
	/**
	 * @brief Принудительное указание гравитации объекту
	 * @param a Максимальное значение гравитации
	 * @param b Минимальное значение гравитации
	 * @param a4 хз
	 */
	void applyGravityForce( RwV3D a, CVector b, char a4 = 1 );

	/// Прикрепляет объект к поверхности под ногами/колесами
	void stickToPlace();

	/// Блокирует движение объекта
	void lock();
	/// Разблокирует движение объекта
	void unlock();
	/**
	 * @brief Изменяет состояние блокировки объекта
	 * @param state Новое состояние
	 */
	void toggleLock( bool state );
	/**
	 * @brief Проверяет, заблокирован ли объект
	 * @return состояние блокировки
	 */
	bool isLocked();

	/**
	 * @brief Проверяет, использует ли объект гравитацию
	 * @return состояние гравитации для объекта
	 */
	bool isUsesGravity();
	/**
	 * @brief Устанавливает использование гравитации объектом
	 * @param use_gravity состояние гравитации для объекта
	 */
	void setUsesGravity( bool use_gravity );

	/// Проверяет, что объект соприкосается с "землей"
	bool isOnPlace();

	/**
	 * @brief Возвращает скорость вращения объекта по оси Z
	 * @return скорость вращения по оси Z
	 */
	float getSpeedRotationZ();
	/**
	 * @brief Устанавливает скорость вращения объекта по оси Z
	 * @param speed скорость вращения по оси Z
	 */
	void setSpeedRotationZ( float speed );

	/**
	 * @brief Получает текущие иммунитеты объекта
	 * @param bullet иммунитет к пулям
	 * @param fire иммунитет к огню
	 * @param collision иммунитет к столкновениям
	 * @param melee иммунитет к ударам
	 * @param explosion иммунитет к взрывам
	 */
	void getProof( bool &bullet, bool &fire, bool &collision, bool &melee, bool &explosion );

	/**
	 * @brief Устанавливает иммунитеты объекту
	 * @param bullet иммунитет к пулям
	 * @param fire иммунитет к огню
	 * @param collision иммунитет к столкновениям
	 * @param melee иммунитет к ударам
	 * @param explosion иммунитет к взрывам
	 */
	void setProof( const bool &bullet, const bool &fire, const bool &collision, const bool &melee,
				   const bool &explosion );

	/**
	 * @brief Получает текущие иммунитеты объекта
	 * @return список иммунитетов
	 */
	std::deque<bool> getProof();

	/**
	 * @brief Устанавливает иммунитеты объекту
	 * @param immunities иммунитеты
	 */
	bool setProof( const std::deque<bool> &immunities );

	/**
	 * @brief Устанавливает бессмертие объекту
	 * @details Эквивалентно вызову setProof(gm, gm, gm, gm, gm)
	 * @param gm состояние бессмертия
	 */
	void setGodMode( const bool &gm );

	/**
	 * @brief Проверяет бессмертен ли объект
	 * @return состояние бессмертия
	 */
	bool isGodMode();

	/**
	 * @brief Проверяет есть ли под ногами земля
	 * @return наличие земли под ногами
	 */
	bool isGroundUnder();
};

#endif // CPHYSICAL_H
