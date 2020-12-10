PalletTown_PlayersHouse_2F_MapScripts:: @ 8168CA3
	map_script MAP_SCRIPT_ON_TRANSITION, PalletTown_PlayersHouse_2F_OnTransition
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, PalletTown_PlayersHouse_2F_OnWarp
	.byte 0

PalletTown_PlayersHouse_2F_OnTransition:: @ 8168CAE
	compare VAR_MAP_SCENE_PALLET_TOWN_PLAYERS_HOUSE_2F, 0
	call_if_eq PalletTown_PlayersHouse_2F_EventScript_SetRespawn
	end

PalletTown_PlayersHouse_2F_EventScript_SetRespawn:: @ 8168CBA
	setrespawn SPAWN_PALLET_TOWN
	return

PalletTown_PlayersHouse_2F_OnWarp:: @ 8168CBE
	map_script_2 VAR_MAP_SCENE_PALLET_TOWN_PLAYERS_HOUSE_2F, 0, PalletTown_PlayersHouse_2F_FirstWarpIn
	.2byte 0

PalletTown_PlayersHouse_2F_FirstWarpIn:: @ 8168CC8
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
	setvar VAR_MAP_SCENE_PALLET_TOWN_PLAYERS_HOUSE_2F, 1
	end

PalletTown_PlayersHouse_2F_EventScript_NES:: @ 8168CD2
	msgbox PalletTown_PlayersHouse_2F_Text_PlayedWithNES, MSGBOX_SIGN
	end

PalletTown_PlayersHouse_2F_EventScript_Sign:: @ 8168CDB
	msgbox PalletTown_PlayersHouse_2F_Text_PressLRForHelp, MSGBOX_SIGN
	end

PalletTown_PlayersHouse_2F_EventScript_PC:: @ 8168CE4
	goto_if_questlog EventScript_ReleaseEnd
	lockall
	setvar VAR_0x8004, HELPCONTEXT_BEDROOM_PC
	special Script_SetHelpContext
	setvar VAR_0x8004, 1
	special AnimatePcTurnOn
	playse SE_PC_ON
	msgbox Text_PlayerBootedUpPC
	special BedroomPC
	waitstate
	special SetHelpContextForMap
	releaseall
	end

EventScript_PalletTown_PlayersHouse_2F_ShutDownPC:: @ 8168D17
	setvar VAR_0x8004, 1
	playse SE_PC_OFF
	special AnimatePcTurnOff
	special SetHelpContextForMap
	releaseall
	end

PalletTown_PlayersHouse_2F_CharlesMewBattle::
	lock
	faceplayer
	waitse
	getpartysize
	compare VAR_RESULT, 1
	goto_if_lt PalletTown_PlayersHouse_2F_CharlesMewBattle_2
	playmoncry SPECIES_MEW, 2
	msgbox PalletTown_PlayersHouse_2F_CharlesMewBattle_Text_1
	waitmessage
    waitmoncry
    delay 20
    playbgm MUS_ENCOUNTER_GYM_LEADER, 0
    waitbuttonpress
	setwildbattle SPECIES_MEW, 5, ITEM_NONE
	setflag FLAG_SYS_SPECIAL_WILD_BATTLE
	special StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_SPECIAL_WILD_BATTLE
	dowildbattle
	release
	end

PalletTown_PlayersHouse_2F_CharlesMewBattle_1:
	release
	end

PalletTown_PlayersHouse_2F_CharlesMewBattle_2:
	msgbox PalletTown_PlayersHouse_2F_CharlesMewBattle_Text_0
	goto PalletTown_PlayersHouse_2F_CharlesMewBattle_1


PalletTown_PlayersHouse_2F_CharlesMewBattle_Text_0:
	.string "You don't have any Pokemon!$"

PalletTown_PlayersHouse_2F_CharlesMewBattle_Text_1:
	.string "Get ready to fight my Mew!$"
