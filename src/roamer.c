#include "global.h"
#include "random.h"
#include "overworld.h"
#include "field_specials.h"
#include "constants/species.h"
#include "constants/maps.h"
#include "constants/region_map_sections.h"
#include "../include/roamer.h"
#include "../include/pokemon_icon.h"

EWRAM_DATA u8 sLocationHistory[3][2] = {};
EWRAM_DATA u8 sRoamerLocation[2] = {};

#define saveRoamer (*(&gSaveBlock1Ptr->roamer))

#define ROAMING_MAP_BANK 3
#define NUM_MAPS_IN_SET 7

/*
static void CreateInitialRoamerMon(u16 species, u8 level, bool8 allowedOnLand, bool8 allowedOnWater);
static bool8 IsRoamerAt(u8 mapGroup, u8 mapNum, u8 id);
static void CreateRoamerMonInstance(u8 id);
*/
enum
{
    MAP_GRP = 0, // map group
    MAP_NUM = 1, // map number
};

const u8 sRoamerLocations[][NUM_MAPS_IN_SET] = {
    {MAP_NUM(ROUTE1), MAP_NUM(ROUTE2), MAP_NUM(ROUTE21_NORTH), MAP_NUM(ROUTE22), 0xff, 0xff, 0xff},
    {MAP_NUM(ROUTE2), MAP_NUM(ROUTE1), MAP_NUM(ROUTE3), MAP_NUM(ROUTE22), 0xff, 0xff, 0xff},
    {MAP_NUM(ROUTE3), MAP_NUM(ROUTE2), MAP_NUM(ROUTE4), 0xff, 0xff, 0xff, 0xff},
    {MAP_NUM(ROUTE4), MAP_NUM(ROUTE3), MAP_NUM(ROUTE5), MAP_NUM(ROUTE9), MAP_NUM(ROUTE24), 0xff, 0xff},
    {MAP_NUM(ROUTE5), MAP_NUM(ROUTE4), MAP_NUM(ROUTE6), MAP_NUM(ROUTE7), MAP_NUM(ROUTE8), MAP_NUM(ROUTE9), MAP_NUM(ROUTE24)},
    {MAP_NUM(ROUTE6), MAP_NUM(ROUTE5), MAP_NUM(ROUTE7), MAP_NUM(ROUTE8), MAP_NUM(ROUTE11), 0xff, 0xff},
    {MAP_NUM(ROUTE7), MAP_NUM(ROUTE5), MAP_NUM(ROUTE6), MAP_NUM(ROUTE8), MAP_NUM(ROUTE16), 0xff, 0xff},
    {MAP_NUM(ROUTE8), MAP_NUM(ROUTE5), MAP_NUM(ROUTE6), MAP_NUM(ROUTE7), MAP_NUM(ROUTE10), MAP_NUM(ROUTE12), 0xff},
    {MAP_NUM(ROUTE9), MAP_NUM(ROUTE4), MAP_NUM(ROUTE5), MAP_NUM(ROUTE10), MAP_NUM(ROUTE24), 0xff, 0xff},
    {MAP_NUM(ROUTE10), MAP_NUM(ROUTE8), MAP_NUM(ROUTE9), MAP_NUM(ROUTE12), 0xff, 0xff, 0xff},
    {MAP_NUM(ROUTE11), MAP_NUM(ROUTE6), MAP_NUM(ROUTE12), 0xff, 0xff, 0xff, 0xff},
    {MAP_NUM(ROUTE12), MAP_NUM(ROUTE10), MAP_NUM(ROUTE11), MAP_NUM(ROUTE13), 0xff, 0xff, 0xff},
    {MAP_NUM(ROUTE13), MAP_NUM(ROUTE12), MAP_NUM(ROUTE14), 0xff, 0xff, 0xff, 0xff},
    {MAP_NUM(ROUTE14), MAP_NUM(ROUTE13), MAP_NUM(ROUTE15), 0xff, 0xff, 0xff, 0xff},
    {MAP_NUM(ROUTE15), MAP_NUM(ROUTE14), MAP_NUM(ROUTE18), MAP_NUM(ROUTE19), 0xff, 0xff, 0xff},
    {MAP_NUM(ROUTE16), MAP_NUM(ROUTE7), MAP_NUM(ROUTE17), 0xff, 0xff, 0xff, 0xff},
    {MAP_NUM(ROUTE17), MAP_NUM(ROUTE16), MAP_NUM(ROUTE18), 0xff, 0xff, 0xff, 0xff},
    {MAP_NUM(ROUTE18), MAP_NUM(ROUTE15), MAP_NUM(ROUTE17), MAP_NUM(ROUTE19), 0xff, 0xff, 0xff},
    {MAP_NUM(ROUTE19), MAP_NUM(ROUTE15), MAP_NUM(ROUTE18), MAP_NUM(ROUTE20), 0xff, 0xff, 0xff},
    {MAP_NUM(ROUTE20), MAP_NUM(ROUTE19), MAP_NUM(ROUTE21_NORTH), 0xff, 0xff, 0xff, 0xff},
    {MAP_NUM(ROUTE21_NORTH), MAP_NUM(ROUTE1), MAP_NUM(ROUTE20), 0xff, 0xff, 0xff, 0xff},
    {MAP_NUM(ROUTE22), MAP_NUM(ROUTE1), MAP_NUM(ROUTE2), MAP_NUM(ROUTE23), 0xff, 0xff, 0xff},
    {MAP_NUM(ROUTE23), MAP_NUM(ROUTE22), MAP_NUM(ROUTE2), 0xff, 0xff, 0xff, 0xff},
    {MAP_NUM(ROUTE24), MAP_NUM(ROUTE4), MAP_NUM(ROUTE5), MAP_NUM(ROUTE9), 0xff, 0xff, 0xff},
    {MAP_NUM(ROUTE25), MAP_NUM(ROUTE24), MAP_NUM(ROUTE9), 0xff, 0xff, 0xff, 0xff},
    {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}
};

void ClearRoamerData(void)
{
    memset(gRoamers, 0, sizeof(struct Roamer) * MAX_NUM_ROAMERS);
}

#define GetRoamerSpecies() ({\
    u16 a;\
    switch (GetStarterSpecies())\
    {\
    default:\
        a = SPECIES_RAIKOU;\
        break;\
    case SPECIES_BULBASAUR:\
        a = SPECIES_ENTEI;\
        break;\
    case SPECIES_CHARMANDER:\
        a = SPECIES_SUICUNE;\
        break;\
    }\
    a;\
})

static void CreateInitialRoamerMon(u16 species, u8 level, bool8 allowedOnLand, bool8 allowedOnWater)
{
    u8 i;
    struct Roamer roamer;

    /*
    if (species == 0xFFFF) //FRLGSytle
    {
        switch(GetStarterChoice()) { //0x80CBDB0
            case SPECIES_BULBASAUR:
                species = SPECIES_ENTEI;
                break;
            case SPECIES_CHARMANDER:
                species = SPECIES_SUICUNE;
                break;
            default:
                species = SPECIES_RAIKOU;
        }
    }
    */

    if (IsSpeciesRoaming(species)) //Only one of each species may roam at a time.
    {
        return;
    }

    CreateMon(&gEnemyParty[0], species, level, 0x20, 0, 0, 0, 0);

#ifdef CREATE_ROAMER_WITH_X_PERFECT_IVS
    {
		u8 numPerfectStats = 0;
		u8 perfect = 31;
		bool8 perfectStats[NUM_STATS] = {0};

		//Count pre-existing perfect stats
		u8 i;
		for (i = 0; i < NUM_STATS; ++i)
		{
			if (GetMonData(&gEnemyParty[0], MON_DATA_HP_IV + i, NULL) >= 31)
			{
				perfectStats[i] = TRUE;
				++numPerfectStats;
			}
		}

		//Add more perfect stats up to max
		while (numPerfectStats < MathMin(CREATE_ROAMER_WITH_X_PERFECT_IVS, NUM_STATS)) //Error prevention
		{
			u8 statId = Random() % NUM_STATS;
			if (!perfectStats[statId]) //Must be unique
			{
				perfectStats[statId] = TRUE;
				++numPerfectStats;
				SetMonData(&gEnemyParty[0], MON_DATA_HP_IV + statId, &perfect);
			}
		}

		HealMon(&gEnemyParty[0]);
	}
#endif

    roamer.level = level;
    roamer.status = 0;
    roamer.ivs = GetMonData(&gEnemyParty[0], MON_DATA_IVS, NULL);
    roamer.personality = GetMonData(&gEnemyParty[0], MON_DATA_PERSONALITY);
    roamer.species = species;
    roamer.hp = gEnemyParty[0].hp;
    roamer.canAppearOnLand = allowedOnLand;
    roamer.canAppearOnWater = allowedOnWater;
    roamer.location[MAP_GRP] = ROAMING_MAP_BANK;
    roamer.location[MAP_NUM] = sRoamerLocations[Random() % (ARRAY_COUNT(sRoamerLocations) - 1)][0];

    for (i = 0; i < MAX_NUM_ROAMERS; ++i)
    {
        if (gRoamers[i].species == SPECIES_NONE) //Fill in empty spot
        {
            gRoamers[i] = roamer;
            break;
        }
    }
}

void InitRoamer(void)
{
    ClearRoamerData();
    CreateInitialRoamerMon(SPECIES_ENTEI, 50, TRUE, FALSE);
    CreateInitialRoamerMon(SPECIES_RAIKOU, 50, TRUE, FALSE);
    CreateInitialRoamerMon(SPECIES_SUICUNE, 50, TRUE, TRUE);
    CreateInitialRoamerMon(SPECIES_LATIAS, 50, TRUE, TRUE);
    CreateInitialRoamerMon(SPECIES_LATIOS, 50, TRUE, TRUE);
}

void UpdateLocationHistoryForRoamer(void)
{
    u8 i;
    for (i = 0; i < MAX_NUM_ROAMERS; ++i)
    {
        struct Roamer* roamer = &gRoamers[i];

        if (roamer->species != SPECIES_NONE)
        {
            roamer->locationHistory[2][MAP_GRP] = roamer->locationHistory[1][MAP_GRP];
            roamer->locationHistory[2][MAP_NUM] = roamer->locationHistory[1][MAP_NUM];

            roamer->locationHistory[1][MAP_GRP] = roamer->locationHistory[0][MAP_GRP];
            roamer->locationHistory[1][MAP_NUM] = roamer->locationHistory[0][MAP_NUM];

            roamer->locationHistory[0][MAP_GRP] = gSaveBlock1Ptr->location.mapGroup;
            roamer->locationHistory[0][MAP_NUM] = gSaveBlock1Ptr->location.mapNum;
        }
    }
}

void RoamersMoveToOtherLocationSet(void)
{
    u8 mapNum = 0;
    u8 i;

    for (i = 0; i < MAX_NUM_ROAMERS; ++i)
    {
        struct Roamer* roamer = &gRoamers[i];

        if (roamer->species != SPECIES_NONE)
        {
            roamer->location[MAP_GRP] = ROAMING_MAP_BANK;

            while (TRUE)
            {
                mapNum = sRoamerLocations[Random() % (ARRAY_COUNT(sRoamerLocations) - 1)][0];
                if (roamer->location[MAP_NUM] != mapNum)
                {
                    roamer->location[MAP_NUM] = mapNum;
                    break;
                }
            }
        }
    }
}

void RoamersMove(void)
{
    u8 locSet = 0;

    if ((Random() % 16) == 0)
    {
        RoamersMoveToOtherLocationSet();
    }
    else
    {
        u8 i;
        for (i = 0; i < MAX_NUM_ROAMERS; ++i)
        {
            struct Roamer* roamer = &gRoamers[i];

            if (roamer->species != SPECIES_NONE)
            {
                while (locSet < (ARRAY_COUNT(sRoamerLocations) - 1))
                {
                    if (roamer->location[MAP_NUM] == sRoamerLocations[locSet][0])
                    {
                        u8 mapNum;
                        while (TRUE)
                        {
                            mapNum = sRoamerLocations[locSet][Random() % NUM_MAPS_IN_SET];
                            if (!(roamer->locationHistory[2][MAP_GRP] == ROAMING_MAP_BANK && roamer->locationHistory[2][MAP_NUM] == mapNum) && mapNum != 0xFF)
                                break;
                        }
                        roamer->location[MAP_NUM] = mapNum;
                        break;
                    }
                    locSet++;
                }
            }
        }
    }
}

static bool8 IsRoamerAt(u8 mapGroup, u8 mapNum, u8 id)
{
    struct Roamer* roamer = &gRoamers[id];

    return roamer->species != SPECIES_NONE && mapGroup == roamer->location[MAP_GRP] && mapNum == roamer->location[MAP_NUM];
}

static void CreateRoamerMonInstance(u8 id)
{
    struct Pokemon* mon = &gEnemyParty[0];
    struct Roamer* roamer = &gRoamers[id];

    ZeroEnemyPartyMons();
    CreateMonWithIVsPersonality(mon, roamer->species, roamer->level, roamer->ivs, roamer->personality);
    SetMonData(mon, MON_DATA_STATUS, &roamer->status);
    mon->hp = roamer->hp;
}

bool8 TryStartRoamerEncounter()
{
    u8 i;
    for (i = 0; i < MAX_NUM_ROAMERS; ++i)
    {
        if (IsRoamerAt(gSaveBlock1Ptr->location.mapGroup, gSaveBlock1Ptr->location.mapNum, i) && (Random() % 4) == 0)
        {
            /*
            switch (environment) {
                case ENCOUNTER_TYPE_LAND:
                    if (!gRoamers[i].canAppearOnLand)
                        continue;
                    break;
                case ENCOUNTER_TYPE_WATER:
                    if (!gRoamers[i].canAppearOnWater)
                        continue;
                    break;
            }
             */

            CreateRoamerMonInstance(i);
            gLastSelectedRoamer = i;
            return TRUE;
        }
    }

    return FALSE;
}

void UpdateFoughtRoamerHPStatus(struct Pokemon* mon)
{
    gRoamers[gLastSelectedRoamer].hp = GetMonData(&mon, MON_DATA_HP, NULL);
    gRoamers[gLastSelectedRoamer].status = GetMonData(&mon, MON_DATA_STATUS, NULL);;

    RoamersMoveToOtherLocationSet();
}

void SetFoughtRoamerInactive(void)
{
    memset(&gRoamers[gLastSelectedRoamer], 0, sizeof(struct Roamer));
}

//HOOK
void GetRoamerLocation(u8* mapGroup, u8* mapNum, u8 id)
{
    *mapGroup = gRoamers[id].location[MAP_GRP];
    *mapNum = gRoamers[id].location[MAP_NUM];
}

bool8 IsSpeciesRoaming(u16 species)
{
    u8 i;
    for (i = 0; i < MAX_NUM_ROAMERS; ++i)
    {
        if (gRoamers[i].species == species)
            return TRUE;
    }

    return FALSE;
}

void GetMapGroupAndMapNumOfRoamer(u16 species, u8* mapGroup, u8* mapNum)
{
    u8 i;
    for (i = 0; i < MAX_NUM_ROAMERS; ++i)
    {
        if (gRoamers[i].species == species)
        {
            *mapGroup = gRoamers[i].location[MAP_GRP];
            *mapNum = gRoamers[i].location[MAP_NUM];
        }
    }
}

/*
void BattleSetup_StartRoamerBattle(void)
{
    ScriptContext2_Enable();
    FreezeEventObjects();
    StopPlayerAvatar();
    gMain.savedCallback = CB2_EndWildBattle;
    gBattleTypeFlags = BATTLE_TYPE_ROAMER;
    CreateBattleStartTask(GetWildBattleTransition(), GetMUS_ForBattle());
    IncrementGameStat(GAME_STAT_TOTAL_BATTLES);
    IncrementGameStat(GAME_STAT_WILD_BATTLES);
}
 */


/*static const union AffineAnimCmd sSpriteAffineAnim_RegionMapRoamer[] =
{
	AFFINEANIMCMD_FRAME(-128, -128, 0, 1), //Half size
	AFFINEANIMCMD_END,
};
static const union AffineAnimCmd* const sSpriteAffineAnimTable_RegionMapRoamer[] =
{
	sSpriteAffineAnim_RegionMapRoamer,
};*/
u16 GetRoamerLocationMapSectionId(u16 species)
{
    u8 i = 0;
    struct Roamer *roamer = &gRoamers[i];
    if (!IsSpeciesRoaming(species));
        return MAPSEC_NONE;
    while(roamer->species != species){
        roamer = &gRoamers[++i];
    }
    return Overworld_GetMapHeaderByGroupAndId(roamer->location[MAP_GRP], roamer->location[MAP_NUM])->regionMapSectionId;
}