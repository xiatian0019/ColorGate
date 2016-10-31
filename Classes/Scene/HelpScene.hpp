//
//  HelpScene.hpp
//  ColorGate
//
//  Created by xiaoming on 16/5/5.
//
//

#ifndef HelpScene_hpp
#define HelpScene_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class HelpScene : public Layer
{
public:
    static Scene* createScene();
    bool init();
    CREATE_FUNC(HelpScene);
private:
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    float addHelpLabel(std::string labelTxt,Vec2 pos,float fontSize);
};

#endif /* HelpScene_hpp */
