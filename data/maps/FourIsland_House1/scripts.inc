FourIsland_House1_MapScripts:: @ 8171C44
	.byte 0

FourIsland_House1_Max::
    lock
    faceplayer
    goto_if_unset FLAG_SYS_GAME_CLEAR, FourIsland_House1_MaxWeak
	trainerbattle_single TRAINER_HIKER_MAX, FourIsland_House1_MaxIntro, FourIsland_House1_MaxDefeat
	msgbox FourIsland_House1_MaxPostBattle, MSGBOX_AUTOCLOSE
	release
	end

FourIsland_House1_Avery::
    lock
    faceplayer
    goto_if_unset FLAG_SYS_GAME_CLEAR, FourIsland_House1_AveryWeak
	trainerbattle_single TRAINER_GENTLEMAN_AVERY, FourIsland_House1_AveryIntro, FourIsland_House1_AveryDefeat
	msgbox FourIsland_House1_AveryPostBattle, MSGBOX_AUTOCLOSE
	release
	end

FourIsland_House1_Matthew::
    lock
    faceplayer
    goto_if_unset FLAG_SYS_GAME_CLEAR, FourIsland_House1_MatthewWeak
	trainerbattle_single TRAINER_SUPER_NERD_MATTHEW, FourIsland_House1_MatthewIntro, FourIsland_House1_MatthewDefeat
	msgbox FourIsland_House1_MatthewPostBattle, MSGBOX_AUTOCLOSE
	release
	end

FourIsland_House1_MaxWeak::
    msgbox FourIsland_House1_MaxWeak_Text
    release
    end

FourIsland_House1_AveryWeak::
    msgbox FourIsland_House1_AveryWeak_Text
    release
    end

FourIsland_House1_MatthewWeak::
    msgbox FourIsland_House1_MatthewWeak_Text
    release
    end
