Route23_MapScripts:: @ 81684EB
	map_script MAP_SCRIPT_ON_TRANSITION, Route23_OnTransition
	.byte 0

Route23_OnTransition:: @ 81684F1
	setflag FLAG_VISITED_ROUTE_23
	clearflag FLAG_HIDE_VICTORY_ROAD_3F_BOULDER
	setflag FLAG_HIDE_VICTORY_ROAD_2F_BOULDER
	setvar VAR_MAP_SCENE_VICTORY_ROAD_1F, 0
	setvar VAR_MAP_SCENE_VICTORY_ROAD_2F_BOULDER1, 0
	setvar VAR_MAP_SCENE_VICTORY_ROAD_2F_BOULDER2, 0
	setvar VAR_MAP_SCENE_VICTORY_ROAD_3F, 0
	end

Route23_EventScript_CascadeBadgeGuard:: @ 816850C
	lock
	faceplayer
	setvar VAR_TEMP_1, 2
	getstdstring 0, STDSTRING_CASCADE_BADGE
	goto Route23_EventScript_BadgeGuard
	end

Route23_EventScript_ThunderBadgeGuard:: @ 816851D
	lock
	faceplayer
	setvar VAR_TEMP_1, 3
	getstdstring 0, STDSTRING_THUNDER_BADGE
	goto Route23_EventScript_BadgeGuard
	end

Route23_EventScript_RainbowBadgeGuard:: @ 816852E
	lock
	faceplayer
	setvar VAR_TEMP_1, 4
	getstdstring 0, STDSTRING_RAINBOW_BADGE
	goto Route23_EventScript_BadgeGuard
	end

Route23_EventScript_SoulBadgeGuard:: @ 816853F
	lock
	faceplayer
	setvar VAR_TEMP_1, 5
	getstdstring 0, STDSTRING_SOUL_BADGE
	goto Route23_EventScript_BadgeGuard
	end

Route23_EventScript_MarshBadgeGuard:: @ 8168550
	lock
	faceplayer
	setvar VAR_TEMP_1, 6
	getstdstring 0, STDSTRING_MARSH_BADGE
	goto Route23_EventScript_BadgeGuard
	end

Route23_EventScript_VolcanoBadgeGuard:: @ 8168561
	lock
	faceplayer
	setvar VAR_TEMP_1, 7
	getstdstring 0, STDSTRING_VOLCANO_BADGE
	goto Route23_EventScript_BadgeGuard
	end

Route23_EventScript_EarthBadgeGuard:: @ 8168572
	lock
	faceplayer
	setvar VAR_TEMP_1, 8
	getstdstring 0, STDSTRING_EARTH_BADGE
	goto Route23_EventScript_BadgeGuard
	end

Route23_EventScript_CascadeBadgeGuardTrigger:: @ 8168583
	lockall
	setvar VAR_TEMP_1, 2
	setvar VAR_0x8009, 1
	getstdstring 0, STDSTRING_CASCADE_BADGE
	goto Route23_EventScript_BadgeGuardTrigger
	end

Route23_EventScript_ThunderBadgeGuardTrigger:: @ 8168598
	lockall
	setvar VAR_TEMP_1, 3
	setvar VAR_0x8009, 2
	getstdstring 0, STDSTRING_THUNDER_BADGE
	goto Route23_EventScript_BadgeGuardTrigger
	end

Route23_EventScript_RainbowBadgeGuardTrigger:: @ 81685AD
	lockall
	setvar VAR_TEMP_1, 4
	setvar VAR_0x8009, 3
	getstdstring 0, STDSTRING_RAINBOW_BADGE
	goto Route23_EventScript_BadgeGuardTrigger
	end

Route23_EventScript_SoulBadgeGuardTrigger:: @ 81685C2
	lockall
	setvar VAR_TEMP_1, 5
	setvar VAR_0x8009, 4
	getstdstring 0, STDSTRING_SOUL_BADGE
	goto Route23_EventScript_BadgeGuardTrigger
	end

Route23_EventScript_MarshBadgeGuardTrigger:: @ 81685D7
	lockall
	setvar VAR_TEMP_1, 6
	setvar VAR_0x8009, 5
	getstdstring 0, STDSTRING_MARSH_BADGE
	goto Route23_EventScript_BadgeGuardTrigger
	end

Route23_EventScript_VolcanoBadgeGuardTrigger:: @ 81685EC
	lockall
	setvar VAR_TEMP_1, 7
	setvar VAR_0x8009, 6
	getstdstring 0, STDSTRING_VOLCANO_BADGE
	goto Route23_EventScript_BadgeGuardTrigger
	end

Route23_EventScript_EarthBadgeGuardTrigger:: @ 8168601
	lockall
	setvar VAR_TEMP_1, 8
	setvar VAR_0x8009, 7
	getstdstring 0, STDSTRING_EARTH_BADGE
	goto Route23_EventScript_BadgeGuardTrigger
	end

Route23_EventScript_VictoryRoadGateSign:: @ 8168616
	msgbox Route23_Text_VictoryRoadGateSign, MSGBOX_SIGN
	end

Route23_EventScript_MtSilverTrigger::
    goto_if_set FLAG_FOUGHT_FUTURE_RED, EventScript_ReleaseEnd
	setvar VAR_0x8004, SPECIES_CELEBI
	specialvar VAR_RESULT, DoesPlayerPartyContainSpecies
	compare VAR_RESULT, TRUE
	goto_if_eq Route23_EventScript_MtSilverTrigger_HasCelebi
    msgbox Route23_Text_TurnBack
    closemessage
    applymovement OBJ_EVENT_ID_PLAYER, Route16_NorthEntrance_1F_Movement_WalkRight
    end

Route23_EventScript_MtSilverTrigger_HasCelebi::
    waitse
    goto_if_set FLAG_TEMP_1, EventScript_ReleaseEnd
    playmoncry SPECIES_CELEBI, 2
    setflag FLAG_TEMP_1
    waitmoncry
	msgbox Route23_Text_GoForth
	closemessage
    release
    end
