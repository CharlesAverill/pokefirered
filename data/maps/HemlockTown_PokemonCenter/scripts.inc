HemlockTown_PokemonCenter_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, HemlockTown_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

HemlockTown_PokemonCenter_1F_OnTransition::
	setrespawn SPAWN_HEMLOCK_TOWN
	end

HemlockTown_PokemonCenter_1F_EventScript_Nurse::
	lock
	faceplayer
	call EventScript_PkmnCenterNurse
	release
	end