#include "CVehicle.h"
#include "CCamera.h"
#include "CPed.h"
#include "Pools.h"
#include "methods.h"
#include <llmo/callfunc.hpp>

typedef bool( __cdecl *CVehicle__isType )( int modelId );
CU IS_BOAT_FUNC				 = 0x4c5a70;
CU IS_CAR_FUNC				 = 0x4c5aa0;
CU IS_TRAIN_FUNC			 = 0x4c5ad0;
CU IS_HELI_FUNC				 = 0x4c5b00;
CU IS_PLANE_FUNC			 = 0x4c5b30;
CU IS_BIKE_FUNC				 = 0x4c5b60;
CU IS_FAKE_PLANE_FUNC		 = 0x4c5b90;
CU IS_MONSTER_TRUCK_FUNC	 = 0x4c5bc0;
CU IS_QUAD_BIKE_FUNC		 = 0x4c5bf0;
CU IS_BMX_FUNC				 = 0x4c5c20;
CU IS_TRAILER_FUNC			 = 0x4c5c50;
CU LOCK_VEHICLE_FUNC		 = 0x5433B0;
CU SET_ANGULAR_VELOCITY_FUNC = 0x45AFB0;
CU IS_VALID_FUNC			 = 0x6E38F0;

float CVehicle::getHitpoints() {
	return this->hitpoints;
}

void CVehicle::setHitpoints( float hp ) {
	this->hitpoints = hp;
}

void CVehicle::repair() {
	fix();
	setHitpoints( 1000.0f );
}

bool CVehicle::switchModel(
	int id ) { // TODO: Скорее всего не будет работать - сделать как хотел изначально, через замену модели,
	// хендлингов и очистку некоторых параметров, типа тюнинга
	if ( id < 400 || id > 611 ) return false;
	class CPed *players[9];
	memcpy( players, this->players, sizeof( players ) );
	kickOffAll();
	auto spn   = spin;
	auto spd   = speed;
	auto spd_a = speed_acceleration;
	auto spn_a = spin_acceleration;
	auto vf	   = m_vForce;
	auto vt	   = m_vTorque;
	auto mat   = matrix;
	if ( ( CVehicle__isType( IS_CAR_FUNC ) )( id ) )
		CallFunc::thiscall<int>( this, 0x006B0A90, id, VehicleCreatedBy, 1 );
	else if ( ( CVehicle__isType( IS_BOAT_FUNC ) )( id ) )
		CallFunc::thiscall<int>( this, 0x006F2940, id, VehicleCreatedBy );
	else if ( ( CVehicle__isType( IS_HELI_FUNC ) )( id ) )
		CallFunc::thiscall<int>( this, 0x006C4190, id, VehicleCreatedBy );
	else if ( ( CVehicle__isType( IS_PLANE_FUNC ) )( id ) )
		CallFunc::thiscall<int>( this, 0x006C8E20, id, VehicleCreatedBy );
	else if ( ( CVehicle__isType( IS_BIKE_FUNC ) )( id ) )
		CallFunc::thiscall<int>( this, 0x006BF430, id, VehicleCreatedBy );
	else if ( ( CVehicle__isType( IS_MONSTER_TRUCK_FUNC ) )( id ) )
		CallFunc::thiscall<int>( this, 0x006C8D60, id, VehicleCreatedBy );
	else if ( ( CVehicle__isType( IS_QUAD_BIKE_FUNC ) )( id ) )
		CallFunc::thiscall<int>( this, 0x006CE370, id, VehicleCreatedBy );
	else if ( ( CVehicle__isType( IS_BMX_FUNC ) )( id ) )
		CallFunc::thiscall<int>( this, 0x006BF820, id, VehicleCreatedBy );
	else if ( ( CVehicle__isType( IS_TRAIN_FUNC ) )( id ) )
		CallFunc::thiscall<int>( this, 0x006F6030, id, VehicleCreatedBy );
	else if ( ( CVehicle__isType( IS_TRAILER_FUNC ) )( id ) )
		CallFunc::thiscall<int>( this, 0x006D03A0, id, VehicleCreatedBy );
	else
		return false;
	matrix			   = mat;
	m_vTorque		   = vt;
	m_vForce		   = vf;
	spin_acceleration  = spn_a;
	speed_acceleration = spd_a;
	speed			   = spd;
	spin			   = spn;
	players[0]->putToCarAsDriver( this );
	for ( int i = 0; i < m_nNumPassengers; ++i ) players[i + 1]->putToCarAsPassenger( this );
	return true;
}

bool CVehicle::isValid() {
	if ( IsBadReadPtr( this, sizeof( CVehicle ) ) ) return false;
	if ( matrix == nullptr ) return false;
	if ( bRemoveFromWorld ) return false;
	if ( m_pCollisionList == nullptr ) return false;
	for ( int i = 0; i < Pools::vehicles()->getSize(); ++i )
		if ( Pools::vehicles()->atIndexForce( i ) == this ) return true;
	return false;
	//	typedef bool( __thiscall * CVehicle__isPointerValid )( CVehicle * _this );
	//	return ( CVehicle__isPointerValid( IS_VALID_FUNC ) )( this );
}

bool CVehicle::isBoat() {
	return ( CVehicle__isType( IS_BOAT_FUNC ) )( modelID );
}

bool CVehicle::isCar() {
	return ( CVehicle__isType( IS_CAR_FUNC ) )( modelID );
}

bool CVehicle::isTrain() {
	return ( CVehicle__isType( IS_TRAIN_FUNC ) )( modelID );
}

bool CVehicle::isHeli() {
	return ( CVehicle__isType( IS_HELI_FUNC ) )( modelID );
}

bool CVehicle::isPlane() {
	return ( CVehicle__isType( IS_PLANE_FUNC ) )( modelID );
}

bool CVehicle::isBike() {
	return ( CVehicle__isType( IS_BIKE_FUNC ) )( modelID );
}

bool CVehicle::isFakePlane() {
	return ( CVehicle__isType( IS_FAKE_PLANE_FUNC ) )( modelID );
}

bool CVehicle::isMonsterTruck() {
	return ( CVehicle__isType( IS_MONSTER_TRUCK_FUNC ) )( modelID );
}

bool CVehicle::isQuadBike() {
	return ( CVehicle__isType( IS_QUAD_BIKE_FUNC ) )( modelID );
}

bool CVehicle::isBmx() {
	return ( CVehicle__isType( IS_BMX_FUNC ) )( modelID );
}

bool CVehicle::isTrailer() {
	return ( CVehicle__isType( IS_TRAILER_FUNC ) )( modelID );
}

bool CVehicle::isEmpty() {
	for ( int i = 0; i < 9; ++i ) {
		if ( !players[i] ) continue;
		if ( !players[i]->isValid() ) continue;
		return false;
	}
	return true;
}

bool CVehicle::withPlayer( CPed *ped ) {
	if ( !ped ) return false;
	for ( int i = 0; i < 9; ++i )
		if ( players[i] == ped ) return true;
	return false;
}

void CVehicle::kickOff( CPed *ped ) {
	if ( !ped ) return;
	if ( !ped->isValid() ) return;
	if ( !ped->isDriving() ) return;
	if ( ped->vehicle != this ) return;
	uint8_t task[24];
	CallFunc::thiscall<void *>( task, 0x6478B0, this, 10, 0 ); // create task
	task[19] = 1;											   // knock of bike
	task[17] = 1;											   // wrap ped to car
	CallFunc::thiscall<bool>( task, 0x647D10, ped );		   // process player in task
	CallFunc::thiscall<void>( task, 0x64BF70, false );		   // destroy task
}

void CVehicle::kickOffDriver() {
	kickOff( driver );
}

void CVehicle::kickOffPassenger( uint8_t seat ) {
	if ( seat <= m_nMaxPassengers ) kickOff( players[seat + 1] );
}

void CVehicle::kickOffPassengers() {
	for ( int i = 1; i < 9; ++i ) kickOff( players[i] );
}

void CVehicle::kickOffAll() {
	for ( int i = 0; i < 9; ++i ) kickOff( players[i] );
}

bool CVehicle::lockCar() {
	typedef bool( __thiscall * CVehicle__lock )( CVehicle * _this );
	return ( CVehicle__lock( LOCK_VEHICLE_FUNC ) )( this );
}

float CVehicle::setAngularVelocity( RwV3D angularVelocity ) {
	typedef float( __thiscall * CVehicle__setAngularVelocity )( CVehicle * _this, float X, float Y, float Z );
	return ( CVehicle__setAngularVelocity( SET_ANGULAR_VELOCITY_FUNC ) )( this, angularVelocity.fX, angularVelocity.fY,
																		  angularVelocity.fZ );
}

bool CVehicle::isEngineOn() {
	return engineState;
}

void CVehicle::setEngineState( bool state ) {
	engineState = state;
}
