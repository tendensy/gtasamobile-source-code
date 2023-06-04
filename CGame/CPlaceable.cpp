#include "CPlaceable.h"
#include <llmo/memsafe.h>

CU SET_ROTATION_FUNC = 0x439A80;
CU SET_HEADING_FUNC	 = 0x43E0C0;
CU GET_ROTATION_FUNC = 0x441DB0;

RwMatrix *CPlaceable::getMatrix() {
	if ( IsBadReadPtr( matrix, sizeof( RwMatrix ) ) ) return nullptr;
	return matrix;
}

float CPlaceable::setRotation( float X, float Y, float Z ) {
	typedef float( __thiscall * CPlaceable__setRotation )( CPlaceable * _this, float rotX, float rotY, float rotZ );
	return ( CPlaceable__setRotation( SET_ROTATION_FUNC ) )( this, X, Y, Z );
}

float CPlaceable::setRotation( RwV3D rot ) {
	return setRotation( rot.fX, rot.fY, rot.fZ );
}

int CPlaceable::setHeading( float Zangle ) {
	typedef int( __thiscall * CPlaceable__setHeading )( CPlaceable * _this, float rotZ );
	return ( CPlaceable__setHeading( SET_HEADING_FUNC ) )( this, Zangle );
}

long double CPlaceable::getRotation() {
	typedef long double( __thiscall * CPlaceable__getRotation )( CPlaceable * _this );
	return ( CPlaceable__getRotation( GET_ROTATION_FUNC ) )( this );
}

RwV3D CPlaceable::getPosition() {
	if ( getMatrix() ) return matrix->pos;
	return pos;
}

RwV3D CPlaceable::getPositionOffset( RwV3D offset ) {
	if ( getMatrix() ) return matrix->pos + matrix->getOffset( offset );
	return RwV3D();
}

void CPlaceable::setPosition( RwV3D pos ) {
	if ( getMatrix() ) matrix->pos = pos;
	this->pos = pos;
}

void CPlaceable::addPosition( RwV3D pos ) {
	if ( getMatrix() ) matrix->pos += pos;
	this->pos += pos;
}

void CPlaceable::addOffsetPosition( RwV3D pos ) {
	if ( getMatrix() ) matrix->pos = getPositionOffset( pos );
}

float CPlaceable::getAngleZ() {
	if ( getMatrix() ) return matrix->getAngleZ();
	return this->angle;
}

void CPlaceable::setAngleZ( float angle ) {
	if ( getMatrix() )
		matrix->rotZ( angle );
	else
		this->angle = angle;
}

void CPlaceable::addAngleZ( float angle ) {
	if ( getMatrix() )
		matrix->rotZ( matrix->getAngleZ() + angle );
	else
		this->angle += angle;
}

bool CPlaceable::isValid() {
	if ( IsBadReadPtr( this, sizeof( CPlaceable ) ) ) return false;
	return true;
}
