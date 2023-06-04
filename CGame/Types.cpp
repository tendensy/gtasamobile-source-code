#include "Types.h"
#define _USE_MATH_DEFINES
#include <cmath>

RwV3D::RwV3D( float X, float Y, float Z ) {
	fX = X;
	fY = Y;
	fZ = Z;
}

RwV3D::RwV3D( const RwV2D &v2d, float Z ) {
	fX = v2d.fX;
	fY = v2d.fY;
	fZ = Z;
}

void RwV3D::clear() {
	fX = 0.0f;
	fY = 0.0f;
	fZ = 0.0f;
}

bool RwV3D::isClear() {
	return fX == 0.0f && fY == 0.0f && fZ == 0.0f;
}

float RwV3D::length() {
	return sqrtf( powf( fX, 2 ) + powf( fY, 2 ) + powf( fZ, 2 ) );
}

float RwV3D::angle() {
	return -atan2( fY, -fX );
}

float RwV3D::angle( const float &X, const float &Y ) {
	float kx = X - fX;
	float ky = Y - fY;

	if ( kx == 0 ) kx = 0.00001f;
	float t = kx / ky;
	if ( t < 0 ) t = -t;

	float a = (float)( 180 * atan( (float)t ) / 3.14159265358979323846 );

	if ( ( kx <= 0 ) && ( ky <= 0 ) )
		a = 180 - a;
	else if ( ( kx >= 0 ) && ( ky >= 0 ) )
		a = 359.99999f - a;
	else if ( ( kx >= 0 ) && ( ky <= 0 ) )
		a = -( 180 - a );

	return ( a * 3.14159265358979323846 ) / 180.0f;
}

float RwV3D::angle( const RwV3D &r ) {
	return angle( r.fX, r.fY );
}

float RwV3D::DotProduct( const CVector *param ) const {
	return fX * param->fX + fY * param->fY + fZ * param->fZ;
}

void RwV3D::CrossProduct( const CVector *param ) {
	float _fX = fX, _fY = fY, _fZ = fZ;
	fX = _fY * param->fZ - param->fY * _fZ;
	fY = _fZ * param->fX - param->fZ * _fX;
	fZ = _fX * param->fY - param->fX * _fY;
}

void RwV3D::normalize() {
	float len = length();
	fX /= len;
	fY /= len;
	fZ /= len;
}

bool RwV3D::isNormalized() {
	return fX >= -1.0f && fX <= 1.0f && fY >= -1.0f && fY <= 1.0f && fZ >= -1.0f && fZ <= 1.0f;
}

RwMatrix::RwMatrix() {
	up	  = { 1.0, 0.0, 0.0 };
	right = { 0.0, 1.0, 0.0 };
	at	  = { 0.0, 0.0, 1.0 };
	pos	  = { 0.0, 0.0, 0.0 };

	flags = 0;
	pad_u = 0.0;
	pad_p = 0.0;
	pad_a = 0.0;
}

RwMatrix::RwMatrix( const RwMatrix &mat ) {
	up	  = mat.up;
	right = mat.right;
	at	  = mat.at;
	pos	  = mat.pos;

	flags = 0;
	pad_u = 0.0;
	pad_p = 0.0;
	pad_a = 0.0;
}

RwMatrix::RwMatrix( Quaternion q ) {
	RwMatrix(); // to be reset
	QuaternionToMatrix( q );
}

void RwMatrix::setQuaternion( const Quaternion &quater ) {
	QuaternionToMatrix( quater );
}

Quaternion RwMatrix::quaternion() {
	long double v13; // st7@1
	long double v14; // st7@3
	long double v15; // st5@5
	float		v16; // st6@5
	float		v17; // st7@5
	long double v18; // st6@7
	Quaternion	result;
	float		v23; // [sp+10h] [bp-20h]@7
	float		v24; // [sp+18h] [bp-18h]@9

	v13 = right.fX + up.fY + at.fZ + 1.0f;
	if ( v13 < 0.0f ) v13 = 0.0f;
	result.fW = (float)sqrt( v13 ) * 0.5f;
	v14		  = right.fX + 1.0 - up.fY - at.fZ;
	if ( v14 < 0.0f ) v14 = 0.0f;
	v17 = (float)sqrt( v14 ) * 0.5f;
	v16 = 1.0f - right.fX;
	v15 = up.fY + v16 - at.fZ;
	if ( v15 < 0.0f ) v15 = 0.0f;
	v23 = (float)sqrt( v15 ) * 0.5f;
	v18 = v16 - up.fY + at.fZ;
	if ( v18 < 0.0f ) v18 = 0.0f;
	v24 = (float)sqrt( v18 ) * 0.5f;
	if ( result.fW < 0.0f ) result.fW = 0.0f;
	if ( v17 < 0.0f ) v17 = 0.0f;
	if ( v23 < 0.0f ) v23 = 0.0f;
	if ( v24 < 0.0f ) v24 = 0.0f;
	result.fX = (float)copysign( v17, at.fY - up.fZ );
	result.fY = (float)copysign( v23, right.fZ - at.fX );
	result.fZ = (float)copysign( v24, up.fX - right.fY );

	return result;
}

void RwMatrix::invert() {
	// Transpose the rotation matrix and negate the position
	RwV3D vOldRight = right, vOldFront = at, vOldUp = up;
	right = RwV3D( vOldRight.fX, vOldFront.fX, vOldUp.fX );
	at	  = RwV3D( vOldRight.fY, vOldFront.fY, vOldUp.fY );
	up	  = RwV3D( vOldRight.fZ, vOldFront.fZ, vOldUp.fZ );
	pos *= -1.0f;
}

RwMatrix RwMatrix::rotate( const RwV3D *param, const float &theta ) {
	// Rotate the rotation matrix
	double	 sin_t = sinf( theta ), cos_t = cosf( theta );
	RwMatrix mRotateMult;
	// rotate X
	mRotateMult.right.fX = (double)cos_t + ( 1.0f - cos_t ) * param->fX * param->fX;
	mRotateMult.right.fY = (double)( 1.0f - cos_t ) * param->fX * param->fY - sin_t * param->fZ;
	mRotateMult.right.fZ = (double)( 1.0f - cos_t ) * param->fX * param->fZ + sin_t * param->fY;
	// rotate Y
	mRotateMult.at.fX = (double)( 1.0f - cos_t ) * param->fY * param->fX + sin_t * param->fZ;
	mRotateMult.at.fY = (double)cos_t + ( 1.0f - cos_t ) * param->fY * param->fY;
	mRotateMult.at.fZ = (double)( 1.0f - cos_t ) * param->fY * param->fZ - sin_t * param->fX;
	// rotate Z
	mRotateMult.up.fX = (double)( 1.0f - cos_t ) * param->fZ * param->fX - sin_t * param->fY;
	mRotateMult.up.fY = (double)( 1.0f - cos_t ) * param->fZ * param->fY + sin_t * param->fX;
	mRotateMult.up.fZ = (double)cos_t + ( 1.0f - cos_t ) * param->fZ * param->fZ;
	// multiply matrix
	mRotateMult = mRotateMult * ( *this );
	// set vectors
	mRotateMult.pos = pos;
	// return
	return mRotateMult;
}

RwMatrix RwMatrix::rotX( const float &angle ) {
	RwMatrix mat( *this );
	mat.right = { 1.0f, 0.0f, 0.0f };
	mat.up.fX = 0.0f;
	mat.up.fY = cosf( angle );
	mat.up.fZ = sinf( angle );
	mat.at.fX = 0.0f;
	mat.at.fY = -sinf( angle );
	mat.at.fZ = cosf( angle );
	return mat;
}

RwMatrix RwMatrix::rotY( const float &angle ) {
	RwMatrix mat( *this );
	mat.right.fX = cosf( angle );
	mat.right.fY = 0.0f;
	mat.right.fZ = -sinf( angle );
	mat.up		 = { 0.0f, 1.0f, 0.0f };
	mat.at.fX	 = sinf( angle );
	mat.at.fY	 = 0.0f;
	mat.at.fZ	 = cosf( angle );
	return mat;
}

RwMatrix RwMatrix::rotZ( const float &angle ) {
	RwMatrix mat( *this );
	mat.right.fX = cosf( angle );
	mat.right.fY = sinf( angle );
	mat.right.fZ = 0.0f;
	mat.up.fX	 = -sinf( angle );
	mat.up.fY	 = cosf( angle );
	mat.up.fZ	 = 0.0f;
	mat.at		 = { 0.0f, 0.0f, 1.0f };
	return mat;
}

RwV3D RwMatrix::getOffset( RwV3D offset ) {
	CVector offsetVector;
	offsetVector.fX = ( offset.fX * right.fX ) + ( offset.fY * up.fX ) + ( offset.fZ * at.fX );
	offsetVector.fY = ( offset.fX * right.fY ) + ( offset.fY * up.fY ) + ( offset.fZ * at.fY );
	offsetVector.fZ = ( offset.fX * right.fZ ) + ( offset.fY * up.fZ ) + ( offset.fZ * at.fZ );
	return offsetVector;
}

float RwMatrix::getAngleZ() {
	return atan2f( -up.fX, up.fY );
}

void RwMatrix::QuaternionToMatrix( const Quaternion &quater ) {
	float SquarredQuaterW = 0.0f, SquarredQuaterX = 0.0f, SquarredQuaterY = 0.0f, SquarredQuaterZ = 0.0f;

	SquarredQuaterW = quater.fW * quater.fW;
	SquarredQuaterX = quater.fX * quater.fX;
	SquarredQuaterY = quater.fY * quater.fY;
	SquarredQuaterZ = quater.fZ * quater.fZ;
	right.fX		= SquarredQuaterX - SquarredQuaterY - SquarredQuaterZ + SquarredQuaterW;
	up.fY			= SquarredQuaterY - SquarredQuaterX - SquarredQuaterZ + SquarredQuaterW;
	at.fZ			= SquarredQuaterZ - ( SquarredQuaterY + SquarredQuaterX ) + SquarredQuaterW;

	float multXY = quater.fX * quater.fY;
	float multWZ = quater.fW * quater.fZ;
	up.fX		 = multWZ + multXY + multWZ + multXY;
	right.fY	 = multXY - multWZ + multXY - multWZ;

	float multXZ = quater.fX * quater.fZ;
	float multWY = quater.fW * quater.fY;
	at.fX		 = multXZ - multWY + multXZ - multWY;
	right.fZ	 = multWY + multXZ + multWY + multXZ;

	float multYZ = quater.fY * quater.fZ;
	float multWX = quater.fW * quater.fX;
	at.fY		 = multWX + multYZ + multWX + multYZ;
	up.fZ		 = multYZ - multWX + multYZ - multWX;
}

void CMatrix::SyncRwMatrix() {
	if ( haveRwMatrix && rwMatrix ) {
		rwMatrix->right = right;
		rwMatrix->up	= up;
		rwMatrix->at	= at;
		rwMatrix->pos	= pos;
	}
}

void CMatrix::UpdateRwMatrix() {
	if ( haveRwMatrix && rwMatrix ) {
		SyncRwMatrix();
		rwMatrix->flags &= 0xFFFDFFFC;
	}
}

RwV2D::RwV2D( float X, float Y ) {
	fX = X;
	fY = Y;
}

RwV2D::RwV2D( const RwV3D &vec3d ) {
	fX = vec3d.fX;
	fY = vec3d.fY;
}

void RwV2D::clear() {
	fX = 0.0f;
	fY = 0.0f;
}

bool RwV2D::isClear() const {
	return fX == 0.0f && fY == 0.0f;
}

void RwV2D::normalize() {
	float len = length();
	fX /= len;
	fY /= len;
}

void RwV2D::normalizeRect() {
	float len = length();
	if ( len > 1.41421f ) {
		fX /= len * 0.70710f;
		fY /= len * 0.70710f;
	}
	if ( fX > 1.0f )
		fX = 1.0f;
	else if ( fX < -1.0f )
		fX = -1.0f;
	if ( fY > 1.0f )
		fY = 1.0f;
	else if ( fY < -1.0f )
		fY = -1.0f;
}

float RwV2D::length() const {
	return sqrtf( powf( fX, 2 ) + powf( fY, 2 ) );
}

float RwV2D::DotProduct( const CVector *param ) const {
	return fX * param->fX + fY * param->fY;
}

void RwV2D::CrossProduct( const CVector *param ) {
	float _fX = fX, _fY = fY;
	fX = _fY * param->fZ - param->fY;
	fY = param->fX - param->fZ * _fX;
}

std::ostream &operator<<( std::ostream &out, const RwMatrix &mat ) {
	out << "{ " << mat.right << ", " << mat.up << ", " << mat.at << ", " << mat.pos << " }";
	return out;
}

std::ostream &operator<<( std::ostream &out, const RwV3D &vec ) {
	out << "{ " << vec.fX << ", " << vec.fY << ", " << vec.fZ << " }";
	return out;
}

int &RwD3D9DisplayMode::currentId() {
	return *(int *)0xC97C18;
}

RwD3D9DisplayMode *RwD3D9DisplayMode::current() {
	return &modes()[currentId()];
}

RwD3D9DisplayMode *RwD3D9DisplayMode::modes() {
	return *(RwD3D9DisplayMode **)0xC97C48;
}

void RwD3D9DisplayMode::apply( int mode ) {
	typedef void( __cdecl * CSettings__SetCurrentVideoMode )( int mode );
	( CSettings__SetCurrentVideoMode( 0x745C70 ) )( mode );
}

RwCamera *RwCamera::get() {
	return *(RwCamera **)0xC1703C;
}
