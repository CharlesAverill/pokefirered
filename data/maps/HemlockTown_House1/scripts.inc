HemlockTown_House1_MapScripts::
	.byte 0

HemlockTown_Agatha::
    lock
    faceplayer
    goto_if_unset PLAYER_IS_CHAMPION, HemlockTown_Agatha_PlayerIsNotChampion
    HemlockTown_Agatha_PlayerIsChampion_Text
    release
    end

HemlockTown_Agatha_PlayerIsNotChampion::
    msgbox HemlockTown_Agatha_PlayerIsNotChampion_Text
    release
    end