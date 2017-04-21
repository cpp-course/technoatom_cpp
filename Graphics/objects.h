#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Constants.h"

class GameObject
{
public:
	GameObject(sf::Vector2f pos, sf::Vector2i size, sf::String filename)
	{
		size_ = size;
		pos_.x = pos.x + size_.x / 2;
		pos_.y = pos.y + size_.y / 2;
		image_.loadFromFile("Textures/" + filename);
		texture_.loadFromImage(image_);
		sprite_.setTexture(texture_);
		sprite_.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), size_));
		sprite_.setOrigin(size_.x / 2, size.y / 2);
		sprite_.setPosition(pos_);
	}
	virtual void Draw() = 0;
protected:
	sf::String filename_;
	sf::Image image_;
	sf::Texture texture_;
	sf::Sprite sprite_;
	sf::Vector2f pos_;	//! coords of an object
	sf::Vector2i size_;	//! params of an object
};

class DynamicObject : public GameObject
{
public:
	DynamicObject(sf::Vector2f pos, sf::Vector2i size, sf::Vector2f speed, sf::String filename) :
		GameObject(pos, size, filename),
		direction_(RIGHT),
		v_(speed) {}
	
	virtual void Move() = 0;
	void DoPhysics(float dt)
	{
		if (!gravity_ || is_on_floor_)
			return;
		pos_ += v_*dt;
		v_.y -= FREE_FALL_ACC*dt;
	}
	void setDirection(DirectType direct)
	{
		direction_ = direct;
	}
protected:
	DirectType direction_;
	sf::Vector2f v_;
	bool gravity_;
	bool is_on_floor_;
};

class StaticObject : public GameObject
{

};

class Hero : public DynamicObject
{
public:
	Hero(sf::Vector2f pos, sf::Vector2i size, sf::Vector2f speed, sf::String filename, float jump_speed, size_t hp, size_t armour, size_t mana) :
		DynamicObject(pos, size, speed, filename),
		jump_speed_(jump_speed),
		hp_(hp),
		armour_(armour),
		mana_(mana) {}

	virtual void Attack() = 0;
	virtual void Jump() = 0;

protected:
	size_t hp_;
	size_t armour_;
	size_t mana_;
	float jump_speed_;
};

class Wizard : public Hero
{
public:
	Wizard(sf::Vector2f pos, sf::Vector2i size, sf::Vector2f speed, sf::String filename, float jump_speed, size_t hp, size_t armour, size_t mana) :
		Hero(pos, size, speed, filename, jump_speed, hp, armour, mana) {}
	
	void Attack() override
	{

	}
	void Jump() override
	{
		
	}
	void Move() override
	{
		switch (direction_)
		{
		case 0: //left
			pos_.x -= v_.x;
			break;
		case 1:	//right
			pos_.x += v_.x;
			break;
		}
		sprite_.setPosition(pos_);
	}
	void Draw() override
	{

	}
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

};
