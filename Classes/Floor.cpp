#include "Floor.h"

USING_NS_CC;

Floor::Floor(){}

Floor::~Floor(){}

std::vector<Rect> Floor::getBoardsRects(){
    std::vector<Rect> vec;
    vec.push_back(this->getChildByName("board_1")->getBoundingBox());
    vec.push_back(this->getChildByName("board_2")->getBoundingBox());
    return vec;
}

Vector<Sprite*> Floor::getBlocksSprites(){
	Vector<Sprite*> vec;
	for (int i = 0; i < 12; i++)
	{
		vec.pushBack((Sprite*)this->getChildByName("block_" + Value(i + 1).asString()));
	}
	return vec;
}