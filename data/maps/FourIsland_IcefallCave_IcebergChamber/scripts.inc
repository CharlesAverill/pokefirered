FourIsland_IcefallCave_IcebergChamber_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, FourIsland_IcefallCave_IcebergChamber_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, FourIsland_IcefallCave_IcebergChamber_OnTransition
	.byte 0

FourIsland_IcefallCave_IcebergChamber_OnResume:
	call_if_set FLAG_SYS_SPECIAL_WILD_BATTLE, FourIsland_IcefallCave_IcebergChamber_TryRemoveRegice
	end

FourIsland_IcefallCave_IcebergChamber_OnTransition::
	call_if_set FLAG_FOUGHT_REGICE, FourIsland_IcefallCave_IcebergChamber_HideRegice
	call_if_unset FLAG_FOUGHT_REGICE, FourIsland_IcefallCave_IcebergChamber_TryShowRegice
	end

FourIsland_IcefallCave_IcebergChamber_HideRegice::
	setvar VAR_TEMP_1, 1
	setflag FLAG_HIDE_REGICE
	return

FourIsland_IcefallCave_IcebergChamber_TryShowRegice::
	setvar VAR_TEMP_1, 1
	goto_if_set FLAG_REGICE_DISAPPEARED, EventScript_Return
	setvar VAR_TEMP_1, 0
	clearflag FLAG_HIDE_REGICE
	return

FourIsland_IcefallCave_IcebergChamber_TryRemoveRegice::
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_ne EventScript_Return
	removeobject 1
	return

FourIsland_IcefallCave_IcebergChamber_Initiate_Regice_Battle::
    goto_if_questlog EventScript_ReleaseEnd
    special QuestLog_CutRecording
    lock
    faceplayer
    waitse
    message FourIsland_IcefallCave_IcebergChamber_Statue_Text
    waitmessage
    delay 20
    waitbuttonpress
    playmoncry SPECIES_REGICE, 2
    message FourIsland_IcefallCave_IcebergChamber_Text_Regice
    waitmessage
    waitmoncry
    delay 20
    playbgm MUS_ENCOUNTER_GYM_LEADER, 0
    waitbuttonpress
    setwildbattle SPECIES_REGICE, 80, ITEM_NONE
    setflag FLAG_SYS_SPECIAL_WILD_BATTLE
    special StartLegendaryBattle
    waitstate
    clearflag FLAG_SYS_SPECIAL_WILD_BATTLE
    specialvar VAR_RESULT, GetBattleOutcome
    compare VAR_RESULT, B_OUTCOME_WON
    goto_if_eq FourIsland_IcefallCave_IcebergChamber_DefeatedRegice
    compare VAR_RESULT, B_OUTCOME_RAN
    goto_if_eq FourIsland_IcefallCave_IcebergChamber_RanFromRegice
    compare VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED
    goto_if_eq FourIsland_IcefallCave_IcebergChamber_RanFromRegice
    setflag FLAG_FOUGHT_REGICE
    release
    end

FourIsland_IcefallCave_IcebergChamber_DefeatedRegice::
	setflag FLAG_REGICE_DISAPPEARED
	setvar VAR_0x8004, SPECIES_REGICE
	goto EventScript_MonDisappeared
	end

FourIsland_IcefallCave_IcebergChamber_RanFromRegice::
	setflag FLAG_REGICE_DISAPPEARED
	setvar VAR_0x8004, SPECIES_REGICE
	goto EventScript_MonDisappeared
	end

FourIsland_IcefallCave_IcebergChamber_Text_Regice:
    .string "Jakiih!$"

FourIsland_IcefallCave_IcebergChamber_Statue_Text:
    .string "The Pokemon statue that\n"
    .string "exudes the power of ice\l"
    .string "started moving!$"
