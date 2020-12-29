DiglettsCave_RockPeakChamber_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, DiglettsCave_RockPeakChamber_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, DiglettsCave_RockPeakChamber_OnTransition
	.byte 0

DiglettsCave_RockPeakChamber_OnResume:
	call_if_set FLAG_SYS_SPECIAL_WILD_BATTLE, DiglettsCave_RockPeakChamber_TryRemoveRegirock
	end

DiglettsCave_RockPeakChamber_OnTransition::
	call_if_set FLAG_FOUGHT_REGIROCK, DiglettsCave_RockPeakChamber_HideRegirock
	call_if_unset FLAG_FOUGHT_REGIROCK, DiglettsCave_RockPeakChamber_TryShowRegirock
	end

DiglettsCave_RockPeakChamber_HideRegirock::
	setvar VAR_TEMP_1, 1
	setflag FLAG_HIDE_REGIROCK
	return

DiglettsCave_RockPeakChamber_TryShowRegirock::
	setvar VAR_TEMP_1, 1
	goto_if_set FLAG_REGIROCK_DISAPPEARED, EventScript_Return
	setvar VAR_TEMP_1, 0
	clearflag FLAG_HIDE_REGIROCK
	return

DiglettsCave_RockPeakChamber_TryRemoveRegirock::
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_ne EventScript_Return
	removeobject 1
	return

DiglettsCave_RockPeakChamber_Initiate_Regirock_Battle::
    goto_if_questlog EventScript_ReleaseEnd
    special QuestLog_CutRecording
    lock
    faceplayer
    waitse
    message DiglettsCave_RockPeakChamber_Statue_Text
    waitmessage
    delay 20
    waitbuttonpress
    playmoncry SPECIES_REGIROCK, 2
    message DiglettsCave_RockPeakChamber_Text_Regirock
    waitmessage
    waitmoncry
    delay 20
    playbgm MUS_ENCOUNTER_GYM_LEADER, 0
    waitbuttonpress
    setwildbattle SPECIES_REGIROCK, 80, ITEM_NONE
    setflag FLAG_SYS_SPECIAL_WILD_BATTLE
    special StartLegendaryBattle
    waitstate
    clearflag FLAG_SYS_SPECIAL_WILD_BATTLE
    specialvar VAR_RESULT, GetBattleOutcome
    compare VAR_RESULT, B_OUTCOME_WON
    goto_if_eq DiglettsCave_RockPeakChamber_DefeatedRegirock
    compare VAR_RESULT, B_OUTCOME_RAN
    goto_if_eq DiglettsCave_RockPeakChamber_RanFromRegirock
    compare VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED
    goto_if_eq DiglettsCave_RockPeakChamber_RanFromRegirock
    setflag FLAG_FOUGHT_REGIROCK
    release
    end

DiglettsCave_RockPeakChamber_DefeatedRegirock::
	setflag FLAG_REGIROCK_DISAPPEARED
	setvar VAR_0x8004, SPECIES_REGIROCK
	goto EventScript_MonDisappeared
	end

DiglettsCave_RockPeakChamber_RanFromRegirock::
	setflag FLAG_REGIROCK_DISAPPEARED
	setvar VAR_0x8004, SPECIES_REGIROCK
	goto EventScript_MonDisappeared
	end

DiglettsCave_RockPeakChamber_Text_Regirock:
    .string "Zaza zari za...$"

DiglettsCave_RockPeakChamber_Statue_Text:
    .string "The Pokemon statue that\n"
    .string "exudes the power of rock\l"
    .string "started moving!$"
