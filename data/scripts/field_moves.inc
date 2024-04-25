EventScript_CutTree:: @ 81BDF13
	goto_if_questlog EventScript_ReleaseEnd
	lockall
	goto_if_unset FLAG_BADGE02_GET, EventScript_CantCutTree
	goto_if_unset FLAG_GOT_HM01, EventScript_CantCutTree
	setfieldeffectarg 0, VAR_RESULT
	getspeciesname 0, SPECIES_SCYTHER
	getmovename 1, MOVE_CUT
	msgbox Text_CutTreeDown, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq EventScript_DontCutTree
	msgbox Text_MonUsedMove
	closemessage
	setvar VAR_0x8000, SPECIES_SCYTHER
	setflag FLAG_CUSTOM_POKE_HM
	dofieldeffect FLDEFF_USE_CUT_ON_TREE
	waitstate
	goto EventScript_CutTreeDown
	end

EventScript_FldEffCut:: @ 81BDF6B
	lockall
	dofieldeffect FLDEFF_USE_CUT_ON_TREE
	waitstate
	goto EventScript_CutTreeDown
	end

EventScript_CutTreeDown:: @ 81BDF76
	applymovement VAR_LAST_TALKED, Movement_CutTreeDown
	waitmovement 0
	removeobject VAR_LAST_TALKED
	releaseall
	end

Movement_CutTreeDown:: @ 81BDF85
	cut_tree
	step_end

EventScript_CantCutTree:: @ 81BDF87
	msgbox Text_TreeCanBeCutDown, MSGBOX_SIGN
	releaseall
	end

EventScript_DontCutTree:: @ 81BDF91
	closemessage
	releaseall
	end

Text_CutTreeDown:: @ 81BDF94
	.string "This tree looks like it can be CUT\n"
	.string "down!\p"
	.string "Would you like to CUT it?$"

Text_MonUsedMove:: @ 81BDFD7
	.string "{PLAYER} summoned {STR_VAR_1}\n"
	.string "to use {STR_VAR_2}!$"

Text_TreeCanBeCutDown:: @ 81BDFE3
	.string "This tree looks like it can be CUT\n"
	.string "down!$"

EventScript_RockSmash:: @ 81BE00C
	goto_if_questlog EventScript_ReleaseEnd
	lockall
	goto_if_unset FLAG_BADGE06_GET, EventScript_CantSmashRock
	goto_if_unset FLAG_GOT_HM06, EventScript_CantSmashRock
	getspeciesname 0, SPECIES_GOLEM
	getmovename 1, MOVE_ROCK_SMASH
	msgbox Text_UseRockSmash, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq EventScript_DontSmashRock
	msgbox Text_MonUsedMove
	closemessage
	setvar VAR_0x8000, SPECIES_GOLEM
	setflag FLAG_CUSTOM_POKE_HM
	dofieldeffect FLDEFF_USE_ROCK_SMASH
	waitstate
	goto EventScript_UseRockSmash
	end

EventScript_FldEffRockSmash:: @ 81BE064
	lockall
	setvar VAR_0x8000, SPECIES_GOLEM
	dofieldeffect FLDEFF_USE_ROCK_SMASH
	waitstate
	goto EventScript_UseRockSmash
	end

EventScript_UseRockSmash:: @ 81BE06F
	applymovement VAR_LAST_TALKED, Movement_BreakRock
	waitmovement 0
	removeobject VAR_LAST_TALKED
	special RockSmashWildEncounter
	compare VAR_RESULT, FALSE
	goto_if_eq EventScript_RockSmashNoEncounter
	waitstate
	releaseall
	end

EventScript_RockSmashNoEncounter:: @ 81BE08D
	releaseall
	end

Movement_BreakRock:: @ 81BE08F
	rock_smash_break
	step_end

EventScript_CantSmashRock:: @ 81BE091
	msgbox Text_MonMaySmashRock, MSGBOX_SIGN
	end

EventScript_DontSmashRock:: @ 81BE09A
	closemessage
	releaseall
	end

Text_UseRockSmash:: @ 81BE09D
	.string "This rock appears to be breakable.\n"
	.string "Would you like to use ROCK SMASH?$"

Text_MonMaySmashRock:: @ 81BE0E2
	.string "It's a rugged rock, but a POKéMON\n"
	.string "may be able to smash it.$"

EventScript_StrengthBoulder:: @ 81BE11D
	goto_if_questlog EventScript_ReleaseEnd
	lockall
	goto_if_unset FLAG_BADGE04_GET, EventScript_CantMoveBoulder
	goto_if_set FLAG_SYS_USE_STRENGTH, EventScript_AlreadyUsedStrength
	goto_if_unset FLAG_GOT_HM06, EventScript_CantMoveBoulder
	setfieldeffectarg 0, VAR_RESULT
	msgbox Text_UseStrength, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq EventScript_DontUseStrength
	closemessage
	setvar VAR_0x8000, SPECIES_ARCANINE
	setflag FLAG_CUSTOM_POKE_HM
	dofieldeffect FLDEFF_USE_STRENGTH
	waitstate
	getspeciesname 0, SPECIES_ARCANINE
	goto EventScript_UseStrength
	end

EventScript_FldEffStrength:: @ 81BE16E
	lockall
	dofieldeffect FLDEFF_USE_STRENGTH
	waitstate
	goto EventScript_UseStrength
	end

EventScript_UseStrength:: @ 81BE179
	setflag FLAG_SYS_USE_STRENGTH
	msgbox Text_MonUsedStrengthCanMoveBoulders, MSGBOX_SIGN
	end

EventScript_CantMoveBoulder:: @ 81BE185
	msgbox Text_MonMayPushBoulder, MSGBOX_SIGN
	end

EventScript_AlreadyUsedStrength:: @ 81BE18E
	msgbox Text_StrengthMadeMovingBouldersPossible, MSGBOX_SIGN
	end

EventScript_DontUseStrength:: @ 81BE197
	closemessage
	releaseall
	end

Text_UseStrength:: @ 81BE19A
	.string "It's a big boulder, but a POKéMON\n"
	.string "may be able to push it aside.\p"
	.string "Would you like to use STRENGTH?$"

Text_MonUsedStrengthCanMoveBoulders:: @ 81BE1FA
	.string "{PLAYER} summoned Arcanine to\n"
	.string "use STRENGTH!\p"
	.string "{STR_VAR_1}'s STRENGTH made it\n"
	.string "possible to move boulders around!$"

Text_MonMayPushBoulder:: @ 81BE244
	.string "It's a big boulder, but a POKéMON\n"
	.string "may be able to push it aside.$"

Text_StrengthMadeMovingBouldersPossible:: @ 81BE284
	.string "STRENGTH made it possible to move\n"
	.string "boulders around.$"

EventScript_Waterfall:: @ 81BE2B7
	goto_if_questlog EventScript_ReleaseEnd
	lockall
	goto_if_unset FLAG_HIDE_FOUR_ISLAND_ICEFALL_CAVE_1F_HM07, EventScript_WaterCrashingDown
	getspeciesname 0, SPECIES_GYARADOS
	getmovename 1, MOVE_WATERFALL
	setfieldeffectarg 0, VAR_RESULT
	msgbox Text_UseWaterfall, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq EventScript_EndWaterfall
	msgbox Text_MonUsedMove
	setvar VAR_0x8000, SPECIES_GYARADOS
	setflag FLAG_CUSTOM_POKE_HM
	dofieldeffect FLDEFF_USE_WATERFALL
	goto EventScript_EndWaterfall

EventScript_CantUseWaterfall:: @ 81BE2FF
	lockall
EventScript_WaterCrashingDown:
	msgbox Text_WallOfWaterCrashingDown
EventScript_EndWaterfall:
	releaseall
	end

Text_WallOfWaterCrashingDown:: @ 81BE30A
	.string "A wall of water is crashing down\n"
	.string "with a mighty roar.$"

Text_UseWaterfall:: @ 81BE33F
	.string "It's a large waterfall.\n"
	.string "Would you like to use WATERFALL?$"

Text_MonUsedWaterfall:: @ 81BE378
	.string "{STR_VAR_1} used WATERFALL.$"

@ Unused leftover from R/S
EventScript_DeepWater:: @ 81BE38B
	lockall
	checkpartymove MOVE_DIVE
	compare VAR_RESULT, PARTY_SIZE
	goto_if_eq EventScript_MayGoUnderwater
	getpartymonname 0, VAR_RESULT
	setfieldeffectarg 0, VAR_RESULT
	setfieldeffectarg 1, 1
	msgbox Text_SeaIsDeepUseDive, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq EventScript_EndDive
	msgbox Text_MonUsedDive
	dofieldeffect FLDEFF_USE_DIVE
	goto EventScript_EndDive

EventScript_CantDive:: @ 81BE3C9
	lockall
EventScript_MayGoUnderwater:
	msgbox Text_MonMayGoUnderwater
EventScript_EndDive:
	releaseall
	end

EventScript_TrySurface:: @ 81BE3D4
	lockall
	checkpartymove MOVE_DIVE
	compare VAR_RESULT, PARTY_SIZE
	goto_if_eq EventScript_CantSurface
	getpartymonname 0, VAR_RESULT
	setfieldeffectarg 0, VAR_RESULT
	setfieldeffectarg 1, 1
	msgbox Text_LightFilteringUseDive, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq EventScript_EndSurface
	msgbox Text_MonUsedDive
	dofieldeffect FLDEFF_USE_DIVE
	goto EventScript_EndSurface

EventScript_CantSurface:: @ 81BE412
	lockall
	msgbox Text_MonMaySurface
	goto EventScript_EndSurface

EventScript_ObstacleCantSurface:: @ 81BE420
	lockall
	msgbox Text_DiveCantBeUsedHere
EventScript_EndSurface:
	releaseall
	end

Text_MonMayGoUnderwater:: @ 81BE42B
	.string "The sea is deep here. A POKéMON\n"
	.string "may be able to go underwater.$"

Text_SeaIsDeepUseDive:: @ 81BE469
	.string "The sea is deep here.\n"
	.string "Would you like to use DIVE?$"

Text_MonUsedDive:: @ 81BE49B
	.string "{STR_VAR_1} used DIVE.$"

Text_MonMaySurface:: @ 81BE4A9
	.string "Light is filtering down from above.\n"
	.string "A POKéMON may be able to surface.$"

Text_LightFilteringUseDive:: @ 81BE4EF
	.string "Light is filtering down from above.\n"
	.string "Would you like to use DIVE?$"

Text_DiveCantBeUsedHere:: @ 81BE52F
	.string "There is an obstacle above.\n"
	.string "DIVE can't be used here.$"

EventScript_FailSweetScent:: @ 81BE564
	msgbox Text_LooksLikeNothingHere, MSGBOX_SIGN
	end

Text_LooksLikeNothingHere:: @ 81BE56D
	.string "Looks like there's nothing here…$"
