Route9_MapScripts::
    map_script MAP_SCRIPT_ON_TRANSITION, Transition_Route9
    .byte 0

Transition_Route9::
    setflag FLAG_VISITED_ROUTE_9
	end

Route9_EventScript_RouteSign:: @ 8167FD0
	msgbox Route9_Text_RouteSign, MSGBOX_SIGN
	end
