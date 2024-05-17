#ifndef REGION_MAP
#define REGION_MAP

#include "global.h"
#include "bg.h"

enum {
    REGIONMAP_TYPE_NORMAL,
    REGIONMAP_TYPE_WALL,
    REGIONMAP_TYPE_FLY,
    REGIONMAP_TYPE_COUNT
};

enum {
    MAPSECTYPE_NONE,
    MAPSECTYPE_ROUTE,
    MAPSECTYPE_VISITED,
    MAPSECTYPE_NOT_VISITED,
    MAPSECTYPE_UNKNOWN, // Checked but never used
};

enum {
    LAYER_MAP,
    LAYER_DUNGEON,
    LAYER_COUNT
};

enum {
    REGIONMAP_KANTO,
    REGIONMAP_SEVII123,
    REGIONMAP_SEVII45,
    REGIONMAP_SEVII67,
    REGIONMAP_COUNT
};

#define MAP_WIDTH 22
#define MAP_HEIGHT 15

u8 *GetMapName(u8 *dest, u16 mapsec, u16 fill);
u8 *GetMapNameGeneric(u8 *dest, u16 mapsec);
u8 *GetMapNameGeneric_(u8 *dest, u16 mapsec);
void InitRegionMapWithExitCB(u8 a0, void (*a1)(void));
void CB2_OpenFlyMap(void);
void GetPlayerPositionOnRegionMapFromCurrFieldPos(u16 *mapSectionId, u16 *cursorPosX, u16 *cursorPosY, bool8 *playerIsInCave);
u16 GetPlayerCurrentMapSectionId(void);
u8 GetSelectedMapSection(u8, u8, s16, s16);
u8 GetSelectedRegionMap(void);
u8 GetDungeonMapsecType(u8);
u8 GetMapsecType(u8);
void MapPositionOverrides(u16* cursorx, u16* cursory);

#endif /* REGION_MAP */
