#pragma once

#include "Enity.h"

class Player : public Enity
{
public:
	Player();
	~Player();
    enum State
    {
        Idle,
        Walk,
        JumpUp,
        JumpDown,
        Die,
        Attack,
        Drop
    } m_State;
	void initData();
	cocos2d::Rect getDropRect();
    void KeepIdle();
    void MoveLeft();
    void MoveRight();
    void StopMove();
    void Attacks();
    void Jumps(bool isDrop);
    void Dead();
	//碰撞后恢复移动的位置偏移
	void RestoreMove();
private:
	cocos2d::Vec2 m_pos;
    float moveSpeed;
    float jumpSpeed;
};