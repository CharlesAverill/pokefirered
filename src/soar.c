#include "global.h"
#include "constants/songs.h"
#include "constants/flags.h"
#include "constants/heal_locations.h"
#include "decompress.h"
#include "event_object_movement.h"
#include "event_data.h"
#include "field_effect.h"
#include "item_menu.h"
#include "load_save.h"
#include "main.h"
#include "menu.h"
#include "overworld.h"
#include "palette.h"
#include "region_map.h"
#include "constants/region_map_sections.h"
#include "help_system.h"
// #include "constants/rgb.h"
#include "scanline_effect.h"
#include "script.h"
#include "script_menu.h"
#include "soar.h"
#include "sound.h"
#include "sprite.h"
#include "string_util.h"
#include "task.h"
#include "text_window.h"
#include "trig.h"
#include "window.h"
#include "new_menu_helpers.h"
#include "text_window_graphics.h"
#include "wild_encounter.h"
#include "battle_main.h"
#include "overworld.h"
#include "battle_setup.h"

#define NOCASH_BREAKPOINT asm("mov r11, r11")

// VRAM memory layout
// Contains 256 8x8 tiles with 8-bit color (0x4000 bytes)
#define BG2_IMAGE_OFFSET 0
// 128x128 map with 1 byte per entry (0x4000 bytes)
#define BG2_TILEMAP_OFFSET 0xB000

// Not sure how much space this takes
#define BG0_IMAGE_OFFSET 0x4000
// 32x32 map with 2 bytes per entry (0x800 bytes)
#define BG0_TILEMAP_OFFSET 0xB800

static void CB2_LoadSoarGraphics(void);
static void DoSoarFieldEffectsCB2(void);
static void SoarVBlankCallback(void);
static void SoarHBlankCallback(void);
static void CB2_HandleInput(void);
static void PromptLandCB2(void);
static void ProcessYesNoCB2(void);
static void WarpCB2(void);
static void FadeOutVBlankCallback(void);
static void CB2_FadeOut(void);
static u8 windid;
static u8 windid2;

extern const u8 sMapFlyDestinations[][3];
extern const u16 sMapSectionTopLeftCorners[MAPSEC_COUNT][2];

static const struct WindowTemplate sPopupWindowTemplate =
{
	0, // BG number
	1, // tilemap left coordinate
	1, // tilemap top coordinate
	12, // width
	2, // height
	15, // palette number
	BG0_TILEMAP_OFFSET / 0x800, // BG screen base block
};

// For now, just use the region map graphics
static const u16 sRegionMapBkgnd_Pal[] = INCBIN_U16("graphics/soar/kanto_map_modified_big_tiles.gbapal");
static const u32 sRegionMapBkgnd_ImageLZ[] = INCBIN_U32("graphics/soar/kanto_map_modified_big_tiles.8bpp.lz");
static const u32 sRegionMapBkgnd_TilemapLZ[] = INCBIN_U32("graphics/soar/kanto_map_modified_big_tiles.bin.lz");

//
// Eon sprite data
//

#define GFX_TAG_EON 9999

//#if SAPPHIRE
static const u32 sEonRedSpriteTiles[] = INCBIN_U32("graphics/soar/charizard_red.4bpp.lz");
static const u32 sEonRedSpritePaletteData[] = INCBIN_U32("graphics/soar/charizard_red.gbapal.lz");
static const u32 sEonGreenSpriteTiles[] = INCBIN_U32("graphics/soar/charizard_green.4bpp.lz");
static const u32 sEonGreenSpritePaletteData[] = INCBIN_U32("graphics/soar/charizard_green.gbapal.lz");
//#else
/*
static const u8 sEonRedSpriteTiles[] = INCBIN_U8("graphics/soar/charizard_red.4bpp.lz");
static const u8 sEonRedSpritePaletteData[] = INCBIN_U8("graphics/soar/charizard_red.gbapal.lz");
static const u8 sEonGreenSpriteTiles[] = INCBIN_U8("graphics/soar/charizard_green.4bpp.lz");
static const u8 sEonGreenSpritePaletteData[] = INCBIN_U8("graphics/soar/charizard_green.gbapal.lz");
*/
//#endif

static const struct OamData sEonSpriteOamData =
{
	.y = 0,
	.affineMode = 3,
	.objMode = 0,
	.mosaic = 0,
	.bpp = 0,
	.shape = 1,
	.x = 0,
	.matrixNum = 0,
	.size = 3,
	.tileNum = 0,
	.priority = 0,
	.paletteNum = 0,
	.affineParam = 0,
};

static const struct SpriteTemplate sEonSpriteTemplate =
{
	.tileTag = GFX_TAG_EON,
	.paletteTag = GFX_TAG_EON,
	.oam = &sEonSpriteOamData,
	.anims = gDummySpriteAnimTable,
	.images = NULL,
	.affineAnims = NULL,
	.callback = SpriteCallbackDummy,
};

//
// Shadow sprite data
//

#define GFX_TAG_SHADOW 9998

static const u32 sShadowSpriteTiles[] = INCBIN_U32("graphics/soar/shadow.4bpp.lz");
static const struct CompressedSpriteSheet sShadowSpriteSheet = {
	.data = sShadowSpriteTiles,
	.size = 1024,
	.tag = GFX_TAG_SHADOW
};

static const struct OamData sShadowSpriteOamData =
{
	.y = 0,
	.affineMode = 0,
	.objMode = 2,
	.mosaic = 0,
	.bpp = 0,
	.shape = 1,
	.x = 0,
	.matrixNum = 0,
	.size = 3,
	.tileNum = 16,
	.priority = 0,
	.paletteNum = 0,
	.affineParam = 0,
};

static const struct SpriteTemplate sShadowSpriteTemplate =
{
	.tileTag = GFX_TAG_SHADOW,
	.paletteTag = GFX_TAG_SHADOW,
	.oam = &sShadowSpriteOamData,
	.anims = gDummySpriteAnimTable,
	.images = NULL,
	.affineAnims = NULL,
	.callback = SpriteCallbackDummy,
};

static const struct { u8 left; u8 top; u8 right; u8 bottom; } sPopupWindowRect = { 0, 0, 15, 3 };

static s32 sPlayerPosX;
static s32 sPlayerPosY;
static s32 sPlayerPosZ;
static u8 sPlayerYaw;
static u8 sPlayerPitch;
static u16 sPrevMapSection;
static u16 sSelectedMapSection;

static u8 sEonSpriteId;
static u8 sShadowSpriteId;

#define Q_8_7(iPart, fPart) (((iPart) << 8) | (fPart))
#define IPART(n) ((n) >> 8)
#define FPART(n) ((n) & 0xFFFF)

static const u8 sEonFluteUseMessage[] = _("{PLAYER} used the EON FLUTE.{PAUSE_UNTIL_PRESS}");

static u16 currentMusic;

static bool8 inBattle;
static u16 encounterCheck;
static bool8 returnFromBattle;

void CB2_InitSoarState2(void) {
	gMain.state = 2;
	returnFromBattle = TRUE;
	CB2_InitSoar();
}

void CB2_InitSoar(void)
{
	currentMusic = GetCurrentMapMusic();
	gHelpSystemEnabled = FALSE;
	enterSkyEncounterZone();
	Overworld_EnterSky();
	BattleSetup_EnterSky();
	encounterCheck = 0;

	switch (gMain.state)
	{
	case 0:
		returnFromBattle = FALSE;
		StringExpandPlaceholders(gStringVar4, sEonFluteUseMessage);

		DrawDialogueFrame(0, 0);
		AddTextPrinterParameterized(0, 1, gStringVar4, 0, 0, GetTextSpeedSetting(), NULL);
		CopyWindowToVram(0, 3);

		gMain.state++;
		break;
	case 1:
		if (RunTextPrinters_CheckPrinter0Active() != 1)
		{
			BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, 0);
			gMain.state++;
		}
		break;
	case 2:
		if (!UpdatePaletteFade())
		{
			u16 cursorX, cursorY;
			bool8 inCave;
			ClearDialogWindowAndFrame(0, 1);

			// Only update position if we aren't already in the sky
			if (!returnFromBattle) {
				sPrevMapSection = GetPlayerCurrentMapSectionId();

				switch (GetDungeonMapsecType(sPrevMapSection)) {
				case MAPSECTYPE_ROUTE:
					// If we're looking at a town, just get the raw position
					cursorX = sMapSectionTopLeftCorners[sPrevMapSection - MAPSECS_KANTO][0];
					cursorY = sMapSectionTopLeftCorners[sPrevMapSection - MAPSECS_KANTO][1];
					break;
				default:
					MapPositionOverrides(&cursorX, &cursorY);
				}

				AGBPrintf("%d %d\n", cursorX, cursorY);
				AGBPrintFlush();

				sPlayerPosX = Q_8_7((cursorX + 2 + 27) * 8 - 4, 0);
				sPlayerPosY = Q_8_7((cursorY + 3 + 30) * 8 - 4, 0);
				sPlayerPosZ = Q_8_7(8, 0);
				sPlayerYaw = 0;
				sPlayerPitch = 0;
			}

			FadeOutAndFadeInNewMapMusic(MUS_SURF, 2, 2);

			// some of these may not be necessary, but I'm just being safe
			ScanlineEffect_Stop();
			ResetTasks();
			ResetSpriteData();
			ResetPaletteFade();
			FreeAllSpritePalettes();

			SetMainCallback2(CB2_LoadSoarGraphics);
		}
		break;
	}
}

void ItemUseOnFieldCB_EonFlute(u8 taskId)
{
	ScriptContext2_Enable();
	FreezeObjectEvents();
	SetMainCallback2(CB2_InitSoar);
}

static void LoadEonGraphics(void)
{
	struct CompressedSpriteSheet sEonSpriteSheet =
	{
		sEonRedSpriteTiles, 1024, GFX_TAG_EON
	};
	struct CompressedSpritePalette sEonSpritePalette =
	{
		sEonRedSpritePaletteData, GFX_TAG_EON
	};

	if (gSaveBlock2Ptr->playerGender != MALE)
	{
		sEonSpriteSheet.data = sEonGreenSpriteTiles;
		sEonSpritePalette.data = sEonGreenSpritePaletteData;
	}

	LoadCompressedSpriteSheet(&sEonSpriteSheet);
	LoadCompressedSpritePalette(&sEonSpritePalette);
	sEonSpriteId = CreateSprite(&sEonSpriteTemplate, DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2, 0);
	gSprites[sEonSpriteId].data[0] = 0;
	gSprites[sEonSpriteId].data[1] = 0;
	gSprites[sEonSpriteId].data[2] = 0;
}

static void CB2_LoadSoarGraphics(void)
{
	unsigned int i;
	u8 *src;
	u8 *dest;

	switch (gMain.state)
	{
	case 0:
		REG_DISPCNT = 0;

		DmaClearLarge32(3, (void *)(VRAM), VRAM_SIZE, 0x1000);

		SetVBlankCallback(SoarVBlankCallback);
		SetHBlankCallback(SoarHBlankCallback);

		// Load image data
		LZ77UnCompVram(sRegionMapBkgnd_ImageLZ, (void *)(VRAM + BG2_IMAGE_OFFSET));

		// Load tilemap
		LZ77UnCompVram(sRegionMapBkgnd_TilemapLZ, gDecompressionBuffer);
		src = gDecompressionBuffer;
		dest = (void *)(VRAM + BG2_TILEMAP_OFFSET);
		// Copy each row to VRAM
		for (i = 0; i < 64; i++)
		{
			DmaCopy32(3, src, dest, 64);
			src += 64;
			dest += 128;
		}

		// load palette
		LoadPalette(sRegionMapBkgnd_Pal, 0, 64);

		// Create sprites
		LoadEonGraphics();
		gPlttBufferUnfaded[0] = RGB(8, 8, 20);

		gMain.state++;
		break;
	case 1:
		LoadUserWindowBorderGfx(0, 1, 0xD0);
		LoadPalette(GetUserFrameGraphicsInfo(gSaveBlock2Ptr->optionsWindowFrameType)->palette, 0x20, 0x20);
		windid = InitWindows(&sPopupWindowTemplate);
		TextWindow_LoadResourcesStdFrame0(0, 0x013, 0xD0);
		TextWindow_SetStdFrame0_WithPal(0, 0x00A, 0xC0);
		windid2 = CreateWindowFromRect(0, 14, 28, 4);

		gMain.state++;
		break;
	case 2:
		// Enable hblank and vblank interrupts
		REG_IME = 0;
		REG_IE |= INTR_FLAG_VBLANK | INTR_FLAG_HBLANK;
		REG_IME = 1;
		REG_DISPSTAT |= DISPSTAT_VBLANK_INTR | DISPSTAT_HBLANK_INTR;

		// Set up video regs
		REG_DISPCNT = DISPCNT_MODE_1 | DISPCNT_BG2_ON | DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP;
		REG_BG2CNT = BGCNT_PRIORITY(0)
			| BGCNT_256COLOR
			| BGCNT_CHARBASE(BG2_IMAGE_OFFSET / 0x4000)
			| BGCNT_SCREENBASE(BG2_TILEMAP_OFFSET / 0x800)
			| BGCNT_AFF1024x1024
			| BGCNT_WRAP;

		// Start palette fade
		BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, 0);
		gMain.state++;
		break;
	case 3:
		// Wait for fade to finish palette fade
		if (!gPaletteFade.active)
		{
			SetMainCallback2(CB2_HandleInput);
		}
		break;
	}
	BuildOamBuffer();
}

static void SoarVBlankCallback(void)
{
	LoadOam();
	UpdatePaletteFade();

	REG_BG2X = 0;
	REG_BG2Y = 0;
	REG_BG2PA = 0;
	REG_BG2PB = 0;
	REG_BG2PC = 0;
	REG_BG2PD = 0;

	// Turn off BG for first scanline
	REG_DISPCNT &= ~DISPCNT_BG2_ON;

	TransferPlttBuffer();
}

#define M7_D 128

static void SoarHBlankCallback(void)
{
	const unsigned int bldcntFog = BLDCNT_EFFECT_LIGHTEN | BLDCNT_TGT1_BD | BLDCNT_TGT1_BG2;
	const unsigned int bldcntShadow = BLDCNT_EFFECT_DARKEN | BLDCNT_TGT1_BG2;
	int sinYaw = gSineTable[sPlayerYaw];
	int cosYaw = gSineTable[sPlayerYaw + 64];

	int lam, lcf, lsf, lxr, lyr;
	u32 currScanline = REG_VCOUNT - 1;

	if (currScanline > 159)  // We're in vblank. Nothing to do.
		return;
	if (currScanline < 32)  // draw gradient for sky
	{
		REG_DISPCNT &= ~DISPCNT_BG2_ON;
		REG_BLDCNT = bldcntFog;
		REG_BLDY = currScanline / 2;
		return;
	}

	if (currScanline == 32)
		REG_DISPCNT |= DISPCNT_BG2_ON;

	if (currScanline <= 16 * 6)
	{
		REG_BLDCNT = bldcntFog;
		REG_BLDY = 16 - (currScanline / 6);
	}
	else
	{
		REG_BLDCNT = 0;
	}

	lam = sPlayerPosZ * ((1 << 16) / (currScanline - 32)) >> 12;  // .8*.16 /.12 = 20.12
	lcf = lam * cosYaw >> 8;                     // .12*.8 /.8 = .12
	lsf = lam * sinYaw >> 8;                     // .12*.8 /.8 = .12

	REG_BG2PA = lcf >> 4;
	REG_BG2PC = lsf >> 4;

	// Offsets
	// Note that the lxr shifts down first! 

	// horizontal offset
	lxr = 120 * (lcf >> 4);
	lyr = (M7_D*lsf) >> 4;
	REG_BG2X = sPlayerPosX - lxr + lyr;

	// vertical offset
	lxr = 120 * (lsf >> 4);
	lyr = (M7_D*lcf) >> 4;
	REG_BG2Y = sPlayerPosY - lxr - lyr;
}

#define spTiltAngle data[0]
#define spBarrelRollDir data[1]
#define spDestAngle data[2]
#define spFlipped data[3]

#define TILT_MAX 0x1000
#define TILT_MIN -0x1000
#define TILT_STEP 0x100
#define ROLL_TILT_STEP (TILT_STEP * 8)

static void UpdateEonSpriteRotation(struct Sprite *sprite)
{
	switch (sprite->spBarrelRollDir)
	{
	case 0:  // no barrel roll
		if (sprite->spTiltAngle < sprite->spDestAngle)
			sprite->spTiltAngle += TILT_STEP;
		else if (sprite->spTiltAngle > sprite->spDestAngle)
			sprite->spTiltAngle -= TILT_STEP;
		break;
	case 1:  // increase angle
		if (sprite->spTiltAngle < TILT_MIN)  // rotation is past 180 degrees
		{
			sprite->spTiltAngle += ROLL_TILT_STEP;
			if (sprite->spTiltAngle >= TILT_MIN)
				sprite->spBarrelRollDir = 0;
			break;
		}
		sprite->spTiltAngle += ROLL_TILT_STEP;
		break;
	case -1:  // decrease angle
		if (sprite->spTiltAngle > TILT_MAX)  // rotation is past 180 degrees
		{
			sprite->spTiltAngle -= ROLL_TILT_STEP;
			if (sprite->spTiltAngle <= TILT_MAX)
				sprite->spBarrelRollDir = 0;
			break;
		}
		sprite->spTiltAngle -= ROLL_TILT_STEP;
		break;
	}

	SetOamMatrixRotationScaling(sprite->oam.matrixNum, 1 << 8, 1 << 8, -sprite->spTiltAngle);
}

static void StartBarrelRoll(void)
{
	struct Sprite *sprite = &gSprites[sEonSpriteId];

	if (sprite->spBarrelRollDir == 0)
	{
		sprite->spFlipped = 0;
		if (sprite->spDestAngle >= 0)
			sprite->spBarrelRollDir = 1;
		else
			sprite->spBarrelRollDir = -1;
	}
}

#include <stdarg.h>
#include <stdio.h>
#include "config.h"
#include "gba/gba.h"

static void UpdateMapSectionPopup(void)
{
	s32 playerCursorY = IPART(sPlayerPosY) / 8 - 30 - 2;
	s32 playerCursorX = IPART(sPlayerPosX) / 8 - 27 - 1;
	u16 mapSection; 
	u8 str[50];
	u16 cursorX, cursorY; bool8 inCave;


	if (playerCursorY < 0 || playerCursorY >= MAP_HEIGHT || playerCursorX < 0 || playerCursorY >= MAP_WIDTH)
		return;
	mapSection = GetSelectedMapSection(REGIONMAP_KANTO, LAYER_MAP, playerCursorY, playerCursorX);		

	if (mapSection != sPrevMapSection)
	{
		if (mapSection == MAPSEC_NONE)
		{
			REG_DISPCNT &= ~DISPCNT_BG0_ON;
		}
		else
		{
			GetMapName(gStringVar4, mapSection, 0);
			DrawStdFrameWithCustomTileAndPalette(windid, 0, 1, 14);
			AddTextPrinterParameterized(windid, 1, gStringVar4, 0, 0, TEXT_SPEED_FF, NULL);

			CopyWindowToVram(windid, 3);
			REG_DISPCNT |= DISPCNT_BG0_ON;
		}
		sPrevMapSection = mapSection;
	}
}

void Soar_LoadTranslation(s32 x, s32 y, s32 z, u8 pitch, u8 yaw) {
	sPlayerPosX = x;
	sPlayerPosY = y;
	sPlayerPosZ = z;
	sPlayerPitch = pitch;
	sPlayerYaw = yaw;
}

static const u8 sText_LandHere[] = _("Would you like to land here?");

static void ExitSoar(bool8 encounter)
{
	if (encounter) {
		FadeOutMapMusic(10);
		BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, 0);
		gHelpSystemEnabled = TRUE;
		Overworld_RememberTranslation(sPlayerPosX, sPlayerPosY, sPlayerPosZ, sPlayerPitch, sPlayerYaw);
	} else {
		PlaySE(SE_PC_OFF);
		BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, 0);
		FadeOutAndFadeInNewMapMusic(currentMusic, 2, 2);
		gHelpSystemEnabled = TRUE;

		// We only want to exit the sky zones when we aren't battling, due to some
		// post-battle code
		exitSkyEncounterZone();
		Overworld_ExitSky();
		BattleSetup_ExitSky();
	}
	SetMainCallback2(CB2_FadeOut);
}

// movement limits
#define max_z_int 40
#define MIN_Z Q_8_7(1, 0)
#define MAX_Z Q_8_7(max_z_int, 0)
#define MIN_X Q_8_7(27*8, 0)
#define MAX_X Q_8_7((27+40)*8, 0)
#define MIN_Y Q_8_7(30*8, 0)
#define MAX_Y Q_8_7((30+34)*8, 0)

static const u8 mapsectype_none[] = "None";
static const u8 mapsectype_route[] = "Route";
static const u8 mapsectype_visited[] = "Visited";

static void CB2_HandleInput(void)
{
	int sinYaw;
	int cosYaw;
	bool8 moved;

	u16 cursorX, cursorY; bool8 inCave;

	const f32 speed = 0.75; //((f32)sPlayerPosZ / (f32)max_z_int) / 64.0;

    int mapsectype = GetMapsecType(sPrevMapSection);

	if ((gMain.newKeys & A_BUTTON) && 
		sPrevMapSection != MAPSEC_NONE && 
		mapsectype == MAPSECTYPE_VISITED)
	{
		PlaySE(SE_SELECT);
		sSelectedMapSection = sPrevMapSection;

		DrawStdFrameWithCustomTileAndPalette(windid2, 0, 1, 14);
		AddTextPrinterParameterized(windid2, 1, sText_LandHere, 0, 0, TEXT_SPEED_FF, NULL);
		CopyWindowToVram(windid2, 3);

		// DrawDialogFrameWithCustomTileAndPalette(windid2, 0, 10, 15);
		// AddTextPrinterParameterized(windid2, 1, sText_LandHere, 0, 0, TEXT_SPEED_FF, NULL);
		// CopyWindowToVram(windid2, 3);

		SetMainCallback2(PromptLandCB2);
		return;
	}

	if (gMain.newKeys & START_BUTTON)
	{
		ExitSoar(FALSE);
		return;
	}

	if (gMain.newKeys & R_BUTTON)
		StartBarrelRoll();

	gSprites[sEonSpriteId].spDestAngle = 0;

	moved = FALSE;
	if (gMain.heldKeys & DPAD_LEFT)
	{
		sPlayerYaw--;
		gSprites[sEonSpriteId].spDestAngle = TILT_MIN;
		moved = TRUE;
	}
	if (gMain.heldKeys & DPAD_RIGHT)
	{
		sPlayerYaw++;
		gSprites[sEonSpriteId].spDestAngle = TILT_MAX;
		moved = TRUE;
	}
	if (gMain.heldKeys & DPAD_UP)
	{
		sPlayerPosZ += 0x10;
		if (sPlayerPosZ > MAX_Z)
			sPlayerPosZ = MAX_Z;
		moved = TRUE;
	}
	if (gMain.heldKeys & DPAD_DOWN)
	{
		sPlayerPosZ -= 0x10;
		if (sPlayerPosZ < MIN_Z)
			sPlayerPosZ = MIN_Z;
		moved = TRUE;
	}

	encounterCheck++;

	if (encounterCheck % 100 == 0 && StandardWildEncounter(0, 0)) {
		inBattle = TRUE;
		ExitSoar(TRUE);
	}

	UpdateEonSpriteRotation(&gSprites[sEonSpriteId]);

	sinYaw = gSineTable[sPlayerYaw];
	cosYaw = gSineTable[sPlayerYaw + 64];

	sPlayerPosX += speed * sinYaw / 8;
	sPlayerPosY -= speed * cosYaw / 8;

	if (gMain.heldKeys & L_BUTTON)
	{
		sPlayerPosX += speed * sinYaw / 8;
		sPlayerPosY -= speed * cosYaw / 8;
	}

	if (sPlayerPosX < MIN_X)
		sPlayerPosX = MIN_X;
	else if (sPlayerPosX > MAX_X)
		sPlayerPosX = MAX_X;

	if (sPlayerPosY < MIN_Y)
		sPlayerPosY = MIN_Y;
	else if (sPlayerPosY > MAX_Y)
		sPlayerPosY = MAX_Y;

	UpdateMapSectionPopup();

	BuildOamBuffer();
}

static const struct WindowTemplate sYesNo_WindowTemplates =
{
	.bg = 0,
	.tilemapLeft = 21,
	.tilemapTop = 9,
	.width = 5,
	.height = 4,
	.paletteNum = 15,
	.baseBlock = 0x125
};

static void PromptLandCB2(void)
{
	if (!IsTextPrinterActive(0))
	{
		CreateYesNoMenu(&sYesNo_WindowTemplates, 1, 14, 0,  0x001, 0xF, 1);
		SetMainCallback2(ProcessYesNoCB2);
	}
	UpdateEonSpriteRotation(&gSprites[sEonSpriteId]);
	BuildOamBuffer();
}

static void ProcessYesNoCB2(void)
{
	switch (Menu_ProcessInputNoWrapClearOnChoose())
	{
	case 0:
		BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, 0);
		ClearDialogWindowAndFrame(windid2, 1);
		SetMainCallback2(WarpCB2);
		break;
	case -1:
	case 1:
		ClearDialogWindowAndFrame(windid2, 1);
		SetMainCallback2(CB2_HandleInput);
		break;
	}
	BuildOamBuffer();
}

static void WarpCB2(void)
{
	switch (sSelectedMapSection) {
	// case MAPSEC_SOUTHERN_ISLAND:
	// 	SetWarpDestinationToHealLocation(HEAL_LOCATION_SOUTHERN_ISLAND_EXTERIOR);
	// 	break;
	// case MAPSEC_BATTLE_FRONTIER:
	// 	SetWarpDestinationToHealLocation(HEAL_LOCATION_BATTLE_FRONTIER_OUTSIDE_EAST);
	// 	break;
	// case MAPSEC_LITTLEROOT_TOWN:
	// 	SetWarpDestinationToHealLocation(gSaveBlock2Ptr->playerGender == MALE ? HEAL_LOCATION_LITTLEROOT_TOWN_1 : HEAL_LOCATION_LITTLEROOT_TOWN_2);
	// 	break;
	// case MAPSEC_EVER_GRANDE_CITY:
	// 	SetWarpDestinationToHealLocation(FlagGet(FLAG_LANDMARK_POKEMON_LEAGUE) && (IPART(sPlayerPosY) / 8) == 10 ? HEAL_LOCATION_EVER_GRANDE_CITY_2 : HEAL_LOCATION_EVER_GRANDE_CITY_1);
	// 	break;
	// case MAPSEC_MT_CHIMNEY:
	// 	SetWarpDestinationToHealLocation(HEAL_LOCATION_MT_CHIMNEY);
	// 	break;
	default:
		SetWarpDestinationToHealLocation(sMapFlyDestinations[sSelectedMapSection - MAPSECS_KANTO][2]);

	}

	exitSkyEncounterZone();
	Overworld_ExitSky();
	BattleSetup_ExitSky();

	if (!gPaletteFade.active)
	{
		Fldeff_FlyLand();
	}
}

static void CB2_FadeOut(void)
{
	if (!gPaletteFade.active)
	{
		REG_IME = 0;
		REG_IE &= ~(INTR_FLAG_HBLANK);
		REG_IME = 1;
		REG_DISPSTAT &= ~(DISPSTAT_HBLANK_INTR);

		SetHBlankCallback(NULL);
		if (inBattle) {
			PlayMapChosenOrBattleBGM(0);
			SetMainCallback2(CB2_InitBattle);
		}
		else 
			SetMainCallback2(CB2_ReturnToFieldWithOpenMenu);
	}
}
