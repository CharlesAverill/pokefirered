CinnabarIsland_Cinnabar_Volcano_B1F_MapScripts::
    map_script MAP_SCRIPT_ON_TRANSITION, CinnabarIsland_Cinnabar_Volcano_B1F_OnTransition
	.byte 0

CinnabarIsland_Cinnabar_Volcano_B1F_OnTransition::
    setworldmapflag FLAG_WORLD_MAP_CINNABAR_VOLCANO
    goto_if_set FLAG_FOUGHT_GROUDON, CinnabarIsland_Cinnabar_Volcano_SetFlash
    end
