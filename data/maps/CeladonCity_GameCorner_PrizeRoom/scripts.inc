CeladonCity_GameCorner_PrizeRoom_MapScripts:: @ 816CB75
	.byte 0

CeladonCity_GameCorner_PrizeRoom_EventScript_BaldingMan:: @ 816CB76
	msgbox CeladonCity_GameCorner_PrizeRoom_Text_FancyThatPorygon, MSGBOX_NPC
	end

CeladonCity_GameCorner_PrizeRoom_EventScript_OldMan:: @ 816CB7F
	msgbox CeladonCity_GameCorner_PrizeRoom_Text_RakedItInToday, MSGBOX_NPC
	end

CeladonCity_GameCorner_PrizeRoom_EventScript_PrizeClerkMons:: @ 816CB88
	lock
	faceplayer
	goto_if_unset FLAG_GOT_COIN_CASE, CeladonCity_GameCorner_PrizeRoom_EventScript_NeedCoinCase
	goto_if_questlog EventScript_ReleaseEnd
	showcoinsbox 0, 0
	msgbox CeladonCity_GameCorner_PrizeRoom_Text_WeExchangeCoinsForPrizes
	goto CeladonCity_GameCorner_PrizeRoom_EventScript_ChoosePrizeMon
	end

CeladonCity_GameCorner_PrizeRoom_EventScript_ChoosePrizeMon:: @ 816CBB2
	message CeladonCity_GameCorner_PrizeRoom_Text_WhichPrize
	waitmessage
	multichoice 11, 0, MULTICHOICE_GAME_CORNER_POKEMON_PRIZES, FALSE
	switch VAR_RESULT
	case 0, CeladonCity_GameCorner_PrizeRoom_EventScript_Abra
	case 1, CeladonCity_GameCorner_PrizeRoom_EventScript_Clefairy
	case 2, CeladonCity_GameCorner_PrizeRoom_EventScript_Dratini
	case 3, CeladonCity_GameCorner_PrizeRoom_EventScript_Pinsir
	case 4, CeladonCity_GameCorner_PrizeRoom_EventScript_Scyther
	case 5, CeladonCity_GameCorner_PrizeRoom_EventScript_Porygon
	case 6, CeladonCity_GameCorner_PrizeRoom_EventScript_EndPrizeExchange
	case 127, CeladonCity_GameCorner_PrizeRoom_EventScript_EndPrizeExchange
	end

CeladonCity_GameCorner_PrizeRoom_EventScript_EndPrizeExchange:: @ 816CC10
	hidecoinsbox 0, 0
	release
	end

CeladonCity_GameCorner_PrizeRoom_EventScript_Abra:: @ 816CC15
	.ifdef FIRERED
	setvar VAR_TEMP_1, SPECIES_ABRA
	setvar VAR_TEMP_2, 180
	.else
	.ifdef LEAFGREEN
	setvar VAR_TEMP_1, SPECIES_ABRA
	setvar VAR_TEMP_2, 120
	.endif
	.endif
	goto CeladonCity_GameCorner_PrizeRoom_EventScript_ConfirmPrizeMon
	end

CeladonCity_GameCorner_PrizeRoom_EventScript_Clefairy:: @ 816CC25
	.ifdef FIRERED
	setvar VAR_TEMP_1, SPECIES_CLEFAIRY
	setvar VAR_TEMP_2, 500
	.else
	.ifdef LEAFGREEN
	setvar VAR_TEMP_1, SPECIES_CLEFAIRY
	setvar VAR_TEMP_2, 750
	.endif
	.endif
	goto CeladonCity_GameCorner_PrizeRoom_EventScript_ConfirmPrizeMon
	end

CeladonCity_GameCorner_PrizeRoom_EventScript_Dratini:: @ 816CC35
	setvar VAR_TEMP_1, SPECIES_DRATINI
	setvar VAR_TEMP_2, 2800
	goto CeladonCity_GameCorner_PrizeRoom_EventScript_ConfirmPrizeMon
	end

CeladonCity_GameCorner_PrizeRoom_EventScript_Pinsir:
    setvar VAR_TEMP_1, SPECIES_PINSIR
	setvar VAR_TEMP_2, 5500
	goto CeladonCity_GameCorner_PrizeRoom_EventScript_ConfirmPrizeMon
	end

CeladonCity_GameCorner_PrizeRoom_EventScript_Scyther:: @ 816CC45
	setvar VAR_TEMP_1, SPECIES_SCYTHER
	setvar VAR_TEMP_2, 5500
	goto CeladonCity_GameCorner_PrizeRoom_EventScript_ConfirmPrizeMon
	end

CeladonCity_GameCorner_PrizeRoom_EventScript_Porygon:: @ 816CC55
	setvar VAR_TEMP_1, SPECIES_PORYGON
	setvar VAR_TEMP_2, 9999
	goto CeladonCity_GameCorner_PrizeRoom_EventScript_ConfirmPrizeMon
	end

CeladonCity_GameCorner_PrizeRoom_EventScript_ConfirmPrizeMon:: @ 816CC65
	getspeciesname 0, VAR_TEMP_1
	msgbox CeladonCity_GameCorner_PrizeRoom_Text_YouWantPrize, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq CeladonCity_GameCorner_PrizeRoom_EventScript_EndPrizeExchange
	checkcoins VAR_RESULT
	compare VAR_RESULT, VAR_TEMP_2
	goto_if_lt CeladonCity_GameCorner_PrizeRoom_EventScript_NotEnoughCoins
	textcolor 3
	switch VAR_TEMP_1
	case SPECIES_ABRA,     CeladonCity_GameCorner_PrizeRoom_EventScript_GiveAbra
	case SPECIES_CLEFAIRY, CeladonCity_GameCorner_PrizeRoom_EventScript_GiveClefairy
	case SPECIES_DRATINI,  CeladonCity_GameCorner_PrizeRoom_EventScript_GiveDratini
	case SPECIES_SCYTHER,  CeladonCity_GameCorner_PrizeRoom_EventScript_GiveScyther
	case SPECIES_PORYGON,  CeladonCity_GameCorner_PrizeRoom_EventScript_GivePorygon
	case SPECIES_PINSIR,   CeladonCity_GameCorner_PrizeRoom_EventScript_GivePinsir
	end

CeladonCity_GameCorner_PrizeRoom_EventScript_GiveAbra:: @ 816CCD4
	givemon VAR_TEMP_1, 9, ITEM_TWISTED_SPOON
	goto CeladonCity_GameCorner_PrizeRoom_EventScript_CheckReceivedMon
	end

CeladonCity_GameCorner_PrizeRoom_EventScript_GiveClefairy:: @ 816CCE9
	givemon VAR_TEMP_1, 12, ITEM_LEFTOVERS
	goto CeladonCity_GameCorner_PrizeRoom_EventScript_CheckReceivedMon
	end

CeladonCity_GameCorner_PrizeRoom_EventScript_GiveDratini:: @ 816CCFE
	givemon VAR_TEMP_1, 24, ITEM_DRAGON_FANG
	goto CeladonCity_GameCorner_PrizeRoom_EventScript_CheckReceivedMon
	end

CeladonCity_GameCorner_PrizeRoom_EventScript_GiveScyther:: @ 816CD13
	givemon VAR_TEMP_1, 25, ITEM_LIECHI_BERRY
	goto CeladonCity_GameCorner_PrizeRoom_EventScript_CheckReceivedMon
	end

CeladonCity_GameCorner_PrizeRoom_EventScript_GivePorygon:: @ 816CD28
	givemon VAR_TEMP_1, 26, ITEM_SILK_SCARF
	goto CeladonCity_GameCorner_PrizeRoom_EventScript_CheckReceivedMon
	end

CeladonCity_GameCorner_PrizeRoom_EventScript_GivePinsir:: @ 816CD3D
	givemon VAR_TEMP_1, 25, ITEM_SALAC_BERRY
	goto CeladonCity_GameCorner_PrizeRoom_EventScript_CheckReceivedMon
	end

CeladonCity_GameCorner_PrizeRoom_EventScript_CheckReceivedMon:: @ 816CD52
	compare VAR_RESULT, 0
	goto_if_eq CeladonCity_GameCorner_PrizeRoom_EventScript_ReceivedMonParty
	compare VAR_RESULT, 1
	goto_if_eq CeladonCity_GameCorner_PrizeRoom_EventScript_ReceivedMonPC
	compare VAR_RESULT, 2
	goto_if_eq CeladonCity_GameCorner_PrizeRoom_EventScript_PartyFull
	end

CeladonCity_GameCorner_PrizeRoom_EventScript_PartyFull:: @ 816CD74
	textcolor 3
	msgbox Text_NoMoreRoomForPokemon
	hidecoinsbox 0, 0
	release
	end

CeladonCity_GameCorner_PrizeRoom_EventScript_NicknamePartyMon:: @ 816CD83
	getpartysize
	subvar VAR_RESULT, 1
	copyvar VAR_0x8004, VAR_RESULT
	call EventScript_ChangePokemonNickname
	goto CeladonCity_GameCorner_PrizeRoom_EventScript_EndPrizeExchange
	end

CeladonCity_GameCorner_PrizeRoom_EventScript_NeedCoinCase:: @ 816CD99
	textcolor 3
	msgbox CeladonCity_GameCorner_PrizeRoom_Text_CoinCaseRequired
	release
	end

CeladonCity_GameCorner_PrizeRoom_EventScript_NotEnoughCoins:: @ 816CDA5
	msgbox CeladonCity_GameCorner_PrizeRoom_Text_NeedMoreCoins
	goto CeladonCity_GameCorner_PrizeRoom_EventScript_EndPrizeExchange
	end

CeladonCity_GameCorner_PrizeRoom_EventScript_ReceivedMonParty:: @ 816CDB3
	removecoins VAR_TEMP_2
	updatecoinsbox 0, 5
	getspeciesname 0, VAR_TEMP_1
	playfanfare MUS_LEVEL_UP
	message Text_PlayerObtainedTheMon
	waitmessage
	waitfanfare
	msgbox Text_GiveNicknameToThisMon, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq CeladonCity_GameCorner_PrizeRoom_EventScript_NicknamePartyMon
	goto CeladonCity_GameCorner_PrizeRoom_EventScript_EndPrizeExchange
	end

CeladonCity_GameCorner_PrizeRoom_EventScript_ReceivedMonPC:: @ 816CDE0
	removecoins VAR_TEMP_2
	updatecoinsbox 0, 5
	getspeciesname 0, VAR_TEMP_1
	playfanfare MUS_LEVEL_UP
	message Text_PlayerObtainedTheMon
	waitmessage
	waitfanfare
	msgbox Text_GiveNicknameToThisMon, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq CeladonCity_GameCorner_PrizeRoom_EventScript_TransferredToPC
	call EventScript_NameReceivedBoxMon
	goto CeladonCity_GameCorner_PrizeRoom_EventScript_TransferredToPC
	end

CeladonCity_GameCorner_PrizeRoom_EventScript_TransferredToPC:: @ 816CE12
	call EventScript_TransferredToPC
	goto CeladonCity_GameCorner_PrizeRoom_EventScript_EndPrizeExchange
	end

CeladonCity_GameCorner_PrizeRoom_EventScript_PrizeClerkTMs:: @ 816CE1D
	lock
	faceplayer
	goto_if_unset FLAG_GOT_COIN_CASE, CeladonCity_GameCorner_PrizeRoom_EventScript_NeedCoinCase
	goto_if_questlog EventScript_ReleaseEnd
	showcoinsbox 0, 0
	msgbox CeladonCity_GameCorner_PrizeRoom_Text_WeExchangeCoinsForPrizes
	goto CeladonCity_GameCorner_PrizeRoom_EventScript_ChoosePrizeTM
	end

CeladonCity_GameCorner_PrizeRoom_EventScript_ChoosePrizeTM:: @ 816CE47
	message CeladonCity_GameCorner_PrizeRoom_Text_WhichPrize
	waitmessage
	multichoice 11, 0, MULTICHOICE_GAME_CORNER_TMPRIZES, FALSE
	switch VAR_RESULT
	case 0, CeladonCity_GameCorner_PrizeRoom_EventScript_TM13
	case 1, CeladonCity_GameCorner_PrizeRoom_EventScript_TM23
	case 2, CeladonCity_GameCorner_PrizeRoom_EventScript_TM24
	case 3, CeladonCity_GameCorner_PrizeRoom_EventScript_TM30
	case 4, CeladonCity_GameCorner_PrizeRoom_EventScript_TM35
	case 5, CeladonCity_GameCorner_PrizeRoom_EventScript_EndPrizeExchange
	case 127, CeladonCity_GameCorner_PrizeRoom_EventScript_EndPrizeExchange
	end

CeladonCity_GameCorner_PrizeRoom_EventScript_TM13:: @ 816CEA5
	setvar VAR_TEMP_1, ITEM_TM13
	setvar VAR_TEMP_2, 4000
	getmovename 1, MOVE_ICE_BEAM
	goto CeladonCity_GameCorner_PrizeRoom_EventScript_ConfirmPrizeTM
	end

CeladonCity_GameCorner_PrizeRoom_EventScript_TM23:: @ 816CEB9
	setvar VAR_TEMP_1, ITEM_TM23
	setvar VAR_TEMP_2, 3500
	getmovename 1, MOVE_IRON_TAIL
	goto CeladonCity_GameCorner_PrizeRoom_EventScript_ConfirmPrizeTM
	end

CeladonCity_GameCorner_PrizeRoom_EventScript_TM24:: @ 816CECD
	setvar VAR_TEMP_1, ITEM_TM24
	setvar VAR_TEMP_2, 4000
	getmovename 1, MOVE_THUNDERBOLT
	goto CeladonCity_GameCorner_PrizeRoom_EventScript_ConfirmPrizeTM
	end

CeladonCity_GameCorner_PrizeRoom_EventScript_TM30:: @ 816CEE1
	setvar VAR_TEMP_1, ITEM_TM30
	setvar VAR_TEMP_2, 4500
	getmovename 1, MOVE_SHADOW_BALL
	goto CeladonCity_GameCorner_PrizeRoom_EventScript_ConfirmPrizeTM
	end

CeladonCity_GameCorner_PrizeRoom_EventScript_TM35:: @ 816CEF5
	setvar VAR_TEMP_1, ITEM_TM35
	setvar VAR_TEMP_2, 4000
	getmovename 1, MOVE_FLAMETHROWER
	goto CeladonCity_GameCorner_PrizeRoom_EventScript_ConfirmPrizeTM
	end

CeladonCity_GameCorner_PrizeRoom_EventScript_ConfirmPrizeTM:: @ 816CF09
	msgbox CeladonCity_GameCorner_PrizeRoom_Text_YouWantTM, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq CeladonCity_GameCorner_PrizeRoom_EventScript_EndPrizeExchange
	goto CeladonCity_GameCorner_PrizeRoom_EventScript_TryGivePrizeTM
	end

CeladonCity_GameCorner_PrizeRoom_EventScript_ConfirmPrizeItem:: @ 816CF22
	getitemname 0, VAR_TEMP_1
	msgbox CeladonCity_GameCorner_PrizeRoom_Text_YouWantPrize, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq CeladonCity_GameCorner_PrizeRoom_EventScript_EndPrizeExchange
	goto CeladonCity_GameCorner_PrizeRoom_EventScript_TryGivePrize
	end

CeladonCity_GameCorner_PrizeRoom_EventScript_TryGivePrize:: @ 816CF3F
	getitemname 0, VAR_TEMP_1
	checkcoins VAR_RESULT
	compare VAR_RESULT, VAR_TEMP_2
	goto_if_lt CeladonCity_GameCorner_PrizeRoom_EventScript_NotEnoughCoins
	checkitemspace VAR_TEMP_1, 1
	compare VAR_RESULT, FALSE
	goto_if_eq CeladonCity_GameCorner_PrizeRoom_EventScript_BagFull
	removecoins VAR_TEMP_2
	updatecoinsbox 0, 5
	giveitem VAR_TEMP_1
	goto CeladonCity_GameCorner_PrizeRoom_EventScript_EndPrizeExchange
	end

CeladonCity_GameCorner_PrizeRoom_EventScript_TryGivePrizeTM::
	getitemname 0, VAR_TEMP_1
	checkcoins VAR_RESULT
	compare VAR_RESULT, VAR_TEMP_2
	goto_if_lt CeladonCity_GameCorner_PrizeRoom_EventScript_NotEnoughCoins
	checkitem VAR_TEMP_1, 1
	compare VAR_RESULT, TRUE
	goto_if_eq CeladonCity_GameCorner_PrizeRoom_EventScript_TMAlreadyOwned
	removecoins VAR_TEMP_2
	updatecoinsbox 0, 5
	giveitem VAR_TEMP_1
	goto CeladonCity_GameCorner_PrizeRoom_EventScript_EndPrizeExchange
	end

CeladonCity_GameCorner_PrizeRoom_EventScript_BagFull:: @ 816CF79
	textcolor 3
	msgbox Text_TooBadBagFull
	hidecoinsbox 0, 0
	release
	end

CeladonCity_GameCorner_PrizeRoom_EventScript_TMAlreadyOwned:: @ 816CF79
	textcolor 3
	msgbox CeladonCity_GameCorner_PrizeRoom_Text_AlreadyHaveTM
	hidecoinsbox 0, 0
	release
	end

CeladonCity_GameCorner_PrizeRoom_EventScript_PrizeClerkItems:: @ 816CF88
	lock
	faceplayer
	goto_if_unset FLAG_GOT_COIN_CASE, CeladonCity_GameCorner_PrizeRoom_EventScript_NeedCoinCase
	goto_if_questlog EventScript_ReleaseEnd
	showcoinsbox 0, 0
	msgbox CeladonCity_GameCorner_PrizeRoom_Text_WeExchangeCoinsForPrizes
	goto CeladonCity_GameCorner_PrizeRoom_EventScript_ChoosePrizeItem
	end

CeladonCity_GameCorner_PrizeRoom_EventScript_ChoosePrizeItem:: @ 816CFB2
	message CeladonCity_GameCorner_PrizeRoom_Text_WhichPrize
	waitmessage
	multichoice 10, 0, MULTICHOICE_GAME_CORNER_BATTLE_ITEM_PRIZES, FALSE
	switch VAR_RESULT
	case 4, CeladonCity_GameCorner_PrizeRoom_EventScript_SmokeBall
	case 0, CeladonCity_GameCorner_PrizeRoom_EventScript_MiracleSeed
	case 1, CeladonCity_GameCorner_PrizeRoom_EventScript_Charcoal
	case 2, CeladonCity_GameCorner_PrizeRoom_EventScript_MysticWater
	case 3, CeladonCity_GameCorner_PrizeRoom_EventScript_YellowFlute
	case 5, CeladonCity_GameCorner_PrizeRoom_EventScript_EndPrizeExchange
	case 127, CeladonCity_GameCorner_PrizeRoom_EventScript_EndPrizeExchange
	end

CeladonCity_GameCorner_PrizeRoom_EventScript_SmokeBall:: @ 816D010
	setvar VAR_TEMP_1, ITEM_SMOKE_BALL
	setvar VAR_TEMP_2, 800
	goto CeladonCity_GameCorner_PrizeRoom_EventScript_ConfirmPrizeItem
	end

CeladonCity_GameCorner_PrizeRoom_EventScript_MiracleSeed:: @ 816D020
	setvar VAR_TEMP_1, ITEM_RARE_CANDY
	setvar VAR_TEMP_2, 200
	goto CeladonCity_GameCorner_PrizeRoom_EventScript_ConfirmPrizeItem
	end

CeladonCity_GameCorner_PrizeRoom_EventScript_Charcoal:: @ 816D030
	setvar VAR_TEMP_1, ITEM_MAX_REVIVE
	setvar VAR_TEMP_2, 333
	goto CeladonCity_GameCorner_PrizeRoom_EventScript_ConfirmPrizeItem
	end

CeladonCity_GameCorner_PrizeRoom_EventScript_MysticWater:: @ 816D040
	setvar VAR_TEMP_1, ITEM_FULL_RESTORE
	setvar VAR_TEMP_2, 333
	goto CeladonCity_GameCorner_PrizeRoom_EventScript_ConfirmPrizeItem
	end

CeladonCity_GameCorner_PrizeRoom_EventScript_YellowFlute:: @ 816D050
	setvar VAR_TEMP_1, ITEM_YELLOW_FLUTE
	setvar VAR_TEMP_2, 1600
	goto CeladonCity_GameCorner_PrizeRoom_EventScript_ConfirmPrizeItem
	end
