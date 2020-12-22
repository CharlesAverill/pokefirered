VermilionCity_BrendanHouse_MapScripts::
	.byte 0

VermilionCity_BrendanHouse_Brendan::
    lock
    faceplayer
    goto VermilionCity_BrendanHouse_GiveRayquaza
    /*
    goto_if_unset FLAG_MET_BRENDAN, VermilionCity_BrendanHouse_HaventMetBrendan
    goto_if_unset FLAG_IS_CHAMPION, VermilionCity_BrendanHouse_HaveMetBrendanNotChampion
    goto_if_set FLAG_RECEIVED_RAYQUAZA, VermilionCity_BrendanHouse_BrendanPostBattle
    msgbox VermilionCity_Text_Brendan_PostChampionMet
    // Brendan battle
    goto_if_unset FLAG_RECEIVED_RAYQUAZA, VermilionCity_BrendanHouse_GiveRayquaza
    msgbox VermilionCity_Text_Brendan_PostBattle
    */
    release
    end

VermilionCity_BrendanHouse_BrendanPostBattle::
    msgbox VermilionCity_Text_Brendan_PostBattle
    release
    end

VermilionCity_BrendanHouse_GiveRayquaza::
    msgbox VermilionCity_Text_Brendan_GiveRayquaza
    setvar VAR_TEMP_1, SPECIES_RAYQUAZA
    givemon SPECIES_RAYQUAZA, 80, ITEM_NONE
    compare VAR_RESULT, 0
    goto_if_eq VermilionCity_BrendanHouse_ReceiveRayquazaParty
    compare VAR_RESULT, 1
    goto_if_eq SilphCo_7F_EventScript_ReceiveLaprasPC
    compare VAR_RESULT, 2
    goto_if_eq EventScript_NoMoreRoomForPokemon
    release
    end

VermilionCity_BrendanHouse_ReceiveRayquazaParty::
	textcolor 3
	playfanfare MUS_LEVEL_UP
	message VermilionCity_Text_ReceivedRayquaza
	waitmessage
	waitfanfare
	getspeciesname 0, SPECIES_RAYQUAZA
	msgbox Text_GiveNicknameToThisMon, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq VermilionCity_BrendanHouse_EndReceiveRayquaza
	call EventScript_GetGiftMonPartySlot
	call EventScript_ChangePokemonNickname
	goto VermilionCity_BrendanHouse_EndReceiveRayquaza
	end

VermilionCity_BrendanHouse_ReceiveRayquazaPC::
	textcolor 3
	playfanfare MUS_LEVEL_UP
	message VermilionCity_Text_ReceivedRayquaza
	waitmessage
	waitfanfare
	getspeciesname 0, SPECIES_LAPRAS
	msgbox Text_GiveNicknameToThisMon, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq VermilionCity_BrendanHouse_RayquazaTransferredToPC
	call EventScript_NameReceivedBoxMon
	goto VermilionCity_BrendanHouse_RayquazaTransferredToPC
	end

VermilionCity_BrendanHouse_RayquazaTransferredToPC::
	call EventScript_TransferredToPC
	goto VermilionCity_BrendanHouse_EndReceiveRayquaza
	end

VermilionCity_BrendanHouse_EndReceiveRayquaza::
	textcolor 0
	msgbox VermilionCity_Text_ExplainRayquaza
    setflag FLAG_RECEIVED_RAYQUAZA
	release
	end

VermilionCity_BrendanHouse_HaventMetBrendan::


VermilionCity_BrendanHouse_End::
    releaseall
    end