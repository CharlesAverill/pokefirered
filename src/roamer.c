#include "global.h"
#include "random.h"
#include "overworld.h"
#include "field_specials.h"
#include "constants/species.h"
#include "constants/maps.h"
#include "constants/region_map_sections.h"
#include "../include/roamer.h"

EWRAM_DATA u8 sLocationHistory[3][2] = {};
EWRAM_DATA u8 sRoamerLocation[2] = {};

#define saveRoamer (*(&gSaveBlock1Ptr->roamer))

#define ROAMING_MAP_BANK 3
#define NUM_MAPS_IN_SET 7

static void CreateInitialRoamerMon(u16 species, u8 level, bool8 allowedOnLand, bool8 allowedOnWater);
static bool8 IsRoamerAt(u8 mapGroup, u8 mapNum, u8 id);
static void CreateRoamerMonInstance(u8 id);

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
    int i;
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
        gSpecialVar_LastResult = 0;
        return;
    }

    CreateMon(&gEnemyParty[0], species, level, 0x20, 0, 0, 0, 0);

#ifdef CREATE_ROAMER_WITH_X_PERFECT_IVS
    {
		u8 numPerfectStats = 0;
		u8 perfect = 31;
		bool8 perfectStats[NUM_STATS] = {0};

		//Count pre-existing perfect stats
		for (int i = 0; i < NUM_STATS; ++i)
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
    roamer.personality = gEnemyParty[0].personality;
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

    if (i == MAX_NUM_ROAMERS)
        gSpecialVar_LastResult = 0; //Too many roamers
    else
        gSpecialVar_LastResult = 1; //Success
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
    for (int i = 0; i < MAX_NUM_ROAMERS; ++i)
    {
        struct Roamer* roamer = &gRoamers[i];

        if (roamer->species != SPECIES_NONE)
        {
            roamer->locationHistory[2][MAP_GRP] = roamer->locationHistory[1][MAP_GRP];
            roamer->locationHistory[2][MAP_NUM] = roamer->locationHistory[1][MAP_NUM];

            roamer->locationHistory[1][MAP_GRP] = roamer->locationHistory[0][MAP_GRP];
            roamer->locationHistory[1][MAP_NUM] = roamer->locationHistory[0][MAP_NUM];

            roamer->locationHistory[0][MAP_GRP] = gSaveBlock1->location.mapGroup;
            roamer->locationHistory[0][MAP_NUM] = gSaveBlock1->location.mapNum;
        }
    }
}

void RoamersMoveToOtherLocationSet(void)
{
    u8 mapNum = 0;

    for (int i = 0; i < MAX_NUM_ROAMERS; ++i)
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
        for (int i = 0; i < MAX_NUM_ROAMERS; ++i)
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
    mon->condition = roamer->status;
    mon->hp = roamer->hp;
}

bool8 TryStartRoamerEncounter(u8 environment)
{
    for (int i = 0; i < MAX_NUM_ROAMERS; ++i)
    {
        if (IsRoamerAt(gSaveBlock1->location.mapGroup, gSaveBlock1->location.mapNum, i) && (Random() % 4) == 0)
        {
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

            CreateRoamerMonInstance(i);
            gLastSelectedRoamer = i;
            return TRUE;
        }
    }

    return FALSE;
}

void UpdateFoughtRoamerHPStatus(struct Pokemon* mon)
{
    gRoamers[gLastSelectedRoamer].hp = mon->hp;
    gRoamers[gLastSelectedRoamer].status = mon->condition;

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
    for (int i = 0; i < MAX_NUM_ROAMERS; ++i)
    {
        if (gRoamers[i].species == species)
            return TRUE;
    }

    return FALSE;
}

void GetMapGroupAndMapNumOfRoamer(u16 species, u8* mapGroup, u8* mapNum)
{
    for (int i = 0; i < MAX_NUM_ROAMERS; ++i)
    {
        if (gRoamers[i].species == species)
        {
            *mapGroup = gRoamers[i].location[MAP_GRP];
            *mapNum = gRoamers[i].location[MAP_NUM];
        }
    }
}

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


/*static const union AffineAnimCmd sSpriteAffineAnim_RegionMapRoamer[] =
{
	AFFINEANIMCMD_FRAME(-128, -128, 0, 1), //Half size
	AFFINEANIMCMD_END,
};
static const union AffineAnimCmd* const sSpriteAffineAnimTable_RegionMapRoamer[] =
{
	sSpriteAffineAnim_RegionMapRoamer,
};*/

extern const u16 sMapSectionTopLeftCorners[][2];
extern const u16 sMapSectionDimensions[][2];
void CreateTownMapRoamerSprites(void)
{
    if (GetSelectedRegionMap() != 0)
        return; //Roaming only tracked on the main map

    for (int i = 0; i < MAX_NUM_ROAMERS; ++i)
    {
        //FlagSet(FLAG_SYS_SEVII_MAP_123); //For debugging
        if (gRoamers[i].species != SPECIES_NONE)
        {
            LoadMonIconPalettes();
            u8 mapGroup = gRoamers[i].location[MAP_GRP];
            u8 mapNum = gRoamers[i].location[MAP_NUM];
            const struct MapHeader* mapHeader = Overworld_GetMapHeaderByGroupAndId(mapGroup, mapNum);
            u8 regionMapSecId = mapHeader->regionMapSectionId - (MAPSEC_DYNAMIC + 1);

            s16 x = 8 * sMapSectionTopLeftCorners[regionMapSecId][0];
            s16 y = 8 * sMapSectionTopLeftCorners[regionMapSecId][1];

            if (sMapSectionDimensions[regionMapSecId][0] > 1)
                x += 4 * sMapSectionDimensions[regionMapSecId][0];
            if (sMapSectionDimensions[regionMapSecId][1] > 1)
                y += 4 * sMapSectionDimensions[regionMapSecId][1];

            u8 spriteId = CreateMonIcon(gRoamers[i].species, SpriteCB_PokeIcon, x + 36, y + 36 - 8, 0, gRoamers[i].personality, FALSE);
            if (spriteId < MAX_SPRITES)
            {
                struct Sprite* sprite = &gSprites[spriteId];

                sprite->oam.priority = 2;
                sprite->invisible = TRUE;
                /*sprite->oam.affineMode = ST_OAM_AFFINE_NORMAL;
                sprite->affineAnims = sSpriteAffineAnimTable_RegionMapRoamer;
                CalcCenterToCornerVec(sprite, sprite->oam.shape, sprite->oam.size, sprite->oam.affineMode);
                InitSpriteAffineAnim(sprite);*/
            }
        }
    }
}

void DestroyTownMapRoamerSprites(void)
{
    u32 i, j;

    for (i = 0; i < MAX_SPRITES; ++i)
    {
        for (j = 0; j < MAX_NUM_ROAMERS; ++j)
        {
            if (gRoamers[j].species != SPECIES_NONE
                &&  (void*) gSprites[i].images == (void*) GetMonIconTiles(gRoamers[j].species, FALSE))
            {
                FreeSpriteOamMatrix(&gSprites[i]);
                DestroyMonIconSprite(&gSprites[i]);
            }
        }
    }
}

void HideOrShowTownMapRoamerSprites(bool8 invisible)
{
    u32 i, j;

    for (i = 0; i < MAX_SPRITES; ++i)
    {
        if (gSprites[i].inUse)
        {
            for (j = 0; j < MAX_NUM_ROAMERS; ++j)
            {
                if (gRoamers[j].species != SPECIES_NONE
                    &&  (void*) gSprites[i].images == (void*) GetMonIconTiles(gRoamers[j].species, FALSE))
                {
                    gSprites[i].invisible = invisible;
                }
            }
        }
    }
}