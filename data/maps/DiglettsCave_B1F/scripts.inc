DiglettsCave_B1F_MapScripts:: @ 8160EF1
	map_script MAP_SCRIPT_ON_TRANSITION, DiglettsCave_B1F_OnTransition
	.byte 0

DiglettsCave_B1F_OnTransition:: @ 8160EF7
	setworldmapflag FLAG_WORLD_MAP_DIGLETTS_CAVE_B1F
	end

DiglettsCave_B1F_EventScript_ClawFossil::
    removeobject 1
    giveitem_msg DiglettsCave_B1F_EventScript_ClawFossil_Text, ITEM_CLAW_FOSSIL, 1, MUS_OBTAIN_KEY_ITEM
    closemessage
    setflag FLAG_HIDE_CLAW_FOSSIL
    end

DiglettsCave_B1F_EventScript_ClawFossil_Text:
    .string "Obtained the CLAW FOSSIL!$"
