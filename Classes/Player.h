#pragma once

#include "cocos2d.h"
#include "Enity.h"
#include <cocostudio/CocoStudio.h>

class Player : public Enity
{
public:
	Player();
	~Player();
	void initData();
	static Player* Create(cocos2d::Node* node);
    void MoveLeft();
    void MoveRight();
    void StopMove();
    void Attack();
    void Jump();
    void Dead();
private:
	cocos2d::Vec2 m_pos;
    cocos2d::Node* leftNode;
    cocos2d::Node* rightNode;
    cocostudio::timeline::ActionTimeline* m_action;
    float moveSpeed;
    float jumpSpeed;
};