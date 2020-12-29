HemlockTown_House3_MapScripts::
	.byte 0

HemlockTown_House3_OldMan::
    lock
    faceplayer
    msgbox HemlockTown_House3_Text_WantToHear, MSGBOX_YESNO
    compare VAR_RESULT, NO
    goto_if_eq HemlockTown_House3_DontWantToHear
    msgbox HemlockTown_House3_Text_MentionCelebi
    drawmonpic SPECIES_CELEBI, 10, 3
	delay 20
	waitbuttonpress
	erasemonpic
	msgbox HemlockTown_House3_Text_TalkAboutCelebi
    release
    end

HemlockTown_House3_DontWantToHear::
    msgbox HemlockTown_House3_Text_DontWantToHear
    release
    end
