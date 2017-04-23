#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include <memory>

const size_t M_HEIGHT = 8;
const size_t M_WIDTH = 16;



template <typename T>
const sf::Vector2<T> vec0 = sf::Vector2<T>(0, 0);

class GameObject
{
public:
	GameObject(sf::Vector2f pos, sf::RenderTarget *win, sf::String filename) :
		win_(win),
		filename_(filename)
	{
		image_.loadFromFile("Textures/" + filename);
		size_.x = image_.getSize().x;
		size_.y = image_.getSize().y;
		pos_.x = pos.x + size_.x / 2;
		pos_.y = pos.y + size_.y / 2;
		texture_.loadFromImage(image_);
		sprite_.setTexture(texture_);
		sprite_.setTextureRect(sf::IntRect(vec0<int>, size_));
		sprite_.setOrigin(size_.x / 2, size_.y / 2);
		sprite_.setPosition(pos_);
	}

	/*virtual*/ void Draw()
	{
		sprite_.setPosition(pos_);
		win_->draw(sprite_);
	}
	
	const sf::Vector2f &getPos() const
	{
		return pos_;
	}

	const sf::Vector2i &getSize() const
	{
		return size_;
	}

protected:
	sf::String filename_;
	sf::Image image_;
	sf::Texture texture_;
	sf::Sprite sprite_;
	sf::RenderTarget *win_;
	sf::Vector2f pos_;	//! coords of an object
	sf::Vector2i size_;	//! params of an object
};

class DynamicObject : public GameObject
{
public:
	DynamicObject(sf::Vector2f pos, sf::RenderTarget *win, sf::Vector2f v0, sf::String filename) :
		GameObject(pos, win, filename),
		direction_(RIGHT),
		v0_(v0),
		v_(vec0<float>)
	{
		size_.x = image_.getSize().y;
		sprite_.setTextureRect(sf::IntRect(vec0<int>, size_));
		sprite_.setOrigin(size_.x / 2, size_.y / 2);
	}

	void Control()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			setDirection(RIGHT);
			v_.x = v0_.x;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			setDirection(LEFT);
			v_.x = -v0_.x;
		}
		else
			v_.x = 0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && is_on_floor_)
		{
			is_on_floor_ = false;
			v_.y = -v0_.y;
		}
	}

	void Physics(float dt)
	{
		pos_ += v_*dt;
		if (gravity_ && !is_on_floor_)
			v_.y += FREE_FALL_ACC*dt;
	}

	void Intersection();

	void setDirection(DirectType direct)
	{
		switch (direction_ = direct)
		{
		case RIGHT:
			sprite_.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), size_));
			break;
		case LEFT:
			sprite_.setTextureRect(sf::IntRect(sf::Vector2i(size_.x, 0), size_));
		}
	}
protected:
	DirectType direction_;
	sf::Vector2f v_, v0_;
	bool gravity_;
	bool is_on_floor_ = false;
};

class StaticObject : public GameObject
{
public:
	StaticObject(sf::Vector2f pos, sf::RenderTarget *win, sf::String filename) :
		GameObject(pos, win, filename) {}
};

class Hero : public DynamicObject
{
public:
	Hero(sf::Vector2f pos, sf::RenderTarget *win, sf::Vector2f v0, sf::String filename, size_t hp, size_t armour, size_t mana) :
		DynamicObject(pos, win, v0, filename),
		hp_(hp),
		armour_(armour),
		mana_(mana) {}

	virtual void Attack() = 0;

protected:
	size_t hp_;
	size_t armour_;
	size_t mana_;
};

class Wizard : public Hero
{
public:
	Wizard(sf::Vector2f pos, sf::RenderTarget *win) :
		Hero(pos, win, sf::Vector2f(wiz_speed, wiz_jump), "Wizard.png", wiz_hp, wiz_armour, wiz_mana)
	{
		gravity_ = true;
	}
	
	void Attack() override
	{

	}
private:
	static const size_t wiz_speed = 5; // float
	static const size_t wiz_jump = 15; // float
	static const size_t wiz_hp = 5;
	static const size_t wiz_armour = 2;
	static const size_t wiz_mana = 10;
};

class Archer : public Hero
{

};

class Warrior : public Hero
{

};

class Projectile : public DynamicObject
{

};

class Fireball : public Projectile
{

};

class Arrow : public Projectile
{

};

class Bullet : public Projectile
{

};

class Boss : public Hero
{

};

class Zombie : public Hero
{

};

class Skeleton : public Hero
{

};

class Platform : public StaticObject
{
public:
	Platform(sf::Vector2f pos, sf::RenderTarget *win) :
		StaticObject(pos, win, "Platform.png") {}

};

StaticObject *TileMap[M_HEIGHT][M_WIDTH] = {};

#define SET(stat_what, i, j, win) TileMap[i][j] = new stat_what(sf::Vector2f(j*BLOCK_X, i*BLOCK_Y), win)

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

void DynamicObject::Intersection()
{
	size_t i = (pos_.y + size_.y / 2) / BLOCK_Y, j = pos_.x / BLOCK_X;
	if (!TileMap[i][j])
	{
		is_on_floor_ = false;
	}
	else if (0 < TileMap[i][j]->getPos().y - pos_.y &&
		TileMap[i][j]->getPos().y - pos_.y <= TileMap[i][j]->getSize().y / 2 + size_.y / 2 && v_.y > 0)
	{
		pos_.y = TileMap[i][j]->getPos().y - (TileMap[i][j]->getSize().y / 2 + size_.y / 2);
		v_.y = 0;
		is_on_floor_ = true;
	}
	if (pos_.y >= WINDOW_Y - size_.y / 2)
	{
		is_on_floor_ = true;
		pos_.y = WINDOW_Y - size_.y / 2;
		v_.y = 0;
	}
	if (pos_.x < size_.x / 2)
	{
		pos_.x = size_.x / 2;
	}
	if (pos_.x > WINDOW_X - size_.x / 2)
	{
		pos_.x = WINDOW_X - size_.x / 2;
	}
}