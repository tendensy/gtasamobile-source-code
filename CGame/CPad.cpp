#include "CPad.h"
#include <llmo/callfunc.hpp>

CPad *CPad::get( int playerId ) {
	if ( playerId < 0 || playerId > 1 ) return nullptr;
	return &( (CPad *)0xB73458 )[playerId];
}

CControllerConfigManager *CControllerConfigManager::get() {
	return (CControllerConfigManager *)0xB70198;
}

const char *CControllerConfigManager::keyName( int action, int id ) {
	if ( !Action[action].data[id].keycode ) return "";
	auto priority = Action[action].data[id].priority;
	auto name	  = CallFunc::thiscall<const char *>( CControllerConfigManager::get(), 0x0531E20, action, priority );
	if ( !name || !*name ) return "";
	return name;
}
