#include "CEntity.h"
#include "CModel.h"
#include "methods.h"
#include <llmo/memsafe.h>

#ifdef _MSC_VER
#	define strncasecmp _strnicmp
#	define strcasecmp _stricmp
#endif

CU	 REMOVE_REF_TO_ENTITY_FUNC		= 0x544280;
CU	 IS_VALID_FUNC					= 0x533310;
CU	 SET_HEADING_FUNC				= 0x43E0C0;
CU	 GET_HEADING_FUNC				= 0x0049D520;
CU	 UPDATERW_FUNC					= 0x446F90;
auto MODEL_INFO_ARRAY				= (CModel **)0xA9B0C8;
CU	 SET_ALPHA						= 0x5332C0;
CU	 GET_FRAME						= 0x4C53C0;
CU	 GET_FRAMEBYNAME				= 0x4C5400;
CU	 GET_MODELLING_MATRIX			= 0x46A2D0;
CU	 GET_BOUND_CNETRE				= 0x534250;
CU	 RpGeometryForAllMaterials_FUCN = 0x74C790;
CU	 RpClumpForAllAtomics_FUCN		= 0x749B70;

bool CEntity::teleport( RwV3D pos, bool lockRotate ) {
	return teleport( pos.fX, pos.fY, pos.fZ, lockRotate );
}

bool CEntity::isVehicle() {
	//return ( modelID >= 400 && modelID <= 611 );
	return nType == 2;
}

bool CEntity::isPed() {
	return modelID <= 311;
}

bool CEntity::isUnderWater() {
	return this->bUnderwater;
}

bool CEntity::isOnScreen() {
	return this->bOffscreen ^ true;
}

bool CEntity::isValidEntity() {
	typedef bool( __thiscall * CEntity__isPointerValid )( CEntity * _this );
	return ( CEntity__isPointerValid( IS_VALID_FUNC ) )( this );
}

bool CEntity::isValid() {
	//	if ( memsafe::isBadPtrRead( this, sizeof( CEntity ) ) ) return false;
	if ( IsBadReadPtr( this, sizeof( CEntity ) ) ) return false;
	//	if ( matrix == nullptr ) return false;
	if ( bRemoveFromWorld ) return false;
	return true;
}

bool CEntity::isVisible() {
	return this->bIsVisible;
}

void CEntity::setVisible( bool visible ) {
	this->bIsVisible = visible;
}

bool CEntity::isUsesCollision() {
	return this->bUsesCollision;
}

bool CEntity::isCollisionProcessed() {
	return this->bCollisionProcessed;
}

void CEntity::setUsesCollision( bool collision ) {
	this->bUsesCollision = collision;
}

bool CEntity::_removeRefsToEntity( int a2 ) {
	typedef bool( __thiscall * CEntity__removeRefToEntity )( CEntity * _this, int a2 );
	return ( CEntity__removeRefToEntity( REMOVE_REF_TO_ENTITY_FUNC ) )( this, a2 );
}

void CEntity::setHeading( float zangle ) {
	typedef void( __thiscall * CEntity__SetHeading )( CEntity * _this, float angle );
	return ( CEntity__SetHeading( SET_HEADING_FUNC ) )( this, zangle * 57.2956 );
}

double CEntity::getHeading() {
	typedef float( __cdecl * CEntity__GetHeading )( CEntity * _this );
	return ( CEntity__GetHeading( GET_HEADING_FUNC ) )( this ) * 0.0175;
}

void CEntity::updateRwMatrix() {
	typedef void( __thiscall * CEntity__UpdateRW_ )( CEntity * _this );
	return ( CEntity__UpdateRW_( UPDATERW_FUNC ) )( this );
}

CModel *CEntity::getModelInfo() {
	return MODEL_INFO_ARRAY[modelID];
}

CBaseModelInfo *CEntity::getBaseModelInfo() {
	return CBaseModelInfo::getModel( modelID );
}

void CEntity::setAlpha( DWORD alpha ) {
	if ( alpha && alpha != 255 )
		CBaseModelInfo::getModel( modelID )->bAlphaTransparency = 1;
	else
		CBaseModelInfo::getModel( modelID )->bAlphaTransparency = 0;
	CBaseModelInfo::getModel( modelID )->ucAlpha = alpha;
	typedef void( __thiscall * CEntity__SetAplha )( CEntity * _this, DWORD _alpha );
	return ( CEntity__SetAplha( SET_ALPHA ) )( this, alpha );
}

char CEntity::getAlpha() {
	if ( CBaseModelInfo::getModel( modelID )->bAlphaTransparency ) return CBaseModelInfo::getModel( modelID )->ucAlpha;
	return -1;
}

RwFrame *CEntity::GetFrameFromId( int id ) {
	typedef RwFrame *( __cdecl * CClumpModelInfo__GetFrameFromId )( RpClump * _clump, int _id );
	return ( CClumpModelInfo__GetFrameFromId( GET_FRAME ) )( ptr_RpClump, id );
}

RwFrame *CEntity::GetFrameFromName( char *name ) {
	typedef RwFrame *( __cdecl * CClumpModelInfo__GetFrameFromName )( RpClump * _clump, char *_name );
	return ( CClumpModelInfo__GetFrameFromName( GET_FRAMEBYNAME ) )( ptr_RpClump, name );
}

std::deque<RpGeometry *> CEntity::getAllGeometry() {
	std::deque<RpGeometry *> result;

	if ( ptr_RpClump->object.type == 1 && ptr_RpClump->cameraList.link.next ) {
		result.push_back( (RpGeometry *)ptr_RpClump->cameraList.link.next );
	} else if ( ptr_RpClump->object.type == 2 && ptr_RpClump->atomicList.link.next ) {
		auto atomics = getAllAtomics();
		for ( auto &&atomic : atomics )
			if ( atomic->geometry ) result.push_back( atomic->geometry );
	}

	return result;
}

std::deque<RpAtomic *> CEntity::getAllAtomics() {
	std::deque<RpAtomic *> result;

	if ( ptr_RpClump->object.type == 2 && ptr_RpClump->atomicList.link.next ) {
		RpAtomic *v3;	// eax
		RpAtomic *next; // esi

		v3 = (RpAtomic *)ptr_RpClump->atomicList.link.next;
		if ( v3 != (RpAtomic *)&ptr_RpClump->atomicList ) {
			do {
				next		= *(RpAtomic **)&v3->object.object.type;
				auto atomic = (RpAtomic *)( (char *)v3 - 64 );
				if ( atomic ) result.push_back( atomic );
				v3 = next;
			} while ( next != (RpAtomic *)&ptr_RpClump->atomicList );
		}
	}
	return result;
}

std::deque<RpMaterial *> CEntity::getAllMaterials() {
	std::deque<RpMaterial *> result;

	auto geos = getAllGeometry();
	for ( auto &&geo : geos )
		for ( int i = 0; i < geo->matList.numMaterials; ++i )
			if ( geo->matList.materials[i] ) result.push_back( geo->matList.materials[i] );

	return result;
}

std::deque<RpMaterial *> CEntity::getMaterials( const char *name ) {
	std::deque<RpMaterial *> result;

	auto allMaterials = getAllMaterials();
	for ( auto &&material : allMaterials )
		if ( material->texture && !IsBadReadPtr( material->texture, sizeof( RwTexture ) ) )
			if ( !strcasecmp( material->texture->name, name ) ) result.push_back( material );

	return result;
}

CMatrix *CEntity::getModellingMatrix() {
	typedef CMatrix *( __thiscall * CEntity__getModellingMatrix )( CEntity * _this );
	return ( CEntity__getModellingMatrix( GET_MODELLING_MATRIX ) )( this );
}

RwV3D *CEntity::GetBoundCentre( RwV3D *vec ) {
	typedef RwV3D *( __thiscall * CEntity__GetBoundCentre )( CEntity * _this, RwV3D * outPoint );
	return ( CEntity__GetBoundCentre( GET_MODELLING_MATRIX ) )( this, vec );
}
