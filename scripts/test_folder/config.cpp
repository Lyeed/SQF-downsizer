class CfgPatches
{
	class YourTAG_ReplacementSet_With_AddonName
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DependencyToAddonsCfgPatchesClass"};
	};
};
class CfgVehicles
{
	class SoldierWB;
	class B_Soldier_base_F: SoldierWB
	{
		model = "\A3\characters_F\BLUFOR\b_soldier_01.p3d";
		nakedUniform = "U_BasicBody";
		uniformClass = "U_B_CombatUniform_mcam";
		hiddenSelections[] = {"Camo"};
		hiddenSelectionsTextures[] = {"\a3\characters_f\blufor\data\clothing1_co.paa"};
		linkedItems[] = {"V_PlateCarrier1_rgr","H_HelmetB","ItemMap","ItemCompass","ItemWatch","ItemRadio","NVGoggles"};
		respawnLinkedItems[] = {"V_PlateCarrier1_rgr","H_HelmetB","ItemMap","ItemCompass","ItemWatch","ItemRadio","NVGoggles"};
		class Wounds
		{
			tex[] = {};
			mat[] = {"A3\Characters_F\BLUFOR\Data\clothing1.rvmat",...};
		};
	};
	class B_Soldier_F: B_Soldier_base_F
	{
		nakedUniform = "U_BasicBody";
		uniformClass = "U_B_CombatUniform_mcam";
	};
};
