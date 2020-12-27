HemlockTown_MapScripts::
    map_script MAP_SCRIPT_ON_TRANSITION, HemlockTown_OnTransition
	.byte 0

HemlockTown_OnTransition::
    setworldmapflag FLAG_WORLD_MAP_HEMLOCK_TOWN
    end
