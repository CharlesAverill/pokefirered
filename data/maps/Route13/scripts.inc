Route13_MapScripts::
    map_script MAP_SCRIPT_ON_TRANSITION, Transition_Route13
    .byte 0

Transition_Route13::
    setflag FLAG_VISITED_ROUTE_13
	end

Route13_EventScript_TrainerTips1:: @ 81680B6
	msgbox Route13_Text_LookToLeftOfThatPost, MSGBOX_SIGN
	end

Route13_EventScript_TrainerTips2:: @ 81680BF
	msgbox Route13_Text_SelectToSwitchItems, MSGBOX_SIGN
	end

Route13_EventScript_RouteSign:: @ 81680C8
	msgbox Route13_Text_RouteSign, MSGBOX_SIGN
	end
