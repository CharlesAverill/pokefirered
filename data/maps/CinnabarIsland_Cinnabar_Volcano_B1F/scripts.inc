CinnabarIsland_Cinnabar_Volcano_B1F_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, CinnabarIsland_Cinnabar_Volcano_B1F_OnResume
    map_script MAP_SCRIPT_ON_TRANSITION, CinnabarIsland_Cinnabar_Volcano_B1F_OnTransition
	.byte 0

CinnabarIsland_Cinnabar_Volcano_B1F_OnTransition::
    clearflag FLAG_SYS_FLASH_ACTIVE
    setworldmapflag FLAG_WORLD_MAP_CINNABAR_VOLCANO
    end

CinnabarIsland_Cinnabar_Volcano_B1F_OnResume:
    clearflag FLAG_SYS_FLASH_ACTIVE
	end
