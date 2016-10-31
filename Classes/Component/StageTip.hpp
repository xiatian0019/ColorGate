//
//  StageTip.hpp
//  ColorGate
//
//  Created by xiaoming on 16/5/5.
//
//

#ifndef StageTip_hpp
#define StageTip_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
#include "GameSetting.h"

class StageTip : public Node
{
public:
    StageTip(GATE_POS gatePos,GATE_COLOR gateColor);
    void updateState(GATE_POS gatePos,GATE_COLOR gateColor);
private:
    std::string getPosDesc(GATE_POS gatePos);
    Label *label1;
    Label *label2;
    Label *label3;
    ui::Scale9Sprite *backSp;
};

#endif /* StageTip_hpp */
