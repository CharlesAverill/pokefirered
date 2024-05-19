Route4_MapScripts::
    map_script MAP_SCRIPT_ON_TRANSITION, Transition_Route4
    .byte 0

Transition_Route4::
    setflag FLAG_VISITED_ROUTE_4
	end

Route4_EventScript_Unused:: @ 8167F8B
	end

Route4_EventScript_Woman:: @ 8167F8C
	msgbox Route4_Text_TrippedOverGeodude, MSGBOX_NPC
	end

Route4_EventScript_MtMoonSign:: @ 8167F95
	msgbox Route4_Text_MtMoonEntrance, MSGBOX_SIGN
	end

Route4_EventScript_RouteSign:: @ 8167F9E
	msgbox Route4_Text_RouteSign, MSGBOX_SIGN
	end

Route4_Summit_Sign::
    msgbox Route4_Summit_Sign_Text, MSGBOX_SIGN
    end

Route4_Summit_Sign_Text::
    .string "MT. MOON\n"
    .string "SUMMIT ENTRANCE$"
