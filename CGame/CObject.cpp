#include "CObject.h"

CU SET_TARGATABLE_FUNC = 0x59F300;
CU IS_TARGATABLE_FUNC  = 0x59F320;
CU IS_DAMAGED_FUNC	   = 0x46A2F0;
CU IS_VALID_FUNC	   = 0x5A2C20;

int CObject::setTargatable( bool targatable ) {
	typedef int( __thiscall * CObject__setTargatable )( CObject * _this, uint8_t targatable );
	return ( CObject__setTargatable( SET_TARGATABLE_FUNC ) )( this, targatable );
}

bool CObject::isTargatable() {
	typedef int( __thiscall * CObject__isTargatable )( CObject * _this );
	return ( CObject__isTargatable( IS_TARGATABLE_FUNC ) )( this );
}

bool CObject::isDamaged() {
	typedef int( __thiscall * CObject__isDamafed )( CObject * _this );
	return ( CObject__isDamafed( IS_DAMAGED_FUNC ) )( this );
}

bool CObject::isValid() {
	typedef bool( __thiscall * CObject__isPointerValid )( CObject * _this );
	return ( CObject__isPointerValid( IS_VALID_FUNC ) )( this );
}
