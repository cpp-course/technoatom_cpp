#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include <memory>

class GameObject
{
public:
	GameObject(sf::Vector2f pos, sf::String filename);
	const sf::Vector2f &getPos() const;
	const sf::Vector2i &getSize() const;
	/*virtual*/ void Draw(sf::RenderTarget *win)
	{
		sprite_.setPosition(pos_);
		win->draw(sprite_);
	}
protected:
	//void SetSprite(sf::String filename);
	sf::String filename_;
	sf::Image image_;
	sf::Texture texture_;
	sf::Sprite sprite_;
	sf::Vector2f pos_;	//! coords of an object
	sf::Vector2i size_;	//! size of an object
};

class DynamicObject : public GameObject
{
public:
	DynamicObject(sf::Vector2f pos, sf::Vector2f v0, sf::String filename);
	void Control();
	void Physics(float dt);
	void Intersection();
	void setDirection(DirectType direct);
protected:
	DirectType direction_;
	sf::Vector2f v_, v0_;
	bool gravity_;
	bool is_on_floor_ = false;
};

class StaticObject : public GameObject
{
public:
	StaticObject(sf::Vector2f pos, BlockType type);
	BlockType type_;
};

class Hero : public DynamicObject
{
public:
	Hero(sf::Vector2f pos, sf::Vector2f v0, HeroType type);
	void Attack();
protected:
	void Init(const size_t hp, const size_t armour, const size_t mana);
	HeroType type_;
	size_t hp_;
	size_t armour_;
	size_t mana_;
};

class Projectile : public DynamicObject
{

};

/*
StaticObject *TileMap[M_HEIGHT][M_WIDTH] = {};

void init_static_obj(sf::RenderTarget *win)
{
	SET(Platform, 6, 0, win);
	SET(Platform, 6, 1, win);
	SET(Platform, 5, 2, win);
	SET(Platform, 5, 3, win);
	SET(Platform, 4, 4, win);
	SET(Platform, 4, 5, win);
	SET(Platform, 3, 6, win);
	SET(Platform, 3, 7, win);
	SET(Platform, 2, 8, win);
	SET(Platform, 2, 9, win);
	SET(Platform, 1, 10, win);
	SET(Platform, 1, 11, win);
	SET(Platform, 2, 12, win);
	SET(Platform, 2, 13, win);
	SET(Platform, 4, 14, win);
	SET(Platform, 4, 15, win);
	SET(Platform, 6, 16, win);
	SET(Platform, 6, 17, win);
}

void draw_static_obj()
{
	for (size_t i = 0; i < M_HEIGHT; ++i)
		for (size_t j = 0; j < M_WIDTH; ++j)
			if (TileMap[i][j])
				TileMap[i][j]->Draw();
}

void delete_stat_obj()
{
	for (size_t i = 0; i < M_HEIGHT; ++i)
		for (size_t j = 0; j < M_WIDTH; ++j)
			delete TileMap[i][j];
}
*/
