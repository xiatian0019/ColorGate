//
//  GateGroup.hpp
//  ColorGate
//
//  Created by xiaoming on 16/4/28.
//
//

#ifndef GateGroup_hpp
#define GateGroup_hpp

#include <stdio.h>
#include "Gate.hpp"
#include "GameSetting.h"

class GateGroupDelegate
{
public:
    virtual void gateCorrect(GATE_COLOR newColor,int lastPos)=0;
    virtual void gateWrong()=0;
    virtual void gatePress(GATE_COLOR gateColor,Vec2 point)=0;
};


class GateGroup : public Layer
{
public:
    GateGroup(GATE_COLOR correctColor);
    void setDelegate(GateGroupDelegate *delegate);
private:
    GATE_COLOR correctColor;
    void openTouchEvent();
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    Vec2 startPoint;
    std::vector<Gate *>gateList;
    void addGate();
    GateGroupDelegate *myDelegate;
    void gatePressed(bool correct,GATE_COLOR pressedColor,Vec2 gatePos);
    void addExplosionEffect(GATE_COLOR color,Vec2 point);
    void gateOpenAnime();
};

#endif /* GateGroup_hpp */
