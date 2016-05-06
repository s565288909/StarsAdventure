//
//  DefineUtils.h
//  StarsAdventure
//
//  Created by 史潇 on 16/5/1.
//
//

#ifndef DefineUtils_h
#define DefineUtils_h

#include <cocos2d.h>

USING_NS_CC;

#define JumpUpAction EaseSineOut::create(MoveBy::create(0.35f, Vec2(0, 300)))

#define JumpDownActions MoveBy::create(4,Vec2(0,-3000))

#define DropActions MoveBy::create(3,Vec2(0,-3000))




#endif /* DefineUtils_h */
