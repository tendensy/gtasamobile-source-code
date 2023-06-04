#include "CWeapon.h"

const uint32_t WEAPON_DAT = 0xC8AAB8;

const std::string_view weapon_list[] = { "Fist",
										 "Brass Knuckles",
										 "Golf Club",
										 "Nitestick",
										 "Knife",
										 "Baseball Bat",
										 "Shovel",
										 "Pool Cue",
										 "Katana",
										 "Chainsaw",
										 "Dildo 1",
										 "Dildo 2",
										 "Vibe 1",
										 "Vibe 2",
										 "Flowers",
										 "Cane",
										 "Grenade",
										 "Teargas",
										 "Molotov Cocktail",
										 "Weapon 19",
										 "Weapon 20",
										 "Weapon 21",
										 "Pistol",
										 "Silenced Pistol",
										 "Desert Eagle",
										 "Shotgun",
										 "Sawn-Off Shotgun",
										 "SPAZ12",
										 "Micro UZI",
										 "MP5",
										 "AK47",
										 "M4",
										 "Tech9",
										 "Country Rifle",
										 "Sniper Rifle",
										 "Rocket Launcher",
										 "Heat Seeking RPG",
										 "Flame Thrower",
										 "Minigun",
										 "Remote Explosives",
										 "Detonator",
										 "Spray Can",
										 "Fire Extinguisher",
										 "Camera",
										 "NV Goggles",
										 "IR Goggles",
										 "Parachute",
										 "INVALID_WEAPON_ID" };

const std::string_view CWeapon::getName( int id ) {
	if ( id < 0 || id > 46 ) return weapon_list[47];
	return weapon_list[id];
}

int CWeapon::getId( const std::string_view &name ) {
	for ( int id = 0; id <= 46; ++id )
		if ( getName( id ) == name ) return id;
	return -1;
}

CWeapon *CWeapon::getWeapon( uint8_t id, uint8_t skill ) {
	if ( id > 46 ) return nullptr;
	if ( id >= 19 && id <= 21 ) return nullptr;
	if ( id < 22 || id > 32 ) skill = 0;
	uint32_t skill_offset = 0;
	switch ( skill ) {
		case 1:
			skill_offset = 25;
			break;
		case 2:
			skill_offset = 36;
			break;
		case 3:
			skill_offset = 47;
			break;
		default:
			break;
	}
	uint32_t index = id + skill_offset;
	return (CWeapon *)( WEAPON_DAT + ( index * sizeof( CWeapon ) ) );
}
