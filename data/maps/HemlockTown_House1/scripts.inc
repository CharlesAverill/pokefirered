HemlockTown_House1_MapScripts::
	.byte 0

HemlockTown_House1_End::
    releaseall
    end

HemlockTown_Agatha::
    textcolor 1
    lock
    faceplayer
    goto_if_unset FLAG_SYS_GAME_CLEAR, HemlockTown_Agatha_PlayerIsNotChampion
    msgbox HemlockTown_Agatha_PlayerIsChampion_Text
    release
    end

HemlockTown_Agatha_PlayerIsNotChampion::
    textcolor 1
    lock
    faceplayer
    msgbox HemlockTown_Agatha_HasMet_Text
    release
    end

HemlockTown_Agatha_HasntMet::
    goto_if_set FLAG_SYS_GAME_CLEAR, HemlockTown_House1_End
    goto_if_set FLAG_MET_AGATHA, HemlockTown_House1_End
    lockall
    textcolor 1
    applymovement 1, Movement_FaceDown
    waitmovement 0
    playse SE_PIN
    applymovement 1, Movement_ExclamationMark
    waitmovement 0
    msgbox HemlockTown_Agatha_ComeHere
    waitmessage
    closemessage
    applymovement OBJ_EVENT_ID_PLAYER, HemlockTown_Player_WalkUp
    waitmovement 0
    msgbox HemlockTown_Agatha_HasntMet_Text
    waitmessage
    closemessage
    applymovement 1, Movement_FaceRight
    setflag FLAG_MET_AGATHA
    releaseall
    end

HemlockTown_Player_WalkUp::
    walk_up
    walk_up
    walk_up
    walk_up
    step_end
