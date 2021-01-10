Route16_ChanseyGrove_House_MapScripts::
    map_script MAP_SCRIPT_ON_TRANSITION, Route16_ChanseyGrove_House_OnTransition
	.byte 0

Route16_ChanseyGrove_House_OnTransition::
    setworldmapflag FLAG_WORLD_MAP_CHANSEY_GROVE
    end

Route16_ChanseyGrove_House_ChanseyMan::
    lock
    faceplayer
    msgbox Route16_ChanseyGrove_House_ChanseyMan_MyChanseysLikeHelpingOthers_Text
    closemessage
    msgbox Route16_ChanseyGrove_House_ChanseyMan_WantToBattle_Text, MSGBOX_YESNO
    closemessage
    compare VAR_RESULT, NO
    goto_if_eq Route16_ChanseyGrove_House_ChanseyMan_DontBattle
    goto Route16_ChanseyGrove_House_ChanseyMan_Battle
    release
    end

Route16_ChanseyGrove_House_ChanseyMan_Battle::
    cleartrainerflag TRAINER_CHANSEYMAN
    trainerbattle_single TRAINER_CHANSEYMAN, Route16_ChanseyGrove_House_ChanseyMan_LetsDoIt_Text, Route16_ChanseyGrove_House_ChanseyMan_DefeatText
    msgbox Route16_ChanseyGrove_House_ChanseyMan_WantToBattleAgain_Text, MSGBOX_YESNO
    compare VAR_RESULT, YES
    goto_if_eq Route16_ChanseyGrove_House_ChanseyMan_Battle
    goto_if_unset FLAG_MENTIONED_EV_TRAINERS, Route16_ChanseyGrove_House_ChanseyMan_MentionEVTrainers
    release
    end

Route16_ChanseyGrove_House_ChanseyMan_DontBattle::
    msgbox Route16_ChanseyGrove_House_ChanseyMan_DontBattle_Text
    release
    end

Route16_ChanseyGrove_House_ChanseyMan_MentionEVTrainers::
    msgbox Route16_ChanseyGrove_House_ChanseyMan_MentionEVTrainers_Text
    setflag FLAG_MENTIONED_EV_TRAINERS
    release
    end
