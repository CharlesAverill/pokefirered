SaffronCity_RocketMart_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SaffronCity_RocketMart_OnTransition
	.byte 0

SaffronCity_RocketMart_OnTransition::
    goto_if_set FLAG_SYS_GAME_CLEAR, SaffronCity_RocketMart_TryShowRockets
    goto SaffronCity_RocketMart_HideRockets
    end

SaffronCity_RocketMart_TryShowRockets:
	clearflag FLAG_HIDE_RM_ROCKETS
	end

SaffronCity_RocketMart_HideRockets::
    setflag FLAG_HIDE_RM_ROCKETS
    end

SaffronCity_RocketMart_1F_SellMons::
    lock
    faceplayer
	getpartysize
	compare VAR_RESULT, 2
	goto_if_lt SaffronCity_RocketMart_1F_NotEnoughMons
    getpartymonname 0, 0
    getpartymonvalue 0
    msgbox SaffronCity_RocketMart_1F_SellMons_Text, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq SaffronCity_RocketMart_1F_DontSell
	goto SaffronCity_RocketMart_1F_Sell
    release
    end

SaffronCity_RocketMart_1F_NotEnoughMons::
    msgbox SaffronCity_RocketMart_1F_NotEnoughMonsText
    release
    end

SaffronCity_RocketMart_1F_DontSell::
    textcolor 0
    msgbox SaffronCity_RocketMart_1F_DidntSell_Text
    release
    end

SaffronCity_RocketMart_1F_Sell::
    textcolor 3
    msgbox SaffronCity_RocketMart_1F_AreYouSure, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq SaffronCity_RocketMart_1F_DontSell
	msgbox SaffronCity_RocketMart_1F_PlayerSoldMonForMoney
    sellpartymon 0
    removepartymon 0
    textcolor 0
    msgbox SaffronCity_RocketMart_1F_Sold_Text
    release
    end
