PalletTown_PlayersHouse_1F_MapScripts:: @ 8168C08
	.byte 0

PalletTown_PlayersHouse_1F_EventScript_Mom:: @ 8168C09
	lock
	faceplayer
	goto_if_set FLAG_BEAT_RIVAL_IN_OAKS_LAB, PalletTown_PlayersHouse_1F_EventScript_MomHeal
	checkplayergender
	compare VAR_RESULT, MALE
	call_if_eq PalletTown_PlayersHouse_1F_EventScript_MomOakLookingForYouMale
	compare VAR_RESULT, FEMALE
	call_if_eq PalletTown_PlayersHouse_1F_EventScript_MomOakLookingForYouFemale
	closemessage
	applymovement 1, Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

PalletTown_PlayersHouse_1F_EventScript_MomOakLookingForYouMale:: @ 8168C38
	msgbox PalletTown_PlayersHouse_1F_Text_AllBoysLeaveOakLookingForYou
	return

PalletTown_PlayersHouse_1F_EventScript_MomOakLookingForYouFemale:: @ 8168C41
	msgbox PalletTown_PlayersHouse_1F_Text_AllGirlsLeaveOakLookingForYou
	return

PalletTown_PlayersHouse_1F_EventScript_MomHeal:: @ 8168C4A
	msgbox PalletTown_PlayersHouse_1F_Text_YouShouldTakeQuickRest
	closemessage
	call EventScript_OutOfCenterPartyHeal
	msgbox PalletTown_PlayersHouse_1F_Text_LookingGreatTakeCare
	release
	end

@ Displays special text if interacted with from side or back (which are normally inaccessible)
PalletTown_PlayersHouse_1F_EventScript_TV:: @ 8168C62
	lockall
	compare VAR_FACING, DIR_NORTH
	goto_if_eq PalletTown_PlayersHouse_1F_EventScript_TVScreen
	msgbox PalletTown_PlayersHouse_1F_Text_OopsWrongSide
	releaseall
	end

PalletTown_PlayersHouse_1F_EventScript_TVScreen:: @ 8168C78
	checkplayergender
	compare VAR_RESULT, MALE
	call_if_eq PalletTown_PlayersHouse_1F_EventScript_TVScreenMale
	compare VAR_RESULT, FEMALE
	call_if_eq PalletTown_PlayersHouse_1F_EventScript_TVScreenFemale
	releaseall
	end

PalletTown_PlayersHouse_1F_EventScript_TVScreenMale:: @ 8168C91
	msgbox PalletTown_PlayersHouse_1F_Text_MovieOnTVFourBoysOnRailroad
	return

PalletTown_PlayersHouse_1F_EventScript_TVScreenFemale:: @ 8168C9A
	msgbox PalletTown_PlayersHouse_1F_Text_MovieOnTVGirlOnBrickRoad
	return

PalletTown_PlayersHouse_1F_EventScript_MomShoes::
	setvar VAR_TEMP_0, 1
	goto_if_unset FLAG_HIDE_PEWTER_CITY_RUNNING_SHOES_GUY, EventScript_Return
	clearflag FLAG_HIDE_PEWTER_CITY_RUNNING_SHOES_GUY
	textcolor 1
	lock
	applymovement 1, Movement_FaceDown
	waitmovement 0
	playse SE_PIN
	msgbox MomSaysWait
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Movement_GiveShoes_Mom
	waitmovement 0
	msgbox MomOffersShoes
	closemessage
	textcolor 3
	playfanfare MUS_OBTAIN_KEY_ITEM
	message PlayerGotShoes
	waitmessage
	waitfanfare
	msgbox PewterCity_Text_SwitchedShoesWithRunningShoes
	closemessage
	textcolor 1
	msgbox MomSaysGoodLuck
	closemessage
	applymovement 1, Movement_FaceLeft
	waitmovement 0
	setflag FLAG_SYS_B_DASH
	release
	end

MomSaysWait::
	.string "MOM: {PLAYER}!\n"
	.string "Wait up!$"

MomOffersShoes::
	.string "MOM: Before you go, I got you\n"
	.string "these nice RUNNING SHOES!\p"
	.string "Why don't you try them on?$"

PlayerGotShoes:: 
    .string "{PLAYER} received the\n"
    .string "RUNNING SHOES from MOM.$"

MomSaysGoodLuck::
	.string "Be safe {PLAYER}!$"

Movement_GiveShoes_Mom::
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_up
	walk_up
	step_end
