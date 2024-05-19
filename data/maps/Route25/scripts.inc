Route25_MapScripts::
    map_script MAP_SCRIPT_ON_TRANSITION, Transition_Route25
    .byte 0

Transition_Route25::
    setflag FLAG_VISITED_ROUTE_25
	end

Route25_EventScript_SeaCottageSign:: @ 8168746
	msgbox Route25_Text_SeaCottageSign, MSGBOX_SIGN
	end

Route25_EventScript_Man:: @ 816874F
	msgbox Route25_Text_AreYouHereAlone, MSGBOX_NPC
	end
