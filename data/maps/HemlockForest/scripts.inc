HemlockForest_MapScripts::
    map_script MAP_SCRIPT_ON_TRANSITION, HemlockForest_OnTransition
    map_script MAP_SCRIPT_ON_RESUME, HemlockForest_OnResume
	.byte 0

HemlockForest_OnTransition::
    goto HemlockForest_HideCelebi
    end

HemlockForest_HideCelebi::
    applymovement 1, Movement_SetInvisible
    end

HemlockForest_OnResume::
	call_if_set FLAG_SYS_SPECIAL_WILD_BATTLE, HemlockForest_EventScript_TryRemoveCelebi
	end

HemlockForest_EventScript_TryRemoveCelebi::
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_ne EventScript_Return
	removeobject 1
	return

HemlockForest_EventScript_Celebi::
	goto_if_questlog EventScript_ReleaseEnd
	goto_if_unset FLAG_IS_CHAMPION, EventScript_ReleaseEnd
	goto_if_unset FLAG_FOUGHT_CELEBI, EventScript_ReleaseEnd
	goto_if_unset FLAG_CELEBI_FLEW_AWAY, EventScript_ReleaseEnd
	special QuestLog_CutRecording
	lockall
	setvar VAR_TEMP_1, 1
	special SpawnCameraObject
	setvar VAR_0x8004, 3  @ Num loops
	setvar VAR_0x8005, 35 @ Delay
	special LoopWingFlapSound
    setobjectxyperm 1, 30, 53
    applymovement 1, Movement_SetVisible
	applymovement OBJ_EVENT_ID_PLAYER, Movement_FaceUp
	applymovement 1, Movement_HoOhAppear
	applymovement OBJ_EVENT_ID_CAMERA, Movement_CameraPanUp
	waitmovement 0
	delay 50
	setweather 0
	doweather
	waitse
	playmoncry SPECIES_CELEBI, 2
	delay 30
	waitmoncry
	delay 60
	setvar VAR_0x8004, 3  @ Num loops
	setvar VAR_0x8005, 35 @ Delay
	special LoopWingFlapSound
	applymovement OBJ_EVENT_ID_CAMERA, Movement_CameraPanDown
	applymovement 1, Movement_HoOhApproach
	waitmovement 0
	special RemoveCameraObject
	setvar VAR_0x8004, SPECIES_CELEBI
	setvar VAR_0x8005, 70  @ Level
	setvar VAR_0x8006, ITEM_NONE
	special CreateObedientEnemyMon
	setflag FLAG_SYS_SPECIAL_WILD_BATTLE
	special StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_SPECIAL_WILD_BATTLE
	setvar VAR_LAST_TALKED, 1
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq HemlockForest_EventScript_DefeatedCelebi
	compare VAR_RESULT, B_OUTCOME_RAN
	goto_if_eq HemlockForest_EventScript_RanFromCelebi
	compare VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED
	goto_if_eq HemlockForest_EventScript_RanFromCelebi
	setflag FLAG_FOUGHT_CELEBI
	releaseall
	end

HemlockForest_EventScript_DefeatedCelebi::
	setflag FLAG_CELEBI_FLEW_AWAY
	setvar VAR_0x8004, SPECIES_CELEBI
	goto EventScript_MonFlewAway
	end

HemlockForest_EventScript_RanFromCelebi::
	setflag FLAG_CELEBI_FLEW_AWAY
	setvar VAR_0x8004, SPECIES_CELEBI
	goto EventScript_MonFlewAway
	end

Movement_FaceUp::
    face_up
    step_end

Movement_SetVisible::
    set_visible
    step_end
