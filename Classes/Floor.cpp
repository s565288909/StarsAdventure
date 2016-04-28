#include "Floor.h"

USING_NS_CC;

Floor::Floor(){}

Floor::~Floor(){}

Vector<Rect> Floor::getWallsRects(){
    Vector<Rect> vec;
    vec.pushBack(this->getChildByName("wall_1")->getBoundingBox());
    vec.pushBack(this->getChildByName("wall_2")->getBoundingBox());
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