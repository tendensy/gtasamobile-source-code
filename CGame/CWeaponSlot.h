#ifndef CWEAPONSLOT_H
#define CWEAPONSLOT_H

#include "Types.h"

class CWeaponSlot
{
public:
	/// Тип оружия
	DWORD		m_Type;
	/// Статус: 0 - ожидание, 1 - стреляет, 2 - перезарядка
	DWORD		m_dwState;
	/// Патронов в обойме
	DWORD		m_dwAmmoInClip;
	/// Патронов всего
	DWORD		m_dwTotalAmmo;
	/// Время для следующего выстрела (время последнего выстрела + время ожидания)
	DWORD		m_dwTimeForNextShot;
	/// 0 off, 256 on
	uint32_t	__goggle;
	/// Прикреплённый эффект
	void		*m_pParticle;
};

#endif // CWEAPONSLOT_H
