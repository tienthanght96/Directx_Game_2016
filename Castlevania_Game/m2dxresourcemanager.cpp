#include "m2dxresourcemanager.h"
#include "Quadtree.h"
#include "SimonBelmont.h"
#include "ScoreManager.h"

M2DXResourceManager* M2DXResourceManager::instance = nullptr;

M2DXResourceManager* M2DXResourceManager::getInstance()
{
	if (!instance)
	{
		instance = new M2DXResourceManager();
	}

	return instance;
}

M2DXResourceManager::M2DXResourceManager() { }

M2DXResourceManager::~M2DXResourceManager()
{
	release();
}

void M2DXResourceManager::release()
{
	for (auto& texturePair : textureMap)
	{
		M2_SAFE_DELETE(texturePair.second);
	}

	for (auto& soundPair : soundMap)
	{
		M2_SAFE_DELETE(soundPair.second);
	}
}

bool M2DXResourceManager::init()
{
	M2DXResourceManager::getInstance()->addTextureWithFile(SIMON_BELMONT_SPRITE_SHEET_PATH);
	M2DXResourceManager::getInstance()->addTextureWithFile(WHIP_SPRITE_SHEET_PATH);
	M2DXResourceManager::getInstance()->addTextureWithFile(CANDLE_SPRITE);
	M2DXResourceManager::getInstance()->addTextureWithFile(SMALL_HEART_SPRITE);
	M2DXResourceManager::getInstance()->addTextureWithFile(LARGE_HEART_SPRITE);
	M2DXResourceManager::getInstance()->addTextureWithFile(DOOR_SPRITE);
	M2DXResourceManager::getInstance()->addTextureWithFile(ZOMBIE_SPRITE);
	M2DXResourceManager::getInstance()->addTextureWithFile(MONEY_BAG_100_SPRITE);
	M2DXResourceManager::getInstance()->addTextureWithFile(MONEY_BAG_400_SPRITE);
	M2DXResourceManager::getInstance()->addTextureWithFile(MONEY_BAG_700_SPRITE);
	M2DXResourceManager::getInstance()->addTextureWithFile(MONEY_BAG_1000_SPRITE);
	M2DXResourceManager::getInstance()->addTextureWithFile(BLACK_KNIGHT_SPRITE);
	M2DXResourceManager::getInstance()->addTextureWithFile(AXE_MAN_SPRITE);
	M2DXResourceManager::getInstance()->addTextureWithFile(MEDUSA_SPRITE);
	M2DXResourceManager::getInstance()->addTextureWithFile(GHOST_SPRITE);
	M2DXResourceManager::getInstance()->addTextureWithFile(VAMPIRE_BAT_SPRITE);
	M2DXResourceManager::getInstance()->addTextureWithFile(DRAGON_SKULL_SPRITE);
	M2DXResourceManager::getInstance()->addTextureWithFile(FIRE_BALL_SPRITE);
	M2DXResourceManager::getInstance()->addTextureWithFile(QUEEN_MEDUSA_SPRITE);
	M2DXResourceManager::getInstance()->addTextureWithFile(SNAKE_SPRITE);
	M2DXResourceManager::getInstance()->addTextureWithFile(FLAME_HIT_SPRITE);
	M2DXResourceManager::getInstance()->addTextureWithFile(PLATFORM_SPRITE);
	M2DXResourceManager::getInstance()->addTextureWithFile(AXE_SPRITE);
	M2DXResourceManager::getInstance()->addTextureWithFile(BOMERANG_SPRITE);
	M2DXResourceManager::getInstance()->addTextureWithFile(HUNCHBACK_SPRITE);
	M2DXResourceManager::getInstance()->addTextureWithFile(WHITE_BONE_SPRITE);
	M2DXResourceManager::getInstance()->addTextureWithFile(WHITE_SKELETON_SPRITE);
	M2DXResourceManager::getInstance()->addTextureWithFile(RAVEN_SPRITE);
	M2DXResourceManager::getInstance()->addTextureWithFile(MUMMY_MAN_SPRITE);
	M2DXResourceManager::getInstance()->addTextureWithFile(BANDAGE_SPRITE);
	M2DXResourceManager::getInstance()->addTextureWithFile("tile\\1.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("tile\\2.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("Font\\A.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("Font\\B.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("Font\\C.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("Font\\D.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("Font\\E.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("Font\\F.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("Font\\G.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("Font\\H.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("Font\\I.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("Font\\J.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("Font\\K.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("Font\\L.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("Font\\M.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("Font\\N.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("Font\\O.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("Font\\P.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("Font\\Q.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("Font\\R.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("Font\\S.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("Font\\T.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("Font\\U.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("Font\\V.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("Font\\W.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("Font\\X.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("Font\\Y.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("Font\\Z.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("Font\\Heart.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("Font\\Rect.png");
	M2DXResourceManager::getInstance()->addTextureWithFile(NUMBER_SPRITE);
	M2DXResourceManager::getInstance()->addTextureWithFile(BLOOD_SIMON_SPRITE);
	M2DXResourceManager::getInstance()->addTextureWithFile(BLOOD_ENEMY_SPRITE);
	M2DXResourceManager::getInstance()->addTextureWithFile(WEPON_SPRITE);
	M2DXResourceManager::getInstance()->addTextureWithFile("TileScreen\\TileScreen.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("TileScreen\\BatScreenSheet.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("TileScreen\\PushEnter.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("Intro\\Intro.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("Intro\\Cloud.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("Intro\\BlackBatSheet.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("Map\\FullMap.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("Map\\SimonFromMap.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("Map\\BossFromMapSheet.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("Resources\\Sprites\\MagicalCrystal\\MagicalCrystalSheet.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("EndGame\\EndGame.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("EndGame\\Castle1.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("EndGame\\DangMinhTuan.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("EndGame\\TranTienThang.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("EndGame\\TruongVinhTien.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("EndGame\\GVHD.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("EndGame\\End.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("EndGame\\End.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("Pause\\Resume.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("Pause\\GameOver.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("Pause\\btnResume.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("Pause\\btnRestart.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("Pause\\btnExit.png");
	M2DXResourceManager::getInstance()->addTextureWithFile(HOLY_WATER_SPRITE);
	M2DXResourceManager::getInstance()->addTextureWithFile(DAGGER_SPRITE);
	M2DXResourceManager::getInstance()->addTextureWithFile(BLOCK_SPRITE);
	M2DXResourceManager::getInstance()->addTextureWithFile("Resources\\Sprites\\ChunkFromBrokenBlock.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("Resources\\Sprites\\WeaponsItem\\MorningStar.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("Resources\\Sprites\\PorkChop\\PorkChop.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("Resources\\Sprites\\WeaponsItem\\Axe.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("Resources\\Sprites\\WeaponsItem\\Boomerang.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("Resources\\Sprites\\WeaponsItem\\Dagger.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("Resources\\Sprites\\WeaponsItem\\FireBomb.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("Resources\\Sprites\\WeaponsItem\\Watch.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("Resources\\Sprites\\Crown\\CrownSheet.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("Resources\\Sprites\\TreasureChest\\TreasureChestSheet.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("Resources\\Sprites\\Thorns\\Chain.png");
	M2DXResourceManager::getInstance()->addTextureWithFile(THORNS_SPRITE);
	M2DXResourceManager::getInstance()->addTextureWithFile("Resources\\Sprites\\Cross.png");
	M2DXResourceManager::getInstance()->addTextureWithFile("Resources\\Sprites\\ipotion.png");
	//add sound
	M2DXResourceManager::getInstance()->addSoundWithFile("Sound\\sound\\falling.wav");
	M2DXResourceManager::getInstance()->addSoundWithFile("Sound\\sound\\usingwhip.wav");
	M2DXResourceManager::getInstance()->addSoundWithFile("Sound\\sound\\splashwater.wav");
	M2DXResourceManager::getInstance()->addSoundWithFile("Sound\\sound\\collectitem.wav");
	M2DXResourceManager::getInstance()->addSoundWithFile("Sound\\sound\\hit.wav");
	M2DXResourceManager::getInstance()->addSoundWithFile("Sound\\sound\\hitcannon.wav");
	M2DXResourceManager::getInstance()->addSoundWithFile("Sound\\sound\\opendoor.wav");
	M2DXResourceManager::getInstance()->addSoundWithFile("Sound\\sound\\decreaseweaponusepoint.wav");
	M2DXResourceManager::getInstance()->addSoundWithFile("Sound\\sound\\getscoretimer.wav");
	M2DXResourceManager::getInstance()->addSoundWithFile("Sound\\sound\\getscoreweapon.wav");
	M2DXResourceManager::getInstance()->addSoundWithFile("Sound\\music\\map1.wav");
	M2DXResourceManager::getInstance()->addSoundWithFile("Sound\\music\\map2.wav");
	M2DXResourceManager::getInstance()->addSoundWithFile("Sound\\music\\Boss.wav");
	M2DXResourceManager::getInstance()->addSoundWithFile("Sound\\music\\Stage_Clear.wav");
	M2DXResourceManager::getInstance()->addSoundWithFile("Sound\\music\\Title_Theme.wav");
	M2DXResourceManager::getInstance()->addSoundWithFile("Sound\\music\\Life_Lost.wav");
	M2DXResourceManager::getInstance()->addSoundWithFile("Sound\\music\\GameOver.wav");
	return true;
}

void M2DXResourceManager::addTextureWithFile(LPCTSTR fileName)
{
	auto texture = M2DXD3DX::getInstance()->createTextureWithFile(fileName);

	textureMap.insert(M2DXTexturePair(getFileNameWithoutExtension(fileName), texture));
}

M2DXTexture* M2DXResourceManager::getTextureByName(LPCTSTR textureName)
{
	auto result = textureMap[textureName];
	return textureMap[textureName];
}

void M2DXResourceManager::addSoundWithFile(LPCTSTR fileName)
{
	auto sound = M2DXDSound::getInstance()->createSoundWithFile(fileName);

	soundMap.insert(M2DXSoundPair(getFileNameWithoutExtension(fileName), sound));
}

CSound* M2DXResourceManager::getSoundByName(LPCTSTR soundName)
{
	return soundMap[soundName];
}
