#include "methods.h"
#include <cmath>
#define M_PI 3.14159

CU IS_LINE_OF_SIGHT_CLEAR_FUNC		= 0x56A490;
CU FIND_PLAYER_PED_FUNC				= 0x56E210;
CU REQUEST_MODEL_FUNC				= 0x4087e0;
CU LOAD_ALL_REQUESTED_MODELS		= 0x40ea10;
CU GET_ANGLE_BETWEEN_POINTS_FUNC	= 0x53CBE0;
CU CONVERT_WORLD_TO_SCREEN_POS_FUNC = 0x70CE30;
CU GET_FRAME_NAME_FUNC				= 0x72FB30;

void GetMatrixForGravity( CVector &vecGravity, CMatrix &mat ) {
	// Calculates a basis where the z axis is the inverse of the gravity
	if ( vecGravity.length() > 0.0001f ) {
		mat.up = -vecGravity;
		mat.up.normalize();
		if ( fabs( mat.up.fX ) > 0.0001f || fabs( mat.up.fZ ) > 0.0001f ) {
			CVector y( 0.0f, 1.0f, 0.0f );
			mat.at = vecGravity;
			mat.at.CrossProduct( &y );
			mat.at.CrossProduct( &vecGravity );
			mat.at.normalize();
		} else {
			mat.at = CVector( 0.0f, 0.0f, vecGravity.fY );
		}
		mat.right = mat.at;
		mat.right.CrossProduct( &mat.up );
	} else {
		// No gravity, use default axes
		mat.right = CVector( 1.0f, 0.0f, 0.0f );
		mat.at	  = CVector( 0.0f, 1.0f, 0.0f );
		mat.up	  = CVector( 0.0f, 0.0f, 1.0f );
	}
}

bool IsLineOfSightClear( RwV3D start, RwV3D end, bool buildings, bool vehicles, bool peds, bool objects, bool dummies,
						 bool seeThroughStuff, bool ignoreSomeObjectsForCamera ) {
	typedef bool( __cdecl * _IsLineOfSightClear )( RwV3D * start, RwV3D * end, bool buildings, bool vehicles, bool peds,
												   bool objects, bool dummies, bool seeThroughStuff,
												   bool ignoreSomeObjectsForCamera );
	return ( _IsLineOfSightClear( IS_LINE_OF_SIGHT_CLEAR_FUNC ) )(
		&start, &end, buildings, vehicles, peds, objects, dummies, seeThroughStuff, ignoreSomeObjectsForCamera );
}

class CPed *findPlayerPed( int handle ) {
	typedef class CPed *( __cdecl * __findPlayerPed )( int id );
	return ( __findPlayerPed( FIND_PLAYER_PED_FUNC ) )( handle );
}

float getAngleBetweenPoints( float x1, float y1, float x2, float y2 ) {
	typedef float( __cdecl * CGeneral__GetRadianAngleBetweenPoints )( float x1, float y1, float x2, float y2 );
	return ( CGeneral__GetRadianAngleBetweenPoints( GET_ANGLE_BETWEEN_POINTS_FUNC ) )( x1, y1, x2, y2 );
}

float getAngleBetweenPointsDeg( float x1, float y1, float x2, float y2 ) {
	return getAngleBetweenPoints( x1, y1, x2, y2 ) * float( M_PI / 2.0 );
}

int isModelLoaded( eModelIndex modelID ) {
	int *ModelsLoadStateArray = (int *)0x8E4CD0;
	return ModelsLoadStateArray[5 * modelID];
}

bool requestModelLoad( eModelIndex modelID ) {
	if ( isModelLoaded( modelID ) ) return false;
	typedef void( __cdecl * CStreaming__requestModel )( int modelId, int a2 );
	( CStreaming__requestModel( REQUEST_MODEL_FUNC ) )( modelID, 2 );
	return true;
}

void loadRequestedModels() {
	typedef void( __cdecl * CStreaming__loadRequestedModels )( int a1 );
	( CStreaming__loadRequestedModels( LOAD_ALL_REQUESTED_MODELS ) )( 0 );
}

void loadModel( eModelIndex modelID ) {
	if ( isModelLoaded( modelID ) ) return;
	if ( requestModelLoad( modelID ) ) loadRequestedModels();
}

eModelIndex getWeaponModel( int weaponId ) {
	if ( weaponId == 1 )
		return weapon_BrassKnuckles;
	else if ( weaponId >= 2 && weaponId <= 8 )
		return eModelIndex( weaponId + 331 );
	else if ( weaponId == 9 )
		return weapon_Chainsaw;
	else if ( weaponId >= 22 && weaponId <= 29 )
		return eModelIndex( weaponId + 324 );
	else if ( weaponId == 32 )
		return weapon_Tech9;
	else if ( weaponId >= 30 && weaponId <= 31 )
		return eModelIndex( weaponId + 325 );
	else if ( weaponId >= 33 && weaponId <= 38 )
		return eModelIndex( weaponId + 324 );
	else if ( weaponId >= 16 && weaponId <= 18 )
		return eModelIndex( weaponId + 326 );
	else if ( weaponId == 39 )
		return weapon_RemoteExplosives;
	else if ( weaponId >= 41 && weaponId <= 43 )
		return eModelIndex( weaponId + 324 );
	else if ( weaponId >= 10 && weaponId <= 15 )
		return eModelIndex( weaponId + 311 );
	else if ( weaponId >= 44 && weaponId <= 45 )
		return eModelIndex( weaponId + 324 );
	else if ( weaponId == 46 )
		return weapon_Parachute;
	else if ( weaponId == 40 )
		return weapon_Detonator;
	return eModelIndex( -1 );
}

void loadWeaponModel( int weaponId ) {
	loadModel( getWeaponModel( weaponId ) );
}

void loadAllWeaponModels() {
	requestModelLoad( weapon_BrassKnuckles );
	requestModelLoad( weapon_GolfClub );
	requestModelLoad( weapon_Nitestick );
	requestModelLoad( weapon_Knife );
	requestModelLoad( weapon_BaseballBat );
	requestModelLoad( weapon_Shovel );
	requestModelLoad( weapon_PoolCue );
	requestModelLoad( weapon_Katana );
	requestModelLoad( weapon_Chainsaw );
	requestModelLoad( weapon_Pistol );
	requestModelLoad( weapon_SilencedPistol );
	requestModelLoad( weapon_DesertEagle );
	requestModelLoad( weapon_Shotgun );
	requestModelLoad( weapon_SawnOffShotgun );
	requestModelLoad( weapon_SPAZ12 );
	requestModelLoad( weapon_MicroUZI );
	requestModelLoad( weapon_MP5 );
	requestModelLoad( weapon_Tech9 );
	requestModelLoad( weapon_AK47 );
	requestModelLoad( weapon_M4 );
	requestModelLoad( weapon_CountryRifle );
	requestModelLoad( weapon_SniperRifle );
	requestModelLoad( weapon_RocketLauncher );
	requestModelLoad( weapon_HeatSeekingRPG );
	requestModelLoad( weapon_FlameThrower );
	requestModelLoad( weapon_Minigun );
	requestModelLoad( weapon_Grenade );
	requestModelLoad( weapon_Teargas );
	requestModelLoad( weapon_MolotovCocktail );
	requestModelLoad( weapon_RemoteExplosives );
	requestModelLoad( weapon_SprayCan );
	requestModelLoad( weapon_FireExtinguisher );
	requestModelLoad( weapon_Camera );
	requestModelLoad( weapon_Dildo1 );
	requestModelLoad( weapon_Dildo2 );
	requestModelLoad( weapon_Vibe1 );
	requestModelLoad( weapon_Vibe2 );
	requestModelLoad( weapon_Flowers );
	requestModelLoad( weapon_Cane );
	requestModelLoad( weapon_NVGoggles );
	requestModelLoad( weapon_IRGoggles );
	requestModelLoad( weapon_Parachute );
	requestModelLoad( weapon_Detonator );
	loadRequestedModels();
}

RwV2D WindowScreenToGameScreen( float X, float Y ) {
	return { ( 640.0f / SCREEN_X ) * X, ( 448.0f / SCREEN_Y ) * Y };
}

RwV2D GameScreenToWindowScreen( float X, float Y ) {
	return { ( SCREEN_X / 640.0f ) * X, ( SCREEN_Y / 448.0f ) * Y };
}

RwV2D ConvertGlobalXYZToWindowScreenXY( RwV3D world ) {
	typedef bool( __cdecl * CWorld__ConvertGlobalXYZToScreenXY )( RwV3D * world, RwV3D * screen, float *mulX,
																  float *mulY, bool unk, bool unk2 );
	RwV3D screen;
	float mulX, mulY;
	if ( !( CWorld__ConvertGlobalXYZToScreenXY( CONVERT_WORLD_TO_SCREEN_POS_FUNC ) )( &world, &screen, &mulX, &mulY,
																					  false, false ) )
		return { -1.0f * SCREEN_X, -1.0f * SCREEN_Y };
	return { screen.fX, screen.fY };
}

RwV2D ConvertGlobalXYZToGameScreenXY( RwV3D world ) {
	RwV2D pos = ConvertGlobalXYZToWindowScreenXY( world );
	if ( pos == RwV2D{ -1.0f * SCREEN_X, -1.0f * SCREEN_Y } ) return { -640.0f, -448.0f };
	return WindowScreenToGameScreen( pos.fX, pos.fY );
}

const char *GetFrameNodeName( RwFrame *frame ) {
	typedef const char *( __cdecl * GetFrameNodeName_ )( RwFrame * frame );
	return ( GetFrameNodeName_( GET_FRAME_NAME_FUNC ) )( frame );
}
