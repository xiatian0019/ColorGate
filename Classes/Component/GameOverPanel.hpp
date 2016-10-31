//
//  GameOverPanel.hpp
//  MiniGameHor
//
//  Created by xiaoming on 16/6/28.
//
//

#ifndef GameOverPanel_hpp
#define GameOverPanel_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
class GameOverPanel : public Layer
{
public:
    GameOverPanel(int newScore);
    ~GameOverPanel();
};


#endif /* GameOverPanel_hpp */
