#ifndef CMENUMANAGER_H
#define CMENUMANAGER_H

#include "Types.h"

#pragma pack( push, 1 )
struct CEntryData {
	char  action;
	char  description[8];
	char  field_9;
	short targetMenu;
	short cx;
	short cy;
	short align;
};
struct CMenuItem {
	char	   name[8];
	char	   field_8;
	char	   field_9;
	CEntryData entryList[12];
};
#pragma pack( pop )

struct CMenuManager {
	char		  field_0;
	char		  field_1[3];
	float		  m_fStatsScrollSpeed;
	char		  field_8;
	char		  field_9[23];
	char		  field_20;
	bool		  m_bHudOn;
	char		  field_22[2];
	int			  m_nRadarMode;
	char		  field_28[4];
	int			  m_nTargetBlipIndex;
	char		  field_30;
	char		  field_31;
	bool		  m_bDontDrawFrontEnd;
	bool		  m_bActivateMenuNextFrame;
	bool		  m_bMenuAccessWidescreen;
	char		  field_35;
	char		  field_36[2];
	int			  field_38;
	int			  m_nBrightness;
	float		  m_fDrawDistance;
	bool		  m_bShowSubtitles;
	char		  field_45[4];
	char		  hideGangZones_;
	bool		  m_bMapLegend;
	bool		  m_bWidescreenOn;
	bool		  m_bFrameLimiterOn;
	bool		  m_bRadioAutoSelect;
	char		  field_4E;
	char		  m_nSfxVolume;
	char		  m_nRadioVolume;
	bool		  m_bRadioEq;
	char		  m_nRadioStation;
	char		  field_53;
	int			  m_nSelectedMenuItem;
	char		  field_58;
	char		  drawRadarOrMap;
	char		  field_5A;
	char		  field_5B;
	bool		  m_bMenuActive;
	char		  doGameReload;
	char		  field_5E;
	char		  isSaveDone;
	bool		  m_bLoadingData;
	char		  field_61[3];
	float		  m_fMapZoom; // out: 5779A8/7,5779C7/21; in: 577679/7,577698/21; max: 5776C8/1100; min: 5779F7/300
	float		  m_fMapBaseX;
	float		  m_fMapBaseY;
	CVector2D	  m_vMousePos;
	bool		  m_bMapFromZones;
	char		  field_79[3];
	int			  titleLanguage;
	int			  textLanguage;
	char		  m_nLanguage;
	char		  m_nPreviousLanguage;
	char		  field_86[2];
	int			  field_88;
	bool		  m_bLanguageChanged;
	char		  field_8D[3];
	int			  field_90;
	int			  field_94;
	char *		  m_pJPegBuffer;
	char		  field_9C[16];
	int			  field_AC;
	char		  m_nRadioMode;
	char		  invertPadX1;
	char		  invertPadY1;
	char		  invertPadX2;
	char		  invertPadY2;
	char		  swapPadAxis1;
	char		  swapPadAxis2;
	char		  bIsCarControlPage;
	bool		  m_bDrawMouse;
	char		  field_B9[3];
	int			  m_nMousePosLeft;
	int			  m_nMousePosTop;
	bool		  m_bMipMapping;
	bool		  m_bTracksAutoScan;
	short		  field_C6;
	int			  m_nAppliedAntiAliasingLevel;
	int			  m_nAntiAliasingLevel;
	char		  m_nController;
	char		  field_D1[3];
	int			  m_nAppliedResolution;
	int			  m_nResolution;
	int			  field_DC;
	int			  mousePosLeftA;
	int			  mousePosTopA;
	bool		  m_bSavePhotos;
	bool		  m_bMainMenuSwitch;
	char		  m_nPlayerNumber;
	char		  field_EB;
	int			  field_EC;
	int			  field_F0;
	char		  field_F4;
	char		  field_F5[3];
	CSprite2d	  m_apTextures[25];
	bool		  m_bTexturesLoaded;
	unsigned char m_nCurrentMenuPage;
	char		  field_15E;
	unsigned char m_bSelectedSaveGame;
	char		  field_160;
	char		  field_161;
	char		  m_szMpackName[8];
	char		  field_16A[6486];
	int			  field_1AC0;
	int			  field_1AC4;
	int			  field_1AC8;
	int			  field_1ACC;
	int			  field_1AD0;
	int			  field_1AD4;
	int			  field_1AD8;
	short		  field_1ADC;
	bool		  m_bChangeVideoMode;
	char		  field_1ADF;
	int			  field_1AE0;
	int			  field_1AE4;
	char		  field_1AE8;
	char		  field_1AE9;
	char		  field_1AEA;
	bool		  m_bScanningUserTracks;
	int			  field_1AEC;
	char		  field_1AF0;
	char		  field_1AF1;
	char		  field_1AF2;
	char		  field_1AF3;
	int			  field_1AF4;
	int			  field_1AF8;
	int			  field_1AFC;
	int			  field_1B00;
	int			  field_1B04;
	char		  field_1B08;
	char		  field_1B09;
	char		  field_1B0A;
	char		  field_1B0B;
	int			  field_1B0C;
	char		  field_1B10;
	char		  field_1B11;
	char		  field_1B12;
	char		  field_1B13;
	char		  field_1B14;
	char		  field_1B15;
	char		  field_1B16;
	char		  field_1B17;
	int			  EventToDo;
	int			  field_1B1C;
	unsigned char m_nTexturesRound;
	unsigned char m_nNumberOfMenuOptions;
	short		  field_1B22;
	int			  field_1B24;
	char		  field_1B28;
	char		  field_1B29;
	short		  field_1B2A;
	int			  field_1B2C;
	int			  field_1B30;
	short		  field_1B34;
	short		  field_1B36;
	int			  field_1B38;
	char		  field_1B3C;
	char		  field_1B3D;
	char		  field_1B3E;
	char		  field_1B3F;
	int			  field_1B40;
	char		  field_1B44;
	char		  field_1B45;
	short		  field_1B46;
	int			  field_1B48;
	int			  field_1B4C;
	char		  m_nBackgroundSprite;
	char		  field_1B51;
	short		  field_1B52;
	int			  field_1B54;
	int			  field_1B58;
	char		  field_1B5C;
	char		  field_1B5D;
	short		  field_1B5E;
	int			  field_1B60;
	int			  field_1B64;
	int			  field_1B68;
	int			  field_1B6C;
	int			  field_1B70;
	int			  field_1B74;
};

namespace MenuManager {
	CMenuItem *	  items();
	CMenuManager *frontend();
}; // namespace MenuManager

#endif // CMENUMANAGER_H