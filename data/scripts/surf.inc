EventScript_UseSurf:: @ 81A6AC8
	goto_if_questlog EventScript_UseSurfEnd
	lockall
	goto_if_unset FLAG_BADGE05_GET, EventScript_UseSurfRelease
	goto_if_unset FLAG_GOT_HM03, EventScript_UseSurfRelease
	setfieldeffectarg 0, VAR_RESULT
	msgbox Text_WantToSurf, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq EventScript_UseSurfRelease
	getspeciesname 0, SPECIES_LAPRAS
	getmovename 1, MOVE_SURF
	msgbox Text_MonUsedMove
	closemessage
	setvar VAR_0x8000, SPECIES_LAPRAS
	setflag FLAG_CUSTOM_POKE_HM
	dofieldeffect FLDEFF_USE_SURF
	end

Text_SummonedSurf::
    .string "{PLAYER} summoned LAPRAS\n"
    .string "to use SURF!$"

EventScript_UseSurfRelease:@ 81A6B0B
	releaseall

EventScript_UseSurfEnd: @ 81A6B0C
	end

EventScript_CurrentTooFast:: @ 81A6B0D
	lockall
	msgbox Text_CurrentTooFast
	releaseall
	end