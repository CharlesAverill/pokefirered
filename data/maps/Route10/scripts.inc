Route10_MapScripts::
    map_script MAP_SCRIPT_ON_TRANSITION, Transition_Route10
    .byte 0

Transition_Route10::
    setflag FLAG_VISITED_ROUTE_10
	end

Route10_EventScript_Unused:: @ 8167FDA
	end

Route10_EventScript_NorthRockTunnelSign:: @ 8167FDB
	msgbox Route10_Text_RockTunnelDetourToLavender, MSGBOX_SIGN
	end

Route10_EventScript_SouthRockTunnelSign:: @ 8167FE4
	msgbox Route10_Text_RockTunnel, MSGBOX_SIGN
	end

Route10_EventScript_PowerPlantSign:: @ 8167FED
	msgbox Route10_Text_PowerPlant, MSGBOX_SIGN
	end
