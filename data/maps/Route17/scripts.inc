Route17_MapScripts::
    map_script MAP_SCRIPT_ON_TRANSITION, Transition_Route17
    .byte 0

Transition_Route17::
    setflag FLAG_VISITED_ROUTE_17
	end

Route17_EventScript_ItemsNotice:: @ 81681C0
	msgbox Route17_Text_WatchOutForDiscardedItems, MSGBOX_SIGN
	end

Route17_EventScript_TrainerTips1:: @ 81681C9
	msgbox Route17_Text_SameSpeciesGrowDifferentRates, MSGBOX_SIGN
	end

Route17_EventScript_TrainerTips2:: @ 81681D2
	msgbox Route17_Text_PressBToStayInPlace, MSGBOX_SIGN
	end

Route17_EventScript_RouteSign:: @ 81681DB
	msgbox Route17_Text_RouteSign, MSGBOX_SIGN
	end

Route17_EventScript_BallsNotice:: @ 81681E4
	msgbox Route17_Text_DontThrowGameThrowBalls, MSGBOX_SIGN
	end

Route17_EventScript_CyclingRoadSign:: @ 81681ED
	msgbox Route17_Text_CyclingRoadSign, MSGBOX_SIGN
	end
