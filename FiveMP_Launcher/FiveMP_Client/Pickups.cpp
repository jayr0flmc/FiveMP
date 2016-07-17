#include "stdafx.h"

void CreatePickup(int pickupid, int modelid, float x, float y, float z)
{
	int clientpickupid = -1;
	for (int i = 0; i < 100; i++) {
		if (!pickupData[i].used) {
			clientpickupid = i;
			pickupData[i].used = true;
			pickupData[i].serverID = i;
			break;
		}
	}
	if (clientpickupid == -1) { return; }

	Hash model = GAMEPLAY::GET_HASH_KEY("prop_bench_01b");

	if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_VALID(model))

		STREAMING::REQUEST_MODEL(model);
	while (!STREAMING::HAS_MODEL_LOADED(model))
		WAIT(0);

	//Creating pickup.
	pickupData[clientpickupid].pickup = OBJECT::CREATE_PICKUP(PickupTypeHealth, x, y, z, 0, 0, 0, model);

}

DWORD pickups[] = {
PickupTypeCustomScript,
PickupTypeVehicleCustomScript,
PickupTypeParachute,
PickupTypePortablePackage,
PickupTypePortableCrateUnfixed,

PickupTypeHealth,
PickupTypeHealthSnack,
PickupTypeArmour,

PickupTypeMoneyCase,
PickupTypeMoneySecurityCase,
PickupTypeMoneyVariable,
PickupTypeMoneyMedBag,
PickupTypeMoneyPurse,
PickupTypeMoneyDepBag,
PickupTypeMoneyWallet,
PickupTypeMoneyPaperBag,

PickupTypeWeaponPistol,
PickupTypeWeaponCombatPistol,
PickupTypeWeaponAPPistol,
PickupTypeWeaponSNSPistol,
PickupTypeWeaponHeavyPistol,
PickupTypeWeaponMicroSMG,
PickupTypeWeaponSMG,
PickupTypeWeaponMG,
PickupTypeWeaponCombatMG,
PickupTypeWeaponAssaultRifle,
PickupTypeWeaponCarbineRifle,
PickupTypeWeaponAdvancedRifle,
PickupTypeWeaponSpecialCarbine,
PickupTypeWeaponBullpupRifle,
PickupTypeWeaponPumpShotgun,
PickupTypeWeaponSawnoffShotgun,
PickupTypeWeaponAssaultShotgun,
PickupTypeWeaponSniperRifle,
PickupTypeWeaponHeavySniper,
PickupTypeWeaponGrenadeLauncher,
PickupTypeWeaponRPG,
PickupTypeWeaponMinigun,
PickupTypeWeaponGrenade,
PickupTypeWeaponStickyBomb,
PickupTypeWeaponSmokeGrenade,
PickupTypeWeaponMolotov,
PickupTypeWeaponPetrolCan,
PickupTypeWeaponKnife,
PickupTypeWeaponNightstick,
PickupTypeWeaponBat,
PickupTypeWeaponCrowbar,
PickupTypeWeaponGolfclub,
PickupTypeWeaponBottle,
PickupTypeWeaponFlaregun,
PickupTypeWeaponVintagePistol,
PickupTypeWeaponHandcuffKey,

PickupTypeVehicleWeaponPistol,
PickupTypeVehicleWeaponCombatPistol,
PickupTypeVehicleWeaponAPPistol,
PickupTypeVehicleWeaponMicroSMG,
PickupTypeVehicleWeaponSawnoffShotgun,
PickupTypeVehicleWeaponGrenade,
PickupTypeVehicleWeaponSmokeGrenade,
PickupTypeVehicleWeaponStickyBomb,
PickupTypeVehicleWeaponMolotov,
PickupTypeVehicleHealth,

PickupTypeAmmoPistol,
PickupTypeAmmoSMG,
PickupTypeAmmoMG,
PickupTypeAmmoRifle,
PickupTypeAmmoShotgun,
PickupTypeAmmoSniper,
PickupTypeAmmoGrenadeLauncher,
PickupTypeAmmoRPG,
PickupTypeAmmoMinigun,
PickupTypeAmmoMissileMP,
PickupTypeAmmoBulletMP,
PickupTypeAmmoGrenadeLauncherMP
};