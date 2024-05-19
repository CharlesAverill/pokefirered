Route5_MapScripts::
    map_script MAP_SCRIPT_ON_TRANSITION, Transition_Route5
    .byte 0

Transition_Route5::
    setflag FLAG_VISITED_ROUTE_5
	end

Route5_EventScript_UndergroundPathSign:: @ 8167FA8
	msgbox Route5_Text_UndergroundPathSign, MSGBOX_SIGN
	end
