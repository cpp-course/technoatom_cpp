#include "objects.h"
#include "Constants.h"


GameObject::GameObject(sf::Vector2f pos, sf::String filename) :
	filename_(filename)
{
	sf::Image image;
	image.loadFromFile("Textures/" + filename);
	sf::Texture texture;
	texture.loadFromImage(image);
	sprite_.setTexture(texture);
	size_.x = image.getSize().x;
	size_.y = image.getSize().y;
	pos_.x = pos.x + size_.x / 2;
	pos_.y = pos.y + size_.y / 2;
	sprite_.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), size_));
	sprite_.setOrigin(size_.x / 2, size_.y / 2);
	sprite_.setPosition(pos_);
}
const sf::Vector2f & GameObject::getPos() const
{
	return pos_;
}
const sf::Vector2i & GameObject::getSize() const
{
	return size_;
}
//----------------------------------------------------------------------------------
DynamicObject::DynamicObject(sf::Vector2f pos, sf::Vector2f v0, sf::String filename) :
	GameObject(pos, filename),
	direction_(RIGHT),
	v0_(v0),
	v_(sf::Vector2f(0.0f, 0.0f))
{
	size_.x = image_.getSize().y;
	sprite_.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), size_));
	sprite_.setOrigin(size_.x / 2, size_.y / 2);
}
void DynamicObject::Control()
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
void DynamicObject::Physics(float dt)
{
	pos_ += v_*dt;
	if (gravity_ && !is_on_floor_)
		v_.y += FREE_FALL_ACC*dt;
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
DynamicObject::~DynamicObject()
{
	//??????????????????????????
}
DirectType DynamicObject::GetDirection()
{
	return direction_;
}
void DynamicObject::SetDirection(DirectType direct)
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
sf::Vector2f DynamicObject::GetVelo()
{
	return v_;
}
void DynamicObject::SetVelo(sf::Vector2f v)
{
	v_ = v;
}
sf::Vector2f DynamicObject::GetVelo0()
{
	return v0_;
}
bool DynamicObject::GetGravity()
{
	return gravity_;
}
void DynamicObject::SetGravity(bool gravity)
{
	gravity_ = gravity;
}
bool DynamicObject::GetIsOnFloor()
{
	return is_on_floor_;
}
void DynamicObject::SetIsOnFloor(bool is_on_floor)
{
	is_on_floor_ = is_on_floor;
}
//----------------------------------------------------------------------------------
StaticObject::StaticObject(sf::Vector2f pos, BlockType type) :
	GameObject(pos, GetBlockType(type))
{}
StaticObject::~StaticObject()
{
	//?????????????????????????
}
BlockType StaticObject::GetType()
{
	return type_;
}
//----------------------------------------------------------------------------------
Hero::Hero(sf::Vector2f pos, sf::Vector2f v0, HeroType type):
	DynamicObject(pos, v0, GetFilename(type))
{
	switch (type)
	{
	case Wizard:
		Init(WIZ_HP, WIZ_ARMOUR, WIZ_MANA);
		break;
	case Warrior:
		Init(WAR_HP, WAR_ARMOUR, WAR_MANA);
		break;
	case Archer:
		Init(ARC_HP, ARC_ARMOUR, ARC_MANA);
		break;
	case Zombie:
		Init(ZOM_HP, ZOM_ARMOUR, ZOM_MANA);
		break;
	case Skeleton:
		Init(SKE_HP, SKE_ARMOUR, SKE_MANA);
		break;
	default:
		Init(0, 0, 0);
		break;
	}
}
Hero::~Hero()
{
	//?????????????????????????
}
HeroType Hero::GetType()
{
	return type_;
}
size_t Hero::GetHp()
{
	return hp_;
}
void Hero::SetHp(size_t newhp)
{
	hp_ = newhp;
}
size_t Hero::GetArmour()
{
	return armour_;
}
void Hero::SetArmour(size_t newarmour)
{
	armour_ = newarmour;
}
size_t Hero::GetMana()
{
	return mana_;
}
void Hero::SetMana(size_t newmana)
{
	mana_ = newmana;
}
void Hero::Init(const size_t hp, const size_t armour, const size_t mana)
{
	hp_ = hp;
	armour_ = armour;
	mana_ = mana;
}
