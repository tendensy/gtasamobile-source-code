#include "CModel.h"

CBaseModelInfo *CBaseModelInfo::getModel( int id ) {
	if ( id < 0 || id > 20000 ) return nullptr;
	return ( (CBaseModelInfo **)0xA9B0C8 )[id];
}
