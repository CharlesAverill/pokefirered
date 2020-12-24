#ifndef GUARD_ROAMER_H
#define GUARD_ROAMER_H

#include "global.h"

#define MAX_NUM_ROAMERS 5
#define gRoamers ((struct Roamer*) 0x203BA30)

#define gLastSelectedRoamer (*((u8*) 0x203F3AE))

struct Roamer
{
    /*0x00*/ u32 ivs;
    /*0x04*/ u32 personality;
    /*0x08*/ u16 species;
    /*0x0A*/ u16 hp;
    /*0x0C*/ u8 level;
    /*0x0D*/ u8 status;
    /*0x0E*/ u8 canAppearOnLand;
    /*0x0F*/ u8 canAppearOnWater;
    /*0x10*/ u8 locationHistory[3][2];
    /*0x16*/ u8 location[2];
    /*SIZE = 0x18*/
};

void ClearRoamerData(void);
void sp129_InitRoamer(void);
void UpdateLocationHistoryForRoamer(void);
void RoamersMoveToOtherLocationSet(void);
void RoamersMove(void);
bool8 TryStartRoamerEncounter();
void UpdateFoughtRoamerHPStatus(struct Pokemon *mon);
void SetFoughtRoamerInactive(void);
void GetRoamerLocation(u8* mapGroup, u8* mapNum, u8 id);
bool8 IsSpeciesRoaming(u16 species);
void GetMapGroupAndMapNumOfRoamer(u16 species, u8* mapGroup, u8* mapNum);
void BattleSetup_StartRoamerBattle(void);
u16 GetRoamerLocationMapSectionId(u16 species);

#endif // GUARD_ROAMER_H
