SaffronCity_RocketMart_2F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, SaffronCity_RocketMart_OnTransition
	.byte 0

SaffronCity_RocketMart_2F_Scene::
    goto_if_set FLAG_TEMP_1, EventScript_ReleaseEnd
    setflag FLAG_TEMP_1
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

SaffronCity_RocketMart_2F_Jesse::
    lock
    msgbox SaffronCity_RocketMart_2F_Jesse_IndividualText
    release
    end

SaffronCity_RocketMart_2F_James::
    lock
    msgbox SaffronCity_RocketMart_2F_James_IndividualText
    release
    end

SaffronCity_RocketMart_2F_Meowth::
    lock
    msgbox SaffronCity_RocketMart_2F_Meowth_IndividualText
    release
    end

SaffronCity_RocketMart_2F_Wait::
    delay_16
    delay_16
    step_end
