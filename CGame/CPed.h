#ifndef CPED_H
#define CPED_H

#include "CObject.h"
#include "CPedIK.h"
#include "CPhysical.h"
#include "CWeaponSlot.h"
#include "Types.h"


class CPedFlags {
public:
	unsigned int bIsStanding : 1;		   // is ped standing on something
	unsigned int bWasStanding : 1;		   // was ped standing on something
	unsigned int bIsLooking : 1;		   // is ped looking at something or in a direction
	unsigned int bIsRestoringLook : 1;	   // is ped restoring head postion from a look
	unsigned int bIsAimingGun : 1;		   // is ped aiming gun
	unsigned int bIsRestoringGun : 1;	   // is ped moving gun back to default posn
	unsigned int bCanPointGunAtTarget : 1; // can ped point gun at target
	unsigned int bIsTalking : 1;		   // is ped talking(see Chat())

	unsigned int bInVehicle : 1;			 // is in a vehicle
	unsigned int bIsInTheAir : 1;			 // is in the air
	unsigned int bIsLanding : 1;			 // is landing after being in the air
	unsigned int bHitSomethingLastFrame : 1; // has been in a collision last fram
	unsigned int bIsNearCar : 1;			 // has been in a collision last fram
	unsigned int bRenderPedInCar : 1;		 // has been in a collision last fram
	unsigned int bUpdateAnimHeading : 1;	 // update ped heading due to heading change during anim sequence
	unsigned int bRemoveHead : 1;			 // waiting on AntiSpazTimer to remove head

	unsigned int bFiringWeapon : 1;		   // is pulling trigger
	unsigned int bHasACamera : 1;		   // does ped possess a camera to document accidents
	unsigned int bPedIsBleeding : 1;	   // Ped loses a lot of blood if true
	unsigned int bStopAndShoot : 1;		   // Ped cannot reach target to attack with fist, need to use gun
	unsigned int bIsPedDieAnimPlaying : 1; // is ped die animation finished so can dead now
	unsigned int bStayInSamePlace : 1;	   // when set, ped stays put
	unsigned int
				 bKindaStayInSamePlace : 1; // when set, ped doesn't seek out opponent or cover large distances. Will still shuffle and look for cover
	unsigned int bBeingChasedByPolice : 1; // use nodes for routefind

	unsigned int bNotAllowedToDuck : 1;	  // Is this ped allowed to duck at all?
	unsigned int bCrouchWhenShooting : 1; // duck behind cars etc
	unsigned int bIsDucking : 1;		  // duck behind cars etc
	unsigned int bGetUpAnimStarted : 1;	  // don't want to play getup anim if under something
	unsigned int bDoBloodyFootprints : 1; // unsigned int bIsLeader :1;
	unsigned int bDontDragMeOutCar : 1;
	unsigned int bStillOnValidPoly : 1; // set if the polygon the ped is on is still valid for collision
	unsigned int bAllowMedicsToReviveMe : 1;

	unsigned int bResetWalkAnims : 1;
	unsigned int bOnBoat : 1;				// flee but only using nodes
	unsigned int bBusJacked : 1;			// flee but only using nodes
	unsigned int bFadeOut : 1;				// set if you want ped to fade out
	unsigned int bKnockedUpIntoAir : 1;		// has ped been knocked up into the air by a car collision
	unsigned int bHitSteepSlope : 1;		// has ped collided/is standing on a steep slope (surface type)
	unsigned int bCullExtraFarAway : 1;		// special ped only gets culled if it's extra far away (for roadblocks)
	unsigned int bTryingToReachDryLand : 1; // has ped just exited boat and trying to get to dry land

	unsigned int bCollidedWithMyVehicle : 1;
	unsigned int bRichFromMugging : 1; // ped has lots of cash cause they've been mugging people
	unsigned int bChrisCriminal : 1; // Is a criminal as killed during Chris' police mission (should be counted as such)
	unsigned int bShakeFist : 1;	 // test shake hand at look entity
	unsigned int bNoCriticalHits : 1;		  // ped cannot be killed by a single bullet
	unsigned int bHasAlreadyBeenRecorded : 1; // Used for replays
	unsigned int bUpdateMatricesRequired : 1; // if PedIK has altered bones so matrices need updated this frame
	unsigned int bFleeWhenStanding : 1;		  //

	unsigned int bMiamiViceCop : 1;				 //
	unsigned int bMoneyHasBeenGivenByScript : 1; //
	unsigned int bHasBeenPhotographed : 1;		 //
	unsigned int bIsDrowning : 1;
	unsigned int bDrownsInWater : 1;
	unsigned int bHeadStuckInCollision : 1;
	unsigned int bDeadPedInFrontOfCar : 1;
	unsigned int bStayInCarOnJack : 1;

	unsigned int bDontFight : 1;
	unsigned int bDoomAim : 1;
	unsigned int bCanBeShotInVehicle : 1;
	unsigned int
				 bPushedAlongByCar : 1; // ped is getting pushed along by car collision (so don't take damage from horz velocity)
	unsigned int bNeverEverTargetThisPed : 1;
	unsigned int bThisPedIsATargetPriority : 1;
	unsigned int bCrouchWhenScared : 1;
	unsigned int bKnockedOffBike : 1;

	unsigned int bDonePositionOutOfCollision : 1;
	unsigned int bDontRender : 1;
	unsigned int bHasBeenAddedToPopulation : 1;
	unsigned int bHasJustLeftCar : 1;
	unsigned int bIsInDisguise : 1;
	unsigned int bDoesntListenToPlayerGroupCommands : 1;
	unsigned int bIsBeingArrested : 1;
	unsigned int bHasJustSoughtCover : 1;

	unsigned int bKilledByStealth : 1;
	unsigned int bDoesntDropWeaponsWhenDead : 1;
	unsigned int bCalledPreRender : 1;
	unsigned int bBloodPuddleCreated : 1; // Has a static puddle of blood been created yet
	unsigned int bPartOfAttackWave : 1;
	unsigned int bClearRadarBlipOnDeath : 1;
	unsigned int bNeverLeavesGroup : 1; // flag that we want to test 3 extra spheres on col model
	unsigned int
		bTestForBlockedPositions : 1; // this sets these indicator flags for various posisions on the front of the ped

	unsigned int bRightArmBlocked : 1;
	unsigned int bLeftArmBlocked : 1;
	unsigned int bDuckRightArmBlocked : 1;
	unsigned int bMidriffBlockedForJump : 1;
	unsigned int bFallenDown : 1;
	unsigned int bUseAttractorInstantly : 1;
	unsigned int bDontAcceptIKLookAts : 1;
	unsigned int bHasAScriptBrain : 1;

	unsigned int bWaitingForScriptBrainToLoad : 1;
	unsigned int bHasGroupDriveTask : 1;
	unsigned int bCanExitCar : 1;
	unsigned int
				 CantBeKnockedOffBike : 2; // 0=Default(harder for mission peds) 1=Never 2=Always normal(also for mission peds)
	unsigned int bHasBeenRendered : 1;
	unsigned int bIsCached : 1;
	unsigned int
		bPushOtherPeds : 1; // GETS RESET EVERY FRAME - SET IN TASK: want to push other peds around (eg. leader of a group or ped trying to
							// get in a car)
	unsigned int bHasBulletProofVest : 1;

	unsigned int bUsingMobilePhone : 1;
	unsigned int bUpperBodyDamageAnimsOnly : 1;
	unsigned int bStuckUnderCar : 1;
	unsigned int bKeepTasksAfterCleanUp : 1; // If true ped will carry on with task even after cleanup
	unsigned int bIsDyingStuck : 1;
	unsigned int bIgnoreHeightCheckOnGotoPointTask : 1; // set when walking round buildings, reset when task quits
	unsigned int bForceDieInCar : 1;
	unsigned int bCheckColAboveHead : 1;

	unsigned int bIgnoreWeaponRange : 1;
	unsigned int bDruggedUp : 1;
	unsigned int
				 bWantedByPolice : 1; // if this is set, the cops will always go after this ped when they are doing a KillCriminal task
	unsigned int bSignalAfterKill : 1;
	unsigned int bCanClimbOntoBoat : 1;
	unsigned int bPedHitWallLastFrame : 1; // useful to store this so that AI knows (normal will still be available)
	unsigned int bIgnoreHeightDifferenceFollowingNodes : 1;
	unsigned int bMoveAnimSpeedHasBeenSetByTask : 1;

	unsigned int bGetOutUpsideDownCar : 1;
	unsigned int bJustGotOffTrain : 1;
	unsigned int bDeathPickupsPersist : 1;
	unsigned int bTestForShotInVehicle : 1;
	//#ifdef GTA_REPLAY
	unsigned int bUsedForReplay : 1; // This ped is controlled by replay and should be removed when replay is done.
									 //#endif

	unsigned int bFreeFlag1 : 1; // Не использованый флаг
	unsigned int bFreeFlag2 : 1; // Не использованый флаг
	unsigned int bFreeFlag3 : 1; // Не использованый флаг
};

class CPed : public CPhysical {
public:
	// CPhysical					physical;
	uint8_t __unknown_316[32]; /* 316 */
	uint8_t animation_state;
	// 	0 = прыгает от земли
	// 	61 = ударяет
	// 	102 = остановился
	// 	154 = спринт(бежит с ускорением)
	// 	205 = бежит
	uint8_t	  __unknown_349[7];	   /* 349 */
	RwV3D	  step_pos;			   /* 356 - coordinates, last foot step */
	RwV3D	  step_pos_before;	   /* 368 - coordinates, foot step before last one */
	uint8_t	  __unknown_380[280];  /* 380 */
	uint8_t	  CPedSound[0x100];	   /* 660 */
	uint8_t	  __unknown_916[216];  /* 916 */
	CPedFlags pedFlags;			   /* 1132 */
	DWORD	  ptr_pedIntelligence; /* 1148 */
	void *	  pPlayerData;		   /* 1152 */
	char	  PedCreatedBy;

	uint8_t __unknown_1156[7]; /* 1157 */

	// relative body-part-positions
	void *		 pNeck;				/* 1164 - void* pNeck
(pChest?)
- 4 unknown
- float height
- float front/back
- float left/right
- void* pObject
(same class for the following body-part-pointers [except pLeft/RightArm])
*/
	class CBone *boneHead;			/* 1168 */
	class CBone *boneLeftArm;		/* 1172 */
	class CBone *boneRightArm;		/* 1176 */
	class CBone *pboneLeftLowArm;	/* 1180 */
	class CBone *boneRightLowArm;	/* 1184 */
	class CBone *boneLeftLeg;		/* 1188 */
	class CBone *boneRightLeg;		/* 1192 */
	class CBone *boneLeftLowLeg;	/* 1196 */
	class CBone *boneRightLowLeg;	/* 1200 */
	class CBone *boneRightMidLeg;	/* 1204 */
	class CBone *boneLeftMidLeg;	/* 1208 */
	class CBone *boneLeftMidArm;	/* 1212 */
	class CBone *boneRightMidArm;	/* 1216 */
	class CBone *boneLeftShoulder;	/* 1220 */
	class CBone *boneRightShoulder; /* 1224 */
	class CBone *boneChest;			/* 1228 */
	class CBone *boneMouth;			/* 1232 */
	DWORD		 animGroup;
	uint8_t		 __unknown_1240[4]; /* 1240 */
	float		 runspeed;			/* 1244 */
	uint8_t		 animLoopStatus;
	// 	0 = ничего
	// 	61 = начало / остановка
	// 	62 = идёт цикл
	uint8_t		 __unknown_1249[19]; /* 1249 */
	DWORD		 CurrentWeapon;		 /* RpClump */
	DWORD		 muzzle_flash;		 /* RpClump */
	DWORD		 Scores;			 /* RpClump */
	DWORD		 ScoresType;
	DWORD		 AlphaBlendMuzzle_flash;
	DWORD		 AlphaBlendMuzzle_flash2;
	class CPedIK PedIK;
	uint32_t	 m_nAntiSpazTimer; /* 1324 */

	uint32_t		state;				  /* 1328 - ACTOR_STATE_* */
	uint32_t		run_state;			  /* 1332 - ACTOR_MSTATE_* */
	uint8_t			__unknown_1336[8];	  /* 1336 */
	float			hitpoints;			  /* 1344 */
	float			hitpoints_max;		  /* 1348 - нужный_уровень_ХП * 5.69 */
	float			armor;				  /* 1352 */
	RwV3D			reset_position;		  /* 1356 */
	float			fCurrentRotation;	  /* 1368 */
	float			fTargetRotation;	  /* 1372 */
	float			fRotationSpeed;		  /* 1376 */
	float			fRotationCalculation; /* 1380 - is 0.1 when target rotation reached */
	class CVehicle *pContactVehicle;	  /* CVehicle */
	RwV3D			vehicle_contact_dist;
	RwV3D			fPlaneAnglesContactEntity;
	class CEntity * item_contact;
	float			fUnknown_1416; /* 1416 - only changing when slightly under map */
	union {
		class CVehicle *	 vehicle;	 /* CVehicle */
		class CAutomobile *	 automobile; /* CAutomobile */
		class CMonsterTruck *mtruck;	 /* CMonsterTruck */
		class CTrailer *	 trailer;	 /* CTrailer */
		class CBike *		 bike;		 /* CBike */
		class CQuad *		 quad;		 /* CQuad */
		class CBmx *		 bmx;		 /* CBmx */
		class CHeli *		 heli;		 /* CHeli */
		class CPlane *		 plane;		 /* CPlane */
		class CBoat *		 boat;		 /* CBoat */
	};
	uint8_t		   __unknown_1424[8]; /* 1424 */
	uint8_t		   actor_lock;		  /* 1432 */
	uint8_t		   __unknown_1433[7]; /* 1433 */
	CWeaponSlot	   WeaponSlot[13];	  /* 1440 */
	DWORD		   turrelWeaponID;
	uint8_t		   __unknown_1808[8]; /* 1808 */
	uint8_t		   weapon_slot;		  /* 1816 */
	uint8_t		   __unknown_1817;	  /* 1817 */
	uint8_t		   AccuracyShot;
	uint8_t		   __unknown_1819; /* 1819 */
	class CObject *targetObject;
	RwV3D		   fImpactPos_close;
	uint8_t		   weaponSkills;
	uint8_t		   fightStyle;
	uint8_t		   fightStyle2;
	uint8_t		   __unknown_1839; /* 1839 */
	DWORD		   ptr_CFire;
	uint8_t		   __unknown_1836[12]; /* 1844 */
	uint32_t	   weapon_model;	   /* 1856 */
	uint8_t		   __unknown_1860[18]; /* 1860 */
	WORD		   money;
	uint8_t		   __unknown_1880[8]; /* 1880 */
	DWORD		   killedByWeaponID;
	CPed *		   killer;
	uint8_t		   __unknown_1896[4]; /* 1896 */
	RwV3D		   turrelOffset;
	float		   angleTurrelA;
	float		   angleTurrelB;
	DWORD		   vievPosInTurrel;
	DWORD		   ammoInTurrel;
	uint8_t		   __unknown_1928[20]; /* 1928 */
	class CPed *   TargetedPed;
	uint8_t		   __unknown_1952[36]; /* 1952 */

	void *operator new( uint32_t pedType );

	// Car methods
	bool isDriving();
	bool isDriver();
	bool isPassenger();
	bool isLeavingCar();

	bool isValid();
	bool isInPool();
	bool isActorDead();
	bool isAvailable();
	bool isControlable();
	bool isStopped();

	RwV3D getBonePos( uint8_t boneId, bool includeAnim = true ); // TODO: change to enumeration

	int		 giveWeapon( int weaponId, int ammo );
	int		 setAmmo( int weaponId, int ammo ); // return slot
	void	 setActiveWeaponSlot( int slotId );
	unsigned setWeapon( int weaponId );
	void	 clearWeapons();
	uint8_t	 getWeaponSkillIndex();
	uint8_t	 getWeaponSkillByType( int weaponId );
	void *	 removeWeaponModel( int model );
	int		 grantAmmo( int weaponId, int ammo ); // return slot

	int getPlayerNumber();

	void rotatePlayer( float zangle );
	void putToCarAsDriver( CVehicle *veh );
	void putToCarAsPassenger( CVehicle *veh, int seat = -1 );
	void setPedInCarDirect( CVehicle *veh, bool driver = true, int doorId = 10 );
	void removeDirect();

	static void	 setPlayerStatValue( int statId, float value );
	static float getPlayerStatValue( int statId );
};

#define LOCAL_PLAYER ( *reinterpret_cast<CPed **>( 0xB6F5F0 ) )
#define CPED_POOL_START 0xB7CD98
#define CPEDS_MAXIMUM 0xB74498
#define CPED_SIZE 0x7C4

#endif // CPED_H
