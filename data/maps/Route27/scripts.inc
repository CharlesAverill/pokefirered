Route27_MapScripts::
	.byte 0

Route27_Policeman::
    lock
    faceplayer
    msgbox Route27_Policeman_Text
    release
    end

Route27_Charles::
    lock
    faceplayer
    msgbox Route27_Charles_Text
    closemessage
    setflag FLAG_MET_CREATOR
    applymovement 2, Route27_Charles_Movement
    waitmovement 0
    removeobject 2
    release
    end

Route27_Charles_Movement::
    walk_left
    walk_left
    walk_left
    walk_left
    walk_left
    walk_left
    walk_left
    step_end
