#include "Player.h"
#include "DefineUtils.h"

USING_NS_CC;
using namespace cocostudio;

Player::Player(){}

Player::~Player(){}

void Player::initData(){
	isDead = false;
	HP = 100;
	MP = 0;
    moveSpeed = 3;
    jumpSpeed = 3;
    this->runAction(m_TimeLineAction);
	leftNode = this->getChildByName("Player_Left");
	rightNode = this->getChildByName("Player_Right");
	leftNode->setVisible(false);
	rightNode->setVisible(false);
	m_Dir = Direction::Left;
	switch (m_Dir)
	{
	case Direction::Left:
		leftNode->setVisible(true);
		break;
	case Direction::Right:
		rightNode->setVisible(true);
		break;
	}
	m_TimeLineAction->play("P_Idle", true);
	m_State = State::Idle;
	this->setPosition(545,196);
}

Rect Player::getDropRect(){
	return Rect(this->getPositionX() - getNowNode()->getBoundingBox().size.width / 4, this->getPositionY() - getNowNode()->getBoundingBox().size.height / 2, getNowNode()->getBoundingBox().size.width / 2, getNowNode()->getBoundingBox().size.height);
}

void Player::KeepIdle(){
    this->stopAllActions();
	m_TimeLineAction->play("P_Idle", true);
    m_State = State::Idle;
}

void Player::MoveLeft()
{
    if (m_State==State::Idle) {
        if (m_Dir != Direction::Left) {
			m_Dir = Direction::Left;
            leftNode->setVisible(true);
            rightNode->setVisible(false);
        }
		m_TimeLineAction->play("P_Walk", true);
        m_State = State::Walk;
    }
    this->setPositionX(this->getPositionX()-moveSpeed);
}

void Player::MoveRight()
{
    if (m_State==State::Idle) {
        if (m_Dir != Direction::Right) {
			m_Dir = Direction::Right;
            leftNode->setVisible(false);
            rightNode->setVisible(true);
        }
        m_TimeLineAction->play("P_Walk", true);
        m_State = State::Walk;
    }
    this->setPositionX(this->getPositionX()+moveSpeed);
}

void Player::StopMove(){
	m_TimeLineAction->play("P_Idle", true);
    m_State = State::Idle;
}

void Player::Jumps(bool isDrop){
    if (m_State!=State::JumpUp && m_State!=State::JumpDown && m_State!=State::Attack) {
		m_TimeLineAction->play("P_Jump", false);
//        m_action->setAnimationEndCallFunc("P_Jump", [&]{
//            m_action->play("P_Idle", true);
//            m_State = State::Idle;
//        });
        if (isDrop) {
			m_State = State::JumpDown;
			this->runAction(JumpDownAction);
        }
        else{
			auto action = Sequence::create(JumpUpAction, CallFunc::create([&]{
				m_State = State::JumpDown;
				CCLOG("JumpDown Over");
			}), nullptr);
			this->runAction(Sequence::create(action, JumpDownAction, nullptr));
        }
    }
}

void Player::Attacks()
{
    if (m_State!=State::JumpUp && m_State!=State::JumpDown) {
		m_TimeLineAction->play("P_Attack", false);
        
		m_TimeLineAction->setAnimationEndCallFunc("P_Attack", [&]{
			m_TimeLineAction->play("P_Idle", true);
            m_State = State::Idle;
        });
        m_State = State::Attack;
    }

}

void Player::RestoreMove(){
	switch (m_Dir)
	{
	case Enity::Left:
		this->setPositionX(this->getPositionX() + moveSpeed);
		break;
	case Enity::Right:
		this->setPositionX(this->getPositionX() - moveSpeed);
		break;
	}
}
