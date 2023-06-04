#ifndef C3DMARKERS_H
#define C3DMARKERS_H

#include "Types.h"

struct C3dMarker {
	CMatrix			   matrix;
	struct RpAtomic *  m_pAtomic;
	struct RpMaterial *m_pMaterial;
	unsigned __int16   m_nType;
	char			   m_bIsUsed;
	char			   m_bMustBeRenderedThisFrame;
	int				   m_nIdentifier;
	RwRGBA			   m_colour;
	__int16			   m_nPulsePeriod;
	__int16			   m_nRotateRate;
	int				   m_nStartTime;
	float			   m_fPulseFraction;
	float			   m_fStdSize;
	float			   m_fSize;
	float			   m_fBrightness;
	float			   m_fCameraRange;
	CVector			   m_vecNormal;
	__int16			   m_nLastMapReadX;
	__int16			   m_nLastMapReadY;
	float			   m_fLastMapReadResultZ;
	float			   m_fRoofHeight;
	CVector			   m_vecLastPosition;
	int				   m_nOnScreenTestTime;

	static C3dMarker *pool();
};

struct CCheckpoint {
	__int16 m_nType;
	char	m_bIsUsed;
	char	m_rotFlag;
	int		m_nIdentifier;
	RwRGBA	rwColour;
	__int16 m_nPulsePeriod;
	__int16 m_nRotateRate;
	RwV3D	m_pos;
	RwV3D	m_pointDir;
	float	m_fPulseFraction;
	float	m_fSize;
	float	m_fCameraRange;
	float	m_multiSize;

	static CCheckpoint *pool();
};

#endif // C3DMARKERS_H
