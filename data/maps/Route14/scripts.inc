Route14_MapScripts::
    map_script MAP_SCRIPT_ON_TRANSITION, Transition_Route14
    .byte 0

Transition_Route14::
    setflag FLAG_VISITED_ROUTE_14
	end

Route14_EventScript_RouteSign:: @ 81680D2
	msgbox Route14_Text_RouteSign, MSGBOX_SIGN
	end
