#pragma once

#include "cocos2d.h"
#include "Enity.h"
#include "cocostudio\CocoStudio.h"

class Player : public Enity
{
public:
	Player();
	~Player();
	void initData();
	static Player* Create(cocos2d::Node* node);
private:
	cocos2d::Vec2 m_pos;
	cocostudio::Armature* arm;
};