FourIsland_House1_MapScripts:: @ 8171C44
	.byte 0

FourIsland_House1_Max::
    lock
    faceplayer
	trainerbattle_single TRAINER_HIKER_MAX, FourIsland_House1_MaxIntro, FourIsland_House1_MaxDefeat
	msgbox FourIsland_House1_MaxPostBattle, MSGBOX_AUTOCLOSE
	end

FourIsland_House1_Avery::
    lock
    faceplayer
	trainerbattle_single TRAINER_GENTLEMAN_AVERY, FourIsland_House1_AveryIntro, FourIsland_House1_AveryDefeat
	msgbox FourIsland_House1_AveryPostBattle, MSGBOX_AUTOCLOSE
	end

FourIsland_House1_Matthew::
    lock
    faceplayer
	trainerbattle_single TRAINER_SUPER_NERD_MATTHEW, FourIsland_House1_MatthewIntro, FourIsland_House1_MatthewDefeat
	msgbox FourIsland_House1_MatthewPostBattle, MSGBOX_AUTOCLOSE
	end
