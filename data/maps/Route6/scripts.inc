Route6_MapScripts::
    map_script MAP_SCRIPT_ON_TRANSITION, Transition_Route6
    .byte 0

Transition_Route6::
    setflag FLAG_VISITED_ROUTE_6
	end

Route6_EventScript_UndergroundPathSign:: @ 8167FB2
	msgbox Route6_Text_UndergroundPathSign, MSGBOX_SIGN
	end
