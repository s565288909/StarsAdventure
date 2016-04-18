#pragma once

#include "cocos2d.h"

class Enity : public cocos2d::Ref
{
public:
	Enity();
	~Enity();
	cocos2d::Node* getNode();
	void setNode(cocos2d::Node* node);
protected:
	cocos2d::Node* m_Node;
	int HP;
	int MP;
	bool isDead;
	//Enity�����ö��
	enum Dir
	{
		Left,
		Right
	} m_Dir;
	//Entiy��״̬ö��
	enum State
	{
		Idle,
		Walk,
		Jump,
		Die,
		Attack
	} m_State;
};