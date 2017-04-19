#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class GameObject
{
public:
	GameObject(size_t x, size_t y, size_t w, size_t h, sf::String filename)
	{
		x_ = x;
		y_ = y;
		w_ = w;
		h_ = h;
		image_.loadFromFile("Textures/" + filename);
		texture_.loadFromImage(image_);
		sprite_.setTexture(texture_);
		sprite_.setTextureRect(sf::IntRect(0, 0, w_, h_));
		sprite_.setPosition(x_, y_);
	}
	virtual void Draw() = 0;
	sf::String filename_;
	sf::Image image_;
	sf::Texture texture_;
	sf::Sprite sprite_;
	size_t x_, y_;	//! coords of an object
	size_t w_, h_;	//! params of an object
};

class DynamicObject : public GameObject
{
public:
	DynamicObject(size_t x, size_t y, size_t w, size_t h, sf::String filename, size_t speed):GameObject(x, y, w, h, filename)
	{
		speed_ = speed;
		y0_ = y;
		y0speed_ = 5;
		yspeed_ = 0;
		ffa_ = 0.4;
		direction_ = 0;
	}
	virtual void Move(float time) = 0;
	size_t direction_;
	float speed_;
	float y0speed_;
	size_t y0_;
	float yspeed_;
	float ffa_;
};

class StaticObject : public GameObject
{

};

class Hero : public DynamicObject
{
public:
	Hero();
	Hero(size_t x, size_t y, size_t w, size_t h, sf::String filename, size_t speed, size_t hp, size_t armour, size_t mana)
		:DynamicObject(x, y, w, h, filename, speed)
	{
		hp_ = hp;
		armour_ = armour;
		mana_ = mana;
	}
	virtual void Attack() = 0;
	virtual void Jump() = 0;
	size_t hp_;
	size_t armour_;
	size_t mana_;
};

class Wizard : public Hero
{
public:
	Wizard(size_t x, size_t y, size_t w, size_t h, sf::String filename, size_t speed, size_t hp, size_t armour, size_t mana)
		:Hero(x, y, w, h, filename, speed, hp, armour, mana){}
	void Attack() override
	{

	}
	void Jump() override
	{
		if (y_ == y0_ && yspeed_ == 0)
			yspeed_ = y0speed_;
		y_ -= yspeed_;
		yspeed_ -= ffa_;
		if (y_ >= y0_)
		{
			y_ = y0_;
			yspeed_ = 0;
		}
		sprite_.setPosition(x_, y_);
	}
	void Move(float time) override
	{
		switch (direction_)
		{
		case 0: //left
			x_ -= speed_*time;
			break;
		case 1:	//right
			x_ += speed_*time;
			break;
		}
		direction_ = -1;
		sprite_.setPosition(x_, y_);
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
