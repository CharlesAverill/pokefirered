MtSilver_1F_MapScripts::
    map_script MAP_SCRIPT_ON_TRANSITION, MtSilver_1F_OnTransition
	.byte 0

MtSilver_1F_OnTransition::
    setworldmapflag FLAG_WORLD_MAP_MT_SILVER
    end