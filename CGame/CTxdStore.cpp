#include "CTxdStore.h"
#include "Types.h"
#include <llmo/callfunc.hpp>

CU ADDTXDSLOT_FUNC	  = 0x00731C80;
CU REMOVETXDSLOT_FUNC = 0x00731CD0;
CU LOADTXD_FUNC		  = 0x007320B0;
CU REMOVETXD_FUNC	  = 0x00731E90;
CU ADDREF_FUNC		  = 0x00731A00;
CU REMOVEREF_FUNC	  = 0x00731A30;
CU COUNTREF_FUNC	  = 0x00731AA0;
CU PUSHCURRENT_FUNC	  = 0x007316A0;
CU POPCURRENT_FUNC	  = 0x007316B0;
CU SETCURRENTTXD_FUNC = 0x007319C0;
CU FINDSLOT_FUNC	  = 0x00731850;
CU RWTEXTUREREAD_FUNC = 0x007F3AC0;

CTxdSlot::CTxdSlot( const int &index ) : index( index ) {}

CTxdSlot::CTxdSlot( const char *name ) {
	index = CallFunc::ccall<int>( ADDTXDSLOT_FUNC, name );
}

CTxdSlot::~CTxdSlot() {
	CallFunc::ccall<void>( REMOVETXDSLOT_FUNC, index );
}

int CTxdSlot::load( const char *name ) {
	return CallFunc::ccall<int>( LOADTXD_FUNC, index, name );
}

void CTxdSlot::remove() {
	return CallFunc::ccall<void>( REMOVETXD_FUNC, index );
}

void *CTxdSlot::addRef() const {
	return CallFunc::ccall<void *>( ADDREF_FUNC, index );
}

void CTxdSlot::removeRef() const {
	return CallFunc::ccall<void>( REMOVEREF_FUNC, index );
}

int CTxdSlot::countRef() const {
	return CallFunc::ccall<int>( COUNTREF_FUNC, index );
}

int CTxdSlot::getIndex() const {
	return index;
}

void CTxdStore::push() {
	CallFunc::ccall<void>( PUSHCURRENT_FUNC );
}

void CTxdStore::pop() {
	CallFunc::ccall<void>( POPCURRENT_FUNC );
}

int CTxdStore::setSlot( const CTxdSlot *slot ) {
	return CallFunc::ccall<int>( SETCURRENTTXD_FUNC, slot->getIndex() );
}

int CTxdStore::findSlotIndex( const char *name ) {
	return CallFunc::ccall<int>( FINDSLOT_FUNC, name );
}

CTxdSlot *CTxdStore::findSlot( const char *name ) {
	auto index = findSlotIndex( name );
	if ( index == -1 ) return nullptr;
	return new CTxdSlot( index );
}

void *CTxdStore::rwTexture( const char *name, const char *maskName ) {
	return CallFunc::ccall<void *>( RWTEXTUREREAD_FUNC, name, maskName );
}
