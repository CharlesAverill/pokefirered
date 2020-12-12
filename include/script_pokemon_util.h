#ifndef GUARD_SCRIPT_POKEMON_UTIL_H
#define GUARD_SCRIPT_POKEMON_UTIL_H

bool8 ScriptGiveMon(u16 species, u8 level, u16 item, u32 unk1, u32 unk2, u8 unk3);
bool8 ScriptGiveMonWithStats(u16 species, u8 level, u16 item, u8 isShiny, u8 isEgg, u8 *stats, u8 *EVs, u8 *IVs);
bool8 ScriptGiveEgg(u16 species);
void ScriptSetMonMoveSlot(u8 partyIdx, u16 move, u8 slot);
void HealPlayerParty(void);
void ReducePlayerPartyToThree(void);
void CreateScriptedWildMon(u16 species, u8 level, u16 item);

#endif //GUARD_SCRIPT_POKEMON_UTIL_H
