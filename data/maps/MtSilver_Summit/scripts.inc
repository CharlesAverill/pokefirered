MtSilver_Summit_MapScripts::
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, MtSilver_Summit_HideRedCelebi
	map_script MAP_SCRIPT_ON_TRANSITION, MtSilver_Summit_HideRedCelebi
	.byte 0

MtSilver_Summit_HideRedCelebi::
    removeobject 2
    removeobject 1
    release
    end

MtSilver_Summit_Trigger::
    goto_if_set FLAG_BEAT_GOLD EventScript_ReleaseEnd
    setvar VAR_0x8004, SPECIES_CELEBI
	specialvar VAR_RESULT, DoesPlayerPartyContainSpecies
    compare VAR_RESULT, FALSE
	goto_if_eq EventScript_ReleaseEnd
    fadescreen FADE_TO_WHITE
    playse SE_BALL_OPEN
    addobject 2
    delay 15
    fadescreen FADE_FROM_WHITE
    delay 60
    waitse
	playmoncry SPECIES_CELEBI, 2
	delay 60
	waitmoncry
	applymovement 2, FourIsland_IcefallCave_Back_Movement_WalkInPlaceDown
	waitmovement 0
    fadescreen FADE_TO_WHITE
    playse SE_BALL_CLICK
    waitse
    removeobject 2
	msgbox MtSilver_Summit_YouFeelSomething_Text
	closemessage
    fadescreen FADE_FROM_WHITE
    delay 100
    goto MtSilver_Summit_WalkToGold
    release
    end

MtSilver_Summit_WalkToGold::
    applymovement OBJ_EVENT_ID_PLAYER, MtSilver_Summit_WalkToGold_Movement
    waitmovement 0
    delay 100

    @ spawn Red (object 1) offscreen (assumed 3 tiles south of player)
    addobject 1
    applymovement 1, MtSilver_Summit_Red_EntranceMovement
    waitmovement 1

    goto MtSilver_Summit_Red
    end

MtSilver_Summit_Red_EntranceMovement::
    walk_up
    walk_up
    walk_up
    walk_up
    step_end

MtSilver_Summit_WalkToGold_Movement::
    walk_up
    walk_up
    walk_up
    face_down
    step_end

MtSilver_Summit_Trigger_L::
    applymovement OBJ_EVENT_ID_PLAYER, MtSilver_Summit_Trigger_L_MovementCenter
    waitmovement 0
    delay 30
    goto MtSilver_Summit_Trigger
    end

MtSilver_Summit_Trigger_R::
    applymovement OBJ_EVENT_ID_PLAYER, MtSilver_Summit_Trigger_R_MovementCenter
    waitmovement 0
    delay 30
    goto MtSilver_Summit_Trigger
    end

MtSilver_Summit_Trigger_L_MovementCenter::
    walk_right
    face_up
    step_end

MtSilver_Summit_Trigger_R_MovementCenter::
    walk_left
    face_up
    step_end

MtSilver_Summit_Red::
    compare VAR_STARTER_MON, SPECIES_BULBASAUR
    call_if_eq MtSilver_Summit_GoldBulbasaur
    compare VAR_STARTER_MON, SPECIES_CHARMANDER
    call_if_eq MtSilver_Summit_GoldCharmander
    compare VAR_STARTER_MON, SPECIES_SQUIRTLE
    call_if_eq MtSilver_Summit_GoldSquirtle
    release
    end

MtSilver_Summit_GoldBulbasaur::
    cleartrainerflag TRAINER_ETHAN_BULBASAUR
    trainerbattle_single TRAINER_ETHAN_BULBASAUR, MtSilver_Summit_Red_IntroDefeatText, MtSilver_Summit_Red_IntroDefeatText, MtSilver_Summit_PostRedBattle, NO_MUSIC
    release
    end

MtSilver_Summit_GoldCharmander::
    cleartrainerflag TRAINER_ETHAN_CHARMANDER
    trainerbattle_single TRAINER_ETHAN_CHARMANDER, MtSilver_Summit_Red_IntroDefeatText, MtSilver_Summit_Red_IntroDefeatText, MtSilver_Summit_PostRedBattle, NO_MUSIC
    release
    end

MtSilver_Summit_GoldSquirtle::
    cleartrainerflag TRAINER_ETHAN_SQUIRTLE
    trainerbattle_single TRAINER_ETHAN_SQUIRTLE, MtSilver_Summit_Red_IntroDefeatText, MtSilver_Summit_Red_IntroDefeatText, MtSilver_Summit_PostRedBattle, NO_MUSIC
    release
    end

MtSilver_Summit_PostRedBattle::
    setflag FLAG_BEAT_GOLD
	setrespawn SPAWN_PALLET_TOWN
	fadescreenspeed FADE_TO_BLACK, 24
	special HealPlayerParty
	warp MAP_PALLET_TOWN_PLAYERS_HOUSE_2F, 255, 6, 6
	fadescreen FADE_FROM_BLACK
	waitstate
    releaseall
    end
