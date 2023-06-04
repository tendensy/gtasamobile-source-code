#include "CVehiclePool.h"
#include "../CPed.h"
#include <algorithm>
#include <llmo/callfunc.hpp>

CVehicle *CVehiclePool::atIndex( int id ) {
	return CallFunc::thiscall<CVehicle *>( this, 0x41CC10, id );
}

int CVehiclePool::handleOf( CVehicle *veh ) {
	return CallFunc::thiscall<int>( this, 0x424160, veh );
}

CVehicle *CVehiclePool::atHandle( int handle ) {
	return CallFunc::thiscall<CVehicle *>( this, 0x4048E0, handle );
}

void CVehiclePool::fix() {
	for ( int i = 0; i < this->getSize(); ++i )
		if ( this->atIndex( i ) != nullptr ) this->atIndex( i )->fix();
}

void CVehiclePool::playCarHorn() {
	for ( int i = 0; i < this->getSize(); ++i )
		if ( this->atIndex( i ) != nullptr ) this->atIndex( i )->playCarHorn();
}

void CVehiclePool::setHitpoints( float hp ) {
	for ( int i = 0; i < this->getSize(); ++i )
		if ( this->atIndex( i ) != nullptr ) this->atIndex( i )->setHitpoints( hp );
}

void CVehiclePool::repair() {
	for ( int i = 0; i < this->getSize(); ++i )
		if ( this->atIndex( i ) != nullptr ) this->atIndex( i )->repair();
}

void CVehiclePool::lockCar() {
	for ( int i = 0; i < this->getSize(); ++i )
		if ( this->atIndex( i ) != nullptr ) this->atIndex( i )->lockCar();
}

void CVehiclePool::lockIfEmpty() {
	for ( int i = 0; i < this->getSize(); ++i )
		if ( this->atIndex( i ) != nullptr )
			if ( this->atIndex( i )->isEmpty() && this->atIndex( i )->speed.length() < 0.05f )
				this->atIndex( i )->lock();
}

void CVehiclePool::unlockNotEmpty() {
	for ( int i = 0; i < this->getSize(); ++i )
		if ( this->atIndex( i ) != nullptr )
			if ( !this->atIndex( i )->isEmpty() ) this->atIndex( i )->unlock();
}

void CVehiclePool::processAntiCollision( const std::deque<CVehicle *> &exclude, const RwV3D &pos, const float &dist ) {
	for ( int i = 0; i < this->getSize(); ++i ) {
		auto veh = this->atIndex( i );
		if ( !veh ) continue;
		if ( !veh->getMatrix() ) continue;
		if ( std::find( exclude.begin(), exclude.end(), veh ) != exclude.end() ) continue;
		if ( ( pos != RwV3D( 0, 0, 0 ) && ( veh->getPosition() - pos ).length() > dist ) || veh->matrix->at.fZ < 0.5f )
			veh->bUsesCollision = true;
		else
			veh->bUsesCollision = false;
	}
}

void CVehiclePool::setAngularVelocity( RwV3D angularVelocity ) {
	for ( int i = 0; i < this->getSize(); ++i )
		if ( this->atIndex( i ) != nullptr ) this->atIndex( i )->setAngularVelocity( angularVelocity );
}

int CVehiclePool::getScmHandle( CVehicle *veh ) {
	typedef int( __thiscall * CVehiclePool__getHandle )( CVehiclePool * _this, CVehicle * veh );
	return ( CVehiclePool__getHandle( 0x424160 ) )( this, veh );
}

void CVehiclePool::kickOffDrivers() {
	for ( int i = 0; i < this->getSize(); ++i )
		if ( this->atIndex( i ) != nullptr ) this->atIndex( i )->kickOffDriver();
}

void CVehiclePool::kickOffPassengers() {
	for ( int i = 0; i < this->getSize(); ++i )
		if ( this->atIndex( i ) != nullptr ) this->atIndex( i )->kickOffPassengers();
}

void CVehiclePool::kickOffAll() {
	for ( int i = 0; i < this->getSize(); ++i )
		if ( this->atIndex( i ) != nullptr ) this->atIndex( i )->kickOffAll();
}
