#ifndef CBIKE_H
#define CBIKE_H

#include "../CVehicle.h"

class CBike : public CVehicle {
public:
	RwFrame *	  m_aBikeNodes[10];		   // 1440
	bool		  m_bLeanMatrixCalculated; // 1480
	char		  _pad0[3];				   // 1481
	CMatrix		  m_mLeanMatrix;		   // 1484
	unsigned char m_nDamageFlags;		   // 1556
	char		  field_615[27];		   // 1557
	CVector		  field_630;			   // 1584
	void *		  m_pBikeHandlingData;	   // 1596
	CRideAnimData m_rideAnimData;		   // 1600
	unsigned char m_anWheelDamageState[2]; // 1628
	char		  field_65E;
	char		  field_65F;
	CColPoint	  m_anWheelColPoint[4];
	float		  field_710[4];
	float		  field_720[4];
	float		  field_730[4];
	float		  field_740;
	int			  m_anWheelSurfaceType[2];
	char		  field_74C[2];
	char		  field_74E[2];
	float		  m_afWheelRotationX[2];
	float		  m_fWheelSpeed[2];
	float		  field_760;
	float		  field_764;
	float		  field_768;
	float		  field_76C;
	float		  field_770[4];
	float		  field_780[4];
	float		  m_fHeightAboveRoad;
	float		  m_fCarTraction;
	float		  field_798;
	float		  field_79C;
	float		  field_7A0;
	float		  field_7A4;
	short		  field_7A8;
	char		  field_7AA[2];
	int			  field_7AC;
	int			  field_7B0;
	bool		  m_bPedLeftHandFixed;
	bool		  m_bPedRightHandFixed;
	char		  field_7B6[2];
	int			  field_7B8;
	int			  field_7BC;
	CEntity *	  m_apWheelCollisionEntity[4];
	CVector		  m_avTouchPointsLocalSpace[4];
	CEntity *	  m_pDamager;
	unsigned char m_nNumContactWheels;
	unsigned char m_nNumWheelsOnGround;
	char		  field_806;
	char		  field_807;
	int			  field_808;
	unsigned int  m_anWheelState[2]; // enum tWheelState

	virtual int ProcessAI() = 0;

	bool _processFall( float mass, int unused_a3, int unused_a4, int unused_a5, RwV3D *a6 );
	bool processUnderWater();
	int	 placeOnRoadProperly();
};

VALIDATE_SIZE( CBike, 0x814 );

#endif // CBIKE_H
