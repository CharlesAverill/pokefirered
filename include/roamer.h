#ifndef GUARD_ROAMER_H
#define GUARD_ROAMER_H

#include "global.h"

#define MAX_NUM_ROAMERS 5
#define gRoamers ((struct Roamer*) 0x203BA30)

#define gLastSelectedRoamer (*((u8*) 0x203F3AE))

void ClearRoamerData(void);
void ClearRoamerLocationData(void);
void InitRoamer(void);
void UpdateLocationHistoryForRoamers(void);
void RoamersMoveToOtherLocationSet(void);
void RoamersMove(void);
bool8 IsRoamerAt(u8 mapGroup, u8 mapNum);
void CreateRoamerMonInstance(void);
u8 TryStartRoamerEncounter(void);
void UpdateFoughtRoamerHPStatus(struct Pokemon *mon);
void SetRoamerInactive(void);
void GetRoamerLocation(u8 *mapGroup, u8 *mapNum);
u16 GetRoamerLocationMapSectionId(void);

#endif // GUARD_ROAMER_H
