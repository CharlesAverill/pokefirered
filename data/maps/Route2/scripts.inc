Route2_MapScripts::
    map_script MAP_SCRIPT_ON_TRANSITION, Transition_Route2
    .byte 0

Transition_Route2::
    setflag FLAG_VISITED_ROUTE_2
	end

Route2_EventScript_RouteSign:: @ 8167F65
	msgbox Route2_Text_RouteSign, MSGBOX_SIGN
	end

Route2_EventScript_DiglettsCaveSign:: @ 8167F6E
	msgbox Route2_Text_DiglettsCave, MSGBOX_SIGN
	end

Route2_EventScript_ChanseyGroveMan::
    lock
    faceplayer
    goto_if_unset FLAG_SYS_GAME_CLEAR, Route2_EventScript_ChanseyGroveMan_PrivateProperty
    hascaughtmon SPECIES_CHANSEY
    compare VAR_RESULT, 0
    goto_if_eq Route2_EventScript_ChanseyGroveMan_PrivateProperty
    msgbox Route2_EventScript_ChanseyGroveMan_WelcomeIn_Text
    closemessage
    applymovement 8, Route2_EventScript_ChanseyGroveMan_Movement
    waitmovement 0
    removeobject 8
    setflag FLAG_HIDE_CHANSEY_GROVE_MAN
    release
    end

Route2_EventScript_ChanseyGroveMan_PrivateProperty::
    msgbox Route2_EventScript_ChanseyGroveMan_PrivateProperty_Text
    release
    end

Route2_EventScript_ChanseyGroveMan_AhTheChampion::
    msgbox Route2_EventScript_ChanseyGroveMan_AhTheChampion_Text
    release
    end

Route2_EventScript_ChanseyGroveMan_Movement::
    walk_right
    walk_right
    walk_down
    walk_down
    walk_down
    walk_right
    walk_down
    walk_down
    walk_down
    walk_down
    step_end
