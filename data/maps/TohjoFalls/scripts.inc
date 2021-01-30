TohjoFalls_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, TohjoFalls_OnTransition
	.byte 0

TohjoFalls_OnTransition::
	setworldmapflag FLAG_WORLD_MAP_TOHJO_FALLS
	end
