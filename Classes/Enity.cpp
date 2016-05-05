#include "Enity.h"

USING_NS_CC;
using namespace cocostudio::timeline;

Enity::Enity(){}

Enity::~Enity(){}

Node* Enity::getNowNode(){
	switch (m_Dir)
	{
	case Enity::Left:
		return leftNode;
	case Enity::Right:
		return rightNode;
	}
}
