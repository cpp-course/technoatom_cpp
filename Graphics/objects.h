#pragma once

class GameObject
{
public:
	virtual void Draw() = 0;
	int x, y;
};

class DynamicObject : public GameObject
{
public:
	virtual void Move() = 0;
	size_t speed_;
};

class StaticObject : public GameObject
{

};

class Hero : public DynamicObject
{
public:
	Hero();
	virtual void Attack() = 0;
	virtual void Jump() = 0;
	size_t hp_;
	size_t armour_;
	size_t mana_;
};

class Projectile : public DynamicObject
{
};

class Wizard : public Hero
{
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

class Stars : public StaticObject
{

};

class Wall : public StaticObject
{

};

class Water : public StaticObject
{

};

class Lava : public StaticObject
{

};

class Thorns : public StaticObject
{

};