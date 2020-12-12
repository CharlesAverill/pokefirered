FiveIsland_Meadow_MapScripts:: @ 8168932
	map_script MAP_SCRIPT_ON_LOAD, FiveIsland_Meadow_OnLoad
	.byte 0

FiveIsland_Meadow_OnLoad:: @ 8168938
	call_if_set FLAG_UNLOCKED_ROCKET_WAREHOUSE, FiveIsland_Meadow_EventScript_SetWarehouseDoorUnlocked
	end

FiveIsland_Meadow_EventScript_WarehouseDoor:: @ 8168942
	lockall
	goto_if_set FLAG_UNLOCKED_ROCKET_WAREHOUSE, FiveIsland_Meadow_EventScript_WarehouseDoorAlreadyOpen
	goto_if_set FLAG_LEARNED_YES_NAH_CHANSEY, FiveIsland_Meadow_EventScript_OpenWarehouseDoor
	msgbox FiveIsland_Meadow_Text_EnteredPasswordAnotherNeeded
	releaseall
	end

FiveIsland_Meadow_EventScript_OpenWarehouseDoor:: @ 816895F
	setflag FLAG_UNLOCKED_ROCKET_WAREHOUSE
	message FiveIsland_Meadow_Text_EnteredPasswordDoorOpened
	waitmessage
	delay 60
	call FiveIsland_Meadow_EventScript_SetWarehouseDoorUnlocked
	special DrawWholeMapView
	playse SE_PIN
	waitse
	releaseall
	end

FiveIsland_Meadow_EventScript_WarehouseDoorAlreadyOpen:: @ 8168979
	msgbox FiveIsland_Meadow_Text_WarehouseDoorAlreadyOpen
	releaseall
	end

FiveIsland_Meadow_EventScript_SetWarehouseDoorUnlocked:: @ 8168983
	setmetatile 12, 21, METATILE_SeviiIslands45_RocketWarehouseDoor_Unlocked, 1
	return

FiveIsland_Meadow_EventScript_Rocket1:: @ 816898D
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT_49, FiveIsland_Meadow_Text_Rocket1Intro, FiveIsland_Meadow_Text_Rocket1Defeat
	msgbox FiveIsland_Meadow_Text_Rocket1PostBattle, MSGBOX_AUTOCLOSE
	end

FiveIsland_Meadow_EventScript_Rocket2:: @ 81689A4
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT_50, FiveIsland_Meadow_Text_Rocket2Intro, FiveIsland_Meadow_Text_Rocket2Defeat
	msgbox FiveIsland_Meadow_Text_Rocket2PostBattle, MSGBOX_AUTOCLOSE
	end

FiveIsland_Meadow_EventScript_Rocket3:: @ 81689BB
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT_51, FiveIsland_Meadow_Text_Rocket3Intro, FiveIsland_Meadow_Text_Rocket3Defeat
	msgbox FiveIsland_Meadow_Text_Rocket3PostBattle, MSGBOX_AUTOCLOSE
	end

FiveIsland_Meadow_EventScript_SailorSolomon::
	lock
	goto_if_set FLAG_FOUGHT_LUGIA, FiveIsland_Lugia_Fought
	goto_if_set FLAG_FOUGHT_HO_OH, FiveIsland_HoOh_Fought
	goto_if_set FLAG_LUGIA_FLEW_AWAY, FiveIsland_Lugia_Fought
	goto_if_set FLAG_HO_OH_FLEW_AWAY, FiveIsland_HoOh_Fought
	checkitem ITEM_MYSTIC_TICKET, 1
	compare VAR_RESULT, TRUE
	goto_if_eq FiveIsland_Neither_Fought
	goto_if_set FLAG_GOT_MYSTIC_TICKET, FiveIsland_Neither_Fought
	msgbox FiveIsland_Meadow_SailorSolomon_Text_0, MSGBOX_YESNO
    msgbox FiveIsland_Meadow_SailorSolomon_Text_1
	waitmessage
	waitbuttonpress
    faceplayer
    msgbox FiveIsland_Meadow_SailorSolomon_Text_2
	waitmessage
	waitbuttonpress
    msgbox FiveIsland_Meadow_SailorSolomon_Text_3
	waitmessage
	waitbuttonpress
    msgbox FiveIsland_Meadow_SailorSolomon_Text_4
	waitmessage
	waitbuttonpress
	checkitemspace ITEM_MYSTIC_TICKET, 1
	compare VAR_RESULT, FALSE
	goto_if_eq MysticTicket_NoBagSpace
	giveitem ITEM_MYSTIC_TICKET
	setflag FLAG_ENABLE_SHIP_NAVEL_ROCK
	setflag FLAG_GOT_MYSTIC_TICKET
	release
	end

MysticTicket_NoBagSpace: @ 84896ED
	message sText_MysticTicketNoPlace
	waitmessage
	waitbuttonpress
	release
	end

FiveIsland_Neither_Fought:
	msgbox FiveIsland_Neither_Fought_Text
	waitmessage
	waitbuttonpress
	release
	end

FiveIsland_Lugia_Fought:
	goto_if_set FLAG_FOUGHT_HO_OH, FiveIsland_BothLegendaryBirds_Fought
    goto_if_set FLAG_HO_OH_FLEW_AWAY, FiveIsland_BothLegendaryBirds_Fought
	msgbox FiveIsland_Lugia_Fought_Text
	waitmessage
	waitbuttonpress
	release
	end

FiveIsland_HoOh_Fought:
    goto_if_set FLAG_FOUGHT_LUGIA, FiveIsland_BothLegendaryBirds_Fought
    goto_if_set FLAG_LUGIA_FLEW_AWAY, FiveIsland_BothLegendaryBirds_Fought
    msgbox FiveIsland_HoOh_Fought_Text
	waitmessage
	waitbuttonpress
    release
    end

FiveIsland_BothLegendaryBirds_Fought:
	msgbox FiveIsland_BothLegendaryBirds_Fought_Text
	waitmessage
	waitbuttonpress
	release
	end
