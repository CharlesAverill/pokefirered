Route49_MapScripts::
	.byte 0

Route49_DeepWaterCave_Sign::
    msgbox Route49_DeepWaterCave_Sign_Text, MSGBOX_SIGN
    end

Route49_DeepWaterCave_Sign_Text:
    .string "DEEPWATER CAVE$"

Route49_Seel::
    lock
    msgbox Route49_Seel_Text
    release
    end

Route49_SeelTrainer::
    lock
    msgbox Route49_SeelTrainer_Text
    release
    end

Route49_Seel_Text::
    .string "Seel!"

Route49_SeelTrainer_Text::
    .string "I'm a SEEL trainer! I'm\n"
    .string "not too good at it though...\l"
    .string "They just won't cooperate!$"
