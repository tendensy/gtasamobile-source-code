#include "CAutomobile.h"

CU FIX_TIRE_FUNC = 0x6A3580;
CU SET_TAXI_LIGHT_FUNC = 0x6A3740;
CU SET_ALL_TAXI_LIGHTS_FUNC = 0x6A3760;
CU CREATE_NITRO_PARTICLE_FUNC = 0x6A3BD0;
CU PROCESS_NITRO_FUNC = 0x6A3EA0;
CU HYDRAULIC_CONTROL_FUNC = 0x6A07A0;

int CAutomobile::fixTire(int nWheel)
{
	typedef int(__thiscall *CAutomobile__fixTire)(CAutomobile *_this, int nWheel);
	return (CAutomobile__fixTire(FIX_TIRE_FUNC))(this, nWheel);
}

int CAutomobile::setTaxiLight(bool enable)
{
	typedef int(__thiscall *CAutomobile__setTaxiLight)(CAutomobile *_this, bool enable);
	return (CAutomobile__setTaxiLight(SET_TAXI_LIGHT_FUNC))(this, enable);
}

void CAutomobile::setAllTaxiLights(bool enable)
{
	typedef int(__thiscall *CAutomobile__setAllTaxiLights)(CAutomobile *_this, bool enable);
	(CAutomobile__setAllTaxiLights(SET_ALL_TAXI_LIGHTS_FUNC))(this, enable);
}

void CAutomobile::createNitroParticle(float a2)
{
	typedef int(__thiscall *CAutomobile__createNitroParticle)(CAutomobile *_this, float a2);
	(CAutomobile__createNitroParticle(CREATE_NITRO_PARTICLE_FUNC))(this, a2);
}

void CAutomobile::processNitro(char slot)
{
	typedef int(__thiscall *CAutomobile__processNitro)(CAutomobile *_this, char slot);
	(CAutomobile__processNitro(PROCESS_NITRO_FUNC))(this, slot);
}

bool CAutomobile::hydraulicControl()
{
	typedef bool(__thiscall *CAutomobile__hydraulicControl)(CAutomobile *_this);
	return (CAutomobile__hydraulicControl(HYDRAULIC_CONTROL_FUNC))(this);
}
