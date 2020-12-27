DeepwaterCave_1F_MapScripts::
    map_script MAP_SCRIPT_ON_TRANSITION, DeepwaterCave_1F_OnTransition
	.byte 0

DeepwaterCave_1F_OnTransition::
    setworldmapflag FLAG_WORLD_MAP_DEEPWATER_CAVE
    end