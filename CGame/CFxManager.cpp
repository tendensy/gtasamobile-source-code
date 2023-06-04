#include "CFxManager.h"

CFxManager *CFxManager::Instance() {
	return (CFxManager *)0xA9AE80;
}

CFxSystem *CFxManager::CreateFxSystem( char *name, RwV3D *point, RwMatrix *mat, int flag ) {
	typedef CFxSystem *( __thiscall * func )( CFxManager * _this, char *name, RwV3D *point, RwMatrix *mat, int flag );
	return ( func( 0x4A9BE0 ) )( this, name, point, mat, flag );
}

CFx *CFx::Instance() {
	return (CFx *)0xA9AE00;
}

void CFxSystem::Play() {
	typedef void( __thiscall * func )( CFxSystem * _this );
	return ( func( 0x4AA2F0 ) )( this );
}

void CFxSystem::Stop() {
	typedef void( __thiscall * func )( CFxSystem * _this );
	return ( func( 0x4AA390 ) )( this );
}

void CFxSystem::PlayAndKill() {
	typedef void( __thiscall * func )( CFxSystem * _this );
	return ( func( 0x4AA3D0 ) )( this );
}

void CFxSystem::Kill() {
	typedef void( __thiscall * func )( CFxSystem * _this );
	return ( func( 0x4AA3F0 ) )( this );
}

void CFxSystem::AttachToBone( CPed *ped, int boneId ) {
	typedef void( __thiscall * func )( CFxSystem * _this, CPed * ped, int boneId );
	return ( func( 0x4AA400 ) )( this, ped, boneId );
}
