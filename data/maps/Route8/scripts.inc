Route8_MapScripts::
    map_script MAP_SCRIPT_ON_TRANSITION, Transition_Route8
    .byte 0

Transition_Route8::
    setflag FLAG_VISITED_ROUTE_8
	end

Route8_EventScript_UndergroundPathSign:: @ 8167FC6
	msgbox Route8_Text_UndergroundPathSign, MSGBOX_SIGN
	end
