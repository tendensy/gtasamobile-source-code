#ifndef CENTITY_H
#define CENTITY_H

#include "CPlaceable.h"
#include "Types.h"
#include <deque>

enum eEntityType {
	ENTITY_TYPE_NOTHING,
	ENTITY_TYPE_BUILDING,
	ENTITY_TYPE_VEHICLE,
	ENTITY_TYPE_PED,
	ENTITY_TYPE_OBJECT,
	ENTITY_TYPE_DUMMY,
	ENTITY_TYPE_NOTINPOOLS
};

enum eEntityStatus {
	STATUS_PLAYER,
	STATUS_PLAYER_PLAYBACKFROMBUFFER,
	STATUS_SIMPLE,
	STATUS_PHYSICS,
	STATUS_ABANDONED,
	STATUS_WRECKED,
	STATUS_TRAIN_MOVING,
	STATUS_TRAIN_NOT_MOVING,
	STATUS_HELI,
	STATUS_PLANE,
	STATUS_PLAYER_REMOTE,
	STATUS_PLAYER_DISABLED,
	STATUS_TRAILER,
	STATUS_SIMPLE_TRAILER
};

class CEntity : public CPlaceable {
public:
	union {
		struct RwObject *ptr_RwObject;
		struct RpClump * ptr_RpClump;
		struct RpAtomic *ptr_RwAtomic;
	};
	/********** BEGIN CFLAGS **************/ // + 28
	/// does entity use collision
	unsigned long bUsesCollision : 1;
	/// has object been processed by a ProcessEntityCollision function
	unsigned long bCollisionProcessed : 1;
	/// is entity static
	unsigned long bIsStatic : 1;
	/// has entity processed some contact forces
	unsigned long bHasContacted : 1;
	/// is entity stuck
	unsigned long bIsStuck : 1;
	/// is entity in a collision free safe position
	unsigned long bIsInSafePosition : 1;
	/// was entity control processing postponed
	unsigned long bWasPostponed : 1;
	/// is the entity visible
	unsigned long bIsVisible : 1;
	// + 29
	/// Set if this entity is a big building
	unsigned long bIsBIGBuilding : 1;
	/// use damaged LOD models for objects with applicable damage
	unsigned long bRenderDamaged : 1;
	/// Dont let the streaming remove this
	unsigned long bStreamingDontDelete : 1;
	/// remove this entity next time it should be processed
	unsigned long bRemoveFromWorld : 1;
	/// has collided with a building (changes subsequent collisions)
	unsigned long bHasHitWall : 1;
	/// don't delete me because I'm being rendered
	unsigned long bImBeingRendered : 1;
	/// draw object last
	unsigned long bDrawLast : 1;
	/// Fade entity because it is far away
	unsigned long bDistanceFade : 1;
	// +30
	/// Dont cast shadows on this object
	unsigned long bDontCastShadowsOn : 1;
	/// offscreen flag. This can only be trusted when it is set to true
	unsigned long bOffscreen : 1;
	/// this is used by script created entities - they are static until the collision is loaded below them
	unsigned long bIsStaticWaitingForCollision : 1;
	/// tell the streaming not to stream me
	unsigned long bDontStream : 1;
	/// this object is underwater change drawing order
	unsigned long bUnderwater : 1;
	/// Object has a prerender effects attached to it
	unsigned long bHasPreRenderEffects : 1;
	/// whether or not the building is temporary (i.e. can be created and deleted more than once)
	unsigned long bIsTempBuilding : 1;
	/// Don't update the animation hierarchy this frame
	unsigned long bDontUpdateHierarchy : 1;
	// + 31
	/// entity is roadsign and has some 2deffect text stuff to be rendered
	unsigned long bHasRoadsignText : 1;
	unsigned long bDisplayedSuperLowLOD : 1;
	/// set object has been generate by procedural object generator
	unsigned long bIsProcObject : 1;
	/// has backface culling on
	unsigned long bBackfaceCulled : 1;
	/// light object with directional lights
	unsigned long bLightObject : 1;
	/// set that this object is unimportant, if streaming is having problems
	unsigned long bUnimportantStream : 1;
	/// Is this model part of a tunnel
	unsigned long bTunnel : 1;
	/// This model should be rendered from within and outside of the tunnel
	unsigned long bTunnelTransition : 1;
	/********** END CFLAGS **************/

	uint8_t			   wSeedColFlags;	  // 0x20
	uint8_t			   wSeedVisibleFlags; // 0x21
	WORD			   modelID;
	struct CReference *pReferences; // 36 - collision related (objects only?)

	// CReferences *pReferences; //36
	/// CLink<CEntity*>* m_pLastRenderedLink;
	uint32_t *m_pLastRenderedLink; // 40
	uint16_t  timer;			   // 44
	/// used to define which IPL file object is in
	uint8_t		   m_iplIndex;	// 46
	uint8_t		   interior_id; // 47
	class CEntity *m_pLod;
	uint8_t		   numLodChildren;
	uint8_t		   numLodChildrenRendered;

	//********* BEGIN CEntityInfo **********//
	/// what type is the entity (1 == map, 2 == Vehicle, 3 == ped, 4 == object)
	uint8_t nType : 3; // 54
	/// control status
	uint8_t nStatus : 5; // 54

	// 55 alignment
	//********* END CEntityInfo **********//
	uint8_t __unknown_55[8]; // 55
	/// this really needs to be figured out cos it's probably a bit field
	union {
		struct {
			uint8_t __quantumPhysics_1 : 1;
			uint8_t __quantumPhysics_2 : 1;
			uint8_t __quantumPhysics_3 : 1;
			uint8_t skipCollision : 1; // skip collision
			uint8_t __quantumPhysics_5 : 1;
			uint8_t __quantumPhysics_6 : 1;
			uint8_t __quantumPhysics_7 : 1;
			uint8_t __quantumPhysics_8 : 1;
		};
		uint8_t quantumPhysics; // 64
	};

	virtual int						__add_CRect()			  = 0;
	virtual void					add()					  = 0;
	virtual int /*unk, mb it void*/ remove()				  = 0;
	virtual void					setIsStatic( bool state ) = 0;
	/**
	 * @brief Изменение модели сущности
	 * @param index Номер модели
	 */
	virtual void setModelIndex( eModelIndex index ) = 0;
	/**
	 * @brief Устанавливает модель сущности, но не меняет ее
	 * @param index Номер модели
	 * @return BaseModelInfo
	 */
	virtual void /*BaseModelInfo*/ *setModelIndexNoCreate( eModelIndex index ) = 0;
	virtual int						createRwObject()						   = 0;
	virtual void					deleteRwObject()						   = 0;
	virtual CRect *					getBoundRect( CRect *rect )				   = 0;
	virtual int						processControl()						   = 0;
	virtual int						__processCollision()					   = 0;
	virtual int						processShift()							   = 0;
	virtual bool					_testCollision( char a2 )				   = 0;
	/**
	 * @brief Телепортирует сущность
	 * @details Телепорт от перемещения отличается тем, что при телепорте сбрасываются скорость, анимация,
	 * вращение (опционально), повороты (кроме Z)
	 * @param X Координата X
	 * @param Y Координата Y
	 * @param Z Координата Z
	 * @param lockRotate Блокировка вращения при телепорте
	 * @return Успешность телепортации?
	 */
	virtual bool teleport( float X, float Y, float Z, bool lockRotate = true )					   = 0;
	virtual bool _specialEntityPreCollisionStuff( int a1, int a2, int a3, int a4, int a5, int a6 ) = 0;
	virtual bool _SpecialEntityCalcCollisionSteps( int a1, int a2 )								   = 0;
	/// Подготовка сущности к рендеру
	virtual void preRender() = 0;
	/// Рендер сущности
	virtual void render() = 0;
	/// Установка освещения сущности
	virtual bool setupLighting()				   = 0;
	virtual bool _removeLighting( bool a2 = true ) = 0;
	virtual void flagToDestroyWhenNextProcessed()  = 0;

	/**
	 * @brief Телепортирует сущность
	 * @details Телепорт от перемещения отличается тем, что при телепорте сбрасываются скорость, анимация,
	 * вращение (опционально), повороты (кроме Z)
	 * @param pos Координаты
	 * @param lockRotate Блокировка вращения при телепорте
	 * @return Успешность телепортации?
	 */
	bool teleport( RwV3D pos, bool lockRotate = true );

	/// Проверяет является ли сущность транспортом
	bool isVehicle();
	/// Проверяет является ли сущность человеком
	bool isPed();
	/// Проверяет находитсяли сущность под водой
	bool isUnderWater();
	/// Проверяет находится ли сущность на экране
	bool isOnScreen();

	/**
	 * @brief Проверяет, валидна ли данная сущность
	 * @details Это странно, используется родная функция игры, но она не работает с игроками и машинами
	 * @return true, если валидна
	 */
	bool isValidEntity();
	/**
	 * @brief Кастомная проверка валидации сущности
	 * @details Не использует проверку типа сущности и вызов ее метода, проверяет только по тем данным, что
	 * известны в рамках CEntity
	 * @return true, если валидна
	 */
	bool isValid();
	/**
	 * @brief Проверяет является ли сущность видимой
	 * @return Видимость
	 */
	bool isVisible();
	/**
	 * @brief Устанавливает видимость сущности
	 * @param visible Видимость
	 */
	void setVisible( bool visible );

	/**
	 * @brief Проверяет имеет ли сущность коллизию
	 * @return Наличие коллизии
	 */
	bool isUsesCollision();
	/**
	 * @brief Проверяет сталкивается ли сущность с другими сущностями
	 * @return Наличие столкновений
	 */
	bool isCollisionProcessed();
	/**
	 * @brief Устанавливает наличие коллизии сущности
	 * @param collision Наличие коллизии
	 */
	void setUsesCollision( bool collision );

	bool _removeRefsToEntity( int a2 );

	/**
	 * @brief Поворачивает объект по оси Z
	 * @param zangle угол в радианах
	 */
	void setHeading( float zangle );
	/**
	 * @brief Получает угол Z объекта
	 * @param zangle угол в радианах
	 */
	double getHeading();

	/**
	 * @brief Обновляет данные в RW-матрице
	 * @details Как правило требуется толко для педов. Остальные сущности, а так же педы находящиеся в
	 * воздухе, автоматически обновляют эту матрицу из матрицы сущности
	 */
	void updateRwMatrix();

	class CModel *		  getModelInfo();
	class CBaseModelInfo *getBaseModelInfo();

	/**
	 * @brief Устанавливает прозрачность сущности
	 * @details Вызывать надо перед вызовом CEntity::Render
	 * @param alpha уровень прозрачности [0-255]
	 */
	void setAlpha( DWORD alpha );
	char getAlpha();

	class RwFrame *GetFrameFromId( int id );
	class RwFrame *GetFrameFromName( char *name );

	std::deque<RpGeometry *> getAllGeometry();
	std::deque<RpAtomic *>	 getAllAtomics();
	std::deque<RpMaterial *> getAllMaterials();
	std::deque<RpMaterial *> getMaterials( const char *name );

	CMatrix *getModellingMatrix();

	RwV3D *GetBoundCentre( RwV3D *vec );
};

struct CReference {
	struct CReference *m_pNext;
	class CEntity **   m_ppEntity;
};


#endif // CENTITY_H
