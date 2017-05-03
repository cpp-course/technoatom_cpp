#ifndef CONSTANTS_H
#define CONSTANTS_H

const size_t WINDOW_X = 1024;
const size_t WINDOW_Y = 512;

const size_t BLOCK_X = 50;
const size_t BLOCK_Y = 50;

const size_t DIFF_LEVEL = 1;
const float FREE_FALL_ACC = 0.6;
//---------------------------
// Paramaters of Heroes
//---------------------------
const size_t WIZ_HP = 5;
const size_t WIZ_ARMOUR = 2;
const size_t WIZ_MANA = 13;

const size_t WAR_HP = 10;
const size_t WAR_ARMOUR = 7;
const size_t WAR_MANA = 3;

const size_t ARC_HP = 7;
const size_t ARC_ARMOUR = 7;
const size_t ARC_MANA = 6;

const size_t ZOM_HP = 5 * DIFF_LEVEL;
const size_t ZOM_ARMOUR = 2 * DIFF_LEVEL;
const size_t ZOM_MANA = 0;

const size_t SKE_HP = 3 * DIFF_LEVEL;
const size_t SKE_ARMOUR = 3 * DIFF_LEVEL;
const size_t SKE_MANA = 0;
//---------------------------

enum DirectType
{
	LEFT,
	RIGHT
};
enum HeroType
{
	Wizard,
	Warrior,
	Archer,
	Zombie,
	Skeleton
};
const char * GetFilename(HeroType type)
{
	switch (type)
	{
	case Wizard:
		return "Wizard.png";
	case Warrior:
		return "Warrior.png";
	case Archer:
		return "Archer.png";
	case Zombie:
		return "Zombie.png";
	case Skeleton:
		return "Skeleton.png";
	default:
		return "DefaultHero.png";
	}
}
enum BlockType
{
	Dirt,
	Stone,
	Platform
};
const char * GetBlockType(BlockType type)
{
	switch (type)
	{
	case Dirt:
		return "Dirt.png";
	case Stone:
		return "Stone.png";
	case Platform:
		return "Platform.png";
	default:
		return "DefaultBlock.png";
	}
}
enum ProjType
{
	Fireball,
	Arrow
};
const char * GetLvlFile(size_t lvl_num)
{
	switch (lvl_num)
	{
	case 0:
		return "tutorial.txt";
	case 1:
		return "first.txt";
	default:
		return "tutorial.txt";
		break;
	}
}
#endif