#include "global.h"
#include "gflib.h"
#include "berry.h"
#include "daycare.h"
#include "event_data.h"
#include "load_save.h"
#include "overworld.h"
#include "party_menu.h"
#include "pokedex.h"
#include "script_pokemon_util.h"
#include "constants/items.h"
#include "constants/species.h"
#include "constants/pokemon.h"
#include "pokemon_storage_system.h"
#include "field_specials.h"
#include "money.h"
#include "roamer.h"
#include "region_map.h"

static void CB2_ReturnFromChooseHalfParty(void);
static void CB2_ReturnFromChooseBattleTowerParty(void);

void HealPlayerParty(void)
{
    u8 i, j;
    u8 ppBonuses;
    u8 arg[4];

    // restore HP.
    for(i = 0; i < gPlayerPartyCount; i++)
    {
        u16 maxHP = GetMonData(&gPlayerParty[i], MON_DATA_MAX_HP);
        arg[0] = maxHP;
        arg[1] = maxHP >> 8;
        SetMonData(&gPlayerParty[i], MON_DATA_HP, arg);
        ppBonuses = GetMonData(&gPlayerParty[i], MON_DATA_PP_BONUSES);

        // restore PP.
        for(j = 0; j < MAX_MON_MOVES; j++)
        {
            arg[0] = CalculatePPWithBonus(GetMonData(&gPlayerParty[i], MON_DATA_MOVE1 + j), ppBonuses, j);
            SetMonData(&gPlayerParty[i], MON_DATA_PP1 + j, arg);
        }

        // since status is u32, the four 0 assignments here are probably for safety to prevent undefined data from reaching SetMonData.
        arg[0] = 0;
        arg[1] = 0;
        arg[2] = 0;
        arg[3] = 0;
        SetMonData(&gPlayerParty[i], MON_DATA_STATUS, arg);
    }
}

u8 ScriptGiveMon(u16 species, u8 level, u16 item, u32 unused1, u32 unused2, u8 unused3)
{
    u16 nationalDexNum;
    int sentToPc;
    u8 heldItem[2];
    struct Pokemon *mon = AllocZeroed(sizeof(struct Pokemon));

    CreateMon(mon, species, level, 32, 0, 0, OT_ID_PLAYER_ID, 0);
    heldItem[0] = item;
    heldItem[1] = item >> 8;
    SetMonData(mon, MON_DATA_HELD_ITEM, heldItem);
    sentToPc = GiveMonToPlayer(mon);
    nationalDexNum = SpeciesToNationalPokedexNum(species);

    switch(sentToPc)
    {
    case MON_GIVEN_TO_PARTY:
    case MON_GIVEN_TO_PC:
        GetSetPokedexFlag(nationalDexNum, FLAG_SET_SEEN);
        GetSetPokedexFlag(nationalDexNum, FLAG_SET_CAUGHT);
        break;
    }

    Free(mon);
    return sentToPc;
}

void ScriptBufferRoamerData(void){
    u16 species = GetRoamerSpecies();
    u16 roamerLocation = GetRoamerLocationMapSectionId();
    GetSpeciesName(gStringVar1, species);
    GetMapNameGeneric(gStringVar2, roamerLocation);
}

void ScriptTakeMonFromPlayer(u16 index){
    ZeroMonData(&gPlayerParty[index]);
    CompactPartySlots();
    CalculatePlayerPartyCount();
}

static const u16 sLegendaryValuable[] = {
    SPECIES_ARTICUNO,
    SPECIES_ZAPDOS,
    SPECIES_MOLTRES,
    SPECIES_MEWTWO,
    SPECIES_MEW,
    SPECIES_ENTEI,
    SPECIES_RAIKOU,
    SPECIES_SUICUNE,
    SPECIES_HO_OH,
    SPECIES_LUGIA,
    SPECIES_CELEBI,
    SPECIES_LATIOS,
    SPECIES_LATIAS,
    SPECIES_REGIROCK,
    SPECIES_REGICE,
    SPECIES_REGISTEEL,
    SPECIES_KYOGRE,
    SPECIES_GROUDON,
    SPECIES_RAYQUAZA,
    SPECIES_JIRACHI
};

static const u16 sThirdEvolutionValuable[] = {
    SPECIES_VENUSAUR,
    SPECIES_CHARIZARD,
    SPECIES_BLASTOISE,
    SPECIES_BUTTERFREE,
    SPECIES_BEEDRILL,
    SPECIES_PIDGEOT,
    SPECIES_RAICHU,
    SPECIES_NIDOQUEEN,
    SPECIES_NIDOKING,
    SPECIES_CLEFABLE,
    SPECIES_WIGGLYTUFF,
    SPECIES_CROBAT,
    SPECIES_VILEPLUME,
    SPECIES_BELLOSSOM,
    SPECIES_POLIWRATH,
    SPECIES_POLITOED,
    SPECIES_ALAKAZAM,
    SPECIES_VICTREEBEL,
    SPECIES_MACHAMP,
    SPECIES_GOLEM,
    SPECIES_GENGAR,
    SPECIES_BLISSEY,
    SPECIES_KINGDRA,
    SPECIES_MEGANIUM,
    SPECIES_TYPHLOSION,
    SPECIES_FERALIGATR,
    SPECIES_AMPHAROS,
    SPECIES_AZUMARILL,
    SPECIES_JUMPLUFF,
    SPECIES_SCEPTILE,
    SPECIES_BLAZIKEN,
    SPECIES_SWAMPERT,
    SPECIES_BEAUTIFLY,
    SPECIES_DUSTOX,
    SPECIES_LUDICOLO,
    SPECIES_SHIFTRY,
    SPECIES_GARDEVOIR,
    SPECIES_SLAKING,
    SPECIES_EXPLOUD,
    SPECIES_AGGRON,
    SPECIES_FLYGON,
    SPECIES_WALREIN
};

static const u16 sPseudoLegendaryValuable[] = {
    SPECIES_DRAGONITE,
    SPECIES_TYRANITAR,
    SPECIES_SALAMENCE,
    SPECIES_METAGROSS
};

static const u16 sRareValuable[] = {
    SPECIES_BULBASAUR,
    SPECIES_CHARMANDER,
    SPECIES_SQUIRTLE,
    SPECIES_CHIKORITA,
    SPECIES_CYNDAQUIL,
    SPECIES_TOTODILE,
    SPECIES_MUDKIP,
    SPECIES_TORCHIC,
    SPECIES_TREECKO,
    SPECIES_CHANSEY,
    SPECIES_ELECTABUZZ,
    SPECIES_MAGMAR,
    SPECIES_PIKACHU,
    SPECIES_DUGTRIO,
    SPECIES_HYPNO,
    SPECIES_EXEGGUTOR,
    SPECIES_HITMONLEE,
    SPECIES_HITMONCHAN,
    SPECIES_HITMONTOP,
    SPECIES_SCYTHER,
    SPECIES_PINSIR,
    SPECIES_HERACROSS,
    SPECIES_MR_MIME,
    SPECIES_JYNX,
    SPECIES_TAUROS,
    SPECIES_LAPRAS,
    SPECIES_DITTO,
    SPECIES_EEVEE,
    SPECIES_PORYGON,
    SPECIES_SNORLAX,
    SPECIES_SUDOWOODO,
    SPECIES_SHUCKLE,
    SPECIES_BRELOOM,
    SPECIES_SHEDINJA,
    SPECIES_NINJASK,
    SPECIES_PLUSLE,
    SPECIES_MINUN,
    SPECIES_WAILORD,
    SPECIES_SPINDA,
    SPECIES_ALTARIA,
    SPECIES_MILOTIC,
    SPECIES_CASTFORM,
    SPECIES_KECLEON,
    SPECIES_GLALIE
};

static const u16 sNotValuable[] = {
    SPECIES_CATERPIE,
    SPECIES_METAPOD,
    SPECIES_WEEDLE,
    SPECIES_KAKUNA,
    SPECIES_PIDGEY,
    SPECIES_RATTATA,
    SPECIES_SPEAROW,
    SPECIES_EKANS,
    SPECIES_SANDSHREW,
    SPECIES_NIDORAN_M,
    SPECIES_NIDORAN_F,
    SPECIES_VULPIX,
    SPECIES_GROWLITHE,
    SPECIES_ZUBAT,
    SPECIES_GOLBAT,
    SPECIES_ODDISH,
    SPECIES_PARAS,
    SPECIES_VENONAT,
    SPECIES_DIGLETT,
    SPECIES_PSYDUCK,
    SPECIES_POLIWAG,
    SPECIES_MACHOP,
    SPECIES_BELLSPROUT,
    SPECIES_GEODUDE,
    SPECIES_TENTACOOL,
    SPECIES_PONYTA,
    SPECIES_SLOWPOKE,
    SPECIES_GASTLY,
    SPECIES_DROWZEE,
    SPECIES_KRABBY,
    SPECIES_EXEGGCUTE,
    SPECIES_KOFFING,
    SPECIES_TANGELA,
    SPECIES_HORSEA,
    SPECIES_GOLDEEN,
    SPECIES_MAGIKARP,
    SPECIES_SENTRET,
    SPECIES_HOOTHOOT,
    SPECIES_SPINARAK,
    SPECIES_HOPPIP,
    SPECIES_SUNKERN,
    SPECIES_YANMA,
    SPECIES_WOOPER,
    SPECIES_PINECO,
    SPECIES_DUNSPARCE,
    SPECIES_TEDDIURSA,
    SPECIES_SLUGMA,
    SPECIES_SWINUB,
    SPECIES_REMORAID,
    SPECIES_HOUNDOUR,
    SPECIES_SMEARGLE,
    SPECIES_POOCHYENA,
    SPECIES_ZIGZAGOON,
    SPECIES_WURMPLE,
    SPECIES_SILCOON,
    SPECIES_CASCOON,
    SPECIES_LOTAD,
    SPECIES_SEEDOT,
    SPECIES_TAILLOW,
    SPECIES_WINGULL,
    SPECIES_SURSKIT,
    SPECIES_ROSELIA,
    SPECIES_NUMEL,
    SPECIES_FEEBAS,
    SPECIES_CHIMECHO,
    SPECIES_SPHEAL
};

int ScriptGetMonValue(u16 index){
    u32 value = 0;
    u8 ballValue = 0;
    u16 evSum = 0;
    u8 ivSum = 0;
    u8 foundRarity = 1;
    u32 species;
    u8 i;

    struct Pokemon *mon = &gPlayerParty[index];

    species = GetMonData(mon, MON_DATA_SPECIES);

    switch(GetMonData(mon, MON_DATA_POKEBALL)){
        case ITEM_MASTER_BALL:
            ballValue = 100;
            break;
        case ITEM_POKE_BALL:
            ballValue = 20;
            break;
        case ITEM_GREAT_BALL:
            ballValue = 40;
            break;
        case ITEM_ULTRA_BALL:
            ballValue = 60;
            break;
        case ITEM_NET_BALL:
            ballValue = 50;
            break;
        case ITEM_DIVE_BALL:
            ballValue = 50;
            break;
        case ITEM_NEST_BALL:
            ballValue = 50;
            break;
        case ITEM_REPEAT_BALL:
            ballValue = 55;
            break;
        case ITEM_TIMER_BALL:
            ballValue = 55;
            break;
        case ITEM_LUXURY_BALL:
            ballValue = 70;
            break;
        case ITEM_PREMIER_BALL:
            ballValue = 85;
            break;
        default:
            ballValue = 20;
            break;
    }

    for(i = 0; i < 6; i++){
        evSum += GetMonData(mon, MON_DATA_HP_EV + i);
        ivSum += GetMonData(mon, MON_DATA_HP_IV + i);
    }

    for (i = 0; i < (sizeof(sLegendaryValuable) / sizeof((sLegendaryValuable)[0])); i++)
    {
        if (species == sLegendaryValuable[i])
        {
            foundRarity = 5;
            break;
        }
    }

    for (i = 0; i < (sizeof(sThirdEvolutionValuable) / sizeof((sThirdEvolutionValuable)[0])); i++)
    {
        if (species == sThirdEvolutionValuable[i])
        {
            foundRarity = 3;
            break;
        }
    }

    for (i = 0; i < (sizeof(sPseudoLegendaryValuable) / sizeof((sPseudoLegendaryValuable)[0])); i++)
    {
        if (species == sPseudoLegendaryValuable[i])
        {
            foundRarity = 4;
            break;
        }
    }

    for (i = 0; i < (sizeof(sRareValuable) / sizeof((sRareValuable)[0])); i++)
    {
        if (species == sRareValuable[i])
        {
            foundRarity = 2;
            break;
        }
    }

    for (i = 0; i < (sizeof(sNotValuable) / sizeof((sNotValuable)[0])); i++)
    {
        if (species == sNotValuable[i])
        {
            foundRarity = -1;
            break;
        }
    }

    // Value formula = (.3)(level) + (.05)(rarity of pokeball) + (.35)(species rarity) + (.15)(sum of EVs / 510) + (.15)(sum of IVs / (6 * 31))
    // Max selling value is $100,000, so divide value by 100 to get decimal and multiply by 100,000 (idc that it's not concise)

    value += 30.0 * GetMonData(mon, MON_DATA_LEVEL) / 100.0;

    value += 5.0 * ballValue / (100.0);

    value += 35.0 * ((foundRarity * 20.0)) / 100.0;

    value += 15.0 * (evSum / 510.0) / 10.0;
    value += 15.0 * (ivSum / 186.0) / 100.0;

    value *= 100000.0;
    value /= 100.0;

    if(value < 0 || value > 100000){
        value = 1000;
    }

    value = (int)value;

    ConvertIntToDecimalStringN(gStringVar2, value, STR_CONV_MODE_LEFT_ALIGN, CountDigits(value));

    return value;
}

void ScriptGetMonValueAndSell(u16 index){
    int value = ScriptGetMonValue(index);

    AddMoney(&gSaveBlock1Ptr->money, value);
}

u8 ScriptGiveMonWithStats(u16 species, u8 level, u16 item, bool8 isShiny, bool8 isEgg, u8 *stats, u8 *EVs, u8 *IVs)
{
    u16 nationalDexNum;
    int sentToPc;
    u8 heldItem[2];
    s32 j;
    struct Pokemon *mon = AllocZeroed(sizeof(struct Pokemon));

    if(isShiny){
        CreateShinyMon(mon, species, level);
    }
    else{
        CreateMon(mon, species, level, 32, 0, 0, OT_ID_PLAYER_ID, 0);
    }

    SetMonData(mon, MON_DATA_IS_EGG, &isEgg);
    if(isEgg){
        SetMonData(mon, MON_DATA_FRIENDSHIP, &gBaseStats[species].eggCycles);
    }

    // Set IVs, EVs, and stats
    SetMonData(mon, MON_DATA_HP, &stats[0]);
    for (j = 0; j < 6; j++) {
        if (IVs[j] > 0) {
            SetMonData(mon, MON_DATA_HP_IV + j, &IVs[j]);
        }
        if (IVs[j] > 0) {
            SetMonData(mon, MON_DATA_HP_EV + j, &EVs[j]);
        }
        if (IVs[j] > 0) {
            SetMonData(mon, MON_DATA_MAX_HP + j, &stats[j]);
        }
    }

    heldItem[0] = item;
    heldItem[1] = item >> 8;
    SetMonData(mon, MON_DATA_HELD_ITEM, heldItem);
    sentToPc = GiveMonToPlayer(mon);
    nationalDexNum = SpeciesToNationalPokedexNum(species);

    switch(sentToPc)
    {
        case MON_GIVEN_TO_PARTY:
        case MON_GIVEN_TO_PC:
            GetSetPokedexFlag(nationalDexNum, FLAG_SET_SEEN);
            GetSetPokedexFlag(nationalDexNum, FLAG_SET_CAUGHT);
            break;
    }

    Free(mon);
    return sentToPc;
}

u8 ScriptGiveEgg(u16 species)
{
    struct Pokemon *mon = AllocZeroed(sizeof(struct Pokemon));
    bool8 isEgg;
    bool8 sentToPc;

    CreateEgg(mon, species, TRUE);
    isEgg = TRUE;
    SetMonData(mon, MON_DATA_IS_EGG, &isEgg);

    sentToPc = GiveMonToPlayer(mon);
    Free(mon);
    return sentToPc;
}

void HasEnoughMonsForDoubleBattle(void)
{
    switch (GetMonsStateToDoubles())
    {
    case PLAYER_HAS_TWO_USABLE_MONS:
        gSpecialVar_Result = PLAYER_HAS_TWO_USABLE_MONS;
        break;
    case PLAYER_HAS_ONE_MON:
        gSpecialVar_Result = PLAYER_HAS_ONE_MON;
        break;
    case PLAYER_HAS_ONE_USABLE_MON:
        gSpecialVar_Result = PLAYER_HAS_ONE_USABLE_MON;
        break;
    }
}

static bool8 CheckPartyMonHasHeldItem(u16 item)
{
    int i;

    for(i = 0; i < PARTY_SIZE; i++)
    {
        u16 species = GetMonData(&gPlayerParty[i], MON_DATA_SPECIES2);
        if (species != SPECIES_NONE && species != SPECIES_EGG && GetMonData(&gPlayerParty[i], MON_DATA_HELD_ITEM) == item)
            return TRUE;
    }
    return FALSE;
}

bool8 DoesPartyHaveEnigmaBerry(void)
{
    bool8 hasItem = CheckPartyMonHasHeldItem(ITEM_ENIGMA_BERRY);
    if (hasItem == TRUE)
        GetBerryNameByBerryType(ItemIdToBerryType(ITEM_ENIGMA_BERRY), gStringVar1);

    return hasItem;
}

void CreateScriptedWildMon(u16 species, u8 level, u16 item)
{
    u8 heldItem[2];

    ZeroEnemyPartyMons();
    CreateMon(&gEnemyParty[0], species, level, 32, 0, 0, OT_ID_PLAYER_ID, 0);
    if (item)
    {
        heldItem[0] = item;
        heldItem[1] = item >> 8;
        SetMonData(&gEnemyParty[0], MON_DATA_HELD_ITEM, heldItem);
    }
}

void ScriptSetMonMoveSlot(u8 monIndex, u16 move, u8 slot)
{
    if (monIndex > PARTY_SIZE)
        monIndex = gPlayerPartyCount - 1;

    SetMonMoveSlot(&gPlayerParty[monIndex], move, slot);
}

// Note: When control returns to the event script, gSpecialVar_Result will be
// TRUE if the party selection was successful.
void ChooseHalfPartyForBattle(void)
{
    gMain.savedCallback = CB2_ReturnFromChooseHalfParty;
//    VarSet(VAR_FRONTIER_FACILITY, FACILITY_MULTI_OR_EREADER);
    InitChooseHalfPartyForBattle(0);
}

static void CB2_ReturnFromChooseHalfParty(void)
{
    switch (gSelectedOrderFromParty[0])
    {
    case 0:
        gSpecialVar_Result = FALSE;
        break;
    default:
        gSpecialVar_Result = TRUE;
        break;
    }

    SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
}

void ChooseBattleTowerPlayerParty(void)
{
    gMain.savedCallback = CB2_ReturnFromChooseBattleTowerParty;
    InitChooseHalfPartyForBattle(1);
}

static void CB2_ReturnFromChooseBattleTowerParty(void)
{
    switch (gSelectedOrderFromParty[0])
    {
    case 0:
        LoadPlayerParty();
        gSpecialVar_Result = FALSE;
        break;
    default:
        ReducePlayerPartyToThree();
        gSpecialVar_Result = TRUE;
        break;
    }

    SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
}

void ReducePlayerPartyToThree(void)
{
    struct Pokemon * party = AllocZeroed(3 * sizeof(struct Pokemon));
    int i;

    // copy the selected pokemon according to the order.
    for (i = 0; i < 3; i++)
        if (gSelectedOrderFromParty[i]) // as long as the order keeps going (did the player select 1 mon? 2? 3?), do not stop
            party[i] = gPlayerParty[gSelectedOrderFromParty[i] - 1]; // index is 0 based, not literal

    CpuFill32(0, gPlayerParty, sizeof gPlayerParty);

    // overwrite the first 3 with the order copied to.
    for (i = 0; i < 3; i++)
        gPlayerParty[i] = party[i];

    CalculatePlayerPartyCount();
    Free(party);
}
