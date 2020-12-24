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
    goto_if_unset FLAG_IS_CHAMPION, FuchsiaCity_House3_Eunice_Busy
    lock
    faceplayer
    goto_if_unset FLAG_MET_EUNICE, FuchsiaCity_House3_MeetEunice
    goto_if_unset FLAG_CAUGHT_ENTEI, FuchsiaCity_House3_CheckEntei
    goto_if_unset FLAG_CAUGHT_LATIAS, FuchsiaCity_House3_CheckLatias
    goto_if_unset FLAG_CAUGHT_RAIKOU, FuchsiaCity_House3_CheckRaikou
    goto_if_unset FLAG_CAUGHT_LATIOS, FuchsiaCity_House3_CheckLatios
    goto_if_unset FLAG_CAUGHT_SUICUNE, FuchsiaCity_House3_CheckSuicune
    msgbox FuchsiaCity_House3_AllDone
    release
    end

FuchsiaCity_House3_CheckEntei::
	setvar 0x8005, SPECIES_ENTEI
	special CheckSpecies
    compare VAR_RESULT, 1
    goto_if_eq FuchsiaCity_House3_HasEntei
    msgbox FuchsiaCity_House3_Entei_Intro
    msgbox FuchsiaCity_House3_CanYouShowItToMe
    release
    end

FuchsiaCity_House3_HasEntei::
    msgbox FuchsiaCity_House3_WoahThatsEntei
    msgbox FuchsiaCity_House3_Latias_Intro
    setflag FLAG_CAUGHT_ENTEI
    special InitRoamer
    release
    end

FuchsiaCity_House3_CheckLatias::
	setvar 0x8005, SPECIES_LATIAS
	special CheckSpecies
    compare VAR_RESULT, 1
    goto_if_eq FuchsiaCity_House3_HasLatias
    msgbox FuchsiaCity_House3_Latias_Intro
    msgbox FuchsiaCity_House3_CanYouShowItToMe
    release
    end

FuchsiaCity_House3_HasLatias::
    msgbox FuchsiaCity_House3_WoahThatsLatias
    msgbox FuchsiaCity_House3_Raikou_Intro
    msgbox FuchsiaCity_House3_GiveBallText
    giveitem ITEM_MASTER_BALL
    setflag FLAG_CAUGHT_LATIAS
    special InitRoamer
    release
    end

FuchsiaCity_House3_CheckRaikou::
	setvar 0x8005, SPECIES_RAIKOU
	special CheckSpecies
    compare VAR_RESULT, 1
    goto_if_eq FuchsiaCity_House3_HasRaikou
    msgbox FuchsiaCity_House3_Raikou_Intro
    msgbox FuchsiaCity_House3_CanYouShowItToMe
    release
    end

FuchsiaCity_House3_HasRaikou::
    msgbox FuchsiaCity_House3_WoahThatsRaikou
    msgbox FuchsiaCity_House3_Latios_Intro
    msgbox FuchsiaCity_House3_GiveBallText
    giveitem ITEM_MASTER_BALL
    special InitRoamer
    release
    end

FuchsiaCity_House3_CheckLatios::
	setvar 0x8005, SPECIES_LATIOS
	special CheckSpecies
    compare VAR_RESULT, 1
    goto_if_eq FuchsiaCity_House3_HasLatios
    msgbox FuchsiaCity_House3_Latios_Intro
    msgbox FuchsiaCity_House3_CanYouShowItToMe
    release
    end

FuchsiaCity_House3_HasLatios::
    msgbox FuchsiaCity_House3_WoahThatsLatios
    msgbox FuchsiaCity_House3_Suicune_Intro
    setflag FLAG_CAUGHT_LATIOS
    special InitRoamer
    release
    end

FuchsiaCity_House3_CheckSuicune::
	setvar 0x8005, SPECIES_SUICUNE
	special CheckSpecies
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
    msgbox FuchsiaCity_House3_GiveBallText
    giveitem ITEM_MASTER_BALL
    setflag FLAG_MET_EUNICE
    special InitRoamer
    release
    end

FuchsiaCity_House3_Eunice_Busy::
    msgbox FuchsiaCity_House3_Eunice_Text_Thinking
    waitmessage
    msgbox FuchsiaCity_House3_Eunice_Text_Busy
    waitmessage
    end

FuchsiaCity_House3_Eusine::
    lock
    faceplayer
    msgbox FuchisaCity_House3_Eusine_Text
    release
    end