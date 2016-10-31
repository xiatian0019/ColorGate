//
//  AboutScene.hpp
//  MagicSnake
//
//  Created by xiaoming on 15/12/30.
//
//

#ifndef AboutScene_hpp
#define AboutScene_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class AboutScene : public Layer
{
public:
    CREATE_FUNC(AboutScene);
    static Scene *createScene();
    bool init();
private:
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    std::vector<Label *>labelList;
    Label * addSpecialLabel(std::string labelTxt,Vec2 pos,Vec2 anchorPoint,bool setDimensions=false);
    void specialStart(float dt);
    void specialCall();
    int labelNum;
    Node *aboutNode;
};


#endif /* AboutScene_hpp */
