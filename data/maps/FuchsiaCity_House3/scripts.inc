FuchsiaCity_House3_MapScripts:: @ 816D894
	.byte 0

FuchsiaCity_House3_EventScript_MoveDeleter:: @ 816D895
	lock
	faceplayer
	msgbox FuchsiaCity_House3_Text_WouldYouLikeToForgetMove, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq FuchsiaCity_House3_EventScript_ChooseMonForMoveDeleter
	goto FuchsiaCity_House3_EventScript_CancelForgetMove
	end

FuchsiaCity_House3_EventScript_ChooseMonForMoveDeleter:: @ 816D8B0
	msgbox FuchsiaCity_House3_Text_WhichMonShouldForgetMove
	special ChoosePartyMon
	waitstate
	compare VAR_0x8004, PARTY_SIZE
	goto_if_ge FuchsiaCity_House3_EventScript_CancelForgetMove
	special IsSelectedMonEgg
	compare VAR_RESULT, TRUE
	goto_if_eq FuchsiaCity_House3_EventScript_CantForgetMoveEgg
	special GetNumMovesSelectedMonHas
	compare VAR_RESULT, 1
	goto_if_eq FuchsiaCity_House3_EventScript_CantForgetOnlyMove
	msgbox FuchsiaCity_House3_Text_WhichMoveShouldBeForgotten
	fadescreen FADE_TO_BLACK
	special SelectMoveDeleterMove
	fadescreen FADE_FROM_BLACK
	compare VAR_0x8005, MAX_MON_MOVES
	goto_if_eq FuchsiaCity_House3_EventScript_ChooseMonForMoveDeleter
	special BufferMoveDeleterNicknameAndMove
	msgbox FuchsiaCity_House3_Text_MonsMoveShouldBeForgotten, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq FuchsiaCity_House3_EventScript_ForgetMove
	goto FuchsiaCity_House3_EventScript_CancelForgetMove
	end

FuchsiaCity_House3_EventScript_ForgetMove:: @ 816D919
	special MoveDeleterForgetMove
	playfanfare MUS_MOVE_DELETED
	waitfanfare
	msgbox FuchsiaCity_House3_Text_MonHasForgottenMoveCompletely
	release
	end

FuchsiaCity_House3_EventScript_CantForgetOnlyMove:: @ 816D92A
	special BufferMoveDeleterNicknameAndMove
	msgbox FuchsiaCity_House3_Text_MonOnlyKnowsOneMove
	release
	end

FuchsiaCity_House3_EventScript_CantForgetMoveEgg:: @ 816D937
	msgbox FuchsiaCity_House3_Text_NoEggShouldKnowMoves
	release
	end

FuchsiaCity_House3_EventScript_CancelForgetMove:: @ 816D941
	msgbox FuchsiaCity_House3_Text_ComeAgainToForgetOtherMoves
	release
	end

FuchsiaCity_House3_Eunice::
    goto_if_unset FLAG_SYS_GAME_CLEAR, FuchsiaCity_House3_Eunice_Busy
    lock
    faceplayer
    goto_if_unset FLAG_MET_EUNICE, FuchsiaCity_House3_MeetEunice
    goto_if_unset FLAG_CAUGHT_ENTEI, FuchsiaCity_House3_CheckEntei
    goto_if_unset FLAG_CAUGHT_LATI1, FuchsiaCity_House3_CheckLatias
    goto_if_unset FLAG_CAUGHT_RAIKOU, FuchsiaCity_House3_CheckRaikou
    goto_if_unset FLAG_CAUGHT_LATI2, FuchsiaCity_House3_CheckLatios
    goto_if_unset FLAG_CAUGHT_SUICUNE, FuchsiaCity_House3_CheckSuicune
    msgbox FuchsiaCity_House3_AllDone
    release
    end

FuchsiaCity_House3_CheckEntei::
    hascaughtmon SPECIES_ENTEI
    compare VAR_RESULT, 1
    goto_if_eq FuchsiaCity_House3_HasEntei
    setvar VAR_CURRENT_ROAMER, SPECIES_ENTEI
    msgbox FuchsiaCity_House3_Entei_Intro
    msgbox FuchsiaCity_House3_CanYouShowItToMe
    release
    end

FuchsiaCity_House3_HasEntei::
    msgbox FuchsiaCity_House3_WoahThatsEntei
	checkplayergender
	compare VAR_RESULT, MALE
    call_if_eq FuchisaCity_House3_SetLatias
	compare VAR_RESULT, FEMALE
    call_if_eq FuchisaCity_House3_SetLatios
    msgbox FuchsiaCity_House3_Latias_Intro
    setflag FLAG_CAUGHT_ENTEI
    setvar VAR_CURRENT_ROAMER, SPECIES_LATIAS
    special InitRoamer
    release
    end

FuchsiaCity_House3_CheckLatias::
    hascaughtmon SPECIES_LATIAS
    compare VAR_RESULT, 1
    goto_if_eq FuchsiaCity_House3_HasLatias
	checkplayergender
	compare VAR_RESULT, MALE
    call_if_eq FuchisaCity_House3_SetLatias
	compare VAR_RESULT, FEMALE
    call_if_eq FuchisaCity_House3_SetLatios
    msgbox FuchsiaCity_House3_Latias_Intro
    msgbox FuchsiaCity_House3_CanYouShowItToMe
    release
    end

FuchsiaCity_House3_HasLatias::
	checkplayergender
	compare VAR_RESULT, MALE
    call_if_eq FuchisaCity_House3_SetLatias
	compare VAR_RESULT, FEMALE
    call_if_eq FuchisaCity_House3_SetLatios
    msgbox FuchsiaCity_House3_WoahThatsLatias
    call FuchsiaCity_House3_GiveEonFluteEvent
    msgbox FuchsiaCity_House3_Raikou_Intro
    setflag FLAG_CAUGHT_LATI1
    setvar VAR_CURRENT_ROAMER, SPECIES_RAIKOU
    special InitRoamer
    release
    end

FuchsiaCity_House3_GiveEonFluteEvent::
	checkplayergender
	compare VAR_RESULT, MALE
    call_if_eq FuchisaCity_House3_SetLatias
	compare VAR_RESULT, FEMALE
    call_if_eq FuchisaCity_House3_SetLatios
    msgbox FuchsiaCity_House3_GiveEonFlute
	waitmessage
	waitbuttonpress
	checkitemspace ITEM_EON_FLUTE, 1
	compare VAR_RESULT, FALSE
	vgoto_if_eq EonFlute_NoBagSpace
	giveitem ITEM_EON_FLUTE
    return

FuchisaCity_House3_SetLatias::
	getspeciesname 0, SPECIES_LATIAS
    return

FuchisaCity_House3_SetLatios::
	getspeciesname 0, SPECIES_LATIOS
    return

EonFlute_NoBagSpace:
	vmessage sText_EonFluteNoPlace
	waitmessage
	waitbuttonpress
	release
	end

FuchsiaCity_House3_CheckRaikou::
    hascaughtmon SPECIES_RAIKOU
    compare VAR_RESULT, 1
    goto_if_eq FuchsiaCity_House3_HasRaikou
    msgbox FuchsiaCity_House3_Raikou_Intro
    msgbox FuchsiaCity_House3_CanYouShowItToMe
    release
    end

FuchsiaCity_House3_HasRaikou::
    msgbox FuchsiaCity_House3_WoahThatsRaikou
    msgbox FuchsiaCity_House3_Latios_Intro
    setflag FLAG_CAUGHT_RAIKOU
    setvar VAR_CURRENT_ROAMER, SPECIES_LATIOS
    special InitRoamer
    release
    end

FuchsiaCity_House3_CheckLatios::
    hascaughtmon SPECIES_LATIOS
    compare VAR_RESULT, 1
    goto_if_eq FuchsiaCity_House3_HasLatios
	checkplayergender
	compare VAR_RESULT, MALE
    call_if_eq FuchisaCity_House3_SetLatios
	compare VAR_RESULT, FEMALE
    call_if_eq FuchisaCity_House3_SetLatias
    msgbox FuchsiaCity_House3_Latios_Intro
    msgbox FuchsiaCity_House3_CanYouShowItToMe
    release
    end

FuchsiaCity_House3_HasLatios::
	checkplayergender
	compare VAR_RESULT, MALE
    call_if_eq FuchisaCity_House3_SetLatios
	compare VAR_RESULT, FEMALE
    call_if_eq FuchisaCity_House3_SetLatias
    msgbox FuchsiaCity_House3_WoahThatsLatios
    msgbox FuchsiaCity_House3_Suicune_Intro
    setflag FLAG_CAUGHT_LATI2
    setvar VAR_CURRENT_ROAMER, SPECIES_SUICUNE
    special InitRoamer
    release
    end

FuchsiaCity_House3_CheckSuicune::
    hascaughtmon SPECIES_SUICUNE
    compare VAR_RESULT, 1
    goto_if_eq FuchsiaCity_House3_HasSuicune
    msgbox FuchsiaCity_House3_Suicune_Intro
    msgbox FuchsiaCity_House3_CanYouShowItToMe
    release
    end

FuchsiaCity_House3_HasSuicune::
    msgbox FuchsiaCity_House3_WoahThatsSuicune
    msgbox FuchsiaCity_House3_AllDone
    setflag FLAG_CAUGHT_SUICUNE
    release
    end

FuchsiaCity_House3_MeetEunice::
    msgbox FuchsiaCity_House3_Eunice_Introduction
    msgbox FuchsiaCity_House3_Entei_Intro
    setflag FLAG_MET_EUNICE
    special InitRoamer
    release
    end

FuchsiaCity_House3_Eunice_Busy::
    lock
    msgbox FuchsiaCity_House3_Eunice_Text_Thinking
    msgbox FuchsiaCity_House3_Eunice_Text_Busy
    release
    end

FuchsiaCity_House3_Eusine::
    lock
    faceplayer
    goto_if_set FLAG_CAUGHT_SUICUNE, FuchisaCity_House3_Eusine_Post
    msgbox FuchisaCity_House3_Eusine_Text
    release
    end

FuchisaCity_House3_Eusine_Post::
    msgbox FuchisaCity_House3_Eusine_PostText
    release
    end

EuniceAgent::
    lock
    faceplayer
    bufferroamerdata
    msgbox EuniceAgent_SayRoamerLocation
    release
    end

EuniceAgent_GoSeeEunice::
    msgbox EuniceAgent_GoSeeEunice_Text
    release
    end

EuniceAgent_NotMet::
    msgbox EuniceAgent_MeetText
    setflag FLAG_EUNICE_AGENTS_MET
    release
    end
