PokemonTower_7F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PokemonTower_7F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, PokemonTower_7F_OnResume
	.byte 0

PokemonTower_7F_OnTransition::
    call_if_unset FLAG_TALKED_ABOUT_JIRACHI, PokemonTower_7F_HideJirachi
	call_if_set FLAG_FOUGHT_JIRACHI, PokemonTower_7F_HideJirachi
	call_if_unset FLAG_FOUGHT_JIRACHI, PokemonTower_7F_TryShowJirachi
	end

PokemonTower_7F_Initiate_Jirachi_Battle::
    goto_if_questlog EventScript_ReleaseEnd
    special QuestLog_CutRecording
    lock
    faceplayer
    waitse
    playmoncry SPECIES_JIRACHI, 2
    message PokemonTower_7F_Text_Jirachi
    waitmessage
    waitmoncry
    delay 20
    playbgm MUS_ENCOUNTER_GYM_LEADER, 0
    waitbuttonpress
    setwildbattle SPECIES_JIRACHI, 80, ITEM_NONE
    setflag FLAG_SYS_SPECIAL_WILD_BATTLE
    special StartLegendaryBattle
    waitstate
    clearflag FLAG_SYS_SPECIAL_WILD_BATTLE
    specialvar VAR_RESULT, GetBattleOutcome
    compare VAR_RESULT, B_OUTCOME_WON
    goto_if_eq PokemonTower_7F_DefeatedJirachi
    compare VAR_RESULT, B_OUTCOME_RAN
    goto_if_eq PokemonTower_7F_RanFromJirachi
    compare VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED
    goto_if_eq PokemonTower_7F_RanFromJirachi
    setflag FLAG_FOUGHT_JIRACHI
    release
    end

PokemonTower_7F_DefeatedJirachi::
	setflag FLAG_JIRACHI_FLEW_AWAY
	goto EventScript_RemoveStaticMon
	end

PokemonTower_7F_RanFromJirachi::
	setflag FLAG_JIRACHI_FLEW_AWAY
	setvar VAR_0x8004, SPECIES_JIRACHI
	goto EventScript_MonFlewAway
	end

PokemonTower_7F_Text_Jirachi:
    .string "zzzzz....\n"
    .string "Xir Xii!$"

PokemonTower_7F_HideJirachi::
	setvar VAR_TEMP_1, 1
	setflag FLAG_HIDE_JIRACHI
	return

PokemonTower_7F_TryShowJirachi:
	setvar VAR_TEMP_1, 1
	goto_if_set FLAG_JIRACHI_FLEW_AWAY, EventScript_Return
	setvar VAR_TEMP_1, 0
	clearflag FLAG_HIDE_JIRACHI
	return

PokemonTower_7F_OnResume::
	call_if_set FLAG_SYS_SPECIAL_WILD_BATTLE, PokemonTower_7F_EventScript_TryRemoveJirachi
	end

PokemonTower_7F_EventScript_TryRemoveJirachi::
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_ne EventScript_Return
	removeobject 5
	return

PokemonTower_7F_TriggerHideJirachi::
    goto_if_set FLAG_TALKED_ABOUT_JIRACHI, PokemonTower_7F_End
    releaseall
    removeobject 5
    end

PokemonTower_7F_End::
    releaseall
    end

PokemonTower_7F_EventScript_MrFuji:: @ 816355A
	lock
	faceplayer
	famechecker FAMECHECKER_MRFUJI, FCPICKSTATE_COLORED, UpdatePickStateFromSpecialVar8005
	setflag FLAG_HIDE_TOWER_FUJI
	clearflag FLAG_HIDE_POKEHOUSE_FUJI
	setflag FLAG_RESCUED_MR_FUJI
	msgbox PokemonTower_7F_Text_MrFujiThankYouFollowMe
	closemessage
	warp MAP_LAVENDER_TOWN_VOLUNTEER_POKEMON_HOUSE, 255, 4, 7
	waitstate
	release
	end

PokemonTower_7F_EventScript_Grunt1:: @ 8163586
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT_19, PokemonTower_7F_Text_Grunt1Intro, PokemonTower_7F_Text_Grunt1Defeat, PokemonTower_7F_EventScript_DefeatedGrunt1
	msgbox PokemonTower_7F_Text_Grunt1PostBattle, MSGBOX_AUTOCLOSE
	end

PokemonTower_7F_EventScript_DefeatedGrunt1:: @ 81635A1
	msgbox PokemonTower_7F_Text_Grunt1PostBattle
	closemessage
	getplayerxy VAR_0x8004, VAR_0x8005
	compare VAR_0x8004, 10
	goto_if_eq PokemonTower_7F_EventScript_Grunt1ExitMid
	compare VAR_0x8004, 11
	goto_if_eq PokemonTower_7F_EventScript_Grunt1ExitRight
	compare VAR_0x8004, 9
	goto_if_eq PokemonTower_7F_EventScript_Grunt1ExitLeft
	applymovement 2, PokemonTower_7F_Movement_Grunt1Exit
	waitmovement 0
	goto PokemonTower_7F_EventScript_RemoveGrunt1
	end

PokemonTower_7F_EventScript_Grunt1ExitMid:: @ 81635E0
	applymovement 2, PokemonTower_7F_Movement_Grunt1ExitMid
	waitmovement 0
	goto PokemonTower_7F_EventScript_RemoveGrunt1
	end

PokemonTower_7F_EventScript_Grunt1ExitRight:: @ 81635F0
	applymovement 2, PokemonTower_7F_Movement_Grunt1ExitRight
	waitmovement 0
	goto PokemonTower_7F_EventScript_RemoveGrunt1
	end

PokemonTower_7F_EventScript_Grunt1ExitLeft:: @ 8163600
	applymovement 2, PokemonTower_7F_Movement_Grunt1ExitLeft
	waitmovement 0
	playse SE_EXIT
	delay 25
	goto PokemonTower_7F_EventScript_RemoveGrunt1
	end

PokemonTower_7F_EventScript_RemoveGrunt1:: @ 8163616
	removeobject 2
	release
	end

PokemonTower_7F_Movement_Grunt1ExitMid:: @ 816361B
	walk_down
	walk_right
	walk_down
	walk_down
	walk_down
	walk_right
	walk_down
	walk_down
	step_end

PokemonTower_7F_Movement_Grunt1ExitRight:: @ 8163624
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_down
	walk_down
	step_end

PokemonTower_7F_Movement_Grunt1Exit:: @ 816362C
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

PokemonTower_7F_Movement_Grunt1ExitLeft:: @ 8163633
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_down
	walk_down
	walk_in_place_fastest_left
	step_end

PokemonTower_7F_EventScript_Grunt2:: @ 816363D
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT_20, PokemonTower_7F_Text_Grunt2Intro, PokemonTower_7F_Text_Grunt2Defeat, PokemonTower_7F_EventScript_DefeatedGrunt2
	msgbox PokemonTower_7F_Text_Grunt2PostBattle, MSGBOX_AUTOCLOSE
	end

PokemonTower_7F_EventScript_DefeatedGrunt2:: @ 8163658
	famechecker FAMECHECKER_MRFUJI, 1
	msgbox PokemonTower_7F_Text_Grunt2PostBattle
	closemessage
	getplayerxy VAR_0x8004, VAR_0x8005
	compare VAR_0x8004, 12
	goto_if_eq PokemonTower_7F_EventScript_Grunt2ExitLeft
	compare VAR_0x8004, 13
	goto_if_eq PokemonTower_7F_EventScript_Grunt2ExitRight
	applymovement 3, PokemonTower_7F_Movement_Grunt2Exit
	waitmovement 0
	goto PokemonTower_7F_EventScript_RemoveGrunt2
	end

PokemonTower_7F_EventScript_Grunt2ExitLeft:: @ 8163699
	applymovement 3, PokemonTower_7F_Movement_Grunt2ExitLeft
	waitmovement 0
	goto PokemonTower_7F_EventScript_RemoveGrunt2
	end

PokemonTower_7F_EventScript_Grunt2ExitRight:: @ 81636A9
	applymovement 3, PokemonTower_7F_Movement_Grunt2ExitRight
	waitmovement 0
	goto PokemonTower_7F_EventScript_RemoveGrunt2
	end

PokemonTower_7F_EventScript_RemoveGrunt2:: @ 81636B9
	removeobject 3
	release
	end

PokemonTower_7F_Movement_Grunt2ExitLeft:: @ 81636BE
	walk_down
	walk_down
	walk_down
	walk_left
	walk_down
	walk_down
	walk_down
	step_end

PokemonTower_7F_Movement_Grunt2Exit:: @ 81636C6
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

PokemonTower_7F_Movement_Grunt2ExitRight:: @ 81636CD
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

PokemonTower_7F_EventScript_Grunt3:: @ 81636D6
	trainerbattle_single TRAINER_TEAM_ROCKET_GRUNT_21, PokemonTower_7F_Text_Grunt3Intro, PokemonTower_7F_Text_Grunt3Defeat, PokemonTower_7F_EventScript_DefeatedGrunt3
	msgbox PokemonTower_7F_Text_Grunt3PostBattle, MSGBOX_AUTOCLOSE
	end

PokemonTower_7F_EventScript_DefeatedGrunt3:: @ 81636F1
	msgbox PokemonTower_7F_Text_Grunt3PostBattle
	closemessage
	getplayerxy VAR_0x8004, VAR_0x8005
	compare VAR_0x8004, 10
	goto_if_eq PokemonTower_7F_EventScript_Grunt3ExitRight
	compare VAR_0x8004, 9
	goto_if_eq PokemonTower_7F_EventScript_Grunt3ExitLeft
	applymovement 4, PokemonTower_7F_Movement_Grunt3Exit
	waitmovement 0
	goto PokemonTower_7F_EventScript_RemoveGrunt3
	end

PokemonTower_7F_EventScript_Grunt3ExitRight:: @ 8163725
	applymovement 4, PokemonTower_7F_Movement_Grunt3ExitRight
	waitmovement 0
	goto PokemonTower_7F_EventScript_RemoveGrunt3
	end

PokemonTower_7F_EventScript_Grunt3ExitLeft:: @ 8163735
	applymovement 4, PokemonTower_7F_Movement_Grunt3ExitLeft
	waitmovement 0
	goto PokemonTower_7F_EventScript_RemoveGrunt3
	end

PokemonTower_7F_EventScript_RemoveGrunt3:: @ 8163745
	removeobject 4
	release
	end

PokemonTower_7F_EventScript_Unused:: @ 816374A
	release
	end

PokemonTower_7F_Movement_Grunt3ExitRight:: @ 816374C
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_down
	step_end

PokemonTower_7F_Movement_Grunt3Exit:: @ 8163754
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

PokemonTower_7F_Movement_Grunt3ExitLeft:: @ 816375B
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end
