DeepwaterCave_7F_MapScripts::
	.byte 0

/*
Button order is 1, 4, 6, 2, 5, 3
*/

DeepwaterCave_7F_Button1::
    call DeepwaterCave_7F_ClearFlags
    setvar VAR_0x8004, FLAG_DWC_SWITCH_1
    call DeepwaterCave_7F_SetFlag
    end

DeepwaterCave_7F_Button2::
    goto_if_unset FLAG_DWC_SWITCH_4, DeepwaterCave_7F_ClearFlags
    setvar VAR_0x8004, FLAG_DWC_SWITCH_2
    call DeepwaterCave_7F_SetFlag
    end

DeepwaterCave_7F_Button3::
    goto_if_unset FLAG_DWC_SWITCH_5, DeepwaterCave_7F_ClearFlags
    playse SE_THUNDER
    waitse
    playse SE_THUNDER2
    waitse
    hideobject 1, 0
    end

DeepwaterCave_7F_Button4::
    goto_if_unset FLAG_DWC_SWITCH_1, DeepwaterCave_7F_ClearFlags
    setvar VAR_0x8004, FLAG_DWC_SWITCH_4
    call DeepwaterCave_7F_SetFlag
    end

DeepwaterCave_7F_Button5::
    goto_if_unset FLAG_DWC_SWITCH_2, DeepwaterCave_7F_ClearFlags
    setvar VAR_0x8004, FLAG_DWC_SWITCH_5
    call DeepwaterCave_7F_SetFlag
    end

DeepwaterCave_7F_Button6::
    goto_if_unset FLAG_DWC_SWITCH_4, DeepwaterCave_7F_ClearFlags
    setvar VAR_0x8004, FLAG_DWC_SWITCH_6
    call DeepwaterCave_7F_SetFlag
    end

DeepwaterCave_7F_SetFlag::
    playse SE_CLICK
    setflag VAR_0x8004

DeepwaterCave_7F_ClearFlags::
    clearflag FLAG_DWC_SWITCH_1
    clearflag FLAG_DWC_SWITCH_2
    clearflag FLAG_DWC_SWITCH_3
    clearflag FLAG_DWC_SWITCH_4
    clearflag FLAG_DWC_SWITCH_5
    clearflag FLAG_DWC_SWITCH_6
