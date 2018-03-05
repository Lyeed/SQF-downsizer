/*
		ArmA 3 N'Ziwasogo Life RPG - ALYSIA
	Code written by Lyeed
	@Copyright ALYSIA - N'Ziwasogo (http://alysiarp.fr)
	YOU ARE NOT ALLOWED TO COPY OR DISTRIBUTE THE CONTENT OF THIS FILE WITHOUT AUTHOR AGREEMENT
	More informations : https://www.bistudio.com/community/game-content-usage-rules
*/

if (hasInterface) then
{
	diag_log "------------------------------------------------------------------------------------------------------";
	diag_log "---------------------------------------- Starting Client Init ----------------------------------------";
	diag_log "------------------------------------------------------------------------------------------------------";
	_timeStamp = diag_tickTime;
	_staff = !(("(getText(_x >> 'uid') isEqualTo (getPlayerUID player)) && (getNumber(_x >> 'skip_checks') isEqualTo 1)" configClasses (missionConfigFile >> "ALYSIA_STAFF" >> "members")) isEqualTo []);

	enableSaving [false, false];

	{
		_x setVariable ["BIS_noCoreConversations", true];
	} forEach allUnits;
	0 fadeRadio 0;
	0 fadeSpeech 0;
	0 fadeSound 0;
	enableSentences false;
	disableRemoteSensors true;
	showChat false;

	waitUntil {!(isNull player) && !(isNull (findDisplay 46))};
	player setVariable ["tf_globalVolume", 0];

	diag_log "<INIT> En attente de réponse du serveur...";
	("initLayer" call BIS_fnc_rscLayer) cutText ["En attente de réponse du serveur", "BLACK FADED", 999999, true];
	waitUntil {!(isNil "gServer_server_isReady") && !(isNil "gServer_mods")};
	if (!(isNil "gServer_soonReboot") && !_staff) exitWith
	{
		["Le serveur redémarre dans moins de 4 minutes, veuillez vous reconnecter après."] spawn AlysiaClient_fnc_errorExit;
	};
	setDate [gServer_year, (date select 1), (date select 2), (date select 3), (date select 4)];

	diag_log "<INIT> Vérification des mods...";
	_check = "";
	("initLayer" call BIS_fnc_rscLayer) cutText ["Vérification de la présence des mods @Alysia", "BLACK FADED", 999999, true];
	{
		if (!(isClass(configFile >> "CfgPatches" >> _x))) exitWith {_check = _x};
	} forEach gServer_mods;
	if (_check != "") exitWith
	{
		[format["Le pbo [%1] est nécessaire pour vous connecter.", _check]] spawn AlysiaClient_fnc_errorExit;
	};
	diag_log "<INIT> Mods vérifiés";
};
