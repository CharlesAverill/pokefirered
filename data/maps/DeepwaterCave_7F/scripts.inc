DeepwaterCave_7F_MapScripts::
	.byte 0

/*
Button order is 1, 4, 6, 2, 5, 3
*/

DeepwaterCave_7F_Button1::
    lockall
    setvar VAR_0x8004, FLAG_DWC_SWITCH_1
    goto DeepwaterCave_7F_SetFlag

DeepwaterCave_7F_Button2::
    lockall
    goto_if_unset FLAG_DWC_SWITCH_4, DeepwaterCave_7F_ClearFlags
    setvar VAR_0x8004, FLAG_DWC_SWITCH_2
    goto DeepwaterCave_7F_SetFlag

DeepwaterCave_7F_Button3::
    lockall
    goto_if_unset FLAG_DWC_SWITCH_5, DeepwaterCave_7F_ClearFlags
    playse SE_THUNDER
    waitse
    playse SE_THUNDER2
    waitse
    hideobject 1, 0
    releaseall
    end

DeepwaterCave_7F_Button4::
    lockall
    goto_if_unset FLAG_DWC_SWITCH_1, DeepwaterCave_7F_ClearFlags
    setvar VAR_0x8004, FLAG_DWC_SWITCH_4
    goto DeepwaterCave_7F_SetFlag

DeepwaterCave_7F_Button5::
    lockall
    goto_if_unset FLAG_DWC_SWITCH_2, DeepwaterCave_7F_ClearFlags
    setvar VAR_0x8004, FLAG_DWC_SWITCH_5
    goto DeepwaterCave_7F_SetFlag

DeepwaterCave_7F_Button6::
    lockall
    goto_if_unset FLAG_DWC_SWITCH_4, DeepwaterCave_7F_ClearFlags
    setvar VAR_0x8004, FLAG_DWC_SWITCH_6
    goto DeepwaterCave_7F_SetFlag

DeepwaterCave_7F_SetFlag::
    playse SE_CLICK
    waitse
    setflag VAR_0x8004
    releaseall
    end

DeepwaterCave_7F_ClearFlags::
    playse SE_FAILURE
    waitse
    clearflag FLAG_DWC_SWITCH_1
    clearflag FLAG_DWC_SWITCH_2
    clearflag FLAG_DWC_SWITCH_3
    clearflag FLAG_DWC_SWITCH_4
    clearflag FLAG_DWC_SWITCH_5
    clearflag FLAG_DWC_SWITCH_6
    releaseall
    end
