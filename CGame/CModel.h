#ifndef CMODEL_H
#define CMODEL_H

#include "Types.h"

class CModel {
public:
	virtual ~CModel()												= 0;
	virtual int						   AsAtomicModelInfoPtr()		= 0;
	virtual void *					   AsDamageAtomicModelInfoPtr() = 0;
	virtual class CLodAtomicModelInfo *AsLodAtomicModelInfoPtr()	= 0;
	virtual int						   GetModelType()				= 0;
	virtual int						   GetTimeInfo()				= 0;
	virtual void					   Init()						= 0;
	virtual void					   Shutdown()					= 0;
	virtual int						   DeleteRwObject()				= 0;
	virtual int						   GetRwModelType()				= 0;
	virtual int						   CreateInstance_()			= 0;
	virtual class RpAtomic *		   CreateInstance()				= 0;
	virtual void					   SetAnimFile( char * )		= 0;
	virtual void					   ConvertAnimFileIndex()		= 0;
	virtual int						   GetAnimFileIndex()			= 0;

	int				 ulHashKey;			   // 4
	short			 usNumberOfRefs;	   // 8
	short			 usTextureDictionary;  // 10
	char			 ucAlpha;			   // 12
	char			 ucNumOf2DEffects;	   // 13
	short			 field_E;			   // 14
	char			 ucDynamicIndex;	   // 16
	char			 field_11;			   // 17
	short			 wFlags;			   // 18
	class CColModel *pColModel;			   // 20
	float			 fLodDistanceUnscaled; // 24
	class RwObject * pRwObject;			   // 28
	int				 ifp;				   // 32
};

class CModelVehicle : public CModel {
public:
	void *						customPlateMaterial; // 36
	char						customPlateText[8];	 // 40
	char						field_30;			 // 48
	char						CustomPlateDesign;	 // 49
	char						GameName[8];		 // 50
	short						field_3A;			 // 58
	int							VehicleType;		 // 60
	float						WheelScale1;		 // 64
	float						WheelScale2;		 // 68
	short						WheelModelID;		 // 72
	short						VehicleHandlingID;	 // 74
	char						NumOfDoors;			 // 76
	char						VehicleList;		 // 77
	char						VehicleFlags;		 // 78
	char						WheelUpgradeClass;	 // 79
	char						NumTimesUsed;		 // 80
	short						VehicleFreq;		 // 82
	int							ComponentRules;		 // 84
	float						SteerAngle;			 // 88
	struct CModelVehicleStruct *vehicle_struct;		 // 92
	int							field_60;
	int							field_64;
	int							field_68;
	int							field_6C;
	int							field_70;
	int							field_74;
	int							field_78;
	int							field_7C;
	int							field_80;
	int							field_84;
	int							field_88;
	int							field_8C;
	int							field_90;
	int							field_94;
	int							field_98;
	int							field_9C;
	int							field_A0;
	int							field_A4;
	int							field_A8;
	int							field_AC;
	int							field_B0;
	int							VehicleUpgradePositions[95];
	void *						m_pEditableMaterials[32];
	char						vehiclePrimaryColours[8];
	char						vehicleSecondaryColours[8];
	char						vehicleTertiaryColours[8];
	char						vehicleQuaternaryColours[8];
	unsigned __int8				NumPossibleColors;
	char						lastColourChoice;
	char						m_bPrimaryColour;
	char						m_bSecondaryColour;
	char						m_bTertiaryColour;
	char						m_bQuaternaryColour;
	__int16						carMods[18];
	__int16						Paintjobs[5];
	int							m_pAnimBlock;
};

struct UpgradePosnDesc {
	RwV3D m_vPosition;
	struct RtQuat {
		RwV3D imag;
		float ereal;
	} m_qRotation;
	int m_dwParentComponentId;
};

struct CModelVehicleStruct {
	RwV3D			frontLight;					 // 0
	RwV3D			backLight;					 // 12
	RwV3D			frontSecondLight;			 // 24
	RwV3D			backSecondLight;			 // 36
	RwV3D			pedfront;					 // 48
	RwV3D			pedback;					 // 60
	RwV3D			smoke;						 // 72
	RwV3D			engine;						 // 84
	RwV3D			gas;						 // 96
	RwV3D			hookup;						 // 108
	RwV3D			pedarm;						 // 120
	RwV3D			misc[4];					 // 132
	UpgradePosnDesc m_aUpgrades[18];			 // 180
	void *			m_apExtras[6];				 // 756
	char			m_nNumExtras;				 // 780
	int				m_dwMaskComponentsDamagable; // 784
};

#pragma pack( push, 8 )
struct CBaseModelInfo {
	//	CBaseModelInfo_VTBL *__vmt;
	virtual ~CBaseModelInfo()										   = 0;
	virtual class CAtomicModelInfo *	  AsAtomicModelInfoPtr()	   = 0;
	virtual class CDamageAtomicModelInfo *AsDamageAtomicModelInfoPtr() = 0;
	virtual void *						  AsLodAtomicModelInfoPtr()	   = 0;
	virtual int							  GetModelType()			   = 0;
	virtual int							  GetTimeInfo()				   = 0;
	virtual void						  Init()					   = 0;
	virtual void *						  Shutdown()				   = 0;
	virtual int							  DeleteRwObject()			   = 0;
	virtual int							  GetRwModelType()			   = 0;
	virtual int							  CreateInstance_()			   = 0;
	virtual void *						  CreateInstance()			   = 0;
	virtual void						  SetAnimFile( char * )		   = 0;
	virtual void						  ConvertAnimFileIndex()	   = 0;
	virtual int							  GetAnimFileIndex( DWORD )	   = 0;

	unsigned long
				   ulHashKey; // +4   Generated by CKeyGen::GetUppercaseKey(char const *) called by CBaseModelInfo::SetModelName(char const *)
	unsigned short usNumberOfRefs : 16;		 // +8
	unsigned short usTextureDictionary : 16; // +10
	unsigned char  ucAlpha : 8;				 // +12

	unsigned char  ucNumOf2DEffects : 8; // +13
	unsigned short usUnknown : 16;		 // +14     Something with 2d effects

	unsigned short usDynamicIndex : 16; // +16

	// Flags used by CBaseModelInfo
	unsigned char bDoWeOwnTheColModel : 1; // +18
	unsigned char bAlphaTransparency : 1;
	unsigned char bIsLod : 1;
	unsigned char bDontCastShadowsOn : 1;
	unsigned char bDontWriteZBuffer : 1;
	unsigned char bDrawAdditive : 1;
	unsigned char bDrawLast : 1;
	unsigned char bHasBeenPreRendered : 1;

	unsigned char bIsRoad : 1; // +19 // does not used
	unsigned char dwUnknownFlag26 : 1;
	unsigned char dwUnknownFlag27 : 1;
	unsigned char bSwaysInWind : 1;
	unsigned char bCollisionWasStreamedWithModel : 1; // CClumpModelInfo::SetCollisionWasStreamedWithModel(unsigned int)
	unsigned char bDontCollideWithFlyer : 1;		  // CAtomicModelInfo::SetDontCollideWithFlyer(unsigned int)
	unsigned char bHasComplexHierarchy : 1;			  // CClumpModelInfo::SetHasComplexHierarchy(unsigned int)
	unsigned char bWetRoadReflection : 1;			  // CAtomicModelInfo::SetWetRoadReflection(unsigned int)

	CColModel *pColModel; // +20      CColModel: public CBoundingBox

	float	  fLodDistanceUnscaled; // +24      Scaled is this value multiplied with flt_B6F118
	RwObject *pRwObject;			// +28

	// CWeaponModelInfo:
	// +36 = Weapon info as int

	// CPedModelInfo:
	// +36 = Motion anim group (AssocGroupID, long)
	// +40 = Default ped type (long)
	// +44 = Default ped stats (ePedStats)
	// +48 = Can drive cars (byte)
	// +50 = Ped flags (short)
	// +52 = Hit col model (CColModel*)
	// +56 = First radio station
	// +57 = Second radio station
	// +58 = Race (byte)
	// +60 = Audio ped type (short)
	// +62 = First voice
	// +64 = Last voice
	// +66 = Next voice (short)

	// CVehicleModelInfo:
	// +36 = Custom plate material (RpMaterial*)
	// +49 = Custom plate design (byte)
	// +50 = Pointer to game name (const char*)
	// +60 = Vehicle type (enum, int)
	// +64 = Wheel scale (float). Front/rear?
	// +68 = Wheel scale (float). Front/rear?
	// +72 = Wheel model id
	// +74 = Vehicle handling ID (word)
	// +76 = Number of doors (byte)
	// +77 = Vehicle list (byte)
	// +78 = Vehicle flags (byte)
	// +79 = Wheel upgrade class (byte)
	// +80 = Number of times used (byte)
	// +82 = Vehicle freq (short)
	// +84 = Component rules mask (long)
	// +88 = Steer angle
	// +92 = Pointer to some class containing back seat position @ +60
	// +180 = Vehicle upgrade position descriptors array (32 bytes each)
	// +720 = Number of possible colors
	// +726 = Word array as referenced in CVehicleModelInfo::GetVehicleUpgrade(int)
	// +762 = Array of WORD containing something relative to paintjobs
	// +772 = Anim file index

	static CBaseModelInfo *getModel( int id );
};

struct CClumpModelInfo : public CBaseModelInfo {
	int _ifp;
};

struct CVehicleModelInfo : public CClumpModelInfo {
	void *						CustomPlateMaterial;
	char						CustomPlateText[8];
	char						field_30;
	char						CustomPlateDesign;
	char						GameName[8];
	__int16						field_3A;
	int							VehicleType;
	float						WheelScale1;
	float						WheelScale2;
	__int16						WheelModelID;
	__int16						VehicleHandlingID;
	char						NumOfDoors;
	char						VehicleList;
	char						VehicleFlags;
	char						WheelUpgradeClass;
	char						NumTimesUsed;
	__int16						VehicleFreq;
	int							ComponentRules;
	float						SteerAngle;
	struct CModelVehicleStruct *vehicleStruct;
	int							field_60;
	int							field_64;
	int							field_68;
	int							field_6C;
	int							field_70;
	int							field_74;
	int							field_78;
	int							field_7C;
	int							field_80;
	int							field_84;
	int							field_88;
	int							field_8C;
	int							field_90;
	int							field_94;
	int							field_98;
	int							field_9C;
	int							field_A0;
	int							field_A4;
	int							field_A8;
	int							field_AC;
	int							field_B0;
	int							VehicleUpgradePositions[95];
	void *						m_pEditableMaterials[32];
	char						vehiclePrimaryColours[8];
	char						vehicleSecondaryColours[8];
	char						vehicleTertiaryColours[8];
	char						vehicleQuaternaryColours[8];
	unsigned __int8				NumPossibleColors;
	char						lastColourChoice;
	char						m_bPrimaryColour;
	char						m_bSecondaryColour;
	char						m_bTertiaryColour;
	char						m_bQuaternaryColour;
	__int16						carMods[18];
	__int16						Paintjobs[5];
	int							m_pAnimBlock;
};
#pragma pack( pop )

#endif // CMODEL_H
