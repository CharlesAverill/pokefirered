EventScript_UseSurf:: @ 81A6AC8
	goto_if_questlog EventScript_UseSurfEnd
	getspeciesname 0, SPECIES_LAPRAS
	setfieldeffectarg 0, VAR_RESULT
	lockall
	msgbox Text_WantToSurf, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq EventScript_UseSurfRelease
	/*msgbox Text_SummonedSurf*/
	setvar VAR_0x8000, SPECIES_LAPRAS
	dofieldeffect FLDEFF_USE_SURF

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