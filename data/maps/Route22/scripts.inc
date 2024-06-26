Route22_MapScripts::
    map_script MAP_SCRIPT_ON_TRANSITION, Transition_Route22
    .byte 0

Transition_Route22::
    setflag FLAG_VISITED_ROUTE_22
	end

Route22_EventScript_EarlyRivalTriggerTop:: @ 816828C
	lockall
	setvar VAR_TEMP_1, 0
	goto Route22_EventScript_EarlyRival
	end

Route22_EventScript_EarlyRivalTriggerMid:: @ 8168298
	lockall
	setvar VAR_TEMP_1, 1
	setobjectxyperm 1, 25, 8
	goto Route22_EventScript_EarlyRival
	end

Route22_EventScript_EarlyRivalTriggerBottom:: @ 81682AB
	lockall
	setvar VAR_TEMP_1, 2
	setobjectxyperm 1, 25, 8
	goto Route22_EventScript_EarlyRival
	end

Route22_EventScript_EarlyRival:: @ 81682BE
	textcolor 0
	playbgm MUS_ENCOUNTER_RIVAL, 0
	addobject 1
	compare VAR_TEMP_1, 0
	call_if_eq Route22_Movement_RivalApproachTop
	compare VAR_TEMP_1, 1
	call_if_eq Route22_Movement_RivalApproachMid
	compare VAR_TEMP_1, 2
	call_if_eq Route22_Movement_RivalApproachBottom
	delay 6
	msgbox Route22_Text_EarlyRivalIntro
	compare VAR_STARTER_MON, 2
	call_if_eq Route22_EventScript_EarlyRivalSquirtle
	compare VAR_STARTER_MON, 1
	call_if_eq Route22_EventScript_EarlyRivalBulbasaur
	compare VAR_STARTER_MON, 0
	call_if_eq Route22_EventScript_EarlyRivalCharmander
	msgbox Route22_Text_EarlyRivalPostBattle
	closemessage
	delay 10
	playbgm MUS_RIVAL_EXIT, 0
	compare VAR_TEMP_1, 0
	call_if_eq Route22_EventScript_EarlyRivalExit
	compare VAR_TEMP_1, 1
	call_if_eq Route22_EventScript_EarlyRivalExit
	compare VAR_TEMP_1, 2
	call_if_eq Route22_EventScript_EarlyRivalExitBottom
	fadedefaultbgm
	removeobject 1
	setvar VAR_MAP_SCENE_ROUTE22, 2
	releaseall
	end

Route22_EventScript_EarlyRivalApproachBottom:: @ 816835B
	applymovement 1, Route22_Movement_RivalApproachBottom
	applymovement OBJ_EVENT_ID_PLAYER, Route22_Movement_PlayerFaceRival
	waitmovement 0
	return

Route22_EventScript_EarlyRivalSquirtle:: @ 816836D
	trainerbattle_earlyrival TRAINER_RIVAL_ROUTE22_EARLY_SQUIRTLE, 0, Route22_Text_EarlyRivalDefeat, Text_RivalVictory
	return

Route22_EventScript_EarlyRivalBulbasaur:: @ 816837C
	trainerbattle_earlyrival TRAINER_RIVAL_ROUTE22_EARLY_BULBASAUR, 0, Route22_Text_EarlyRivalDefeat, Text_RivalVictory
	return

Route22_EventScript_EarlyRivalCharmander:: @ 816838B
	trainerbattle_earlyrival TRAINER_RIVAL_ROUTE22_EARLY_CHARMANDER, 0, Route22_Text_EarlyRivalDefeat, Text_RivalVictory
	return

Route22_EventScript_EarlyRivalExit:: @ 816839A
	applymovement 1, Route22_Movement_EarlyRivalExit
	waitmovement 0
	return

Route22_EventScript_EarlyRivalExitBottom:: @ 81683A5
	applymovement 1, Route22_Movement_EarlyRivalExitBottom
	waitmovement 0
	return

Route22_Movement_UnusedRivalExit:: @ 8
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

Route22_Movement_EarlyRivalExit:: @ 81683B8
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

Route22_Movement_EarlyRivalExitBottom:: @ 81683C5
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

Route22_Movement_RivalApproachTop:: @ 81683D1
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_fastest_up
	step_end

Route22_Movement_RivalApproachMid::
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

Route22_Movement_RivalApproachBottom:: @ 81683D9
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_fastest_down
	step_end

Route22_Movement_PlayerFaceRival:: @ 81683E3
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_8
	walk_in_place_fastest_up
	step_end

Route22_EventScript_LateRivalTriggerTop:: @ 81683ED
	lockall
	setvar VAR_TEMP_1, 0
	goto Route22_EventScript_LateRival
	end

Route22_EventScript_LateRivalTriggerMid:: @ 81683F9
	lockall
	setvar VAR_TEMP_1, 1
	setobjectxyperm 1, 25, 8
	goto Route22_EventScript_LateRival
	end

Route22_EventScript_LateRivalTriggerBottom:: @ 816840C
	lockall
	setvar VAR_TEMP_1, 2
	setobjectxyperm 1, 25, 8
	goto Route22_EventScript_LateRival
	end

Route22_EventScript_LateRival:: @ 816841F
	textcolor 0
	playbgm MUS_ENCOUNTER_RIVAL, 0
	addobject 1
	compare VAR_TEMP_1, 0
	call_if_eq Route22_EventScript_LateRivalApproachTop
	compare VAR_TEMP_1, 1
	call_if_eq Route22_EventScript_LateRivalApproachMid
	compare VAR_TEMP_1, 2
	call_if_eq Route22_EventScript_LateRivalApproachBottom
	msgbox Route22_Text_LateRivalIntro
	setvar VAR_LAST_TALKED, 1
	compare VAR_STARTER_MON, 2
	call_if_eq Route22_EventScript_LateRivalSquirtle
	compare VAR_STARTER_MON, 1
	call_if_eq Route22_EventScript_LateRivalBulbasaur
	compare VAR_STARTER_MON, 0
	call_if_eq Route22_EventScript_LateRivalCharmander
	msgbox Route22_Text_LateRivalPostBattle
	closemessage
	delay 10
	playbgm MUS_RIVAL_EXIT, 0
	applymovement 1, Route22_Movement_LateRivalExit
	waitmovement 0
	fadedefaultbgm
	removeobject 1
	setvar VAR_MAP_SCENE_ROUTE22, 4
	releaseall
	end

Route22_EventScript_LateRivalApproachTop::
	applymovement 1, Route22_Movement_RivalApproachTop
	applymovement OBJ_EVENT_ID_PLAYER, Route22_Movement_PlayerFaceRival
	waitmovement 0
	return

Route22_EventScript_LateRivalApproachMid::
	applymovement 1, Route22_Movement_RivalApproachMid
	waitmovement 0
	return

Route22_EventScript_LateRivalApproachBottom::
	applymovement 1, Route22_Movement_RivalApproachBottom
	applymovement OBJ_EVENT_ID_PLAYER, Route22_Movement_PlayerFaceRival
	waitmovement 0
	return

Route22_EventScript_LateRivalSquirtle:: @ 81684B9
	trainerbattle_no_intro TRAINER_RIVAL_ROUTE22_LATE_SQUIRTLE, Route22_Text_LateRivalDefeat
	return

Route22_EventScript_LateRivalBulbasaur:: @ 81684C4
	trainerbattle_no_intro TRAINER_RIVAL_ROUTE22_LATE_BULBASAUR, Route22_Text_LateRivalDefeat
	return

Route22_EventScript_LateRivalCharmander:: @ 81684CF
	trainerbattle_no_intro TRAINER_RIVAL_ROUTE22_LATE_CHARMANDER, Route22_Text_LateRivalDefeat
	return

Route22_Movement_LateRivalExit:: @ 81684DA
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

Route22_EventScript_LeagueGateSign:: @ 81684E2
	msgbox Route22_Text_LeagueGateSign, MSGBOX_SIGN
	end
