Route7_MapScripts::
    map_script MAP_SCRIPT_ON_TRANSITION, Transition_Route7
    .byte 0

Transition_Route7::
    setflag FLAG_VISITED_ROUTE_7
	end

Route7_EventScript_UndergroundPathSign:: @ 8167FBC
	msgbox Route7_Text_UndergroundPathSign, MSGBOX_SIGN
	end
