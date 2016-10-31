//
//  StageTip.cpp
//  ColorGate
//
//  Created by xiaoming on 16/5/5.
//
//

#include "StageTip.hpp"
#include "Dialog.hpp"

StageTip::StageTip(GATE_POS gatePos,GATE_COLOR gateColor)
{
    backSp = ui::Scale9Sprite::create("tipsBack.png");
    this->addChild(backSp);
    label1=Label::createWithSystemFont("", FONT_HELVETICA_BOLD, 26);
    label1->setAnchorPoint(Vec2(0, 0.5));
    this->addChild(label1);
    
    label2=Label::createWithSystemFont(this->getPosDesc(gatePos), FONT_HELVETICA_BOLD, 36);
    label2->setAnchorPoint(Vec2(0, 0.5));
    label2->setColor(Color3B(255, 0, 0));
    this->addChild(label2);
    
    label3=Label::createWithSystemFont(Dialog::getInstance()->getStringByID(TXT_STAGE_TIPS_END), FONT_HELVETICA_BOLD, 26);
    label3->setAnchorPoint(Vec2(0, 0.5));
    this->addChild(label3);
    this->setAnchorPoint(Vec2(0.5, 0.5));
    this->updateState(gatePos,gateColor);
    this->autorelease();
}


void StageTip::updateState(GATE_POS gatePos,GATE_COLOR gateColor)
{
    if (gatePos==NONE) {
        if (gateColor==ANY) {
            label1->setString(Dialog::getInstance()->getStringByID(TXT_TIPS_ANY));
        }
        else{
            label1->setString(Dialog::getInstance()->getStringByID(TXT_TIPS_LAST));
        }
        label2->setVisible(false);
        label3->setVisible(false);
        this->setContentSize(Size(label1->getContentSize().width+5, 60));
    }
    else{
        label1->setString(Dialog::getInstance()->getStringByID(TXT_STAGE_TIPS_START));
        label2->setVisible(true);
        label3->setVisible(true);
        label2->setString(this->getPosDesc(gatePos));
        label2->setPositionX(label1->getPositionX()+label1->getContentSize().width+5);
        label3->setPositionX(label2->getPositionX()+label2->getContentSize().width+5);
        this->setContentSize(Size(label3->getPositionX()+label3->getContentSize().width+5, 55));
    }
    
    backSp->setContentSize(Size(this->getContentSize().width+40, this->getContentSize().height));
    backSp->setPosition(Vec2(this->getContentSize().width/2, 0));
}

std::string StageTip::getPosDesc(GATE_POS gatePos)
{
    std::string desc="";
    switch (gatePos) {
        case LEFT:
            desc=Dialog::getInstance()->getStringByID(TXT_STAGE_TIPS_LEFT);
            break;
        case CENTER:
            desc=Dialog::getInstance()->getStringByID(TXT_STAGE_TIPS_MIDDLE);
            break;
        case RIGHT:
            desc=Dialog::getInstance()->getStringByID(TXT_STAGE_TIPS_RIGHT);
            break;
        default:
            break;
    }
    return desc;
}