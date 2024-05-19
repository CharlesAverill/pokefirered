Route15_MapScripts::
    map_script MAP_SCRIPT_ON_TRANSITION, Transition_Route15
    .byte 0

Transition_Route15::
    setflag FLAG_VISITED_ROUTE_15
	end

Route15_EventScript_RouteSign:: @ 81680DC
	msgbox Route15_Text_RouteSign, MSGBOX_SIGN
	end
