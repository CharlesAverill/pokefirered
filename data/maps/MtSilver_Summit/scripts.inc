MtSilver_Summit_MapScripts::
	.byte 0

MtSilver_Summit_HideRedCelebi::
    removeobject 2
    removeobject 1
    goto_if_set FLAG_FOUGHT_FUTURE_RED, MtSilver_Summit_ShowRed
    release
    end

MtSilver_Summit_Trigger::
    goto_if_set FLAG_DID_CELEBI_RED_CUTSCENE, EventScript_ReleaseEnd
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
    addobject 1
    fadescreen FADE_FROM_WHITE
    setflag FLAG_DID_CELEBI_RED_CUTSCENE
    release
    end

MtSilver_Summit_Trigger_L::
    goto_if_set FLAG_DID_CELEBI_RED_CUTSCENE, EventScript_ReleaseEnd
    applymovement OBJ_EVENT_ID_PLAYER, MtSilver_Summit_Trigger_L_MovementCenter
    waitmovement 0
    delay 30
    goto MtSilver_Summit_Trigger
    end

MtSilver_Summit_Trigger_R::
    goto_if_set FLAG_DID_CELEBI_RED_CUTSCENE, MtSilver_Summit_ShowRed
    applymovement OBJ_EVENT_ID_PLAYER, MtSilver_Summit_Trigger_R_MovementCenter
    waitmovement 0
    delay 30
    goto MtSilver_Summit_Trigger
    end

MtSilver_Summit_ShowRed::
    addobject 1
    release
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
    setflag FLAG_FOUGHT_FUTURE_RED
    cleartrainerflag TRAINER_OLD_RED
    trainerbattle_single TRAINER_OLD_RED, MtSilver_Summit_Red_IntroDefeatText, MtSilver_Summit_Red_IntroDefeatText, MtSilver_Summit_PostRedBattle, NO_MUSIC
    release
    end

MtSilver_Summit_PostRedBattle::
	setrespawn SPAWN_PALLET_TOWN
	fadescreenspeed FADE_TO_BLACK, 24
	warp MAP_PALLET_TOWN_PLAYERS_HOUSE_2F, 255, 6, 6
	waitstate
    releaseall
    end
