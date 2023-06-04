#ifndef CHANDLINGDATAMGR_H
#define CHANDLINGDATAMGR_H

#include "../Types.h"

#pragma pack( push, 4 )
struct TransmissionGear {
	float fGearRatio;
	float field_4;
	float field_8;
};
struct CTransmissionData {
	TransmissionGear gears[6];
	char			 nDriveType;
	char			 nEngineType;
	char			 nNumberOfGears;
	char			 field_4B;
	int				 flags;
	float			 fEngineAcceleration;
	float			 fEngineInertia;
	float			 fMaxVelocity;
	float			 field_5C;
	float			 fMinGearVelocity;
	int				 fCurrentSpeed;
};
struct tHandlingData {
	int				  index;
	float			  fMass;
	float			  fInvMass;
	float			  fTurnMass;
	float			  fDragMult;
	RwV3D			  centreOfMass;
	char			  nPercentSubmerged;
	char			  field_21;
	char			  field_22;
	char			  field_23;
	float			  fBuoyancyConstant;
	float			  fTractionMultiplier;
	CTransmissionData transmissionData;
	float			  fBrakeDeceleration;
	float			  fBrakeBias;
	char			  bABS;
	char			  field_9D;
	char			  field_9E;
	char			  field_9F;
	float			  fSteeringLock;
	float			  fTractionLoss;
	float			  fTractionBias;
	float			  fSuspensionForceLevel;
	float			  fSuspensionDampingLevel;
	float			  fSuspensionHighSpdComDamp;
	float			  fSuspensionUpperLimit;
	float			  fSuspensionLowerLimit;
	float			  fSuspensionBiasBetweenFrontAndRear;
	float			  fSuspensionAntiDiveMultiplier;
	float			  fCollisionDamageMultiplier;
	int				  modelFlags;
	int				  handlingFlags;
	float			  fSeatOffsetDistance;
	int				  nMonetaryValue;
	char			  frontLight;
	char			  rearLight;
	char			  animGroup;
	char			  field_DF;
};
struct CHandlingFlying {
	int	  index;
	float thrust;
	float thrustFallOff;
	float yaw;
	float yawStab;
	float sideSlip;
	float roll;
	float rollStab;
	float pitch;
	float pitchStab;
	float formLift;
	float attackLift;
	float gearUpR;
	float gearDownL;
	float windMult;
	float moveRes;
	RwV3D turnRes;
	RwV3D speedRes;
};
struct CHandlingBoat {
	int	  index;
	float thrustY;
	float thrustZ;
	float thrustAppZ;
	float aqPlaneForce;
	float aqPlaneLimit;
	float aqPlaneOffset;
	float waveAudioMult;
	float look_L_R_BehindCamHeight;
	RwV3D moveRes;
	RwV3D turnRes;
};
struct CHandlingBike {
	int	  index;
	float leanFwdCOM;
	float leanFwdForce;
	float leanBakCOM;
	float leanBakForce;
	float maxLean;
	float fullAnimLean;
	float desLean;
	float speedSteer;
	float slipSteer;
	float noPlayerCOMz;
	float wheelieAng;
	float stoppieAng;
	float wheelieSteer;
	float wheelieStabMult;
	float stoppieStabMult;
};

class CHandlingDataMgr {
public:
	float			field_0;
	float			field_4;
	float			field_8;
	float			field_C;
	float			field_10;
	tHandlingData	vehicleHandling[210];
	CHandlingBike	bikeHandling[13];
	CHandlingFlying flyingHandling[24];
	CHandlingBoat	boatHandling[12];

	CHandlingDataMgr *get();
};
#pragma pack( pop )

#endif // CHANDLINGDATAMGR_H
