#include "CBike.h"

CU PROCESS_FALL_FUNC = 0x6B5A10;
CU PROCESS_UNDER_WATER_FUNC = 0x6B5FB0;
CU PLACE_ON_ROAD_PROPERLY = 0x6BEEB0;

bool CBike::_processFall(float mass, int unused_a3, int unused_a4, int unused_a5, RwV3D *a6)
{
	typedef bool(__thiscall *CBike__processFall)(CBike *_this, float mass, int a3, int a4, int a5, RwV3D *a6);
	return (CBike__processFall(PROCESS_FALL_FUNC))(this, mass, unused_a3, unused_a4, unused_a5, a6);
}

bool CBike::processUnderWater()
{
	typedef bool(__thiscall *CBike__processUnderWater)(CBike *_this);
	return (CBike__processUnderWater(PROCESS_UNDER_WATER_FUNC))(this);
}

int CBike::placeOnRoadProperly()
{
	typedef int(__thiscall *CBike__placeOnRoadProperly)(CBike *_this);
	return (CBike__placeOnRoadProperly(PLACE_ON_ROAD_PROPERLY))(this);
}
