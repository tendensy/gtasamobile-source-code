#ifndef CWEAPON_H
#define CWEAPON_H

#include <string>

class CWeapon {
public:
	int		weaponType;
	float	targetRange;
	float	weaponRange;
	int		dwModelId;
	int		dwModelId2;
	int		nSlot;
	int		hexFlags;
	int		_animStyle;
	__int16 ammoClip;
	int		fireOffsetX;
	int		fireOffsetY;
	int		fireOffsetZ;
	int		_skillLevel;
	int		reqStatLevel;
	float	fAccuracy;
	float	moveSpeed;
	float	animLoopStart;
	float	animLoopEnd;
	float	animLoopFire;
	float	animLoop2Start;
	float	animLoop2End;
	float	animLoop2Fire;
	float	breakoutTime;
	float	speed;
	float	radius;
	float	lifespan;
	float	spread;
	int		_animStyle2;

	static const std::string_view getName( int id );
	static int					  getId( const std::string_view &name );

	static CWeapon *getWeapon( uint8_t id, uint8_t skill = 0 );
};

#endif // CWEAPON_H
