Route11_MapScripts::
    map_script MAP_SCRIPT_ON_TRANSITION, Transition_Route11
    .byte 0

Transition_Route11::
    setflag FLAG_VISITED_ROUTE_11
	end

Route11_EventScript_DiglettsCaveSign:: @ 8167FF7
	msgbox Route11_Text_DiglettsCave, MSGBOX_SIGN
	end
