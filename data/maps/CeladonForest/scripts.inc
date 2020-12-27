CeladonForest_MapScripts::
    map_script MAP_SCRIPT_ON_TRANSITION, CeladonForest_OnTransition
	.byte 0

CeladonForest_OnTransition::
    setworldmapflag FLAG_WORLD_MAP_CELADON_FOREST
    end
