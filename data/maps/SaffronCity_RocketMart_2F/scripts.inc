SaffronCity_RocketMart_2F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SaffronCity_RocketMart_OnTransition
	.byte 0

SaffronCity_RocketMart_2F_Scene::
    clearflag FLAG_SYS_GAME_CLEAR
    applymovement 3, Movement_JumpInPlaceDown
    waitmovement 0
    textcolor 1
    msgbox SaffronCity_RocketMart_2F_Jesse_Text
    closemessage

    applymovement 11, Movement_JumpInPlaceDown
    waitmovement 0
    textcolor 3
    msgbox SaffronCity_RocketMart_2F_Meowth_Text
    closemessage

    applymovement 2, Movement_JumpInPlaceLeft
    waitmovement 0
    textcolor 0
    msgbox SaffronCity_RocketMart_2F_James_Text
    closemessage

    applymovement 3, Movement_FaceLeft
    applymovement 11, Movement_FaceLeft
    waitmovement 0
    applymovement 2, SaffronCity_RocketMart_2F_Wait
    waitmovement 0

    textcolor 3
    msgbox SaffronCity_RocketMart_2F_Reply
    closemessage

    applymovement 2, Movement_FaceRight
    waitmovement 0
    applymovement 2, SaffronCity_RocketMart_2F_Wait
    waitmovement 0
    applymovement 2, SaffronCity_RocketMart_2F_Wait
    waitmovement 0
    applymovement 2, SaffronCity_RocketMart_2F_Wait
    waitmovement 0

    applymovement 2, Movement_FaceLeft
    applymovement 11, Movement_FaceDown
    applymovement 3, Movement_FaceDown

    closemessage

    end

SaffronCity_RocketMart_2F_Wait::
    delay_16
    delay_16
    step_end