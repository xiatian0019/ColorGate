//
//  MainScene.hpp
//  MiniGameHor
//
//  Created by xiaoming on 16/6/23.
//
//

#ifndef MainScene_hpp
#define MainScene_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class MainScene : public Layer
{
public:
    static Scene* createScene();
    bool init();
    CREATE_FUNC(MainScene);
private:
    void setButtons();
    void onStartClick(Ref *ref);
    void onHelpClick(Ref *ref);
    void onAboutClick(Ref *ref);
    void onRankClick(Ref *ref);
    MenuItemImage *soundOn;
    MenuItemImage *soundOff;
    void soundOnClick(Ref *ref);
    void soundOffClick(Ref *ref);
    void updateSoundSwitch(bool soundOn);
    
    void userEvaluate(float dt);
    void onEnter();
    Label *labelTitle;
};

#endif /* MainScene_hpp */
