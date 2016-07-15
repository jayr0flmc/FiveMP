#pragma once

#include "stdafx.h"

template <typename T> class EnumParser
{
	map<string, T> enumMap;
public:
	EnumParser() {};

	T ParseEnum(const string &value)
	{
		typename map <string, T>::const_iterator iValue = enumMap.find(value);
		if (iValue == enumMap.end())
			throw runtime_error("");
		return iValue->second;
	}
};

EnumParser<eWeapon>::EnumParser()
{
	enumMap["Knife"] = WeaponKnife;
	enumMap["Nightstick"] = WeaponNightstick;
	enumMap["Hammer"] = WeaponHammer;
	enumMap["Bat"] = WeaponBat;
	enumMap["GolfClub"] = WeaponGolfClub;
	enumMap["Crowbar"] = WeaponCrowbar;
	enumMap["Pistol"] = WeaponPistol;
	enumMap["CombatPistol"] = WeaponCombatPistol;
	enumMap["APPistol"] = WeaponAPPistol;
	enumMap["Pistol50"] = WeaponPistol50;
	enumMap["MicroSMG"] = WeaponMicroSMG;
	enumMap["SMG"] = WeaponSMG;
	enumMap["AssaultSMG"] = WeaponAssaultSMG;
	enumMap["CombatPDW"] = WeaponCombatPDW;
	enumMap["AssaultRifle"] = WeaponAssaultRifle;
	enumMap["CarbineRifle"] = WeaponCarbineRifle;
	enumMap["AdvancedRifle"] = WeaponAdvancedRifle;
	enumMap["MG"] = WeaponMG;
	enumMap["CombatMG"] = WeaponCombatMG;
	enumMap["PumpShotgun"] = WeaponPumpShotgun;
	enumMap["SawnOffShotgun"] = WeaponSawnOffShotgun;
	enumMap["AssaultShotgun"] = WeaponAssaultShotgun;
	enumMap["BullpupShotgun"] = WeaponBullpupShotgun;
	enumMap["StunGun"] = WeaponStunGun;
	enumMap["SniperRifle"] = WeaponSniperRifle;
	enumMap["HeavySniper"] = WeaponHeavySniper;
	enumMap["GrenadeLauncher"] = WeaponGrenadeLauncher;
	enumMap["GrenadeLauncherSmoke"] = WeaponGrenadeLauncherSmoke;
	enumMap["RPG"] = WeaponRPG;
	enumMap["Minigun"] = WeaponMinigun;
	enumMap["Grenade"] = WeaponGrenade;
	enumMap["StickyBomb"] = WeaponStickyBomb;
	enumMap["SmokeGrenade"] = WeaponSmokeGrenade;
	enumMap["BZGas"] = WeaponBZGas;
	enumMap["Molotov"] = WeaponMolotov;
	enumMap["FireExtinguisher"] = WeaponFireExtinguisher;
	enumMap["PetrolCan"] = WeaponPetrolCan;
	enumMap["SNSPistol"] = WeaponSNSPistol;
	enumMap["SpecialCarbine"] = WeaponSpecialCarbine;
	enumMap["HeavyPistol"] = WeaponHeavyPistol;
	enumMap["BullpupRifle"] = WeaponBullpupRifle;
	enumMap["HomingLauncher"] = WeaponHomingLauncher;
	enumMap["ProximityMine"] = WeaponProximityMine;
	enumMap["Snowball"] = WeaponSnowball;
	enumMap["VintagePistol"] = WeaponVintagePistol;
	enumMap["Dagger"] = WeaponDagger;
	enumMap["Firework"] = WeaponFirework;
	enumMap["Musket"] = WeaponMusket;
	enumMap["MarksmanRifle"] = WeaponMarksmanRifle;
	enumMap["HeavyShotgun"] = WeaponHeavyShotgun;
	enumMap["Gusenberg"] = WeaponGusenberg;
	enumMap["Hatchet"] = WeaponHatchet;
	enumMap["Railgun"] = WeaponRailgun;
	enumMap["Unarmed"] = WeaponUnarmed;
	enumMap["Bottle"] = WeaponBottle;
	enumMap["VintagePistol"] = WeaponVintagePistol;
	enumMap["Flaregun"] = WeaponFlaregun;
	enumMap["GarbageBag"] = WeaponGarbageBag;
	enumMap["Handcuffs"] = WeaponHandcuffs;
	enumMap["MarksmanPistol"] = WeaponMarksmanPistol;
	enumMap["Knuckle"] = WeaponKnuckle;
};

void GameWeapon::GiveWeapon(char * weaponid, int ammo) {
	EnumParser<eWeapon> parser;
	eWeapon weapon = parser.ParseEnum(weaponid);

	WEAPON::GIVE_WEAPON_TO_PED(LocalPlayer->playerPed, weapon, ammo, false, false);
}

void GameWeapon::RemoveWeapon(char * weaponid) {
	EnumParser<eWeapon> parser;
	eWeapon weapon = parser.ParseEnum(weaponid);

	WEAPON::REMOVE_WEAPON_FROM_PED(LocalPlayer->playerPed, weapon);
}

void GameWeapon::RemoveAllWeapons() {
	WEAPON::REMOVE_ALL_PED_WEAPONS(LocalPlayer->playerPed, true);
}

void GameWeapon::GiveAmmo(char * weaponid, int ammo) {
	EnumParser<eWeapon> parser;
	eWeapon weapon = parser.ParseEnum(weaponid);

	WEAPON::ADD_AMMO_TO_PED(LocalPlayer->playerPed, weapon, ammo);
}

void GameWeapon::RemoveAmmo(char * weaponid, int ammo) {
	EnumParser<eWeapon> parser;
	eWeapon weapon = parser.ParseEnum(weaponid);

	int curAmmo = WEAPON::GET_AMMO_IN_PED_WEAPON(LocalPlayer->playerPed, weapon);
	curAmmo = curAmmo - ammo;

	WEAPON::SET_PED_AMMO(LocalPlayer->playerPed, weapon, curAmmo);
}