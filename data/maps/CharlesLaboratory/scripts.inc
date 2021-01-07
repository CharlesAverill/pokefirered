CharlesLaboratory_MapScripts::
	.byte 0

CharlesLaboratory_TalkToCharles::
    lock
    goto_if_unset FLAG_SOLOMON_DONE, CharlesLaboratory_Solomon_Not_Done
    faceplayer
    goto_if_set FLAG_CHARLES_DONE, CharlesLaboratory_Charles_Done
    goto_if_set FLAG_FOUGHT_DEOXYS, CharlesLaboratory_Fought_Deoxys
    checkitem ITEM_AURORA_TICKET, 1
    compare VAR_RESULT, TRUE
    goto_if_eq CharlesLaboratory_HaventUsedTicket
    msgbox CharlesLaboratory_Solomon_Done_Text1
    msgbox CharlesLaboratory_Solomon_Done_Text2
    msgbox CharlesLaboratory_Solomon_Done_Text3
    msgbox CharlesLaboratory_Solomon_Done_Text4
    checkitemspace ITEM_AURORA_TICKET, 1
    compare VAR_RESULT, FALSE
    goto_if_eq AuroraTicket_NoBagSpace
    giveitem ITEM_AURORA_TICKET
    setflag FLAG_ENABLE_SHIP_BIRTH_ISLAND
    setflag FLAG_GOT_AURORA_TICKET
    release
    end

CharlesLaboratory_Charles_Done:
    msgbox CharlesLaboratory_Charles_Done_Text
    release
    end

CharlesLaboratory_Fought_Deoxys:
    msgbox CharlesLaboratory_Completed_Text
    msgbox CharlesLaboratory_Charles_Done_Text
    setflag FLAG_CHARLES_DONE
    release
    end

AuroraTicket_NoBagSpace:
	message sText_AuroraTicketNoPlace
	release
	end

CharlesLaboratory_Solomon_Not_Done:
    msgbox CharlesLaboratory_Solomon_Not_Done_Text
    release
    end

CharlesLaboratory_HaventUsedTicket:
    msgbox CharlesLaboratory_HaventUsedTicket_Text
    release
    end

CharlesLaboratory_ComputerScreen::
    msgbox CharlesLaboratory_ComputerScreen_Text, MSGBOX_SIGN
    end

CharlesLaboratory_Machine::
    msgbox CharlesLaboratory_Machine_Text, MSGBOX_SIGN
    end

CharlesLaboratory_ParticleAccelerator::
    msgbox CharlesLaboratory_ParticleAccelerator_Text, MSGBOX_SIGN
    end
