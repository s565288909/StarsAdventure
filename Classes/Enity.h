#pragma once

#include "cocos2d.h"

class Enity : public cocos2d::CCObject
{
public:
	Enity();
	~Enity();
	cocos2d::Node* getNode();
protected:
	cocos2d::Node* m_Node;
	int HP;
	int MP;
	bool isDead;

	enum Dir
	{
		Left,
		Right
	} m_Dir;
};