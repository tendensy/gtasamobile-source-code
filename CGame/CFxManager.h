#ifndef CFXMANAGER_H
#define CFXMANAGER_H

#include "Types.h"

#pragma pack( push, 8 )
struct CFxMemoryPool {
	int ptr;
	int size;
	int position;
};

struct CFxManager {
	List_c		  pFxSystems;
	List_c		  field_C;
	int			  field_18;
	List_c		  field_1C;
	int			  txdIndex;
	int			  field_2C;
	int			  field_30;
	int			  field_34;
	int			  field_38;
	int			  field_3C;
	int			  field_40;
	int			  field_44;
	int			  field_48;
	int			  field_4C;
	int			  field_50;
	int			  field_54;
	int			  field_58;
	int			  field_5C;
	int			  field_60;
	int			  field_64;
	int			  field_68;
	int			  field_6C;
	int			  field_70;
	int			  field_74;
	int			  field_78;
	int			  field_7C;
	int			  field_80;
	int			  field_84;
	int			  currentMatrix;
	int			  matrices[8];
	CFxMemoryPool m_memoryPool;

	static CFxManager *Instance();

	struct CFxSystem *CreateFxSystem( char *name, RwV3D *point, RwMatrix *mat, int flag );
};

struct CFxSystem {
	ListItem_c		 baseclass_0;
	void *			 m_pBlueprint;
	struct RwMatrix *m_pParentMatrix;
	char			 gap10[64];
	unsigned __int8	 m_nPlayStatus;
	unsigned __int8	 m_nKillStatus;
	unsigned __int8	 m_bConstTimeSet;
	char			 field_53;
	int				 field_54;
	float			 m_fCameraDistance;
	unsigned __int16 m_nConstTime;
	unsigned __int16 m_nRateMult;
	unsigned __int16 m_nTimeMult;
	unsigned __int8	 m_nFlags;
	char			 field_63;
	float			 fUnkRandom;
	CVector			 m_vecVelAdd;
	void *			 m_pBounding;
	void **			 m_pPrimsPtrList;
	char			 m_fireAudio[136];

	void Play();
	void Stop();
	void PlayAndKill();
	void Kill();
	void AttachToBone( class CPed *ped, int boneId );
};

enum FxQuality_e : __int32 {
	FXQUALITY_LOW		= 0x0,
	FXQUALITY_MEDIUM	= 0x1,
	FXQUALITY_HIGH		= 0x2,
	FXQUALITY_VERY_HIGH = 0x3,
};


struct CFx {
	CFxSystem *		m_pPrtBlood;
	CFxSystem *		m_pPrtBoatsplash;
	CFxSystem *		m_pPrtBubble;
	CFxSystem *		m_pPrtCardebris;
	CFxSystem *		m_pPrtCollisionsmoke;
	CFxSystem *		m_pPrtGunshell;
	CFxSystem *		m_pPrtSand;
	CFxSystem *		m_pPrtSand2;
	CFxSystem *		m_pPrtSmoke_huge;
	CFxSystem *		m_pPrtSmokeII3expand;
	CFxSystem *		m_pPrtSpark;
	CFxSystem *		m_pPrtSpark2;
	CFxSystem *		m_pPrtSplash;
	CFxSystem *		m_pPrtWake;
	CFxSystem *		m_pPrtWatersplash;
	CFxSystem *		m_pPrtWheeldirt;
	CFxSystem *		m_pPrtGlass;
	unsigned int	m_nBloodPoolsCount;
	FxQuality_e		m_fxQuality;
	unsigned int	m_nVerticesCount2;
	unsigned int	m_nVerticesCount;
	unsigned int	m_nTransformRenderFlags;
	class RwRaster *m_pRasterToRender;
	RwMatrix *		m_pTransformLTM;
	void *			m_pVerts;

	static CFx *Instance();
};
#pragma pack( pop )


#endif // CFXMANAGER_H
