Route19_MapScripts::
    map_script MAP_SCRIPT_ON_TRANSITION, Transition_Route19
    .byte 0

Transition_Route19::
    setflag FLAG_VISITED_ROUTE_19
	end

Route19_EventScript_RouteSign:: @ 8168232
	msgbox Route19_Text_RouteSign, MSGBOX_SIGN
	end
