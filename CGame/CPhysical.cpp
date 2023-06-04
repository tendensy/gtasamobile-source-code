#include "CPhysical.h"
#include "methods.h"

CU APPLY_MOVE_FORCE_FUNC	= 0x542A07;
CU APPLY_GRAVITY_FORCE_FUNC = 0x542B50;

float CPhysical::getSpeed() {
	return speed.length();
}

void CPhysical::setSpeed( RwV3D spd ) {
	speed.fX = spd.fX;
	speed.fY = spd.fY;
	speed.fZ = spd.fZ;
}

void CPhysical::addSpeed( RwV3D spd ) {
	speed.fX += spd.fX;
	speed.fY += spd.fY;
	speed.fZ += spd.fZ;
}

void CPhysical::setSpinRot( RwV3D rot ) {
	spin.fX = matrix->getOffset( rot ).fX;
	spin.fY = matrix->getOffset( rot ).fY;
	spin.fZ = rot.fZ;
}

void CPhysical::addSpinRot( RwV3D rot ) {
	spin.fX += matrix->getOffset( rot ).fX;
	spin.fY += matrix->getOffset( rot ).fY;
	spin.fZ += rot.fZ;
}

void CPhysical::applyMoveForce( RwV3D mov ) {
	typedef void( __thiscall * CPhysical__applyMoveForce )( CPhysical * _this, CVector vec );
	( CPhysical__applyMoveForce( APPLY_MOVE_FORCE_FUNC ) )( this, mov );
}

void CPhysical::applyGravityForce( RwV3D a, CVector b, char a4 ) {
	typedef void( __thiscall * CPhysical__applyGravityForce )( CPhysical * _this, RwV3D a, CVector b, char a4 );
	( CPhysical__applyGravityForce( APPLY_GRAVITY_FORCE_FUNC ) )( this, a, b, a4 );
}

void CPhysical::stickToPlace() {
	float grav	= *reinterpret_cast<float *>( 0x863984 );
	RwV3D place = matrix->getOffset( { 0.0f, 0.0f, -1.0f } ) * ( mass * grav );
	RwV3D standard( 0.0f, 0.0f, -( mass * grav ) );
	if ( isGroundUnder() )
		applyGravityForce( place, place, 1 );
	else
		applyGravityForce( standard, standard, 1 );
}

void CPhysical::lock() {
	bLock = 1;
}

void CPhysical::unlock() {
	bLock = 0;
}

void CPhysical::toggleLock( bool state ) {
	if ( state )
		lock();
	else
		unlock();
}

bool CPhysical::isLocked() {
	return bLock;
}

bool CPhysical::isUsesGravity() {
	return this->bUsesGravity;
}

void CPhysical::setUsesGravity( bool use_gravity ) {
	this->bUsesGravity = use_gravity;
}

bool CPhysical::isOnPlace() {
	return this->bIsOnPlace;
}

float CPhysical::getSpeedRotationZ() {
	return this->speed_z;
}

void CPhysical::setSpeedRotationZ( float speed ) {
	this->speed_z = speed;
}

void CPhysical::getProof( bool &bullet, bool &fire, bool &collision, bool &melee, bool &explosion ) {
	bullet	  = bullet_proof;
	fire	  = fire_proof;
	collision = collision_proof;
	melee	  = melee_proof;
	explosion = explosion_proof;
}

void CPhysical::setProof( const bool &bullet, const bool &fire, const bool &collision, const bool &melee,
						  const bool &explosion ) {
	bullet_proof	= bullet;
	fire_proof		= fire;
	collision_proof = collision;
	melee_proof		= melee;
	explosion_proof = explosion;
}

std::deque<bool> CPhysical::getProof() {
	std::deque<bool> result;
	result.push_back( bullet_proof );
	result.push_back( fire_proof );
	result.push_back( collision_proof );
	result.push_back( melee_proof );
	result.push_back( explosion_proof );
	return result;
}

bool CPhysical::setProof( const std::deque<bool> &immunities ) {
	if ( immunities.size() != 5 ) return false;
	setProof( immunities[0], immunities[1], immunities[2], immunities[3], immunities[4] );
	return true;
}

void CPhysical::setGodMode( const bool &gm ) {
	setProof( gm, gm, gm, gm, gm );
}

bool CPhysical::isGodMode() {
	return bullet_proof && fire_proof && collision_proof && melee_proof && explosion_proof;
}

bool CPhysical::isGroundUnder() {
	return !IsLineOfSightClear( getPosition(), getPositionOffset( { 0.0f, 0.0f, -3.0f } ), 1, 0, 0, 1, 1, 0, 0 );
}
