CinnabarIsland_Cinnabar_Volcano_B2F_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, CinnabarIsland_Cinnabar_Volcano_B2F_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, CinnabarIsland_Cinnabar_Volcano_B2F_OnTransition
	.byte 0

CinnabarIsland_Cinnabar_Volcano_B2F_OnTransition:
	call_if_unset FLAG_FOUGHT_GROUDON, CinnabarIsland_Cinnabar_Volcano_B2F_EventScript_GroudonNotBattled
	end

CinnabarIsland_Cinnabar_Volcano_B2F_EventScript_GroudonNotBattled:
    clearflag FLAG_SYS_FLASH_ACTIVE
    clearflag FLAG_DONT_LEAVE_LEGEND_YET

CinnabarIsland_Cinnabar_Volcano_B2F_OnResume:
	call_if_set FLAG_SYS_SPECIAL_WILD_BATTLE, CinnabarIsland_Cinnabar_Volcano_B2F_TryRemoveGroudon
	end

CinnabarIsland_Cinnabar_Volcano_B2F_TryRemoveGroudon:
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_ne EventScript_Return
	removeobject VAR_LAST_TALKED
	setflag FLAG_FOUGHT_GROUDON
	clearflag FLAG_DONT_LEAVE_LEGEND_YET
	return

CinnabarIsland_Cinnabar_Volcano_B2F_Approach_Groudon::
    /*goto_if_set FLAG_DONT_LEAVE_LEGEND_YET, CinnabarIsland_Cinnabar_Volcano_B2F_Move_Player*/
    goto_if_set FLAG_SYS_FLASH_ACTIVE, CinnabarIsland_Cinnabar_Volcano_B2F_end
    goto_if_set FLAG_FOUGHT_GROUDON, CinnabarIsland_Cinnabar_Volcano_B2F_end
    lockall
    call CinnabarIsland_Cinnabar_Volcano_SetFlash
	applymovement OBJ_EVENT_ID_PLAYER, Movement_Meet_Groudon
	waitmovement 0
	applymovement 1, Movement_Groudon
    waitmovement 0
    setflag FLAG_DONT_LEAVE_LEGEND_YET
	releaseall
	end

CinnabarIsland_Cinnabar_Volcano_SetFlash::
    goto_if_set FLAG_SYS_FLASH_ACTIVE, CinnabarIsland_Cinnabar_Volcano_B2F_end
    animateflash 0
	setflashradius 0
	setflag FLAG_SYS_FLASH_ACTIVE
	return

CinnabarIsland_Cinnabar_Volcano_B2F_Move_Player:
    lockall
	applymovement OBJ_EVENT_ID_PLAYER, Movement_Meet_Groudon
	waitmovement 0
	releaseall
	end

CinnabarIsland_Cinnabar_Volcano_B2F_Initiate_Groudon_Battle::
    goto_if_questlog EventScript_ReleaseEnd
    special QuestLog_CutRecording
    lock
    faceplayer
    waitse
    playmoncry SPECIES_GROUDON, 2
    message CinnabarIsland_Cinnabar_Volcano_B2F_Text_Groudon
    waitmessage
    waitmoncry
    delay 20
    playbgm MUS_ENCOUNTER_GYM_LEADER, 0
    waitbuttonpress
    setwildbattle SPECIES_GROUDON, 80, ITEM_NONE
    setflag FLAG_SYS_SPECIAL_WILD_BATTLE
    special StartLegendaryBattle
    waitstate
    clearflag FLAG_SYS_SPECIAL_WILD_BATTLE
    specialvar VAR_RESULT, GetBattleOutcome
    compare VAR_RESULT, B_OUTCOME_WON
    goto_if_eq CinnabarIsland_Cinnabar_Volcano_B2F_DefeatedGroudon
    compare VAR_RESULT, B_OUTCOME_RAN
    goto_if_eq CinnabarIsland_Cinnabar_Volcano_B2F_RanFromGroudon
    compare VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED
    goto_if_eq CinnabarIsland_Cinnabar_Volcano_B2F_RanFromGroudon
    setflag FLAG_FOUGHT_GROUDON
    release
    end

CinnabarIsland_Cinnabar_Volcano_B2F_DefeatedGroudon:: @ 8162558
	setflag FLAG_FOUGHT_GROUDON
    clearflag FLAG_DONT_LEAVE_LEGEND_YET
	goto EventScript_RemoveStaticMon
	end

CinnabarIsland_Cinnabar_Volcano_B2F_RanFromGroudon:: @ 8162561
	setvar VAR_0x8004, SPECIES_GROUDON
    clearflag FLAG_DONT_LEAVE_LEGEND_YET
	goto EventScript_MonDisappeared
	end

CinnabarIsland_Cinnabar_Volcano_B2F_Text_Groudon:
    .string "Grrgggrrrrah!$"

CinnabarIsland_Cinnabar_Volcano_B2F_end:
    releaseall
    end

Movement_Meet_Groudon:
    walk_slow_right
    walk_slow_right
    walk_slow_right
    walk_slow_right
    walk_slow_right
    walk_slow_right
    walk_slow_right
    walk_slow_right
    face_up
    delay_16
    delay_16
    delay_16
    step_end

Movement_Walk_Right:
    walk_right
    step_end

Movement_Groudon:
    walk_in_place_slow_down
    delay_16
    delay_16
    walk_slowest_down
    delay_16
    delay_16
    walk_slowest_down
    delay_16
    delay_16
    walk_slowest_down
    delay_16
    delay_16
    step_end
