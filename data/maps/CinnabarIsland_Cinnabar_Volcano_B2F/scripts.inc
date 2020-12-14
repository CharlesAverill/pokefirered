CinnabarIsland_Cinnabar_Volcano_B2F_MapScripts::
	.byte 0

CinnabarIsland_Cinnabar_Volcano_B2F_Approach_Groudon::
    goto_if_set FLAG_SYS_FLASH_ACTIVE, CinnabarIsland_Cinnabar_Volcano_B2F_end
    goto_if_set FLAG_FOUGHT_GROUDON, CinnabarIsland_Cinnabar_Volcano_B2F_end
    lockall
    animateflash 0
	setflashradius 0
	setflag FLAG_SYS_FLASH_ACTIVE
	applymovement OBJ_EVENT_ID_PLAYER, Movement_Meet_Groudon
	waitmovement 0
	applymovement 1, Movement_Groudon
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
	setflag FLAG_FOUGHT_MEWTWO
	goto EventScript_RemoveStaticMon
	end

CinnabarIsland_Cinnabar_Volcano_B2F_RanFromGroudon:: @ 8162561
	setvar VAR_0x8004, SPECIES_MEWTWO
	goto EventScript_MonFlewAway
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