HemlockTown_PokemonCenter_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, HemlockTown_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

HemlockTown_PokemonCenter_1F_OnTransition::
	setrespawn SPAWN_HEMLOCK_TOWN
	end

HemlockTown_PokemonCenter_1F_EventScript_Nurse::
	lock
	faceplayer
	call EventScript_PkmnCenterNurse
	release
	end

HemlockTown_PokemonCenter_1F_OldMan::
    lock
    faceplayer
    msgbox HemlockTown_PokemonCenter_1F_OldMan_Text
    release
    end

HemlockTown_PokemonCenter_1F_LittleGirl::
    lock
    faceplayer
    goto_if_set FLAG_GOT_HEMLOCK_BOOSTER_ITEMS, HemlockTown_PokemonCenter_1F_LittleGirl_AlreadyGotItems
    msgbox HemlockTown_PokemonCenter_1F_LittleGirl_Text
    giveitem_msg HemlockTown_PokemonCenter_1F_Text_ReceivedMiracleSeed, ITEM_MIRACLE_SEED
    giveitem_msg HemlockTown_PokemonCenter_1F_Text_ReceivedCharcoal, ITEM_CHARCOAL
    giveitem_msg HemlockTown_PokemonCenter_1F_Text_ReceivedMysticWater, ITEM_MYSTIC_WATER
    setflag FLAG_GOT_HEMLOCK_BOOSTER_ITEMS
    release
    end

HemlockTown_PokemonCenter_1F_LittleGirl_AlreadyGotItems::
    msgbox HemlockTown_PokemonCenter_1F_Text_AlreadyGotItems
    release
    end
