#include "global.h"
#include "pokedex.h"
#include "pokedex_screen.h"
#include "constants/species.h"
#include "string_util.h"

const u8 *sub_8088E20(u16 dexNum)
{
    return gPokedexEntries[dexNum].categoryName;
}

u16 GetPokedexHeightWeight(u16 dexNum, u8 data)
{
    switch (data)
    {
    case 0:  // height
        return gPokedexEntries[dexNum].height;
    case 1:  // weight
        return gPokedexEntries[dexNum].weight;
    default:
        return 1;
    }
}

void GetSpeciesPokedexDescription(u8* description, u16 species)
{
    StringCopy(description, gPokedexEntries[SpeciesToNationalPokedexNum(species)].description);
}

s8 GetSetPokedexFlag(u16 species, u8 caseID)
{
    return DexScreen_GetSetPokedexFlag(species, caseID, TRUE);
}

s8 GetSetPokedexFlagNational(u16 species, u8 caseID)
{
    return DexScreen_GetSetPokedexFlag(species, caseID, FALSE);
}

u16 GetNationalPokedexCount(u8 caseID)
{
    u16 count = 0;
    u16 i;

    for (i = 0; i < NATIONAL_DEX_COUNT; i++)
    {
        switch (caseID)
        {
        case FLAG_GET_SEEN:
            if (GetSetPokedexFlagNational(i + 1, FLAG_GET_SEEN))
                count++;
            break;
        case FLAG_GET_CAUGHT:
            if (GetSetPokedexFlagNational(i + 1, FLAG_GET_CAUGHT))
                count++;
            break;
        }
    }
    return count;
}

u16 GetKantoPokedexCount(u8 caseID)
{
    u16 count = 0;
    u16 i;

    for (i = 0; i < KANTO_DEX_COUNT; i++)
    {
        switch (caseID)
        {
        case FLAG_GET_SEEN:
            if (GetSetPokedexFlagNational(i + 1, FLAG_GET_SEEN))
                count++;
            break;
        case FLAG_GET_CAUGHT:
            if (GetSetPokedexFlagNational(i + 1, FLAG_GET_CAUGHT))
                count++;
            break;
        }
    }
    return count;
}

bool16 HasAllHoennMons(void)
{
    u16 i;

    for (i = 0; i < HOENN_DEX_COUNT - 2; i++)
    {
        if (!GetSetPokedexFlagNational(HoennToNationalOrder(i + 1), FLAG_GET_CAUGHT))
            return FALSE;
    }
    return TRUE;
}

bool16 HasAllKantoMons(void)
{
    u16 i;

    for (i = 0; i < KANTO_DEX_COUNT - 1; i++)
    {
        if (!GetSetPokedexFlagNational(i + 1, FLAG_GET_CAUGHT))
            return FALSE;
    }
    return TRUE;
}

bool16 HasAllMons(void)
{
    u16 i;

    for (i = 0; i < NATIONAL_DEX_MEWTWO; i++)
    {
        if (!GetSetPokedexFlagNational(i + 1, FLAG_GET_CAUGHT))
            return FALSE;
    }
    for (i = NATIONAL_DEX_MEW; i < NATIONAL_DEX_TYRANITAR; i++)
    {
        if (!GetSetPokedexFlagNational(i + 1, FLAG_GET_CAUGHT))
            return FALSE;
    }
    for (i = NATIONAL_DEX_CELEBI; i < NATIONAL_DEX_RAYQUAZA; i++)
    {
        if (!GetSetPokedexFlagNational(i + 1, FLAG_GET_CAUGHT))
            return FALSE;
    }
    return TRUE;
}
