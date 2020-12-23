#ifndef GUARD_ROAMER_H
#define GUARD_ROAMER_H

#include "global.h"

#define MAX_NUM_ROAMERS 5
#define gRoamers ((struct Roamer*) 0x203BA30)

#define gLastSelectedRoamer (*((u8*) 0x203F3AE))

void ClearRoamerData(void);
void sp129_InitRoamer(void);
void UpdateLocationHistoryForRoamer(void);
void RoamersMoveToOtherLocationSet(void);
void RoamersMove(void);
bool8 TryStartRoamerEncounter(u8 environment);
void UpdateFoughtRoamerHPStatus(struct Pokemon *mon);
void SetFoughtRoamerInactive(void);
void GetRoamerLocation(u8* mapGroup, u8* mapNum, u8 id);
bool8 IsSpeciesRoaming(u16 species);
void GetMapGroupAndMapNumOfRoamer(u16 species, u8* mapGroup, u8* mapNum);
void BattleSetup_StartRoamerBattle(void);

#endif // GUARD_ROAMER_H
