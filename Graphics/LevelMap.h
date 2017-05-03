#ifndef LEVELMAP_H
	#define LEVELMAP_H
	#include <SFML/Graphics.hpp>
#endif

#include "Constants.h"
#include "objects.h"
#include <fstream>

class LevelMap
{
public:
	LevelMap(size_t lvl_num);
	~LevelMap();
protected:
	void Init(size_t lvl_num);
	size_t width_, height_;
	std::vector<std::vector<StaticObject*>> Map;
};
LevelMap::LevelMap(size_t lvl_num):
	width_(0),
	height_(0)
{
	Init(lvl_num);
}
LevelMap::~LevelMap()
{
	for (int i = 0;i < height_;i++)
		for (int j = 0;j < width_;j++)
			delete Map[i][j];
}
void LevelMap::Init(size_t lvl_num)
{
	char * buff;
	const char* l = GetLvlFile(lvl_num);
	std::ifstream lvl(l);
	//if(!lvl.is_open())
	lvl >> height_;
	lvl >> width_;
	for (int i = 0;i < height_;i++)
	{
		lvl >> buff;
		for (int j = 0;j < width_;j++)
		{
			switch (buff[j])
			{
			case '0':	//Dirt
				Map[i][j] = new StaticObject(sf::Vector2f(j*BLOCK_X, i*BLOCK_Y), Dirt);
				break;
			case '1':	//Stone
				Map[i][j] = new StaticObject(sf::Vector2f(j*BLOCK_X, i*BLOCK_Y), Stone);
				break;
			case '2':	//Platform
				Map[i][j] = new StaticObject(sf::Vector2f(j*BLOCK_X, i*BLOCK_Y), Platform);
				break;
			default:
				break;
			}
		}
	}
}