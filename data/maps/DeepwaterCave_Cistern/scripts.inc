DeepwaterCave_Cistern_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, DeepwaterCave_Cistern_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, DeepwaterCave_Cistern_OnTransition
	.byte 0

DeepwaterCave_Cistern_OnTransition::
	call_if_set FLAG_FOUGHT_KYOGRE, DeepwaterCave_Cistern_EventScript_HideKyogre
	call_if_unset FLAG_FOUGHT_KYOGRE, DeepwaterCave_Cistern_EventScript_TryShowKyogre
	clearflag FLAG_TEMP_2
	end

DeepwaterCave_Cistern_EventScript_HideKyogre::
	setvar VAR_TEMP_1, 1
	setflag FLAG_HIDE_KYOGRE
	return

DeepwaterCave_Cistern_EventScript_TryShowKyogre::
	setvar VAR_TEMP_1, 1
	goto_if_set FLAG_KYOGRE_DISAPPEARED, EventScript_Return
	setvar VAR_TEMP_1, 0
	clearflag FLAG_HIDE_KYOGRE
	return

DeepwaterCave_Cistern_OnResume:
	call_if_set FLAG_SYS_SPECIAL_WILD_BATTLE, DeepwaterCave_Cistern_EventScript_TryRemoveKyogre
	end

DeepwaterCave_Cistern_EventScript_TryRemoveKyogre::
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_ne EventScript_Return
	removeobject 1
	return

DeepwaterCave_Cistern_Approach_Kyogre::
    goto_if_set FLAG_TEMP_2, DeepwaterCave_Cistern_end
    goto_if_set FLAG_FOUGHT_KYOGRE, DeepwaterCave_Cistern_end
    lockall
    setflag FLAG_TEMP_2
	applymovement 1, Movement_Kyogre
    waitmovement 0
	releaseall
	end

DeepwaterCave_Cistern_Initiate_Kyogre_Battle::
    goto_if_questlog EventScript_ReleaseEnd
    special QuestLog_CutRecording
    lock
    faceplayer
    waitse
    playmoncry SPECIES_KYOGRE, 2
    message DeepwaterCave_Cistern_Text_Kyogre
    waitmessage
    waitmoncry
    delay 20
    playbgm MUS_ENCOUNTER_GYM_LEADER, 0
    waitbuttonpress
    setwildbattle SPECIES_KYOGRE, 80, ITEM_NONE
    setflag FLAG_SYS_SPECIAL_WILD_BATTLE
    special StartLegendaryBattle
    waitstate
    clearflag FLAG_SYS_SPECIAL_WILD_BATTLE
    specialvar VAR_RESULT, GetBattleOutcome
    compare VAR_RESULT, B_OUTCOME_WON
    goto_if_eq DeepwaterCave_Cistern_DefeatedKyogre
    compare VAR_RESULT, B_OUTCOME_RAN
    goto_if_eq DeepwaterCave_Cistern_RanFromKyogre
    compare VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED
    goto_if_eq DeepwaterCave_Cistern_RanFromKyogre
    setflag FLAG_FOUGHT_KYOGRE
    release
    end

DeepwaterCave_Cistern_DefeatedKyogre::
	setflag FLAG_KYOGRE_DISAPPEARED
    clearflag FLAG_DWC_ROCK
	setvar VAR_0x8004, SPECIES_KYOGRE
	goto EventScript_MonDisappeared
	end

DeepwaterCave_Cistern_RanFromKyogre::
	setflag FLAG_KYOGRE_DISAPPEARED
    clearflag FLAG_DWC_ROCK
	setvar VAR_0x8004, SPECIES_KYOGRE
	goto EventScript_MonDisappeared
	end

DeepwaterCave_Cistern_Text_Kyogre:
    .string "Gyararoooah!$"

DeepwaterCave_Cistern_end:
    releaseall
    end

Movement_Kyogre:
    walk_in_place_slow_down
    delay_16
    delay_16
    walk_slowest_down
    delay_16
    delay_16
    walk_slowest_down
    delay_16
    delay_16
    step_end
