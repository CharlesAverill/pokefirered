DeepwaterCave_7F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, BirthIsland_Exterior_OnTransition
	.byte 0

/*
Button order is 1, 4, 6, 2, 5, 3
*/

DeepwaterCave_7F_OnTransition::
    clearflag FLAG_TEMP_1
    clearflag FLAG_TEMP_2
    clearflag FLAG_TEMP_3
    clearflag FLAG_TEMP_4
    clearflag FLAG_TEMP_5
    clearflag FLAG_TEMP_6

DeepwaterCave_7F_Button1::
    lockall
    goto_if_set FLAG_DWC_ROCK, DeepwaterCave_7F_end
    goto_if_set FLAG_TEMP_1, DeepwaterCave_7F_ClearFlags
    playse SE_CLICK
    waitse
    setflag FLAG_TEMP_1
    releaseall
    end

DeepwaterCave_7F_Button2::
    lockall
    goto_if_set FLAG_DWC_ROCK, DeepwaterCave_7F_end
    goto_if_set FLAG_TEMP_2, DeepwaterCave_7F_ClearFlags
    goto_if_unset FLAG_TEMP_4, DeepwaterCave_7F_ClearFlags
    playse SE_CLICK
    waitse
    setflag FLAG_TEMP_2
    releaseall
    end

DeepwaterCave_7F_Button3::
    lockall
    goto_if_set FLAG_DWC_ROCK, DeepwaterCave_7F_end
    goto_if_unset FLAG_TEMP_5, DeepwaterCave_7F_ClearFlags
    setflag FLAG_DWC_ROCK
    playse SE_THUNDER
    waitse
    playse SE_THUNDER2
    waitse
    applymovement 1, DeepwaterCave_7F_BoulderMove
    removeobject 1
    releaseall
    end

DeepwaterCave_7F_Button4::
    lockall
    goto_if_set FLAG_DWC_ROCK, DeepwaterCave_7F_end
    goto_if_set FLAG_TEMP_4, DeepwaterCave_7F_ClearFlags
    goto_if_unset FLAG_TEMP_1, DeepwaterCave_7F_ClearFlags
    playse SE_CLICK
    waitse
    setflag FLAG_TEMP_4
    releaseall
    end

DeepwaterCave_7F_Button5::
    lockall
    goto_if_set FLAG_DWC_ROCK, DeepwaterCave_7F_end
    goto_if_set FLAG_TEMP_5, DeepwaterCave_7F_ClearFlags
    goto_if_unset FLAG_TEMP_2, DeepwaterCave_7F_ClearFlags
    playse SE_CLICK
    waitse
    setflag FLAG_TEMP_5
    releaseall
    end

DeepwaterCave_7F_Button6::
    lockall
    goto_if_set FLAG_DWC_ROCK, DeepwaterCave_7F_end
    goto_if_set FLAG_TEMP_6, DeepwaterCave_7F_ClearFlags
    goto_if_unset FLAG_TEMP_4, DeepwaterCave_7F_ClearFlags
    playse SE_CLICK
    waitse
    setflag FLAG_TEMP_6
    releaseall
    end

DeepwaterCave_7F_ClearFlags::
    playse SE_FAILURE
    waitse
    clearflag FLAG_TEMP_1
    clearflag FLAG_TEMP_2
    clearflag FLAG_TEMP_3
    clearflag FLAG_TEMP_4
    clearflag FLAG_TEMP_5
    clearflag FLAG_TEMP_6
    warp MAP_DEEPWATER_CAVE_1F, 255, 7, 7
    end

DeepwaterCave_7F_BoulderMove::
    walk_right
    step_end

DeepwaterCave_7F_end::
    releaseall
    end
