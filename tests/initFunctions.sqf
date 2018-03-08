/* EXTRACTED FROM ArmA3 GAME */

/*
	File: init.sqf
	Author: Karel Moricky, optimised headers by Killzone_Kid

	Description:
	Function library initialization.

	Parameter(s):
	_this select 0: 'Function manager' logic

	Returns:
	Nothing
*/

#define VERSION	3.0

if (isNil "BIS_fnc_MP_packet") then {BIS_fnc_MP_packet = compileFinal ""}; 


if (getnumber (configfile >> "CfgFunctions" >> "version") != VERSION) exitwith {
	textlogformat [
		"Log: ERROR: Functions versions mismatch - config is %1, but script is %2",
		getnumber (configfile >> "CfgFunctions" >> "version"),
		VERSION
	];
};


_fnc_scriptName = if (isnil "_fnc_scriptName") then {"Functions Init"} else {_fnc_scriptName};

private ["_this","_debug","_headerDefault","_fncCompile","_recompile"];

private _headerNoDebug = "
	private _fnc_scriptNameParent = if (isNil '_fnc_scriptName') then {'%1'} else {_fnc_scriptName};
	private _fnc_scriptName = '%1';
	scriptName _fnc_scriptName;
";
private _headerSaveScriptMap = "
	private _fnc_scriptMap = if (isNil '_fnc_scriptMap') then {[_fnc_scriptName]} else {_fnc_scriptMap + [_fnc_scriptName]};
";
private _headerLogScriptMap = "
	textLogFormat ['%1 : %2', _fnc_scriptMap joinString ' >> ', _this];
";
private _headerSystem = "
	private _fnc_scriptNameParent = if (isNil '_fnc_scriptName') then {'%1'} else {_fnc_scriptName};
	scriptName '%1';
";
private _headerNone = "";
private _debugHeaderExtended = "";
