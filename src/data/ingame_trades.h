static const struct InGameTrade sInGameTrades[] = {
    [INGAME_TRADE_MR_MIME] = 
    {
        .nickname = _("Sam"),
        .species = SPECIES_MR_MIME,
        .ivs = {20, 15, 17, 24, 23, 22},
        .abilityNum = 0,
        .otId = 40104,
        .conditions = {5, 5, 5, 30, 5},
        .personality = 0x00009cae,
        .heldItem = ITEM_NONE,
        .mailNum = 255,
        .otName = _("Reyley"),
        .otGender = MALE,
        .sheen = 10,
        .requestedSpecies = SPECIES_ALAKAZAM
    }, 
    [INGAME_TRADE_JYNX] = 
    {
        .nickname = _("Dorian"),
        .species = SPECIES_JYNX,
        .ivs = {18, 17, 18, 22, 25, 21},
        .abilityNum = 0,
        .otId = 11800,
        .conditions = {5, 30, 5, 5, 5},
        .personality = 0x00002e1d,
        .heldItem = ITEM_FAB_MAIL,
        .mailNum = 0,
        .otName = _("Dontae"),
        .otGender = MALE,
        .sheen = 10,
        .requestedSpecies = SPECIES_POLITOED
    }, 
    [INGAME_TRADE_NIDORAN] = 
    {
#if defined(FIRERED)
        .nickname = _("Susannah"),
        .species = SPECIES_NIDORAN_F,
        .ivs = {22, 18, 25, 19, 15, 22},
        .abilityNum = 0,
        .otId = 16264,
        .conditions = {5, 5, 5, 5, 30},
        .personality = 0x4c970b9e,
        .heldItem = ITEM_TINY_MUSHROOM,
        .mailNum = 255,
        .otName = _("Saige"),
        .otGender = FEMALE,
        .sheen = 10,
        .requestedSpecies = SPECIES_NIDOKING
#elif defined(LEAFGREEN)
        .nickname = _("Mr. nido"),
        .species = SPECIES_NIDORAN_M,
        .ivs = {19, 25, 18, 22, 22, 15},
        .abilityNum = 0,
        .otId = 63184,
        .conditions = {30, 5, 5, 5, 5},
        .personality = 0x4c970b9e,
        .heldItem = ITEM_TINY_MUSHROOM,
        .mailNum = 255,
        .otName = _("Saige"),
        .otGender = FEMALE,
        .sheen = 10,
        .requestedSpecies = SPECIES_NIDORAN_F
#endif
    }, 
    [INGAME_TRADE_FARFETCHD] = 
    {
        .nickname = _("Grey"),
        .species = SPECIES_FARFETCHD,
        .ivs = {20, 25, 21, 24, 15, 20},
        .abilityNum = 0,
        .otId = 1655552,
        .conditions = {30, 5, 5, 5, 5},
        .personality = 0x00194300,
        .heldItem = ITEM_STICK,
        .mailNum = 255,
        .otName = _("Elyssa"),
        .otGender = MALE,
        .sheen = 10,
        .requestedSpecies = SPECIES_SKARMORY
    }, 
    [INGAME_TRADE_NIDORINOA] = 
    {
#if defined(FIRERED)
        .nickname = _("Elliot"),
        .species = SPECIES_NIDORAN_M,
        .ivs = {22, 25, 18, 19, 22, 15},
        .abilityNum = 0,
        .otId = 969232,
        .conditions = {5, 5, 30, 5, 5},
        .personality = 0x00eeca15,
        .heldItem = ITEM_NONE,
        .mailNum = 255,
        .otName = _("Turner"),
        .otGender = MALE,
        .sheen = 10,
        .requestedSpecies = SPECIES_NIDOQUEEN
#elif defined(LEAFGREEN)
        .nickname = _("Nino"),
        .species = SPECIES_NIDORINO,
        .ivs = {19, 18, 25, 22, 15, 22},
        .abilityNum = 0,
        .otId = 13637,
        .conditions = {5, 5, 5, 5, 30},
        .personality = 0x00eeca19,
        .heldItem = ITEM_NONE,
        .mailNum = 255,
        .otName = _("Turner"),
        .otGender = MALE,
        .sheen = 10,
        .requestedSpecies = SPECIES_NIDORINA
#endif
    }, 
    [INGAME_TRADE_LICKITUNG] = 
    {
        .nickname = _("Marcus"),
        .species = SPECIES_LICKITUNG,
        .ivs = {24, 19, 21, 15, 23, 21},
        .abilityNum = 0,
        .otId = 198824,
        .conditions = {5, 5, 5, 5, 30},
        .personality = 0x000308ab,
        .heldItem = ITEM_NONE,
        .mailNum = 255,
        .otName = _("Haden"),
        .otGender = MALE,
        .sheen = 10,
#if defined(FIRERED)
        .requestedSpecies = SPECIES_LUDICOLO
#elif defined(LEAFGREEN)
        .requestedSpecies = SPECIES_SLOWBRO
#endif
    }, 
    [INGAME_TRADE_ELECTRODE] = 
    {
        .nickname = _("Reese"),
        .species = SPECIES_VOLTORB,
        .ivs = {19, 16, 18, 25, 25, 19},
        .abilityNum = 1,
        .otId = 104075280,
        .conditions = {30, 5, 5, 5, 5},
        .personality = 0x06341016,
        .heldItem = ITEM_NONE,
        .mailNum = 255,
        .otName = _("Clifton"),
        .otGender = MALE,
        .sheen = 10,
        .requestedSpecies = SPECIES_MANECTRIC
    }, 
    [INGAME_TRADE_TANGELA] = 
    {
        .nickname = _("Garrett"),
        .species = SPECIES_TANGELA,
        .ivs = {22, 17, 25, 16, 23, 20},
        .abilityNum = 0,
        .otId = 209186032,
        .conditions = {5, 5, 30, 5, 5},
        .personality = 0x5c77ecfa,
        .heldItem = ITEM_STARDUST,
        .mailNum = 255,
        .otName = _("Norma"),
        .otGender = FEMALE,
        .sheen = 10,
        .requestedSpecies = SPECIES_ARIADOS
    },
    [INGAME_TRADE_SEEL] = 
    {
        .nickname = _("Nicholas"),
        .species = SPECIES_SEEL,
        .ivs = {24, 15, 22, 16, 23, 22},
        .abilityNum = 0,
        .otId = 404794504,
        .conditions = {5, 5, 5, 5, 30},
        .personality = 0x482cac89,
        .heldItem = ITEM_NONE,
        .mailNum = 255,
        .otName = _("Garett"),
        .otGender = MALE,
        .sheen = 10,
        .requestedSpecies = SPECIES_TORKOAL
    }
};

static const u16 sInGameTradeMailMessages[][10] = {
    {
        EC_WORD_THAT_S,
        EC_WORD_A,
        EC_WORD_HEALTHY,
        EC_POKEMON(JYNX),
        EC_WORD_EXCL,
        EC_WORD_BE,
        EC_WORD_KIND,
        EC_WORD_TO,
        EC_WORD_IT
    }
};
