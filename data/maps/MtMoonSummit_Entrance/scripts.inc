MtMoonSummit_Entrance_MapScripts::
	.byte 0

MtMoonSummit_Entrance_Hiker::
    lock
    faceplayer
    msgbox MtMoonSummit_Entrance_Hiker_Text
    release
    end

MtMoonSummit_Entrance_Hiker_Text::
    .string "It took me a long time, but\n"
    .string "I finally carved a path to\l"
    .string "the summit with my Onix. I\l"
    .string "hope you enjoy the summit!$"
