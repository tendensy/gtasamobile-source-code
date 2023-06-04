#ifndef CCAM_H
#define CCAM_H

#include "CEntity.h"
#include "CVehicle.h"
#include "Types.h"

#pragma pack( push, 8 )
struct CCam_obj1 {
	int	  field_0;
	RwV3D field_4;
	int	  field_10;
	int	  field_14;
	RwV3D field_18;
	int	  field_24;
	int	  field_28;
	int	  field_2C;
	int	  field_30;
	int	  field_34;
	int	  field_38;
	int	  field_3C;
	int	  field_40;
	int	  field_44;
	int	  field_48;
	int	  field_4C;
	int	  field_50;
	int	  field_54;
	int	  field_58;
	int	  field_5C;
	int	  field_60;
	int	  field_64;
	int	  field_68;
	int	  field_6C;
	int	  field_70;
	int	  field_74;
	char  field_78;
	char  field_79;
	char  field_7A;
	char  field_7B;
	int	  field_7C;
	int	  field_80;
	int	  field_84;
	int	  field_88;
	int	  field_8C;
	int	  field_90;
	int	  field_94;
};
#pragma pack( pop )


#pragma pack( push, 8 )
struct CCam {
	char			bBelowMinDist;
	char			bBehindPlayerDesired;
	char			m_bCamLookingAtVector;
	char			m_bCollisionChecksOn;
	char			m_bFixingBeta;
	char			m_bTheHeightFixerVehicleIsATrain;
	char			LookBehindCamWasInFront;
	char			LookingBehind;
	char			LookingLeft;
	char			LookingRight;
	char			ResetStatics;
	char			Rotating;
	__int16			mode;
	char			gap_e[2];
	unsigned int	m_uiFinishTime;
	int				m_iDoCollisionChecksOnFrameNum;
	int				m_iDoCollisionCheckEveryNumOfFrames;
	int				m_iFrameNumWereAt;
	int				m_iRunningVectorArrayPos;
	int				m_iRunningVectorCounter;
	int				DirectionWasLooking;
	float			f_max_role_angle;
	float			f_Roll;
	float			f_rollSpeed;
	int				m_fSyphonModeTargetZOffSet;
	int				m_fAmountFractionObscured;
	int				m_fAlphaSpeedOverOneFrame;
	int				m_fBetaSpeedOverOneFrame;
	int				m_fBufferedTargetBeta;
	int				m_fBufferedTargetOrientation;
	int				m_fBufferedTargetOrientationSpeed;
	int				m_fCamBufferedHeight;
	int				m_fCamBufferedHeightSpeed;
	float			m_fCloseInPedHeightOffset;
	float			m_fCloseInPedHeightOffsetSpeed;
	int				m_fCloseInCarHeightOffset;
	int				m_fCloseInCarHeightOffsetSpeed;
	int				m_fDimensionOfHighestNearCar;
	float			m_fDistanceBeforeChanges;
	float			m_fFovSpeedOverOneFrame;
	float			m_fMinDistAwayFromCamWhenInterPolating;
	float			m_fPedBetweenCameraHeightOffset;
	float			m_fPlayerInFrontSyphonAngleOffSet;
	float			m_fRadiusForDead;
	float			m_fRealGroundDist;
	float			m_fTargetBeta;
	float			m_fTimeElapsedFloat;
	float			m_fTilt;
	float			m_fTiltSpeed;
	float			m_fTransitionBeta;
	float			m_fTrueBeta;
	float			m_fTrueAlpha;
	float			m_fInitialPlayerOrientation;
	float			Alpha; // targett Y
	float			AlphaSpeed;
	float			FOV;
	float			FOVSpeed;
	float			Beta; // target X
	float			BetaSpeed;
	float			Distance;
	float			DistanceSpeed;
	float			CA_MIN_DISTANCE;
	float			CA_MAX_DISTANCE;
	float			SpeedVar;
	float			m_fCameraHeightMultiplier;
	float			m_fTargetZoomGroundOne;
	float			m_fTargetZoomGroundTwo;
	float			m_fTargetZoomGroundThree;
	float			m_fTargetZoomOneZExtra;
	float			m_fTargetZoomTwoZExtra;
	float			m_fTargetZoomTwoInteriorZExtra;
	float			m_fTargetZoomThreeZExtra;
	float			m_fTargetZoomZCloseIn;
	float			m_fMinRealGroundDist;
	float			m_fTargetCloseInDist;
	float			Beta_Targeting;
	float			X_Targetting;
	float			Y_Targetting;
	int				CarWeAreFocussingOn;
	float			CarWeAreFocussingOnI;
	float			m_fCamBumpedHorz;
	float			m_fCamBumpedVert;
	int				m_nCamBumpedTime;
	RwV3D			m_cvecSourceSpeedOverOneFrame;
	RwV3D			m_cvecTargetSpeedOverOneFrame;
	RwV3D			m_cvecUpOverOneFrame;
	RwV3D			m_cvecTargetCoorsForFudgeInter;
	RwV3D			m_cvecCamFixedModeVector;
	RwV3D			m_cvecCamFixedModeSource;
	RwV3D			m_cvecCamFixedModeUpOffSet;
	RwV3D			m_vecLastAboveWaterCamPosition;
	RwV3D			m_vecBufferedPlayerBodyOffset;
	RwV3D			Front;
	RwV3D			Source; // right?
	RwV3D			SourceBeforeLookBehind;
	RwV3D			Up;
	RwV3D			m_arrPreviousVectors[2];
	RwV3D			m_aTargetHistoryPos[4];
	int				m_nTargetHistoryTime[4];
	int				m_nCurrentHistoryPoints;
	CEntity *		CamTargetEntity;
	float			m_fCameraDistance;
	float			m_fIdealAlpha;
	float			m_fPlayerVelocity;
	class CVehicle *m_pLastCarEntered;
	CPed *			m_pLastPedLookedAt;
	char			m_bFirstPersonRunAboutActive;
	char			_pad1;
	__int16			_pad2;
};
#pragma pack( pop )


#endif // CCAM_H
