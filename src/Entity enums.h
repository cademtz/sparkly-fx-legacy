#pragma once

enum tf_cond
{
	TFCond_Slowed = (1 << 0), //Toggled when a player is slowed down. 
	TFCond_Zoomed = (1 << 1), //Toggled when a player is zoomed. 
	TFCond_Disguising = (1 << 2), //Toggled when a Spy is disguising.  
	TFCond_Disguised = (1 << 3), //Toggled when a Spy is disguised. 
	TFCond_Cloaked = (1 << 4), //Toggled when a Spy is invisible. 
	TFCond_Ubercharged = (1 << 5), //Toggled when a player is �berCharged. 
	TFCond_TeleportedGlow = (1 << 6), //Toggled when someone leaves a teleporter and has glow beneath their feet. 
	TFCond_Taunting = (1 << 7), //Toggled when a player is taunting. 
	TFCond_UberchargeFading = (1 << 8), //Toggled when the �berCharge is fading. 
	TFCond_CloakFlicker = (1 << 9), //Toggled when a Spy is visible during cloak. 
	TFCond_Teleporting = (1 << 10), //Only activates for a brief second when the player is being teleported; not very useful. 
	TFCond_Kritzkrieged = (1 << 11), //Toggled when a player is being crit buffed by the KritzKrieg. 
	TFCond_TmpDamageBonus = (1 << 12), //Unknown what this is for. Name taken from the AlliedModders SDK. 
	TFCond_DeadRingered = (1 << 13), //Toggled when a player is taking reduced damage from the Deadringer. 
	TFCond_Bonked = (1 << 14), //Toggled when a player is under the effects of The Bonk! Atomic Punch. 
	TFCond_Stunned = (1 << 15), //Toggled when a player's speed is reduced from airblast or a Sandman ball. 
	TFCond_Buffed = (1 << 16), //Toggled when a player is within range of an activated Buff Banner. 
	TFCond_Charging = (1 << 17), //Toggled when a Demoman charges with the shield. 
	TFCond_DemoBuff = (1 << 18), //Toggled when a Demoman has heads from the Eyelander. 
	TFCond_CritCola = (1 << 19), //Toggled when the player is under the effect of The Crit-a-Cola. 
	TFCond_InHealRadius = (1 << 20), //Unused condition, name taken from AlliedModders SDK. 
	TFCond_Healing = (1 << 21), //Toggled when someone is being healed by a medic or a dispenser. 
	TFCond_OnFire = (1 << 22), //Toggled when a player is on fire. 
	TFCond_Overhealed = (1 << 23), //Toggled when a player has >100% health. 
	TFCond_Jarated = (1 << 24), //Toggled when a player is hit with a Sniper's Jarate. 
	TFCond_Bleeding = (1 << 25), //Toggled when a player is taking bleeding damage. 
	TFCond_DefenseBuffed = (1 << 26), //Toggled when a player is within range of an activated Battalion's Backup. 
	TFCond_Milked = (1 << 27), //Player was hit with a jar of Mad Milk. 
	TFCond_MegaHeal = (1 << 28), //Player is under the effect of Quick-Fix charge. 
	TFCond_RegenBuffed = (1 << 29), //Toggled when a player is within a Concheror's range. 
	TFCond_MarkedForDeath = (1 << 30), //Player is marked for death by a Fan O'War hit. Effects are similar to TFCond_Jarated. 
	TFCond_NoHealingDamageBuff = (1 << 31), //Unknown what this is used for.

	TFCondEx_SpeedBuffAlly = (1 << 0), //Toggled when a player gets hit with the disciplinary action. 
	TFCondEx_HalloweenCritCandy = (1 << 1), //Only for Scream Fortress event maps that drop crit candy. 
	TFCondEx_CritCanteen = (1 << 2), //Player is getting a crit boost from a MVM canteen.
	TFCondEx_CritDemoCharge = (1 << 3), //From demo's shield
	TFCondEx_CritHype = (1 << 4), //Soda Popper crits. 
	TFCondEx_CritOnFirstBlood = (1 << 5), //Arena first blood crit buff. 
	TFCondEx_CritOnWin = (1 << 6), //End of round crits. 
	TFCondEx_CritOnFlagCapture = (1 << 7), //CTF intelligence capture crits. 
	TFCondEx_CritOnKill = (1 << 8), //Unknown what this is for. 
	TFCondEx_RestrictToMelee = (1 << 9), //Unknown what this is for. 
	TFCondEx_DefenseBuffNoCritBlock = (1 << 10), //MvM Buff.
	TFCondEx_Reprogrammed = (1 << 11), //MvM Bot has been reprogrammed.
	TFCondEx_PyroCrits = (1 << 12), //Player is getting crits from the Mmmph charge. 
	TFCondEx_PyroHeal = (1 << 13), //Player is being healed from the Mmmph charge. 
	TFCondEx_FocusBuff = (1 << 14), //Player is getting a focus buff.
	TFCondEx_DisguisedRemoved = (1 << 15), //Disguised remove from a bot.
	TFCondEx_MarkedForDeathSilent = (1 << 16), //Player is under the effects of the Escape Plan/Equalizer or GRU.
	TFCondEx_DisguisedAsDispenser = (1 << 17), //Bot is disguised as dispenser.
	TFCondEx_Sapped = (1 << 18), //MvM bot is being sapped.
	TFCondEx_UberchargedHidden = (1 << 19), //MvM Related
	TFCondEx_UberchargedCanteen = (1 << 20), //Player is receiving �berCharge from a canteen.
	TFCondEx_HalloweenBombHead = (1 << 21), //Player has a bomb on their head from Merasmus.
	TFCondEx_HalloweenThriller = (1 << 22), //Players are forced to dance from Merasmus.
	TFCondEx_BulletCharge = (1 << 26), //Player is receiving 75% reduced damage from bullets.
	TFCondEx_ExplosiveCharge = (1 << 27), //Player is receiving 75% reduced damage from explosives.
	TFCondEx_FireCharge = (1 << 28), //Player is receiving 75% reduced damage from fire.
	TFCondEx_BulletResistance = (1 << 29), //Player is receiving 10% reduced damage from bullets.
	TFCondEx_ExplosiveResistance = (1 << 30), //Player is receiving 10% reduced damage from explosives.
	TFCondEx_FireResistance = (1 << 31), //Player is receiving 10% reduced damage from fire.

	TFCondEx2_Stealthed = (1 << 0),
	TFCondEx2_MedigunDebuff = (1 << 1),
	TFCondEx2_StealthedUserBuffFade = (1 << 2),
	TFCondEx2_BulletImmune = (1 << 3),
	TFCondEx2_BlastImmune = (1 << 4),
	TFCondEx2_FireImmune = (1 << 5),
	TFCondEx2_PreventDeath = (1 << 6),
	TFCondEx2_MVMBotRadiowave = (1 << 7),
	TFCondEx2_HalloweenSpeedBoost = (1 << 8), //Wheel has granted player speed boost.
	TFCondEx2_HalloweenQuickHeal = (1 << 9), //Wheel has granted player quick heal.
	TFCondEx2_HalloweenGiant = (1 << 10), //Wheel has granted player giant mode.
	TFCondEx2_HalloweenTiny = (1 << 11), //Wheel has granted player tiny mode.
	TFCondEx2_HalloweenInHell = (1 << 12), //Wheel has granted player in hell mode.
	TFCondEx2_HalloweenGhostMode = (1 << 13), //Wheel has granted player ghost mode.
	TFCondEx2_Parachute = (1 << 16), //Player has deployed the BASE Jumper.
	TFCondEx2_BlastJumping = (1 << 17), //Player has sticky or rocket jumped.

	TFCond_MiniCrits = (TFCond_Buffed | TFCond_CritCola),
	TFCond_IgnoreStates = (TFCond_Ubercharged | TFCond_Bonked),
	TFCondEx_IgnoreStates = (TFCondEx_PyroHeal)
};

enum tf_classes : int
{
	TF2_Scout = 1,
	TF2_Soldier = 3,
	TF2_Pyro = 7,
	TF2_Demoman = 4,
	TF2_Heavy = 6,
	TF2_Engineer = 9,
	TF2_Medic = 5,
	TF2_Sniper = 2,
	TF2_Spy = 8,
};

enum source_lifestates : unsigned char
{
	LIFE_ALIVE,
	LIFE_DYING,
	LIFE_DEAD,
	LIFE_RESPAWNABLE,
	LIFE_DISCARDBODY,
};

//typedef int ent_id;

namespace ent_id
{
	static constexpr const char* CTFWearableRazorback = "CTFWearableRazorback";
	static constexpr const char* CTFWearableDemoShield = "CTFWearableDemoShield";
	static constexpr const char* CTFWearableLevelableItem = "CTFWearableLevelableItem";
	static constexpr const char* CTFWearableCampaignItem = "CTFWearableCampaignItem";
	static constexpr const char* CTFBaseRocket = "CTFBaseRocket";
	static constexpr const char* CTFWeaponBaseMerasmusGrenade = "CTFWeaponBaseMerasmusGrenade";
	static constexpr const char* CTFWeaponBaseMelee = "CTFWeaponBaseMelee";
	static constexpr const char* CTFWeaponBaseGun = "CTFWeaponBaseGun";
	static constexpr const char* CTFWeaponBaseGrenadeProj = "CTFWeaponBaseGrenadeProj";
	static constexpr const char* CTFWeaponBase = "CTFWeaponBase";
	static constexpr const char* CTFWearableRobotArm = "CTFWearableRobotArm";
	static constexpr const char* CTFRobotArm = "CTFRobotArm";
	static constexpr const char* CTFWrench = "CTFWrench";
	static constexpr const char* CTFProjectile_ThrowableBreadMonster = "CTFProjectile_ThrowableBreadMonster";
	static constexpr const char* CTFProjectile_ThrowableBrick = "CTFProjectile_ThrowableBrick";
	static constexpr const char* CTFProjectile_ThrowableRepel = "CTFProjectile_ThrowableRepel";
	static constexpr const char* CTFProjectile_Throwable = "CTFProjectile_Throwable";
	static constexpr const char* CTFThrowable = "CTFThrowable";
	static constexpr const char* CTFSyringeGun = "CTFSyringeGun";
	static constexpr const char* CTFKatana = "CTFKatana";
	static constexpr const char* CTFSword = "CTFSword";
	static constexpr const char* CSniperDot = "CSniperDot";
	static constexpr const char* CTFSniperRifleClassic = "CTFSniperRifleClassic";
	static constexpr const char* CTFSniperRifleDecap = "CTFSniperRifleDecap";
	static constexpr const char* CTFSniperRifle = "CTFSniperRifle";
	static constexpr const char* CTFChargedSMG = "CTFChargedSMG";
	static constexpr const char* CTFSMG = "CTFSMG";
	static constexpr const char* CTFSlap = "CTFSlap";
	static constexpr const char* CTFShovel = "CTFShovel";
	static constexpr const char* CTFShotgunBuildingRescue = "CTFShotgunBuildingRescue";
	static constexpr const char* CTFPEPBrawlerBlaster = "CTFPEPBrawlerBlaster";
	static constexpr const char* CTFSodaPopper = "CTFSodaPopper";
	static constexpr const char* CTFShotgun_Revenge = "CTFShotgun_Revenge";
	static constexpr const char* CTFScatterGun = "CTFScatterGun";
	static constexpr const char* CTFShotgun_Pyro = "CTFShotgun_Pyro";
	static constexpr const char* CTFShotgun_HWG = "CTFShotgun_HWG";
	static constexpr const char* CTFShotgun_Soldier = "CTFShotgun_Soldier";
	static constexpr const char* CTFShotgun = "CTFShotgun";
	static constexpr const char* CTFRocketPack = "CTFRocketPack";
	static constexpr const char* CTFCrossbow = "CTFCrossbow";
	static constexpr const char* CTFRocketLauncher_Mortar = "CTFRocketLauncher_Mortar";
	static constexpr const char* CTFRocketLauncher_AirStrike = "CTFRocketLauncher_AirStrike";
	static constexpr const char* CTFRocketLauncher_DirectHit = "CTFRocketLauncher_DirectHit";
	static constexpr const char* CTFRocketLauncher = "CTFRocketLauncher";
	static constexpr const char* CTFRevolver = "CTFRevolver";
	static constexpr const char* CTFDRGPomson = "CTFDRGPomson";
	static constexpr const char* CTFRaygun = "CTFRaygun";
	static constexpr const char* CTFPistol_ScoutSecondary = "CTFPistol_ScoutSecondary";
	static constexpr const char* CTFPistol_ScoutPrimary = "CTFPistol_ScoutPrimary";
	static constexpr const char* CTFPistol_Scout = "CTFPistol_Scout";
	static constexpr const char* CTFPistol = "CTFPistol";
	static constexpr const char* CTFPipebombLauncher = "CTFPipebombLauncher";
	static constexpr const char* CTFWeaponPDA_Spy = "CTFWeaponPDA_Spy";
	static constexpr const char* CTFWeaponPDA_Engineer_Destroy = "CTFWeaponPDA_Engineer_Destroy";
	static constexpr const char* CTFWeaponPDA_Engineer_Build = "CTFWeaponPDA_Engineer_Build";
	static constexpr const char* CTFWeaponPDAExpansion_Teleporter = "CTFWeaponPDAExpansion_Teleporter";
	static constexpr const char* CTFWeaponPDAExpansion_Dispenser = "CTFWeaponPDAExpansion_Dispenser";
	static constexpr const char* CTFWeaponPDA = "CTFWeaponPDA";
	static constexpr const char* CTFParticleCannon = "CTFParticleCannon";
	static constexpr const char* CTFParachute_Secondary = "CTFParachute_Secondary";
	static constexpr const char* CTFParachute_Primary = "CTFParachute_Primary";
	static constexpr const char* CTFParachute = "CTFParachute";
	static constexpr const char* CTFMinigun = "CTFMinigun";
	static constexpr const char* CTFMedigunShield = "CTFMedigunShield";
	static constexpr const char* CWeaponMedigun = "CWeaponMedigun";
	static constexpr const char* CTFProjectile_MechanicalArmOrb = "CTFProjectile_MechanicalArmOrb";
	static constexpr const char* CTFMechanicalArm = "CTFMechanicalArm";
	static constexpr const char* CTFLunchBox_Drink = "CTFLunchBox_Drink";
	static constexpr const char* CTFLunchBox = "CTFLunchBox";
	static constexpr const char* CLaserDot = "CLaserDot";
	static constexpr const char* CTFLaserPointer = "CTFLaserPointer";
	static constexpr const char* CTFKnife = "CTFKnife";
	static constexpr const char* CTFGasManager = "CTFGasManager";
	static constexpr const char* CTFProjectile_JarGas = "CTFProjectile_JarGas";
	static constexpr const char* CTFJarGas = "CTFJarGas";
	static constexpr const char* CTFProjectile_Cleaver = "CTFProjectile_Cleaver";
	static constexpr const char* CTFProjectile_JarMilk = "CTFProjectile_JarMilk";
	static constexpr const char* CTFProjectile_Jar = "CTFProjectile_Jar";
	static constexpr const char* CTFCleaver = "CTFCleaver";
	static constexpr const char* CTFJarMilk = "CTFJarMilk";
	static constexpr const char* CTFJar = "CTFJar";
	static constexpr const char* CTFWeaponInvis = "CTFWeaponInvis";
	static constexpr const char* CTFCannon = "CTFCannon";
	static constexpr const char* CTFGrenadeLauncher = "CTFGrenadeLauncher";
	static constexpr const char* CTFGrenadePipebombProjectile = "CTFGrenadePipebombProjectile";
	static constexpr const char* CTFGrapplingHook = "CTFGrapplingHook";
	static constexpr const char* CTFFlareGun_Revenge = "CTFFlareGun_Revenge";
	static constexpr const char* CTFFlareGun = "CTFFlareGun";
	static constexpr const char* CTFFlameRocket = "CTFFlameRocket";
	static constexpr const char* CTFFlameThrower = "CTFFlameThrower";
	static constexpr const char* CTFFists = "CTFFists";
	static constexpr const char* CTFFireAxe = "CTFFireAxe";
	static constexpr const char* CTFWeaponFlameBall = "CTFWeaponFlameBall";
	static constexpr const char* CTFCompoundBow = "CTFCompoundBow";
	static constexpr const char* CTFClub = "CTFClub";
	static constexpr const char* CTFBuffItem = "CTFBuffItem";
	static constexpr const char* CTFStickBomb = "CTFStickBomb";
	static constexpr const char* CTFBreakableSign = "CTFBreakableSign";
	static constexpr const char* CTFBottle = "CTFBottle";
	static constexpr const char* CTFBreakableMelee = "CTFBreakableMelee";
	static constexpr const char* CTFBonesaw = "CTFBonesaw";
	static constexpr const char* CTFBall_Ornament = "CTFBall_Ornament";
	static constexpr const char* CTFStunBall = "CTFStunBall";
	static constexpr const char* CTFBat_Giftwrap = "CTFBat_Giftwrap";
	static constexpr const char* CTFBat_Wood = "CTFBat_Wood";
	static constexpr const char* CTFBat_Fish = "CTFBat_Fish";
	static constexpr const char* CTFBat = "CTFBat";
	static constexpr const char* CTFProjectile_EnergyRing = "CTFProjectile_EnergyRing";
	static constexpr const char* CTFDroppedWeapon = "CTFDroppedWeapon";
	static constexpr const char* CTFWeaponSapper = "CTFWeaponSapper";
	static constexpr const char* CTFWeaponBuilder = "CTFWeaponBuilder";
	static constexpr const char* C_TFWeaponBuilder = "C_TFWeaponBuilder";
	static constexpr const char* CTFProjectile_Rocket = "CTFProjectile_Rocket";
	static constexpr const char* CTFProjectile_Flare = "CTFProjectile_Flare";
	static constexpr const char* CTFProjectile_EnergyBall = "CTFProjectile_EnergyBall";
	static constexpr const char* CTFProjectile_GrapplingHook = "CTFProjectile_GrapplingHook";
	static constexpr const char* CTFProjectile_HealingBolt = "CTFProjectile_HealingBolt";
	static constexpr const char* CTFProjectile_Arrow = "CTFProjectile_Arrow";
	static constexpr const char* CMannVsMachineStats = "CMannVsMachineStats";
	static constexpr const char* CTFTankBoss = "CTFTankBoss";
	static constexpr const char* CTFBaseBoss = "CTFBaseBoss";
	static constexpr const char* CBossAlpha = "CBossAlpha";
	static constexpr const char* NextBotCombatCharacter = "NextBotCombatCharacter";
	static constexpr const char* CTFProjectile_SpellKartBats = "CTFProjectile_SpellKartBats";
	static constexpr const char* CTFProjectile_SpellKartOrb = "CTFProjectile_SpellKartOrb";
	static constexpr const char* CTFHellZap = "CTFHellZap";
	static constexpr const char* CTFProjectile_SpellLightningOrb = "CTFProjectile_SpellLightningOrb";
	static constexpr const char* CTFProjectile_SpellTransposeTeleport = "CTFProjectile_SpellTransposeTeleport";
	static constexpr const char* CTFProjectile_SpellMeteorShower = "CTFProjectile_SpellMeteorShower";
	static constexpr const char* CTFProjectile_SpellSpawnBoss = "CTFProjectile_SpellSpawnBoss";
	static constexpr const char* CTFProjectile_SpellMirv = "CTFProjectile_SpellMirv";
	static constexpr const char* CTFProjectile_SpellPumpkin = "CTFProjectile_SpellPumpkin";
	static constexpr const char* CTFProjectile_SpellSpawnHorde = "CTFProjectile_SpellSpawnHorde";
	static constexpr const char* CTFProjectile_SpellSpawnZombie = "CTFProjectile_SpellSpawnZombie";
	static constexpr const char* CTFProjectile_SpellBats = "CTFProjectile_SpellBats";
	static constexpr const char* CTFProjectile_SpellFireball = "CTFProjectile_SpellFireball";
	static constexpr const char* CTFSpellBook = "CTFSpellBook";
	static constexpr const char* CHightower_TeleportVortex = "CHightower_TeleportVortex";
	static constexpr const char* CTeleportVortex = "CTeleportVortex";
	static constexpr const char* CZombie = "CZombie";
	static constexpr const char* CMerasmusDancer = "CMerasmusDancer";
	static constexpr const char* CMerasmus = "CMerasmus";
	static constexpr const char* CHeadlessHatman = "CHeadlessHatman";
	static constexpr const char* CEyeballBoss = "CEyeballBoss";
	static constexpr const char* CTFBotHintEngineerNest = "CTFBotHintEngineerNest";
	static constexpr const char* CBotNPCMinion = "CBotNPCMinion";
	static constexpr const char* CBotNPC = "CBotNPC";
	static constexpr const char* CPasstimeGun = "CPasstimeGun";
	static constexpr const char* CTFViewModel = "CTFViewModel";
	static constexpr const char* CRobotDispenser = "CRobotDispenser";
	static constexpr const char* CTFRobotDestruction_Robot = "CTFRobotDestruction_Robot";
	static constexpr const char* CTFReviveMarker = "CTFReviveMarker";
	static constexpr const char* CTFPumpkinBomb = "CTFPumpkinBomb";
	static constexpr const char* CTFProjectile_BallOfFire = "CTFProjectile_BallOfFire";
	static constexpr const char* CTFBaseProjectile = "CTFBaseProjectile";
	static constexpr const char* CTFPointManager = "CTFPointManager";
	static constexpr const char* CBaseObjectUpgrade = "CBaseObjectUpgrade";
	static constexpr const char* CTFRobotDestructionLogic = "CTFRobotDestructionLogic";
	static constexpr const char* CTFRobotDestruction_RobotGroup = "CTFRobotDestruction_RobotGroup";
	static constexpr const char* CTFRobotDestruction_RobotSpawn = "CTFRobotDestruction_RobotSpawn";
	static constexpr const char* CTFPlayerDestructionLogic = "CTFPlayerDestructionLogic";
	static constexpr const char* CPlayerDestructionDispenser = "CPlayerDestructionDispenser";
	static constexpr const char* CTFMinigameLogic = "CTFMinigameLogic";
	static constexpr const char* CTFHalloweenMinigame_FallingPlatforms = "CTFHalloweenMinigame_FallingPlatforms";
	static constexpr const char* CTFHalloweenMinigame = "CTFHalloweenMinigame";
	static constexpr const char* CTFMiniGame = "CTFMiniGame";
	static constexpr const char* CTFPowerupBottle = "CTFPowerupBottle";
	static constexpr const char* CTFItem = "CTFItem";
	static constexpr const char* CHalloweenSoulPack = "CHalloweenSoulPack";
	static constexpr const char* CTFGenericBomb = "CTFGenericBomb";
	static constexpr const char* CBonusRoundLogic = "CBonusRoundLogic";
	static constexpr const char* CTFGameRulesProxy = "CTFGameRulesProxy";
	static constexpr const char* CTETFParticleEffect = "CTETFParticleEffect";
	static constexpr const char* CTETFExplosion = "CTETFExplosion";
	static constexpr const char* CTETFBlood = "CTETFBlood";
	static constexpr const char* CTFFlameManager = "CTFFlameManager";
	static constexpr const char* CHalloweenGiftPickup = "CHalloweenGiftPickup";
	static constexpr const char* CBonusDuckPickup = "CBonusDuckPickup";
	static constexpr const char* CHalloweenPickup = "CHalloweenPickup";
	static constexpr const char* CCaptureFlagReturnIcon = "CCaptureFlagReturnIcon";
	static constexpr const char* CCaptureFlag = "CCaptureFlag";
	static constexpr const char* CBonusPack = "CBonusPack";
	static constexpr const char* CTFTeam = "CTFTeam";
	static constexpr const char* CTFTauntProp = "CTFTauntProp";
	static constexpr const char* CTFPlayerResource = "CTFPlayerResource";
	static constexpr const char* CTFPlayer = "CTFPlayer";
	static constexpr const char* CTFRagdoll = "CTFRagdoll";
	static constexpr const char* CTEPlayerAnimEvent = "CTEPlayerAnimEvent";
	static constexpr const char* CTFPasstimeLogic = "CTFPasstimeLogic";
	static constexpr const char* CPasstimeBall = "CPasstimeBall";
	static constexpr const char* CTFObjectiveResource = "CTFObjectiveResource";
	static constexpr const char* CTFGlow = "CTFGlow";
	static constexpr const char* CTEFireBullets = "CTEFireBullets";
	static constexpr const char* CTFBuffBanner = "CTFBuffBanner";
	static constexpr const char* CTFAmmoPack = "CTFAmmoPack";
	static constexpr const char* CObjectTeleporter = "CObjectTeleporter";
	static constexpr const char* CObjectSentrygun = "CObjectSentrygun";
	static constexpr const char* CTFProjectile_SentryRocket = "CTFProjectile_SentryRocket";
	static constexpr const char* CObjectSapper = "CObjectSapper";
	static constexpr const char* CObjectCartDispenser = "CObjectCartDispenser";
	static constexpr const char* CObjectDispenser = "CObjectDispenser";
	static constexpr const char* CMonsterResource = "CMonsterResource";
	static constexpr const char* CFuncRespawnRoomVisualizer = "CFuncRespawnRoomVisualizer";
	static constexpr const char* CFuncRespawnRoom = "CFuncRespawnRoom";
	static constexpr const char* CFuncPasstimeGoal = "CFuncPasstimeGoal";
	static constexpr const char* CFuncForceField = "CFuncForceField";
	static constexpr const char* CCaptureZone = "CCaptureZone";
	static constexpr const char* CCurrencyPack = "CCurrencyPack";
	static constexpr const char* CBaseObject = "CBaseObject";
	static constexpr const char* CTestTraceline = "CTestTraceline";
	static constexpr const char* CTEWorldDecal = "CTEWorldDecal";
	static constexpr const char* CTESpriteSpray = "CTESpriteSpray";
	static constexpr const char* CTESprite = "CTESprite";
	static constexpr const char* CTESparks = "CTESparks";
	static constexpr const char* CTESmoke = "CTESmoke";
	static constexpr const char* CTEShowLine = "CTEShowLine";
	static constexpr const char* CTEProjectedDecal = "CTEProjectedDecal";
	static constexpr const char* CTEPlayerDecal = "CTEPlayerDecal";
	static constexpr const char* CTEPhysicsProp = "CTEPhysicsProp";
	static constexpr const char* CTEParticleSystem = "CTEParticleSystem";
	static constexpr const char* CTEMuzzleFlash = "CTEMuzzleFlash";
	static constexpr const char* CTELargeFunnel = "CTELargeFunnel";
	static constexpr const char* CTEKillPlayerAttachments = "CTEKillPlayerAttachments";
	static constexpr const char* CTEImpact = "CTEImpact";
	static constexpr const char* CTEGlowSprite = "CTEGlowSprite";
	static constexpr const char* CTEShatterSurface = "CTEShatterSurface";
	static constexpr const char* CTEFootprintDecal = "CTEFootprintDecal";
	static constexpr const char* CTEFizz = "CTEFizz";
	static constexpr const char* CTEExplosion = "CTEExplosion";
	static constexpr const char* CTEEnergySplash = "CTEEnergySplash";
	static constexpr const char* CTEEffectDispatch = "CTEEffectDispatch";
	static constexpr const char* CTEDynamicLight = "CTEDynamicLight";
	static constexpr const char* CTEDecal = "CTEDecal";
	static constexpr const char* CTEClientProjectile = "CTEClientProjectile";
	static constexpr const char* CTEBubbleTrail = "CTEBubbleTrail";
	static constexpr const char* CTEBubbles = "CTEBubbles";
	static constexpr const char* CTEBSPDecal = "CTEBSPDecal";
	static constexpr const char* CTEBreakModel = "CTEBreakModel";
	static constexpr const char* CTEBloodStream = "CTEBloodStream";
	static constexpr const char* CTEBloodSprite = "CTEBloodSprite";
	static constexpr const char* CTEBeamSpline = "CTEBeamSpline";
	static constexpr const char* CTEBeamRingPoint = "CTEBeamRingPoint";
	static constexpr const char* CTEBeamRing = "CTEBeamRing";
	static constexpr const char* CTEBeamPoints = "CTEBeamPoints";
	static constexpr const char* CTEBeamLaser = "CTEBeamLaser";
	static constexpr const char* CTEBeamFollow = "CTEBeamFollow";
	static constexpr const char* CTEBeamEnts = "CTEBeamEnts";
	static constexpr const char* CTEBeamEntPoint = "CTEBeamEntPoint";
	static constexpr const char* CTEBaseBeam = "CTEBaseBeam";
	static constexpr const char* CTEArmorRicochet = "CTEArmorRicochet";
	static constexpr const char* CTEMetalSparks = "CTEMetalSparks";
	static constexpr const char* CSteamJet = "CSteamJet";
	static constexpr const char* CSmokeStack = "CSmokeStack";
	static constexpr const char* DustTrail = "DustTrail";
	static constexpr const char* CFireTrail = "CFireTrail";
	static constexpr const char* SporeTrail = "SporeTrail";
	static constexpr const char* SporeExplosion = "SporeExplosion";
	static constexpr const char* RocketTrail = "RocketTrail";
	static constexpr const char* SmokeTrail = "SmokeTrail";
	static constexpr const char* CPropVehicleDriveable = "CPropVehicleDriveable";
	static constexpr const char* ParticleSmokeGrenade = "ParticleSmokeGrenade";
	static constexpr const char* CParticleFire = "CParticleFire";
	static constexpr const char* MovieExplosion = "MovieExplosion";
	static constexpr const char* CTEGaussExplosion = "CTEGaussExplosion";
	static constexpr const char* CEnvQuadraticBeam = "CEnvQuadraticBeam";
	static constexpr const char* CEmbers = "CEmbers";
	static constexpr const char* CEnvWind = "CEnvWind";
	static constexpr const char* CPrecipitation = "CPrecipitation";
	static constexpr const char* CBaseTempEntity = "CBaseTempEntity";
	static constexpr const char* CWeaponIFMSteadyCam = "CWeaponIFMSteadyCam";
	static constexpr const char* CWeaponIFMBaseCamera = "CWeaponIFMBaseCamera";
	static constexpr const char* CWeaponIFMBase = "CWeaponIFMBase";
	static constexpr const char* CTFWearableVM = "CTFWearableVM";
	static constexpr const char* CTFWearable = "CTFWearable";
	static constexpr const char* CTFWearableItem = "CTFWearableItem";
	static constexpr const char* CEconWearable = "CEconWearable";
	static constexpr const char* CBaseAttributableItem = "CBaseAttributableItem";
	static constexpr const char* CEconEntity = "CEconEntity";
	static constexpr const char* CHandleTest = "CHandleTest";
	static constexpr const char* CTeamplayRoundBasedRulesProxy = "CTeamplayRoundBasedRulesProxy";
	static constexpr const char* CTeamRoundTimer = "CTeamRoundTimer";
	static constexpr const char* CSpriteTrail = "CSpriteTrail";
	static constexpr const char* CSpriteOriented = "CSpriteOriented";
	static constexpr const char* CSprite = "CSprite";
	static constexpr const char* CRagdollPropAttached = "CRagdollPropAttached";
	static constexpr const char* CRagdollProp = "CRagdollProp";
	static constexpr const char* CPoseController = "CPoseController";
	static constexpr const char* CGameRulesProxy = "CGameRulesProxy";
	static constexpr const char* CInfoLadderDismount = "CInfoLadderDismount";
	static constexpr const char* CFuncLadder = "CFuncLadder";
	static constexpr const char* CEnvDetailController = "CEnvDetailController";
	static constexpr const char* CWorld = "CWorld";
	static constexpr const char* CWaterLODControl = "CWaterLODControl";
	static constexpr const char* CWaterBullet = "CWaterBullet";
	static constexpr const char* CVoteController = "CVoteController";
	static constexpr const char* CVGuiScreen = "CVGuiScreen";
	static constexpr const char* CPropJeep = "CPropJeep";
	static constexpr const char* CPropVehicleChoreoGeneric = "CPropVehicleChoreoGeneric";
	static constexpr const char* CTest_ProxyToggle_Networkable = "CTest_ProxyToggle_Networkable";
	static constexpr const char* CTesla = "CTesla";
	static constexpr const char* CTeamTrainWatcher = "CTeamTrainWatcher";
	static constexpr const char* CBaseTeamObjectiveResource = "CBaseTeamObjectiveResource";
	static constexpr const char* CTeam = "CTeam";
	static constexpr const char* CSun = "CSun";
	static constexpr const char* CParticlePerformanceMonitor = "CParticlePerformanceMonitor";
	static constexpr const char* CSpotlightEnd = "CSpotlightEnd";
	static constexpr const char* CSlideshowDisplay = "CSlideshowDisplay";
	static constexpr const char* CShadowControl = "CShadowControl";
	static constexpr const char* CSceneEntity = "CSceneEntity";
	static constexpr const char* CRopeKeyframe = "CRopeKeyframe";
	static constexpr const char* CRagdollManager = "CRagdollManager";
	static constexpr const char* CPhysicsPropMultiplayer = "CPhysicsPropMultiplayer";
	static constexpr const char* CPhysBoxMultiplayer = "CPhysBoxMultiplayer";
	static constexpr const char* CBasePropDoor = "CBasePropDoor";
	static constexpr const char* CDynamicProp = "CDynamicProp";
	static constexpr const char* CPointCommentaryNode = "CPointCommentaryNode";
	static constexpr const char* CPointCamera = "CPointCamera";
	static constexpr const char* CPlayerResource = "CPlayerResource";
	static constexpr const char* CPlasma = "CPlasma";
	static constexpr const char* CPhysMagnet = "CPhysMagnet";
	static constexpr const char* CPhysicsProp = "CPhysicsProp";
	static constexpr const char* CPhysBox = "CPhysBox";
	static constexpr const char* CParticleSystem = "CParticleSystem";
	static constexpr const char* CMaterialModifyControl = "CMaterialModifyControl";
	static constexpr const char* CLightGlow = "CLightGlow";
	static constexpr const char* CInfoOverlayAccessor = "CInfoOverlayAccessor";
	static constexpr const char* CFuncTrackTrain = "CFuncTrackTrain";
	static constexpr const char* CFuncSmokeVolume = "CFuncSmokeVolume";
	static constexpr const char* CFuncRotating = "CFuncRotating";
	static constexpr const char* CFuncReflectiveGlass = "CFuncReflectiveGlass";
	static constexpr const char* CFuncOccluder = "CFuncOccluder";
	static constexpr const char* CFuncMonitor = "CFuncMonitor";
	static constexpr const char* CFunc_LOD = "CFunc_LOD";
	static constexpr const char* CTEDust = "CTEDust";
	static constexpr const char* CFunc_Dust = "CFunc_Dust";
	static constexpr const char* CFuncConveyor = "CFuncConveyor";
	static constexpr const char* CBreakableSurface = "CBreakableSurface";
	static constexpr const char* CFuncAreaPortalWindow = "CFuncAreaPortalWindow";
	static constexpr const char* CFish = "CFish";
	static constexpr const char* CEntityFlame = "CEntityFlame";
	static constexpr const char* CFireSmoke = "CFireSmoke";
	static constexpr const char* CEnvTonemapController = "CEnvTonemapController";
	static constexpr const char* CEnvScreenEffect = "CEnvScreenEffect";
	static constexpr const char* CEnvScreenOverlay = "CEnvScreenOverlay";
	static constexpr const char* CEnvProjectedTexture = "CEnvProjectedTexture";
	static constexpr const char* CEnvParticleScript = "CEnvParticleScript";
	static constexpr const char* CFogController = "CFogController";
	static constexpr const char* CEntityParticleTrail = "CEntityParticleTrail";
	static constexpr const char* CEntityDissolve = "CEntityDissolve";
	static constexpr const char* CDynamicLight = "CDynamicLight";
	static constexpr const char* CColorCorrectionVolume = "CColorCorrectionVolume";
	static constexpr const char* CColorCorrection = "CColorCorrection";
	static constexpr const char* CBreakableProp = "CBreakableProp";
	static constexpr const char* CBasePlayer = "CBasePlayer";
	static constexpr const char* CBaseFlex = "CBaseFlex";
	static constexpr const char* CBaseEntity = "CBaseEntity";
	static constexpr const char* CBaseDoor = "CBaseDoor";
	static constexpr const char* CBaseCombatCharacter = "CBaseCombatCharacter";
	static constexpr const char* CBaseAnimatingOverlay = "CBaseAnimatingOverlay";
	static constexpr const char* CBoneFollower = "CBoneFollower";
	static constexpr const char* CBaseAnimating = "CBaseAnimating";
	static constexpr const char* CInfoLightingRelative = "CInfoLightingRelative";
	static constexpr const char* CAI_BaseNPC = "CAI_BaseNPC";
	static constexpr const char* CBeam = "CBeam";
	static constexpr const char* CBaseViewModel = "CBaseViewModel";
	static constexpr const char* CBaseProjectile = "CBaseProjectile";
	static constexpr const char* CBaseParticleEntity = "CBaseParticleEntity";
	static constexpr const char* CBaseGrenade = "CBaseGrenade";
	static constexpr const char* CBaseCombatWeapon = "CBaseCombatWeapon";
};