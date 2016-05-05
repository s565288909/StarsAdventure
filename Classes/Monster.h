#pragma once

#include "cocos2d.h"

class Monster : public cocos2d::Node
{
public:
	Monster();
	~Monster();
	enum State
	{
		Idle,
		Walk,
		Attack,
		Dead
	}m_State;
	void initData();
	Monster* getNode();
	Monster* getNowNode();

};