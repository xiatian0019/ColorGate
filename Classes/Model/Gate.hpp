//
//  Gate.hpp
//  ColorGate
//
//  Created by xiaoming on 16/4/28.
//
//

#ifndef Gate_hpp
#define Gate_hpp
#include <stdio.h>
#include "cocos2d.h"
#include "GameSetting.h"
USING_NS_CC;

class Gate : public Node
{
public:
    Gate(GATE_COLOR gateColor,GATE_POS gatePos);
    GATE_POS getGatePos();
    GATE_COLOR getGateColor();
    std::string getPressSoundEffect();
    void gateFadeIn();
    static Color3B getColor3B(GATE_COLOR color);
    static Color4B getColor4B(GATE_COLOR color);
    void onExit();
private:
    GATE_COLOR myColor;
    GATE_POS myPos;
    //LayerColor *bg;
    Sprite *bg;

};

#endif /* Gate_hpp */
