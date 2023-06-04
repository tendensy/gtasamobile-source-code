#ifndef CPARTICLEDATA_H
#define CPARTICLEDATA_H

#include "Types.h"

class CParticleData
{
public:
	DWORD prt_blood;
	DWORD prt_boatsplash;
	DWORD prt_bubble;
	DWORD prt_cardebris;
	DWORD prt_collisionsmoke;
	DWORD prt_gunshell;
	DWORD prt_sand;
	DWORD prt_sand2;
	DWORD prt_smoke_huge;
	DWORD prt_smokeII_3_expand;
	DWORD prt_spark;
	DWORD prt_spark_2;
	DWORD prt_splash;
	DWORD prt_wake;
	DWORD prt_watersplash;
	DWORD prt_wheeldirt;
	DWORD prt_glass;
};

#define POOL_CPARTICLE_DATA 0xA9AE00;

#endif // CPARTICLEDATA_H
