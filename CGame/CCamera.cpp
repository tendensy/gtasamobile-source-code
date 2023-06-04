#include "CCamera.h"
CU IS_SPHERE_VISIBLE_FUNC = 0x420D40;
CU FADE_FUNC			  = 0x50AC20;
CU F3PCTV_FUNC			  = 0x514970;
CU SHAKE_FUNC			  = 0x50A970;

bool CCamera::isSphereVisible( RwV3D pos, float range ) {
	typedef bool( __thiscall * CCamera__isSphereVisible )( CCamera * _this, RwV3D * pos, float radius );
	return ( CCamera__isSphereVisible( IS_SPHERE_VISIBLE_FUNC ) )( this, &pos, range );
}

RwV3D CCamera::getPosition() /* Cams[0].Source */ {
	return *(RwV3D *)( 0x00B6F338 );
}

RwV3D CCamera::getRotation() {
	return *(RwV3D *)( 0x00B6F32C );
}

CVector2D CCamera::getTarget() {
	return { *(float *)0x00B6F258, *(float *)0x00B6F248 };
}

void CCamera::setTarget( CVector2D vec ) {
	*(float *)0x00B6F258 = vec.fX;
	*(float *)0x00B6F248 = vec.fY;
}

int CCamera::fade( float diraction, uint16_t inOut ) {
	typedef int( __thiscall * CCamera__fade )( CCamera * _this, float d, uint16_t io );
	return ( CCamera__fade( FADE_FUNC ) )( this, diraction, inOut );
}

void CCamera::Find3rdPersonCamTargetVector( float dist, float posX, float posY, float posZ, const RwV3D &unkVec,
											RwV3D &output ) {
	typedef void( __thiscall * CCamera__Find3rdPersonCamTargetVector )(
		CCamera * _this, float dist, float posX, float posY, float posZ, const RwV3D &unkVec, RwV3D &output );
	return ( CCamera__Find3rdPersonCamTargetVector( F3PCTV_FUNC ) )( this, dist, posX, posY, posZ, unkVec, output );
}

void CCamera::Find3rdPersonCamTargetVector( float dist, const RwV3D &pos, const RwV3D &unkVec, RwV3D &output ) {
	Find3rdPersonCamTargetVector( dist, pos.fX, pos.fY, pos.fZ, unkVec, output );
}

RwV3D CCamera::Find3rdPersonCamTargetVector( float dist, const RwV3D &pos ) {
	RwV3D unk{ 0, 0, 0 }, output{ 0, 0, 0 };
	CCamera::TheCamera()->Find3rdPersonCamTargetVector( dist, pos, unk, output );
	return output;
}

void CCamera::setShake( float stretch ) {
	typedef void( __thiscall * CCamera__CamShakeNoPos )( CCamera * _this, float d );
	return ( CCamera__CamShakeNoPos( SHAKE_FUNC ) )( this, stretch );
}

CCamera *CCamera::TheCamera() {
	return LOCAL_CAMERA;
}
