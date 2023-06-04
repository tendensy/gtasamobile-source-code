#ifndef CVEHICLE_H
#define CVEHICLE_H

#include "CPhysical.h"
#include "Transport/CHandlingDataMgr.h"
#include "Types.h"

class CDamageManager {
public:
	float		  m_fWheelDamageEffect;
	unsigned char m_nEngineStatus;
	union {
		unsigned char m_anWheelsStatus[4];
		struct {
			unsigned char m_nRightRearWheelsStatus;
			unsigned char m_nRightFrontWheelsStatus;
			unsigned char m_nLeftRearWheelsStatus;
			unsigned char m_nLeftFrontWheelsStatus;
		};
	};
	union {
		unsigned char m_anDoorsStatus[6];
		struct {
			unsigned char m_nBonnetStatus;
			unsigned char m_nBootStatus;
			unsigned char m_nLeftFrontDoorStatus;
			unsigned char m_nRightFrontDoorStatus;
			unsigned char m_nLeftRearDoorStatus;
			unsigned char m_nRightRearDoorStatus;
		};
	};
	union {
		unsigned int m_nLightsStatus;
		struct {
			unsigned int m_nLeftFrontLightStatus : 2;
			unsigned int m_nRightFrontLightStatus : 2;
			unsigned int m_nRightRearLightStatus : 2;
			unsigned int m_nLeftRearLightStatus : 2;
		};
	};
	unsigned int m_nPanelsStatus;
};

VALIDATE_SIZE( CDamageManager, 0x18 );

enum eDoorState : unsigned char { DOOR_NOTHING, DOOR_HIT_MAX_END, DOOR_HIT_MIN_END, DOOR_POP_OPEN, DOOR_SLAM_SHUT };

class CDoor {
public:
	float		  m_fOpenAngle;
	float		  m_fClosedAngle;
	short		  m_nDirn;
	unsigned char m_nAxis;
	eDoorState	  m_nDoorState;
	float		  m_fAngle;
	float		  m_fPrevAngle;
	float		  m_fAngVel;
};

VALIDATE_SIZE( CDoor, 0x18 );

#pragma pack( push, 1 )
class CVehicle : public CPhysical {
public:
	// CPhysical				   physical;
	void *	__unknown_316;		/* 316 - pointer to this something in this classure */
	uint8_t __unknown_320[157]; /* 320 */
	uint8_t in_vehicle;			/* 477 */
	uint8_t __unknown_478[422]; /* 478 */

	class tHandlingData *  pHandlingData; /* 900 */
	class CHandlingFlying *pFlyData;	  /* 904 */
	union {
		int m_nHandlingFlagsIntValue;
		struct {
			unsigned int b1gBoost : 1;
			unsigned int b2gBoost : 1;
			unsigned int bNpcAntiRoll : 1;
			unsigned int bNpcNeutralHandl : 1;
			unsigned int bNoHandbrake : 1;
			unsigned int bSteerRearwheels : 1;
			unsigned int bHbRearwheelSteer : 1;
			unsigned int bAltSteerOpt : 1;
			unsigned int bWheelFNarrow2 : 1;
			unsigned int bWheelFNarrow : 1;
			unsigned int bWheelFWide : 1;
			unsigned int bWheelFWide2 : 1;
			unsigned int bWheelRNarrow2 : 1;
			unsigned int bWheelRNarrow : 1;
			unsigned int bWheelRWide : 1;
			unsigned int bWheelRWide2 : 1;
			unsigned int bHydraulicGeom : 1;
			unsigned int bHydraulicInst : 1;
			unsigned int bHydraulicNone : 1;
			unsigned int bNosInst : 1;
			unsigned int bOffroadAbility : 1;
			unsigned int bOffroadAbility2 : 1;
			unsigned int bHalogenLights : 1;
			unsigned int bProcRearwheelFirst : 1;
			unsigned int bUseMaxspLimit : 1;
			unsigned int bLowRider : 1;
			unsigned int bStreetRacer : 1;
			unsigned int bUnused1 : 1;
			unsigned int bSwingingChassis : 1;
		} m_nHandlingFlags;
	};
	uint8_t		  __unknown_912[36];	  /* 912 */
	uint8_t		  trafficBehavior;		  /* 948 */
	uint8_t		  driverBehavior;		  /* 949 */
	uint8_t		  __unknown_950[18];	  /* 950 */
	float		  __trafficSpeed;		  /* 968 */
	uint8_t		  __unknown_972[4];		  /* 972 */
	float		  trafficSpeed;			  /* 976 */
	uint8_t		  __unknown_980[24];	  /* 980 */
	uint32_t	  hFlagsLocal;			  /* 1004 */
	uint8_t		  AutoPilot[56];		  /* 1008 - AutoPilot */
	unsigned char bIsLawEnforcer : 1;	  // Is this guy chasing the player at the moment
	unsigned char bIsAmbulanceOnDuty : 1; // Ambulance trying to get to an accident
	unsigned char bIsFireTruckOnDuty : 1; // Firetruck trying to get to a fire
	unsigned char bIsLocked : 1;		  // Is this guy locked by the script (cannot be removed)
	uint8_t		  engineState : 1;
	unsigned char bIsHandbrakeOn : 1;	 // How's the handbrake doing ?
	uint8_t		  lights : 1;			 /* 1064 - 60 bits/flags */
	unsigned char bFreebies : 1;		 // Any freebies left in this vehicle ?
	unsigned char bIsVan : 1;			 // Is this vehicle a van (doors at back of vehicle)
	unsigned char bIsBus : 1;			 // Is this vehicle a bus
	unsigned char bIsBig : 1;			 // Is this vehicle a bus
	unsigned char bLowVehicle : 1;		 // Need this for sporty type cars to use low getting-in/out anims
	unsigned char bComedyControls : 1;	 // Will make the car hard to control (hopefully in a funny way)
	unsigned char bWarnedPeds : 1;		 // Has scan and warn peds of danger been processed?
	unsigned char bCraneMessageDone : 1; // A crane message has been printed for this car allready
	// unsigned char bExtendedRange: 1; // This vehicle needs to be a bit further away to get deleted
	unsigned char bTakeLessDamage : 1;		 // This vehicle is stronger (takes about 1/4 of damage)
	unsigned char bIsDamaged : 1;			 // This vehicle has been damaged and is displaying all its components
	unsigned char bHasBeenOwnedByPlayer : 1; // To work out whether stealing it is a crime
	unsigned char bFadeOut : 1;				 // Fade vehicle out
	unsigned char bIsBeingCarJacked : 1;	 // Fade vehicle out
	unsigned char
		bCreateRoadBlockPeds : 1; // If this vehicle gets close enough we will create peds (coppers or gang members) round it
	unsigned char bCanBeDamaged : 1; // Set to FALSE during cut scenes to avoid explosions
	// unsigned char bUsingSpecialColModel : 1;
	// Is player vehicle using special collision model, stored in player strucure
	unsigned char
		bOccupantsHaveBeenGenerated : 1; // Is true if the occupants have already been generated. (Shouldn't happen again)
	unsigned char bGunSwitchedOff : 1;	 // Level designers can use this to switch off guns on boats
	unsigned char bVehicleColProcessed : 1;	   // Has ProcessEntityCollision been processed for this car?
	unsigned char bIsCarParkVehicle : 1;	   // Car has been created using the special CAR_PARK script command
	unsigned char bHasAlreadyBeenRecorded : 1; // Used for replays
	unsigned char bPartOfConvoy : 1;
	unsigned char bHeliMinimumTilt : 1;	  // This heli should have almost no tilt really
	unsigned char bAudioChangingGear : 1; // sounds like vehicle is changing gear
	unsigned char bIsDrowning : 1;		  // is vehicle occupants taking damage in water (i.e. vehicle is dead in water)
	unsigned char bTyresDontBurst : 1;	  // If this is set the tyres are invincible
	unsigned char
		bCreatedAsPoliceVehicle : 1; // True if this guy was created as a police vehicle (enforcer, policecar, miamivice car etc)
	unsigned char
		bRestingOnPhysical : 1; // Dont go static cause car is sitting on a physical object that might get removed
	unsigned char bParking : 1;
	unsigned char bCanPark : 1;
	unsigned char bFireGun : 1;			// Does the ai of this vehicle want to fire it's gun?
	unsigned char bDriverLastFrame : 1; // Was there a driver present last frame ?
	unsigned char
		bNeverUseSmallerRemovalRange : 1; // Some vehicles (like planes) we don't want to remove just behind the camera.
	unsigned char
		bIsRCVehicle : 1; // Is this a remote controlled (small) vehicle. True whether the player or AI controls it.
	unsigned char bAlwaysSkidMarks : 1; // This vehicle leaves skidmarks regardless of the wheels' states.
	unsigned char bEngineBroken : 1;	// Engine doesn't work. Player can get in but the vehicle won't drive
	unsigned char
		bVehicleCanBeTargetted : 1;		 // The ped driving this vehicle can be targetted, (for Torenos plane mission)
	unsigned char bPartOfAttackWave : 1; // This car is used in an attack during a gang war
	unsigned char bWinchCanPickMeUp : 1; // This car cannot be picked up by any ropes.
	unsigned char bImpounded : 1;		 // Has this vehicle been in a police impounding garage
	unsigned char bVehicleCanBeTargettedByHS : 1; // Heat seeking missiles will not target this vehicle.
	unsigned char bSirenOrAlarm : 1;			  // Set to TRUE if siren or alarm active, else FALSE
	unsigned char bHasGangLeaningOn : 1;
	unsigned char bGangMembersForRoadBlock : 1; // Will generate gang members if NumPedsForRoadBlock > 0
	unsigned char
		bDoesProvideCover : 1;		   // If this is false this particular vehicle can not be used to take cover behind.
	unsigned char bMadDriver : 1;	   // This vehicle is driving like a lunatic
	unsigned char bUpgradedStereo : 1; // This vehicle has an upgraded stereo
	unsigned char bConsideredByPlayer : 1;	  // This vehicle is considered by the player to enter
	unsigned char bPetrolTankIsWeakPoint : 1; // If false shootong the petrol tank will NOT Blow up the car
	unsigned char bDisableParticles : 1;	  // Disable particles from this car. Used in
	unsigned char bHasBeenResprayed : 1; // Has been resprayed in a respray garage. Reset after it has been checked.
	unsigned char bUseCarCheats : 1;	 // If this is true will set the car cheat stuff up in ProcessControl()
	unsigned char
		bDontSetColourWhenRemapping : 1; // If the texture gets remapped we don't want to change the colour with it.
	unsigned char bUsedForReplay : 1;	 // This car is controlled by replay and should be removed when replay is done.
	uint32_t	  m_TimeOfCreation;		 /* 1072 - GetTimeInMilliseconds when this vehicle was created. */

	// TODO: В CAutomobile запихать методы для апгрейда
	uint8_t		   color[4];		   /* 1076 - as in carcolors.dat - body, stripe, body2, stripe2 */
	uint8_t		   modding[2];		   /* 1080 - modding data */
	unsigned short UpgradeModelID[15]; /* 1082 - attached upgrades */
	float		   wheel_size;		   /* 1112 */
	unsigned short CarAlarmState;	   /* 1116 - time left for car alarm to sound in ms */
	unsigned short ForcedRandomSeed;   /* 1118 - if this is non-zero the random wander gets deterministic */

	union {
		class CPed *players[9];
		struct {
			class CPed *driver;
			class CPed *passenger_FrontRight;	  //Переднее правое сиденье
			class CPed *passenger_RearLeft;		  //Заднее левое сиденье
			class CPed *passenger_RearRight;	  //Заднее правое сиденье
			class CPed *passengers_additional[5]; //Для автобусов
		};
	};

	unsigned char m_nNumPassengers;					/* 1156 */
	unsigned char m_nNumGettingIn;					/* 1157 */
	unsigned char m_nGettingInFlags;				/* 1158 */
	unsigned char m_nGettingOutFlags;				/* 1159 */
	unsigned char m_nMaxPassengers;					/* 1160 */
	unsigned char m_windowsOpenFlags;				/* 1161 */
	char		  m_nNitroBoosts;					/* 1162 - count of nitro boosts */
	char		  m_nSpecialColModel;				/* 1163 */
	DWORD *		  pEntityWeAreOnForVisibilityCheck; /* 1164 - we need a CEntity */
	DWORD *		  m_pFire;							/* 1168 - CFire*/

	float steer_angles[2]; /* 1172 - steer angles */
	float gas_pedal;	   /* 1180 - gas pedal */
	float break_pedal;	   /* 1184 - break pedal */

	// 1188
	unsigned char VehicleCreatedBy; // Contains information on whether this vehicle can be deleted or not.
									// Probably only need this or IsLocked.
	short ExtendedRemovalRange;

	// this padding probably isn't in the right place.
	uint8_t __unknown_1191;

	// 1192
	/// 0 = None. 1 = Timed. 2 = On ignition, 3 = remotely set ? 4 = Timed Bomb has been activated. 5 = On
	/// ignition has been activated.
	unsigned char car_bomb : 3;
	unsigned char OverrideLights : 2; // uses enum NO_CAR_LIGHT_OVERRIDE, FORCE_CAR_LIGHTS_OFF, FORCE_CAR_LIGHTS_ON
	unsigned char WinchType : 2;	  // Does this vehicle use a winch?

	// this padding probably isn't in the right place.
	uint8_t __unknown_1193;

	// 1194
	unsigned char m_GunsCycleIndex : 2;		// Cycle through alternate gun hardpoints on planes/helis
	unsigned char m_OrdnanceCycleIndex : 2; // Cycle through alternate ordnance hardpoints on planes/helis

	// 1195
	unsigned char nUsedForCover; // Has n number of cops hiding/attempting to hid behind it
	unsigned char AmmoInClip;	 // Used to make the guns on boat do a reload.
	unsigned char PacMansCollected;
	unsigned char PedsPositionForRoadBlock;
	unsigned char NumPedsForRoadBlock;

	// 1200
	/// Dirt level of vehicle body texture: 0.0f=fully clean, 15.0f=maximum dirt visible, it may be altered at
	/// any time while vehicle's cycle of lige
	float nBodyDirtLevel;

	// values used by transmission
	unsigned char m_nCurrentGear;		/* 1204 */
	float		  m_fGearChangeCount;	/* 1205 */
	float		  m_fWheelSpinForAudio; /* 1209 */
	uint8_t		  __unknown_1213[3];	/* 1213 */

	/// здоровье транспорта
	float			hitpoints;	   /* 1216 */
	class CVehicle *pulling_truck; /* 1220 - vehicle_info - pulling truck */
	class CVehicle *trailer;	   /* 1224 - pointer to the currently attached trailer; 0 if theres no trailer */
	class CPed *	m_pWhoInstalledBombOnMe;	   /* 1228 */
	int				m_nTimeTillWeNeedThisCar;	   /* 1232 */
	int				m_nGunFiringTime;			   /* 1236 */
	int				m_nTimeWhenBlowedUp;		   /* 1240 */
	short			m_nCopsInCarTimer;			   /* 1244 */
	uint16_t		m_wBombTimer;				   /* 1246 */
	void *			m_pWhoDetonatedMe;			   /* 1248 */
	float			m_fVehicleFrontGroundZ;		   /* 1252 */
	float			m_fVehicleRearGroundZ;		   /* 1256 */
	uint8_t			__unknown_1260[2];			   /* 1260 */
	int				m_nDoorLock;				   /* 1262 */
	int				m_nProjectileWeaponFiringTime; /* 1266 */
	uint8_t			__unknown_1270[2];
	/// 1272 - car door status (1:Opened 2:Locked)
	uint32_t   door_status;			/* 1272 */
	uint8_t	   __unknown_1276[136]; /* 1276 */
	uint8_t	   lightsFlags;			// 1412;
	uint8_t	   __unknown_1413[11];
	uint8_t	   vehicle_type;	  /* 1424 - VEHICLE_TYPE_* */
	uint8_t	   __unknown_1425[3]; /* 1425 */
	int		   m_nVehicleSubClass;
	short	   m_nPreviousRemapTxd;
	short	   m_nRemapTxd;
	RwTexture *m_pRemapTexture;

	virtual void		_processControlCollisionCheck( char a1 )						   = 0;
	virtual void		_processControlInputs( bool a2 )								   = 0;
	virtual void		getComponentWorldPosition( int id, RwV3D *pos )					   = 0;
	virtual bool		isComponentPresent( int id )									   = 0;
	virtual bool		_openDoor( int a2, int a3, int a4, float a5, char a6 )			   = 0;
	virtual void		_processOpenDoor( int a2, float a3, float a4, float a5, float a6 ) = 0;
	virtual long double getDoorAngleOpenRatio( int id )									   = 0;
	virtual void		_getDoorAngleOpenRatio( int id )								   = 0;
	virtual bool		isDoorReady( int id )											   = 0;
	virtual bool		_isDoorReady( int id )											   = 0;
	virtual bool		isDoorFullyOpen( int id )										   = 0;
	virtual bool		_isDoorFullyOpen( int id )										   = 0;
	virtual bool		isDoorClosed( int id )											   = 0;
	virtual bool		_isDoorClosed( int id )											   = 0;
	virtual bool		isDoorMissing( int id )											   = 0;
	virtual bool		_isDoorMissing( int id )										   = 0;
	virtual bool		isOpenTopCar()													   = 0;
	virtual void		_removeRefsToVehicle( int a1 )									   = 0;
	virtual void		_blowUpCar( int frame, bool a2 )								   = 0;
	virtual void		_blowUpCarCutSceneNoExtras( int a1, int a2, int a3, int a4 )	   = 0;
	virtual bool		_setUpWheelColModel( int a1 )									   = 0;
	/**
	 * @brief Пробивает/чинит покрышки
	 * @param nWheel номер колеса
	 * @param state состояние покрышки (пробитая/целая)
	 * @return хз. Успех, если колесо с таким id есть?
	 */
	virtual bool   _burstTyre( uint8_t nWheel, bool state )			= 0;
	virtual bool   __isRoomForPedToLeaveCar()						= 0;
	virtual void   _processDrivingAnims( class CPed *ped, bool a3 ) = 0;
	virtual char * getRideAnimData()								= 0;
	virtual void   setupSuspensionLines()							= 0;
	virtual RwV3D *_addMovingCollisionSpeed( RwV3D *a2, RwV3D *a3 ) = 0;
	/// Чинит транспорт. Не восстанавливает HP
	virtual void fix()						  = 0;
	virtual int	 setupDamageAfterLoad()		  = 0;
	virtual void doBurstAndSoftGroundRatios() = 0;
	/**
	 * @brief Возвращает высоту транспорта над землей
	 * @return высота над землей
	 */
	virtual long double getHeightAboveRoad() = 0;
	/// Воспроизведение гудка
	virtual bool playCarHorn() = 0;
	/**
	 * @brief Возвращает число колес, соприкасающихся с землей
	 * @return число колес
	 */
	virtual int getNumContactWheels() = 0;
	/**
	 * @brief Повреждение компаонентов транспорта
	 * @param a1 хз какой компанен
	 * @param a2 хз какой компанен
	 * @param a3 хз какой компанен
	 * @param a4 хз какой компанен
	 * @param a5 хз какой компанен
	 * @param a6 хз какой компанен
	 */
	virtual void _vehicleDamage( int a1, int a2, int a3, int a4, int a5, int a6 ) = 0;
	/**
	 * @brief Проверяет, может ли указанный пассажир выйти из машины через дверь
	 * @param passengerId Номер пассажира (0 - водитель)
	 * @return может/не может
	 */
	virtual bool canPedStepOutCar( uint8_t passengerId ) = 0;
	/**
	 * @brief Проверяет, может ли указанный пассажир быть выброшен из машины (типа телепорт)
	 * @param passengerId Номер пассажира (0 - водитель)
	 * @return может/не может
	 */
	virtual bool		canPedJumpOutCar( uint8_t passengerId )					  = 0;
	virtual bool		getTowHitchPos( RwV3D *pos, bool get, CEntity *pEntity )  = 0;
	virtual bool		getTowBarPos( RwV3D *pos, bool get, CEntity *pEntity )	  = 0;
	virtual bool		SetTowLink( CEntity *pEntity, bool set )				  = 0;
	virtual bool		breakTowLink()											  = 0;
	virtual long double _findWheelWidth( bool a1 /* возможно это byte nWheel */ ) = 0;
	virtual bool		save()													  = 0;
	virtual bool		load()													  = 0;

	/**
	 * @brief Возвращает количество ХП транспорта
	 * @details Дымит при ХП меньше 700, горит при ЗП меньше 250 (запускается таймер до взрыва. Момент взрыва
	 * не зависит от оставшегося ХП)
	 * @return по дефолту 0 - 1000
	 */
	float getHitpoints();
	/**
	 * @brief Устанавливает количество ХП транспорту
	 * @param hp количество ХП
	 */
	void setHitpoints( float hp );

	/// Чинит транспорт с восстановлением ХП до 1000
	void repair();

	bool switchModel( int id );

	/**
	 * @brief Проверяет, является ли транспорт валидным
	 * @details Почему-то хуярит false, хз как собейт собейт с этим живет
	 * @return true если указатель валиден
	 */
	bool isValid();
	/// Проверяет, что транспорт является лодкой
	bool isBoat();
	/// Проверяет, что транспорт является машиной
	bool isCar();
	/// Проверяет, что транспорт является поездом
	bool isTrain();
	/// Проверяет, что транспорт является вертолетом
	bool isHeli();
	/// Проверяет, что транспорт является самолетом
	bool isPlane();
	/// Проверяет, что транспорт является мотоциклом
	bool isBike();
	/// Проверяет, что транспорт является не настоящим самолетом
	bool isFakePlane();
	/// Проверяет, что транспорт является грузовиком
	bool isMonsterTruck();
	/// Проверяет, что транспорт является квадрациклом
	bool isQuadBike();
	/// Проверяет, что транспорт является велосипедом
	bool isBmx();
	/// Проверяет, что транспорт является трейлером
	bool isTrailer();

	/// Проверяет, что в машине никого
	bool isEmpty();

	bool withPlayer( CPed *ped );

	void kickOff( CPed *ped );
	void kickOffDriver();
	void kickOffPassenger( uint8_t seat );
	void kickOffPassengers();
	void kickOffAll();

	/**
	 * @brief Закрывает машину?
	 * @return Успешность?
	 */
	bool  lockCar();
	float setAngularVelocity( RwV3D angularVelocity );

	bool isEngineOn();
	void setEngineState( bool state );
};
#pragma pack( pop )

VALIDATE_SIZE( CVehicle, 0x5A0 );

#endif // CVEHICLE_H
