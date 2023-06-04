#ifndef CSURFACE_H
#define CSURFACE_H

struct CSurfaceType {
	char  tyreGrip;
	char  wetGrip;
	short pad;
	union {
		struct {
			unsigned int sWater : 1;
			unsigned int flag1_1 : 1;
			unsigned int flag1_2 : 1;
			unsigned int flag1_3 : 1;
			unsigned int flag1_4 : 1;
			unsigned int flag1_5 : 1;
			unsigned int flag1_6 : 1;
			unsigned int flag1_7 : 1;

			unsigned int flag1_8 : 1;
			unsigned int flag1_9 : 1;
			unsigned int flag1_10 : 1;
			unsigned int softLand : 1;
			unsigned int seeThrough : 1;
			unsigned int shootT : 1;
			unsigned int sand : 1;
			unsigned int water : 1;

			unsigned int flag1_16 : 1;
			unsigned int beach : 1;
			unsigned int steepSI : 1;
			unsigned int glass : 1;
			unsigned int stairs : 1;
			unsigned int skateable : 1;
			unsigned int pavement : 1;
			unsigned int flag1_23 : 1;

			unsigned int flag1_24 : 1;
			unsigned int flag1_25 : 1;
			unsigned int flag1_26 : 1;
			unsigned int sparks : 1;
			unsigned int sprint : 1;
			unsigned int flag1_29 : 1;
			unsigned int flag1_30 : 1;
			unsigned int makeCarDirty : 1;
		};
		unsigned int flags1;
	};
	union {
		struct {
			unsigned int audMetalOrMakeCarClean : 1;
			unsigned int wGrass : 1;
			unsigned int wGravel : 1;
			unsigned int wMud : 1;
			unsigned int wDust : 1;
			unsigned int wSand : 1;
			unsigned int wSpray : 1;
			unsigned int flag2_7 : 1;

			unsigned int flag2_8 : 1;
			unsigned int climbable : 1;
			unsigned int audConcrete : 1;
			unsigned int audGrass : 1;
			unsigned int audSand : 1;
			unsigned int audGravel : 1;
			unsigned int audWood : 1;
			unsigned int audWater : 1;

			unsigned int flag2_16 : 1;
			unsigned int audLongGrass : 1;
			unsigned int audTitle : 1;
			unsigned int flag2_19 : 1;
			unsigned int flag2_20 : 1;
			unsigned int flag2_21 : 1;
			unsigned int flag2_22 : 1;
			unsigned int flag2_23 : 1;

			unsigned int flag2_24 : 1;
			unsigned int flag2_25 : 1;
			unsigned int flag2_26 : 1;
			unsigned int flag2_27 : 1;
			unsigned int flag2_28 : 1;
			unsigned int flag2_29 : 1;
			unsigned int flag2_30 : 1;
			unsigned int flag2_31 : 1;
		};
		unsigned int flags2;
	};
};

struct CSurface
{
	int surface[36];
	CSurfaceType surfType[179];
};

#endif // CSURFACE_H
