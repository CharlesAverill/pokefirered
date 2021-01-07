SSAnne_Exterior_MapScripts:: @ 8160840
	map_script MAP_SCRIPT_ON_TRANSITION, SSAnne_Exterior_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SSAnne_Exterior_OnFrame
	.byte 0

SSAnne_Exterior_OnTransition:: @ 816084B
	setworldmapflag FLAG_WORLD_MAP_SSANNE_EXTERIOR
    call_if_unset FLAG_FOUGHT_MEW, SSAnne_Exterior_ShowMew
	end

SSAnne_Exterior_OnFrame:: @ 816084F
	map_script_2 VAR_MAP_SCENE_VERMILION_CITY, 1, SSAnne_Exterior_ExitSSAnne
	.2byte 0

SSAnne_Exterior_BlockSSAnne_Entrance::
    lock
    faceplayer
    msgbox SSAnne_Exterior_BlockSSAnne_Text
    release
    end

SSAnne_Exterior_ExitSSAnne:: @ 8160859
	lockall
	getplayerxy VAR_0x8004, VAR_0x8005
	compare VAR_0x8005, 6
	call_if_le SSAnne_Exterior_WalkDown
	compare VAR_0x8005, 7
	call_if_ge SSAnne_Exterior_WalkInPlaceDown
	fadenewbgm MUS_SURF
	delay 50
	special DoSSAnneDepartureCutscene
	waitstate
	removeobject 1
	applymovement OBJ_EVENT_ID_PLAYER, SSAnne_Exterior_Movement_Exit
	waitmovement 0
	setvar VAR_MAP_SCENE_VERMILION_CITY, 2
	setvar VAR_VERMILION_CITY_TICKET_CHECK_TRIGGER, 0
	clearflag FLAG_HIDE_SSANNE_BLOCKER
	warp MAP_VERMILION_CITY, 255, 23, 34
	waitstate
	releaseall
	end

SSAnne_Exterior_WalkDown:: @ 81608A1
	applymovement OBJ_EVENT_ID_PLAYER, SSAnne_Exterior_Movement_WalkDown
	waitmovement 0
	return

SSAnne_Exterior_WalkInPlaceDown:: @ 81608AC
	applymovement OBJ_EVENT_ID_PLAYER, Movement_WalkInPlaceFastestDown
	waitmovement 0
	return

SSAnne_Exterior_Movement_Exit:: @ 81608B7
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

SSAnne_Exterior_Movement_WalkDown:: @ 81608C1
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

SSAnne_Exterior_MewTruck::
    goto_if_questlog EventScript_ReleaseEnd

    goto_if_set FLAG_FOUGHT_MEW, SSAnne_Exterior_MewTruck_DefeatedMew_Or_DidNotUseStrength
    goto_if_set FLAG_HIDE_MEW, SSAnne_Exterior_MewTruck_DefeatedMew_Or_DidNotUseStrength
    goto_if_questlog EventScript_ReleaseEnd
    lockall
    goto_if_unset FLAG_BADGE04_GET, SSAnne_Exterior_MewTruck_DefeatedMew_Or_DidNotUseStrength
    goto_if_unset FLAG_GOT_HM06 SSAnne_Exterior_MewTruck_DefeatedMew_Or_DidNotUseStrength
    msgbox SSAnne_Exterior_MewTruck_StrengthText, MSGBOX_YESNO
    compare VAR_RESULT, NO
    goto_if_eq SSAnne_Exterior_MewTruck_DefeatedMew_Or_DidNotUseStrength
    closemessage

    waitse
    playmoncry SPECIES_MEW, 2
    message SSAnne_Exterior_MewTruck_MewText
    waitmessage
    waitmoncry
    delay 20
    playbgm MUS_ENCOUNTER_GYM_LEADER, 0
    waitbuttonpress
    setwildbattle SPECIES_MEW, 40, ITEM_NONE
    setflag FLAG_SYS_SPECIAL_WILD_BATTLE
    special StartLegendaryBattle
    waitstate
    clearflag FLAG_SYS_SPECIAL_WILD_BATTLE
    specialvar VAR_RESULT, GetBattleOutcome
    compare VAR_RESULT, B_OUTCOME_WON
    goto_if_eq SSAnne_Exterior_MewTruck_DefeatedMew
    compare VAR_RESULT, B_OUTCOME_CAUGHT
    goto_if_eq SSAnne_Exterior_MewTruck_DefeatedMew
    compare VAR_RESULT, B_OUTCOME_RAN
    goto_if_eq SSAnne_Exterior_MewTruck_RanFromMew
    compare VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED
    goto_if_eq SSAnne_Exterior_MewTruck_RanFromMew
    setflag FLAG_FOUGHT_MEWTWO
    release
    end

SSAnne_Exterior_MewTruck_DefeatedMew_Or_DidNotUseStrength:
    release
    end

SSAnne_Exterior_MewTruck_DefeatedMew:: @ 8162558
    setflag FLAG_FOUGHT_MEW
    setflag FLAG_HIDE_MEW
    removeobject 2
    end

SSAnne_Exterior_MewTruck_RanFromMew:: @ 8162561
    setflag FLAG_HIDE_MEW
    setvar VAR_0x8004, SPECIES_MEW
    goto EventScript_MonFlewAway
    end

SSAnne_Exterior_BlockSSAnne_Text::
    .string "Looks like the S.S. Anne is\n"
    .string "gone for good!$"

SSAnne_Exterior_MewTruck_StrengthText:
    .string "The truck seems to be rustling.\n"
    .string "Summon Arcanine to use Strength?$"

SSAnne_Exterior_MewTruck_MewText:
    .string "Mew!$"

SSAnne_Exterior_ShowMew:
    clearflag FLAG_HIDE_MEW
    return
