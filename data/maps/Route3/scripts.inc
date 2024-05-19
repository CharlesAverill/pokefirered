Route3_MapScripts::
    map_script MAP_SCRIPT_ON_TRANSITION, Transition_Route3
    .byte 0

Transition_Route3::
    setflag FLAG_VISITED_ROUTE_3
	end

Route3_EventScript_Youngster:: @ 8167F78
	msgbox Route3_Text_TunnelFromCeruleanTiring, MSGBOX_NPC
	end

Route3_EventScript_RouteSign:: @ 8167F81
	msgbox Route3_Text_RouteSign, MSGBOX_SIGN
	end
