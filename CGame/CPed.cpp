#include "CPed.h"
#include "CVehicle.h"
#include "Pools.h"
#include "methods.h"
#include <llmo/callfunc.hpp>
#include <llmo/memsafe.h>

CU BONE_POS_FUNC				 = 0x5E01C0;
CU GIVE_WEAPON_FUNC				 = 0x5E6080;
CU SET_AMMO_FUNC				 = 0x5DF290;
CU IS_AVAILABLE_FUNC			 = 0x5E0170;
CU SET_ACTIVE_WEAPON_SLOT_FUNC	 = 0x5E61F0;
CU SET_WEAPON_FUNC				 = 0x5E6280;
CU CLEAR_WEAPONS_FUNC			 = 0x5E6320;
CU GET_WEAPON_SKILL_INDEX_FUNC	 = 0x5E6580;
CU GET_WEAPON_SKILL_BY_TYPE_FUNC = 0x5E3B60;
CU REMOVE_WEAPON_MODEL_FUNC		 = 0x5E3990;
CU GRANT_AMMO_FUNC				 = 0x5DF220;
// CU SET_MODEL_INDEX_FUNC = 0x5E4880;
CU IS_CONTROLABLE_FUNC		  = 0x609590;
CU CPED_CONSTRUCTOR			  = 0x5E8030;
CU SET_PLAYER_STAT_VALUE_FUNC = 0x55A070;
CU GET_PLAYER_STAT_VALUE_FUNC = 0x558E40;
CU GET_PLAYER_NUMBER_FUNC	  = 0x563FA0;
CU IS_VALID_FUNC			  = 0x5E4220;

void *CPed::operator new( uint32_t pedType ) {
	uint8_t *_this = new uint8_t[sizeof( CPed )];
	typedef bool( __thiscall * CPed__CPed )( void *_this, uint32_t type );
	( CPed__CPed( CPED_CONSTRUCTOR ) )( _this, pedType );
	return reinterpret_cast<void *>( _this );
}

bool CPed::isDriving() {
	return state == 50 && vehicle != nullptr;
}

bool CPed::isDriver() {
	if ( !isDriving() ) return false;
	return vehicle->driver == this;
}

bool CPed::isPassenger() {
	return ( isDriving() && !isDriver() );
}

bool CPed::isLeavingCar() {
	if ( isDriving() ) return false;
	return state == 0;
}

bool CPed::isValid() {
	//	if ( memsafe::isBadPtrRead( this, sizeof( CPed ) ) ) return false;
	if ( IsBadReadPtr( this, sizeof( CPed ) ) ) return false;
	if ( matrix == nullptr ) return false;
	if ( bRemoveFromWorld ) return false;
	if ( m_pCollisionList == nullptr ) return false;
	if ( isInPool() ) return true;
	return false;
	//	typedef bool( __thiscall * CPed__isPointerValid )( CPed * _this );
	//	return ( CPed__isPointerValid( IS_VALID_FUNC ) )( this );
}

bool CPed::isInPool() {
	for ( int i = 0; i < *(int *)0x550FF2; ++i )
		if ( Pools::peds()->atIndexForce( i ) == this ) return true;
	return false;
}

bool CPed::isActorDead() {
	return ( state == 55 || state == 63 || hitpoints == 0.0f );
}

bool CPed::isAvailable() {
	typedef bool( __thiscall * CPed__isAvailable )( CPed * _this );
	return ( CPed__isAvailable( IS_AVAILABLE_FUNC ) )( this );
}

bool CPed::isControlable() {
	typedef bool( __thiscall * CPed__isControlable )( CPed * _this );
	return ( CPed__isControlable( IS_CONTROLABLE_FUNC ) )( this );
}

bool CPed::isStopped() {
	return ( getSpeed() < 0.0001f );
}

RwV3D CPed::getBonePos( uint8_t boneId, bool includeAnim ) {
	RwV3D Position = { 0.0, 0.0, 0.0 };

	typedef int( __thiscall * CPed__getBonePositionWithOffset )( CPed * _this, RwV3D * _offset, int _bodeId,
																 bool _includeAnim );
	( CPed__getBonePositionWithOffset( BONE_POS_FUNC ) )( this, &Position, boneId, includeAnim );

	return Position;
}

int CPed::giveWeapon( int weaponId, int ammo ) {
	loadWeaponModel( weaponId );
	typedef int( __thiscall * CPed__giveWeapon )( CPed * _this, int weapId, int ammo, int unk );
	return ( CPed__giveWeapon( GIVE_WEAPON_FUNC ) )( this, weaponId, ammo, 0 );
}

int CPed::setAmmo( int weaponId, int ammo ) {
	typedef int( __thiscall * CPed__setAmmo )( CPed * _this, int weaponId, int ammo );
	return ( CPed__setAmmo( SET_AMMO_FUNC ) )( this, weaponId, ammo );
}

void CPed::setActiveWeaponSlot( int slotId ) {
	typedef void( __thiscall * CPed__setActiveWeaponSlot )( CPed * _this, int slotId );
	( CPed__setActiveWeaponSlot( SET_ACTIVE_WEAPON_SLOT_FUNC ) )( this, slotId );
}

unsigned CPed::setWeapon( int weaponId ) {
	typedef unsigned( __thiscall * CPed__setWeapon )( CPed * _this, int weaponId );
	return ( CPed__setWeapon( SET_WEAPON_FUNC ) )( this, weaponId );
}

void CPed::clearWeapons() {
	typedef void( __thiscall * CPed__clearWeapons )( CPed * _this );
	( CPed__clearWeapons( CLEAR_WEAPONS_FUNC ) )( this );
}

uint8_t CPed::getWeaponSkillIndex() {
	typedef uint8_t( __thiscall * CPed__getWeaponSkillIndex )( CPed * _this );
	return ( CPed__getWeaponSkillIndex( GET_WEAPON_SKILL_INDEX_FUNC ) )( this );
}

uint8_t CPed::getWeaponSkillByType( int weaponId ) {
	typedef uint8_t( __thiscall * CPed__getWeaponSkillByType )( CPed * _this, int wType );
	return ( CPed__getWeaponSkillByType( GET_WEAPON_SKILL_BY_TYPE_FUNC ) )( this, weaponId );
}

void *CPed::removeWeaponModel( int model ) {
	typedef void *( __thiscall * CPed__removeWeaponModel )( CPed * _this, int model );
	return ( CPed__removeWeaponModel( REMOVE_WEAPON_MODEL_FUNC ) )( this, model );
}

int CPed::grantAmmo( int weaponId, int ammo ) {
	typedef int( __thiscall * CPed__grantAmmo )( CPed * _this, int weaponId, int ammo );
	return ( CPed__grantAmmo( GRANT_AMMO_FUNC ) )( this, weaponId, ammo );
}

int CPed::getPlayerNumber() {
	typedef int( __cdecl * CPlayer__getPlayerNumberForPed )( CPed * ped );
	return ( CPlayer__getPlayerNumberForPed( GET_PLAYER_NUMBER_FUNC ) )( this );
}

void CPed::rotatePlayer( float zangle ) {
	fCurrentRotation = zangle;
	fTargetRotation	 = zangle;
	setHeading( zangle );
	updateRwMatrix();
}

void CPed::putToCarAsDriver( CVehicle *veh ) {
	if ( !veh ) return;
	uint8_t task[28];
	CallFunc::thiscall<void *>( task, 0x6470E0, veh, 0 ); // create task
	task[24] = 1;										  // wrap ped to car
	CallFunc::thiscall<bool>( task, 0x64B950, this );	  // process player in task
	CallFunc::thiscall<void>( task, 0x64B930, false );	  // destroy task
}

void CPed::putToCarAsPassenger( CVehicle *veh, int seat ) {
	if ( !veh ) return;
	if ( seat == -1 ) {
		for ( int i = 0; i < veh->m_nMaxPassengers; ++i ) {
			if ( veh->players[i + 1] == nullptr || !veh->players[i + 1]->isValid() ) {
				seat = i;
				break;
			}
		}
		if ( seat == -1 ) {
			for ( int i = veh->m_nMaxPassengers; i < 8; ++i ) {
				if ( veh->players[i + 1] == nullptr || !veh->players[i + 1]->isValid() ) {
					seat = i;
					break;
				}
			}
		}
	}
	if ( seat == -1 ) return;
	uint8_t task[32];
	CallFunc::thiscall<void *>( task, 0x646FE0, veh, seat, 0 ); // create task
	task[28] = 1;												// wrap ped to car
	CallFunc::thiscall<bool>( task, 0x64B5D0, this );			// process player in task
	CallFunc::thiscall<void>( task, 0x64B5B0, false );			// destroy task
}

void CPed::setPedInCarDirect( CVehicle *veh, bool driver, int doorId ) {
	CallFunc::ccall<void>( 0x650280, this, veh, doorId, driver );
}

void CPed::removeDirect() {
	if ( *(CPed **)ptr_pedIntelligence != this ) return;
	auto taskMgr = ptr_pedIntelligence + 4;
	auto taskId	 = 3;
	auto task	 = taskMgr + ( taskId * sizeof( void * ) );
	if ( task != 0 ) {
		auto outPos = matrix->pos + 1.5;
		if ( isDriver() ) {
			vehicle->kickOffDriver();
			outPos = vehicle->matrix->pos + 1.5;
		}
		CallFunc::thiscall<void>( taskMgr, 0x681AF0, nullptr, taskId, 0 );
		CallFunc::ccall<void>( 0x441290, 0, outPos );
	}
}

void CPed::setPlayerStatValue( int statId, float value ) {
	typedef void( __cdecl * __setPlayerStatValue )( int statId, float value );
	( __setPlayerStatValue( SET_PLAYER_STAT_VALUE_FUNC ) )( statId, value );
}

float CPed::getPlayerStatValue( int statId ) {
	typedef float( __cdecl * __getPlayerStatValue )( uint16_t statId );
	return ( __getPlayerStatValue( GET_PLAYER_STAT_VALUE_FUNC ) )( statId );
}
