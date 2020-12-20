DragonGateCavern_IronChamber_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, DragonGateCavern_IronChamber_OnResume
	.byte 0

DragonGateCavern_IronChamber_OnResume:
	call_if_set FLAG_SYS_SPECIAL_WILD_BATTLE, DragonGateCavern_IronChamber_TryRemoveRegisteel
	end

DragonGateCavern_IronChamber_TryRemoveRegisteel:
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_ne EventScript_Return
	removeobject VAR_LAST_TALKED
	return

DragonGateCavern_IronChamber_Initiate_Registeel_Battle::
    goto_if_questlog EventScript_ReleaseEnd
    special QuestLog_CutRecording
    lock
    faceplayer
    waitse
    message DragonGateCavern_IronChamber_Statue_Text
    waitmessage
    delay 20
    waitbuttonpress
    playmoncry SPECIES_REGISTEEL, 2
    message DragonGateCavern_IronChamber_Text_Registeel
    waitmessage
    waitmoncry
    delay 20
    playbgm MUS_ENCOUNTER_GYM_LEADER, 0
    waitbuttonpress
    setwildbattle SPECIES_REGISTEEL, 80, ITEM_NONE
    setflag FLAG_SYS_SPECIAL_WILD_BATTLE
    special StartLegendaryBattle
    waitstate
    clearflag FLAG_SYS_SPECIAL_WILD_BATTLE
    specialvar VAR_RESULT, GetBattleOutcome
    compare VAR_RESULT, B_OUTCOME_WON
    goto_if_eq DragonGateCavern_IronChamber_DefeatedRegisteel
    compare VAR_RESULT, B_OUTCOME_RAN
    goto_if_eq DragonGateCavern_IronChamber_RanFromRegisteel
    compare VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED
    goto_if_eq DragonGateCavern_IronChamber_RanFromRegisteel
    setflag FLAG_FOUGHT_REGISTEEL
    release
    end

DragonGateCavern_IronChamber_DefeatedRegisteel:
	setflag FLAG_FOUGHT_REGISTEEL
	goto EventScript_RemoveStaticMon
	end

DragonGateCavern_IronChamber_RanFromRegisteel:
	setvar VAR_0x8004, SPECIES_REGISTEEL
	goto EventScript_MonDisappeared
	end

DragonGateCavern_IronChamber_Text_Registeel:
    .string "Ji-ji-ze-ji-zoh...$"

DragonGateCavern_IronChamber_Statue_Text:
    .string "The Pokemon statue that\n"
    .string "exudes the power of steel\l"
    .string "started moving!$"